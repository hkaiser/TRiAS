// cptvw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaptionView view

class CCaptionView : public CView
{
protected:
	CCaptionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCaptionView)

// Attributes
public:
	bool SetCaption(LPCSTR lpcstrCaption);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptionView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCaptionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCaptionView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_strCaption;
};

/////////////////////////////////////////////////////////////////////////////
