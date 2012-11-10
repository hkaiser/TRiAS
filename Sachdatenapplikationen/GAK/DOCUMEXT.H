// DocumExt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocumentExt document

class CDocumentExt : public CDocument
{
protected:
	CDocumentExt(UINT uiCaptionID) { m_uiCaptionID = uiCaptionID; }           
	// DECLARE_DYNCREATE(CDocumentExt)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentExt)
	public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocumentExt() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocumentExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_uiCaptionID;
};
