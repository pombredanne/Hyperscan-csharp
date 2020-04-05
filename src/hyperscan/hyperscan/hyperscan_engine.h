#pragma once

#include "hyperscan_context.h"
#include "hyperscan_compiler.h"
#include "hyperscan_scanner.h"
#include "hyperscan_match_observable.h"

using namespace Hyperscan;
using namespace Hyperscan::Compilation;
using namespace Hyperscan::Scanning;

namespace Hyperscan {
	namespace Core {
		public ref class HyperscanEngine {
		public:
			HyperscanEngine(System::Func<HyperscanContext^, System::IObservable<Match^>^, ICompiler^>^ compilerFactory);
			~HyperscanEngine();
			!HyperscanEngine();
			void Scan(System::String^ input);
		internal:
			property ICompiler^ Compiler {
				ICompiler^ get();
			private:
				void set(ICompiler^);
				}
			property IScanner^ Scanner {
				IScanner^ get();
			private:
				void set(IScanner^);
				}
		private:
			HyperscanContext^ m_Context;
			ICompiler^ m_Compiler;
			IScanner^ m_Scanner;
			MatchObservable^ m_MatchObservable;
		};
	}
}