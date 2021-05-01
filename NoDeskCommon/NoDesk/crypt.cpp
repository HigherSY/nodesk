#include "NoDesk/crypt.h"

#include <bcrypt.h>

#pragma comment(lib, "bcrypt.Lib")

#define NT_SUCCESS(Status)	(((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL	((NTSTATUS)0xC0000001L)
#define BUFSIZE 1024

namespace crypt {
    CONST CHAR rgbDigits[] = "0123456789abcdef";

	bool computeSHA256(LPCWSTR filename, std::string& szHash) {

		BCRYPT_ALG_HANDLE hAlg = NULL;
		BCRYPT_HASH_HANDLE hHash = NULL;

        DWORD cbData = 0, cbHash = 0, cbHashObject = 0;

		PBYTE pbHashObject = NULL;
        PBYTE pbHash = NULL;

        HANDLE hFile = NULL;
        BYTE rgbFile[BUFSIZE];
        DWORD cbRead = 0;

		NTSTATUS status = STATUS_UNSUCCESSFUL;
        BOOL bResult = FALSE;

		if (!NT_SUCCESS(status =BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA256_ALGORITHM, NULL, 0))) {
			goto Cleanup;
		}

        if (!NT_SUCCESS(status =BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbData, 0))) {
            goto Cleanup;
        }

        pbHashObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHashObject);

        if (!NT_SUCCESS(status = BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, (PBYTE)&cbHash, sizeof(DWORD), &cbData, 0))) {
            goto Cleanup;
        }

        pbHash = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHash);

        if (!NT_SUCCESS(status = BCryptCreateHash(hAlg, &hHash, pbHashObject, cbHashObject, NULL, 0, 0))) {
            goto Cleanup;
        }

        hFile = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
        if (INVALID_HANDLE_VALUE == hFile)
        {
            goto Cleanup;
        }

        while (bResult = ReadFile(hFile, rgbFile, BUFSIZE, &cbRead, NULL))
        {
            if (0 == cbRead)
            {
                break;
            }

            if (!NT_SUCCESS(status = BCryptHashData(hHash, (PBYTE)rgbFile, cbRead, 0))) {
                goto Cleanup;
            }
        }

        if (!bResult) {
            goto Cleanup;
        }

        if (!NT_SUCCESS(BCryptFinishHash(hHash, pbHash, cbHash, 0))) {
            goto Cleanup;
        }

        szHash.clear();
        szHash.reserve(cbHash * 2 + 1);

        for (DWORD i = 0; i < cbHash; i++) {
            szHash.push_back(rgbDigits[pbHash[i] >> 4]);
            szHash.push_back(rgbDigits[pbHash[i] & 0xf]);
        }

    Cleanup:

        if (hAlg)
        {
            BCryptCloseAlgorithmProvider(hAlg, 0);
        }

        if (hHash)
        {
            BCryptDestroyHash(hHash);
        }

        if (pbHashObject)
        {
            HeapFree(GetProcessHeap(), 0, pbHashObject);
        }

        if (pbHash)
        {
            HeapFree(GetProcessHeap(), 0, pbHash);
        }

        if (hFile && INVALID_HANDLE_VALUE != hFile) {
            CloseHandle(hFile);
        }

        return true;
	}
}
