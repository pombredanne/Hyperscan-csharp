// MIT License
// Copyright(c) 2020 Benjamin BOUGOT
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

#include "hyperscan_context.h"
#include "hyperscan_compiler.h"
#include "hyperscan_scanner.h"
#include "hyperscan_match_observable.h"

using namespace System;

using namespace Hyperscan;
using namespace Compilation;
using namespace Scanning;

namespace Hyperscan {
	namespace Core {
		/// <summary>
		/// Hyperscan core component which defines the compilers and expose scanning abilities
		/// </summary>
		public ref class HyperscanEngine {
		public:
			/// <summary>
			/// Instanciate the Hyperscan engine
			/// </summary>
			/// <param name="compilerFactory">The factory used to configure the Hyperscan compiler</param>
			HyperscanEngine(Func<HyperscanContext^, ICompiler^>^ compilerFactory);

			~HyperscanEngine();

			!HyperscanEngine();

			/// <summary>
			/// Trigger a scan on the configured compiler with the given input
			/// </summary>
			void Scan(String^ input);

			/// <summary>
			/// Get the configured compiler
			/// </summary>
			property ICompiler^ Compiler {
				ICompiler^ get();
			}

			/// <summary>
			/// Get the configured scanner
			/// </summary>
			property IScanner^ Scanner {
				IScanner^ get();
			}

			/// <summary>
			/// Subscribe to observe matches
			/// </summary
			property IObservable<Match^>^ OnMatch {
				IObservable<Match^>^ get();
			}
		private:
			HyperscanContext^ m_context_;
			ICompiler^ m_compiler_;
			IScanner^ m_scanner_;
			IScan^ m_scan_;
			MatchObservable^ m_match_observable_;
			IObservable<Match^>^ m_on_match_;
		};
	}
}