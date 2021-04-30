#include "NoDesk.h"

#include <nlohmann/json.hpp>

#include "NoDesk/strings.h"
#include "NoDesk/paths.h"
#include "NoDesk/process.h"
#include "NoDesk/update.h"

#define UPDATE_SOURCE "http://localhost:8000/update_v1.json"
#define LOCAL_VERSION 0

using json = nlohmann::json;

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
	GeneratePaths();
	GetModuleFileNameW(hInst, szSelfFilename, MAX_PATH);
	if (wcscmp(szSelfFilename, target_launcher) != 0) {
		return 0;
	}

	std::string szUpdateInfo;
	if (update::GetUpdateInfo(UPDATE_SOURCE, szUpdateInfo)) {
		auto jsUpdateInfo = json::parse(szUpdateInfo);
		int remoteVersion = jsUpdateInfo["version"].get<int>();

		if (remoteVersion > LOCAL_VERSION) {
			update::DownloadAndUpdate(szUpdateInfo);
		}
	}

	if (!PathFileExistsW(target_dll)) {
		DEBUG(L"[NoDesk] Launcher: crt.dll not found.");
		return 0;
	}

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	if (!PathFileExistsW(target_exe)) {
		DEBUG(L"[NoDesk] Launcher: AnyDesk not found.");
		return 0;
	}

	if (!CreateProcessW(NULL, target_exe, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		DEBUG(L"[NoDesk] Launcher: CreateProcess failed with %lu", GetLastError());
		return 0;
	}

	if (InjectDllToProcess(target_dll, &pi)) ResumeThread(pi.hThread);
	else {
		DEBUG(L"[NoDesk] Launcher: CreateProcess failed with %lu", GetLastError());
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
