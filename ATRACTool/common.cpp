#include "pch.h"
#include "common.h"
#include "resource.h"
#include "ATRACToolDlg.h"

void LoadResources() {
	HINSTANCE hinst = AfxGetInstanceHandle();
	if (!hinst) {
		OutputDebugString(_T("Instance handle not found."));
	}
	const HRSRC hResInfo1 = FindResource(
		NULL,					// モジュール（リソース）のハンドル
		MAKEINTRESOURCE(IDR_EXE1),	// リソースの名前 
		L"EXE");					// リソースの種類
	const HRSRC hResInfo2 = FindResource(
		NULL,					// モジュール（リソース）のハンドル
		MAKEINTRESOURCE(IDR_EXE2),	// リソースの名前 
		L"EXE");					// リソースの種類

	// リソースを読みだす（リソースに関連付けられたデータのハンドルを取得）
	if (hResInfo1 != 0 && hResInfo2 != 0 ) {
		const HGLOBAL hResData1 = LoadResource(
			NULL,	// モジュール（リソース）のハンドル
			hResInfo1);	// リソースのハンドル
		const HGLOBAL hResData2 = LoadResource(
			NULL,	// モジュール（リソース）のハンドル
			hResInfo2);	// リソースのハンドル

		// リソースデータへのポインタを取得
		if (hResData1 != 0 && hResData2 != 0 ) {
			const LPVOID pvResData1 = LockResource(hResData1);
			const LPVOID pvResData2 = LockResource(hResData2);

			DWORD ResSize1 = SizeofResource(
				NULL,	// モジュール（リソース）のハンドル
				hResInfo1);	// リソースのハンドル
			DWORD ResSize2 = SizeofResource(
				NULL,	// モジュール（リソース）のハンドル
				hResInfo2);	// リソースのハンドル

			FILE* FP;
			_wfopen_s(&FP, L".\\Resources\\at3tool.exe", L"wb");
			if (FP == NULL) {
				return;
			}

			// ファイルの書き込み
			fwrite(
				pvResData1,	// 書き込むファイルのポインタ
				ResSize1,	// 書き込むファイルのサイズ
				1,			// 書き込むファイルの個数
				FP);		// 書き込み先のファイルポインタ

			fclose(FP);
			_wfopen_s(&FP, L".\\Resources\\at9tool.exe", L"wb");
			if (FP == NULL) {
				return;
			}

			fwrite(
				pvResData2,	// 書き込むファイルのポインタ
				ResSize2,	// 書き込むファイルのサイズ
				1,			// 書き込むファイルの個数
				FP);		// 書き込み先のファイルポインタ

			fclose(FP);

			return;
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}

CString DEF_TEXT() {
	CString FUNCTION = _T("なにも読み込んでいません");
	return FUNCTION;
}

CString READ_TEXT() {
	CString FUNCTION = _T("読み込み完了");
	return FUNCTION;
}

DWORD GetFileSizeStat(const wchar_t* fp) {
	struct _stat st;
	if (_wstat(fp, &st) != 0) {
		return NULL;
	}
	if ((st.st_mode & S_IFMT) != S_IFREG) {
		return NULL;
	}

	return st.st_size;
}

BOOL DeleteDirectory(LPCTSTR lpPathName) {
	CFileFind fnd;
	CString strPathName = lpPathName;
	strPathName.TrimRight('\\');
	strPathName += _T("\\*.*");
	if (fnd.FindFile(strPathName, 0))
	{
		int i = 1;
		while (i)
		{
			i = fnd.FindNextFile();

			// ファイル名が"."か".."の場合は次を検索
			if (fnd.IsDots())
				continue;

			// 削除するファイル名取得
			// GetFilePath()にはバグがあり正確に取得できない場合があるので使わない
			CString strDeleteFile = lpPathName;
			strDeleteFile.TrimRight('\\');
			strDeleteFile += _T("\\") + fnd.GetFileName();

			// フォルダだった場合、再帰呼び出しでそのフォルダを削除
			if (fnd.IsDirectory())
				DeleteDirectory(strDeleteFile);

			// ファイルの削除
			else
				::DeleteFile(strDeleteFile);
		}
		fnd.Close();

		// フォルダの削除
		return ::RemoveDirectory(lpPathName);
	}
	return FALSE;
}

bool checkExistenceOfFolder(const std::string folder_name)
{
	if (_mkdir(folder_name.c_str()) == 0) {
		return true;
	}
	else {
		return false;
	}
}

CString AfxReplaceStr(CString& replacedStr, CString from, CString to) {
	const DWORD32 pos = replacedStr.Find(from);
	const INT len = from.GetLength();

	if (pos == std::string::npos || from.IsEmpty()) {
		return replacedStr;
	}

	replacedStr.Replace(from, to);
	return replacedStr;
}


CStringA AfxReplaceStrA(CStringA& replacedStr, CStringA from, CStringA to) {
	const DWORD32 pos = replacedStr.Find(from);
	const INT len = from.GetLength();

	if (pos == std::string::npos || from.IsEmpty()) {
		return replacedStr;
	}

	replacedStr.Replace(from, to);
	return replacedStr;
}

CString AppUpdateCheck() {
	HINTERNET    hNet;
	HINTERNET    hUrl;
	HINTERNET hHttpSession;
	HINTERNET hHttpRequest;
	DWORD BufSizeTextSize = 1000;
	DWORD StatusCode = sizeof(DWORD);
	DWORD StatusCode_Size = sizeof(DWORD);
	wchar_t Path[MAX_PATH + 1], Drive[10], Dir[MAX_PATH], Name[MAX_PATH], Ext[MAX_PATH];
	wchar_t ptr[MAX_PATH] = { 0 };
	TCHAR m_cPath[MAX_PATH + 1];

	CString URL;
	CString URL2;

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
		_tsplitpath_s(Path, Drive, Dir, Name, Ext);
		CString NAME = Name;
		URL = _T("https://res.xyle-official.com/versions/") + NAME.MakeLower() + _T("/");
		URL2 = _T("https://res.xyle-official.com/versions/") + NAME.MakeLower() + _T("/VERSIONINFO");
	}

	// 初期化
	hNet = ::InternetOpen(L"UpdateCheck...",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);
	if (hNet == NULL)
		return NULL;

	/* サーバへ接続 */
	hHttpSession = InternetConnect(
		hNet,
		_T("xyle-official.com"),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		0,
		0);

	/* HTTP要求の作成 */
	hHttpRequest = HttpOpenRequest(
		hHttpSession,
		_T("GET"),
		_T("VERSIONINFO"),
		NULL,
		URL,
		NULL,
		0,
		0);
	OutputDebugString(_T("Request URI:( ") + URL + _T(" )\n"));

	/* 作成したHTTP要求の発行 */
	BOOL bHttpSendRequest = HttpSendRequest(
		hHttpRequest,
		NULL,
		0,
		NULL,
		0);

	if (bHttpSendRequest == 0) {//bHttpSendRequestが0の場合はインターネットに接続されいないので、エラーを返す。
		::InternetCloseHandle(hNet);
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		return NULL;//106:ERR_INTERNET_DISCONNECTED
	}

	/* 返されたコンテンツの長さを取得 */
	HttpQueryInfo(
		hHttpRequest,
		HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
		&StatusCode,
		&StatusCode_Size,
		NULL);

	CString STC;
	STC.Format(_T("%d"), StatusCode);

	if (StatusCode != HTTP_STATUS_OK) {
		OutputDebugString(_T("HTTP Request failed.\n"));
		OutputDebugString(_T("HTTP Status code: ") + STC);
		OutputDebugString(_T("\n"));
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hNet);
		return NULL;
	}
	else {
		OutputDebugString(_T("HTTP Request completed.\n"));
		OutputDebugString(_T("HTTP Status code: ") + STC);
		OutputDebugString(_T("\n"));

		// バージョンチェック用のページ
		::_tcscpy_s(m_cPath, MAX_PATH, URL2);

		// URLオープン
		hUrl = ::InternetOpenUrl(hNet,
			m_cPath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
		if (hUrl == NULL)
		{
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hNet);
			return NULL;
		}

		// 読み込み
		TCHAR m_wBuf[256] = { sizeof(TCHAR) };
		DWORD dwReadSize = 0;
		::InternetReadFile(hUrl, m_wBuf, 256, &dwReadSize);
		if (dwReadSize == 256) {
			::InternetCloseHandle(hHttpRequest);
			::InternetCloseHandle(hHttpSession);
			::InternetCloseHandle(hUrl);
			::InternetCloseHandle(hNet);
			OutputDebugString(_T("Exception occured.\n"));
			return _T("-1");
		}
		m_wBuf[dwReadSize] = '\0';

		// クローズ
		::InternetCloseHandle(hHttpRequest);
		::InternetCloseHandle(hHttpSession);
		::InternetCloseHandle(hUrl);
		::InternetCloseHandle(hNet);

		// 変換
		char m_cBuf[256];

		const int cchWideByte = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, NULL, NULL);
		LPWSTR lpw = new WCHAR[cchWideByte];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_wBuf, -1, lpw, cchWideByte);

		const int cchMultiByte = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, NULL, 0, NULL, NULL);
		LPSTR lpa = new CHAR[cchMultiByte];

		const int nMultiCount = ::WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, cchMultiByte, NULL, NULL);

		::strcpy_s(m_cBuf, 256, lpa);

		delete[] lpa;
		delete[] lpw;

		// 解析
		char cVersion[256] = { 0 };
		char* cTmp = NULL, * cNext = NULL;
		cTmp = ::strtok_s(m_cBuf, ":", &cNext);
		if (::strcmp(cTmp, "version") == 0)
		{
			cTmp = ::strtok_s(NULL, "\n", &cNext);
			::strcpy_s(cVersion, 256, cTmp);
		}
		CString FINAL;
		FINAL = cVersion;
		OutputDebugString(_T("Latest version: ") + FINAL);
		OutputDebugString(_T("\n"));

		return FINAL;
	}
}


CString AppCurrentVersionCheck() {
	DWORD dwLen;
	DWORD dwHandle;
	TCHAR cBuf[256] = { NULL };
	wchar_t Path[MAX_PATH + 1];

	if (0 != GetModuleFileName(NULL, Path, MAX_PATH)) {// 実行ファイルの完全パスを取得
	}
	const TCHAR* const AppName = Path;

	dwLen = ::GetFileVersionInfoSize(AppName, &dwHandle);
	if (dwLen > 0)
	{
		char* lpData = new char[static_cast<DWORD64>(dwLen) + 1];
		::GetFileVersionInfo(AppName, NULL, dwLen, lpData);

		// 情報を取得する
		void* pvVersion;
		UINT VersionLen;
		::VerQueryValue(lpData, L"\\StringFileInfo\\041104b0\\ProductVersion", &pvVersion, &VersionLen);

		::_stprintf_s(cBuf, 256, _T("%s"), static_cast<wchar_t*>(pvVersion));

		delete[] lpData;
	}
	return cBuf;
}