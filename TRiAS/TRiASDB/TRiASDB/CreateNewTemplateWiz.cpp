// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.11.1999 23:20:41
//
// @doc
// @module CreateNewTemplateWiz.cpp | Implementation of the <c CCreateNewTemplateWiz> class

#include "stdafx.h"
#include <afxdlgs.h>

#include "resource.h"

#include "Strings.h"
#include "CreateNewTemplateWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewTemplateWiz property page

IMPLEMENT_DYNCREATE(CCreateNewTemplateWiz, CPropertyPage)

CCreateNewTemplateWiz::CCreateNewTemplateWiz() 
	: CPropertyPage(CCreateNewTemplateWiz::IDD)
{
	//{{AFX_DATA_INIT(CCreateNewTemplateWiz)
	//}}AFX_DATA_INIT
}

CCreateNewTemplateWiz::~CCreateNewTemplateWiz()
{
}

void CCreateNewTemplateWiz::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewTemplateWiz)
	DDX_Control(pDX, IDC_COMPATIBLE_WITH_V2, m_cbCompatible);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateNewTemplateWiz, CPropertyPage)
	//{{AFX_MSG_MAP(CCreateNewTemplateWiz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sonstige Helper
void CCreateNewTemplateWiz::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = PSWIZB_FINISH|PSWIZB_BACK;

	pSheet -> SetWizardButtons (dwBttns);
}

HRESULT CCreateNewTemplateWiz::SaveSettingsToPairs()
{
	if (!m_Pairs) 
		return E_UNEXPECTED;

//CComBSTR bstrCompatible (m_fCompatible ? "1" : "0");

//lint -save -e1550
//	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(g_cbCompatible), bstrCompatible, VARIANT_TRUE));
//lint -restore
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CCreateNewTemplateWiz message handlers

BOOL CCreateNewTemplateWiz::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CCreateNewTemplateWiz::OnWizardNext() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardNext();
}

BOOL CCreateNewTemplateWiz::OnWizardFinish() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardFinish();
}

BOOL CCreateNewTemplateWiz::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
