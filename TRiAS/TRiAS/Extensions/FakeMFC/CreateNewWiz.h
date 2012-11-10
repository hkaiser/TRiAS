// CreateNewWiz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

class CCoordSystemItem {
private:
	CString m_strFullDesc;
	CString m_strRegKey;
	CString m_strTcfName;

public:
		CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey);
		~CCoordSystemItem (void) {}

	CString &GetDesc (void) { return m_strFullDesc; }
	CString &GetRegKey (void) { return m_strRegKey; }
	CString &GetTcfName (void) { return m_strTcfName; }
};

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree window
#define IMG_COORDFOLDER		3
#define IMG_COORDOPENFOLDER	4

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

	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

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
	CCreateNewWiz(BOOL fCoordSysForPrj = TRUE, 
		UINT uiCapID = IDS_CREATENEWWIZARD);
	~CCreateNewWiz();

public:
	void SetDescription (HTREEITEM hItem = NULL);
	void SetStandAlone() { m_fStandAlone = TRUE; }

	bool RegisterEntries (HPROJECT hPr);
	static bool RegisterEntries (HPROJECT hPr, LPCSTR pcRegKey);

// Dialog Data
	enum { 
		IDD = IDD_CREATENEWWIZARD,
		IDD_CAPTION_NEW = IDS_CREATENEWWIZARD,
		IDD_CAPTION_ADD = IDS_ADDDATASOURCE,
		IDD_PROMPT_DS = IDS_COORDSYS_DS
	};
	//{{AFX_DATA(CCreateNewWiz)
	CStatic	m_ftDescText;
	CStatic	m_ftDescription;
	CCoordSystemTree	m_tvCoordSystems;
	//}}AFX_DATA

	void SetPairs (IComposeStringPairs *pIPairs, BSTR bstrSelectCS)
	{
		m_Pairs = pIPairs;
		if (NULL != bstrSelectCS && SysStringLen(bstrSelectCS) > 0) {
			USES_CONVERSION;
			m_strTcfName = OLE2A(bstrSelectCS);
		}
		else
			m_strTcfName.Empty();
	}
	HRESULT HandleConnectString();
	void PresetCS();

	void SetIsLast (bool fFlag) { m_fIsLast = fFlag; }

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewWiz)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool InitCoordSystemEntry (CRegistry &rCurr, HTREEITEM hParent, LPCSTR pcFullKey, LPCSTR pcSubkey, DWORD dwPos);
	bool InitCoordSystem (CRegistry &rCurr, HTREEITEM hParent, LPCSTR pcFullKey, LPCSTR pcKey);
	bool InitCoordSystemsFromRegistry (void);

	static bool RegisterEntry (CRegistry &rCurr, LPCSTR pcSubKey, DWORD dwMode, HPROJECT hPr);

	HTREEITEM FindTcfName (LPCSTR pcTcfName, HTREEITEM hParent = TVI_ROOT);
	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

	void AdjustButtons(HTREEITEM hItem = NULL);

protected:
	// Generated message map functions
	//{{AFX_MSG(CCreateNewWiz)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_strSelKey;
	CString m_strTcfName;
	bool m_fStandAlone;
	bool m_fNotEmpty;
	bool m_fIsLast;
	UINT m_uiPrompt;
	WComposeStringPairs m_Pairs;
	BOOL m_fCoordSysForPrj;
};

/////////////////////////////////////////////////////////////////////////////
