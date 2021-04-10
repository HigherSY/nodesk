#pragma once
#include "framework.h"

BOOL SimpleCreateProcess(LPWSTR lpCmdLine);
BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation);
