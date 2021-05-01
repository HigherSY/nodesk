#include "NoDesk/update.h"

#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include "NoDesk/paths.h"
#include "NoDesk/strings.h"
#include "NoDesk/process.h"

#ifndef _DEBUG

#pragma comment(lib, "Ws2_32.Lib")
#pragma comment(lib, "Wldap32.Lib")
#pragma comment(lib, "Crypt32.Lib")

#endif // !_DEBUG

using json = nlohmann::json;

namespace update {
    int writeToString(char* data, size_t size, size_t nmemb,
        std::string* writerData)
    {
        if (writerData == NULL)
            return 0;

        writerData->append(data, size * nmemb);

        return size * nmemb;
    }

    CURL* createCURL(LPCSTR url) {
        CURL* conn = curl_easy_init();

        if (conn) {
            curl_easy_setopt(conn, CURLOPT_URL, url);
            curl_easy_setopt(conn, CURLOPT_CONNECTTIMEOUT, 3);
            curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, TRUE);

            return conn;
        }
        else return nullptr;
	}

    bool performAndOK(CURL* conn) {
        CURLcode res;
        res = curl_easy_perform(conn);
        if (res != CURLE_OK) {
            DEBUG(L"[NoDesk] Update: CURL Error: %d", res);
            return false;
        }

        long response_code;
        curl_easy_getinfo(conn, CURLINFO_RESPONSE_CODE, &response_code);
        if (200 <= response_code && response_code <= 299) {
            return true;
        }
        else {
            DEBUG(L"[NoDesk] Update: Unsuccessful response: %d", response_code);
            return false;
        }
    }

	bool GetUpdateInfo(LPCSTR updateSource, std::string& szUpdateInfo) {
        CURL* conn = createCURL(updateSource);

        if (!conn) return false;

        curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writeToString);
        curl_easy_setopt(conn, CURLOPT_WRITEDATA, &szUpdateInfo);
        if (performAndOK(conn)) {
            curl_easy_cleanup(conn);
            return true;
        }
        else {
            curl_easy_cleanup(conn);
            return false;
        }
	}

    bool DownloadAndUpdate(const std::string& szUpdateInfo) {
        auto jsUpdateInfo = json::parse(szUpdateInfo);
        std::string launcherURL = jsUpdateInfo.at("launcher_url").get<std::string>();

        DWORD err;
        if (!DeleteFileW(L"launcher.tmp") && (err = GetLastError()) != ERROR_FILE_NOT_FOUND) {
            DEBUG(L"[NoDesk] Update: 无法删除 tmp");
            return false;
        }

        if (!DeleteFileW(L"launcher.old") && (err = GetLastError()) != ERROR_FILE_NOT_FOUND) {
            DEBUG(L"[NoDesk] Update: 无法删除 old");
            return false;
        }

        CURL* conn = createCURL(launcherURL.c_str());
        if (!conn) return false;

        FILE* launcherTemp;
        _wfopen_s(&launcherTemp, L"launcher.tmp", L"wb");

        if (launcherTemp == nullptr) {
            DEBUG(L"[NoDesk] Update: 无法创建 tmp 文件");
            curl_easy_cleanup(conn);
            return false;
        }

        curl_easy_setopt(conn, CURLOPT_WRITEDATA, launcherTemp);

        if (performAndOK(conn)) {
            fclose(launcherTemp);
            curl_easy_cleanup(conn);

            if (!MoveFileW(target_launcher, L"launcher.old")) {
                DEBUG(L"[NoDesk] Update: 无法移动至 old");
                return false;
            }

            if (MoveFileW(L"launcher.tmp", target_launcher)) {
                SimpleCreateProcess(target_launcher);
                ExitProcess(0);
                return true;
            }
            else {
                DEBUG(L"[NoDesk] Update: 移动至 exe 错误: %u", GetLastError());
                return false;
            }
        }
        else {
            fclose(launcherTemp);
            curl_easy_cleanup(conn);
        }
    }
}
