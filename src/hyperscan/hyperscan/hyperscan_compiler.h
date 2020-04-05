#pragma once

#include "hyperscan_context.h"
#include "hyperscan_exception.h"

using namespace System::Runtime::InteropServices;
using namespace Hyperscan::Core;
using namespace Hyperscan::Core::Exceptions;

namespace Hyperscan {
	namespace Compilation {
		public interface class ICompiler {

		};

		public ref class Compiler : public ICompiler {
		public:
			Compiler(HyperscanContext^ context, System::String^ pattern);
		private:
			HyperscanContext^ m_Context;
		};
	}
}
