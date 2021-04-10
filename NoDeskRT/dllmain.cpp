#include "dllmain.h"
#include <detours.h>

#include "DetourFunctions.h"

WCHAR szSelfPath[MAX_PATH];

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        GetModuleFileNameW(hModule, szSelfPath, MAX_PATH);
        
        DetourRestoreAfterWith();

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
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
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
        break;
    }
    return TRUE;
}

