// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/28/1998 10:54:14 PM
//
// @doc
// @module EditFeatureParamDlg.cpp | Implementation of CEditFeatureParamDlg

#include "stdafx.h"
#include "resource.h"

#include "EditFeatureParamDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureParamDlg property page

IMPLEMENT_DYNCREATE(CEditFeatureParamDlg, COlePropertyPage)

CEditFeatureParamDlg::CEditFeatureParamDlg() 
	: COlePropertyPage(CEditFeatureParamDlg::IDD, IDS_TITLE_EDITFEATUREPARAMDLG)
{
	//{{AFX_DATA_INIT(CEditFeatureParamDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

#if defined(_DEBUG)
	m_bNonStandardSize = TRUE;
#endif	// _DEBUG

// To keep the application running as long as an OLE automation 
// object is active, the constructor calls AfxOleLockApp.   
	AfxOleLockApp(); 
}

CEditFeatureParamDlg::~CEditFeatureParamDlg()
{
	AfxOleUnlockApp(); 
}

void CEditFeatureParamDlg::DoDataExchange(CDataExchange* pDX)
{
	COlePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditFeatureParamDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditFeatureParamDlg, COlePropertyPage)
	//{{AFX_MSG_MAP(CEditFeatureParamDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFeatureParamDlg message handlers
