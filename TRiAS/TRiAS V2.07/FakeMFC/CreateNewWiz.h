// CreateNewWiz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

class CCoordSystemItem {
private:
	CString m_strFullDesc;
	CString m_strRegKey;

public:
		CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey);
		~CCoordSystemItem (void) {}

	CString &GetDesc (void) { return m_strFullDesc; }
	CString &GetRegKey (void) { return m_strRegKey; }
};

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree window
#define IMG_FOLDER		3
#define IMG_OPENFOLDER	4

class CCoordSystemTree : public CTreeCtrl
{
private:
	class CCreateNewWiz *m_pPage;
	CImageList m_ilImages;

// Construction
public:
	CCoordSystemTree();

// Attributes
public:

// Operations
public:
	void InitTreeCrtl (CCreateNewWiz *pPage);
	int GetImageCount (void) 
		{ return m_ilImages.GetImageCount(); }
	void AdjustImage (HTREEITEM hItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoordSystemTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoordSystemTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoordSystemTree)
	afx_msg void OnDeleteCoordSystemItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCreateNewWiz dialog

class CCreateNewWiz : public CPropertyPage
{
	DECLARE_DYNCREATE(CCreateNewWiz)

// Construction
public:
	CCreateNewWiz (bool fStandAlone = false);
	~CCreateNewWiz();

public:
	void SetDescription (HTREEITEM hItem = NULL);
	bool RegisterEntries (void);

// Dialog Data
	//{{AFX_DATA(CCreateNewWiz)
	enum { IDD = IDD_CREATENEWWIZARD };
	CStatic	m_ftDescText;
	CStatic	m_ftDescription;
	CCoordSystemTree	m_tvCoordSystems;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewWiz)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool InitCoordSystemEntry (CRegistry &rCurr, HTREEITEM hParent, LPCSTR pcFullKey, LPCSTR pcSubkey, DWORD dwPos);
	bool InitCoordSystem (CRegistry &rCurr, HTREEITEM hParent, LPCSTR pcFullKey, LPCSTR pcKey);
	bool InitCoordSystemsFromRegistry (void);

	bool RegisterEntry (CRegistry &rCurr, LPCSTR pcSubKey, DWORD dwMode);

protected:
	// Generated message map functions
	//{{AFX_MSG(CCreateNewWiz)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strSelKey;
	bool m_fStandAlone;
	bool m_fNotEmpty;
};

/////////////////////////////////////////////////////////////////////////////
