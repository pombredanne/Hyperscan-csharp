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

#include "hyperscan_logger.h"

using namespace Hyperscan::Logging;

Logger::Logger(Action<String^>^ onTrace, Action<String^>^ onDebug, Action<String^>^ onInfo, Action<String^>^ onWarning, Action<String^>^ onError, Action<String^>^ onCritical)
{
	this->m_on_trace_ = onTrace;
	this->m_on_debug_ = onDebug;
	this->m_on_info_ = onInfo;
	this->m_on_warning_ = onWarning;
	this->m_on_error_ = onError;
	this->m_on_critical_ = onCritical;
}


void Logger::Trace(String^ message)
{
	this->m_on_trace_(message);
}

void Logger::Debug(String^ message)
{
	this->m_on_debug_(message);
}

void Logger::Info(String^ message)
{
	this->m_on_info_(message);
}


void Logger::Warning(String^ message)
{
	this->m_on_warning_(message);
}

void Logger::Error(String^ message)
{
	this->m_on_error_(message);
}

void Logger::Critical(String^ message)
{
	this->m_on_critical_(message);
}

