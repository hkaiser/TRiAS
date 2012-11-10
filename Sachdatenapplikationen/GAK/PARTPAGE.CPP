// PartPage.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"			// CGakSet
#include "PartPage.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CGakSet *g_pErzSet;

/////////////////////////////////////////////////////////////////////////////
// CPartnerPage property page

IMPLEMENT_DYNCREATE(CPartnerPage, CPropertyPage)

CPartnerPage::CPartnerPage() : CPropertyPage(CPartnerPage::IDD)
{
	//{{AFX_DATA_INIT(CPartnerPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPartnerPage::~CPartnerPage()
{
}

void CPartnerPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPartnerPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	ASSERT (g_pErzSet != NULL);
	DDX_FieldText (pDX, IDE_TELEFON, g_pErzSet -> m_Partnertelefon, g_pErzSet);
	DDX_FieldText (pDX, IDE_TELEFAX, g_pErzSet -> m_Partnertelefax, g_pErzSet);
	DDX_FieldText (pDX, IDE_NAME, g_pErzSet -> m_Ansprechpartner, g_pErzSet);
	DDX_FieldText (pDX, IDE_BB_TELEFON, g_pErzSet -> m_Betriebsbeauftragtentelefon, g_pErzSet);
	DDX_FieldText (pDX, IDE_BB_TELEFAX, g_pErzSet -> m_Betriebsbeauftragtentelefax, g_pErzSet);
	DDX_FieldText (pDX, IDE_BB_NAME, g_pErzSet -> m_Betriebsbeauftragter, g_pErzSet);
	DDX_FieldText (pDX, IDE_FUNKTION, g_pErzSet -> m_Partnerfunktion, g_pErzSet);
//	DDX_FieldText (pDX, IDE_BB_NUMMER, g_pErzSet -> m_Betriebsbeauftragtennummer, g_pErzSet);

	if (!pDX -> m_bSaveAndValidate)
		SetControlState ();
}

BEGIN_MESSAGE_MAP(CPartnerPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPartnerPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPartnerPage message handlers

BOOL CPartnerPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here --> Feldbegrenzungen
//	Telefon
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_TELEFON);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (TelefonLaenge);

//	Telefax
	pCWnd = (CEdit *) GetDlgItem (IDE_TELEFAX);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (TelefaxLaenge);

//	Name
	pCWnd = (CEdit *) GetDlgItem (IDE_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (PartnerNamenLaenge);

//	Telefon
	pCWnd = (CEdit *) GetDlgItem (IDE_BB_TELEFON);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (TelefonLaenge);

//	Telefax
	pCWnd = (CEdit *) GetDlgItem (IDE_BB_TELEFAX);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (TelefaxLaenge);

//	Name
	pCWnd = (CEdit *) GetDlgItem (IDE_BB_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (PartnerNamenLaenge);

//	Funktion
	pCWnd = (CEdit *) GetDlgItem (IDE_FUNKTION);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (PartnerNamenLaenge);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPartnerPage :: SetControlState (void)
{
	ASSERT (g_pErzSet != NULL);
//	Telefon
	CWnd *pCWnd = GetDlgItem (IDE_TELEFON);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Telefax
	pCWnd = GetDlgItem (IDE_TELEFAX);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Name
	pCWnd = GetDlgItem (IDE_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Telefon
	pCWnd = GetDlgItem (IDE_BB_TELEFON);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Telefax
	pCWnd = GetDlgItem (IDE_BB_TELEFAX);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Name
	pCWnd = GetDlgItem (IDE_BB_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Funktion
	pCWnd = GetDlgItem (IDE_FUNKTION);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Beauftragter
/*
	pCWnd = (CEdit *) GetDlgItem (IDE_BB_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());
*/
}
