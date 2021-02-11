// AT3Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "ATRACTool.h"
#include "AT3Dlg.h"
#include "afxdialogex.h"


// AT3Dlg ダイアログ

IMPLEMENT_DYNAMIC(AT3Dlg, CDialogEx)

AT3Dlg::AT3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AT3SETTINGS_DLG, pParent)
	, m_hLoopStartLength(_T(""))
	, m_hLoopEndLength(_T(""))
	, m_hLoopPart(_T(""))
{

}

AT3Dlg::~AT3Dlg()
{
}

void AT3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_CH1, m_hRADIOCHANNEL);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_hBitrate);
	DDX_Text(pDX, IDC_EDIT_LOOPSTART, m_hLoopStartLength);
	DDV_MaxChars(pDX, m_hLoopStartLength, 11);
	DDX_Text(pDX, IDC_EDIT_LOOPEND, m_hLoopEndLength);
	DDV_MaxChars(pDX, m_hLoopEndLength, 11);
	DDX_Text(pDX, IDC_EDIT_LOOPPART, m_hLoopPart);
	DDV_MaxChars(pDX, m_hLoopPart, 3);
}


BEGIN_MESSAGE_MAP(AT3Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AT3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AT3Dlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_BITRATE, &AT3Dlg::OnCbnSelchangeComboBitrate)
	ON_EN_CHANGE(IDC_EDIT_LOOPSTART, &AT3Dlg::OnEnChangeEditLoopstart)
	ON_EN_CHANGE(IDC_EDIT_LOOPEND, &AT3Dlg::OnEnChangeEditLoopend)
	ON_BN_CLICKED(IDC_CHECK_LOOPPOINT, &AT3Dlg::OnBnClickedCheckLooppoint)
	ON_BN_CLICKED(IDC_CHECK_WHOLELOOP, &AT3Dlg::OnBnClickedCheckWholeloop)
	ON_EN_CHANGE(IDC_EDIT_LOOPPART, &AT3Dlg::OnEnChangeEditLooppart)
	ON_BN_CLICKED(IDC_CHECK_PARTLOOP, &AT3Dlg::OnBnClickedCheckPartloop)
END_MESSAGE_MAP()


// AT3Dlg メッセージ ハンドラー

