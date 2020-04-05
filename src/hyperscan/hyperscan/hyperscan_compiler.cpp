#include "pch.h"

#include "hyperscan_compiler.h"

using namespace Hyperscan::Compilation;

Compiler::Compiler(HyperscanContext^ context, System::String^ pattern) {
    this->m_Context = context;
    this->m_Context->m_Pattern = pattern;
    System::IntPtr native_pattern_ = Marshal::StringToHGlobalAnsi(pattern);
    char* pattern_ = static_cast<char*>(native_pattern_.ToPointer());

    try {
        hs_compile_error_t* compile_err_;
        pin_ptr<hs_database_t*> database;
        database = &this->m_Context->m_Database;
        if (hs_compile(pattern_, HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL, database, &compile_err_) != HS_SUCCESS) {
            hs_free_compile_error(compile_err_);
            throw gcnew HyperscanException(System::String::Format("Unable to compile pattern ""{0}"": {1}", pattern, gcnew System::String(compile_err_->message)));
        }

        pin_ptr<hs_scratch_t*> scratch;
        scratch = &this->m_Context->m_Scratch;
        hs_error_t alloc_scratch_err_ = hs_alloc_scratch(*database, scratch);
        if (alloc_scratch_err_ != HS_SUCCESS) {
            throw gcnew HyperscanException(System::String::Format("ERROR {0}: Unable to allocate scratch space. Exiting.", alloc_scratch_err_));
        }
    }
    finally {
        Marshal::FreeHGlobal(native_pattern_);
    }
}