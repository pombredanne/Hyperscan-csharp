#pragma once

namespace Hyperscan {
	namespace Utils {
		public ref class StringUtils {
		public:
			static char* Substring(const char* src, long long startIndex, long long endIndex);
		};
	}
}