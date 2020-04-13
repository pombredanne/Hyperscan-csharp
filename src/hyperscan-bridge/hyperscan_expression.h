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

#include "hyperscan_expression_flag.h"
#include "hyperscan_expression_info.h"
#include "hyperscan_utils.h"
#include "hyperscan_exception.h"

using namespace System;
using namespace Hyperscan::Utils;
using namespace Hyperscan::Core::Exceptions;
using namespace Runtime::InteropServices;

namespace Hyperscan {
	namespace Compilation {
		/// <summary>
		/// Expression to be matched
		/// </summary>
		public ref class Expression sealed {
		public:
			/// <summary>
			/// Construct an expression
			/// </summary>
			/// <param name="pattern">The pattern to match with</param>
			/// <param name="expressionFlag">Expression flag</param>
			Expression(String^ pattern, ExpressionFlag expressionFlag);

			/// <summary>
			/// Fetching the expression info
			/// </summary>
			bool TryGetInfo([Out] ExpressionInfo^% info);

			/// <summary>
			/// Unique identifier of the expressions
			/// </summary>
			property int Id
			{
			public:
				int get();
			internal:
				void set(int);
			}

			/// <summary>
			/// The pattern to match with
			/// </summary>
			property String^ Pattern
			{
				String^ get();
			}

			/// <summary>
			/// The expression flag
			/// </summary>
			property ExpressionFlag Flag
			{
				ExpressionFlag get();
			}
		private:
			int m_id_;
			String^ m_pattern_;
			ExpressionFlag m_expression_flag_;
		};
	}
}