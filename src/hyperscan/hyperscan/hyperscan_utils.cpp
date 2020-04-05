#include "pch.h"

#include <algorithm>
#include <string.h>
#include "hyperscan_utils.h"

using namespace Hyperscan::Utils;

char* StringUtils::Substring(const char* src, long long startIndex, long long endIndex) {
	long long length = endIndex - startIndex;
	if (length < 0)
		return NULL;

	char* dest = new char[length + 1];

	std::copy(src + startIndex, src + endIndex, dest);
	dest[length] = '\0';

	return dest;
}