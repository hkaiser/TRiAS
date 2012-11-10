// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 28.01.2003 11:54:08
//
// @doc
// @module ClsfyByCodeDlg.cpp | Implementation of the <c CClsfyByCodeDlg> class

#include "stdafx.h"

#include "LineTools.h"
#include "ClsfyByCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClsfyByCodeDlg

CClsfyByCodeDlg* CClsfyByCodeDlg::CreateInstance (LPCSTR pcCaption)
{
CClsfyByCodeDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CClsfyByCodeDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CClsfyByCodeDlg, CPropertyPage)

CClsfyByCodeDlg::CClsfyByCodeDlg() 
	: CPropertyPage(CClsfyByCodeDlg::IDD)
{
	//{{AFX_DATA_INIT(CClsfyByCodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
	m_iAreaCtrl = 1;
}

CClsfyByCodeDlg::~CClsfyByCodeDlg()
{
}

void CClsfyByCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClsfyByCodeDlg)
	DDX_Control(pDX, IDC_AREACONSTRUCTION, m_btnAreaCtrl);
	DDX_Control(pDX, IDC_LINECONSTRUCTION, m_btnLineCtrl);
	DDX_Control(pDX, IDC_HELPCONSTRUCTION, m_nTextHelp);
	DDX_Control(pDX, IDC_SELECTCAPTION, m_nCaption);
	DDX_Control(pDX, IDC_GCOIDENT, m_nTextLink);
	DDX_Text(pDX, IDC_HELPCONSTRUCTION, m_nDescription);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClsfyByCodeDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CClsfyByCodeDlg)
	ON_BN_CLICKED(IDC_AREACONSTRUCTION, OnAreaConstruction)
	ON_BN_CLICKED(IDC_LINECONSTRUCTION, OnLineConstructiomn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CClsfyByCodeDlg::AdjustSheetButtons()
{

//CPropertySheet *pSheet = DYNAMIC_DOWNCAST(CPropertySheet, GetParent());
CPropertySheet *pSheet = (CPropertySheet *) GetParent();

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CClsfyByCodeDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CClsfyByCodeDlg message handlers

BOOL CClsfyByCodeDlg::OnSetActive() 
{

	USES_CONVERSION;

	m_nTextLink.SetWindowText (W2A(m_bstrCheckFeature));


	m_iAreaCtrl = 1;
	m_btnAreaCtrl.SetCheck(true);
	SetInformation();

	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CClsfyByCodeDlg ::SetConfigData (CComBSTR strLink, int iListIndex)
{

	m_bstrCheckFeature = strLink;
	m_iListIndex = iListIndex;

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void CClsfyByCodeDlg::OnAreaConstruction() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	m_iAreaCtrl = 1;

	UpdateData();

	SetInformation();

	AdjustSheetButtons();
}


void CClsfyByCodeDlg::OnLineConstructiomn() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	m_iAreaCtrl = 0;

	UpdateData();

	SetInformation();

	AdjustSheetButtons();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CClsfyByCodeDlg::SetInformation(void)
{
	m_nDescription.Empty();

	CString sK;

	m_nTextHelp.SetWindowText (m_nDescription);
	if ( 1 == m_iListIndex) {
		sK.LoadString(IDS_LINECAPTION);
		m_nCaption.SetWindowText (sK);
	}

	if ( 2 == m_iListIndex) {
		sK.LoadString(IDS_MULTICAPTION);
		m_nCaption.SetWindowText (sK);
	}


	if ( m_iAreaCtrl ) {

		if ( 0 == m_iListIndex)
			sK.LoadString(IDS_HELPAREACTRL);

		if ( 1 == m_iListIndex)
			sK.LoadString(IDS_HELPLINEAREACTRL);

		if ( 2 == m_iListIndex)
			sK.LoadString(IDS_HELPMULTIAREACTRL);

		m_nDescription += sK;

	} else {

		if ( 0 == m_iListIndex)
			sK.LoadString(IDS_HELPLINECTRL);

		if ( 1 == m_iListIndex)
			sK.LoadString(IDS_HELPLINELINECTRL);

		if ( 2 == m_iListIndex)
			sK.LoadString(IDS_HELPMULTILINECTRL);

		m_nDescription += sK;
	}

	m_nTextHelp.SetWindowText (m_nDescription);


	UpdateData();
}
////////////////////////////////////////////////////////////////////////////
