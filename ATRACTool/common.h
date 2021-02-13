#pragma once
#include "pch.h"
#include <io.h>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <string>
#include "wininet.h" 
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "version.lib")
#include <mmsystem.h>

#include "common.define.h"

void LoadResources();
CString DEF_TEXT();
CString READ_TEXT();
CString CURRENT_VER();
DWORD GetFileSizeStat(const wchar_t* fp);
BOOL DeleteDirectory(LPCTSTR lpPathName);
bool checkExistenceOfFolder(const std::string folder_name);
CString AfxReplaceStr(CString& replacedStr, CString from, CString to);
CStringA AfxReplaceStrA(CStringA& replacedStr, CStringA from, CStringA to);
CString AppUpdateCheck();
CString AppCurrentVersionCheck();