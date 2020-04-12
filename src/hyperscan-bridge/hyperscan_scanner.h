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
		private ref class Scanner sealed {
		internal:
			Scanner(Database^ database, IDictionary<int, Expression^>^ expressionsById, MatchObservable^ matchObservable);
			~Scanner();
			!Scanner();
			void Scan(String^ input);
			void CreateScratch(hs_scratch_t* scratchPrototype);
			property int ScratchSize
			{
				int get();
			}
		private:
			MatchEventHandler^ m_match_event_handler_;
			gcroot<IDictionary<int, Expression^>^>* m_expressions_by_id_handle_;
			hs_scratch_t* m_scratch_;
			hs_database_t* m_database_;
		};
	}
}