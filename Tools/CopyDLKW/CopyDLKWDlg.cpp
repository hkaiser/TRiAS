// CopyDLKWDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CopyDLKW.h"
#include "CopyDLKWDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlg dialog

IMPLEMENT_DYNAMIC(CCopyDLKWDlg, CDialog);

#pragma warning(disable: 4355)		// 'this' : used in base member initializer list

CCopyDLKWDlg::CCopyDLKWDlg(CWnd* pParent /*=NULL*/) :
	CDialog(CCopyDLKWDlg::IDD, pParent),
	m_threadCopy (this, reinterpret_cast<LPARAM>(&m_CopyData))
{
	//{{AFX_DATA_INIT(CCopyDLKWDlg)
	m_strDestPath = _T("");
	m_strSourcePath = _T("");
	m_strPrompt = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

#if defined(_DEBUG)
	m_strDestPath = _T("\\\\FORTYTWO\\Tiff\\");
	m_strSourcePath = _T("\\\\FORTYTWO\\Tiff\\");
#endif // defined(_DEBUG)

	m_iMinRange = 0;
	m_iMaxRange = 100;
}

CCopyDLKWDlg::~CCopyDLKWDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CCopyDLKWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyDLKWDlg)
	DDX_Control(pDX, IDC_COPYPROGRESS, m_Status);
	DDX_Control(pDX, IDC_CLOSE, m_pbClose);
	DDX_Control(pDX, IDOK, m_pbAction);
	DDX_Text(pDX, IDC_DESTINATIONDIR, m_strDestPath);
	DDX_Text(pDX, IDC_SOURCEDIR, m_strSourcePath);
	DDX_Text(pDX, IDC_PROMPT, m_strPrompt);
	//}}AFX_DATA_MAP

DWORD dwFlags = 0;
CString strCaptionDest;
CString strCaptionSrc;

	VERIFY(strCaptionSrc.LoadString(IDS_SELECTSOURCEDIR));
	VERIFY(strCaptionDest.LoadString(IDS_SELECTDESTINATIONDIR));

//	if (!IsWin40())
//		dwFlags |= GFLDR_OLD_STYLE_DIALOG;
//	if (IsWin50())
		dwFlags |= GFLDR_SAVEASDIALOG;

	DDX_GetFolderControl(pDX, IDC_SOURCEDIR, m_sleSourcePath, dwFlags, 
		strCaptionSrc,	m_strSourcePath);
	DDX_GetFolderControl(pDX, IDC_DESTINATIONDIR, m_sleDestPath, dwFlags, 
		strCaptionDest,	m_strDestPath);
}

const UINT WM_THREADCALLBACK = RegisterWindowMessage("WM_THREADCALLBACK");
const UINT WM_COPYDLKSTATUS = RegisterWindowMessage("WM_COPYDLKSTATUS");
const UINT WM_THREADERROR = RegisterWindowMessage("WM_THREADERROR");

BEGIN_MESSAGE_MAP(CCopyDLKWDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyDLKWDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_DESTINATIONDIR, OnChangeDestinationdir)
	ON_EN_CHANGE(IDC_SOURCEDIR, OnChangeSourcedir)
	ON_BN_CLICKED(IDC_CLOSE, OnCloseApp)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_REGISTERED_MESSAGE(WM_THREADCALLBACK, OnThreadCallback)
	ON_REGISTERED_MESSAGE(WM_COPYDLKSTATUS, OnCopyDLKStatus)
	ON_REGISTERED_MESSAGE(WM_THREADERROR, OnCopyError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlg message handlers

BOOL CCopyDLKWDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	AdjustOK();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCopyDLKWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCopyDLKWDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCopyDLKWDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CCopyDLKWDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CCopyDLKWDlg::OnCloseApp() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CCopyDLKWDlg::OnOK() 
{
	try {
		UpdateData(TRUE);
		m_CopyData.m_strSourcePath = m_strSourcePath;
		m_CopyData.m_strDestPath = m_strDestPath;

		m_pbAction.EnableWindow(FALSE);		// während Initialisierung
		m_threadCopy.Start();
	}
	catch (CThreadException *pe) {
		if (!pe->GetErrorMsg().IsEmpty())
			pe->ReportError();
		pe->Delete();
	}
}

void CCopyDLKWDlg::OnCancel()
{
	if (!m_threadCopy.IsAlive()) 
		OnCloseApp();		// same as 'Close'
	else
		OnStop();			// same as 'Cancel'
}

void CCopyDLKWDlg::OnStop() 
{
	if (IDYES == AfxMessageBox(IDS_ASKTOCANCEL, MB_YESNO)) {
		try {
			m_pbAction.EnableWindow(FALSE);
			m_threadCopy.Stop();
		}
		catch (CThreadException *pe) {
			if (!pe->GetErrorMsg().IsEmpty())
				pe->ReportError();
			pe->Delete();
		}
	}
}

BOOL CCopyDLKWDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}
	return TRUE;
}

