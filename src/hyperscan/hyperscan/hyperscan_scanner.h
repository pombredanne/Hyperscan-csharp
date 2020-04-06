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
#include "hyperscan_exception.h"
#include "hyperscan_match_event_handler.h"
#include "hyperscan_match_observable.h"

using namespace System;

using namespace Hyperscan::Core;
using namespace Exceptions;
using namespace Event;

namespace Hyperscan {
	namespace Scanning {
		public interface class IScanner {
		};

		private interface class IScan {
			void Scan(String^ input);
		};

		private ref class Scanner : public IScanner, IScan {
		public:
			virtual void Scan(String^ input);
		internal:
			Scanner(HyperscanContext^ context, MatchObservable^ matchObservable);
		private:
			HyperscanContext^ m_context_;
			MatchEventHandler^ m_match_event_handler_;
		};
	}
}