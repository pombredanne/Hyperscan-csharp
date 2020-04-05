#include "pch.h"

#include "hyperscan_scanner.h"

using namespace Hyperscan::Scanning;

Scanner::Scanner(HyperscanContext^ context, MatchObservable^ matchObservable) {
    this->m_Context = context;
    this->m_MatchEventHandler = gcnew MatchEventHandler(matchObservable);
}

void Scanner::Scan(System::String^ input) {
    System::IntPtr native_input_ = Marshal::StringToHGlobalAnsi(input);
    char* input_ = static_cast<char*>(native_input_.ToPointer());

    System::IntPtr native_pattern_ = Marshal::StringToHGlobalAnsi(this->m_Context->m_Pattern);
    char* pattern_ = static_cast<char*>(native_pattern_.ToPointer());
    try {
        pin_ptr<hs_database_t*> database;
        database = &this->m_Context->m_Database;

        pin_ptr<hs_scratch_t*> scratch;
        scratch = &this->m_Context->m_Scratch;
        hs_error_t scan_err_ = hs_scan(*database, input_, input->Length, 0, *scratch, this->m_MatchEventHandler->m_Handler, pattern_);
        if (scan_err_ != HS_SUCCESS) {
            throw gcnew HyperscanException(System::String::Format("ERROR {0}: Unable to scan input buffer. Exiting.", scan_err_));
        }
    }
    finally {
        Marshal::FreeHGlobal(native_input_);
        Marshal::FreeHGlobal(native_pattern_);
    }
}