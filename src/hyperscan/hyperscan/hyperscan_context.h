#pragma once

namespace Hyperscan {
	namespace Core {
		public ref class HyperscanContext {
		public:
			HyperscanContext();
			~HyperscanContext();
			!HyperscanContext();
		internal:
			System::String^ m_Pattern;
			hs_database_t* m_Database;
			hs_scratch_t* m_Scratch = NULL;
		};
	}
}