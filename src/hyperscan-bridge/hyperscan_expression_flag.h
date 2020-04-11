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

namespace Hyperscan {
    namespace Compilation {
        /// <summary>
        /// Flags which modify the behaviour of the expression. Multiple flags may be used by ORing them together
        /// </summary>
        [System::Flags]
        public enum class ExpressionFlag {
            /// <summary>
            /// Matching will be performed case-insensitively
            /// </summary>
            HsFlagCaseless = 1,
            /// <summary>
            /// Matching a . will not exclude newlines
            /// </summary>
            HsFlagDotall = 2,
            /// <summary>
            ///  ^ and $ anchors match any newlines in data
            /// </summary>
            HsFlagMultiline = 4,
            /// <summary>
            /// Only one match will be generated for the expression per stream
            /// </summary>
            HsFlagSinglematch = 8,
            /// <summary>
            ///  Allow expressions which can match against an empty string, such as .*
            /// </summary>
            HsFlagAllowempty = 16,
            /// <summary>
            /// Treat this pattern as a sequence of UTF-8 characters
            /// </summary>
            HsFlagUtf8 = 32,
            /// <summary>
            /// Use Unicode properties for character classes
            /// </summary>
            HsFlagUcp = 64,
            /// <summary>
            /// Compile pattern in prefiltering mode
            /// </summary>
            HsFlagPrefilter = 128,
            /// <summary>
            /// Report the leftmost start of match offset when a match is found
            /// </summary>
            HsFlagSomLeftmost = 256,
            /// <summary>
            /// Parse the expression in logical combination syntax
            /// </summary>
            HsFlagCombination = 512,
            /// <summary>
            /// Ignore match reporting for this expression. Used for the sub-expressions in logical combinations
            /// </summary>
            HsFlagQuiet = 1024
        };
    }
}