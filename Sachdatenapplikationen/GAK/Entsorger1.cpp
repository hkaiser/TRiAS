// Entsorger1.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "BranPage.h"	// CBranchPage: Basisklasse
#include "gaksete.h"	// CDaoRecordsetExt	
#include "abfset.h"		// CAbfSet
#include "selset.h"		// CSelectSet
#include "selnum.h"		// CSelNumberDlg	
#include "entsset.h"	// CEntsorgerSet
#include "Entsorger1.h"	// zugeh. Header
#include "TextClipboard.h" // CTextClipBoard einfaches Kpieren ins Clipboard


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CAbfSet *g_pAbfSet;

/////////////////////////////////////////////////////////////////////////////
// CEntsorger1 property page

IMPLEMENT_DYNCREATE(CEntsorger1, CBranchPage)

CEntsorger1::CEntsorger1(UINT uiID) : CBranchPage(uiID)
{
	//{{AFX_DATA_INIT(CEntsorger1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CEntsorger1::~CEntsorger1()
{
}

void CEntsorger1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntsorger1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	DDX_Control(pDX, IDE_NAME, m_edName);
	DDX_Control(pDX, IDB_CHANGE, m_btChange);

	if (g_pAbfSet->IsValid())
	{
		DDX_FieldText (pDX, IDE_NUMMER, g_pAbfSet -> m_Entsorgernummer, g_pAbfSet);
		DDX_FieldText (pDX, IDE_BEMERKUNGEN, g_pAbfSet -> m_Entsorgerbemerkungen, g_pAbfSet);

		// nur lesen handhaben
		if (!pDX -> m_bSaveAndValidate)
		{
			SetControlState ();
		}

	}
	else
	{
		
		CString strDummy;
		DDX_Text (pDX, IDE_BEMERKUNGEN, strDummy);
		DDX_Text (pDX, IDE_NUMMER, strDummy);

		// nur lesen handhaben
		if (!pDX -> m_bSaveAndValidate)
		{
			SetControlState (true);
		}
	}
}


BEGIN_MESSAGE_MAP(CEntsorger1, CBranchPage)
	//{{AFX_MSG_MAP(CEntsorger1)
	ON_BN_CLICKED(IDB_CHANGE, OnChange)
	ON_BN_CLICKED(IDC_COPYCLIPBOARD, OnCopyClipboard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntsorger1 message handlers
/////////////////////////////////////////////////////////////////////////////
// CEntPage message handlers
void CEntsorger1::OnChange() 
{
	Change (((CGakApp *)AfxGetApp ())->EntsorgerDefaultSQL(), IDS_ENTS_CAPTION);
}

void CEntsorger1::SetControlState (bool bDisableAll)
{
	ASSERT (g_pAbfSet != NULL);
	
	m_btChange.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	m_edNummer.EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
	
//	Bemerkungen
	CWnd *pCWnd = GetDlgItem (IDE_BEMERKUNGEN);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll);
}

//	Set öffnen
int CEntsorger1::OpenSet ()
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

LONG CEntsorger1:: OnChangeNummer(UINT uiMsg, LONG lText)
{
	CBranchPage:: OnChangeNummer (uiMsg, lText);

	if (IsWindowVisible ())
	{
		// welche veränderten Daten?
//		OutputEntsParam ((const char *)lText);
	}

	return TRUE;
}

BOOL CEntsorger1::OnInitDialog() 
{
	BOOL retval = CBranchPage::OnInitDialog();
	
	return retval;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntsorger1::OnCopyClipboard() 
{
	CString strClipboardText;

	// Kopieren der spezifischen Daten in den String
	GetStringData(strClipboardText);

	// Kopieren des Kommentars ins Clipboard
	CTextClipboard::SetText(strClipboardText);
}

BOOL CEntsorger1::GetStringData(CString& strTarget)
{
	// erstmal aktualisieren
	UpdateData(true);

	ADDWINDOWTEXT(m_edNummer, strTarget);

	if ((NULL != g_pAbfSet) && g_pAbfSet->IsValid())
	{
		ADDTEXT(strTarget, g_pAbfSet -> m_Entsorgerbemerkungen);
	}

	return TRUE;
}
