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

#include "hyperscan_compiler.h"
#include "hyperscan_scanner.h"
#include "hyperscan_database.h"
#include "hyperscan_match_observable.h"
#include "hyperscan_match.h"
#include "hyperscan_platform_info.h"

using namespace System;

using namespace Hyperscan;
using namespace Databases;
using namespace Compilation;
using namespace Scanning;
using namespace Platform;

namespace Hyperscan {
	namespace Core {
		/// <summary>
		/// Hyperscan core component which defines the compilers and expose scanning abilities
		/// </summary>
		public ref class HyperscanEngine {
		public:
			/// <summary>
			/// Get the database
			/// </summary>
			property Database^ Database {
				Databases::Database^ get();
			}

			/// <summary>
			/// Subscribe to observe matches
			/// </summary>
			property IObservable<Match^>^ OnMatch {
				IObservable<Match^>^ get();
			}

			/// <summary>
			/// Check if the hardware platform is supported
			/// </summary>
			property bool IsPlatformValid {
				bool get();
			}

			/// <summary>
			/// Get the version information for the underlying hyperscan library
			/// </summary>
			property String^ Version {
				String^ get();
			}
		internal:
			/// <summary>
			/// Instanciate the Hyperscan engine
			/// </summary>
			/// <param name="databaseFactory">The factory used to configure the Hyperscan database</param>
			/// <param name="compilerFactory">The factory used to configure the Hyperscan compiler</param>
			HyperscanEngine(Func<Databases::Database^>^ databaseFactory, Func<Compiler^>^ compilerFactory);
			~HyperscanEngine();
			!HyperscanEngine();
			Scanner^ CreateScanner();
		private:
			Compiler^ m_compiler_;
			Databases::Database^ m_database_;
			MatchObservable^ m_match_observable_;
			PlatformInfo^ m_platform_info_;
		};
	}
}