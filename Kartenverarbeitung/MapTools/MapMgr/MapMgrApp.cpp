#include "stdafx.h"
#include "MapMgrApp.h"

#include "MapMgrDoc.h"

#include "MainFrm.h"
#include "ViewPict.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: mapmgrapp.cpp 1.1 1996/07/12 10:49:55 andy Exp andy $";
/* $Log: mapmgrapp.cpp $
// Revision 1.1  1996/07/12  10:49:55  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMapMgrApp

BEGIN_MESSAGE_MAP(CMapMgrApp, CWinApp)
	//{{AFX_MSG_MAP(CMapMgrApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapMgrApp construction

CMapMgrApp::CMapMgrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMapMgrApp object

CMapMgrApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapMgrApp initialization

BOOL CMapMgrApp::InitInstance()
{
	if( !FirstInstance() )
		return FALSE;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	SetDialogBkColor();        // Set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	AfxEnableControlContainer();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapMgrDoc),
		RUNTIME_CLASS(CMainFrame),     // main SDI frame window
		RUNTIME_CLASS(CPictView));
	AddDocTemplate(pDocTemplate);

	// create a new (empty) document
	OnFileNew();
    ((CMainFrame*)GetMainWnd())->RestorePosition( SW_SHOWNORMAL );

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	m_pMainWnd->SendMessage( WM_COMMAND, ID_APPSTART, 0 );
	return TRUE;
}

BOOL CMapMgrApp::FirstInstance()
{
	CString	strCaption;
	strCaption.LoadString(AFX_IDS_APP_TITLE);
	CWnd *pWndFirst = CWnd::FindWindow(NULL,strCaption);
	if( pWndFirst )
	{
		CWnd *pWndPopup = pWndFirst->GetLastActivePopup();
		pWndFirst->BringWindowToTop();
		if(pWndFirst->IsIconic())
			pWndFirst->ShowWindow(SW_SHOWNORMAL);
		if(pWndFirst != pWndPopup)
			pWndPopup->BringWindowToTop();
		return FALSE;
	}
	return TRUE;
}

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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
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

// App command to run the dialog
void CMapMgrApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMapMgrApp commands
