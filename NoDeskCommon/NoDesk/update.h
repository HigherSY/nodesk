#pragma once
#include "framework.h"

namespace update {
    bool GetUpdateInfo(LPCSTR updateSource, std::string& szUpdateInfo);

    bool DownloadAndUpdate(const std::string& szUpdateInfo);
}
