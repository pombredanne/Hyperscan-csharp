#pragma once

#include "hyperscan_context.h"
#include "hyperscan_exception.h"
#include "hyperscan_match_event_handler.h"
#include "hyperscan_match_observable.h"

using namespace Hyperscan::Core;
using namespace Hyperscan::Core::Exceptions;
using namespace Hyperscan::Scanning::Event;

namespace Hyperscan {
	namespace Scanning {
		private interface class IScanner {
			void Scan(System::String^ input);
		};

		private ref class Scanner : public IScanner {
		public:
			Scanner(HyperscanContext^ context, MatchObservable^ matchObservable);
			virtual void Scan(System::String^ input);
		private:
			HyperscanContext^ m_Context;
			MatchEventHandler^ m_MatchEventHandler;
		};
	}
}
