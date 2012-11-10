// afidlg.cpp : implementation file
//
#include "stdafx.h"			//	prec. Header	
#include "gak.h"			//	CGakApp
#include "resource.h"		//	Ressource
#include "KreisSet.h"		//	CKreisSet

#include "afidlg.h"			//	zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAfiDlg dialog
CAfiDlg::CAfiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAfiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAfiDlg)
	m_bOnlySA = FALSE;
	m_bOnlyNotExported = FALSE;
	//}}AFX_DATA_INIT
	m_strGKZ = "";
	m_bType = TRUE;
}

void CAfiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAfiDlg)
	DDX_Control(pDX, IDC_KREISE, m_cbKreise);
	DDX_Control(pDX, IDC_AFIS, m_cbAfis);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDB_AFIS, m_btAfis);	
	DDX_Check(pDX, IDB_SONDER_ABF, m_bOnlySA);
	DDX_Check(pDX, IDC_ONLYNOTEXPORTED, m_bOnlyNotExported);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAfiDlg, CDialog)
	//{{AFX_MSG_MAP(CAfiDlg)
	ON_CBN_SELCHANGE(IDC_AFIS, OnSelchangeAfis)
	ON_CBN_SELCHANGE(IDC_KREISE, OnSelchangeKreise)
	ON_BN_CLICKED(IDB_AFIS, OnAfis)
	ON_BN_CLICKED(IDB_KREISE, OnKreise)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAfiDlg message handlers
void CAfiDlg::OnSelchangeAfis()
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_cbAfis.GetCurSel () >= 0);
}

void CAfiDlg::OnSelchangeKreise()
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_cbKreise.GetCurSel () >= 0);	
}

void CAfiDlg::OnAfis()
{
	// TODO: Add your control notification handler code here
	m_bType = TRUE; 
	m_cbAfis.EnableWindow (TRUE);
	m_cbKreise.EnableWindow (FALSE);
}

void CAfiDlg::OnKreise()
{
	// TODO: Add your control notification handler code here
	m_bType = FALSE;	            
	m_cbAfis.EnableWindow (FALSE);
	m_cbKreise.EnableWindow (TRUE);
}

//	Fenster in Bildschirmmitte pos.    
//	Comboboxen füllen
BOOL CAfiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
//	Kreise ausgeben	
	CWaitCursor wc;
	CKreisSet Set;
	Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);
	while (!Set.IsEOF ())	
	{
		if (m_cbKreise.AddString (Set.m_Name) < 0)
			AfxThrowUserException ();	                    
	                    
		Set.MoveNext ();
	}
#pragma MSG("JG")
	Set.Close();
	
//	Afis ausgeben
	CKreisSet ASet;
	CString strSel;
	AfxFormatString1 (strSel, IDS_SELECT_AFIS, ((CGakApp *)AfxGetApp ()) -> KreisDefaultSQL ());
	ASet.m_nFields = 1;
	ASet.Open (dbOpenSnapshot, strSel, dbForwardOnly);			                             
	while (!ASet.IsEOF ())	
	{
		if (m_cbAfis.AddString (ASet.m_AfI) < 0)
			AfxThrowUserException ();	                    
	                    
		ASet.MoveNext ();
	}
#pragma MSG("JG")
	ASet.Close();	
	
	m_btAfis.SetCheck (1);
	m_bType = TRUE;
	m_cbAfis.EnableWindow (TRUE);
	m_cbKreise.EnableWindow (FALSE);
	CenterWindow ();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAfiDlg::OnOK()
{
//	lese Gemeindekennzahlen
	CKreisSet Set;
	CString strSel;
	if (m_bType)
	{
		m_cbAfis.GetLBText (m_cbAfis.GetCurSel (), strSel);
		AfxFormatString1 (Set.m_strFilter, IDS_SELECT_AFI, strSel); 
	}				
	else                                                   
	{
		m_cbKreise.GetLBText (m_cbKreise.GetCurSel (), strSel); 
		AfxFormatString1 (Set.m_strFilter, IDS_SELECT_NAME, strSel); 
	}		
	
	Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);			                             	
	while (!Set.IsEOF ())
	{               
		if (m_strGKZ.IsEmpty ())
			m_strGKZ = Set.m_Nummer;
		else			
			m_strGKZ += "," + Set.m_Nummer;
		
		Set.MoveNext ();
	}
	Set.Close ();
	
	CDialog::OnOK();
}
    
