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

#include "hyperscan_utils.h"

using namespace System;
using namespace Runtime::InteropServices;

using namespace Hyperscan::Utils;

array<Byte>^ StringUtils::to_managed_array(char* input, const int len)
{
	const auto managed_array = gcnew array<Byte>(len);
	Marshal::Copy(static_cast<IntPtr>(input), managed_array, 0, len);
	return managed_array;
}

array<Byte>^ StringUtils::string_to_managed_array(String^ input, const int len)
{
	auto input_ptr = Marshal::StringToHGlobalAnsi(input);
	try {
		const auto managed_array = gcnew array<Byte>(len);
		Marshal::Copy(input_ptr, managed_array, 0, len);
		return managed_array;
	}
	finally
	{
		Marshal::FreeHGlobal(input_ptr);
	}
}