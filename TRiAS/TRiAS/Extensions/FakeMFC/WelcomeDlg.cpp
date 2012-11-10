// WelcomeDlg.cpp : implementation file
//

#include "fakemfcp.hxx"

#include <registrx.hxx>

#include "fakemfc.h"
#include "WelcomeDlg.h"
#include "Strings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog

CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcomeDlg)
	//}}AFX_DATA_INIT
	m_iOpenMode = -1;
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDlg)
	DDX_Control(pDX, IDC_DONTSHOWFURTHER, m_cbDontShowFurther);
	DDX_Control(pDX, IDC_OPENOLDPROJECT, m_rbOpenOldProject);
	DDX_Control(pDX, IDC_OPENMRUPROJECT, m_rbOpenLast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialog)
	//{{AFX_MSG_MAP(CWelcomeDlg)
	ON_BN_CLICKED(IDC_CREATENEWPROJECT, OnCreateNewProject)
	ON_BN_CLICKED(IDC_OPENMRUPROJECT, OnOpenMruProject)
	ON_BN_CLICKED(IDC_OPENOLDPROJECT, OnOpenOldProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg message handlers

BOOL CWelcomeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Controls initialisieren
	{
	CCurrentUser regMRU (KEY_READ, g_cbMRUFiles);
	TCHAR cbBuffer[_MAX_PATH+5];
	ULONG ulLen = sizeof(cbBuffer);

		if (!regMRU.GetSubSZ (g_cbLastFile, cbBuffer, ulLen)) {
			m_rbOpenLast.EnableWindow (false);

			m_iOpenMode = 0;					// erster RadioButton
			m_rbOpenOldProject.SetCheck (true);
		} else {
			m_iOpenMode = 1;					// zweiter RadioButton
			m_rbOpenLast.SetCheck (true);
			m_rbOpenLast.SetFocus();
			return false;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWelcomeDlg::OnOK() 
{
// diesen Dialog wieder anzeigen?
	{
	CCurrentUser regMRU (g_cbMRUFiles, true);

		regMRU.SetDWORD (g_cbHideOpenWizard, m_cbDontShowFurther.GetCheck());
	}

// Ausführen der gewünschten Aktion
CWnd *pWnd = GetParent();

	ASSERT(NULL != pWnd);

// entsprechende MenuKommandos in TRiAS auslösen
	switch (m_iOpenMode) {
	case 0:		// OpenProject
		pWnd -> PostMessage (WM_COMMAND, IDM_OPEN);
		break;

	case 1:		// OpenMRUProject
		pWnd -> PostMessage (WM_COMMAND, IDM_OPENOLD1);
		break;

	case 2:		// CreateNewProject
		pWnd -> PostMessage (WM_COMMAND, IDM_CREATENEWPROJECT+g_pTE->MenuOffset());
		break;
	}

	CDialog::OnOK();
}

void CWelcomeDlg::OnCreateNewProject() 
{
	m_iOpenMode = 2;
}

void CWelcomeDlg::OnOpenMruProject() 
{
	m_iOpenMode = 1;
}

void CWelcomeDlg::OnOpenOldProject() 
{
	m_iOpenMode = 0;
}
