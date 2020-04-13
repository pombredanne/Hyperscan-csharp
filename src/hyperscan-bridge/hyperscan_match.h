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

#include <msclr/gcroot.h>

#include "hyperscan_expression.h"

using namespace msclr;
using namespace System;
using namespace Collections::Generic;
using namespace Buffers;

using namespace Hyperscan::Compilation;

namespace Hyperscan {
	namespace Scanning {
		private struct MatchAttribute {
			gcroot<IDictionary<int, Expression^>^>* expressions_by_id_handle;
			gcroot<ReadOnlySequence<Byte>^>* input_handle;
		};

		/// <summary>
		/// Represents a match from a successful scan
		/// </summary>
		public ref class Match {
		public:
			/// <summary>
			/// Represents the expression Id of the match
			/// </summary>
			property int Id {
				int get();
			}

			/// <summary>
			/// Represents the match of the successful expression
			/// </summary>
			property String^ FullMatch {
				String^ get();
			}

			/// <summary>
			/// Represents the expression associated to the successful match
			/// </summary>
			property Expression^ Expression {
				Compilation::Expression^ get();
			}

			/// <summary>
			/// The input to which the expression has matched against
			/// </summary>
			property ReadOnlySequence<Byte> Input {
				ReadOnlySequence<Byte> get();
			}
		internal:
			/// <summary>
			/// Construct a match
			/// </summary>
			/// <param name="id">The expression Id</param>
			/// <param name="fullMatch">The match</param>
			/// <param name="expression">The expression</param>
			/// <param name="input">The input</param>
			Match(int id, String^ fullMatch, Compilation::Expression^ expression, ReadOnlySequence<Byte>^ input);
		private:
			int m_id_;
			String^ m_full_match_;
			Compilation::Expression^ m_expression_;
			ReadOnlySequence<Byte>^ m_input_;
		};
	}
}
