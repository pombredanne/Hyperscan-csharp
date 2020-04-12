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

#include "hyperscan_platform_info.h"

using namespace Hyperscan::Platform;

PlatformInfo::PlatformInfo()
{
	const auto info = new hs_platform_info();
    const auto populate_platform_err = hs_populate_platform(info);
    if (populate_platform_err != HS_SUCCESS) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to populate platform infos.", populate_platform_err));
    }

    if (Runtime::Intrinsics::X86::Avx2::IsSupported)
    {
        info->cpu_features = HS_CPU_FEATURES_AVX2;
    }

    this->m_platform_info = info;
}

PlatformInfo::~PlatformInfo()
{
    this->!PlatformInfo();
}

PlatformInfo::!PlatformInfo()
{
    delete this->m_platform_info;
}

bool PlatformInfo::IsPlatformValid::get()
{
    return HS_SUCCESS == hs_valid_platform();
}

CpuFeature PlatformInfo::CpuFeature::get()
{
    return static_cast<Platform::CpuFeature>(this->m_platform_info->cpu_features);
}
