#include "pch.h"

#include "hyperscan_match_observable.h"

using namespace Hyperscan::Scanning;

MatchObservable::MatchObservable() {
	this->m_Observers = gcnew System::Collections::Generic::List<System::IObserver<Match^>^>();
}

System::IDisposable^ MatchObservable::Subscribe(System::IObserver<Match^>^ observer) {
	if (!this->m_Observers->Contains(observer)) {
		this->m_Observers->Add(observer);
	}

	return gcnew Unsubscriber(this->m_Observers, observer);
}

void MatchObservable::OnMatch(Match^ match) {
	for each (System::IObserver<Match^>^ observer in this->m_Observers)
	{
		observer->OnNext(match);
	}
}

Unsubscriber::Unsubscriber(System::Collections::Generic::List<System::IObserver<Match^>^>^ observers, System::IObserver<Match^>^ observer) {
	this->m_Observers = observers;
	this->m_Observer = observer;
}

Unsubscriber::~Unsubscriber() {
	this->!Unsubscriber();
}

Unsubscriber::!Unsubscriber() {
	if (this->m_Observers->Contains(this->m_Observer)) {
		this->m_Observers->Remove(this->m_Observer);
	}
}