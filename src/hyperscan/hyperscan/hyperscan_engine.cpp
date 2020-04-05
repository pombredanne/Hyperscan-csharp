#include "pch.h"

#include "hyperscan_engine.h"
#include "hyperscan_match.h"

HyperscanEngine::HyperscanEngine(System::Func<HyperscanContext^, System::IObservable<Hyperscan::Scanning::Match^>^, ICompiler^>^ compilerFactory) {
	this->m_Context = gcnew HyperscanContext();
	this->m_MatchObservable = gcnew MatchObservable();
	this->Compiler = compilerFactory(this->m_Context, this->m_MatchObservable);
	this->Scanner = gcnew Hyperscan::Scanning::Scanner(this->m_Context, this->m_MatchObservable);
}

HyperscanEngine::~HyperscanEngine() {
	this->!HyperscanEngine();
}

HyperscanEngine::!HyperscanEngine() {

}

void HyperscanEngine::Scan(System::String^ input) {
	this->Scanner->Scan(input);
}

ICompiler^ HyperscanEngine::Compiler::get() {
	return this->m_Compiler;
}

void HyperscanEngine::Compiler::set(ICompiler^ compiler) {
	this->m_Compiler = compiler;
}

IScanner^ HyperscanEngine::Scanner::get(){
	return this->m_Scanner;
}

void HyperscanEngine::Scanner::set(IScanner^ scanner) {
	this->m_Scanner = scanner;
}