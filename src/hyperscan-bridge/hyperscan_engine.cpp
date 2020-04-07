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
#include "hyperscan_match.h"

HyperscanEngine::HyperscanEngine(Func<HyperscanContext^, ICompiler^>^ compilerFactory) {
	this->m_context_ = gcnew HyperscanContext();
	const auto match_observable = gcnew MatchObservable();
	this->m_on_match_ = match_observable;
	this->m_match_observable_ = match_observable;
	const auto scanner = gcnew Scanning::Scanner(this->m_context_, this->m_match_observable_);
	this->m_scan_ = scanner;
	this->m_scanner_ = scanner;
	this->m_compiler_ = compilerFactory(this->m_context_);
}

HyperscanEngine::~HyperscanEngine() {
	this->!HyperscanEngine();
}

HyperscanEngine::!HyperscanEngine() {

}

void HyperscanEngine::Scan(String^ input) {
	this->m_scan_->Scan(input);
}

ICompiler^ HyperscanEngine::Compiler::get() {
	return this->m_compiler_;
}

IScanner^ HyperscanEngine::Scanner::get(){
	return this->m_scanner_;
}

IObservable<Match^>^ HyperscanEngine::OnMatch::get() {
	return this->m_on_match_;
}