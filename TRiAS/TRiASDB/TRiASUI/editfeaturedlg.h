// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/28/1998 10:49:31 PM
//
// @doc
// @module EditFeatureDlg.h | Declaration of the CCEditFeatureDlg

#if !defined(_EDITFEATUREDLG_H__B31D1E67_56D1_11D2_9ECF_006008447800__INCLUDED_)
#define _EDITFEATUREDLG_H__B31D1E67_56D1_11D2_9ECF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "MfcAtlPropertyPage.h"
#include "EditRO.h"

EXTERN_C const CLSID CLSID_CEditFeatureDlg;

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureDlg dialog

class CEditFeatureDlg : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEditFeatureDlg)

// Construction
public:
	CEditFeatureDlg();
	~CEditFeatureDlg();

// Dialog Data
	//{{AFX_DATA(CEditFeatureDlg)
	enum { IDD = IDD_EDITFEATUREDLG };
	CString	m_PropName;
	CString	m_Feature;
	BOOL	m_IsRO;
	CString	m_Description;
	//}}AFX_DATA
	CStatic m_ObjPropName;
	CEditRO m_FeatCtrl;
	CButton m_rbIsRO;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditFeatureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditFeatureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFeaturevalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(UIContextHandle, IUIContextHandle)
		STDMETHOD_(HRESULT, get_ContextHandle)(INT_PTR *pContextHandle);
		STDMETHOD_(HRESULT, put_ContextHandle)(INT_PTR ContextHandle);
	END_INTERFACE_PART(UIContextHandle)

	HRESULT get_ContextHandle (INT_PTR *pContextHandle);
	HRESULT put_ContextHandle (INT_PTR ContextHandle);

private:
	INT_PTR m_ContextHandle;
};

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureAtlDlg
typedef CMfcAtlPropertyPage<CEditFeatureDlg, &CLSID_EditFeatureDlg, IDR_EDITFEATUREDLG> CEditFeatureAtlDlg;

#endif // !defined(_EDITFEATUREDLG_H__B31D1E67_56D1_11D2_9ECF_006008447800__INCLUDED_)
