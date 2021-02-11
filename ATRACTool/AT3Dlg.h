#pragma once


// AT3Dlg ダイアログ

class AT3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(AT3Dlg)

public:
	AT3Dlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~AT3Dlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AT3SETTINGS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int m_hRADIOCHANNEL{};
	CString TOOL = _T("at3tool -e"), BITRATE, CHANNEL, LOOPFLAG, LOOPSTART, LOOPEND, WHOLELOOPFLAG, LOOPPARTFLAG, LOOPPART, CMDPARAM;
	CString m_hLoopStartLength, m_hLoopEndLength, m_hLoopPart;
	CComboBox m_hBitrate;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboBitrate();
	afx_msg void OnEnChangeEditLoopstart();
	afx_msg void OnEnChangeEditLoopend();
	afx_msg void OnBnClickedCheckLooppoint();
	afx_msg void OnBnClickedCheckWholeloop();
	afx_msg void OnEnChangeEditLooppart();
	afx_msg void OnBnClickedCheckPartloop();
};
