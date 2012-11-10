// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 27.01.2003 08:38:45
//
// @doc
// @module CodeLineDlg.cpp | Implementation of the <c CCodeLineDlg> class

#include "stdafx.h"

#include "LineTools.h"
#include "CodeLineDlg.h"
#include "errorcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeLineDlg

CCodeLineDlg* CCodeLineDlg::CreateInstance (LPCSTR pcCaption)
{
CCodeLineDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CCodeLineDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CCodeLineDlg, CPropertyPage)

CCodeLineDlg::CCodeLineDlg() 
	: CPropertyPage(CCodeLineDlg::IDD)
{
	//{{AFX_DATA_INIT(CCodeLineDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
	m_iNotCtrl = m_iFeature = m_iIntern = 0;
	m_iErrorCode = 0;
}

CCodeLineDlg::~CCodeLineDlg()
{
}

void CCodeLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeLineDlg)
	DDX_Control(pDX, IDC_CHECKFIRSTCTRL, m_btnNotCtrl);
	DDX_Control(pDX, IDC_CHECKFEATURE, m_btnFeature);
	DDX_Control(pDX, IDC_CHECKINTERN, m_btnIntern);
	DDX_Control(pDX, IDC_LINEDESCRIPTION, m_nTextHelp);
	DDX_Control(pDX, IDC_LINEGCSCONTROL, m_nTextLink);
	DDX_Check(pDX, IDC_CHECKFIRSTCTRL, m_iNotCtrl);
	DDX_Check(pDX, IDC_CHECKFEATURE, m_iFeature);
	DDX_Check(pDX, IDC_CHECKINTERN, m_iIntern);
	DDX_Text(pDX, IDC_LINEDESCRIPTION, m_nDescription);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCodeLineDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CCodeLineDlg)
	ON_BN_CLICKED(IDC_CHECKFIRSTCTRL, OnCheckfirstctrl)
	ON_BN_CLICKED(IDC_CHECKFEATURE, OnCheckfeature)
	ON_BN_CLICKED(IDC_CHECKINTERN, OnCheckintern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCodeLineDlg::AdjustSheetButtons()
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

	dwBttns |= (!m_iErrorCode) ? PSWIZB_DISABLEDFINISH : PSWIZB_FINISH;


	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CCodeLineDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

//	return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCodeLineDlg message handlers

BOOL CCodeLineDlg::OnSetActive() 
{

	USES_CONVERSION;

	m_nTextLink.SetWindowText (W2A(m_bstrCheckFeature));

	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}

void CCodeLineDlg::OnCheckfirstctrl() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	if ( !m_iNotCtrl)
		m_iErrorCode = m_iErrorCode | LINE_NOTCONTROL;
	else
		m_iErrorCode = m_iErrorCode & ~LINE_NOTCONTROL;

	UpdateData();

	SetInformation();

	AdjustSheetButtons();


}

void CCodeLineDlg::OnCheckfeature() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	if ( !m_iFeature)
		m_iErrorCode = m_iErrorCode | LINE_CTRLFEATURE;
	else
		m_iErrorCode = m_iErrorCode & ~LINE_CTRLFEATURE;

	UpdateData();

	SetInformation();

	AdjustSheetButtons();
}

void CCodeLineDlg::OnCheckintern() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	if ( !m_iIntern)
		m_iErrorCode = m_iErrorCode | LINE_CTRLINTERN;
	else
		m_iErrorCode = m_iErrorCode & ~LINE_CTRLINTERN;

	UpdateData();

	SetInformation();

	AdjustSheetButtons();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeLineDlg ::SetConfigData (CComBSTR strLink)
{

	m_bstrCheckFeature = strLink;

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void CCodeLineDlg::SetInformation(void)
{
	m_nDescription.Empty();

	m_nTextHelp.SetWindowText (m_nDescription);

//	m_iNotCtrl = m_iFeature = m_iIntern = 0;

	CString sK;

	if ( m_iNotCtrl ) {
		sK.LoadString(IDS_HELPNOTCTRL);
		m_nDescription += sK;
	}

	if ( m_iFeature ) {
		sK.LoadString(IDS_HELPFEATURE);
		m_nDescription += sK;
	}

	if ( m_iIntern ) {
		sK.LoadString(IDS_HELPINTERN);
		m_nDescription += sK;
	}


	m_nTextHelp.SetWindowText (m_nDescription);


	UpdateData();
}
////////////////////////////////////////////////////////////////////////////
