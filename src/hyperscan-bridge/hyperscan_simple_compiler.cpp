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

#include "hyperscan_simple_compiler.h"

using namespace Hyperscan::Compilation;

SimpleCompiler::SimpleCompiler(Expression^ expression, CompilerMode compilerMode) {
    this->m_expression_ = expression;
    this->m_compiler_mode_ = compilerMode;
}

void SimpleCompiler::Compile(Database^ database, PlatformInfo^ platformInfo)
{
    auto native_pattern = Marshal::StringToHGlobalAnsi(this->m_expression_->Pattern);
    const auto pattern_ptr = static_cast<char*>(native_pattern.ToPointer());
    hs_compile_error_t* compile_err;
    try
    {
        const pin_ptr<hs_database_t*> hs_database = &database->m_database;
        if (hs_compile(pattern_ptr, static_cast<unsigned int>(this->m_expression_->Flag), static_cast<unsigned int>(this->m_compiler_mode_), platformInfo->m_platform_info, hs_database, &compile_err) != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR: Unable to compile pattern ""{0}"": {1}", this->m_expression_->Pattern, gcnew String(compile_err->message)));
        }
    }
    finally
    {
        hs_free_compile_error(compile_err);
        Marshal::FreeHGlobal(native_pattern);
    }
}

IDictionary<int, Expression^>^ SimpleCompiler::ExpressionsById::get()
{
    const auto expressions_by_id =  gcnew Dictionary<int, Expression^>();
    expressions_by_id->Add(this->m_expression_->Id, this->m_expression_);
    return expressions_by_id;
}

CompilerMode SimpleCompiler::Mode::get()
{
    return this->m_compiler_mode_;
}
