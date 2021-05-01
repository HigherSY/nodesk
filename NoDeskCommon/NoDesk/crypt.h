#pragma once
#include "framework.h"

namespace crypt {
	bool computeSHA256(LPCWSTR filename, std::string& szHash);
}
