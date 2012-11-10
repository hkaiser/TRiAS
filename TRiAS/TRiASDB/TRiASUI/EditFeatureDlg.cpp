// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/28/1998 10:48:59 PM
//
// @doc
// @module EditFeatureDlg.cpp | Implementation of CEditFeatureDlg

#include "stdafx.h"
#include "resource.h"

#include "mfchelper.h"
#include "TRiASUI.h"
#include "EditFeatureDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureDlg property page

IMPLEMENT_DYNCREATE(CEditFeatureDlg, COlePropertyPage)

BEGIN_INTERFACE_MAP(CEditFeatureDlg, COlePropertyPage)
	INTERFACE_PART(CEditFeatureDlg, IID_IUIContextHandle, UIContextHandle)
END_INTERFACE_MAP()

CEditFeatureDlg::CEditFeatureDlg() 
	: COlePropertyPage(CEditFeatureDlg::IDD, IDS_TITLE_EDITFEATUREDLG)
{
	//{{AFX_DATA_INIT(CEditFeatureDlg)
	m_PropName = _T("");
	m_Feature = _T("");
	m_IsRO = FALSE;
	m_Description = _T("");
	//}}AFX_DATA_INIT

#if defined(_DEBUG)
	m_bNonStandardSize = TRUE;
#endif	// _DEBUG

	m_ContextHandle = NULL;

// To keep the application running as long as an OLE automation 
// object is active, the constructor calls AfxOleLockApp.   
	AfxOleLockApp(); 
}

CEditFeatureDlg::~CEditFeatureDlg()
{
	AfxOleUnlockApp(); 
}

void CEditFeatureDlg::DoDataExchange(CDataExchange* pDX)
{
	COlePropertyPage::DoDataExchange(pDX);

CString strFeature, strIsRO;

	strFeature.Format ("Feature_%08x", m_ContextHandle);
	strIsRO.Format ("IsRO_%08x", m_ContextHandle);

	if (pDX -> m_bSaveAndValidate) {
		DDX_Text(pDX, IDC_EDIT_FEATUREVALUE, m_Feature);
		DDP_Text(pDX, IDC_EDIT_FEATUREVALUE, m_Feature, strFeature);
	} else {
		DDP_Text(pDX, IDC_EDIT_FEATUREVALUE, m_Feature, strFeature);
		DDX_Text(pDX, IDC_EDIT_FEATUREVALUE, m_Feature);
	}

	//{{AFX_DATA_MAP(CEditFeatureDlg)
	DDP_Check(pDX, IDC_PROPERTY_RO, m_IsRO, strIsRO);
	DDX_Check(pDX, IDC_PROPERTY_RO, m_IsRO);
	DDP_Text(pDX, IDC_PROPERTY_LONGNAME, m_Description, _T("Description"));
	DDX_Text(pDX, IDC_PROPERTY_LONGNAME, m_Description);
	//}}AFX_DATA_MAP

// Synchronisation der anderen Eigenschaften der Objekteigenschaft
	DDP_Text(pDX, IDC_PROPERTY_NAME, m_PropName, _T("Name") );
	DDP_PostProcessing(pDX);

// Namen der Objekteigenschaft in Static Text setzen
	if (::IsWindow(m_ObjPropName.GetSafeHwnd()) && ::IsWindow(m_FeatCtrl.GetSafeHwnd())) {
	CString strText;

		strText.Format (IDS_PROPERTY_NAME_TEMPLATE, m_PropName);
		m_ObjPropName.SetWindowText (strText);
		m_FeatCtrl.SetRO (m_IsRO);
	}
}


BEGIN_MESSAGE_MAP(CEditFeatureDlg, COlePropertyPage)
	//{{AFX_MSG_MAP(CEditFeatureDlg)
	ON_EN_CHANGE(IDC_EDIT_FEATUREVALUE, OnChangeEditFeaturevalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureDlg message handlers

BOOL CEditFeatureDlg::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	
	m_ObjPropName.SubclassDlgItem (IDC_PROPERTY_NAME, this);
	m_FeatCtrl.SubclassDlgItem (IDC_EDIT_FEATUREVALUE, this);
	m_rbIsRO.SubclassDlgItem (IDC_PROPERTY_RO, this);

#if defined(_DEBUG)
	m_rbIsRO.ShowWindow (SW_NORMAL);
	m_rbIsRO.EnableWindow (FALSE);
#else
	m_rbIsRO.ShowWindow (SW_HIDE);
#endif // _DEBUG

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditFeatureDlg::OnChangeEditFeaturevalue() 
{
	SetModifiedFlag(TRUE);		// muß gespeichert werden
}

///////////////////////////////////////////////////////////////////////////////
// IUIContextHandle

IMPLEMENT_IUNKNOWN(CEditFeatureDlg, UIContextHandle)

HRESULT CEditFeatureDlg::XUIContextHandle::get_ContextHandle(INT_PTR *pContextHandle)
{
	METHOD_PROLOGUE(CEditFeatureDlg, UIContextHandle)
	return pThis->get_ContextHandle(pContextHandle);
}

HRESULT CEditFeatureDlg::XUIContextHandle::put_ContextHandle(INT_PTR ContextHandle)
{
	METHOD_PROLOGUE(CEditFeatureDlg, UIContextHandle)
	return pThis->put_ContextHandle(ContextHandle);
}

HRESULT CEditFeatureDlg::get_ContextHandle (INT_PTR *pContextHandle)
{
	if (NULL == pContextHandle)
		return E_POINTER;

	*pContextHandle = m_ContextHandle;
	return S_OK;
}

HRESULT CEditFeatureDlg::put_ContextHandle (INT_PTR ContextHandle)
{
	m_ContextHandle = ContextHandle;
	return S_OK;
}

