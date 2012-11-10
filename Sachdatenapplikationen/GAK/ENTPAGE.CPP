// EntPage.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "BranPage.h"	// CBranchPage: Basisklasse
#include "gaksete.h"	// CDaoRecordsetExt	
#include "abfset.h"		// CAbfSet
#include "selset.h"		// CSelectSet
#include "selnum.h"		// CSelNumberDlg	
#include "entsset.h"	// CEntsorgerSet
#include "EntPage.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CAbfSet *g_pAbfSet;

/////////////////////////////////////////////////////////////////////////////
// CEntPage property page
IMPLEMENT_DYNCREATE(CEntPage, CEntsorger1)

CEntPage::CEntPage() : CEntsorger1(CEntPage::IDD)
{
	//{{AFX_DATA_INIT(CEntPage)
	//}}AFX_DATA_INIT
}

CEntPage::~CEntPage()
{
}

void CEntPage::DoDataExchange(CDataExchange* pDX)
{
//	Basisklasse (CBranchPage) wird hier nicht gerufen !
	CPropertyPage::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEntPage)
	DDX_Control(pDX, IDE_FREI_NR, m_edFreiNr);
	DDX_Control(pDX, IDB_EIGEN, m_btEigen);
	DDX_Control(pDX, IDB_FREI, m_btFrei);
	DDX_Control(pDX, IDE_STRASSE, m_edStrasse);
	DDX_Control(pDX, IDE_PLZ, m_edPlz);
	DDX_Control(pDX, IDE_ORT, m_edOrt);
	DDX_Control(pDX, IDE_ART, m_edArt);
	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	DDX_Control(pDX, IDE_NAME, m_edName);
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	//}}AFX_DATA_MAP

	ASSERT (g_pAbfSet != NULL);
	if (g_pAbfSet->IsValid())
	{
		DDX_FieldText (pDX, IDE_NUMMER, g_pAbfSet -> m_Entsorgernummer, g_pAbfSet);
		DDX_FieldText (pDX, IDE_BEMERKUNGEN, g_pAbfSet -> m_Entsorgerbemerkungen, g_pAbfSet);
		DDX_FieldText (pDX, IDE_PARTNER, g_pAbfSet -> m_Entsorgungspartner, g_pAbfSet);
		DDX_FieldText (pDX, IDE_TELEFON, g_pAbfSet -> m_Entsorgungstelefon, g_pAbfSet);
		DDX_FieldText (pDX, IDE_TELEFAX, g_pAbfSet -> m_Entsorgungstelefax, g_pAbfSet);
		DDX_FieldText (pDX, IDE_FREI_NR, g_pAbfSet -> m_Freistellungsnummer, g_pAbfSet);

		if (pDX -> m_bSaveAndValidate)		// Daten schreiben
		{
			g_pAbfSet -> m_Entsorgungsfreistellung = 1 == m_btFrei.GetCheck () ? TRUE : FALSE;
			g_pAbfSet -> m_Eigenentsorgung = 1 == m_btEigen.GetCheck () ? TRUE : FALSE;	
		}
		else
		{
			if (m_pSet)		// Daten lesen
				OutputEntsParam (g_pAbfSet -> m_Entsorgernummer);						
			
			m_btEigen.SetCheck (g_pAbfSet -> m_Eigenentsorgung);
			m_btFrei.SetCheck (g_pAbfSet -> m_Entsorgungsfreistellung);

			SetControlState ();
		}
	}
	else
	{
		CString strDummy;
		DDX_Text (pDX, IDE_NUMMER, strDummy);
		DDX_Text (pDX, IDE_BEMERKUNGEN, strDummy);
		DDX_Text (pDX, IDE_PARTNER, strDummy);
		DDX_Text (pDX, IDE_TELEFON, strDummy);
		DDX_Text (pDX, IDE_TELEFAX, strDummy);
		DDX_Text (pDX, IDE_FREI_NR, strDummy);

		// nur lesen handhaben
		if (!pDX -> m_bSaveAndValidate)
		{
			SetControlState (true);
		}
	}
}

