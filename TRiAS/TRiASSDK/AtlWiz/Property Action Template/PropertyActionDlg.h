// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: [!DateAndTime]
//
// @doc
// @module [!DlgHeaderName] | Declaration of the <c [!DlgClassName]> class

[!crlf]
[!if=(FileExists, "FALSE")]
#if !defined(__[!UpperShortName]DLG_H_)
#define __[!UpperShortName]DLG_H_
[!crlf]
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
[!crlf]
// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif
[!crlf]
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!DlgClassName] dialog

[!crlf]
class [!DlgClassName] : 
	public CPropertyPage
{
	DECLARE_DYNCREATE([!DlgClassName])

[!crlf]
// Construction
public:
	[!DlgClassName]();
	~[!DlgClassName]();

[!crlf]
// Dialog Data
	//{{AFX_DATA([!DlgClassName])
	enum { IDD = [!IDD_DIALOGID] };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

[!crlf]
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL([!DlgClassName])
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

[!crlf]
public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static [!DlgClassName] *CreateInstance (LPCSTR pcCaption);

[!crlf]
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG([!DlgClassName])
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

[!crlf]
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

[!crlf]
private:
	DWORD m_dwFlags;
};

[!crlf]
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

[!crlf]
[!if=(FileExists, "FALSE")]
#endif // !defined(__[!UpperShortName]DLG_H_)
[!endif]
