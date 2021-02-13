
// ATRACToolDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "ATRACTool.h"
#include "ATRACToolDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "PROCDlg.h"
#include "common.define.h"
#include "AT3Dlg.h"
#include "AT9Dlg.h"


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();

// 実装
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_hHYPER1, m_hHYPER2;
	COLORREF m_hyperlink;
	CFont m_hlfont;
	afx_msg void OnStnClickedStaticHyper1();
	afx_msg void OnStnClickedStaticHyper2();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	m_hyperlink = NULL;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HYPER1, m_hHYPER1);
	DDX_Control(pDX, IDC_STATIC_HYPER2, m_hHYPER2);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_STN_CLICKED(IDC_STATIC_HYPER1, &CAboutDlg::OnStnClickedStaticHyper1)
	ON_STN_CLICKED(IDC_STATIC_HYPER2, &CAboutDlg::OnStnClickedStaticHyper2)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hyperlink = RGB(0, 0, 255);
	CFont* pFont = m_hHYPER1.GetFont();
	LOGFONT lFont;
	pFont->GetLogFont(&lFont);
	lFont.lfUnderline = (TRUE);
	m_hlfont.CreateFontIndirect(&lFont);
	m_hHYPER1.SetFont(&m_hlfont, TRUE);
	m_hHYPER2.SetFont(&m_hlfont, TRUE);

	return TRUE;
}


BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (pWnd == &this->m_hHYPER1)
	{
		HCURSOR CURSOR_CUR = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(CURSOR_CUR);
		return TRUE;
	}
	if (pWnd == &this->m_hHYPER2)
	{
		HCURSOR CURSOR_CUR = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
		::SetCursor(CURSOR_CUR);
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd == &this->m_hHYPER1) {
		pDC->SetTextColor(m_hyperlink);
	}
	if (pWnd == &this->m_hHYPER2) {
		pDC->SetTextColor(m_hyperlink);
	}
	return hbr;
}


void CAboutDlg::OnStnClickedStaticHyper1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	ShellExecute(NULL, _T("open"), _T("https://xyle-official.com"), NULL, NULL, SW_SHOWNORMAL);
}


void CAboutDlg::OnStnClickedStaticHyper2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	ShellExecute(NULL, _T("open"), _T("https://xyle-official.com/tools/atractool"), NULL, NULL, SW_SHOWNORMAL);
}


// CATRACToolDlg ダイアログ



CATRACToolDlg::CATRACToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ATRACTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CATRACToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_hStatus);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_hFileFullName);
	DDX_Control(pDX, IDC_STATIC_FILEPATH, m_hFileFullPath);
	DDX_Radio(pDX, IDC_RADIO_AT3, m_hRadioFlag);
}

BEGIN_MESSAGE_MAP(CATRACToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPENFILE, &CATRACToolDlg::OnOpenFile)
	ON_COMMAND(ID_CLOSEFILE, &CATRACToolDlg::OnCloseFile)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CATRACToolDlg::OnBnClickedButtonDecode)
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CATRACToolDlg::OnBnClickedButtonEncode)
	ON_COMMAND(ID_AT3SETTINGS, &CATRACToolDlg::OnAt3settings)
	ON_COMMAND(ID_AT9SETTINGS, &CATRACToolDlg::OnAt9Settings)
	ON_COMMAND(ID_ABOUT, &CATRACToolDlg::OnAbout)
	ON_COMMAND(ID_UPDATE, &CATRACToolDlg::OnUpdate)
	ON_COMMAND(ID_EXIT, &CATRACToolDlg::OnExit)
	ON_WM_DESTROY()
	ON_COMMAND(ID_DELETEINI, &CATRACToolDlg::OnDeleteIniFile)
END_MESSAGE_MAP()


// CATRACToolDlg メッセージ ハンドラー

