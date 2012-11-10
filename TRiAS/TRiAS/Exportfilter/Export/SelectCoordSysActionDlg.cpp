// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 02.05.2004 19:36:09
//
// @doc
// @module SelectCoordSysActionDlg.cpp | Implementation of the <c CSelectCoordSysActionDlg> class

#include "stdafx.h"
#include "ExportImpl.h"

#include "resource.h"
#include "SelectCoordSysActionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg

CSelectCoordSysActionDlg* CSelectCoordSysActionDlg::CreateInstance (LPCSTR pcCaption)
{
CSelectCoordSysActionDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CSelectCoordSysActionDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CSelectCoordSysActionDlg, CPropertyPage)

CSelectCoordSysActionDlg::CSelectCoordSysActionDlg() 
	: CPropertyPage(CSelectCoordSysActionDlg::IDD)
{
	//{{AFX_DATA_INIT(CSelectCoordSysActionDlg)
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
	m_fNotEmpty = false;
}

CSelectCoordSysActionDlg::~CSelectCoordSysActionDlg()
{
}

void CSelectCoordSysActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectCoordSysActionDlg)
	DDX_Control(pDX, IDC_DESCTEXT, m_ftDescText);
	DDX_Control(pDX, IDC_COORDDESCRIPTION, m_ftDescription);
	DDX_Control(pDX, IDC_COORDSYSTEMS, m_tvCoordSystems);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelectCoordSysActionDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectCoordSysActionDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_COORDSYSTEMS, OnDblclkCoordSystems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSelectCoordSysActionDlg::AdjustSheetButtons(HTREEITEM hItem)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage(hItem)) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CSelectCoordSysActionDlg::GetDisableNextPage(HTREEITEM hItem)
{
	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		return (NULL != pItemData) ? FALSE : TRUE;
	}
	return FALSE;
}

void CSelectCoordSysActionDlg::SetDescription (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = m_tvCoordSystems.GetSelectedItem();
	_ASSERTE(!m_fNotEmpty || NULL != hItem);

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL == pItemData) 
			m_ftDescription.SetWindowText ("");
		else 
			m_ftDescription.SetWindowText (pItemData -> GetDesc());
	} 
	AdjustSheetButtons(hItem);
}

namespace {
	// output error message, if CS isn't loadable
	void CantLoadCS(char const *pcCsName)
	{
		CString strPrompt;
		strPrompt.Format(IDS_CANTLOADCS, pcCsName, GetLastError());
		AfxMessageBox(strPrompt);
	}
}

bool CSelectCoordSysActionDlg::PrepareResult()
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return false;		// nur Childs behandeln

CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return false;

// Koordinatensystem am Parent setzen
CString strTcfName = pItemData->GetTcfName();

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(strTcfName)));

		m_CS = CS;		// store result coordsystem

	} COM_CATCH_OP_RETURN(CantLoadCS(strTcfName), false);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg message handlers

BOOL CSelectCoordSysActionDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
// TreeControl/Imagelist initialisieren
	m_tvCoordSystems.InitTreeCrtl (this);

// Koordinatensysteme einlesen
	m_fNotEmpty = m_tvCoordSystems.InitCoordSystemsFromRegistry();
	m_tvCoordSystems.SetFocus();

	SetDescription();
	AdjustSheetButtons(m_tvCoordSystems.GetSelectedItem());
	UpdateData (FALSE);

	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectCoordSysActionDlg::OnSetActive() 
{
	AdjustSheetButtons(m_tvCoordSystems.GetSelectedItem());
	return CPropertyPage::OnSetActive();
}

void CSelectCoordSysActionDlg::OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL != pItemData) {
		// nur, wenn leaf selektiert wurde
		CPropertySheet *pSheet = (CPropertySheet *)GetParent();

			_ASSERTE(NULL != pSheet);
			pSheet -> PressButton ((m_dwFlags & ADDPAGES_LASTPAGE) ? 
				PSBTN_FINISH : PSBTN_NEXT);
		}
	}
}

LRESULT CSelectCoordSysActionDlg::OnWizardNext() 
{
	_ASSERTE(!(m_dwFlags & ADDPAGES_LASTPAGE));		// darf nicht letztes Fenster sein
	if (!PrepareResult())
		return 0;

	return CPropertyPage::OnWizardNext();
}

BOOL CSelectCoordSysActionDlg::OnWizardFinish() 
{
	_ASSERTE(m_dwFlags & ADDPAGES_LASTPAGE);		// muﬂ letztes Fenster sein
	if (!PrepareResult())
		return FALSE;

	return CPropertyPage::OnWizardFinish();
}

