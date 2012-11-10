// TransPge.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "BranPage.h"	// CBranchPage: Basisklasse
#include "gaksete.h"	// CDaoRecordsetExt	
#include "abfset.h"		// CAbfSet
#include "selset.h"		// CSelectSet
#include "transset.h"	// CTranspSet
#include "TransPge.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CAbfSet *g_pAbfSet;

// CTranspPage property page

IMPLEMENT_DYNCREATE(CTranspPage, CBranchPage)

CTranspPage::CTranspPage() : CBranchPage(CTranspPage::IDD)
{
	//{{AFX_DATA_INIT(CTranspPage)
	//}}AFX_DATA_INIT
}

CTranspPage::~CTranspPage()
{
}

void CTranspPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranspPage)
	DDX_Control(pDX, IDE_BEMERKUNGEN, m_edBemerkungen);
	DDX_Control(pDX, IDB_EIGENTRANSPORT, m_btEigen);
	DDX_Control(pDX, IDE_STRASSE, m_edStrasse);
	DDX_Control(pDX, IDE_PLZ, m_edPlz);
	DDX_Control(pDX, IDE_ORT, m_edOrt);
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	DDX_Control(pDX, IDE_NAME, m_edName);
	//}}AFX_DATA_MAP

	ASSERT (g_pAbfSet != NULL);
	if (g_pAbfSet->IsValid())
	{
		DDX_FieldText (pDX, IDE_NUMMER, g_pAbfSet -> m_Transporteurnummer, g_pAbfSet);
		DDX_FieldText (pDX, IDE_BEMERKUNGEN, g_pAbfSet -> m_Transporteurbemerkungen, g_pAbfSet);

		if (pDX -> m_bSaveAndValidate)		// Daten lesen
			g_pAbfSet -> m_Eigentransport = 1 == m_btEigen.GetCheck () ? TRUE : FALSE;		
		else
		{
			if (m_pSet)
				OutputTransParam (g_pAbfSet -> m_Transporteurnummer);						

			m_btEigen.SetCheck (g_pAbfSet -> m_Eigentransport);
			SetControlState ();
		}
	}
	else
	{
		CString strDummy;

		DDX_Text (pDX, IDE_NUMMER, strDummy);
		DDX_Text (pDX, IDE_BEMERKUNGEN, strDummy);

		// nur lesen handhaben
		if (!pDX -> m_bSaveAndValidate)
		{
			SetControlState (true);
		}
	}
}

BEGIN_MESSAGE_MAP(CTranspPage, CBranchPage)
	//{{AFX_MSG_MAP(CTranspPage)
	ON_BN_CLICKED(IDB_EIGENTRANSPORT, OnEigentransport)
	ON_BN_CLICKED(IDB_CHANGE, OnChange)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeNummer)
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranspPage message handlers
void CTranspPage::OnEigentransport() 
{
	// TODO: Add your control notification handler code here
	try
	{		
		CString strSelbst;
		if (1 == m_btEigen.GetCheck ())
			VERIFY (strSelbst.LoadString (IDS_SELBST));

		m_edNummer.SetWindowText (strSelbst);
		OutputTransParam (strSelbst);	
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

// Nummer des Transporteurs ändern
void CTranspPage::OnChange() 
{
	Change (((CGakApp *)AfxGetApp())->TransporteureDefaultSQL(), IDS_TRANSP_CAPTION); 
}

void CTranspPage::SetControlState (bool bDisableAll)
{
	ASSERT (g_pAbfSet != NULL);
	m_edNummer.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_btChange.EnableWindow (g_pAbfSet -> CanUpdate ()&& !bDisableAll);
	m_btEigen.EnableWindow (g_pAbfSet -> CanUpdate ()&& !bDisableAll);
	m_edBemerkungen.EnableWindow (g_pAbfSet -> CanUpdate ()&& !bDisableAll);

	m_edPlz.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edOrt.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edStrasse.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edName.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
}

int CTranspPage::OpenSet ()
{
	if (m_pSet)
		return 0;

	try
	{
		CDaoDatabase* pDatabase = NULL;
		if (g_pAbfSet)
			pDatabase = g_pAbfSet -> m_pDatabase;
		m_pSet = new CTranspSet (pDatabase, 
								 ((CGakApp *)AfxGetApp())->TransporteureDefaultSQL());
		m_pSet -> Open();
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

//	Angaben des akt. Transporteurs ausgeben
void CTranspPage::OutputTransParam (const char *pNummer)
{
	ASSERT (NULL != pNummer && AfxIsValidString (pNummer));

	try	
	{
		ASSERT (NULL != m_pSet);
		if (!m_pSet -> IsOpen ())
			return;

		CString strSelbst;
		VERIFY (strSelbst.LoadString (IDS_SELBST));

		BOOL bSelbst = strSelbst == pNummer;
		m_btEigen.SetCheck (bSelbst);						

	//	wenn kein Eingentransport
		if (!bSelbst && OutputName (pNummer))	// und Einträge gefunden
		{
			CTranspSet *pSet = (CTranspSet *) m_pSet;
			m_edPlz.SetWindowText (pSet -> m_Postleitzahl);
			m_edOrt.SetWindowText (pSet -> m_Ortsname);
			m_edStrasse.SetWindowText (pSet -> m_Strasse);
			return;			// alles OK
		}
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

	m_edName.SetWindowText ("");
	m_edPlz.SetWindowText ("");
	m_edOrt.SetWindowText ("");
	m_edStrasse.SetWindowText ("");
}

LONG CTranspPage:: OnChangeNummer(UINT uiMsg, LONG lText)
{
	CBranchPage:: OnChangeNummer (uiMsg, lText);

	if (IsWindowVisible ())
	{
		m_btEigen.SetCheck (0);
		OutputTransParam ((const char *)lText);
	}

	return TRUE;
}

//	neuer Name gesendet
LONG CTranspPage:: OnChangeName(UINT, LONG)
{
//	wird oben eingetragen
	return TRUE;
}

/*
// auf akt. Satz gehen
BOOL CTranspPage::FindActRecord (void)
{
	try
	{
		ASSERT (g_pAbfSet != NULL);

	//	zuerst Sonderfall betrachten
		CString strSelbst;
		VERIFY (strSelbst.LoadString (IDS_SELBST));
		if (strSelbst == g_pAbfSet -> m_Transporteurnummer)
			return FALSE;

		if (-1 == OpenSet ())
			return FALSE;

		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, g_pAbfSet -> m_Transporteurnummer);
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
CString CTranspPage::GetName ()
{
	if (FindActRecord ())
		return m_pSet -> m_Name;
	else
		return "";
}		

CString CTranspPage::GetStrasse (void)
{
	if (FindActRecord ())
		return ((CTranspSet *) m_pSet) -> m_Strasse;
	else
		return "";		
}

CString CTranspPage::GetPlz (void)
{
	if (FindActRecord ())
		return ((CTranspSet *) m_pSet) -> m_Postleitzahl;
	else
		return "";			
}

CString CTranspPage::GetOrt (void)
{
	if (FindActRecord ())
		return ((CTranspSet *) m_pSet) -> m_Ortsname;
	else
		return "";			
}
*/

BOOL CTranspPage::OnInitDialog() 
{

	CBranchPage::OnInitDialog(); 

//	TODO: Add extra initialization here
	m_edNummer.LimitText (NamenLaenge);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

