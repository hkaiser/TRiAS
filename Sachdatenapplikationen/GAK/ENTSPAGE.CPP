// EntsPage.cpp : implementation file
//

#include "stdafx.h"

#include "gak.h"			// CGakApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"			// CGakSet
#include "EntsPage.h"		// zugeh. Header


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CGakSet *g_pErzSet;

/////////////////////////////////////////////////////////////////////////////
// CEntsPage property page

IMPLEMENT_DYNCREATE(CEntsPage, CPropertyPage)

CEntsPage::CEntsPage() : CPropertyPage(CEntsPage::IDD)
{
	//{{AFX_DATA_INIT(CEntsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CEntsPage::~CEntsPage()
{
}

void CEntsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntsPage)
	DDX_Control(pDX, IDB_LIEGT_VOR, m_btLiegtVor);
	DDX_Control(pDX, IDE_ANUMMER, m_edANummer);
	//}}AFX_DATA_MAP
	ASSERT (g_pErzSet != NULL);
	DDX_FieldText (pDX, IDE_BIMSCH_NUMMER, g_pErzSet -> m_Bimschnummer, g_pErzSet);
	DDX_FieldText (pDX, IDE_BIMSCH_NUMMERG, g_pErzSet -> m_Bimschgenehmigungsnummer, g_pErzSet);
	DDX_FieldText (pDX, IDE_ANUMMER, g_pErzSet -> m_Antragsnummer, g_pErzSet);
	// DDX_FieldRadio (pDX, IDB_LIEGT_VOR, g_pErzSet -> m_Anzeigenachweisverordnung, g_pErzSet);
	DDX_FieldCBString (pDX, IDC_SPALTE, g_pErzSet -> m_Bimschspalte, g_pErzSet);
	
	if (pDX -> m_bSaveAndValidate)		// Daten schreiben
		g_pErzSet -> m_Anzeigenachweisverordnung = 1 == m_btLiegtVor.GetCheck () ? TRUE : FALSE;		
	else								// Daten lesen
	{
		SetControlState ();
		m_btLiegtVor.SetCheck (g_pErzSet -> m_Anzeigenachweisverordnung);
	}
}

BEGIN_MESSAGE_MAP(CEntsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CEntsPage)
	ON_BN_CLICKED(IDB_LIEGT_VOR, OnLiegtVor)
	ON_EN_CHANGE(IDE_ANUMMER, OnChangeAnummer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntsPage message handlers

BOOL CEntsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
//	Bimschnummer
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_BIMSCH_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (KurzNummerLaenge);

//	Bimschgenehmigungsnummer
	pCWnd = (CEdit *) GetDlgItem (IDE_BIMSCH_NUMMERG);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (NummerLaenge * 3);

//	Antragsnummer
	pCWnd = (CEdit *) GetDlgItem (IDE_ANUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (NummerLaenge * 2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntsPage :: SetControlState (void)
{
//	Bimschnummer
	CWnd *pCWnd = GetDlgItem (IDE_BIMSCH_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ()); 

//	Bimschgenehmigungsnummer
	pCWnd = GetDlgItem (IDE_BIMSCH_NUMMERG);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ()); 

//	Antragsnummer
	pCWnd = (CEdit *) GetDlgItem (IDE_ANUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate () && g_pErzSet -> m_Anzeigenachweisverordnung); 

//	Spalte
	pCWnd = GetDlgItem (IDC_SPALTE);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ()); 

//	Liegt vor
	pCWnd = GetDlgItem (IDB_LIEGT_VOR);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ()); 
}

void CEntsPage::OnLiegtVor() 
{
//	TODO: Add your control notification handler code here
	if (0 == m_btLiegtVor.GetCheck ()) 
	{
		m_edANummer.SetWindowText ("");
		m_edANummer.EnableWindow (FALSE);
	}
	else
		m_edANummer.EnableWindow (TRUE);
}

void CEntsPage::OnChangeAnummer() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edANummer.GetWindowText (strText);
	if (strText.IsEmpty ())
		m_btLiegtVor.SetCheck (0);
	else
		m_btLiegtVor.SetCheck (1);
}
