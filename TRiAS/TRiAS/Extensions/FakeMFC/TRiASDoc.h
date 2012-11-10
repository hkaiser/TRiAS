// TRiASDoc.h : interface of the CTRiASDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CTRiASSrvrItem;

class CTRiASDoc : public COleServerDoc
{
protected: // create from serialization only
	CTRiASDoc();
	DECLARE_DYNCREATE(CTRiASDoc)

// Attributes
public:
	CTRiASSrvrItem* GetEmbeddedItem()
		{ return (CTRiASSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTRiASDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
