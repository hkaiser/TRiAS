// TRiASView.h : interface of the CTRiASView class
//

#include "scroltip.h"
#include "ConnectedCtf.h"

/////////////////////////////////////////////////////////////////////////////
// TRiAS ProjektFenster

class CTRiASCntrItem;

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
	static CPoint m_ptToolHit;
	static LONG m_lToolTipObject;
	static Punkt m_ptToolTest;

	CString m_strTipText;
	CString m_strStatusText;

	CMRCScrollTip m_ScrollTip;	// ScrollTip
	CComObject<CConnectedCtf> *m_pCTF;		// KoordinatenTransformation

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

protected:

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TRiASView.cpp
inline CTRiASDoc* CTRiASView::GetDocument()
   { return (CTRiASDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
