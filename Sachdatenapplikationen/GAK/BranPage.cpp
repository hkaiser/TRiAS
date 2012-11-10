// BranPage.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"			// CErzSet
#include "selset.h"			// CSelectSet
#include "selnum.h"			// CSelNummerDlg
#include "BranPage.h"		// zugeh. Header

// JG
#include "tmpswitch.h"		// CTmpSwitch exceptionsicheres temp. umschalten einer Variablen

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// externe Variablen
extern CGakSet *g_pErzSet; 

/////////////////////////////////////////////////////////////////////////////
// CBranchPage property page

IMPLEMENT_DYNCREATE(CBranchPage, CPropertyPage)
CBranchPage::CBranchPage(UINT uiID, UINT uiCaption) : CPropertyPage(uiID, uiCaption)
{
	//{{AFX_DATA_INIT(CBranchPage)
	//}}AFX_DATA_INIT
	m_pSet = NULL;
	m_pNumberDlg = NULL;
	m_bInOnChangeNummerField = false;
}

CBranchPage::~CBranchPage()
{
	DELETE_OBJ (m_pSet);
	DELETE_OBJ (m_pNumberDlg);
}

void CBranchPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBranchPage)
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	DDX_Control(pDX, IDE_NAME, m_edName);
	//}}AFX_DATA_MAP

	ASSERT (g_pErzSet != NULL);
	DDX_FieldText (pDX, IDE_NUMMER, g_pErzSet -> m_Branchennummer, g_pErzSet);

//	lese ggf. zugeh. Namen
	if (!pDX -> m_bSaveAndValidate)		// Daten lesen
	{
		OutputName (g_pErzSet -> m_Branchennummer);						

		SetControlState ();
	}
}

BEGIN_MESSAGE_MAP(CBranchPage, CPropertyPage)
	//{{AFX_MSG_MAP(CBranchPage)
	ON_BN_CLICKED(IDB_CHANGE, OnChange)
	ON_WM_CREATE()
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeName)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeNummer)
	ON_MESSAGE (IDM_SEND_DELETEOBJ, OnDeleteNumberDlg)
	ON_EN_CHANGE(IDE_NUMMER, OnChangeNummerField)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBranchPage message handlers

BOOL CBranchPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here --> Feldlängen begrenzen
//	Nummer
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (BrNummerLaenge);

//	Name
/*
	pCWnd = (CEdit *) GetDlgItem (IDE_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (BrNameLaenge);
*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Branchen-Nummer ändern
void CBranchPage::OnChange() 
{
	Change (((CGakApp *)AfxGetApp())->BranchenDefaultSQL(), IDS_BRANCHE_CAPTION);
}

void CBranchPage::Change (const CString &strTableName, UINT uiCaption)
//	TODO: Add your control notification handler code here
{
	try
	{	
		if (!m_pNumberDlg)
		{
			ASSERT (NULL != m_pSet);
			ASSERT (m_pSet -> IsOpen ());
			ASSERT (!strTableName.IsEmpty ());
			m_pNumberDlg = new CSelNumberDlg (this, m_pSet, uiCaption,
											  strTableName);
			if (!m_pNumberDlg -> Create (IDD_SEL_NUMMER))
				AfxThrowMemoryException ();
		}		

	//	aktuelle Selektion setzen
		CString strOldName;
		m_edNummer.GetWindowText (strOldName);
		m_pNumberDlg -> StoreSelection (strOldName);

	//	Fenster aktivieren
		m_pNumberDlg -> ShowWindow (SW_SHOWNORMAL);	
		m_pNumberDlg -> SetFocus ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
}

int CBranchPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	TODO: Add your specialized creation code here
	return OpenSet ();
}

//	zugeh. Branchennamen ausgeben
BOOL CBranchPage::OutputName (const char *pNummer)
{
//	prüfe Parameter
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());
	ASSERT (pNummer != NULL);

	if (!*pNummer)
	{
		m_edName.SetWindowText ("");
		return FALSE;
	}

//	Zeichenkette suchen
	try
	{
		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, pNummer);
		if (m_pSet -> FindFirst (strFind))
		{
			m_edName.SetWindowText (m_pSet -> m_Name); 
			return TRUE;
		}
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	m_edName.SetWindowText ("");			
	return FALSE;
}

void CBranchPage :: SetControlState (void)
{
	ASSERT (g_pErzSet != NULL);
	m_edName.EnableWindow (g_pErzSet -> CanUpdate ());
	m_edNummer.EnableWindow (g_pErzSet -> CanUpdate ());
	m_btChange.EnableWindow (g_pErzSet -> CanUpdate ());
}

BOOL CBranchPage::OnKillActive() 
{
	if (!CPropertyPage::OnKillActive())
		return FALSE;

	// TODO: Add your specialized code here and/or call the base class
	if (m_pNumberDlg && m_pNumberDlg -> IsWindowVisible ())
		m_pNumberDlg -> ShowWindow (SW_HIDE);		
	
	return TRUE;
}

//	Fenster löscht sich selbst
LONG CBranchPage::OnDeleteNumberDlg (UINT, LONG)
{
	m_pNumberDlg = NULL;	
	return TRUE;
}

//	neue Nummer gesendet
LONG CBranchPage:: OnChangeNummer(UINT, LONG lText)
{
	if (IsWindowVisible () && !m_bInOnChangeNummerField)
		m_edNummer.SetWindowText ((const char *) lText);

	return TRUE;
}

//	neuer Name gesendet
LONG CBranchPage:: OnChangeName(UINT, LONG lText)
{
	if (IsWindowVisible ())
		m_edName.SetWindowText ((const char *) lText);

	return TRUE;
}

//	lese Branchenname
/*
CString CBranchPage::GetName ()
{
	if (-1 == OpenSet ())
		return "";

	ASSERT (g_pErzSet != NULL);
	CString strFind;
	AfxFormatString1 (strFind, IDS_FIND_NUMMER, g_pErzSet -> m_Branchennummer);
	if (m_pSet -> FindFirst (strFind))
		return m_pSet -> m_Name;

	return "";
}		
*/

//	Set Öffnen
int CBranchPage::OpenSet ()
{
	ASSERT (NULL != g_pErzSet);
	return OpenSetParam (g_pErzSet -> m_pDatabase, ((CGakApp *)AfxGetApp())->BranchenDefaultSQL());
}

int CBranchPage::OpenSetParam (CDaoDatabase *pDatabase, const CString &strTableName)
{
	if (m_pSet)
		return 0;

	try
	{
		ASSERT (!strTableName.IsEmpty ());
		m_pSet = new CSelectSet (pDatabase, strTableName);
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

// JG
void CBranchPage::OnChangeNummerField() 
{
	// zyklischen Aufruf verhindern, (OnChangeNummer ändert NummernFeld)
	if (m_bInOnChangeNummerField)
		return;

	// m_bInOnChangeNummerField bis zum Ende als belegt markieren
	CTmpSwitch<bool> tmp(&m_bInOnChangeNummerField, true);

//	UpdateData(true);
//	UpdateData(false);	// neue Daten anzeigen
	CString strTmp;
	m_edNummer.GetWindowText(strTmp);
	OnChangeNummer(0, (long) (LPCSTR) strTmp);
}
