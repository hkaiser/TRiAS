// SrvrItem.h : interface of the CTRiASSrvrItem class
//

class CTRiASSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CTRiASSrvrItem)

// Constructors
public:
	CTRiASSrvrItem(CTRiASDoc* pContainerDoc);

// Attributes
	CTRiASDoc* GetDocument() const
		{ return (CTRiASDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CTRiASSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
