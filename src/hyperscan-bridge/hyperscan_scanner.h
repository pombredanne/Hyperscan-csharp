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
	namespace Scanning {
		public ref class Scanner abstract {
		public:
			/// <summary>
			/// Finalizer
			/// </summary>
			~Scanner();

			/// <summary>
			/// Destructor
			/// </summary>
			!Scanner();
			/// <summary>
			/// Scan against an input
			/// </summary>
			/// <param name="input">The input</param>
			/// <returns>True if succeeded, false if scan already completed</returns>
			virtual bool Scan(String^ input);

			/// <summary>
			/// Get the scratch size in bytes
			/// </summary>
			virtual property int ScratchSize
			{
				int get();
			}
		};
	}
}