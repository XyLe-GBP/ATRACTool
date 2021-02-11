
// ATRACToolDlg.h : ヘッダー ファイル
//

#pragma once


// CATRACToolDlg ダイアログ
class CATRACToolDlg : public CDialogEx
{
// コンストラクション
public:
	CATRACToolDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATRACTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_hREADFILE;
	CStatic m_hStatus, m_hFileFullName, m_hFileFullPath;
	int m_hRadioFlag{};
	afx_msg void OnOpenFile();
	afx_msg void OnCloseFile();
	afx_msg void OnBnClickedButtonDecode();
	afx_msg void OnBnClickedButtonEncode();
	afx_msg void OnAt3settings();
	afx_msg void OnAt9Settings();
	afx_msg void OnAbout();
	afx_msg void OnUpdate();
	afx_msg void OnExit();
	afx_msg void OnDestroy();
	afx_msg void OnDeleteIniFile();
};
