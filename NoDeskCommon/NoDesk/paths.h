#pragma once
#include "framework.h"

extern PWSTR sys_ProgramFiles;
extern PWSTR usr_RoamingAppData;
extern PWSTR usr_UserProgramFiles;
extern WCHAR target_dir[MAX_PATH];
extern WCHAR target_dll[MAX_PATH];
extern WCHAR target_exe[MAX_PATH];
extern WCHAR target_launcher[MAX_PATH];
extern WCHAR config_dir[MAX_PATH];
extern WCHAR config_service[MAX_PATH];
extern WCHAR szCurName[MAX_PATH];

void GeneratePaths();
