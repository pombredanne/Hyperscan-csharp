#pragma once

#include "hyperscan_match.h"

namespace Hyperscan {
	namespace Scanning {
		private ref class Unsubscriber {
		public:
			Unsubscriber(System::Collections::Generic::List<System::IObserver<Match^>^>^ observers, System::IObserver<Match^>^ observer);
			~Unsubscriber();
			!Unsubscriber();
		private:
			System::Collections::Generic::List<System::IObserver<Match^>^>^ m_Observers;
			System::IObserver<Match^>^ m_Observer;
		};

		public ref class MatchObservable : public System::IObservable<Match^> {
		public:
			MatchObservable();
			virtual System::IDisposable^ Subscribe(System::IObserver<Match^>^ observer);
			void OnMatch(Match^ match);
		private:
			System::Collections::Generic::List<System::IObserver<Match^>^>^ m_Observers;
		};
	}
}