#pragma once


// AT9Dlg ダイアログ

class AT9Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(AT9Dlg)

public:
	AT9Dlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~AT9Dlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AT9SETTINGS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

	CComboBox m_hBitrate, m_hSampling, m_hEncodeMode;
	CString CMDPARAM, TOOL = _T("at9tool -e"), BITRATE, SAMPLING, LOOPFLAG, LOOPSTART, LOOPEND, WHOLELOOPFLAG, LOOPPARTFLAG, LOOPPART, LOOPLISTFLAG, LOOPLIST, SUPFRAMEFLAG, DUALFLAG, NBANDSFLAG, NBANDS, ISBANDFLAG, ISBAND, GRADMODEFLAG, GRADMODE;
	CString m_hLoopStart, m_hLoopEnd, m_hLoopPart, m_hLoopList, m_hNbands, m_hIsband;
	int m_hSupframe;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboBitrate();
	afx_msg void OnCbnSelchangeComboSampling();
	afx_msg void OnBnClickedCheckLooppoint();
	afx_msg void OnEnChangeEditLoopstart();
	afx_msg void OnEnChangeEditLoopend();
	afx_msg void OnBnClickedCheckWholeloop();
	afx_msg void OnBnClickedCheckPartloop();
	afx_msg void OnEnChangeEditPartloop();
	afx_msg void OnBnClickedCheckLooplist();
	afx_msg void OnEnChangeEditLooplist();
	afx_msg void OnBnClickedButtonOpenlist();
	afx_msg void OnBnClickedCheckAdvanced();
	afx_msg void OnBnClickedCheckDualenc();
	afx_msg void OnBnClickedCheckBand();
	afx_msg void OnEnChangeEditNbands();
	afx_msg void OnEnChangeEditIsband();
	afx_msg void OnCbnSelchangeComboEncmode();
	afx_msg void OnBnClickedRadioSupframeOn();
	afx_msg void OnBnClickedRadioSupframeOff();
};
