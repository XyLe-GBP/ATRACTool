
// ATRACTool.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CATRACToolApp:
// このクラスの実装については、ATRACTool.cpp を参照してください
//

class CATRACToolApp : public CWinApp
{
public:
	CATRACToolApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CATRACToolApp theApp;
