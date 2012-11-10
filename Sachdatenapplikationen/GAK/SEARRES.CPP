// SearRes.cpp : implementation file
//

#include "stdafx.h"		// vorübers. Header
#include "gak.h"		// CGakApp
#include "searchse.h"	// CSearchSet
#include <listext.hpp>	// CListBoxExt
#include "numedit.h"	// CErzNrEdit
#include "SearRes.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchResult dialog
CSearchResult :: CSearchResult(CSearchSet *pSet, CWnd* pParent /*=NULL*/)
			   : CDialog(CSearchResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchResult)
	//}}AFX_DATA_INIT
	ASSERT (pSet != NULL);
	m_pSet = pSet;
}

CSearchResult :: CSearchResult(CWnd* pParent /*=NULL*/)
			   : CDialog(CSearchResult::IDD, pParent)
{
	m_pSet = NULL;
}

CSearchResult :: ~CSearchResult (void)
{
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	pApp -> m_bResDlg = FALSE;
}

void CSearchResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchResult)
	DDX_Control(pDX, IDE_FERZNR, m_edErzNr);
	DDX_Control(pDX, IDB_STAMM, m_btStammdaten);
	DDX_Control(pDX, IDB_ABFAELLE, m_btAbfaelle);
	DDX_Control(pDX, IDC_FOUND, m_stFound);
	DDX_Control(pDX, IDL_NUMMERN, m_lbNummern);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchResult, CDialog)
	//{{AFX_MSG_MAP(CSearchResult)
	ON_BN_CLICKED(IDB_ABFAELLE, OnAbfaelle)
	ON_BN_CLICKED(IDB_STAMM, OnStamm)
	ON_LBN_SELCHANGE(IDL_NUMMERN, OnSelchangeNummern)
	ON_LBN_DBLCLK(IDL_NUMMERN, OnDblclkNummern)
	ON_WM_HELPINFO()
	ON_EN_CHANGE(IDE_FERZNR, OnChangeErznr)
	ON_MESSAGE (IDM_RB_DOWN, OnRBDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchResult message handlers
void CSearchResult::ReadRecordSet (void)
{
	ASSERT (m_pSet != NULL);
	ASSERT (m_pSet -> IsOpen ());

//	ListBox füllen
	try
	{
		if (!m_pSet -> IsBOF ())
		{
			CWaitCursor wc;
			m_lbNummern.ResetContent ();	// alten Inhalt der Listbox löschen
			// m_pSet -> MoveFirst ();			// immer auf 1. Satz
			int iInd = -1;					// akt. Index
			while (!m_pSet -> IsEOF ())
			{
				if ((iInd = m_lbNummern.AddString (m_pSet -> m_strNummer)) == LB_ERR)
					AfxThrowMemoryException ();

				m_pSet -> MoveNext ();
			}
		}

	//	Anzahl Nummer ausgeben
		SetItemCount (TRUE);
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		EndDialog (IDCANCEL);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		EndDialog (IDCANCEL);
	}
}

BOOL CSearchResult::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_edErzNr.LimitText (ErzNummerLaenge);
	
	// TODO: Add extra initialization here
	if (m_pSet)
		ReadRecordSet ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Anzahl der gefundenen Nummern ausgeben
void CSearchResult :: SetItemCount (BOOL bFirstTime)
{
	int iActCnt = m_lbNummern.GetCurSel ();
	if (iActCnt == LB_ERR)
		iActCnt = 0;
	else
		iActCnt++;
	int iCnt = max (m_lbNummern.GetCount (), 0);

	char Buffer [50] = "";
	CString strCnt;
	strCnt.LoadString (IDS_FOUND_RESULT);
	ASSERT (!strCnt.IsEmpty ());
	if (bFirstTime)
		wsprintf (Buffer, "%s (%ld):", strCnt, iCnt);
	else			
		wsprintf (Buffer, "%s (%ld/%ld):", strCnt, iActCnt, iCnt);
	m_stFound.SetWindowText (Buffer);
}		

void CSearchResult::EnableControls (BOOL bEnable)
{
//	m_btRefresh.EnableWindow (bEnable);
	m_btAbfaelle.EnableWindow (bEnable);		
	m_btStammdaten.EnableWindow (bEnable);		
	m_lbNummern.EnableWindow (bEnable);		
}

void CSearchResult :: ShowData (BOOL bData)
{
	int iSel = m_lbNummern.GetCurSel ();
	if (iSel < 0)
		return;

	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);

//	keine weitere Aktionen zulassen
	EnableControls (FALSE);

	CString strSel;
	m_lbNummern.GetText (iSel, strSel);
	m_edErzNr.SetWindowText (strSel);	

	if (bData)
		pApp -> CreateStammdaten (strSel, TRUE);
	else
		pApp -> CreateAbfaelle (strSel, TRUE);

	EnableControls (TRUE);
}

void CSearchResult::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}

void CSearchResult::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
	DestroyWindow ();
}

void CSearchResult::OnCancel()
{
	CDialog::OnCancel();
	DestroyWindow ();
}

void CSearchResult::OnSelchangeNummern() 
{
	// TODO: Add your control notification handler code here
	SetItemCount (FALSE);
	EnableControls (m_lbNummern.GetCurSel () >= 0 ? TRUE : FALSE);
}

/*
void CSearchResult::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	EnableControls (FALSE);
	ReadRecordSet ();
	EnableControls (TRUE);
}
*/

void CSearchResult::OnStamm() 
{
	// TODO: Add your control notification handler code here
	ShowData (TRUE);	
}

void CSearchResult::OnDblclkNummern() 
{
	// TODO: Add your control notification handler code here
	ShowData (TRUE);		
}

void CSearchResult::OnAbfaelle() 
{
	// TODO: Add your control notification handler code here
	ShowData (FALSE);		
}

BOOL CSearchResult::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
	
	// return CDialog::OnHelpInfo(pHelpInfo);
}

void CSearchResult::OnChangeErznr() 
{
	// TODO: Add your control notification handler code here
	if (m_edErzNr.LineLength () > 0)
	{
		CString strSel;
		m_edErzNr.GetWindowText (strSel);	
		m_lbNummern.SelectString (-1, strSel);
	}		
	else
		m_lbNummern.SetCurSel (-1);
}

//	rechte Maustaste betätigt
LONG CSearchResult::OnRBDown(UINT uiParam, LONG lParam)
{
//  Index Ok ?
	int iSel = (int) lParam;
    if ((iSel >= 0) && (iSel < m_lbNummern.GetCount ()))
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);

	//	keine weitere Aktionen zulassen
		EnableControls (FALSE);

		CString strSel;
		m_lbNummern.GetText (iSel, strSel);
		m_edErzNr.SetWindowText (strSel);	
		pApp -> CreateAbfaelle (strSel, TRUE);

		EnableControls (TRUE);
	}
		
	return TRUE;
}