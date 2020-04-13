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

#include "pch.h"

#include "hyperscan_match_observable.h"

using namespace Hyperscan::Scanning;

MatchObservable::MatchObservable() {
	this->m_observers_ = gcnew ConcurrentDictionary<IObserver<Match^>^, bool>();
}

IDisposable^ MatchObservable::Subscribe(IObserver<Match^>^ observer) {
	if (!this->m_observers_->ContainsKey(observer)) {
		this->m_observers_->TryAdd(observer, true);
	}

	return gcnew Unsubscriber(this->m_observers_, observer);
}

void MatchObservable::OnMatch(Match^ match) {
	for each (KeyValuePair<IObserver<Match^>^, bool>^ observer in this->m_observers_)
	{
		observer->Key->OnNext(match);
	}
}

Unsubscriber::Unsubscriber(ConcurrentDictionary<IObserver<Match^>^, bool>^ observers, IObserver<Match^>^ observer) {
	this->m_observers_ = observers;
	this->m_observer_ = observer;
}

Unsubscriber::~Unsubscriber() {
	this->!Unsubscriber();
}

Unsubscriber::!Unsubscriber() {
	if (this->m_observers_->ContainsKey(this->m_observer_)) {
		bool removed;
		this->m_observers_->TryRemove(this->m_observer_, removed);
	}
}