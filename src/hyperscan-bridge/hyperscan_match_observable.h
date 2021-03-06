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

#include "hyperscan_match.h"

using namespace System;
using namespace Collections::Concurrent;

namespace Hyperscan {
	namespace Scanning {
		private ref class Unsubscriber {
		public:
			/// <summary>
			/// Construct an unsubscriber
			/// </summary>
			/// <param name="observers">The observers collection</param>
			/// <param name="observer">The new observer to add</param>
			Unsubscriber(ConcurrentDictionary<IObserver<Match^>^, bool>^ observers, IObserver<Match^>^ observer);

			/// <summary>
			/// Finalizer
			/// </summary>
			~Unsubscriber();

			/// <summary>
			/// Destructor
			/// </summary>
			!Unsubscriber();
		private:
			ConcurrentDictionary<IObserver<Match^>^, bool>^ m_observers_;
			IObserver<Match^>^ m_observer_;
		};

		public ref class MatchObservable : public IObservable<Match^> {
		public:
			/// <summary>
			/// Create a match observable
			/// </summary>
			MatchObservable();

			/// <summary>
			/// Subscribe to the observable
			/// </summary>
			/// <param name="observer">The observer</param>
			virtual IDisposable^ Subscribe(IObserver<Match^>^ observer);

			/// <summary>
			/// Get called on matched
			/// </summary>
			/// <param name="match">The match</param>
			void OnMatch(Match^ match);
		private:
			ConcurrentDictionary<IObserver<Match^>^, bool>^ m_observers_;
		};
	}
}