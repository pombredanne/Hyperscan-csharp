// MIT License
// Copyright(c) 2020 Benjamin Bougot
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"

#include "hyperscan_multiple_compiler.h"

using namespace Hyperscan::Compilation;

MultipleCompiler::MultipleCompiler(List<Expression^>^ expressions, CompilerMode compilerMode) {
    this->m_expressions_ = expressions;
    this->m_compiler_mode_ = compilerMode;
}

void MultipleCompiler::Compile(Database^ database, PlatformInfo^ platformInfo)
{
    const auto expressions = new char* [this->m_expressions_->Count];
    const auto expression_ids = new unsigned int[this->m_expressions_->Count];
    const auto expression_flags = new unsigned int[this->m_expressions_->Count];
    for (auto i = 0; i < this->m_expressions_->Count; i++)
    {
        expressions[i] = static_cast<char*>(Marshal::StringToHGlobalAnsi(this->m_expressions_[i]->Pattern).ToPointer());
        expression_ids[i] = this->m_expressions_[i]->Id;
        expression_flags[i] = static_cast<unsigned int>(this->m_expressions_[i]->Flag);
    }

    hs_compile_error_t* compile_err;
    try
    {
        const pin_ptr<hs_database_t*> hs_database = &database->m_database;
        if (hs_compile_multi(expressions, expression_flags, expression_ids, this->m_expressions_->Count, static_cast<unsigned int>(this->m_compiler_mode_), platformInfo->m_platform_info, hs_database, &compile_err) != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR: Unable to compile expressions: {0}", gcnew String(compile_err->message)));
        }
    }
    finally
    {
        for (auto i = 0; i < this->m_expressions_->Count; i++)
        {
            Marshal::FreeHGlobal(safe_cast<IntPtr>(expressions[i]));
        }

        delete[] expression_ids;
        delete[] expression_flags;
        delete[] expressions;
        hs_free_compile_error(compile_err);
    }
}

IDictionary<int, Expression^>^ MultipleCompiler::ExpressionsById::get()
{
    const auto expressions_by_id = gcnew Dictionary<int, Expression^>();
    for each (Expression ^ expression in this->m_expressions_)
    {
        expressions_by_id->Add(expression->Id, expression);
    }

    return expressions_by_id;
}
CompilerMode MultipleCompiler::Mode::get()
{
    return this->m_compiler_mode_;
}
