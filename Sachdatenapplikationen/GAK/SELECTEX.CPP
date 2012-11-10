// selectex.cpp : implementation file
//
#include "stdafx.h"			//	prec. Header 
//#include "resource.h"		//	Resourcekonstanten
#include "gak.h"			//	CGakApp

#include "selectex.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectExportTables dialog
CSelectExportTables::CSelectExportTables(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectExportTables::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectExportTables)
	m_bAbfaelle = TRUE;
	m_bErzeuger = TRUE;
	//}}AFX_DATA_INIT
}

void CSelectExportTables::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectExportTables)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Check(pDX, IDB_ABFAELLE, m_bAbfaelle);
	DDX_Check(pDX, IDB_ERZEUGER, m_bErzeuger);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelectExportTables, CDialog)
	//{{AFX_MSG_MAP(CSelectExportTables)
	ON_BN_CLICKED(IDB_ABFAELLE, OnAbfaelle)
	ON_BN_CLICKED(IDB_ERZEUGER, OnErzeuger)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSelectExportTables message handlers

BOOL CSelectExportTables::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow ();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSelectExportTables::OnAbfaelle()
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);
	m_btOk.EnableWindow (m_bErzeuger || m_bAbfaelle);		
}

void CSelectExportTables::OnErzeuger()
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);
	m_btOk.EnableWindow (m_bErzeuger || m_bAbfaelle);	
}
