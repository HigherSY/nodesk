#include "process.h"

#include "NoDesk/process.h"
#include "NoDesk/strings.h"

BOOL SimpleCreateProcess(LPWSTR lpCmdLine)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_NORMAL;

	BOOL ret = CreateProcessW(NULL, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return ret;
}

BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation) {
	LPVOID Param = VirtualAllocEx(lpProcessInformation->hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!Param) {
		return FALSE;
	}

	WriteProcessMemory(lpProcessInformation->hProcess, Param, (LPVOID)pszDllPath, wcslenb(pszDllPath), NULL);

	HANDLE hThread = CreateRemoteThread(lpProcessInformation->hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryW, Param, CREATE_SUSPENDED, NULL);
	if (hThread)
	{
		ResumeThread(hThread);
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		return TRUE;
	}
	else {
		DEBUG(L"[NoDesk]: CreateRemoteThread failed with %lu", GetLastError());
		TerminateProcess(lpProcessInformation->hProcess, 0);
		return FALSE;
	}

	return FALSE;
}
