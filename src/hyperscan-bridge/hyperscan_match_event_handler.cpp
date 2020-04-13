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

#include "hyperscan_match_event_handler.h"

using namespace Event;

MatchEventHandler::MatchEventHandler(MatchObservable^ matchObservable) {
	this->m_match_observable_ = matchObservable;
	this->m_callback_ = gcnew OnMatchManagedCallback(this, &MatchEventHandler::on_match);
	this->m_callback_handle_ = GCHandle::Alloc(this->m_callback_);
	this->m_callback_ptr_ = Marshal::GetFunctionPointerForDelegate(this->m_callback_);
	this->m_handler = static_cast<match_event_handler>(this->m_callback_ptr_.ToPointer());
	this->m_utf8_encoding_ = Encoding::UTF8;
}

MatchEventHandler::~MatchEventHandler() {
	this->!MatchEventHandler();
}

MatchEventHandler::!MatchEventHandler() {
	this->m_callback_handle_.Free();
}

int MatchEventHandler::on_match(const unsigned int id, const unsigned long long from, const unsigned long long to, unsigned int flags, void* context) {
	const auto match_attr = static_cast<MatchAttribute*>(context);
	const auto source_handle = match_attr->input_handle;
	const auto expressions_by_id_handle = match_attr->expressions_by_id_handle;
	Expression^ expression;
	const auto source = *source_handle;
	auto match_sequence = source->Slice(static_cast<int>(from), static_cast<int>(to - from));
	const auto match = this->m_utf8_encoding_->GetString(match_sequence.FirstSpan);
	this->m_match_observable_->OnMatch(gcnew Match(id, match, (*expressions_by_id_handle)->TryGetValue(id, expression) ? expression : nullptr, source));
	return 0;
}