BOOL AT3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD32 bitrate{}, loopcheck{}, wholeloopcheck{}, looppartcheck{};
	wchar_t Cmd[MAX_PATH]{}, Loopstart[MAX_PATH]{}, Loopend[MAX_PATH]{}, Looppart[MAX_PATH]{};
	bitrate = GetPrivateProfileInt(L"ATRAC3_ENCODE_SETTINGS", L"0x0001", INFINITE, L".\\settings.ini");
	loopcheck = GetPrivateProfileInt(L"ATRAC3_ENCODE_SETTINGS", L"0x1000", INFINITE, L".\\settings.ini");
	wholeloopcheck = GetPrivateProfileInt(L"ATRAC3_ENCODE_SETTINGS", L"0x1001", INFINITE, L".\\settings.ini");
	looppartcheck = GetPrivateProfileInt(L"ATRAC3_ENCODE_SETTINGS", L"0x1002", INFINITE, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2000", NULL, (LPWSTR)Loopstart, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2001", NULL, (LPWSTR)Loopend, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2002", NULL, (LPWSTR)Looppart, MAX_PATH, L".\\settings.ini");
	GetPrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0000", NULL, (LPWSTR)Cmd, MAX_PATH, L".\\settings.ini");

	m_hBitrate.AddString(_T("32"));
	m_hBitrate.AddString(_T("48"));
	m_hBitrate.AddString(_T("52"));
	m_hBitrate.AddString(_T("64"));
	m_hBitrate.AddString(_T("66"));
	m_hBitrate.AddString(_T("96"));
	m_hBitrate.AddString(_T("105"));
	m_hBitrate.AddString(_T("128"));
	m_hBitrate.AddString(_T("132"));
	m_hBitrate.AddString(_T("160"));
	m_hBitrate.AddString(_T("192"));
	m_hBitrate.AddString(_T("256"));
	m_hBitrate.AddString(_T("320"));
	m_hBitrate.AddString(_T("352"));

	CButton* RADIO1 = (CButton*)GetDlgItem(IDC_RADIO_CH1);
	CButton* RADIO2 = (CButton*)GetDlgItem(IDC_RADIO_CH2);

	if (bitrate == 0) {
		m_hBitrate.SetCurSel(0);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH1);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(FALSE);
		BITRATE = _T(" -br 32");
	}
	else if (bitrate == 1) {
		m_hBitrate.SetCurSel(1);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 48");
	}
	else if (bitrate == 2) {
		m_hBitrate.SetCurSel(2);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH1);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(FALSE);
		BITRATE = _T(" -br 52");
	}
	else if (bitrate == 3) {
		m_hBitrate.SetCurSel(3);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 64");
	}
	else if (bitrate == 4) {
		m_hBitrate.SetCurSel(4);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 66");
	}
	else if (bitrate == 5) {
		m_hBitrate.SetCurSel(5);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 96");
	}
	else if (bitrate == 6) {
		m_hBitrate.SetCurSel(6);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 105");
	}
	else if (bitrate == 7) {
		m_hBitrate.SetCurSel(7);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 128");
	}
	else if (bitrate == 8) {
		m_hBitrate.SetCurSel(8);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 132");
	}
	else if (bitrate == 9) {
		m_hBitrate.SetCurSel(9);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 160");
	}
	else if (bitrate == 10) {
		m_hBitrate.SetCurSel(10);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 192");
	}
	else if (bitrate == 11) {
		m_hBitrate.SetCurSel(11);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 256");
	}
	else if (bitrate == 12) {
		m_hBitrate.SetCurSel(12);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 320");
	}
	else if (bitrate == 13) {
		m_hBitrate.SetCurSel(13);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 352");
	}
	else {
		m_hBitrate.SetCurSel(11);
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 256");
	}

	CButton* CHECK_LOOPPOINT = (CButton*)GetDlgItem(IDC_CHECK_LOOPPOINT);
	CButton* CHECK_WHOLELOOP = (CButton*)GetDlgItem(IDC_CHECK_WHOLELOOP);
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPPART);
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);

	if (loopcheck == 0) {
		CHECK_LOOPPOINT->SetCheck(BST_UNCHECKED);
		LOOPFLAG = _T("");
		LOOPSTART = _T("");
		LOOPEND = _T("");
		EDIT_LOOPSTART->SetWindowText(NULL);
		EDIT_LOOPEND->SetWindowText(NULL);
		EDIT_LOOPSTART->EnableWindow(FALSE);
		EDIT_LOOPEND->EnableWindow(FALSE);
	}
	else if (loopcheck == 1) {
		CHECK_LOOPPOINT->SetCheck(BST_CHECKED);
		LOOPFLAG = _T(" -loop");
		LOOPSTART = _T(" ");
		LOOPSTART += Loopstart;
		LOOPSTART += _T(" ");
		LOOPEND = Loopend;
		EDIT_LOOPSTART->SetWindowText(Loopstart);
		EDIT_LOOPEND->SetWindowText(LOOPEND);
		EDIT_LOOPSTART->EnableWindow(TRUE);
		EDIT_LOOPEND->EnableWindow(TRUE);
	}
	else {
		CHECK_LOOPPOINT->SetCheck(BST_UNCHECKED);
		LOOPFLAG = _T("");
		LOOPSTART = _T("");
		LOOPEND = _T("");
		EDIT_LOOPSTART->SetWindowText(NULL);
		EDIT_LOOPEND->SetWindowText(NULL);
		EDIT_LOOPSTART->EnableWindow(FALSE);
		EDIT_LOOPEND->EnableWindow(FALSE);
	}

	if (wholeloopcheck == 0) {
		CHECK_WHOLELOOP->SetCheck(BST_UNCHECKED);
		WHOLELOOPFLAG = _T("");
	}
	else if (wholeloopcheck == 1) {
		CHECK_WHOLELOOP->SetCheck(BST_CHECKED);
		WHOLELOOPFLAG = _T(" -wholeloop");
	}
	else {
		CHECK_WHOLELOOP->SetCheck(BST_UNCHECKED);
		WHOLELOOPFLAG = _T("");
	}

	if (looppartcheck == 0) {
		CHECK_PARTLOOP->SetCheck(BST_UNCHECKED);
		EDIT_LOOPPART->SetWindowText(NULL);
		EDIT_LOOPPART->EnableWindow(FALSE);
		LOOPPARTFLAG = _T("");
		LOOPPART = _T("");
	}
	else if (looppartcheck == 1) {
		CHECK_PARTLOOP->SetCheck(BST_CHECKED);
		LOOPPARTFLAG = _T(" -repeat");
		LOOPPART = _T(" ");
		LOOPPART += Looppart;
		EDIT_LOOPPART->SetWindowText(Looppart);
		EDIT_LOOPPART->EnableWindow(TRUE);
	}
	else {
		CHECK_PARTLOOP->SetCheck(BST_UNCHECKED);
		EDIT_LOOPPART->SetWindowText(NULL);
		EDIT_LOOPPART->EnableWindow(FALSE);
		LOOPPARTFLAG = _T("");
		LOOPPART = _T("");
	}

	EDIT_PARAM->SetWindowText(CMDPARAM = Cmd);

	return TRUE;
}


