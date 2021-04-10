#include "strings.h"

size_t wcslenb(LPCWSTR wstr) {
	size_t len;
	if SUCCEEDED(StringCbLengthW(wstr, MAX_PATH, &len)) {
		return len;
	}
	else return 0;
}

void DEBUG(LPCWSTR format, ...) {
	WCHAR t[MAX_PATH];
	va_list va;
	va_start(va, format);
	StringCchVPrintfW(t, MAX_PATH, format, va);
	va_end(va);

	OutputDebugStringW(t);
}
