// BetrPage.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	Ressourcen
#include "gaksete.h"	//	CDaoRecordsetExt	
#include "abfset.h"		//	CAbfSet

#include "BetrPage.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CAbfSet *g_pAbfSet;

/////////////////////////////////////////////////////////////////////////////
// CBetreiberPage property page

IMPLEMENT_DYNCREATE(CBetreiberPage, CPropertyPage)

CBetreiberPage::CBetreiberPage() : CPropertyPage(CBetreiberPage::IDD)
{
	//{{AFX_DATA_INIT(CBetreiberPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBetreiberPage::~CBetreiberPage()
{
}

void CBetreiberPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBetreiberPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	ASSERT (g_pAbfSet != NULL);
	if (g_pAbfSet->IsValid())
	{
		DDX_FieldText (pDX, IDE_NUMMER, g_pAbfSet -> m_Betreibernummer, g_pAbfSet);
		DDX_FieldText (pDX, IDE_NAME, g_pAbfSet -> m_Betreiberbemerkungen, g_pAbfSet);

		//	lese ggf. zugeh. Namen
		if (!pDX -> m_bSaveAndValidate)		// Daten lesen
			SetControlState ();
	}
	else
	{
		CString strDummy;
		DDX_Text (pDX, IDE_NUMMER, strDummy);
		DDX_Text (pDX, IDE_NAME, strDummy);

		SetControlState(true);	// alle aus
	}
}


BEGIN_MESSAGE_MAP(CBetreiberPage, CPropertyPage)
	//{{AFX_MSG_MAP(CBetreiberPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBetreiberPage message handlers

BOOL CBetreiberPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	//	Nummer
	CEdit *pCWnd = (CEdit *) GetDlgItem (IDE_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> LimitText (NummerLaenge);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBetreiberPage :: SetControlState (bool bDisableAll)
{
	ASSERT (NULL != g_pAbfSet);

//	Kommentarfeld
	CWnd *pCWnd = GetDlgItem (IDE_NAME);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 
	
//	Nummernfeld
	pCWnd = GetDlgItem (IDE_NUMMER);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (g_pAbfSet -> CanUpdate () && !bDisableAll); 
}