BEGIN_MESSAGE_MAP(CEntPage, CEntsorger1)
	//{{AFX_MSG_MAP(CEntPage)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeNummer)
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeName)
	ON_BN_CLICKED(IDB_EIGEN, OnEigenEntsorgung)
	ON_BN_CLICKED(IDB_FREI, OnFreistellung)
	ON_EN_CHANGE(IDE_FREI_NR, OnChangeFreiNr)
	ON_BN_CLICKED(IDB_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntPage message handlers
/*	now defined in CEntsorger1
void CEntPage::OnChange() 
{
	Change (((CGakApp *)AfxGetApp ())->EntsorgerDefaultSQL(), IDS_ENTS_CAPTION); 	
}
*/
void CEntPage::SetControlState (bool bDisableAll)
{
	ASSERT (g_pAbfSet != NULL);

	m_edNummer.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_btChange.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_btEigen.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
//	m_edVerfahren.EnableWindow (g_pAbfSet -> CanUpdate ());
	m_edName.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edArt.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edStrasse.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edPlz.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edOrt.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_btFrei.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	
//	Bemerkungen
	CWnd *pCWnd = GetDlgItem (IDE_BEMERKUNGEN);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 

//	Partner
	pCWnd = GetDlgItem (IDE_PARTNER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 

//	Telefon
	pCWnd = GetDlgItem (IDE_TELEFON);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 

//	Telefax
	pCWnd = GetDlgItem (IDE_TELEFAX);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 

//	Freistellungsnummer
	pCWnd = GetDlgItem (IDE_FREI_NR);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 

//	Verfahren
/*
	pCWnd = GetDlgItem (IDB_CHANGE_VERF);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate ()); 
*/
}
/* now defined in CEntsorger1
//	Set öffnen
int CEntPage::OpenSet ()
{
	if (m_pSet)
		return 0;

	try
	{
		ASSERT (NULL != g_pAbfSet);
		m_pSet = new CEntsorgerSet (g_pAbfSet -> m_pDatabase, 
									((CGakApp *)AfxGetApp ())->EntsorgerDefaultSQL());
		m_pSet -> Open ();
		return 0;
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	return -1;
}
*/
//	Angaben des akt. Entsorgers ausgeben
void CEntPage::OutputEntsParam (const char *pNummer)
{
	ASSERT (NULL != pNummer && AfxIsValidString (pNummer));

	try	
	{
		ASSERT (NULL != m_pSet);
		if (!m_pSet -> IsOpen ())
			return;

	//	Firmenname ausgeben
		if (OutputName (pNummer))
		{
			CEntsorgerSet *pSet = (CEntsorgerSet *) m_pSet;
			m_edPlz.SetWindowText (pSet -> m_Postleitzahl);
			m_edOrt.SetWindowText (pSet -> m_Ortsname);
			m_edStrasse.SetWindowText (pSet -> m_Strasse);
			m_edArt.SetWindowText (pSet -> m_Anlage);
			return;
		}
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	m_edName.SetWindowText ("");
	m_edPlz.SetWindowText ("");
	m_edOrt.SetWindowText ("");
	m_edStrasse.SetWindowText ("");
	m_edArt.SetWindowText ("");
}
// neue Nummer
LONG CEntPage::OnChangeNummer(UINT uiMsg, LONG lText)
{
	CEntsorger1:: OnChangeNummer (uiMsg, lText);

	if (IsWindowVisible ())
	{
		m_btEigen.SetCheck (0);
		OutputEntsParam ((const char *)lText);
	}

	return TRUE;
}

//	neuer Name gesendet
LONG CEntPage:: OnChangeName(UINT, LONG)
{
//	wird oben eingetragen
	return TRUE;
}

/*
// auf akt. Satz gehen
BOOL CEntPage::FindActRecord (void)
{
	try
	{
		ASSERT (g_pAbfSet != NULL);
		if (-1 == OpenSet ())
			return FALSE;

		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, g_pAbfSet -> m_Entsorgernummer);
		return m_pSet -> FindFirst (strFind);
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	return FALSE;
}

//	lese Firmenname
CString CEntPage::GetName ()
{
	if (FindActRecord ())
		return m_pSet -> m_Name;
	else
		return "";
}		

CString CEntPage::GetStrasse (void)
{
	if (FindActRecord ())
		return ((CEntsorgerSet *) m_pSet) -> m_Strasse;
	else
		return "";		
}

CString CEntPage::GetPlz (void)
{
	if (FindActRecord ())
		return ((CEntsorgerSet *) m_pSet) -> m_Postleitzahl;
	else
		return "";			
}

CString CEntPage::GetOrt (void)
{
	if (FindActRecord ())
		return ((CEntsorgerSet *) m_pSet) -> m_Ortsname;
	else
		return "";			
}

CString CEntPage::GetArt (void)
{
	if (FindActRecord ())
		return ((CEntsorgerSet *) m_pSet) -> m_Anlage;
	else
		return "";			
}

CString CEntPage::GetVerwertung (void)
{
	CString strRes;
	try
	{
		ASSERT (NULL != g_pAbfSet);
		VERIFY (strRes.LoadString (g_pAbfSet -> m_Verwertung ? IDS_JA : IDS_NEIN));
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	return strRes;;
}
*/

BOOL CEntPage::OnInitDialog() 
{
	CEntsorger1::OnInitDialog();
	
//	TODO: Add extra initialization here
//	Nummer
	m_edName.LimitText (NamenLaenge);

//	Ansprechpartner
	CEdit *pWnd = (CEdit *)GetDlgItem (IDE_PARTNER);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (PartnerNamenLaenge); 

//	Telefon
	pWnd = (CEdit *)GetDlgItem (IDE_TELEFON);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (TelefonLaenge); 

//	Telefax
	pWnd = (CEdit *)GetDlgItem (IDE_TELEFAX);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (TelefaxLaenge); 
	
//	Freistellungsnummer
	pWnd = (CEdit *)GetDlgItem (IDE_FREI_NR);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (NummerLaenge * 2); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntPage::OnFreistellung() 
{
	// TODO: Add your control notification handler code here
	if (m_btFrei.GetCheck () == 0)
	{
		m_edFreiNr.SetWindowText ("");
		m_edFreiNr.EnableWindow (FALSE);
	}
	else
		m_edFreiNr.EnableWindow (TRUE);
}

void CEntPage::OnEigenEntsorgung() 
{
	// TODO: Add your control notification handler code here
	try
	{
		if (m_btEigen.GetCheck () == 1)
		{
			CString strSelbst;
			VERIFY (strSelbst.LoadString (IDS_SELBST));
			m_edNummer.SetWindowText (strSelbst);
			m_edName.SetWindowText ("");
			m_edArt.SetWindowText ("");
			m_edStrasse.SetWindowText ("");
			m_edOrt.SetWindowText ("");
			m_edPlz.SetWindowText ("");
		}
		else
			m_edNummer.SetWindowText ("");			
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}		
}

void CEntPage::OnChangeFreiNr() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edFreiNr.GetWindowText (strText);
	if (strText.IsEmpty ())
		m_btFrei.SetCheck (0);
	else
		m_btFrei.SetCheck (1);		
}

/*
void CEntPage::OnChangeVerfahren() 
{
	ASSERT (NULL != m_pSet);
	ASSERT (m_pSet -> IsOpen ());

	try
	{
	//	Set öffnen
		CSelectSet Set(m_pSet -> m_pDatabase, ((CGakApp *)AfxGetApp ())-> VerfahrenDefaultSQL());
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	//	neues Verfahren vom Nutzer eingeben
		CString strSel;
		m_edVerfahren.GetWindowText (strSel);
		CSelNumberDlg Dlg (this, &Set, ((CGakApp *)AfxGetApp ())-> VerfahrenDefaultSQL(), IDS_VERFAHREN_CAPTION,
						   FALSE, strSel);
		if ((IDOK == Dlg.DoModal ()) && (!Dlg.m_strNumber.IsEmpty ()))
			m_edVerfahren.SetWindowText (Dlg.m_strNumber);
		
	//	Set schließen
		if (Set.IsOpen ())
			Set.Close ();		
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}
*/

BOOL CEntPage::GetStringData(CString& strTarget)
{
	// erstmal aktualisieren
	UpdateData(true);

	ADDWINDOWTEXT(m_edNummer, strTarget);
	ADDWINDOWTEXT(m_edName, strTarget);
	ADDWINDOWTEXT(m_edStrasse, strTarget);
	ADDWINDOWTEXT(m_edPlz, strTarget);
	ADDWINDOWTEXT(m_edOrt, strTarget);
	ADDWINDOWTEXT(m_edArt, strTarget);
	ADDWINDOWTEXT(m_edFreiNr, strTarget);

	if ((NULL != g_pAbfSet) && g_pAbfSet->IsValid())
	{
		ADDTEXT(strTarget, g_pAbfSet -> m_Entsorgungspartner);
		ADDTEXT(strTarget, g_pAbfSet -> m_Entsorgungstelefon);
		ADDTEXT(strTarget, g_pAbfSet -> m_Entsorgungstelefax);
		ADDTEXT(strTarget, g_pAbfSet -> m_Freistellungsnummer);
		ADDTEXT(strTarget, CString(""));	// Leerzeile
		ADDTEXT(strTarget, g_pAbfSet -> m_Entsorgerbemerkungen);
	}

	return TRUE;
}