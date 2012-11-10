// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/01/1998 02:18:43 PM
//
// @doc
// @module EditRO.h | Description goes here

#if !defined(AFX_EDITRO_H__880A4FC5_70C5_11D2_9EEC_006008447800__INCLUDED_)
#define AFX_EDITRO_H__880A4FC5_70C5_11D2_9EEC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEditRO window

class CEditRO : public CEdit
{
// Construction
public:
	CEditRO();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditRO)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditRO();

	void SetRO (BOOL fRO) { SendMessage (EM_SETREADONLY, fRO); }

// Generated message map functions
protected:
	//{{AFX_MSG(CEditRO)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITRO_H__880A4FC5_70C5_11D2_9EEC_006008447800__INCLUDED_)
