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
#include "hyperscan_logger.h"
#include "hyperscan_block_scanner.h"
#include "hyperscan_stream_scanner.h"

using namespace System;

using namespace Hyperscan;
using namespace Core;
using namespace Databases;
using namespace Compilation;
using namespace Scanning;
using namespace Platform;
using namespace Logging;
using namespace Scanners;

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
			/// Get the compiler
			/// </summary>
			property Compiler^ Compiler {
				Compilation::Compiler^ get();
			}

			/// <summary>
			/// Get the platform info
			/// </summary>
			property PlatformInfo^ PlatformInfo {
				Platform::PlatformInfo^ get();
			}

			/// <summary>
			/// Get the version information for the underlying hyperscan library
			/// </summary>
			property String^ Version {
				String^ get();
			}

			/// <summary>
			/// Subscribe to observe matches
			/// </summary>
			property IObservable<Match^>^ OnMatch {
				IObservable<Match^>^ get();
			}
		internal:
			/// <summary>
			/// Instanciate the Hyperscan engine
			/// </summary>
			/// <param name="logger">The logger</param>
			/// <param name="databaseFactory">The factory used to configure the Hyperscan database</param>
			/// <param name="compilerFactory">The factory used to configure the Hyperscan compiler</param>
			HyperscanEngine(Logger^ logger, Func<Databases::Database^>^ databaseFactory, Func<Compilation::Compiler^>^ compilerFactory);

			/// <summary>
			/// Finalizer
			/// </summary>
			~HyperscanEngine();

			/// <summary>
			/// Destructor
			/// </summary>
			!HyperscanEngine();

			/// <summary>
			/// Create a scanner
			/// </summary>
			Scanner^ CreateScanner();
		private:
			Compilation::Compiler^ m_compiler_;
			Databases::Database^ m_database_;
			Platform::PlatformInfo^ m_platform_info_;
			Logger^ m_logger_;
			MatchObservable^ m_match_observable_;
			hs_stream_t* m_stream_prototype_;
		};
	}
}