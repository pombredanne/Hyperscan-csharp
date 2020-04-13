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

#include "hyperscan_match_observable.h"
#include "hyperscan_utils.h"
#include "hyperscan_expression.h"

#include <msclr/gcroot.h>

using namespace System;
using namespace System::Text;
using namespace msclr;
using namespace Buffers;
using namespace Runtime::InteropServices;

using namespace Hyperscan::Compilation;
using namespace Hyperscan::Scanning;
using namespace Hyperscan::Utils;

namespace Hyperscan {
	namespace Scanning {
		namespace Event {
			public ref class MatchEventHandler {
			public:
				/// <summary>
				/// Create a match event handler
				/// </summary>
				/// <param name="matchObservable">The match observable</param>
				MatchEventHandler(MatchObservable^ matchObservable);

				/// <summary>
				/// Finalizer
				/// </summary>
				~MatchEventHandler();

				/// <summary>
				/// Destructor
				/// </summary>
				!MatchEventHandler();
			internal:
				match_event_handler m_handler;
			private:
				int on_match(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context);
				delegate int OnMatchManagedCallback(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context);
				OnMatchManagedCallback^ m_callback_;
				GCHandle m_callback_handle_;
				IntPtr m_callback_ptr_;
				MatchObservable^ m_match_observable_;
				Encoding^ m_utf8_encoding_;
			};
		}
	}
}