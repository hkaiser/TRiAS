// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.07.2000 22:46:26 
//
// @doc
// @module TRiASPreviewView.h | Declaration of the <c CTRiASPreviewView> class

#if !defined(_TRIASPREVIEWVIEW_H__034D9733_660C_4E59_9595_DD9D23D24E99__INCLUDED_)
#define _TRIASPREVIEWVIEW_H__034D9733_660C_4E59_9595_DD9D23D24E99__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "AfxPriv.h"
#include "MappedBitmapButton.h"

///////////////////////////////////////////////////////////////////////////////
// Helper for acces to protected mebers of CPreviewDC
class CTRiASPreviewDC :
	public CPreviewDC
{
public:
	CSize GetTopLeft() { return m_sizeTopLeft; }
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASPreviewView view

class CTRiASPreviewView : public CPreviewView
{
protected:
	CTRiASPreviewView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTRiASPreviewView)

// Attributes
public:

protected:
	CMappedBitmapButton m_print;
	CMappedBitmapButton m_config;
	CMappedBitmapButton m_next;
	CMappedBitmapButton m_previous;
	CMappedBitmapButton m_onetwo;
	CMappedBitmapButton m_zoomIn;
	CMappedBitmapButton m_zoomOut;
	CMappedBitmapButton m_repaint;

	BOOL m_bOne;

// Operations
public:
	PRINTLAYOUT *GetLayoutData() { return &m_PL; }
	PRINTPREVIEW *GetPreviewData() { return &m_PP; }
	
	int GetCurrentPage() { return m_nCurrentPage; }
	CTRiASPreviewDC *GetPreviewDC() { _ASSERTE(NULL != m_pPreviewDC); return (CTRiASPreviewDC *)m_pPreviewDC; }
	CRect GetScreenRect(int nPage) { _ASSERTE(nPage >= 1); return m_pPageInfo[nPage-1].rectScreen; }
	UINT GetZoomState() { return m_nZoomState; }
	void PrinterDPtoScreenDP(POINT *ppt) { m_pPreviewDC -> PrinterDPtoScreenDP(ppt); }
	
// Overrides
	virtual void OnDisplayPageNumber(UINT nPage, UINT nPagesDisplayed);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASPreviewView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTRiASPreviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASPreviewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnPreviewRepaint();
	//}}AFX_MSG
	afx_msg void OnPreviewClose();
	afx_msg void OnPreviewPrint();
	afx_msg void OnPreviewConfig();
	afx_msg void OnUpdateNumPageChange(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

private:
	PRINTLAYOUT m_PL;				// Printlayout
	char m_cbBuffer[_MAX_PATH];		// Überschrift
	PRINTLAYOUTDIALOG m_PD;			// Dialog-Initialisierungf
	PRINTPREVIEW m_PP;
	HACCEL m_hAccel;				// lokale Acceleratoren
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_TRIASPREVIEWVIEW_H__034D9733_660C_4E59_9595_DD9D23D24E99__INCLUDED_)
