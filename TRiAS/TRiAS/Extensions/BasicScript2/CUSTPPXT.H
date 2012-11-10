// CustPPxt.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCustomizeMenuPPExt command target

class CCustomizeMenuPPExt : public CCmdTarget
{
	DECLARE_DYNCREATE(CCustomizeMenuPPExt)

	CCustomizeMenuPPExt();           // protected constructor used by dynamic creation
		
	DESTROYNOTIFYPROCPTR m_pProc;
	CCustDlg	*m_pCustomizePageDlg;

	bool FInit(void);
	
	HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey) 
                { return m_xCustomizeMenuPSheetExt.Initialize (pidl, pIDO, hKey); }       

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeMenuPPExt)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	static CCustomizeMenuPPExt * CreateInstance(LPUNKNOWN pIUnk, 
												DESTROYNOTIFYPROCPTR pProc);
// Implementation
protected:
	virtual ~CCustomizeMenuPPExt();

	// Generated message map functions
	//{{AFX_MSG(CCustomizeMenuPPExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCustomizeMenuPPExt)

	DECLARE_INTERFACE_MAP()
	
	BEGIN_INTERFACE_PART(CustomizeMenuPSheetExt, ITriasPropSheetExt)
		STDMETHOD (AddPages)(	LPFNADDPROPSHEETPAGE lpfnAddPage,	
								LPARAM lParam);						
		STDMETHOD (ReplacePage)(UINT uPageID,	
								LPFNADDPROPSHEETPAGE lpfnReplacePage,
								LPARAM lParam);
		HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey);	
	END_INTERFACE_PART(CustomizeMenuPSheetExt)

	BEGIN_INTERFACE_PART(CustomizeMenuExtInit, ITriasExtInit)
		STDMETHOD (Initialize) (LPCITEMIDLIST pidlFolder,	
								LPDATAOBJECT lpdobj,	
								HKEY hkeyProgID);
	END_INTERFACE_PART(CustomizeMenuExtInit)
};

/////////////////////////////////////////////////////////////////////////////
