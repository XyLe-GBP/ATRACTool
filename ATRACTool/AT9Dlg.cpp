// AT9Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "ATRACTool.h"
#include "AT9Dlg.h"
#include "afxdialogex.h"
#include "PROCDlg.h"


// AT9Dlg ダイアログ

IMPLEMENT_DYNAMIC(AT9Dlg, CDialogEx)

AT9Dlg::AT9Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AT9SETTINGS_DLG, pParent)
	, m_hLoopStart(_T(""))
	, m_hLoopEnd(_T(""))
	, m_hLoopPart(_T(""))
	, m_hLoopList(_T(""))
	, m_hNbands(_T(""))
	, m_hIsband(_T(""))
	, m_hSupframe(0)
{

}

AT9Dlg::~AT9Dlg()
{
}

void AT9Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_hBitrate);
	DDX_Control(pDX, IDC_COMBO_SAMPLING, m_hSampling);
	DDX_Control(pDX, IDC_COMBO_ENCMODE, m_hEncodeMode);
	DDX_Text(pDX, IDC_EDIT_LOOPSTART, m_hLoopStart);
	DDV_MaxChars(pDX, m_hLoopStart, 11);
	DDX_Text(pDX, IDC_EDIT_LOOPEND, m_hLoopEnd);
	DDV_MaxChars(pDX, m_hLoopEnd, 11);
	DDX_Text(pDX, IDC_EDIT_PARTLOOP, m_hLoopPart);
	DDV_MaxChars(pDX, m_hLoopPart, 3);
	DDX_Text(pDX, IDC_EDIT_LOOPLIST, m_hLoopList);
	DDV_MaxChars(pDX, m_hLoopList, MAX_PATH);
	DDX_Text(pDX, IDC_EDIT_NBANDS, m_hNbands);
	DDV_MaxChars(pDX, m_hNbands, 2);
	DDX_Text(pDX, IDC_EDIT_ISBAND, m_hIsband);
	DDV_MaxChars(pDX, m_hIsband, 5);
	DDX_Radio(pDX, IDC_RADIO_SUPFRAME_ON, m_hSupframe);
}


BEGIN_MESSAGE_MAP(AT9Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AT9Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AT9Dlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_BITRATE, &AT9Dlg::OnCbnSelchangeComboBitrate)
	ON_CBN_SELCHANGE(IDC_COMBO_SAMPLING, &AT9Dlg::OnCbnSelchangeComboSampling)
	ON_BN_CLICKED(IDC_CHECK_LOOPPOINT, &AT9Dlg::OnBnClickedCheckLooppoint)
	ON_EN_CHANGE(IDC_EDIT_LOOPSTART, &AT9Dlg::OnEnChangeEditLoopstart)
	ON_EN_CHANGE(IDC_EDIT_LOOPEND, &AT9Dlg::OnEnChangeEditLoopend)
	ON_BN_CLICKED(IDC_CHECK_WHOLELOOP, &AT9Dlg::OnBnClickedCheckWholeloop)
	ON_BN_CLICKED(IDC_CHECK_PARTLOOP, &AT9Dlg::OnBnClickedCheckPartloop)
	ON_EN_CHANGE(IDC_EDIT_PARTLOOP, &AT9Dlg::OnEnChangeEditPartloop)
	ON_BN_CLICKED(IDC_CHECK_LOOPLIST, &AT9Dlg::OnBnClickedCheckLooplist)
	ON_EN_CHANGE(IDC_EDIT_LOOPLIST, &AT9Dlg::OnEnChangeEditLooplist)
	ON_BN_CLICKED(IDC_BUTTON_OPENLIST, &AT9Dlg::OnBnClickedButtonOpenlist)
	ON_BN_CLICKED(IDC_CHECK_ADVANCED, &AT9Dlg::OnBnClickedCheckAdvanced)
	ON_BN_CLICKED(IDC_CHECK_DUALENC, &AT9Dlg::OnBnClickedCheckDualenc)
	ON_BN_CLICKED(IDC_CHECK_BAND, &AT9Dlg::OnBnClickedCheckBand)
	ON_EN_CHANGE(IDC_EDIT_NBANDS, &AT9Dlg::OnEnChangeEditNbands)
	ON_EN_CHANGE(IDC_EDIT_ISBAND, &AT9Dlg::OnEnChangeEditIsband)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCMODE, &AT9Dlg::OnCbnSelchangeComboEncmode)
	ON_BN_CLICKED(IDC_RADIO_SUPFRAME_ON, &AT9Dlg::OnBnClickedRadioSupframeOn)
	ON_BN_CLICKED(IDC_RADIO_SUPFRAME_OFF, &AT9Dlg::OnBnClickedRadioSupframeOff)
END_MESSAGE_MAP()


// AT9Dlg メッセージ ハンドラー

