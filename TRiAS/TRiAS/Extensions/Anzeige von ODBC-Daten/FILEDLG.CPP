// FileDlg.cpp : implementation file
//
#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten
#include <hpp/getodbci.hpp>		// CreateNewDataSource u.a.
#include "FileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog
CFileDlg::CFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(/*CFileDlg::IDD, pParent*/)
{
	//{{AFX_DATA_INIT(CFileDlg)
	m_strDsn = _T("");
	//}}AFX_DATA_INIT
	m_tType = NoDataSource;
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileDlg)
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Text(pDX, IDE_DSN, m_strDsn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileDlg, CDialog)
	//{{AFX_MSG_MAP(CFileDlg)
	ON_BN_CLICKED(IDB_CHANGE, OnChangeDsn)
	ON_BN_CLICKED(IDB_CREATE, OnCreateDsn)
	ON_BN_CLICKED(IDB_SELECT, OnSelectDsn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileDlg message handlers
BOOL CFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetControlState ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDlg::SetControlState (void)
{
	m_btChange.EnableWindow (m_strDsn.GetLength () > 0);
}

void CFileDlg::OnCreateDsn() 
{
	// TODO: Add your control notification handler code here
	ASSERT (m_tType == FileDataSource);
	CreateNewDataSource (m_hWnd, m_tType);		
}

void CFileDlg::OnChangeDsn() 
{
	// TODO: Add your control notification handler code here
	ASSERT (m_strDsn.GetLength () > 0);
	ASSERT (m_tType == FileDataSource);
	if (ChangeDataSource (m_hWnd, m_strDsn, m_tType))
	//	Parent ggf. benachrichtigen			
	{
		DataSourceInfo Info;
		Info.tType = m_tType;
		Info.pName = m_strDsn;
		:: SendMessage (GetParent () -> m_hWnd, WM_COMMAND, IDM_CONFIG_DSN, (LPARAM)&Info);	
	}		
}

void CFileDlg::OnSelectDsn() 
{
	// TODO: Add your control notification handler code here
	try
	{
		CString strDsn;
		if (SelectFileDataSource (strDsn, this) && (strDsn != m_strDsn))
		{
			m_strDsn = strDsn;		// speichern
			UpdateData (FALSE);		// anzeigen
			SetControlState ();		// Control-State akt.

		//	Parent benachrichtigen
			DataSourceInfo Info;
			Info.tType = m_tType;
			Info.pName = m_strDsn;
			:: SendMessage (GetParent () -> m_hWnd, WM_COMMAND, IDM_SELECT_DSN, (LPARAM)&Info);	
		}		
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}
}

BOOL CFileDlg::SelectDataSource (const char *pDsn)
{
	try
	{		
		ASSERT (NULL != pDsn && AfxIsValidString (pDsn));

		m_strDsn = pDsn;
		UpdateData (FALSE);

		SetControlState ();
		return TRUE;
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}

	return FALSE;
}
