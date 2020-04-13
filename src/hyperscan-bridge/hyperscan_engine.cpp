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

#include "hyperscan_engine.h"

HyperscanEngine::HyperscanEngine(Logger^ logger, Func<Databases::Database^>^ databaseFactory, Func<Compilation::Compiler^>^ compilerFactory) {
	this->m_logger_ = logger;
	this->m_database_ = databaseFactory();

	const auto compiler = compilerFactory();
	this->m_platform_info_ = gcnew Platform::PlatformInfo();
	const auto stopwatch = gcnew Diagnostics::Stopwatch();
	stopwatch->Start();
	compiler->Compile(this->m_database_, this->m_platform_info_);
	stopwatch->Stop();
	this->m_logger_->Trace(compiler->ExpressionsById->Count + " expression(s) compiled in " + stopwatch->ElapsedMilliseconds.ToString() + "ms.");
	this->m_compiler_ = compiler;

	const auto match_observable = gcnew MatchObservable();
	this->m_match_observable_ = match_observable;

	if ((this->m_compiler_->Mode & CompilerMode::HsModeStream) == CompilerMode::HsModeStream) {
		hs_stream_t* stream_prototype = nullptr;
		const auto open_stream_err = hs_open_stream(this->m_database_->m_database, 0, &stream_prototype);
		if (open_stream_err != HS_SUCCESS)
		{
			throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to open stream.", open_stream_err));
		}

		this->m_stream_prototype_ = stream_prototype;
	}
}

HyperscanEngine::~HyperscanEngine() {
	this->!HyperscanEngine();
}

HyperscanEngine::!HyperscanEngine() {
	if ((this->m_compiler_->Mode & CompilerMode::HsModeStream) == CompilerMode::HsModeStream) {
		const auto close_stream_err = hs_close_stream(this->m_stream_prototype_, nullptr, nullptr, nullptr);
		if (close_stream_err != HS_SUCCESS)
		{
			throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to close stream.", close_stream_err));
		}
	}
}

Database^ HyperscanEngine::Database::get() {
	return this->m_database_;
}

Compiler^ HyperscanEngine::Compiler::get() {
	return this->m_compiler_;
}

PlatformInfo^ HyperscanEngine::PlatformInfo::get()
{
	return this->m_platform_info_;
}

String^ HyperscanEngine::Version::get()
{
	return gcnew String(hs_version());
}

IObservable<Match^>^ HyperscanEngine::OnMatch::get() {
	return this->m_match_observable_;
}

Scanner^ HyperscanEngine::CreateScanner()
{
	hs_scratch_t* scratch_prototype = nullptr;
	try {
		const auto scratch_error = hs_alloc_scratch(this->m_database_->m_database, &scratch_prototype);
		if (scratch_error != HS_SUCCESS) {
			throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to allocate scratch prototype.", scratch_error));
		}

		if ((this->m_compiler_->Mode & CompilerMode::HsModeBlock) == CompilerMode::HsModeBlock) {
			const auto scanner = gcnew BlockScanner(this->m_database_, this->m_compiler_->ExpressionsById, this->m_match_observable_);
			scanner->CreateScratch(scratch_prototype);
			return scanner;
		}

		if ((this->m_compiler_->Mode & CompilerMode::HsModeStream) == CompilerMode::HsModeStream) {
			hs_stream_t* stream;
			const auto copy_stream_err = hs_copy_stream(&stream, this->m_stream_prototype_);
			if (copy_stream_err != HS_SUCCESS)
			{
				throw gcnew HyperscanException(String::Format("ERROR {0}: Unable to copy stream.", copy_stream_err));
			}

			const auto scanner = gcnew StreamScanner(this->m_database_, this->m_compiler_->ExpressionsById, this->m_match_observable_, stream);
			scanner->CreateScratch(scratch_prototype);
			return scanner;
		}

		throw gcnew NotImplementedException("Mode: " + this->m_compiler_->Mode.ToString() + " is not implemented.");
	}
	finally
	{
		hs_free_scratch(scratch_prototype);
	}
}