BOOL AT9Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD32 bitrate{}, sampling{}, encmode{}, chkLoop{}, chkWhole{}, chkLooppart{}, chkLooplist{}, chkAdvanced{}, chkDualenc{}, chkBand{}, chkSupenc{};
	wchar_t Cmd[MAX_PATH]{}, Loopstart[MAX_PATH]{}, Loopend[MAX_PATH]{}, Looppart[MAX_PATH]{}, Looplist[MAX_PATH]{}, Nbands[MAX_PATH]{}, Isband[MAX_PATH]{};
	bitrate = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x0001", INFINITE, L".\\settings.ini");
	sampling = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x0002", INFINITE, L".\\settings.ini");
	encmode = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x0100", INFINITE, L".\\settings.ini");
	chkLoop = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1000", INFINITE, L".\\settings.ini");
	chkWhole = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1001", INFINITE, L".\\settings.ini");
	chkLooppart = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1002", INFINITE, L".\\settings.ini");
	chkLooplist = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1003", INFINITE, L".\\settings.ini");
	chkAdvanced = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1100", INFINITE, L".\\settings.ini");
	chkDualenc = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1101", INFINITE, L".\\settings.ini");
	chkBand = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1102", INFINITE, L".\\settings.ini");
	chkSupenc = GetPrivateProfileInt(L"ATRAC9_ENCODE_SETTINGS", L"0x1103", INFINITE, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2000", NULL, (LPWSTR)Loopstart, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2001", NULL, (LPWSTR)Loopend, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2002", NULL, (LPWSTR)Looppart, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2003", NULL, (LPWSTR)Looplist, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2100", NULL, (LPWSTR)Nbands, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2101", NULL, (LPWSTR)Isband, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0000", NULL, (LPWSTR)Cmd, MAX_PATH, L".\\settings.ini");

	m_hBitrate.AddString(_T("36"));
	m_hBitrate.AddString(_T("48"));
	m_hBitrate.AddString(_T("60"));
	m_hBitrate.AddString(_T("72"));
	m_hBitrate.AddString(_T("84"));
	m_hBitrate.AddString(_T("96"));
	m_hBitrate.AddString(_T("120"));
	m_hBitrate.AddString(_T("144"));
	m_hBitrate.AddString(_T("168"));

	switch (bitrate)
	{
	case 0:
		BITRATE = _T(" -br 36");
		m_hBitrate.SetCurSel(0);
		break;
	case 1:
		BITRATE = _T(" -br 48");
		m_hBitrate.SetCurSel(1);
		break;
	case 2:
		BITRATE = _T(" -br 60");
		m_hBitrate.SetCurSel(2);
		break;
	case 3:
		BITRATE = _T(" -br 72");
		m_hBitrate.SetCurSel(3);
		break;
	case 4:
		BITRATE = _T(" -br 84");
		m_hBitrate.SetCurSel(4);
		break;
	case 5:
		BITRATE = _T(" -br 96");
		m_hBitrate.SetCurSel(5);
		break;
	case 6:
		BITRATE = _T(" -br 120");
		m_hBitrate.SetCurSel(6);
		break;
	case 7:
		BITRATE = _T(" -br 144");
		m_hBitrate.SetCurSel(7);
		break;
	case 8:
		BITRATE = _T(" -br 168");
		m_hBitrate.SetCurSel(8);
		break;
	default:
		BITRATE = _T(" -br 168");
		m_hBitrate.SetCurSel(8);
		break;
	}

	m_hSampling.AddString(_T("12000"));
	m_hSampling.AddString(_T("24000"));
	m_hSampling.AddString(_T("48000"));

	switch (sampling)
	{
	case 0:
		SAMPLING = _T(" -fs 12000");
		m_hSampling.SetCurSel(0);
		break;
	case 1:
		SAMPLING = _T(" -fs 24000");
		m_hSampling.SetCurSel(1);
		break;
	case 2:
		SAMPLING = _T(" -fs 48000");
		m_hSampling.SetCurSel(2);
		break;
	default:
		SAMPLING = _T(" -fs 48000");
		m_hSampling.SetCurSel(2);
		break;
	}

	CButton* CHECK_LOOPPOINT = (CButton*)GetDlgItem(IDC_CHECK_LOOPPOINT);
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CButton* CHECK_WHOLELOOP = (CButton*)GetDlgItem(IDC_CHECK_WHOLELOOP);
	CButton* CHECK_LOOPLIST = (CButton*)GetDlgItem(IDC_CHECK_LOOPLIST);
	CButton* CHECK_ADVANCED = (CButton*)GetDlgItem(IDC_CHECK_ADVANCED);
	CButton* CHECK_DUALENC = (CButton*)GetDlgItem(IDC_CHECK_DUALENC);
	CButton* CHECK_NBAND = (CButton*)GetDlgItem(IDC_CHECK_BAND);
	CButton* BUTTON_LOOPLIST = (CButton*)GetDlgItem(IDC_BUTTON_OPENLIST);
	CButton* RADIO_SUPENCON = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_ON);
	CButton* RADIO_SUPENCOFF = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_OFF);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_PARTLOOP);
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);
	CEdit* EDIT_LOOPLIST = (CEdit*)GetDlgItem(IDC_EDIT_LOOPLIST);
	CEdit* EDIT_NBANDS = (CEdit*)GetDlgItem(IDC_EDIT_NBANDS);
	CEdit* EDIT_ISBAND = (CEdit*)GetDlgItem(IDC_EDIT_ISBAND);
	CComboBox* COMBO_ENCMODE = (CComboBox*)GetDlgItem(IDC_COMBO_ENCMODE);
	
	switch (chkLoop)
	{
	case 0:
		CHECK_LOOPPOINT->SetCheck(BST_UNCHECKED);
		EDIT_LOOPSTART->SetWindowText(NULL);
		EDIT_LOOPEND->SetWindowText(NULL);
		EDIT_LOOPSTART->EnableWindow(FALSE);
		EDIT_LOOPEND->EnableWindow(FALSE);
		LOOPFLAG = _T("");
		LOOPSTART = _T("");
		LOOPEND = _T("");
		break;
	case 1:
		CHECK_LOOPPOINT->SetCheck(BST_CHECKED);
		LOOPFLAG = _T(" -loop");
		LOOPSTART = _T(" ");
		LOOPSTART += Loopstart;
		LOOPSTART += _T(" ");
		LOOPEND = Loopend;
		EDIT_LOOPSTART->SetWindowText(Loopstart);
		EDIT_LOOPEND->SetWindowText(Loopend);
		EDIT_LOOPSTART->EnableWindow(TRUE);
		EDIT_LOOPEND->EnableWindow(TRUE);
		break;
	default:
		CHECK_LOOPPOINT->SetCheck(BST_UNCHECKED);
		EDIT_LOOPSTART->SetWindowText(NULL);
		EDIT_LOOPEND->SetWindowText(NULL);
		EDIT_LOOPSTART->EnableWindow(FALSE);
		EDIT_LOOPEND->EnableWindow(FALSE);
		LOOPFLAG = _T("");
		LOOPSTART = _T("");
		LOOPEND = _T("");
		break;
	}

	switch (chkWhole)
	{
	case 0:
		CHECK_WHOLELOOP->SetCheck(BST_UNCHECKED);
		WHOLELOOPFLAG = _T("");
		break;
	case 1:
		CHECK_WHOLELOOP->SetCheck(BST_CHECKED);
		WHOLELOOPFLAG = _T(" -wholeloop");
		break;
	default:
		CHECK_WHOLELOOP->SetCheck(BST_UNCHECKED);
		WHOLELOOPFLAG = _T("");
		break;
	}

	switch (chkLooppart)
	{
	case 0:
		CHECK_PARTLOOP->SetCheck(BST_UNCHECKED);
		EDIT_LOOPPART->SetWindowText(NULL);
		EDIT_LOOPPART->EnableWindow(FALSE);
		LOOPPARTFLAG = _T("");
		LOOPPART = _T("");
		break;
	case 1:
		CHECK_PARTLOOP->SetCheck(BST_CHECKED);
		LOOPPARTFLAG = _T(" -repeat");
		LOOPPART = _T(" ");
		LOOPPART += Looppart;
		EDIT_LOOPPART->SetWindowText(Looppart);
		EDIT_LOOPPART->EnableWindow(TRUE);
		break;
	default:
		CHECK_PARTLOOP->SetCheck(BST_UNCHECKED);
		EDIT_LOOPPART->SetWindowText(NULL);
		EDIT_LOOPPART->EnableWindow(FALSE);
		LOOPPARTFLAG = _T("");
		LOOPPART = _T("");
		break;
	}

	switch (chkLooplist)
	{
	case 0:
		CHECK_LOOPLIST->SetCheck(BST_UNCHECKED);
		EDIT_LOOPLIST->SetWindowText(NULL);
		EDIT_LOOPLIST->EnableWindow(FALSE);
		BUTTON_LOOPLIST->EnableWindow(FALSE);
		LOOPLISTFLAG = _T("");
		LOOPLIST = _T("");
		break;
	case 1:
		CHECK_LOOPLIST->SetCheck(BST_CHECKED);
		LOOPLISTFLAG = _T(" -looplist");
		LOOPLIST = _T(" ");
		LOOPLIST += Looplist;
		EDIT_LOOPLIST->SetWindowText(Looplist);
		EDIT_LOOPLIST->EnableWindow(TRUE);
		BUTTON_LOOPLIST->EnableWindow(TRUE);
		break;
	default:
		CHECK_LOOPLIST->SetCheck(BST_UNCHECKED);
		EDIT_LOOPLIST->SetWindowText(NULL);
		EDIT_LOOPLIST->EnableWindow(FALSE);
		BUTTON_LOOPLIST->EnableWindow(FALSE);
		LOOPLISTFLAG = _T("");
		LOOPLIST = _T("");
		break;
	}

	switch (chkAdvanced)
	{
	case 0:
		CHECK_ADVANCED->SetCheck(BST_UNCHECKED);
		RADIO_SUPENCON->EnableWindow(FALSE);
		RADIO_SUPENCOFF->EnableWindow(FALSE);
		CHECK_DUALENC->EnableWindow(FALSE);
		CHECK_NBAND->EnableWindow(FALSE);
		EDIT_NBANDS->SetWindowText(NULL);
		EDIT_ISBAND->SetWindowText(NULL);
		EDIT_NBANDS->EnableWindow(FALSE);
		EDIT_ISBAND->EnableWindow(FALSE);
		COMBO_ENCMODE->EnableWindow(FALSE);
		break;
	case 1:
		CHECK_ADVANCED->SetCheck(BST_CHECKED);
		RADIO_SUPENCON->EnableWindow(TRUE);
		RADIO_SUPENCOFF->EnableWindow(TRUE);
		CHECK_DUALENC->EnableWindow(TRUE);
		CHECK_NBAND->EnableWindow(TRUE);
		COMBO_ENCMODE->EnableWindow(TRUE);
		break;
	default:
		CHECK_ADVANCED->SetCheck(BST_UNCHECKED);
		RADIO_SUPENCON->EnableWindow(FALSE);
		RADIO_SUPENCOFF->EnableWindow(FALSE);
		CHECK_DUALENC->EnableWindow(FALSE);
		CHECK_NBAND->EnableWindow(FALSE);
		EDIT_NBANDS->SetWindowText(NULL);
		EDIT_ISBAND->SetWindowText(NULL);
		EDIT_NBANDS->EnableWindow(FALSE);
		EDIT_ISBAND->EnableWindow(FALSE);
		COMBO_ENCMODE->EnableWindow(FALSE);
		break;
	}

	switch (chkSupenc)
	{
	case 0:
		CheckRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF, IDC_RADIO_SUPFRAME_OFF);
		SUPFRAMEFLAG = _T(" -supframeoff");
		break;
	case 1:
		CheckRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF, IDC_RADIO_SUPFRAME_ON);
		SUPFRAMEFLAG = _T(" -supframeon");
		break;
	default:
		CheckRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF, IDC_RADIO_SUPFRAME_OFF);
		SUPFRAMEFLAG = _T("");
		break;
	}

	switch (chkDualenc)
	{
	case 0:
		CHECK_DUALENC->SetCheck(BST_UNCHECKED);
		DUALFLAG = _T("");
		break;
	case 1:
		CHECK_DUALENC->SetCheck(BST_CHECKED);
		DUALFLAG = _T(" -dual");
		break;
	default:
		CHECK_DUALENC->SetCheck(BST_UNCHECKED);
		DUALFLAG = _T("");
		break;
	}

	switch (chkBand)
	{
	case 0:
		CHECK_NBAND->SetCheck(BST_UNCHECKED);
		EDIT_NBANDS->SetWindowText(NULL);
		EDIT_ISBAND->SetWindowText(NULL);
		EDIT_NBANDS->EnableWindow(FALSE);
		EDIT_ISBAND->EnableWindow(FALSE);
		NBANDSFLAG = _T("");
		NBANDS = _T("");
		ISBANDFLAG = _T("");
		ISBAND = _T("");
		break;
	case 1:
		CHECK_NBAND->SetCheck(BST_CHECKED);
		NBANDSFLAG = _T(" -nbands");
		NBANDS = _T(" ");
		NBANDS += Nbands;
		ISBANDFLAG = _T(" -isband");
		ISBAND = _T(" ");
		ISBAND += Isband;
		EDIT_NBANDS->SetWindowText(Nbands);
		EDIT_ISBAND->SetWindowText(Isband);
		EDIT_NBANDS->EnableWindow(TRUE);
		EDIT_ISBAND->EnableWindow(TRUE);
		break;
	default:
		CHECK_NBAND->SetCheck(BST_UNCHECKED);
		EDIT_NBANDS->SetWindowText(NULL);
		EDIT_ISBAND->SetWindowText(NULL);
		EDIT_NBANDS->EnableWindow(FALSE);
		EDIT_ISBAND->EnableWindow(FALSE);
		NBANDSFLAG = _T("");
		NBANDS = _T("");
		ISBANDFLAG = _T("");
		ISBAND = _T("");
		break;
	}

	switch (encmode)
	{
	case 0:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(0);
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 0");
		break;
	case 1:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(1);
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 1");
		break;
	case 2:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(2);
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 2");
		break;
	case 3:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(3);
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 3");
		break;
	case 4:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(4);
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 4");
		break;
	case 5:
		m_hEncodeMode.AddString(_T("0"));
		m_hEncodeMode.AddString(_T("1"));
		m_hEncodeMode.AddString(_T("2"));
		m_hEncodeMode.AddString(_T("3"));
		m_hEncodeMode.AddString(_T("4"));
		m_hEncodeMode.AddString(_T("無効"));
		m_hEncodeMode.SetCurSel(5);
		GRADMODEFLAG = _T("");
		GRADMODE = _T("");
		break;
	default:
		m_hEncodeMode.ResetContent();
		m_hEncodeMode.SetCurSel(0);
		GRADMODEFLAG = _T("");
		GRADMODE = _T("");
		break;
	}

	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);

	if (Cmd == NULL) {
		EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
		UpdateData(FALSE);
	}
	else {
		EDIT_PARAM->SetWindowText(CMDPARAM = Cmd);
		UpdateData(FALSE);
	}

	return TRUE;
}