BOOL CATRACToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	checkExistenceOfFolder(".\\Resources");
	LoadResources();

	CFileFind init;

	SetWindowText(_T("ATRACTool [") + CURRENTTEXT + _T(", Feb. 14, 2021]"));

	OutputDebugString(_T("Initializing...\n"));
	if (init.FindFile(_T(".\\Resources\\at3tool.exe"))) {
		if (init.FindFile(_T(".\\Resources\\at9tool.exe"))) {
			this->m_hStatus.SetWindowText(DEFAULTTEXT);
			this->m_hFileFullName.SetWindowText(NULL);
			this->m_hFileFullPath.SetWindowText(NULL);
		}
		else {
			OutputDebugString(_T("Error! at9tool.exe not found. \n"));
			MessageBox(_T("at9tool.exe が見つかりませんでした"), _T("ATRACTool.exe - システム エラー"), MB_ICONERROR | MB_OK);
			AfxGetMainWnd()->DestroyWindow();
		}
	}
	else {
		OutputDebugString(_T("Error! at3tool.exe not found. \n"));
		MessageBox(_T("at3tool.exe が見つかりませんでした"), _T("ATRACTool.exe - システム エラー"), MB_ICONERROR | MB_OK);
		AfxGetMainWnd()->DestroyWindow();
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CATRACToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CATRACToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CATRACToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CATRACToolDlg::OnOpenFile()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnOpenFile\n"));
	DWORD size;
	PROCDlg* PROCDLG = new PROCDlg;
	CButton* BUTTON_DECODE = (CButton*)GetDlgItem(IDC_BUTTON_DECODE);
	CButton* BUTTON_ENCODE = (CButton*)GetDlgItem(IDC_BUTTON_ENCODE);
	CButton* RADIO_AT3 = (CButton*)GetDlgItem(IDC_RADIO_AT3);
	CButton* RADIO_AT9 = (CButton*)GetDlgItem(IDC_RADIO_AT9);
	wchar_t Drive[10]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
	CString DRIVE, DIR, NAME, EXT, SIZE, AT3EXT = _T(".AT3"), AT9EXT = _T(".AT9"), WAVEEXT = _T(".WAV"), FLAG;
	CString filter("Adaptive TRansform Acoustic Coding 3 (*.at3)|*.at3|Adaptive TRansform Acoustic Coding 9 (*.at9)|*.at9|Microsoft Wave サウンド (*.wav)|*.wav|サポートされているすべてのファイル (*.at3,*.at9,*.wav)|*.at3;*.at9;*.wav||");
	CFileDialog selDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter);
	INT_PTR ret = selDlg.DoModal();
	if (ret == IDOK) {
		m_hREADFILE = selDlg.GetPathName();
		if (!m_hREADFILE) {
			MessageBox(_T("ファイルを開けませんでした"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
		PROCDLG->Create(IDD_PROCESS_DLG);
		PROCDLG->ShowWindow(SW_SHOW);
		_tsplitpath_s(m_hREADFILE, Drive, Dir, Name, Ext);
		DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;
		size = GetFileSizeStat(m_hREADFILE);
		SIZE.Format(_T("%u バイト"), size);
		this->m_hStatus.SetWindowText(READEDTEXT);
		this->m_hFileFullName.SetWindowText(_T("ファイル名：") + NAME + EXT + _T("　　　ファイルサイズ：") + SIZE);
		this->m_hFileFullPath.SetWindowText(_T("絶対パス：") + DRIVE + DIR + NAME + EXT);
		FLAG = EXT;
		FLAG.MakeUpper();
		if (FLAG.Compare(AT3EXT) == 0) {
			BUTTON_DECODE->EnableWindow(TRUE);
			BUTTON_ENCODE->EnableWindow(FALSE);
			RADIO_AT3->EnableWindow(FALSE);
			RADIO_AT9->EnableWindow(FALSE);
			PROCDLG->DestroyWindow();
			delete PROCDLG;
			return;
		}
		else if (FLAG.Compare(AT9EXT) == 0) {
			BUTTON_DECODE->EnableWindow(TRUE);
			BUTTON_ENCODE->EnableWindow(FALSE);
			RADIO_AT3->EnableWindow(FALSE);
			RADIO_AT9->EnableWindow(FALSE);
			PROCDLG->DestroyWindow();
			delete PROCDLG;
			return;
		}
		else if (FLAG.Compare(WAVEEXT) == 0){
			BUTTON_DECODE->EnableWindow(FALSE);
			BUTTON_ENCODE->EnableWindow(TRUE);
			CheckRadioButton(IDC_RADIO_AT3, IDC_RADIO_AT9, IDC_RADIO_AT3);
			RADIO_AT3->EnableWindow(TRUE);
			RADIO_AT9->EnableWindow(TRUE);
			PROCDLG->DestroyWindow();
			delete PROCDLG;
			return;
		}
		else {
			this->m_hStatus.SetWindowText(DEFAULTTEXT);
			this->m_hFileFullName.SetWindowText(NULL);
			this->m_hFileFullPath.SetWindowText(NULL);
			BUTTON_DECODE->EnableWindow(FALSE);
			BUTTON_ENCODE->EnableWindow(FALSE);
			RADIO_AT3->EnableWindow(FALSE);
			RADIO_AT9->EnableWindow(FALSE);
			PROCDLG->DestroyWindow();
			delete PROCDLG;
			return;
		}
	}
	else {
		PROCDLG->Create(IDD_PROCESS_DLG);
		PROCDLG->ShowWindow(SW_SHOW);
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		RADIO_AT3->EnableWindow(FALSE);
		RADIO_AT9->EnableWindow(FALSE);
		PROCDLG->DestroyWindow();
		delete PROCDLG;
		return;
	}
}


void CATRACToolDlg::OnCloseFile()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnCloseFile\n"));
	CButton* BUTTON_DECODE = (CButton*)GetDlgItem(IDC_BUTTON_DECODE);
	CButton* BUTTON_ENCODE = (CButton*)GetDlgItem(IDC_BUTTON_ENCODE);
	if (NULL != m_hREADFILE.GetLength()) {
		m_hREADFILE.Empty();
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		return;
	}
}


void CATRACToolDlg::OnBnClickedButtonDecode()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedButtonDecode\n"));

	CFileFind find;
	CButton* BUTTON_DECODE = (CButton*)GetDlgItem(IDC_BUTTON_DECODE);
	CButton* BUTTON_ENCODE = (CButton*)GetDlgItem(IDC_BUTTON_ENCODE);

	if (m_hREADFILE.GetLength() == 0) {
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		MessageBox(_T("ファイルが選択されていません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else if (m_hREADFILE.GetLength() > MAX_PATH) {
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		MessageBox(_T("ファイルへのパスが長すぎます。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else {
		wchar_t Drive[10]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{};
		wchar_t Drive2[10]{}, Dir2[MAX_PATH]{}, Name2[MAX_PATH]{}, Ext2[MAX_PATH]{};
		CString DRIVE, DIR, NAME, EXT, FNAME, SAVEPATH, LPPATH, AT3EXT = _T(".AT3"), AT9EXT = _T(".AT9"), FLAG;
		CString DRIVE2, DIR2, NAME2, EXT2;
		_tsplitpath_s(m_hREADFILE, Drive, Dir, Name, Ext);
		DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;
		FLAG = EXT;
		FLAG.MakeUpper();
		if (FLAG.Compare(AT3EXT) == 0) {
			FNAME = m_hREADFILE.Right(m_hREADFILE.GetLength() - m_hREADFILE.ReverseFind(_T('\\')) - 1);
			FNAME = FNAME.Left(FNAME.ReverseFind(_T('.')));
			CString filter("Wave ファイル (*.wav)|*.wav;||");
			CFileDialog selDlg(FALSE, _T("wav"), FNAME, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter, this);
			INT_PTR ret = selDlg.DoModal();
			if (ret == IDOK) {
				SAVEPATH = selDlg.GetPathName();
				if (!SAVEPATH) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("不明なエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}

				if (find.FindFile(SAVEPATH)) {
					DeleteFile(SAVEPATH);
				}

				_tsplitpath_s(SAVEPATH, Drive2, Dir2, Name2, Ext2);
				DRIVE2 = Drive2, DIR2 = Dir2, NAME2 = Name2, EXT2 = Ext2;

				LPPATH = _T(".\\Resources\\at3tool -d ") + m_hREADFILE + _T(" ") + SAVEPATH;

				TCHAR* lpPathT = (TCHAR*)malloc(sizeof(TCHAR) * 512); // Convert CString to TCHAR.
				if (NULL == lpPathT) {
					perror("can not malloc");
					OutputDebugString(_T("TCHAR syntax (lpPath) malloc failed.\n"));
					return;
				}
				else {
					ZeroMemory(&lpPathT[0], 512);
					_tcscpy_s(&lpPathT[0], 512, LPPATH);
				}

				PROCDlg* PROCDLG = new PROCDlg;
				PROCDLG->Create(IDD_PROCESS_DLG);
				PROCDLG->ShowWindow(SW_SHOW);

				STARTUPINFO si;
				memset(&si, 0, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				memset(&pi, 0, sizeof(PROCESS_INFORMATION));
				si.dwFlags = STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_HIDE;
				::CreateProcess(NULL, lpPathT, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				CloseHandle(pi.hThread);	// CloseHandleでhThreadを閉じる.
				MSG msg;
				while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if (!AfxGetApp()->PumpMessage())
					{
						::PostQuitMessage(0);
						break;
					}
				}
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				free(lpPathT);

				PROCDLG->DestroyWindow();
				delete PROCDLG;

				if (find.FindFile(SAVEPATH)) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("デコード完了"), _T("完了"), MB_ICONINFORMATION | MB_OK);
					ShellExecute(NULL, _T("open"), DRIVE2 + DIR2, NULL, NULL, SW_SHOWNORMAL);
					return;
				}
				else {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("デコードに失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			else {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("キャンセルされました。"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		else if (FLAG.Compare(AT9EXT) == 0) {
			FNAME = m_hREADFILE.Right(m_hREADFILE.GetLength() - m_hREADFILE.ReverseFind(_T('\\')) - 1);
			FNAME = FNAME.Left(FNAME.ReverseFind(_T('.')));
			CString filter("Wave ファイル (*.wav)|*.wav;||");
			CFileDialog selDlg(FALSE, _T("wav"), FNAME, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter, this);
			INT_PTR ret = selDlg.DoModal();
			if (ret == IDOK) {
				SAVEPATH = selDlg.GetPathName();
				if (!SAVEPATH) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("不明なエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}

				if (find.FindFile(SAVEPATH)) {
					DeleteFile(SAVEPATH);
				}

				_tsplitpath_s(SAVEPATH, Drive2, Dir2, Name2, Ext2);
				DRIVE2 = Drive2, DIR2 = Dir2, NAME2 = Name2, EXT2 = Ext2;

				LPPATH = _T(".\\Resources\\at9tool -d ") + m_hREADFILE + _T(" ") + SAVEPATH;

				TCHAR* lpPathT = (TCHAR*)malloc(sizeof(TCHAR) * 512); // Convert CString to TCHAR.
				if (NULL == lpPathT) {
					perror("can not malloc");
					OutputDebugString(_T("TCHAR syntax (lpPath) malloc failed.\n"));
					return;
				}
				else {
					ZeroMemory(&lpPathT[0], 512);
					_tcscpy_s(&lpPathT[0], 512, LPPATH);
				}

				PROCDlg* PROCDLG = new PROCDlg;
				PROCDLG->Create(IDD_PROCESS_DLG);
				PROCDLG->ShowWindow(SW_SHOW);

				STARTUPINFO si;
				memset(&si, 0, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				memset(&pi, 0, sizeof(PROCESS_INFORMATION));
				si.dwFlags = STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_HIDE;
				::CreateProcess(NULL, lpPathT, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				CloseHandle(pi.hThread);	// CloseHandleでhThreadを閉じる.
				MSG msg;
				while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if (!AfxGetApp()->PumpMessage())
					{
						::PostQuitMessage(0);
						break;
					}
				}
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				free(lpPathT);

				PROCDLG->DestroyWindow();
				delete PROCDLG;

				if (find.FindFile(SAVEPATH)) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("デコード完了"), _T("完了"), MB_ICONINFORMATION | MB_OK);
					ShellExecute(NULL, _T("open"), DRIVE2 + DIR2, NULL, NULL, SW_SHOWNORMAL);
					return;
				}
				else {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("デコードに失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			else {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("キャンセルされました。"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		else {
			this->m_hStatus.SetWindowText(DEFAULTTEXT);
			this->m_hFileFullName.SetWindowText(NULL);
			this->m_hFileFullPath.SetWindowText(NULL);
			BUTTON_DECODE->EnableWindow(FALSE);
			BUTTON_ENCODE->EnableWindow(FALSE);
			m_hREADFILE.Empty();
			MessageBox(_T("不明なファイルが読み込まれました。"), _T("エラー"), MB_ICONERROR | MB_OK);
			return;
		}
	}
}


void CATRACToolDlg::OnBnClickedButtonEncode()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OutputDebugString(_T("OnBnClickedButtonEncode\n"));

	CFileFind find;
	CButton* BUTTON_DECODE = (CButton*)GetDlgItem(IDC_BUTTON_DECODE);
	CButton* BUTTON_ENCODE = (CButton*)GetDlgItem(IDC_BUTTON_ENCODE);
	CButton* RADIO_AT3 = (CButton*)GetDlgItem(IDC_RADIO_AT3);
	CButton* RADIO_AT9 = (CButton*)GetDlgItem(IDC_RADIO_AT9);
	int RADIO = GetCheckedRadioButton(IDC_RADIO_AT3, IDC_RADIO_AT9);

	if (m_hREADFILE.GetLength() == 0) {
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		RADIO_AT3->EnableWindow(FALSE);
		RADIO_AT9->EnableWindow(FALSE);
		MessageBox(_T("ファイルが選択されていません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else if (m_hREADFILE.GetLength() > MAX_PATH) {
		this->m_hStatus.SetWindowText(DEFAULTTEXT);
		this->m_hFileFullName.SetWindowText(NULL);
		this->m_hFileFullPath.SetWindowText(NULL);
		BUTTON_DECODE->EnableWindow(FALSE);
		BUTTON_ENCODE->EnableWindow(FALSE);
		RADIO_AT3->EnableWindow(FALSE);
		RADIO_AT9->EnableWindow(FALSE);
		MessageBox(_T("ファイルへのパスが長すぎます。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	else {
		wchar_t Drive[10]{}, Dir[MAX_PATH]{}, Name[MAX_PATH]{}, Ext[MAX_PATH]{}, lpPath[MAX_PATH]{};
		wchar_t Drive2[10]{}, Dir2[MAX_PATH]{}, Name2[MAX_PATH]{}, Ext2[MAX_PATH]{};
		CString DRIVE, DIR, NAME, EXT, FNAME, SAVEPATH, LPPATH, LPFLAG;
		CString DRIVE2, DIR2, NAME2, EXT2;
		_tsplitpath_s(m_hREADFILE, Drive, Dir, Name, Ext);
		DRIVE = Drive, DIR = Dir, NAME = Name, EXT = Ext;

		if (RADIO == 1016) {
			GetPrivateProfileString(L"ATRAC3_ENCODE_SETTINGS", L"0x0000", NULL, (LPWSTR)lpPath, MAX_PATH, L".\\settings.ini");
			LPFLAG = lpPath;
			if (LPFLAG.GetLength() == NULL) {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				RADIO_AT3->EnableWindow(FALSE);
				RADIO_AT9->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("変換設定が適切に設定されていません"), _T("エラー"), MB_ICONERROR | MB_OK);
				return;
			}

			FNAME = m_hREADFILE.Right(m_hREADFILE.GetLength() - m_hREADFILE.ReverseFind(_T('\\')) - 1);
			FNAME = FNAME.Left(FNAME.ReverseFind(_T('.')));
			CString filter("Adaptive TRansform Acoustic Coding 3 (*.at3)|*.at3;||");
			CFileDialog selDlg(FALSE, _T("at3"), FNAME, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter, this);
			INT_PTR ret = selDlg.DoModal();
			if (ret == IDOK) {
				SAVEPATH = selDlg.GetPathName();
				if (!SAVEPATH) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					RADIO_AT3->EnableWindow(FALSE);
					RADIO_AT9->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("不明なエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}

				if (find.FindFile(SAVEPATH)) {
					DeleteFile(SAVEPATH);
				}

				_tsplitpath_s(SAVEPATH, Drive2, Dir2, Name2, Ext2);
				DRIVE2 = Drive2, DIR2 = Dir2, NAME2 = Name2, EXT2 = Ext2;

				LPPATH = lpPath;
				AfxReplaceStr(LPPATH, L"at3tool", _T(".\\Resources\\at3tool"));
				AfxReplaceStr(LPPATH, L"$InFile", m_hREADFILE);
				AfxReplaceStr(LPPATH, L"$OutFile", SAVEPATH);

				TCHAR* lpPathT = (TCHAR*)malloc(sizeof(TCHAR) * 512); // Convert CString to TCHAR.
				if (NULL == lpPathT) {
					perror("can not malloc");
					OutputDebugString(_T("TCHAR syntax (lpPath) malloc failed.\n"));
					return;
				}
				else {
					ZeroMemory(&lpPathT[0], 512);
					_tcscpy_s(&lpPathT[0], 512, LPPATH);
				}

				PROCDlg* PROCDLG = new PROCDlg;
				PROCDLG->Create(IDD_PROCESS_DLG);
				PROCDLG->ShowWindow(SW_SHOW);

				STARTUPINFO si;
				memset(&si, 0, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				memset(&pi, 0, sizeof(PROCESS_INFORMATION));
				si.dwFlags = STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_HIDE;
				::CreateProcess(NULL, lpPathT, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				CloseHandle(pi.hThread);	// CloseHandleでhThreadを閉じる.
				MSG msg;
				while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if (!AfxGetApp()->PumpMessage())
					{
						::PostQuitMessage(0);
						break;
					}
				}
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				free(lpPathT);

				PROCDLG->DestroyWindow();
				delete PROCDLG;

				if (find.FindFile(SAVEPATH)) {
					DWORD SAVESIZE = GetFileSizeStat(SAVEPATH);
					if (SAVESIZE == 0) {
						DeleteFile(SAVEPATH);
						this->m_hStatus.SetWindowText(DEFAULTTEXT);
						this->m_hFileFullName.SetWindowText(NULL);
						this->m_hFileFullPath.SetWindowText(NULL);
						BUTTON_DECODE->EnableWindow(FALSE);
						BUTTON_ENCODE->EnableWindow(FALSE);
						RADIO_AT3->EnableWindow(FALSE);
						RADIO_AT9->EnableWindow(FALSE);
						m_hREADFILE.Empty();
						MessageBox(_T("エンコードに失敗しました。\nWaveファイルのエンコード形式を確認してください。\nまたは、変換設定が適切に設定されているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
						return;
					}
					else {
						this->m_hStatus.SetWindowText(DEFAULTTEXT);
						this->m_hFileFullName.SetWindowText(NULL);
						this->m_hFileFullPath.SetWindowText(NULL);
						BUTTON_DECODE->EnableWindow(FALSE);
						BUTTON_ENCODE->EnableWindow(FALSE);
						RADIO_AT3->EnableWindow(FALSE);
						RADIO_AT9->EnableWindow(FALSE);
						m_hREADFILE.Empty();
						MessageBox(_T("エンコード完了"), _T("完了"), MB_ICONINFORMATION | MB_OK);
						ShellExecute(NULL, _T("open"), DRIVE2 + DIR2, NULL, NULL, SW_SHOWNORMAL);
						return;
					}
				}
				else {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					RADIO_AT3->EnableWindow(FALSE);
					RADIO_AT9->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("エンコードに失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			else {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				RADIO_AT3->EnableWindow(FALSE);
				RADIO_AT9->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("キャンセルされました。"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		else if (RADIO == 1017) {
			GetPrivateProfileString(L"ATRAC9_ENCODE_SETTINGS", L"0x0000", NULL, (LPWSTR)lpPath, MAX_PATH, L".\\settings.ini");
			LPFLAG = lpPath;
			if (LPFLAG.GetLength() == NULL) {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				RADIO_AT3->EnableWindow(FALSE);
				RADIO_AT9->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("変換設定が適切に設定されていません"), _T("エラー"), MB_ICONERROR | MB_OK);
				return;
			}

			FNAME = m_hREADFILE.Right(m_hREADFILE.GetLength() - m_hREADFILE.ReverseFind(_T('\\')) - 1);
			FNAME = FNAME.Left(FNAME.ReverseFind(_T('.')));
			CString filter("Adaptive TRansform Acoustic Coding 9 (*.at9)|*.at9;||");
			CFileDialog selDlg(FALSE, _T("at9"), FNAME, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, filter, this);
			INT_PTR ret = selDlg.DoModal();
			if (ret == IDOK) {
				SAVEPATH = selDlg.GetPathName();
				if (!SAVEPATH) {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					RADIO_AT3->EnableWindow(FALSE);
					RADIO_AT9->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("不明なエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}

				if (find.FindFile(SAVEPATH)) {
					DeleteFile(SAVEPATH);
				}

				_tsplitpath_s(SAVEPATH, Drive2, Dir2, Name2, Ext2);
				DRIVE2 = Drive2, DIR2 = Dir2, NAME2 = Name2, EXT2 = Ext2;

				LPPATH = lpPath;
				AfxReplaceStr(LPPATH, L"at9tool", _T(".\\Resources\\at9tool"));
				AfxReplaceStr(LPPATH, L"$InFile", m_hREADFILE);
				AfxReplaceStr(LPPATH, L"$OutFile", SAVEPATH);

				TCHAR* lpPathT = (TCHAR*)malloc(sizeof(TCHAR) * 512); // Convert CString to TCHAR.
				if (NULL == lpPathT) {
					perror("can not malloc");
					OutputDebugString(_T("TCHAR syntax (lpPath) malloc failed.\n"));
					return;
				}
				else {
					ZeroMemory(&lpPathT[0], 512);
					_tcscpy_s(&lpPathT[0], 512, LPPATH);
				}

				PROCDlg* PROCDLG = new PROCDlg;
				PROCDLG->Create(IDD_PROCESS_DLG);
				PROCDLG->ShowWindow(SW_SHOW);

				STARTUPINFO si;
				memset(&si, 0, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				memset(&pi, 0, sizeof(PROCESS_INFORMATION));
				si.dwFlags = STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_HIDE;
				::CreateProcess(NULL, lpPathT, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				CloseHandle(pi.hThread);	// CloseHandleでhThreadを閉じる.
				MSG msg;
				while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
					if (!AfxGetApp()->PumpMessage())
					{
						::PostQuitMessage(0);
						break;
					}
				}
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				free(lpPathT);

				PROCDLG->DestroyWindow();
				delete PROCDLG;

				if (find.FindFile(SAVEPATH)) {
					DWORD SAVESIZE = GetFileSizeStat(SAVEPATH);
					if (SAVESIZE == 0) {
						DeleteFile(SAVEPATH);
						this->m_hStatus.SetWindowText(DEFAULTTEXT);
						this->m_hFileFullName.SetWindowText(NULL);
						this->m_hFileFullPath.SetWindowText(NULL);
						BUTTON_DECODE->EnableWindow(FALSE);
						BUTTON_ENCODE->EnableWindow(FALSE);
						RADIO_AT3->EnableWindow(FALSE);
						RADIO_AT9->EnableWindow(FALSE);
						m_hREADFILE.Empty();
						MessageBox(_T("エンコードに失敗しました。\nWaveファイルのエンコード形式を確認してください。\nまたは、変換設定が適切に設定されているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
						return;
					}
					else {
						this->m_hStatus.SetWindowText(DEFAULTTEXT);
						this->m_hFileFullName.SetWindowText(NULL);
						this->m_hFileFullPath.SetWindowText(NULL);
						BUTTON_DECODE->EnableWindow(FALSE);
						BUTTON_ENCODE->EnableWindow(FALSE);
						RADIO_AT3->EnableWindow(FALSE);
						RADIO_AT9->EnableWindow(FALSE);
						m_hREADFILE.Empty();
						MessageBox(_T("エンコード完了"), _T("完了"), MB_ICONINFORMATION | MB_OK);
						ShellExecute(NULL, _T("open"), DRIVE2 + DIR2, NULL, NULL, SW_SHOWNORMAL);
						return;
					}
				}
				else {
					this->m_hStatus.SetWindowText(DEFAULTTEXT);
					this->m_hFileFullName.SetWindowText(NULL);
					this->m_hFileFullPath.SetWindowText(NULL);
					BUTTON_DECODE->EnableWindow(FALSE);
					BUTTON_ENCODE->EnableWindow(FALSE);
					RADIO_AT3->EnableWindow(FALSE);
					RADIO_AT9->EnableWindow(FALSE);
					m_hREADFILE.Empty();
					MessageBox(_T("エンコードに失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
					return;
				}
			}
			else {
				this->m_hStatus.SetWindowText(DEFAULTTEXT);
				this->m_hFileFullName.SetWindowText(NULL);
				this->m_hFileFullPath.SetWindowText(NULL);
				BUTTON_DECODE->EnableWindow(FALSE);
				BUTTON_ENCODE->EnableWindow(FALSE);
				RADIO_AT3->EnableWindow(FALSE);
				RADIO_AT9->EnableWindow(FALSE);
				m_hREADFILE.Empty();
				MessageBox(_T("キャンセルされました。"), _T("警告"), MB_ICONWARNING | MB_OK);
				return;
			}
		}
		else {
			this->m_hStatus.SetWindowText(DEFAULTTEXT);
			this->m_hFileFullName.SetWindowText(NULL);
			this->m_hFileFullPath.SetWindowText(NULL);
			BUTTON_DECODE->EnableWindow(FALSE);
			BUTTON_ENCODE->EnableWindow(FALSE);
			RADIO_AT3->EnableWindow(FALSE);
			RADIO_AT9->EnableWindow(FALSE);
			m_hREADFILE.Empty();
			MessageBox(_T("不明なエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
		}
	}
}


void CATRACToolDlg::OnAt3settings()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AT3Dlg* Dlg = new AT3Dlg;
	INT_PTR ret = Dlg->DoModal();
	if (ret == IDOK) {
		delete Dlg;
	}
	else {
		delete Dlg;
	}
}


void CATRACToolDlg::OnAt9Settings()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AT9Dlg* Dlg = new AT9Dlg;
	INT_PTR ret = Dlg->DoModal();
	if (ret == IDOK) {
		delete Dlg;
	}
	else {
		delete Dlg;
	}
}


void CATRACToolDlg::OnAbout()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnAbout\n"));
	CAboutDlg About;
	About.DoModal();
}


void CATRACToolDlg::OnUpdate()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnUpdateCheck\n"));
	CString LatestVersion = AppUpdateCheck();
	if (LatestVersion == _T("")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nインターネット接続がされているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	if (LatestVersion == _T("-1")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nサーバーにデータが見つかりません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	CString CurrentVersion = AppCurrentVersionCheck();
	if (CurrentVersion == _T("")) {
		MessageBox(_T("情報取得中にエラーが発生しました。\nインターネット接続がされているか確認してください。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
	LatestVersion = LatestVersion.Left(CurrentVersion.GetLength());
	LatestVersion += _T("\r");
	if (LatestVersion == CurrentVersion + _T("\r")) {
		MessageBox(_T("最新バージョン：") + LatestVersion + _T("現在使用中のバージョン：") + CurrentVersion + _T("\nアプリケーションのバージョンは最新です。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
		return;
	}
	else if (LatestVersion > CurrentVersion) {
		UINT ret;
		ret = MessageBox(_T("最新バージョン：") + LatestVersion + _T("現在使用中のバージョン：") + CurrentVersion + _T("\nアプリケーションのアップデートが可能です。サイトを開きますか？"), _T("アップデート確認"), MB_ICONINFORMATION | MB_YESNOCANCEL);
		if (ret == IDYES) {
			ShellExecute(NULL, _T("open"), _T("https://xyle-official.com/tools/atractool/#latest-release"), NULL, NULL, SW_SHOWNORMAL);
			return;
		}
		else if (ret == IDNO) {
			return;
		}
		else if (ret == IDCANCEL) {
			MessageBox(_T("キャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
		}
		else {
			return;
		}
	}
	else {
		MessageBox(_T("情報取得中にエラーが発生しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
}


void CATRACToolDlg::OnExit()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnExit\n"));
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
	AfxGetMainWnd()->DestroyWindow();
	PostQuitMessage(0);
}


void CATRACToolDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	OutputDebugString(_T("OnDestroy\n"));

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	DeleteDirectory(_T(".\\Resources"));
}


void CATRACToolDlg::OnDeleteIniFile()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OutputDebugString(_T("OnDeleteIniFile\n"));
	CFileFind find;
	if (find.FindFile(_T(".\\settings.ini"))) {
		INT_PTR ret = MessageBox(_T("設定ファイルを削除してもよろしいですか？"), _T("確認"), MB_ICONWARNING | MB_YESNO);
		if (ret == IDYES) {
			DeleteFile(_T(".\\settings.ini"));
			if (find.FindFile(_T(".\\settings.ini"))) {
				MessageBox(_T("設定ファイルの削除に失敗しました。"), _T("エラー"), MB_ICONERROR | MB_OK);
			}
			else {
				MessageBox(_T("設定ファイルの削除が完了しました。"), _T("完了"), MB_ICONINFORMATION | MB_OK);
			}
			return;
		}
		else if (ret == IDNO) {
			MessageBox(_T("キャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
			return;
		}
		else {
			MessageBox(_T("キャンセルされました。"), _T("キャンセル"), MB_ICONWARNING | MB_OK);
			return;
		}
	}
	else {
		MessageBox(_T("設定ファイルが存在しないため、削除できません。"), _T("エラー"), MB_ICONERROR | MB_OK);
		return;
	}
}