void AT3Dlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CComboBox* BIT = (CComboBox*)GetDlgItem(IDC_COMBO_BITRATE);
	CButton* RADIO1 = (CButton*)GetDlgItem(IDC_RADIO_CH1);
	CButton* RADIO2 = (CButton*)GetDlgItem(IDC_RADIO_CH2);
	CButton* CHECK_LOOPPOINT = (CButton*)GetDlgItem(IDC_CHECK_LOOPPOINT);
	CButton* CHECK_WHOLELOOP = (CButton*)GetDlgItem(IDC_CHECK_WHOLELOOP);
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPPART);
	CString Comboindex;
	int RADIO_CH_INDEX{}, RADIO_TOOL_INDEX{};
	int index = BIT->GetCurSel();
	Comboindex.Format(_T("%d"), index);
	RADIO_CH_INDEX = GetCheckedRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2);

	if (CHECK_LOOPPOINT->GetCheck() == BST_CHECKED) {
		if (EDIT_LOOPSTART->GetWindowTextLength() < 1) {
			MessageBox(_T("LoopStartの値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
		if (EDIT_LOOPEND->GetWindowTextLength() < 1) {
			MessageBox(_T("LoopEndの値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}

	if (CHECK_PARTLOOP->GetCheck() == BST_CHECKED) {
		if (EDIT_LOOPPART->GetWindowTextLength() == 0) {
			MessageBox(_T("LoopPartの値が無効です。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}

	CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile");

	if (!CMDPARAM) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0000", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0000", CMDPARAM, L".\\settings.ini");
	}

	if (BIT->GetCurSel() != CB_ERR) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0001", Comboindex, L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0001", L"", L".\\settings.ini");
	}
	
	if (CHECK_LOOPPOINT->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1000", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1000", L"0", L".\\settings.ini");
	}

	if (CHECK_WHOLELOOP->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1001", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1001", L"0", L".\\settings.ini");
	}
	if (CHECK_PARTLOOP->GetCheck() == BST_CHECKED) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1002", L"1", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x1002", L"0", L".\\settings.ini");
	}


	if (EDIT_LOOPSTART->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2000", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2000", m_hLoopStartLength, L".\\settings.ini");
	}
	if (EDIT_LOOPEND->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2001", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2001", m_hLoopEndLength, L".\\settings.ini");
	}

	if (EDIT_LOOPPART->GetWindowTextLength() == NULL) {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2002", L"", L".\\settings.ini");
	}
	else {
		WritePrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x2002", m_hLoopPart, L".\\settings.ini");
	}

	CDialogEx::OnOK();
}


void AT3Dlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}


