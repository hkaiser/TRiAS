// AbfDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfDoc document

class CAbfDoc : public CDocumentExt
{
protected:
	CAbfDoc();          // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAbfDoc)

// Attributes
public:
	CAbfSet m_AbfSet;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfDoc)
	public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAbfDoc() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAbfDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
