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

#pragma once

#include "hyperscan_exception.h"
#include "hyperscan_database.h"
#include "hyperscan_platform_info.h"
#include "hyperscan_mode.h"
#include "hyperscan_compiler.h"

using namespace System;
using namespace Runtime::InteropServices;

using namespace Hyperscan::Core;
using namespace Hyperscan::Platform;
using namespace Hyperscan::Databases;
using namespace Exceptions;

namespace Hyperscan {
	namespace Compilation {
		/// <summary>
		/// Compiler which supports compiling only one regular expression pattern into Hyperscan database
		/// </summary>
		public ref class SimpleCompiler sealed : Compiler {
		public:
			SimpleCompiler(Expression^ expression, CompilerMode compilerFlag);
		internal:
			void Compile(Database^ database, PlatformInfo^ platformInfo) override;

			property IDictionary<int, Expression^>^ ExpressionsById
			{
				IDictionary<int, Expression^>^ get() override;
			}
		private:
			Expression^ m_expression_;
			CompilerMode m_compiler_mode_;
		};
	}
}