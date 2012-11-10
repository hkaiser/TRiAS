// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/28/1998 10:54:41 PM
//
// @doc
// @module EditFeatureParamDlg.h | Declaration of the CEditFeatureParamDlg

#if !defined(_EDITFEATUREPARAMDLG_H__B31D1E68_56D1_11D2_9ECF_006008447800__INCLUDED_)
#define _EDITFEATUREPARAMDLG_H__B31D1E68_56D1_11D2_9ECF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "MfcAtlPropertyPage.h"

EXTERN_C const CLSID CLSID_EditFeatureParamDlg;

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureParamDlg dialog

class CEditFeatureParamDlg : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEditFeatureParamDlg)

// Construction
public:
	CEditFeatureParamDlg();
	~CEditFeatureParamDlg();

// Dialog Data
	//{{AFX_DATA(CEditFeatureParamDlg)
	enum { IDD = IDD_EDITFEATUREPARAMDLG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditFeatureParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEditFeatureParamDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureParamAtlDlg
typedef CMfcAtlPropertyPage<CEditFeatureParamDlg, &CLSID_EditFeatureParamDlg, IDR_EDITFEATUREPARAMDLG> CEditFeatureParamAtlDlg;

#endif // !defined(_EDITFEATUREPARAMDLG_H__B31D1E68_56D1_11D2_9ECF_006008447800__INCLUDED_)
