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

#include <vcclr.h>

using namespace Hyperscan::Scanning;

Scanner::Scanner(Database^ database, IDictionary<int, Expression^>^ expressionsById, MatchObservable^ matchObservable) {
    this->m_scratch_ = nullptr;
    this->m_database_ = database->m_database;
    this->m_match_event_handler_ = gcnew MatchEventHandler(matchObservable);
    this->m_expressions_by_id_handle_ = new gcroot<IDictionary<int, Expression^>^>(expressionsById);
}

Scanner::~Scanner()
{
    this->!Scanner();
}

Scanner::!Scanner()
{
    delete this->m_expressions_by_id_handle_;
    hs_free_scratch(this->m_scratch_);
}

void Scanner::Scan(String^ input) {
    const auto match_attr = new MatchAttribute();
    match_attr->expressions_by_id_handle = this->m_expressions_by_id_handle_;
    match_attr->source = new gcroot<String^>(input);
    auto input_ptr = Marshal::StringToHGlobalAnsi(input);
    try {
        const auto data = static_cast<const char*>(input_ptr.ToPointer());
        const auto scan_err = hs_scan(this->m_database_, data, input->Length, 0, this->m_scratch_, this->m_match_event_handler_->m_handler, match_attr);
        if (scan_err != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to scan input buffer.", scan_err));
        }
    }
    finally
    {
        Marshal::FreeHGlobal(input_ptr);
    }
}

void Scanner::CreateScratch(hs_scratch_t* scratchPrototype)
{
    const pin_ptr<hs_scratch_t*> scratch = &this->m_scratch_;
    const auto alloc_scratch_err = hs_clone_scratch(scratchPrototype, scratch);
    if (alloc_scratch_err != HS_SUCCESS) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to allocate scratch space.", alloc_scratch_err));
    }
}

int Scanner::ScratchSize::get()
{
    const auto size = new size_t[1];
    try {
        const auto scratch_size_error = hs_scratch_size(this->m_scratch_, size);
        if (scratch_size_error != HS_SUCCESS) {
            throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to get scratch size.", scratch_size_error));
        }

        return static_cast<int>(*size);
    }
    finally
    {
        delete[] size;
    }
}