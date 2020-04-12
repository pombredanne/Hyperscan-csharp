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

using namespace System;

namespace Hyperscan {
	namespace Compilation {
		/// <summary>
		/// A type containing information related to an expression
		/// </summary>
		public ref class ExpressionInfo sealed {
		public:
			ExpressionInfo(unsigned int minWidth, unsigned int maxWidth, bool unorderedMatches, bool matchesAtEod, bool matchesOnlyAtEod, String^ compilationErrorMessage);

			/// <summary>
			/// The minimum length in bytes of a match for the pattern.
			/// </summary>
			property unsigned int MinWidth
			{
				unsigned int get();
			}

			/// <summary>
			/// The maximum length in bytes of a match for the pattern. If the pattern has an unbounded maximum length, this will be set to the maximum value of an unsigned int (UINT_MAX).
			/// </summary>
			property unsigned int MaxWidth
			{
				unsigned int get();
			}

			/// <summary>
			/// Whether this expression can produce matches that are not returned in order, such as those produced by assertions.
			/// </summary>
			property bool UnorderedMatches
			{
				bool get();
			}

			/// <summary>
			/// Whether this expression can produce matches at end of data (EOD)
			/// </summary>
			property bool MatchesAtEod
			{
				bool get();
			}

			/// <summary>
			/// Whether this expression can *only* produce matches at end of data (EOD).
			/// </summary>
			property bool MatchesOnlyAtEod
			{
				bool get();
			}

			/// <summary>
			/// Error message if this expression can't be compiled
			/// </summary>
			property String^ CompilationErrorMessage
			{
				String^ get();
			}

		private:
			unsigned int m_min_width_;
			unsigned int m_max_width_;
			bool m_unordered_matches_;
			bool m_matches_at_eod_width_;
			bool m_matches_only_at_eod_;
			String^ m_compilation_error_message_;
		};
	}
}