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

#include <vcclr.h>
#include <algorithm>
#include "hyperscan_utils.h"

using namespace System;
using namespace Runtime::InteropServices;

using namespace Hyperscan::Utils;

char* StringUtils::substring(const char* src, const long long start_index, const long long end_index) {
	const auto length = end_index - start_index;
	if (length < 0)
		return nullptr;

	const auto dest = new char[length + 1];

	std::copy(src + start_index, src + end_index, dest);
	dest[length] = '\0';

	return dest;
}

char* StringUtils::to_unmanaged(String^ string) {
	const pin_ptr<const wchar_t> pinned_input = PtrToStringChars(string);
	const size_t input_size = string->Length + 1;
	const auto input_ptr = new char[input_size];
	size_t chars_converted = 0;
	wcstombs_s(&chars_converted, input_ptr, input_size, pinned_input, string->Length);
	return input_ptr;
}

array<Byte>^ StringUtils::to_managed_array(char* input, const int len)
{
	const auto managed_array = gcnew array<Byte>(len);
	Marshal::Copy(static_cast<IntPtr>(input), managed_array, 0, len);
	return managed_array;
}