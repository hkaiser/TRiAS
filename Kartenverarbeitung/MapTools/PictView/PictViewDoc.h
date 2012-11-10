// PictViewDoc.h : interface of the CPictViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CPictViewSrvrItem;

class CPictViewDoc : public COleServerDoc
{
protected: // create from serialization only
	int m_nOptDlgIndex;
	int m_nTranspChannel;
	COLORREF m_dwTranspColor;
	BOOL m_bBanding;
	CFile m_fileOfPicture;
	BOOL CreatePicture( LPCTSTR lpszPictName );
	CPictViewDoc();
	DECLARE_DYNCREATE(CPictViewDoc)

// Attributes
public:
	BOOL IsBanding();
	CString m_strPictName;
	CPictViewSrvrItem* GetEmbeddedItem()
		{ return (CPictViewSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPicture *m_pPicture;
	virtual ~CPictViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPictViewDoc)
	afx_msg void OnOptions();
	afx_msg void OnFileProperties();
	afx_msg void OnUpdateFileProperties(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveCopyAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPictViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#define	PICT_OPENED	1L
#define	PICT_PROPCHANGED	2L

/////////////////////////////////////////////////////////////////////////////
