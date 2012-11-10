// EnterNr.cpp : implementation file
//

#include "stdafx.h"			// vorübersetzter Header
#include "gak.h"			// CGakApp
#include "numedit.h"		// CErzNrEdit
#include "EnterNr.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterNr dialog


CEnterNr::CEnterNr(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterNr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterNr)
	//}}AFX_DATA_INIT
}


void CEnterNr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterNr)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDE_NUMBER, m_edNumber);
	DDX_Control(pDX, IDB_LIKE, m_btLike);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterNr, CDialog)
	//{{AFX_MSG_MAP(CEnterNr)
	ON_EN_CHANGE(IDE_NUMBER, OnChangeNumber)
	ON_BN_CLICKED(IDB_EQ, OnEq)
	ON_BN_CLICKED(IDB_GR, OnGr)
	ON_BN_CLICKED(IDB_GR_EQ, OnGrEq)
	ON_BN_CLICKED(IDB_LESS, OnLess)
	ON_BN_CLICKED(IDB_LESS_EQ, OnLessEq)
	ON_BN_CLICKED(IDB_LIKE, OnLike)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterNr message handlers

void CEnterNr::OnOK() 
{
//	TODO: Add extra validation here
	try
	{
		CString strNummer, strOperator;
		if (!strOperator.LoadString (m_iOperator))
			AfxThrowResourceException ();
		m_edNumber.GetWindowText (strNummer);
		if (IDS_LIKE == m_iOperator)
			strNummer = "*" + strNummer + "*";
		AfxFormatString2 (m_strExpression, IDS_WHERE_KLAUSEL, 
						  strOperator, strNummer);
		CDialog::OnOK();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		EndDialog (IDCANCEL);
	}
}

void CEnterNr::OnChangeNumber() 
{
//	TODO: Add your control notification handler code here
	if (m_edNumber.LineLength () > 0)
		m_btOk.EnableWindow (TRUE);
	else
		m_btOk.EnableWindow (FALSE);
}

BOOL CEnterNr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	m_edNumber.LimitText (ErzNummerLaenge);
	m_btLike.SetCheck (1);
	m_iOperator = IDS_LIKE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnterNr::OnEq() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_EQUAL;
}

void CEnterNr::OnGr() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_GREATER;
}

void CEnterNr::OnGrEq() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_GREATER_EQUAL;
}

void CEnterNr::OnLess() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_LESS;
}

void CEnterNr::OnLessEq() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_LESS_EQUAL;
}

void CEnterNr::OnLike() 
{
	// TODO: Add your control notification handler code here
	m_iOperator = IDS_LIKE;	
}

BOOL CEnterNr::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;

	// return CDialog::OnHelpInfo(pHelpInfo);
}
