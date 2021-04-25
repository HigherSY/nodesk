#pragma once
#include "framework.h"

BOOL SimpleCreateProcess(LPCWSTR lpApp, LPWSTR lpCmdLine = NULL);
BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation);
