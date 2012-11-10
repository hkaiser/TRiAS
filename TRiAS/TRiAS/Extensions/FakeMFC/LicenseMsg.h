// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.11.2000 19:12:48 
//
// @doc
// @module LicenseMsg.h | Declaration of the <c CLicenseMsg> class

#if !defined(_LICENSEMSG_H__84582233_5824_4B4E_AB0E_E5A812F2FAB4__INCLUDED_)
#define _LICENSEMSG_H__84582233_5824_4B4E_AB0E_E5A812F2FAB4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "HyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CLicenseMsg dialog
class COSVersion;

class CLicenseMsg : public CDialog
{
// Construction
public:
	CLicenseMsg(CWnd* pParent = NULL, LPCSTR pcCaption = NULL,
		LPCSTR pcLicText = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenseMsg)
	enum { IDD = IDD_LICENSE };
	CHyperLink m_Email;
	CString	m_LicText;
	CString	m_LicTextAddr;
	//}}AFX_DATA

	CString GetURLEx();
	CString GetOSVersion();
	CString GetOSName(COSVersion &os, DWORD dwPlatFormId, struct _OS_VERSION_INFO &osvi);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenseMsg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strCaption;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_LICENSEMSG_H__84582233_5824_4B4E_AB0E_E5A812F2FAB4__INCLUDED_)
