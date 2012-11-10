// @doc
// @module CreateNewParamWiz.cpp | Implementation for the <c CCreateNewParamWiz>
// class

#include "stdafx.h"
#include <afxdlgs.h>

#include "resource.h"

#include "Strings.h"
#include "CreateNewParamWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz property page

IMPLEMENT_DYNCREATE(CCreateNewParamWiz, CPropertyPage)

CCreateNewParamWiz::CCreateNewParamWiz() 
	: CPropertyPage(CCreateNewParamWiz::IDD)
{
	//{{AFX_DATA_INIT(CCreateNewParamWiz)
	//}}AFX_DATA_INIT

	m_fCompatibleV2 = false;
	m_fCompressed = true;
#if _TRiAS_VER >= 0x0420
	m_fCompatibleV4 = false;
#endif // _TRiAS_VER >= 0x0420
}

CCreateNewParamWiz::~CCreateNewParamWiz()
{
}

void CCreateNewParamWiz::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewParamWiz)
	DDX_Control(pDX, IDC_COMPRESS_STREAMS, m_cbCompressed);
	DDX_Control(pDX, IDC_COMPATIBLE_WITH_V2, m_cbCompatibleV2);
	//}}AFX_DATA_MAP
#if _TRiAS_VER >= 0x0420
	DDX_Control(pDX, IDC_COMPATIBLE_WITH_V4, m_cbCompatibleV4);
#endif // _TRiAS_VER >= 0x0420
}


BEGIN_MESSAGE_MAP(CCreateNewParamWiz, CPropertyPage)
	//{{AFX_MSG_MAP(CCreateNewParamWiz)
	ON_BN_CLICKED(IDC_COMPATIBLE_WITH_V2, OnCompatibilitymode)
	ON_BN_CLICKED(IDC_COMPRESS_STREAMS, OnCompressStreams)
	//}}AFX_MSG_MAP
#if _TRiAS_VER >= 0x0420
	ON_BN_CLICKED(IDC_COMPATIBLE_WITH_V4, OnCompatibilitymodeV4)
#endif // _TRiAS_VER >= 0x0420
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sonstige Helper
void CCreateNewParamWiz::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = PSWIZB_FINISH|PSWIZB_BACK;

	pSheet -> SetWizardButtons (dwBttns);
}

HRESULT CCreateNewParamWiz::SaveSettingsToPairs()
{
	if (!m_Pairs) 
		return E_UNEXPECTED;

//lint -save -e1550
CComBSTR bstrCompressed (m_fCompressed ? "1" : "0");
CComBSTR bstrCompatible (m_fCompatibleV2 ? "209" : "500");

#if _TRiAS_VER >= 0x0420
	if (m_fCompatibleV4)
		bstrCompatible = "400";
#endif // _TRiAS_VER >= 0x0420

	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(g_cbCompatible), bstrCompatible, VARIANT_TRUE));
	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(g_cbCompressed), bstrCompressed, VARIANT_TRUE));
//lint -restore
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz message handlers

BOOL CCreateNewParamWiz::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CCreateNewParamWiz::OnWizardNext() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardNext();
}

BOOL CCreateNewParamWiz::OnWizardFinish() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardFinish();
}

BOOL CCreateNewParamWiz::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_cbCompatibleV2.SetCheck (m_fCompatibleV2);

#if _TRiAS_VER >= 0x0420
	m_cbCompatibleV4.SetCheck (m_fCompatibleV4);
#else
	GetDlgItem(IDC_COMPATIBLE_WITH_V4)->ShowWindow(SW_HIDE);
#endif // _TRiAS_VER >= 0x0420

	m_cbCompressed.SetCheck (m_fCompressed);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateNewParamWiz::OnCompatibilitymode() 
{
	m_fCompatibleV2 = m_cbCompatibleV2.GetCheck() ? 1 : 0;
	if (m_fCompatibleV2) {
		m_cbCompressed.SetCheck(FALSE);
		m_cbCompressed.EnableWindow(FALSE);
		m_fCompressed = false;			// #HK000924: kompatible dürfen nicht komprimiert sein
	} else
		m_cbCompressed.EnableWindow(TRUE);

#if _TRiAS_VER >= 0x0420
	m_cbCompatibleV4.SetCheck(0);
	m_fCompatibleV4 = false;
#endif // _TRiAS_VER >= 0x0420
}

#if _TRiAS_VER >= 0x0420
void CCreateNewParamWiz::OnCompatibilitymodeV4() 
{
	m_fCompatibleV4 = m_cbCompatibleV4.GetCheck() ? 1 : 0;
	m_cbCompatibleV2.SetCheck(0);
	m_fCompatibleV2 = false;
	m_cbCompressed.EnableWindow(TRUE);
}
#endif // _TRiAS_VER >= 0x0420

void CCreateNewParamWiz::OnCompressStreams() 
{
	m_fCompressed = m_cbCompressed.GetCheck() ? 1 : 0;	
}
