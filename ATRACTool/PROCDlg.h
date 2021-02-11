#pragma once


// PROCDlg ダイアログ

class PROCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PROCDlg)

public:
	PROCDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~PROCDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
