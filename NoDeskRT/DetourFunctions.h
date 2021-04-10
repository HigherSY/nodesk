#pragma once
#include "framework.h"
#include <Shellapi.h>

typedef HWND(WINAPI* fnCreateWindowExW)(
	DWORD     dwExStyle,
	LPCWSTR   lpClassName,
	LPCWSTR   lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
	);

extern fnCreateWindowExW fpCreateWindowExW;

HWND WINAPI MyCreateWindowExW(
	DWORD     dwExStyle,
	LPCWSTR   lpClassName,
	LPCWSTR   lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
);

typedef HWND(WINAPI* fnCreateWindowExA)(
	DWORD     dwExStyle,
	LPCSTR    lpClassName,
	LPCSTR    lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
	);

extern fnCreateWindowExA fpCreateWindowExA;

HWND WINAPI MyCreateWindowExA(
	DWORD     dwExStyle,
	LPCSTR    lpClassName,
	LPCSTR    lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
);

typedef BOOL(WINAPI* fnShowWindow)(
	HWND hWnd,
	int  nCmdShow
	);

extern fnShowWindow fpShowWindow;

BOOL WINAPI MyShowWindow(
	HWND hWnd,
	int  nCmdShow
);

typedef BOOL (WINAPI* fnSetWindowPos)(
	HWND hWnd,
	HWND hWndInsertAfter,
	int  X,
	int  Y,
	int  cx,
	int  cy,
	UINT uFlags
);

extern fnSetWindowPos fpSetWindowPos;

BOOL WINAPI MySetWindowPos(
	HWND hWnd,
	HWND hWndInsertAfter,
	int  X,
	int  Y,
	int  cx,
	int  cy,
	UINT uFlags
);

typedef BOOL(WINAPI * fnCreateProcessW)(
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

extern fnCreateProcessW fpCreateProcessW;

BOOL WINAPI MyCreateProcessW(
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

typedef BOOL(WINAPI* fnCreateProcessAsUserW)(
	HANDLE                hToken,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

extern fnCreateProcessAsUserW fpCreateProcessAsUserW;

BOOL WINAPI MyCreateProcessAsUserW(
	HANDLE                hToken,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

typedef BOOL(WINAPI* fnCreateProcessWithTokenW)(
	HANDLE                hToken,
	DWORD                 dwLogonFlags,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

extern fnCreateProcessWithTokenW fpCreateProcessWithTokenW;

BOOL WINAPI MyCreateProcessWithTokenW(
	HANDLE                hToken,
	DWORD                 dwLogonFlags,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);

typedef BOOL (WINAPI * fnShell_NotifyIconW)(
	DWORD            dwMessage,
	PNOTIFYICONDATAW lpData
);

extern fnShell_NotifyIconW fpShell_NotifyIconW;

BOOL WINAPI MyShell_NotifyIconW(
	DWORD            dwMessage,
	PNOTIFYICONDATAW lpData
);
