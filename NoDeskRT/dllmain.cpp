#include "dllmain.h"

#include <detours.h>

#include "NoDesk/strings.h"
#include "DetourFunctions.h"

WCHAR szSelfPath[MAX_PATH];
WCHAR szExePath[MAX_PATH];

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_THREAD_ATTACH || ul_reason_for_call == DLL_THREAD_DETACH) return TRUE;

    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        GetModuleFileNameW(hModule, szSelfPath, MAX_PATH);
        GetModuleFileNameW(NULL, szExePath, MAX_PATH);

        if (wcscmp(PathFindFileNameW(szExePath), L"dwm.exe") != 0) {
            DEBUG(szExePath);
            FreeLibraryAndExitThread(hModule, ERROR_ACCESS_DENIED);
            return FALSE;
        }

        // DetourRestoreAfterWith();

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)fpCreateProcessW, MyCreateProcessW);
        DetourAttach(&(PVOID&)fpCreateProcessAsUserW, MyCreateProcessAsUserW);
        DetourAttach(&(PVOID&)fpCreateProcessWithTokenW, MyCreateProcessWithTokenW);
        DetourAttach(&(PVOID&)fpCreateWindowExW, MyCreateWindowExW);
        DetourAttach(&(PVOID&)fpShowWindow, MyShowWindow);
        DetourAttach(&(PVOID&)fpSetWindowPos, MySetWindowPos);
        DetourAttach(&(PVOID&)fpShell_NotifyIconW, MyShell_NotifyIconW);
        DetourTransactionCommit();
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)fpCreateProcessW, MyCreateProcessW);
        DetourDetach(&(PVOID&)fpCreateProcessAsUserW, MyCreateProcessAsUserW);
        DetourDetach(&(PVOID&)fpCreateProcessWithTokenW, MyCreateProcessWithTokenW);
        DetourDetach(&(PVOID&)fpCreateWindowExW, MyCreateWindowExW);
        DetourDetach(&(PVOID&)fpShowWindow, MyShowWindow);
        DetourDetach(&(PVOID&)fpSetWindowPos, MySetWindowPos);
        DetourDetach(&(PVOID&)fpShell_NotifyIconW, MyShell_NotifyIconW);
        DetourTransactionCommit();
    }

    return TRUE;
}

