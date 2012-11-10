#include "stdafx.h"			// vorübersetzter Header
#include "gak.h"			// CGapApp und Resourcen

#include "about.h"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDS_LIZENS, m_stLizens);
	DDX_Control(pDX, IDS_FUER, m_stFuer);
	DDX_Control(pDX, IDC_USER_NAME, m_stUserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	try
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		m_stUserName.SetWindowText (pApp -> UserName ());

	//	Lizensierung ausgeben
		CString strSection, strEntry;
		VERIFY (strSection.LoadString (IDS_INFO_SECTION));
		VERIFY (strEntry.LoadString (IDS_INFO_LIZENS));
		CString strVal (pApp -> GetProfileString (strSection, strEntry));
		m_stLizens.SetWindowText (strVal);

	//	"Für" ausgeben
		VERIFY (strEntry.LoadString (IDS_INFO_FUER));
		strVal = pApp -> GetProfileString (strSection, strEntry);
		m_stFuer.SetWindowText (strVal);		
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