void AT9Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_LOOPPOINT = (CButton*)GetDlgItem(IDC_CHECK_LOOPPOINT);
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CButton* CHECK_WHOLELOOP = (CButton*)GetDlgItem(IDC_CHECK_WHOLELOOP);
	CButton* CHECK_LOOPLIST = (CButton*)GetDlgItem(IDC_CHECK_LOOPLIST);
	CButton* CHECK_ADVANCED = (CButton*)GetDlgItem(IDC_CHECK_ADVANCED);
	CButton* CHECK_DUALENC = (CButton*)GetDlgItem(IDC_CHECK_DUALENC);
	CButton* CHECK_NBAND = (CButton*)GetDlgItem(IDC_CHECK_BAND);
	CButton* BUTTON_LOOPLIST = (CButton*)GetDlgItem(IDC_BUTTON_OPENLIST);
	CButton* RADIO_SUPENCON = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_ON);
	CButton* RADIO_SUPENCOFF = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_OFF);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_PARTLOOP);
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);
	CEdit* EDIT_LOOPLIST = (CEdit*)GetDlgItem(IDC_EDIT_LOOPLIST);
	CEdit* EDIT_NBANDS = (CEdit*)GetDlgItem(IDC_EDIT_NBANDS);
	CEdit* EDIT_ISBAND = (CEdit*)GetDlgItem(IDC_EDIT_ISBAND);
	CComboBox* COMBO_ENCMODE = (CComboBox*)GetDlgItem(IDC_COMBO_ENCMODE);

	CString COMBO_BITRATE_index, COMBO_SAMPLING_index, COMBO_ENCMODE_index;
	int RADIO_SUP_INDEX{};
	int index1 = m_hBitrate.GetCurSel(), index2 = m_hSampling.GetCurSel(), index3 = m_hEncodeMode.GetCurSel();
	COMBO_BITRATE_index.Format(_T("%d"), index1);
	COMBO_SAMPLING_index.Format(_T("%d"), index2);
	COMBO_ENCMODE_index.Format(_T("%d"), index3);

	RADIO_SUP_INDEX = GetCheckedRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF);

	if (CHECK_LOOPPOINT->GetCheck() == BST_CHECKED) {
		if (EDIT_LOOPSTART->GetWindowTextLength() < 1) {
			MessageBox(_T("LoopStartのサンプル値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
		if (EDIT_LOOPEND->GetWindowTextLength() < 1) {
			MessageBox(_T("LoopEndのサンプル値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}

	if (CHECK_PARTLOOP->GetCheck() == BST_CHECKED) {
		if (EDIT_LOOPPART->GetWindowTextLength() == 0) {
			MessageBox(_T("LoopPartの回数値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}

	if (CHECK_LOOPLIST->GetCheck() == BST_CHECKED) {
		if (EDIT_LOOPLIST->GetWindowTextLength() == 0) {
			MessageBox(_T("リストファイルが参照されていません。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}

	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		if (CHECK_NBAND->GetCheck() == BST_CHECKED) {
			if (EDIT_NBANDS->GetWindowTextLength() == 0) {
				MessageBox(_T("量子化バンド数の値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
				return;
			}
			if (EDIT_ISBAND->GetWindowTextLength() == 0) {
				MessageBox(_T("バンド強度の値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
				return;
			}
		}
	}

	CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile");

	if (!CMDPARAM) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0000", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0000", CMDPARAM, L".\\settings.ini");
	}

	if (m_hBitrate.GetCurSel() != CB_ERR) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0001", COMBO_BITRATE_index, L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0001", L"", L".\\settings.ini");
	}
	if (m_hSampling.GetCurSel() != CB_ERR) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0002", COMBO_SAMPLING_index, L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0002", L"", L".\\settings.ini");
	}
	if (m_hEncodeMode.GetCurSel() != CB_ERR) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0100", COMBO_ENCMODE_index, L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0100", L"", L".\\settings.ini");
	}

	if (CHECK_LOOPPOINT->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1000", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1000", L"0", L".\\settings.ini");
	}

	if (CHECK_WHOLELOOP->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1001", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1001", L"0", L".\\settings.ini");
	}
	if (CHECK_PARTLOOP->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1002", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1002", L"0", L".\\settings.ini");
	}
	if (CHECK_LOOPLIST->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1003", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1003", L"0", L".\\settings.ini");
	}
	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1100", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1100", L"0", L".\\settings.ini");
	}
	if (CHECK_DUALENC->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1101", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1101", L"0", L".\\settings.ini");
	}
	if (CHECK_NBAND->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1102", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1102", L"0", L".\\settings.ini");
	}
	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		if (RADIO_SUP_INDEX == 1031) {
			WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1103", L"1", L".\\settings.ini");
		}
		else if (RADIO_SUP_INDEX == 1032) {
			WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1103", L"0", L".\\settings.ini");
		}
		else {
			WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1103", L"", L".\\settings.ini");
		}
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x1103", L"", L".\\settings.ini");
	}
	


	if (EDIT_LOOPSTART->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2000", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2000", m_hLoopStart, L".\\settings.ini");
	}
	if (EDIT_LOOPEND->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2001", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2001", m_hLoopEnd, L".\\settings.ini");
	}
	if (EDIT_LOOPPART->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2002", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2002", m_hLoopPart, L".\\settings.ini");
	}
	if (EDIT_LOOPLIST->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2003", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2003", m_hLoopList, L".\\settings.ini");
	}
	if (EDIT_NBANDS->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2100", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2100", m_hNbands, L".\\settings.ini");
	}
	if (EDIT_ISBAND->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2101", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x2101", m_hIsband, L".\\settings.ini");
	}

	CDialogEx::OnOK();
}


