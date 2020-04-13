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

using namespace System;

namespace Hyperscan {
	namespace Logging {
		public ref class Logger sealed {
		public:
			/// <summary>
			/// Create a logger
			/// </summary>
			/// <param name="onTrace">Trace action</param>
			/// <param name="onDebug">Debug action</param>
			/// <param name="onInfo">Info action</param>
			/// <param name="onWarning">Warning action</param>
			/// <param name="onError">Error action</param>
			/// <param name="onCritical">Critical action</param>
			Logger(Action<String^>^ onTrace, Action<String^>^ onDebug, Action<String^>^ onInfo, Action<String^>^ onWarning, Action<String^>^ onError, Action<String^>^ onCritical);

			/// <summary>
			/// Log a trace level
			/// </summary>
			/// <param name="message">The message</param>
			void Trace(String^ message);

			/// <summary>
			/// Log a debug level
			/// </summary>
			/// <param name="message">The message</param>
			void Debug(String^ message);

			/// <summary>
			/// Log an info level
			/// </summary>
			/// <param name="message">The message</param>
			void Info(String^ message);

			/// <summary>
			/// Log a warning level
			/// </summary>
			/// <param name="message">The message</param>
			void Warning(String^ message);

			/// <summary>
			/// Log an error level
			/// </summary>
			/// <param name="message">The message</param>
			void Error(String^ message);

			/// <summary>
			/// Log a critical level
			/// </summary>
			/// <param name="message">The message</param>
			void Critical(String^ message);
		private:
			Action<String^>^ m_on_trace_;
			Action<String^>^ m_on_debug_;
			Action<String^>^ m_on_info_;
			Action<String^>^ m_on_warning_;
			Action<String^>^ m_on_error_;
			Action<String^>^ m_on_critical_;
		};
	}
}