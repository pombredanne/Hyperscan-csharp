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

#include "hyperscan_scanner.h"

using namespace Hyperscan::Scanning;

Scanner::Scanner(Database^ database, String^ pattern, MatchObservable^ match_observable) {
    this->m_scratch_ = nullptr;
    this->m_database_ = database->m_database;
    this->m_match_event_handler_ = gcnew MatchEventHandler(match_observable);
    this->m_pattern_ = pattern;
}

Scanner::~Scanner()
{
    this->!Scanner();
}

Scanner::!Scanner()
{
    hs_free_scratch(this->m_scratch_);
}

void Scanner::Scan(String^ input) {
    const auto input_ptr = StringUtils::to_unmanaged(input);
    const auto match_attr = new MatchAttribute();
    match_attr->pattern = StringUtils::to_unmanaged(this->m_pattern_);
    match_attr->source = input_ptr;
    match_attr->source_len = input->Length;
    const auto scan_err = hs_scan(this->m_database_, input_ptr, input->Length, 0, this->m_scratch_, this->m_match_event_handler_->m_handler, match_attr);
    if (scan_err != HS_SUCCESS) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to scan input buffer. Exiting.", scan_err));
    }
}

void Scanner::CreateScratch(hs_scratch_t* scratch_prototype)
{
    const pin_ptr<hs_scratch_t*> scratch = &this->m_scratch_;
    const auto alloc_scratch_err = hs_clone_scratch(scratch_prototype, scratch);
    if (alloc_scratch_err != HS_SUCCESS) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to allocate scratch space. Exiting.", alloc_scratch_err));
    }
}