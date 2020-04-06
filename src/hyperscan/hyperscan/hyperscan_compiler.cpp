// MIT License
// Copyright(c) 2020 Benjamin BOUGOT
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

#include "hyperscan_compiler.h"

using namespace Hyperscan::Compilation;

Compiler::Compiler(HyperscanContext^ context, String^ pattern) {
    this->m_context_ = context;
    this->m_context_->m_pattern = pattern;
    auto native_pattern = Marshal::StringToHGlobalAnsi(pattern);
    const auto pattern_ptr = static_cast<char*>(native_pattern.ToPointer());

    hs_compile_error_t* compile_err;
    const auto info = new hs_platform_info();
    try {
	    const pin_ptr<hs_database_t*> database = &this->m_context_->m_database;
        const auto populate_platform_err = hs_populate_platform(info);
        if (populate_platform_err != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to populate platform infos. Exiting.", populate_platform_err));
        }

        if (Runtime::Intrinsics::X86::Avx2::IsSupported)
        {
            info->cpu_features &= HS_CPU_FEATURES_AVX2;
        }

        if (hs_compile(pattern_ptr, HS_FLAG_UTF8, HS_MODE_BLOCK, info, database, &compile_err) != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("Unable to compile pattern ""{0}"": {1}", pattern, gcnew String(compile_err->message)));
        }

	    const pin_ptr<hs_scratch_t*> scratch = &this->m_context_->m_scratch;
        const auto alloc_scratch_err = hs_alloc_scratch(*database, scratch);
        if (alloc_scratch_err != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to allocate scratch space. Exiting.", alloc_scratch_err));
        }
    }
    finally {
        hs_free_compile_error(compile_err);
        Marshal::FreeHGlobal(native_pattern);
    }
}