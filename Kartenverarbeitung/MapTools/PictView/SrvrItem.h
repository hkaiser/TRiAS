// SrvrItem.h : interface of the CPictViewSrvrItem class
//

class CPictViewSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CPictViewSrvrItem)

// Constructors
public:
	CPictViewSrvrItem(CPictViewDoc* pContainerDoc);

// Attributes
	CPictViewDoc* GetDocument() const
		{ return (CPictViewDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictViewSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CPictViewSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