void AT3Dlg::OnCbnSelchangeComboBitrate()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CComboBox* BIT = (CComboBox*)GetDlgItem(IDC_COMBO_BITRATE);
	CButton* RADIO1 = (CButton*)GetDlgItem(IDC_RADIO_CH1);
	CButton* RADIO2 = (CButton*)GetDlgItem(IDC_RADIO_CH2);
	if (BIT->GetCurSel() == 0) { // 32k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH1);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(FALSE);
		BITRATE = _T(" -br 32");
		OutputDebugString(_T("Set bitrate: 32[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 1) { // 48k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 48");
		OutputDebugString(_T("Set bitrate: 48[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 2) { // 52k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH1);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(FALSE);
		BITRATE = _T(" -br 52");
		OutputDebugString(_T("Set bitrate: 52[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 3) { // 64k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 64");
		OutputDebugString(_T("Set bitrate: 64[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 4) { // 66k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 66");
		OutputDebugString(_T("Set bitrate: 66[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 5) { // 96k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 96");
		OutputDebugString(_T("Set bitrate: 96[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 6) { // 105k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 105");
		OutputDebugString(_T("Set bitrate: 105[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 7) { // 128k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(TRUE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 128");
		OutputDebugString(_T("Set bitrate: 128[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 8) { // 132k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 132");
		OutputDebugString(_T("Set bitrate: 132[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 9) { // 160k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 160");
		OutputDebugString(_T("Set bitrate: 160[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 10) { // 192k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 192");
		OutputDebugString(_T("Set bitrate: 192[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 11) { // 256k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 256");
		OutputDebugString(_T("Set bitrate: 256[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 12) { // 320k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 320");
		OutputDebugString(_T("Set bitrate: 320[kbps]\n"));
	}
	else if (BIT->GetCurSel() == 13) { // 352k
		CheckRadioButton(IDC_RADIO_CH1, IDC_RADIO_CH2, IDC_RADIO_CH2);
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(TRUE);
		BITRATE = _T(" -br 352");
		OutputDebugString(_T("Set bitrate: 352[kbps]\n"));
	}
	else { // Error
		RADIO1->EnableWindow(FALSE);
		RADIO2->EnableWindow(FALSE);
		BITRATE = _T("");
		OutputDebugString(_T("Set bitrate: exception occured.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnBnClickedCheckLooppoint()
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
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnEnChangeEditLoopstart()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPSTART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPSTART);

	if (EDIT_LOOPSTART->GetWindowTextLength() == 0) {
		LOOPSTART = _T("");
		OutputDebugString(_T("LoopStart Length: null \n"));
	}
	else if (EDIT_LOOPSTART->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPSTART = _T(" ");
		LOOPSTART += m_hLoopStartLength;
		LOOPSTART += _T(" ");
		OutputDebugString(_T("LoopStart Length:") + LOOPSTART + _T("Samples.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnEnChangeEditLoopend()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPEND = (CEdit*)GetDlgItem(IDC_EDIT_LOOPEND);

	if (EDIT_LOOPEND->GetWindowTextLength() == 0) {
		LOOPEND = _T("");
		OutputDebugString(_T("LoopEnd Length: null \n"));
	}
	else if (EDIT_LOOPEND->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPEND = m_hLoopEndLength;
		OutputDebugString(_T("LoopEnd Length: ") + LOOPEND + _T(" Samples.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnBnClickedCheckWholeloop()
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
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnEnChangeEditLooppart()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPPART);

	if (EDIT_LOOPPART->GetWindowTextLength() == 0) {
		LOOPPART = _T("");
		OutputDebugString(_T("Repeating loop part: null \n"));
	}
	else if (EDIT_LOOPPART->GetWindowTextLength() != 0) {
		UpdateData(TRUE);
		LOOPPART = _T(" ");
		LOOPPART += m_hLoopPart;
		OutputDebugString(_T("Repeating loop part:") + LOOPPART + _T(" times.\n"));
	}
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}


void AT3Dlg::OnBnClickedCheckPartloop()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CButton* CHECK_PARTLOOP = (CButton*)GetDlgItem(IDC_CHECK_PARTLOOP);
	CEdit* EDIT_LOOPPART = (CEdit*)GetDlgItem(IDC_EDIT_LOOPPART);

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
	CEdit* EDIT_PARAM = (CEdit*)GetDlgItem(IDC_EDIT3);
	EDIT_PARAM->SetWindowText(CMDPARAM = TOOL + BITRATE + LOOPFLAG + LOOPSTART + LOOPEND + WHOLELOOPFLAG + LOOPPARTFLAG + LOOPPART + _T(" $InFile $OutFile"));
	return;
}
