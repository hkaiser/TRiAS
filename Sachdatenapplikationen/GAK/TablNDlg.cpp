// TablNDlg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "TablNDlg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableNameDlg dialog


CTableNameDlg::CTableNameDlg(CWnd* pParent, CString strDatabase)
	: CDialog(CTableNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableNameDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT (!strDatabase.IsEmpty ());
	m_strDatabase = strDatabase;
}

void CTableNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableNameDlg)
	DDX_Control(pDX, IDE_DATABASE, m_edDatabase);
	DDX_Control(pDX, IDE_NAME, m_edName);
	DDX_Control(pDX, IDOK, m_btOk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTableNameDlg, CDialog)
	//{{AFX_MSG_MAP(CTableNameDlg)
	ON_EN_CHANGE(IDE_NAME, OnChangeName)
	ON_BN_CLICKED(IDB_SELECT_DB, OnSelectDatabase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableNameDlg message handlers

void CTableNameDlg::OnChangeName() 
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_edName.LineLength () > 0);	
}

void CTableNameDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_edName.GetWindowText (m_strTableName);
	
	CDialog::OnOK();
}


BOOL CTableNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edName.LimitText (MaxTableNameLen);
	m_edDatabase.SetWindowText (m_strDatabase);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableNameDlg::OnSelectDatabase() 
{
	try
	{
		CString strExt, strFilter;
		VERIFY(strFilter.LoadString (IDS_MDB_FILTER)); 
		VERIFY (strExt.LoadString (IDS_DATABASE_EXTENSION));
		CFileDialog CopyToDialog (FALSE, strExt, "", OFN_HIDEREADONLY, 
								  strFilter, this);
		CString strCaption;
		VERIFY (strCaption.LoadString (IDS_TABLE_OUT_CAPTION));
		CopyToDialog.m_ofn.lpstrTitle = strCaption;				
		
	//	Dialog aufrufen
		if (IDOK == CopyToDialog.DoModal ())
		{
			m_strDatabase = CopyToDialog.GetPathName ();
			m_edDatabase.SetWindowText (m_strDatabase);
		}
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

