// UserDlg.cpp : implementation file
//

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten
#include <hpp/getodbci.hpp>
#include "UserDlg.h"		// zugeh. Header	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(/*CUserDlg::IDD, pParent*/)
{
	//{{AFX_DATA_INIT(CUserDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_tType = NoDataSource;
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Control(pDX, IDC_DSN, m_cbList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDB_CHANGE, OnChangeDsn)
	ON_BN_CLICKED(IDB_CREATE, OnCreateDsn)
	ON_CBN_SELCHANGE(IDC_DSN, OnSelchangeDsn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CUserDlg::SetControlState (void)
{
	m_cbList.EnableWindow (m_cbList.GetCount () > 0);
	m_btChange.EnableWindow (m_cbList.GetCurSel () >= 0);
}

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		try
	{
	//	prüfe DataSourceTyp
		ASSERT (UserDataSource == m_tType || m_tType == SystemDataSource);
	
	//	lade DataSources
		GetDataSources (&m_cbList, m_tType);

	//	ggf. DataSource in ListBox selektieren
		if ((m_cbList.GetCount () > 0) && !m_strDsn.IsEmpty ())
			m_cbList.SelectString (-1, m_strDsn);

		SetControlState ();
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers
void CUserDlg::OnChangeDsn() 
{
	// TODO: Add your control notification handler code here
	try
	{
		ASSERT (m_tType == UserDataSource || m_tType == SystemDataSource);

	//	lese akt. Selektion
		int iSel = m_cbList.GetCurSel ();
		if (iSel < 0)
			return;

	//	lese Namen
		CString strDsn;
		m_cbList.GetLBText (iSel, strDsn);
		
	//	DataSources config.
		if (ChangeDataSource (m_hWnd, strDsn, m_tType))
		{
		//	DataSources neu laden
			GetDataSources (&m_cbList, m_tType);		

		//	Datasource selektieren
			m_cbList.SelectString (-1, strDsn);

		//	Controls neu setzen
			SetControlState ();

		//	Parent immer benachrichtigen
			DataSourceInfo Info;
			Info.tType = m_tType;
			Info.pName = strDsn;
			:: SendMessage (GetParent () -> m_hWnd, WM_COMMAND, IDM_CONFIG_DSN, (LPARAM)&Info);
		}
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}
}

void CUserDlg::OnCreateDsn() 
{
	// TODO: Add your control notification handler code here
	ASSERT (m_tType == UserDataSource || m_tType == SystemDataSource);
	try
	{
		CString strDsn;
		int iSel = m_cbList.GetCurSel ();
		if (iSel >= 0)
			m_cbList.GetLBText (iSel, strDsn);
		
		if (CreateNewDataSource (m_hWnd, m_tType))
		{
		//	DataSources neu laden
			GetDataSources (&m_cbList, m_tType);		

		//	Datasource ggf. selektieren
			if (strDsn.GetLength () > 0)
				m_cbList.SelectString (-1, strDsn);

		//	Controls neu setzen
			SetControlState ();
		}
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}
}

void CUserDlg::OnSelchangeDsn() 
{
	// TODO: Add your control notification handler code here
	try
	{
		ASSERT (m_tType == UserDataSource || m_tType == SystemDataSource);

	//	lese akt. Selektion
		int iSel = m_cbList.GetCurSel ();
		if (iSel < 0)
			return;

	//	lese Namen
		m_cbList.GetLBText (iSel, m_strDsn);
		
	//	Controls neu setzen
		SetControlState ();

	//	Parent immer benachrichtigen
		DataSourceInfo Info;
		Info.tType = m_tType;
		Info.pName = m_strDsn;
		:: SendMessage (GetParent () -> m_hWnd, WM_COMMAND, IDM_SELECT_DSN, (LPARAM)&Info);	
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}
}

//	DataSource setzen
BOOL CUserDlg::SelectDataSource (const char *pDsn)
{
	try
	{
		ASSERT (NULL != pDsn && AfxIsValidString (pDsn));

		BOOL bRet = FALSE;
		if (!*pDsn)
		{
			bRet = TRUE;
			m_cbList.SetCurSel (-1);
		}
		else
		{
			int iSel = m_cbList.FindStringExact (-1, pDsn);
			if (iSel >= 0)
			{
				bRet = TRUE;
				m_cbList.SetCurSel (iSel);
			}
		}

		SetControlState ();
		return bRet;
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}

	return FALSE;
}