void AT9Dlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}


void AT9Dlg::OnCbnSelchangeComboBitrate()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	switch (m_hBitrate.GetCurSel())
	{
	case 0:
		BITRATE = _T(" -br 36");
		break;
	case 1:
		BITRATE = _T(" -br 48");
		break;
	case 2:
		BITRATE = _T(" -br 60");
		break;
	case 3:
		BITRATE = _T(" -br 72");
		break;
	case 4:
		BITRATE = _T(" -br 84");
		break;
	case 5:
		BITRATE = _T(" -br 96");
		break;
	case 6:
		BITRATE = _T(" -br 120");
		break;
	case 7:
		BITRATE = _T(" -br 144");
		break;
	case 8:
		BITRATE = _T(" -br 168");
		break;
	default:
		BITRATE = _T("");
		break;
	}

	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnCbnSelchangeComboSampling()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (m_hSampling.GetCurSel() == 0) { // 12000Hz
		SAMPLING = _T(" -fs 12000");
	}
	else if (m_hSampling.GetCurSel() == 1) { // 24000Hz
		SAMPLING = _T(" -fs 24000");
	}
	else if (m_hSampling.GetCurSel() == 2) { // 48000Hz
		SAMPLING = _T(" -fs 48000");
	}
	else { // Error
		SAMPLING = _T("");
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckLooppoint()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_LOOPPOINT = (CButton*)GetDlgItem(IDC_CHECK_LOOPPOINT);
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);

	if (CHECK_LOOPPOINT->GetCheck() == BST_CHECKED) {
		LOOPFLAG = _T(" -loop");
		EDIT_LOOPSTART->EnableWindow(TRUE);
		EDIT_LOOPEND->EnableWindow(TRUE);
	}
	else {
		if (EDIT_LOOPSTART->GetWindowTextLength() != 0) {
			EDIT_LOOPSTART->SetWindowText(NULL);
		}
		if (EDIT_LOOPEND->GetWindowTextLength() != 0) {
			EDIT_LOOPEND->SetWindowText(NULL);
		}
		LOOPFLAG = _T("");
		EDIT_LOOPSTART->EnableWindow(FALSE);
		EDIT_LOOPEND->EnableWindow(FALSE);
		OutputDebugString(_T("Loop point check disabled.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditLoopstart()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);

	if (EDIT_LOOPSTART->GetWindowTextLength() == 0) {
		LOOPSTART = L"";
		OutputDebugString(_T("LoopStart Length: null \n"));
	}
	else if (EDIT_LOOPSTART->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPSTART = _T(" ");
		LOOPSTART += m_hLoopStart;
		LOOPSTART += _T(" ");
		OutputDebugString(_T("LoopStart Length:") + LOOPSTART + _T("Samples.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditLoopend()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);

	if (EDIT_LOOPEND->GetWindowTextLength() == 0) {
		LOOPEND = L"";
		OutputDebugString(_T("LoopEnd Length: null \n"));
	}
	else if (EDIT_LOOPEND->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPEND = m_hLoopEnd;
		OutputDebugString(_T("LoopEnd Length: ") + LOOPEND + _T(" Samples.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckWholeloop()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_WHOLELOOP = (CButton*)GetDlgItem(IDC_CHECK_WHOLELOOP);

	if (CHECK_WHOLELOOP->GetCheck() == BST_CHECKED) {
		WHOLELOOPFLAG = _T(" -wholeloop");
		CHECK_WHOLELOOP->SetCheck(BST_CHECKED);
		OutputDebugString(_T("Whole loop check enabled.\n"));
	}
	else {
		WHOLELOOPFLAG = _T("");
		CHECK_WHOLELOOP->SetCheck(BST_UNCHECKED);
		OutputDebugString(_T("Whole loop check disabled.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckPartloop()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_PARTLOOP);

	if (CHECK_PARTLOOP->GetCheck() == BST_CHECKED) {
		LOOPPARTFLAG = _T(" -repeat");
		CHECK_PARTLOOP->SetCheck(BST_CHECKED);
		EDIT_LOOPPART->EnableWindow(TRUE);
	}
	else {
		if (EDIT_LOOPPART->GetWindowTextLength() != 0) {
			EDIT_LOOPPART->SetWindowText(NULL);
		}
		LOOPPARTFLAG = _T("");
		CHECK_PARTLOOP->SetCheck(BST_UNCHECKED);
		EDIT_LOOPPART->EnableWindow(FALSE);
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditPartloop()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_PARTLOOP);

	if (EDIT_LOOPPART->GetWindowTextLength() == 0) {
		LOOPPART = L"";
		OutputDebugString(_T("Repeating loop part: null \n"));
	}
	else if (EDIT_LOOPPART->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPPART = _T(" ");
		LOOPPART += m_hLoopPart;
		OutputDebugString(_T("Repeating loop part:") + LOOPPART + _T(" times.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckLooplist()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_LOOPLIST = (CButton*)GetDlgItem(IDC_CHECK_LOOPLIST);
	CButton* BUTTON_LOOPLIST = (CButton*)GetDlgItem(IDC_BUTTON_OPENLIST);
	CEdit* EDIT_LOOPLIST = (CEdit*)GetDlgItem(IDC_EDIT_LOOPLIST);

	if (CHECK_LOOPLIST->GetCheck() == BST_CHECKED) {
		LOOPLISTFLAG = _T(" -looplist");
		EDIT_LOOPLIST->EnableWindow(TRUE);
		BUTTON_LOOPLIST->EnableWindow(TRUE);
	}
	else {
		if (EDIT_LOOPLIST->GetWindowTextLength() != 0) {
			EDIT_LOOPLIST->SetWindowText(NULL);
			LOOPLIST = _T("");
		}
		LOOPLISTFLAG = _T("");
		EDIT_LOOPLIST->EnableWindow(FALSE);
		BUTTON_LOOPLIST->EnableWindow(FALSE);
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditLooplist()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
}


void AT9Dlg::OnBnClickedButtonOpenlist()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CEdit* EDIT_LOOPLIST = (CEdit*)GetDlgItem(IDC_EDIT_LOOPLIST);
	PROCDlg* PROCDLG = new PROCDlg;

	CString FILE;
	CString filter("テキストファイル (*.txt)|*.txt||");
	CFileDialog selDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter);
	INT_PTR ret = selDlg.DoModal();
	if (ret == IDOK) {
		PROCDLG->Create(IDD_PROCESS_DLG);
		PROCDLG->ShowWindow(SW_SHOW);
		FILE = selDlg.GetPathName();
		EDIT_LOOPLIST->SetWindowText(FILE);
		LOOPLIST = _T(" ");
		LOOPLIST += FILE;
		PROCDLG->DestroyWindow();
		delete PROCDLG;
	}
	else {
		PROCDLG->Create(IDD_PROCESS_DLG);
		PROCDLG->ShowWindow(SW_SHOW);
		EDIT_LOOPLIST->SetWindowText(NULL);
		LOOPLIST = _T("");
		PROCDLG->DestroyWindow();
		delete PROCDLG;
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckAdvanced()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_ADVANCED = (CButton*)GetDlgItem(IDC_CHECK_ADVANCED);
	CButton* CHECK_DUALENC = (CButton*)GetDlgItem(IDC_CHECK_DUALENC);
	CButton* CHECK_NBAND = (CButton*)GetDlgItem(IDC_CHECK_BAND);
	CButton* RADIO_SUPENCON = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_ON);
	CButton* RADIO_SUPENCOFF = (CButton*)GetDlgItem(IDC_RADIO_SUPFRAME_OFF);
	CEdit* EDIT_NBANDS = (CEdit*)GetDlgItem(IDC_EDIT_NBANDS);
	CEdit* EDIT_ISBAND = (CEdit*)GetDlgItem(IDC_EDIT_ISBAND);
	CComboBox* COMBO_ENCMODE = (CComboBox*)GetDlgItem(IDC_COMBO_ENCMODE);

	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		INT_PTR ret = MessageBox(_T("この項目は上級者向け設定です。\n無闇に変更すると変換に支障をきたす可能性があります。\n有効にしますか？"), _T("警告"), MB_ICONWARNING | MB_YESNO);
		if (ret == IDYES) {
			m_hEncodeMode.AddString(_T("0"));
			m_hEncodeMode.AddString(_T("1"));
			m_hEncodeMode.AddString(_T("2"));
			m_hEncodeMode.AddString(_T("3"));
			m_hEncodeMode.AddString(_T("4"));
			m_hEncodeMode.AddString(_T("無効"));
			m_hEncodeMode.SetCurSel(5);
			CheckRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF, IDC_RADIO_SUPFRAME_ON);
			SUPFRAMEFLAG = _T(" -supframeon");
			CHECK_ADVANCED->SetCheck(BST_CHECKED);
			CHECK_DUALENC->EnableWindow(TRUE);
			CHECK_NBAND->EnableWindow(TRUE);
			RADIO_SUPENCON->EnableWindow(TRUE);
			RADIO_SUPENCOFF->EnableWindow(TRUE);
			COMBO_ENCMODE->EnableWindow(TRUE);
			CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
			EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
			return;
		}
		else if (ret == IDNO) {
			m_hEncodeMode.ResetContent();
			CHECK_ADVANCED->SetCheck(BST_UNCHECKED);
			CHECK_DUALENC->SetCheck(BST_UNCHECKED);
			CHECK_NBAND->SetCheck(BST_UNCHECKED);
			CHECK_DUALENC->EnableWindow(FALSE);
			CHECK_NBAND->EnableWindow(FALSE);
			RADIO_SUPENCON->EnableWindow(FALSE);
			RADIO_SUPENCOFF->EnableWindow(FALSE);
			COMBO_ENCMODE->EnableWindow(FALSE);
			CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
			EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
			return;
		}
		else {
			m_hEncodeMode.ResetContent();
			CHECK_ADVANCED->SetCheck(BST_UNCHECKED);
			CHECK_DUALENC->SetCheck(BST_UNCHECKED);
			CHECK_NBAND->SetCheck(BST_UNCHECKED);
			CHECK_DUALENC->EnableWindow(FALSE);
			CHECK_NBAND->EnableWindow(FALSE);
			RADIO_SUPENCON->EnableWindow(FALSE);
			RADIO_SUPENCOFF->EnableWindow(FALSE);
			COMBO_ENCMODE->EnableWindow(FALSE);
			CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
			EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
			return;
		}
		return;
	}
	else {
		if (EDIT_NBANDS->GetWindowTextLength() != 0) {
			EDIT_NBANDS->SetWindowText(NULL);
			EDIT_NBANDS->EnableWindow(FALSE);
			NBANDS = _T("");
		}
		if (EDIT_ISBAND->GetWindowTextLength() != 0) {
			EDIT_ISBAND->SetWindowText(NULL);
			EDIT_ISBAND->EnableWindow(FALSE);
			ISBAND = _T("");
		}
		if (CHECK_DUALENC->GetCheck() == BST_CHECKED) {
			DUALFLAG = _T("");
			CHECK_DUALENC->SetCheck(BST_UNCHECKED);
		}
		if (CHECK_NBAND->GetCheck() == BST_CHECKED) {
			NBANDSFLAG = _T("");
			CHECK_NBAND->SetCheck(BST_UNCHECKED);
		}
		if (m_hEncodeMode.GetCurSel() != CB_ERR) {
			GRADMODEFLAG = _T("");
			GRADMODE = _T("");
		}
		CheckRadioButton(IDC_RADIO_SUPFRAME_ON, IDC_RADIO_SUPFRAME_OFF, IDC_RADIO_SUPFRAME_ON);
		SUPFRAMEFLAG = _T("");
		m_hEncodeMode.ResetContent();
		CHECK_ADVANCED->SetCheck(BST_UNCHECKED);
		CHECK_DUALENC->EnableWindow(FALSE);
		CHECK_NBAND->EnableWindow(FALSE);
		RADIO_SUPENCON->EnableWindow(FALSE);
		RADIO_SUPENCOFF->EnableWindow(FALSE);
		COMBO_ENCMODE->EnableWindow(FALSE);
		CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
		EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
		return;
	}
}


void AT9Dlg::OnBnClickedCheckDualenc()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_DUALENC = (CButton*)GetDlgItem(IDC_CHECK_DUALENC);

	if (CHECK_DUALENC->GetCheck() == BST_CHECKED) {
		DUALFLAG = _T(" -dual");
	}
	else {
		DUALFLAG = _T("");
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedCheckBand()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_NBAND = (CButton*)GetDlgItem(IDC_CHECK_BAND);
	CEdit* EDIT_NBANDS = (CEdit*)GetDlgItem(IDC_EDIT_NBANDS);
	CEdit* EDIT_ISBAND = (CEdit*)GetDlgItem(IDC_EDIT_ISBAND);

	if (CHECK_NBAND->GetCheck() == BST_CHECKED) {
		NBANDSFLAG = _T(" -nbands");
		EDIT_NBANDS->EnableWindow(TRUE);
		EDIT_ISBAND->EnableWindow(TRUE);
	}
	else {
		NBANDSFLAG = _T("");
		if (EDIT_NBANDS->GetWindowTextLength() != 0) {
			EDIT_NBANDS->SetWindowText(NULL);
		}
		if (EDIT_ISBAND->GetWindowTextLength() != 0) {
			EDIT_ISBAND->SetWindowText(NULL);
		}
		EDIT_NBANDS->EnableWindow(FALSE);
		EDIT_ISBAND->EnableWindow(FALSE);
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditNbands()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_NBANDS = (CEdit*)GetDlgItem(IDC_EDIT_NBANDS);

	if (EDIT_NBANDS->GetWindowTextLength() == 0) {
		NBANDS = _T("");
		OutputDebugString(_T("Number of quantized bands: null \n"));
	}
	else if (EDIT_NBANDS->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		NBANDS = _T(" ");
		NBANDS += m_hNbands;
		OutputDebugString(_T("Number of quantized bands:") + NBANDS + _T(".\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnEnChangeEditIsband()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_ISBAND = (CEdit*)GetDlgItem(IDC_EDIT_ISBAND);

	if (EDIT_ISBAND->GetWindowTextLength() == 0) {
		ISBAND = _T("");
		ISBANDFLAG = _T("");
		OutputDebugString(_T("Intensity start band: null \n"));
	}
	else if (EDIT_ISBAND->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		ISBAND = _T(" ");
		ISBAND += m_hIsband;
		ISBANDFLAG = _T(" -isband");
		OutputDebugString(_T("Intensity start band:") + ISBAND + _T(".\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnCbnSelchangeComboEncmode()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	switch (m_hEncodeMode.GetCurSel())
	{
	case 0:
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 0");
		OutputDebugString(_T("Encoding mode is: 0.\ngradient of the quantization noise.\n"));
		break;
	case 1:
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 1");
		OutputDebugString(_T("Encoding mode is: 1.\ngradient of the quantization noise.\n"));
		break;
	case 2:
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 2");
		OutputDebugString(_T("Encoding mode is: 2.\ngradient of the quantization noise.\n"));
		break;
	case 3:
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 3");
		OutputDebugString(_T("Encoding mode is: 3.\ngradient of the quantization noise.\n"));
		break;
	case 4:
		GRADMODEFLAG = _T(" -gradmode");
		GRADMODE = _T(" 4");
		OutputDebugString(_T("Encoding mode is: 4.\n0-3 is selected automatically.\nSpecify the small number in case of tone sound source.\nOr specify the high number in case of noisy sound source.\n"));
		break;
	case 5:
		GRADMODEFLAG = _T("");
		GRADMODE = _T("");
		break;
	default:
		GRADMODEFLAG = _T("");
		GRADMODE = _T("");
		break;
	}

	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedRadioSupframeOn()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_ADVANCED = (CButton*)GetDlgItem(IDC_CHECK_ADVANCED);

	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		SUPFRAMEFLAG = _T(" -supframeon");
	}
	else {
		SUPFRAMEFLAG = _T("");
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}


void AT9Dlg::OnBnClickedRadioSupframeOff()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_ADVANCED = (CButton*)GetDlgItem(IDC_CHECK_ADVANCED);

	if (CHECK_ADVANCED->GetCheck() == BST_CHECKED) {
		SUPFRAMEFLAG = _T(" -supframeoff");
	}
	else {
		SUPFRAMEFLAG = _T("");
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT_CMD);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + SAMPLING + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + LOOPLISTFLAG + LOOPLIST + SUPFRAMEFLAG + DUALFLAG + NBANDSFLAG + NBANDS + ISBANDFLAG + ISBAND + GRADMODEFLAG + GRADMODE + _T(" $InFile $OutFile"));
	return;
}
