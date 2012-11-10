// spltree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelMacroTreeBox window

class CSplit;

class CRelMacroTreeBox : public CTreeCtrl
{
// Construction
public:
	CRelMacroTreeBox();

	DECLARE_DYNCREATE( CRelMacroTreeBox )

// Operations
public:
	HRESULT Init(CSplit *pMainFrame);

protected:
	CImageList * m_pImageList;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelMacroTreeBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRelMacroTreeBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRelMacroTreeBox)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnRemove();
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnImport();
	afx_msg void OnNew();
	afx_msg void OnSaveas();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateDebugImport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugSaveas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugNewfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugRemove(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInsert();
	afx_msg void OnUpdateDebugInsert(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnDebugInsert();
	BOOL OnDebugSave(LPSTR **lplplpstr, UINT & uiCnt);
	BOOL OnDebugSaveAs(LPSTR **lplplpstr, UINT & uiCnt);
	HRESULT OnDebugSaveRelated(HTREEITEM hItem = NULL, LPCSTR lpcstrDeleted = NULL); 
	HRESULT	OnDebugGo(void);
	void InitTree(IObjectManagement *pIObjectManagement, IStreamInfo *pISI);

	BOOL		CreateDefaultTree(IObjectManagement *pIOMN, IStreamInfo *pISI);
	HRESULT		CreateSubItems(LPCSTR lpcstrParentName, REFIID riid);

	HRESULT		InitFirstScript(LPCSTR lpcstrScriptName);
	HRESULT		GetItemForExport(ITreeItem **ppIT, DWORD & dwSaveFLag);
	
	BOOL OnDebugOpen(BOOL fSet = true);
	BOOL OnDebugRemoveSelected();
	BOOL OnDebugRemoveLoaded();
	BOOL OnDebugDeleteLoaded();
	BOOL OnDebugImport(LPCSTR lpcstrFileName);
	BOOL OnDebugImportInProject(LPCSTR lpcstrFileName) ;
	BOOL OnDebugImportAllInProject(LPCSTR lpcstrFileName) ;
	HRESULT		InsertFunction (HTREEITEM hItem, const ebHCODE hCode);
	HTREEITEM	InsertDummyFunction (HTREEITEM hParent);
	HRESULT		InsertFunctionLoadedItem (	
		LPCSTR lpcstrName, LPCSTR  lpcstrDecl, LPCSTR lpcstrType, LPCSTR  lpcstrParams, LPCSTR lpcstrComment, LPSTR * lplpstr);

	HTREEITEM	GetChildItemSel(ITreeItem **ppIT);
	HRESULT		EnumFunctions(HTREEITEM hItem = NULL);
	HRESULT		ResetIfOnClose(void);
	
	BOOL IsRBTreeMenu() { return m_fTreeMenu; }
	void SetRBTreeMenu(BOOL f) { m_fTreeMenu = f; }

private:
	BOOL m_fTreeMenu;
	// RootHandle für Scripts
	HTREEITEM m_htreeCurrentMacroRoot;
	HTREEITEM m_htreeLoadedItem;
	CString		m_strBeginLabelEdit;
	BOOL		m_fNotExpand;
	// Zugriff auf MainFrame
	CSplit *	m_pMainFrame;
	CSplit *	GetMainFrame(void) { return m_pMainFrame; }
	HACCEL m_hAccel;

	HRESULT GetGeneralScripts(IObjectManagement **pp);
	HRESULT GetInfoGeneralScripts(IStreamInfo **ppISI);
	HRESULT GetFilterScripts(IObjectManagement **pp);
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI);
	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI);
	
	HRESULT	GetProjectScript(HTREEITEM hItem, ITreeItem **ppTI);

	HRESULT	OnOpenEndLabelEdit (TV_DISPINFO* pTVDispInfo);
	BOOL	OnOpenBeginLabelEdit(TV_DISPINFO* pTVDispInfo);
	BOOL	OnOpenAfterDelete (void);

	// Initialisierung des Controls
	BOOL		GetAccelerator(void);
	BOOL		CreateDefaultTree(void);
	BOOL		InitFilterTree(void); 
	BOOL		InitGeneralTree(void); 
	BOOL		InitObjFeatTree(void); 
	BOOL		FillTree(HTREEITEM hItem, IObjectManagement *pIObjMan, IStreamInfo *pIStreamInfo);
	HTREEITEM	SetSuperItem(IObjectManagement *pIObjMan, IStreamInfo *pIStreamInfo, HTREEITEM hParent, REFIID riid, LPCSTR lpcstr, HTREEITEM *ph);
	HRESULT		SetSubItems(HTREEITEM hParentItem, HTREEITEM hSuperItem, LPCSTR lpcstrParentName, REFIID riid);
	HTREEITEM	InitItem(HTREEITEM hItem);
	DWORD		GetStreamInfo(IStreamInfo *pIStreamInfo, LPCSTR lpcstr);
	// Funktionsentries erzeugen
	HTREEITEM	InsertFunctionItem (HTREEITEM hItem, LPCSTR lpcstr, LPCSTR lpcstrDecl, LPCSTR lpcstrType, LPCSTR lpcstrParams, LPCSTR lpcstrComment);
	HRESULT		DeleteFunctionItems(HTREEITEM hParent);
	HRESULT		EnumFunctionsFromDisk(HTREEITEM hItem);
	HRESULT		EnumFunctionsFromDebugger(HTREEITEM hItem);
	BOOL		Import (LPCSTR lpcstrFileName);
	BOOL		ImportAll (LPCSTR lpcstrFileName);
	BOOL		ImportFile (LPCSTR lpcstrFileName);

	// Tree-Levels
	HRESULT	IsFirstLevel(HTREEITEM hItem);
	HRESULT	IsKeyLevel(HTREEITEM hItem);
	HRESULT	IsScriptLevel(HTREEITEM hItem);
	HRESULT	IsFunctionLevel(HTREEITEM hItem);
	// File oder Projectmacro öffnen
	BOOL		DeleteSubItem(HTREEITEM hItem);
	BOOL		DeleteSuperItem(HTREEITEM hItem, BOOL fIsFromMenu);
	BOOL		DeleteItemWithParent(HTREEITEM hItem) ;
	// Sonstiges
	// alle Einträge am Ende löschen
	HRESULT		DeleteAll(void);
	BOOL		DeleteAllObjects(HTREEITEM hItem);
	// derzeitigen Eintrag löschen
	BOOL		DeleteLoadedItem(void);
	// Bildchen richten
	BOOL		AdjustImage (HTREEITEM hItem);
	void		CloseFoldersImage(void);
	void		OpenFoldersImage(HTREEITEM hItem);
	CString		GenerateTreeEntry (int IDS);
	HTREEITEM	GetLoadedItem(void) { return m_htreeLoadedItem ?  m_htreeLoadedItem : NULL; }
	BOOL		GetStringListLoadedSuperItem(LPSTR * lplpstr);
	UINT		GetCountLoadedSuperItem(void);
	
	HTREEITEM	IsItemAllreadyInsert(HTREEITEM hItem, LPCSTR lpcstr);
	HRESULT		RenameItemEndLabelEdit(HTREEITEM hEditItem, LPCSTR lpcstr, HTREEITEM *phItem);
	HRESULT		InsertItemEndLabelEdit(HTREEITEM hEditItem, LPCSTR lpcstr, HTREEITEM *phItem);
	HTREEITEM	InsertKey(LPCSTR, int iImage, HTREEITEM hParent);
	
	HRESULT		Init(ITreeItem *pProjScript, int iImage,
					HTREEITEM hParent, 							
					LPCSTR lpcstrItemEntry, 
					LPCSTR lpcstr,
					LPCSTR lpcstrPar, 
					BOOL fJustInsert, 
					HTREEITEM *phItem);
	HTREEITEM	InsertGeneralItem(REFIID riid, LPCSTR, LPCSTR lpcstrPar, HTREEITEM hParent, BOOL fSuperItem, BOOL fInitNew, BOOL fJustInsert = true);
	BOOL		FindRightInsertItem(HTREEITEM hSelItem, HTREEITEM hFirstLevelItem);
	
	HTREEITEM	InsertGenRootItem(LPCSTR, int);
	HTREEITEM	InsertFilterRootItem(LPCSTR, int);
	HTREEITEM	InsertObjFeatRootItem(LPCSTR, int);
	HTREEITEM	InsertDefaultItem(HTREEITEM hParent);
	HTREEITEM	InsertGenKeyItem(HTREEITEM hParent, LPCSTR, BOOL fJustInsert = false);
	BOOL		InsertFileOnImport(REFIID riid, LPCSTR lpcstrFileName, BOOL fFirst, HTREEITEM hItem);		
	HTREEITEM	FindRightImportItem(REFIID riid, LPCSTR lpcstrFileName, HTREEITEM hSelItem);

	HRESULT		InsertInitItem(HTREEITEM hItem, LPCSTR lpcstr);

	BOOL		GetNameEndLabelEdit(LPSTR lpstrDefaultName, UINT uiLen);
	CString		GetContainerName(LPCSTR lpcstrFileName);
	BOOL		IsNew (HTREEITEM hItem);
	BOOL		GetRightToken(HTREEITEM hItem, CString & str);
	
	HRESULT		IsSuperItem(HTREEITEM hItem);	
	HTREEITEM	GetSuperItem (HTREEITEM hSubItem, ITreeItem **ppIT);
	UINT		GetCountSuperItem(HTREEITEM hItem, LPCSTR lpcstrDeleted = NULL);
	HTREEITEM	CountOneLevel(HTREEITEM hParItem, LPCSTR lpcstrItemName, UINT & ui);
	BOOL		GetStringListItems(HTREEITEM hItem, LPSTR * lplpstr, UINT ui, LPCSTR lpcstrDeleted = NULL);

	////////////////////////////////////////////////////////////////////////
	// Rechte Maus
	HRESULT RightButtonDown(CPoint point);
};



/////////////////////////////////////////////////////////////////////////////

