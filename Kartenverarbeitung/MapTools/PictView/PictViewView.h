// PictViewView.h : interface of the CPictViewView class
//
/////////////////////////////////////////////////////////////////////////////

class CPictViewView : public CScrollView
{
protected: // create from serialization only
	CPictViewView();
	DECLARE_DYNCREATE(CPictViewView)

// Attributes
public:
	CPictViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPictViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictViewView)
	afx_msg void OnCancelEditSrvr();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRedraw();
	afx_msg void OnUpdateRedraw(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PictViewView.cpp
inline CPictViewDoc* CPictViewView::GetDocument()
   { return (CPictViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
