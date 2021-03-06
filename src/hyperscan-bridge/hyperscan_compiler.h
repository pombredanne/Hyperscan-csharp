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

#include "hyperscan_database.h"
#include "hyperscan_platform_info.h"
#include "hyperscan_expression.h"
#include "hyperscan_compiler_mode.h"

using namespace System;
using namespace Collections::Generic;

using namespace Hyperscan::Databases;
using namespace Hyperscan::Platform;
using namespace Hyperscan::Compilation;

namespace Hyperscan {
	namespace Compilation {
		/// <summary>
		/// Compiler
		/// </summary>
		public ref class Compiler abstract {
		public:
			/// <summary>
			/// The compiler mode
			/// </summary>
			virtual property CompilerMode Mode
			{
				CompilerMode get();
			}
		internal:
			virtual void Compile(Database^ database, PlatformInfo^ platformInfo);
			virtual property IDictionary<int, Expression^>^ ExpressionsById {
				IDictionary<int, Expression^>^ get();
			}
		};
	}
}