// FirmaPage.cpp : implementation file
//

#include "stdafx.h"			// prec. Header

#include "gak.h"			// CGakApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"			// CGakSet
#include "FirmPage.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CGakSet *g_pErzSet;

/////////////////////////////////////////////////////////////////////////////
// CFirmaPage property page

IMPLEMENT_DYNCREATE(CFirmaPage, CPropertyPage)

CFirmaPage::CFirmaPage() : CPropertyPage(CFirmaPage::IDD)
{
	//{{AFX_DATA_INIT(CFirmaPage)
	//}}AFX_DATA_INIT
}

CFirmaPage::~CFirmaPage()
{
}

void CFirmaPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirmaPage)
	DDX_Control(pDX, IDB_UNTERSCHRIFT, m_btUnterschrift);
	DDX_Control(pDX, IDB_GET_ADDRESS, m_btGetAddress);
	//}}AFX_DATA_MAP
	ASSERT (g_pErzSet != NULL);
//	KK990708
	if ( !g_pErzSet )
		return;
	
	DDX_FieldText (pDX, IDE_FIRMA, g_pErzSet -> m_Firmenname, g_pErzSet);
	DDX_FieldText (pDX, IDE_HNR, g_pErzSet -> m_Firmenhausnummer, g_pErzSet);
	DDX_FieldText (pDX, IDE_ORT, g_pErzSet -> m_Firmenortsname, g_pErzSet);
	DDX_FieldText (pDX, IDE_STRASSE, g_pErzSet -> m_Firmenstrasse, g_pErzSet);
	DDX_FieldText (pDX, IDE_PLZ, g_pErzSet -> m_Firmenpostleitzahl, g_pErzSet);
	DDX_FieldText (pDX, IDE_TELEFON, g_pErzSet -> m_Firmentelefon, g_pErzSet);
	DDX_FieldText (pDX, IDE_TELEFAX, g_pErzSet -> m_Firmentelefax, g_pErzSet);
	DDX_FieldText (pDX, IDE_PARTNER, g_pErzSet -> m_Firmenansprechpartner, g_pErzSet);
	DDX_FieldText (pDX, IDE_BILANZ_NR, g_pErzSet -> m_Bilanznummer, g_pErzSet);
	DDX_FieldText (pDX, IDE_BETREIBER_NR, g_pErzSet -> m_Betreibernummer, g_pErzSet);
	
	if (pDX -> m_bSaveAndValidate)
		g_pErzSet -> m_Unterschrift = 1 == m_btUnterschrift.GetCheck () ? TRUE : FALSE;			
	else		
	{
		m_btUnterschrift.SetCheck (g_pErzSet -> m_Unterschrift);

#ifdef _BRANDENBURG
		if (g_pErzSet -> m_Bilanznummer.IsEmpty ())
		{
			CString strBKennung;
			VERIFY (strBKennung.LoadString (IDS_BILANZ_ERZ_KENNUNG));
			GetDlgItem (IDE_BILANZ_NR) -> SetWindowText (strBKennung);
		}		
#endif		
		SetControlState ();
	}
}

BEGIN_MESSAGE_MAP(CFirmaPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFirmaPage)
	ON_BN_CLICKED(IDB_GET_ADDRESS, OnGetAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CFirmaPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here
//	Feldlängen begrenzen: Firma
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_FIRMA);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (FirmenLaenge);

//	Straße
	pCWnd = (CEdit *) GetDlgItem (IDE_STRASSE);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (StrassenLaenge);

//	HNR
	pCWnd = (CEdit *) GetDlgItem (IDE_HNR);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (HausNrLaenge);

//	PLZ
	pCWnd = (CEdit *) GetDlgItem (IDE_PLZ);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (PlzLaenge);

//	Ort
	pCWnd = (CEdit *) GetDlgItem (IDE_ORT);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (OrtsNamenLaenge);

//	Telefon
	pCWnd = (CEdit *) GetDlgItem (IDE_TELEFON);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (TelefonLaenge);
	
//	Telefax
	pCWnd = (CEdit *) GetDlgItem (IDE_TELEFAX);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (TelefaxLaenge);

//	Betreibernummer
	pCWnd = (CEdit *) GetDlgItem (IDE_BETREIBER_NR);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (NummerLaenge*2);

//	Bilanznummer
	pCWnd = (CEdit *) GetDlgItem (IDE_BILANZ_NR);
	ASSERT (pCWnd != NULL);		

#ifdef _BRANDENBURG
	pCWnd -> LimitText (BilanzNummerLaenge);
#else
	pCWnd -> LimitText (NummerLaenge*2);
#endif

//	Partner
	pCWnd = (CEdit *) GetDlgItem (IDE_PARTNER);
	ASSERT (pCWnd != NULL);		
	pCWnd -> LimitText (PartnerNamenLaenge);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Addresse von Anfallstelle übernehmen
void CFirmaPage::OnGetAddress() 
{
	// TODO: Add your control notification handler code here
	try
	{
		ASSERT (g_pErzSet != NULL);
		CWnd *pCWnd = GetDlgItem (IDE_FIRMA);
		ASSERT (pCWnd != NULL);
		pCWnd -> SetWindowText (g_pErzSet -> m_Anfallstelle);
		pCWnd = GetDlgItem (IDE_HNR);
		ASSERT (pCWnd != NULL);
		pCWnd -> SetWindowText (g_pErzSet -> m_Hausnummer);
		pCWnd = GetDlgItem (IDE_ORT);
		ASSERT (pCWnd != NULL);
		pCWnd -> SetWindowText (g_pErzSet -> m_Ortsname);
		pCWnd = GetDlgItem (IDE_STRASSE);
		ASSERT (pCWnd != NULL);
		pCWnd -> SetWindowText (g_pErzSet -> m_Strasse);
		pCWnd = GetDlgItem (IDE_PLZ);
		ASSERT (pCWnd != NULL);
		pCWnd -> SetWindowText (g_pErzSet -> m_Postleitzahl);
			
		// UpdateData (FALSE);		// Werte anzeigen
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}
}

void CFirmaPage :: SetControlState (void)
{
	ASSERT (g_pErzSet != NULL);

//	Firma
	CWnd *pCWnd = GetDlgItem (IDE_FIRMA);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Straße
	pCWnd = GetDlgItem (IDE_STRASSE);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	HNR
	pCWnd = GetDlgItem (IDE_HNR);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	PLZ
	pCWnd = GetDlgItem (IDE_PLZ);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Ort
	pCWnd = GetDlgItem (IDE_ORT);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Telefon
	pCWnd = GetDlgItem (IDE_TELEFON);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());
	
//	Telefax
	pCWnd = GetDlgItem (IDE_TELEFAX);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Betreibernummer
	pCWnd = GetDlgItem (IDE_BETREIBER_NR);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Bilanznummer
	pCWnd = GetDlgItem (IDE_BILANZ_NR);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Partner
	pCWnd = GetDlgItem (IDE_PARTNER);
	ASSERT (pCWnd != NULL);		
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Button setzen
	m_btGetAddress.EnableWindow (g_pErzSet -> CanUpdate ());	

//	Button Unterschrift
	m_btUnterschrift.EnableWindow (g_pErzSet -> CanUpdate ());	
}
