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

HyperscanEngine::HyperscanEngine(Func<Databases::Database^>^ databaseFactory, Func<Compiler^>^ compilerFactory) {
	this->m_database_ = databaseFactory();

	const auto compiler = compilerFactory();
	this->m_platform_info_ = gcnew PlatformInfo();
	compiler->Compile(this->m_database_, this->m_platform_info_);
	this->m_compiler_ = compiler;

	const auto match_observable = gcnew MatchObservable();
	this->m_match_observable_ = match_observable;
}

HyperscanEngine::~HyperscanEngine() {
	this->!HyperscanEngine();
}

HyperscanEngine::!HyperscanEngine() {

}

Database^ HyperscanEngine::Database::get() {
	return this->m_database_;
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
			throw gcnew HyperscanException(String::Format("Unable to allocate scratch prototype: {0}", scratch_error));
		}

		const auto scanner = gcnew Scanner(this->m_database_, this->m_compiler_->Pattern, this->m_match_observable_);
		scanner->CreateScratch(scratch_prototype);
		return scanner;
	}
	finally
	{
		hs_free_scratch(scratch_prototype);
	}
}
