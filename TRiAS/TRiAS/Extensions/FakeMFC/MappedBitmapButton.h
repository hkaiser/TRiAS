// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.07.2000 22:47:12 
//
// @doc
// @module MappedBitmapButton.h | Declaration of the <c CMappedBitmapButton> class

#if !defined(_MAPPEDBITMAPBUTTON_H__8DF03768_C678_449F_A270_E48130194EA4__INCLUDED_)
#define _MAPPEDBITMAPBUTTON_H__8DF03768_C678_449F_A270_E48130194EA4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CMappedBitmapButton window

// Usage -- a replacement for the MFC CBitmapButton
// 1. include an owner-draw button in your dialog
// 2. declare a CMappedBitmapButton member in the CDialog code
// 3. hook in the CMappedBitmapButton using a call to AutoLoad
//
// the bitmap resource specified in AutoLoad must be divisable into
// 4 equally sized images that represent (left to right) the
// up, down, focused and disabled states of the button


class CMappedBitmapButton : public CButton
{
// Construction
public:
	DECLARE_DYNAMIC( CMappedBitmapButton )
	CMappedBitmapButton();

// Attributes
public:

protected:
	CImageList	m_image;
	UINT		m_idResource;

// Operations
public:
	BOOL LoadBitmap( UINT idBitmapResource );
	void SizeToContent();
	BOOL AutoLoad(UINT nID, CWnd* pParent, UINT idBitmapResource);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMappedBitmapButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMappedBitmapButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMappedBitmapButton)
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_MAPPEDBITMAPBUTTON_H__8DF03768_C678_449F_A270_E48130194EA4__INCLUDED_)
