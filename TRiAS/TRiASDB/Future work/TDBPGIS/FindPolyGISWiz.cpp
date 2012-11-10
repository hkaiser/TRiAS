// @doc
// @module CreateNewParamWiz.cpp | Implementation for the <c CFindPolyGISWiz>
// class

#include "stdafx.h"
#include <afxdlgs.h>

#include "resource.h"

#include "Strings.h"
#include "DDXGetFile.h"
#include "FindPolyGISWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindPolyGISWiz property page

IMPLEMENT_DYNCREATE(CFindPolyGISWiz, CPropertyPage)

CFindPolyGISWiz::CFindPolyGISWiz() 
	: CPropertyPage(CFindPolyGISWiz::IDD)
{
	//{{AFX_DATA_INIT(CFindPolyGISWiz)
	m_strFileName = "";
	//}}AFX_DATA_INIT

CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software"), KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, TEXT("TRiASDB"), KEY_READ) &&
		ERROR_SUCCESS == key.Open(key, TEXT("TRiASDB.PolyGIS.Database.1"), KEY_READ))
	{
	char cbBuffer[_MAX_PATH];
	DWORD dwCount = sizeof(cbBuffer);

		if (ERROR_SUCCESS == key.QueryValue (cbBuffer, TEXT("PolyGIS"), &dwCount))
			m_strFileName = cbBuffer;
	} 
}

CFindPolyGISWiz::~CFindPolyGISWiz()
{
}

void CFindPolyGISWiz::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindPolyGISWiz)
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_SELECTPOLYGIS, m_strFileName);

// Dateinamen auswählen
DWORD dwFlags = 0;

	if (!IsWin40())
		dwFlags |= GF_OLD_STYLE_DIALOG;

#if !defined(_READWRITE)
	dwFlags |= GF_HIDEREADONLY;
#endif // !defined(_READWRITE)

CString strCaption;

	DDX_GetFilenameControl(pDX, IDC_SELECTPOLYGIS, 
			m_sleFileName, dwFlags, strCaption, TEXT("*.exe|"),
			TEXT(".exe"), m_strFileName);
}


BEGIN_MESSAGE_MAP(CFindPolyGISWiz, CPropertyPage)
	//{{AFX_MSG_MAP(CFindPolyGISWiz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sonstige Helper
void CFindPolyGISWiz::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = PSWIZB_FINISH|PSWIZB_BACK;

	pSheet -> SetWizardButtons (dwBttns);
}

HRESULT CFindPolyGISWiz::SaveSettingsToPairs()
{
	if (!m_Pairs) 
		return E_UNEXPECTED;

	_ASSERTE(m_strFileName.GetLength() > 0);		// muß gegeben sein
	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR("POLYGIS"), 
		CComBSTR(m_strFileName), VARIANT_TRUE));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CFindPolyGISWiz message handlers

BOOL CFindPolyGISWiz::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CFindPolyGISWiz::OnWizardBack() 
{
	m_sleFileName.Reset();
	return CPropertyPage::OnWizardBack();
}

LRESULT CFindPolyGISWiz::OnWizardNext() 
{
	PrepareResult();
	return CPropertyPage::OnWizardNext();
}

BOOL CFindPolyGISWiz::OnWizardFinish() 
{
	PrepareResult();
	return CPropertyPage::OnWizardFinish();
}

BOOL CFindPolyGISWiz::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindPolyGISWiz::PrepareResult()
{
	SaveSettingsToPairs();

CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
	{
		if (ERROR_SUCCESS == key.Open(key, TEXT("TRiASDB")) ||
			ERROR_SUCCESS == key.Create(key, TEXT("TRiASDB")))
		{
			if (ERROR_SUCCESS == key.Open(key, TEXT("TRiASDB.PolyGIS.Database.1")) ||
				ERROR_SUCCESS == key.Create(key, TEXT("TRiASDB.PolyGIS.Database.1")))
			{
				key.SetValue(m_strFileName, TEXT("PolyGIS"));
			} 
		}
	}
}

