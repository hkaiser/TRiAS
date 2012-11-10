// AnfallStelle.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGapApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"			// CGakSet
#include "selset.h"			// CSelectSet
#include "selnum.h"			// CSelNumberDlg
#include "Anfpage.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CGakSet *g_pErzSet;

/////////////////////////////////////////////////////////////////////////////
// CAnfallStelle property page

IMPLEMENT_DYNCREATE(CAnfallStelle, CPropertyPage)

CAnfallStelle::CAnfallStelle() : CPropertyPage(CAnfallStelle::IDD)
{
	//{{AFX_DATA_INIT(CAnfallStelle)
	//}}AFX_DATA_INIT
	m_pNumberDlg = NULL;
	m_pSet = NULL;
	m_pKreisSet = NULL;
}

CAnfallStelle::~CAnfallStelle()
{
	DELETE_OBJ (m_pNumberDlg);
	DELETE_OBJ (m_pSet);

	if (m_pKreisSet && m_pKreisSet -> IsOpen ())
		m_pKreisSet -> Close ();

	DELETE_OBJ (m_pKreisSet);
}

void CAnfallStelle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnfallStelle)
	DDX_Control(pDX, IDE_KREIS_KUERZEL, m_edKreisK);
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Control(pDX, IDE_GKZ, m_edGKZ);
	DDX_Control(pDX, IDE_ORT, m_edOrtsName);
	//}}AFX_DATA_MAP
	ASSERT (g_pErzSet != NULL);
	DDX_FieldText (pDX, IDE_ANFALLSTELLE, g_pErzSet -> m_Anfallstelle, g_pErzSet);
	DDX_FieldText (pDX, IDE_BETRIEB, g_pErzSet -> m_Betriebsstaette, g_pErzSet);
	DDX_FieldText (pDX, IDE_STRASSE, g_pErzSet -> m_Strasse, g_pErzSet);
	DDX_FieldText (pDX, IDE_HNR, g_pErzSet -> m_Hausnummer, g_pErzSet);
	DDX_FieldText (pDX, IDE_ORT, g_pErzSet -> m_Ortsname, g_pErzSet);
	DDX_FieldText (pDX, IDE_GKZ, g_pErzSet -> m_Gemeindekennzahl, g_pErzSet);
	DDX_FieldText (pDX, IDE_PLZ, g_pErzSet -> m_Postleitzahl, g_pErzSet);
	DDX_FieldText (pDX, IDE_COMMENT, g_pErzSet -> m_Bemerkungen, g_pErzSet);
//	DDX_FieldText (pDX, IDE_BB_NUMMER, g_pErzSet -> m_Betriebsbeauftragtennummer, g_pErzSet);

//	wenn neue Werte gelesen werden
	if (!pDX -> m_bSaveAndValidate)
		SetControlState ();
}

BEGIN_MESSAGE_MAP(CAnfallStelle, CPropertyPage)
	//{{AFX_MSG_MAP(CAnfallStelle)
	ON_BN_CLICKED(IDB_CHANGE, OnChangeGKZ)
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeGemeindeName)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeGemeindeNummer)
	ON_MESSAGE (IDM_SEND_DELETEOBJ, OnDeleteNumberDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnfallStelle message handlers

BOOL CAnfallStelle::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here --> Eingabelängen begrenzen (Anfallstelle)
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_ANFALLSTELLE);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (AnfallLaenge);

//	Betrieb
	pCWnd = (CEdit *) GetDlgItem (IDE_BETRIEB);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (BetriebLaenge);

//	Straße
	pCWnd = (CEdit *) GetDlgItem (IDE_STRASSE);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (StrassenLaenge);

//	Hausnummer
	pCWnd = (CEdit *) GetDlgItem (IDE_HNR);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (HausNrLaenge);

//	PLZ
	pCWnd = (CEdit *) GetDlgItem (IDE_PLZ);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (PlzLaenge);

//	Ortsname
	m_edOrtsName.LimitText (OrtsNamenLaenge);

//	GKZ
	m_edGKZ.LimitText (GkzLaenge);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnfallStelle::OnChangeGKZ() 
{
//	TODO: Add your control notification handler code here
	try
	{
		if (!m_pNumberDlg)
		{
			ASSERT (NULL != m_pSet);
			ASSERT_VALID (m_pSet);
			ASSERT (m_pSet -> IsOpen ());
			m_pNumberDlg = new CSelNumberDlg (this, m_pSet, IDS_GEMEINDE_CAPTION,
											((CGakApp *)AfxGetApp ()) -> GemeindenDefaultSQL (), 
											  NULL, 0, TRUE);
			if (!m_pNumberDlg -> Create (IDD_SEL_NUMMER))
				AfxThrowMemoryException ();
		}			

	//	Fenster aktivieren
		m_pNumberDlg -> ShowWindow (SW_SHOWNORMAL);	

	//	aktuelle Selektion setzen
		CString strOldName, strOldGkz;
		m_edGKZ.GetWindowText (strOldGkz);
		m_edOrtsName.GetWindowText (strOldName);
		m_pNumberDlg -> StoreSelection (strOldGkz, strOldName);

	//	Fenster aktivieren
		m_pNumberDlg -> SetFocus ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
}

void CAnfallStelle::SetControlState (void)
{
//	TODO: Add your specialized code here and/or call the base class
//	Control ggf. aktiv./deakt.
	ASSERT (g_pErzSet != NULL);
	CWnd *pCWnd = GetDlgItem (IDE_ANFALLSTELLE);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Betrieb
	pCWnd = GetDlgItem (IDE_BETRIEB);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Straße
	pCWnd = GetDlgItem (IDE_STRASSE);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());

//	Hausnummer
	pCWnd = GetDlgItem (IDE_HNR);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	

//	PLZ
	pCWnd = GetDlgItem (IDE_PLZ);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	

//	Bemerkungs-Feld
	pCWnd = GetDlgItem (IDE_COMMENT);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());		

