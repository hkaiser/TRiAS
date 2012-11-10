// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.07.2000 15:01:09 
//
// @doc
// @module TRiASView.h | Declaration of the <c CTRiASView> class

#if !defined(_TRIASVIEW_H__E9A255F6_5470_4162_8BD2_A28C8C9843A5__INCLUDED_)
#define _TRIASVIEW_H__E9A255F6_5470_4162_8BD2_A28C8C9843A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "scroltip.h"
#include "ConnectedCtf.h"

/////////////////////////////////////////////////////////////////////////////
// TRiAS ProjektFenster

class CTRiASCntrItem;
class CTRiASPreviewView;

class CTRiASView : public CView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CTRiASView)

// Attributes
public:
	CTRiASDoc* GetDocument();
	// m_pSelection holds the selection to the current CTestAPPCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CTestAPPCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CTRiASCntrItem* m_pSelection;

	static CRect m_rcToolTipObject;	// static info to provide hit text
//	static CPoint m_ptToolHit;
	static LONG m_lToolTipObject;
	static Punkt m_ptToolTest;

	CString m_strTipText;
	CString m_strStatusText;

	CMRCScrollTip m_ScrollTip;	// ScrollTip
	CComObject<CConnectedCtf> *m_pCTF;		// KoordinatenTransformation

#if defined(_USE_WHEELMOUSE)
	BOOL m_fIsPanning;
	BOOL m_fEnablePanning;
#endif // _USE_WHEELMOUSE

	HCURSOR m_hMagnifyCursor;

	BOOL m_fPaintConnectFilters;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	virtual void PreSubclassWindow();
	virtual void OnDraw(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	virtual int OnToolHitTest (CPoint point, TOOLINFO* pTI) const;
	BOOL OnToolTipNeedText (UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	BOOL OnToolTipShow (UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	BOOL OnToolTipPop (UINT id, NMHDR * pNMHDR, LRESULT * pResult);

// Implementation
public:
	CTRiASView();
	virtual ~CTRiASView();

	virtual BOOL WireDocument (CCreateContext* pContext);
	BOOL GenerateTipTextHelper (LPSTR pText, CPoint pt, LONG lONr);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

#if defined(_USE_PRINT_PREVIEW)
	void PrintPreview();
	void HasConfig() { m_fHasPreviewConfig = TRUE; }
	BOOL GetHasConfig() { return m_fHasPreviewConfig; }
	
	CSingleDocTemplate *m_pTemplate;
	CTRiASPreviewView *m_pPreviewView;
	BOOL m_bPrintPreview;
	BOOL m_fHasPreviewConfig;
	BOOL m_fHasPostedRequest;
	BOOL m_fPreviewing;
#endif // defined(_USE_PRINT_PREVIEW)

	void PaintTopLayer(HDC hDC, HDC hDCTarget);

protected:

	BOOL CALLBACK EnumConnectionFilters(char *pName, BOOL, void *pData);

// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
#if defined(_USE_WHEELMOUSE)
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg LONG OnTrackAutoPanStart(UINT, LONG);
	afx_msg LONG OnTrackAutoPanEnd(UINT, LONG);
#endif // defined(_USE_WHEELMOUSE)
#if defined(_USE_PRINT_PREVIEW)
public:
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);
#endif // defined(_USE_PRINT_PREVIEW)

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TRiASView.cpp
inline CTRiASDoc* CTRiASView::GetDocument()
   { return (CTRiASDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_TRIASVIEW_H__E9A255F6_5470_4162_8BD2_A28C8C9843A5__INCLUDED_)
