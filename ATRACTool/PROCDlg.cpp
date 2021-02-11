// PROCDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "ATRACTool.h"
#include "PROCDlg.h"
#include "afxdialogex.h"


// PROCDlg ダイアログ

IMPLEMENT_DYNAMIC(PROCDlg, CDialogEx)

PROCDlg::PROCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS_DLG, pParent)
{

}

PROCDlg::~PROCDlg()
{
}

void PROCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PROCDlg, CDialogEx)
END_MESSAGE_MAP()


// PROCDlg メッセージ ハンドラー