//	Ändern-Button
	m_btChange.EnableWindow (g_pErzSet -> CanUpdate ());	

//	Kreiskürzel setzen
	m_edKreisK.SetWindowText (SetKreisInfo (g_pErzSet -> m_Gemeindekennzahl));

//	Spin-Button akt.
	/*
	pCWnd = GetDlgItem (IDC_SPIN_BB_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	
	*/

//	Ort
	pCWnd = GetDlgItem (IDE_ORT);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	

//	GKZ
	pCWnd = GetDlgItem (IDE_GKZ);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	

//	Kreiskürzel
	pCWnd = GetDlgItem (IDE_KREIS_KUERZEL);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	

//	Beauftragten-Nummer
/*
	pCWnd = GetDlgItem (IDE_BB_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pErzSet -> CanUpdate ());	
*/
}

BOOL CAnfallStelle::OnKillActive() 
{
	if (!CPropertyPage::OnKillActive())
		return FALSE;

	// TODO: Add your specialized code here and/or call the base class
	if (m_pNumberDlg && m_pNumberDlg -> IsWindowVisible ())
		m_pNumberDlg -> ShowWindow (SW_HIDE);		

	return TRUE;
}

//	Fenster löscht sich selbst
LONG CAnfallStelle::OnDeleteNumberDlg (UINT, LONG)
{
	m_pNumberDlg = NULL;	
	return TRUE;
}

CString CAnfallStelle::SetKreisInfo (const char *pGKZ)
{
	if (!pGKZ || !*pGKZ || !m_pKreisSet)
		return "";

	ASSERT (m_pKreisSet -> IsOpen ());
	CString strKK;
	try
	{
		CString strOld, strNew;
		strOld = pGKZ;
		strNew  = strOld.Left (5);
		
	//	Kürzel suchen
		COleVariant varNummer (strNew, VT_BSTRT);
		if (m_pKreisSet -> Seek ("=", &varNummer))
		{
		//	Kürzel lesen
			COleVariant varKK;
			CString strFieldName;
			VERIFY (strFieldName.LoadString (IDS_KUERZEL));
			varKK = m_pKreisSet -> GetFieldValue (strFieldName);
			if (VT_BSTR == varKK.vt)
				strKK = (const char *) varKK.pbVal;
		}
	}
	catch (CDaoException *e)
	{
		DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	
	return strKK;
}

//	neue Gemeindenummer gesendet
LONG CAnfallStelle:: OnChangeGemeindeNummer(UINT, LONG lText)
{
	if (IsWindowVisible ())
	{
		m_edGKZ.SetWindowText ((const char *) lText);
	
	//	Kreiskürzel setzen
		m_edKreisK.SetWindowText (SetKreisInfo ((const char *) lText));
	}

	return TRUE;
}

//	neur Gemeindename gesendet
LONG CAnfallStelle:: OnChangeGemeindeName(UINT, LONG lText)
{
	if (IsWindowVisible ())
		m_edOrtsName.SetWindowText ((const char *) lText);

	return TRUE;
}

//	Set Öffnen
int CAnfallStelle::OpenSet ()
{
	if (m_pSet)
		return 0;

	try
	{
		ASSERT (g_pErzSet != NULL);
		m_pSet = new CSelectSet (g_pErzSet -> m_pDatabase, 
							   ((CGakApp *)AfxGetApp ()) -> GemeindenDefaultSQL ());
		m_pSet -> Open (dbOpenSnapshot);
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

int CAnfallStelle::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	KK990714
	if ( !g_pErzSet)
		return -1;

//	Kreis-Set öffnen	
	try
	{
		ASSERT (g_pErzSet != NULL);
		
		m_pKreisSet = new CDaoRecordset (g_pErzSet -> m_pDatabase);
		m_pKreisSet -> Open (dbOpenTable, 
							((CGakApp*)AfxGetApp())->KreisDefaultSQL(), 
							dbReadOnly);
		CString strIndex;
		VERIFY (strIndex.LoadString (IDS_NUMMER));
		m_pKreisSet -> SetCurrentIndex (strIndex);
	}
	catch (CDaoException *e)
	{
		// :: DisplayDaoException (e);
		e -> Delete ();

	//	Tabelle nicht vorhanden
		DELETE_OBJ (m_pKreisSet);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return -1;
	}
	
	return OpenSet ();
}

/*
void CAnfallStelle::OnDeltaposSpinBbNummer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

//	akt. Wert bestimmen
	CString strActVal;
	CWnd *pWnd = GetDlgItem (IDE_BB_NUMMER);
	ASSERT (NULL != pWnd);
	pWnd -> GetWindowText (strActVal);
	long lNummer = strActVal.IsEmpty () ? 0 : atol (strActVal);

//	neuen Wert berechnen
	if (pNMUpDown -> iDelta < 0)
		lNummer++;
	else
		lNummer--;
	
	if (lNummer < 0)
		lNummer = 0;
	char Buffer [20] = "";
	ltoa (lNummer, Buffer, 10);
	pWnd -> SetWindowText (Buffer);

	*pResult = 0;
}
*/

