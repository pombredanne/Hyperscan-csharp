#pragma once

namespace Hyperscan {
	namespace Scanning {
		public ref class Match {
		public:
			Match(int id, System::String^ result);
			property int Id {
				int get();
			}
			property System::String^ Result {
				System::String^ get();
			}
		private:
			int m_Id;
			System::String^ m_Result;
		};
	}
}
