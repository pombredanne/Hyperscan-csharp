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

#include "hyperscan_scanner.h"
#include "hyperscan_database.h"
#include "hyperscan_exception.h"
#include "hyperscan_match_event_handler.h"
#include "hyperscan_match_observable.h"
#include "hyperscan_expression.h"

#include <msclr/gcroot.h>

using namespace System;
using namespace msclr;

using namespace Hyperscan::Core;
using namespace Hyperscan::Databases;
using namespace Hyperscan::Compilation;
using namespace Exceptions;
using namespace Event;

namespace Hyperscan {
	namespace Scanning {
		namespace Scanners {
			private ref class BlockScanner sealed : Scanner {
			public:
				/// <summary>
				/// Scan against an input
				/// </summary>
				/// <param name="input">The input</param>
				/// <returns>True if succeeded, false if scan already completed</returns>
				bool Scan(String^ input) override;

				/// <summary>
				/// Get the scratch size in bytes
				/// </summary>
				property int ScratchSize
				{
					int get() override;
				}
			internal:
				/// <summary>
				/// Construct a scanner
				/// </summary>
				/// <param name="database">The database</param>
				/// <param name="expressionsById">The dictionary expressions</param>
				/// <param name="matchObservable">The match observable</param>
				BlockScanner(Database^ database, IDictionary<int, Expression^>^ expressionsById, MatchObservable^ matchObservable);

				/// <summary>
				/// Finalizer
				/// </summary>
				~BlockScanner();

				/// <summary>
				/// Destructor
				/// </summary>
				!BlockScanner();

				/// <summary>
				/// Create and allocate a memory scratch for the current scanner
				/// </summary>
				/// <param name="scratchPrototype">The prototype which will be cloned for allocating new scratch</param>
				void CreateScratch(hs_scratch_t* scratchPrototype);
			private:
				MatchEventHandler^ m_match_event_handler_;
				gcroot<IDictionary<int, Expression^>^>* m_expressions_by_id_handle_;
				hs_scratch_t* m_scratch_;
				hs_database_t* m_database_;
			};
		}
	}
}