void CCopyDLKWDlg::AdjustOK()
{
CString strSrc, strDest;

	GetDlgItem(IDC_SOURCEDIR) -> GetWindowText(strSrc);
	GetDlgItem(IDC_DESTINATIONDIR) -> GetWindowText(strDest);
	if (strSrc.GetLength() > 0 && strDest.GetLength() > 0)
		m_pbAction.EnableWindow(TRUE);
	else
		m_pbAction.EnableWindow(FALSE);
}

void CCopyDLKWDlg::OnChangeDestinationdir() 
{
	AdjustOK();
}

void CCopyDLKWDlg::OnChangeSourcedir() 
{
	AdjustOK();
}

LRESULT CCopyDLKWDlg::OnThreadCallback(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case CThread::CMD_INITIALIZE:
		if (!lParam) {
		// vorher
			m_pbClose.EnableWindow(FALSE);
			m_sleSourcePath.EnableWindow(FALSE);
			m_sleDestPath.EnableWindow(FALSE);
		}
		break;

	case CThread::CMD_RUN:
		if (!lParam) {
		// vorher
		CString strCancel;

			VERIFY(strCancel.LoadString(IDS_CANCEL));
			m_pbAction.EnableWindow(TRUE);
			m_pbAction.SetDlgCtrlID(IDC_STOP);
			m_pbAction.SetWindowText(strCancel);
		}
		break;

	case CThread::CMD_STOP:
		if (lParam) {
		// nachher
		CString strCopy;

			VERIFY(strCopy.LoadString(IDS_COPY));
			m_pbAction.EnableWindow(TRUE);
			m_pbAction.SetDlgCtrlID(IDOK);
			m_pbAction.SetWindowText(strCopy);

			m_pbClose.EnableWindow(TRUE);
			m_sleSourcePath.EnableWindow(TRUE);
			m_sleDestPath.EnableWindow(TRUE);

			m_Status.SetPos(m_iMinRange);
			m_strPrompt = "";
			UpdateData(FALSE);
		}
		break;
	}
	return TRUE;
}

LRESULT CCopyDLKWDlg::OnCopyDLKStatus(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case PBM_SETRANGE:
		m_iMinRange = LOWORD(lParam);
		m_iMaxRange = HIWORD(lParam);
		if (m_iMaxRange == m_iMinRange)
			m_iMaxRange = m_iMinRange+1;		// avoid division with zero
		m_Status.SetRange(m_iMinRange, m_iMaxRange);
		break;

	case PBM_SETPOS:
		{
			_ASSERTE(m_iMaxRange-m_iMinRange != 0);
			m_strPrompt.Format(IDS_STATUSPROMPT, ((lParam-m_iMinRange)*100)/(m_iMaxRange-m_iMinRange));
			m_Status.SetPos(lParam);
			UpdateData(FALSE);
		}
		break;
	}
	return TRUE;
}

LRESULT CCopyDLKWDlg::OnCopyError(WPARAM wParam, LPARAM lParam)
{
CString strError;
LPVOID lpMsgBuf = NULL;

	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		wParam,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);

CString strReason((LPCSTR)lpMsgBuf);

	LocalFree(lpMsgBuf);
	strReason.Replace('\n', ' ');

	strError.Format (IDS_COPYERROR, (LPCSTR)lParam, (LPCSTR)strReason, wParam);
	AfxMessageBox (strError);
	return TRUE;
}

