#pragma once

#include "hyperscan_match_observable.h"
#include "hyperscan_utils.h"

using namespace System::Runtime::InteropServices;

namespace Hyperscan {
	namespace Scanning {
		namespace Event {
			public ref class MatchEventHandler {
			public:
				MatchEventHandler(MatchObservable^ matchObservable);
				~MatchEventHandler();
				!MatchEventHandler();
			internal:
				match_event_handler m_Handler;
				int OnMatch(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context);
			private:
				delegate int OnMatchManagedCallback(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context);
				OnMatchManagedCallback^ m_Callback;
				GCHandle m_Callback_Handle;
				System::IntPtr m_Callback_Ptr;
				MatchObservable^ m_MatchObservable;
			};
		}
	}
}