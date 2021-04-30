#pragma once
#include "framework.h"

#ifndef _DEBUG

#pragma comment(lib, "Ws2_32.Lib")
#pragma comment(lib, "Wldap32.Lib")
#pragma comment(lib, "Crypt32.Lib")

#endif // !_DEBUG

namespace update {
    bool GetUpdateInfo(LPCSTR updateSource, std::string& szUpdateInfo);

    bool DownloadAndUpdate(const std::string& szUpdateInfo);
}
