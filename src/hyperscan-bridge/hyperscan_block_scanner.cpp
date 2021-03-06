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

#include "hyperscan_block_scanner.h"

using namespace Hyperscan::Scanning;
using namespace Scanners;

BlockScanner::BlockScanner(Database^ database, IDictionary<int, Expression^>^ expressionsById, MatchObservable^ matchObservable) {
    this->m_scratch_ = nullptr;
    this->m_database_ = database->m_database;
    this->m_match_event_handler_ = gcnew MatchEventHandler(matchObservable);
    this->m_expressions_by_id_handle_ = new gcroot<IDictionary<int, Expression^>^>(expressionsById);
}

BlockScanner::~BlockScanner()
{
    this->!BlockScanner();
}

BlockScanner::!BlockScanner()
{
    delete this->m_expressions_by_id_handle_;
    hs_free_scratch(this->m_scratch_);
}

bool BlockScanner::Scan(String^ input) {
    const auto match_attr = new MatchAttribute();
    match_attr->expressions_by_id_handle = this->m_expressions_by_id_handle_;
    const auto managed_array = StringUtils::string_to_managed_array(input, input->Length);
    const auto input_memory = gcnew ReadOnlyMemory<Byte>(managed_array);
    const auto input_sequence = gcnew ReadOnlySequence<Byte>(*input_memory);
    match_attr->input_handle = new gcroot<ReadOnlySequence<Byte>^>(*input_sequence);
    const pin_ptr<unsigned char> data = &managed_array[0];
    const auto scan_err = hs_scan(this->m_database_, reinterpret_cast<const char*>(data), input->Length, 0, this->m_scratch_, this->m_match_event_handler_->m_handler, match_attr);
    if (scan_err != HS_SUCCESS && scan_err != HS_SCAN_TERMINATED) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to scan input buffer.", scan_err));
    }

    return scan_err == HS_SUCCESS;
}

void BlockScanner::CreateScratch(hs_scratch_t* scratchPrototype)
{
    const pin_ptr<hs_scratch_t*> scratch = &this->m_scratch_;
    const auto alloc_scratch_err = hs_clone_scratch(scratchPrototype, scratch);
    if (alloc_scratch_err != HS_SUCCESS) {
        throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to allocate scratch space.", alloc_scratch_err));
    }
}

int BlockScanner::ScratchSize::get()
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