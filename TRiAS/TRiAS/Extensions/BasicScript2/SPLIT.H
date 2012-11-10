// split.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplit frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDebuggerCtrl;
class CRelMacroTreeBox;
class CBSSplitterWnd;
class CRelScripts;
struct ITreeItem;

#include "cmbnot.h"

typedef enum {
	FILTER_INSERT =		1,
	GENERAL_INSERT =	2,
	FILTER_IMPORT =		3,
	GENERAL_IMPORT =	4,
	OBJFEAT_INSERT =	5,
	OBJFEAT_IMPORT =	6
} KindOfTreeEntry;

class CSplit : public  CFrameWnd
{
// Attributes
protected:
	DECLARE_DYNCREATE(CSplit)

public:
	CSplit(void);// protected constructor used by dynamic creation
	virtual ~CSplit();

	CBSSplitterWnd    m_Splitter;
	BOOL Init (LPCSTR lpcstrScriptName, BOOL fOpenFile, UINT ui, IObjectManagement *pIOM, IStreamInfo *pISI);
	HRESULT Init (LPCSTR lpcstr, BOOL fOpen, IObjectManagement *pIOM, IStreamInfo *pISI);

	BOOL InitFirst(void);

// Aufbewahrung der Superitems und Subitems, "long" eigentlich RunningScriptsOrg aus Subitems
	CRelScripts * GetRelScripts(void);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:

	void OnUpdateDebugMRU(CMenu *pMenu, int nID);

	// OnIdleZugriff von Mainframe
	afx_msg void OnUpdateDebugCut(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugPause(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugCopy(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugBreakpoint(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugCallstack(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugDelete(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugAddwatch(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugDeletewatch(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugModifyDlg(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugHex(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugEditdialog(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugFind(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugFindNext(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugFonts(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugGo(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugGotoline(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugNewdialog(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugPaste(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugRecording(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugReplace(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugSuspend(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugSyntax(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugTracein(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugTraceover(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugUndo(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugGetHelpOn(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugEditorHelp(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugTriasHelp(CCmdUI* pCmdUI);   
	// Persistenz
	afx_msg void OnUpdateDebugNew(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugOpen(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugSave(CCmdUI* pCmdUI);   
	afx_msg void OnUpdateDebugSaveas(CCmdUI* pCmdUI);  // Export 
	afx_msg void OnUpdateDebugImport(CCmdUI* pCmdUI);  // Export 
	afx_msg void OnUpdateDebugFilterImport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugRemove(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugFilterInsert(CCmdUI* pCmdUI);

	// Generated message map functions
	//{{AFX_MSG(CSplit)
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnMenuSelect( UINT nItemID, UINT nFlags, HMENU hSysMenu ); 
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnExit();
	afx_msg void OnDebugNewFile();
	afx_msg void OnDebugCut();
	afx_msg void OnDebugCopy();
	afx_msg void OnDebugBreakpoint();
	afx_msg void OnDebugCallstack();
	afx_msg void OnDebugDelete();
	afx_msg void OnDebugAddwatch();
	afx_msg void OnDebugDeletewatch();
	afx_msg void OnDebugModifyDlg();
	afx_msg void OnDebugHex();
	afx_msg void OnDebugEditdialog();
	afx_msg void OnDebugFind();
	afx_msg void OnDebugFindnext();
	afx_msg void OnDebugFonts();
	afx_msg void OnDebugGo();
	afx_msg void OnDebugPause();
	afx_msg void OnDebugGotoline();
	afx_msg void OnDebugNewdialog();
	afx_msg void OnDebugPaste();
	afx_msg void OnDebugRecording();
	afx_msg void OnDebugReplace();
	afx_msg void OnDebugSuspend();
	afx_msg void OnDebugSyntax();
	afx_msg void OnDebugTracein();
	afx_msg void OnDebugTraceover();
	afx_msg void OnDebugUndo();
	afx_msg void OnDebugNew();
	afx_msg void OnDebugOpen();
	afx_msg void OnDebugSave();
	afx_msg void OnDebugSaveas();
	afx_msg void OnDebugImport();  
	afx_msg void OnDebugGetHelpOn();
	afx_msg void OnDebugEditorHelp();
	afx_msg void OnDebugTriasHelp();
	afx_msg void OnDebugInsert();   
	afx_msg void OnDebugRemove();   
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDebugFunctionInsert();
	afx_msg void OnUpdateDebugFunctionInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugFilterinproject(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugGeneralinproject(CCmdUI* pCmdUI);
	afx_msg void OnDebugObjfeatinsert();
	afx_msg void OnDebugObjfeatimport();
	afx_msg void OnUpdateDebugObjfeatimport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugObjfeatinsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugNewFile(CCmdUI* pCmdUI);
	afx_msg void OnCombo();
	afx_msg void OnViewProjectbar();
	afx_msg void OnUpdateViewProjectbar(CCmdUI* pCmdUI);
	afx_msg void OnViewDebuggerbar();
	afx_msg void OnUpdateViewDebuggerbar(CCmdUI* pCmdUI);
	afx_msg void OnViewNotificationbar();
	afx_msg void OnUpdateViewNotificationbar(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusbar();
	afx_msg void OnUpdateViewStatusbar(CCmdUI* pCmdUI);
	afx_msg void OnDebugExportall();
	afx_msg void OnUpdateDebugExportall(CCmdUI* pCmdUI);
	afx_msg void OnDebugImportall();
	afx_msg void OnUpdateDebugImportall(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnDebugFilterInsert();   
	afx_msg void OnDebugFilterImport();   
	afx_msg void OnSelTabObjFeat();
	afx_msg void OnSelTabFilter();
	afx_msg void OnSelTabGeneral();

	HRESULT InitTreeAndDebugger(void);

	BOOL OnDebugInitOpen(LPCSTR lpcstr = NULL);
	HRESULT InitOpen(LPCSTR lpcstrScriptName, BOOL fOpenFile);

	DECLARE_MESSAGE_MAP()
	
public:
	///////////////////////////
	// Memberzugriff von aussen
	CStatusBar *	GetStatusbar(void) { return &m_wndStatusBar; }	
	CFrameToolBar *	GetToolbar(void) { return &m_wndToolBar; }	
	HWND			GetDebuggerWnd(void);
	HRESULT			RunModal(void);

	HTREEITEM	GetChildItemSel(ITreeItem **ppIT);
	//////////////////////////////////////////////////////
	// Properties Loaded
	void	SetLoadedItem(ITreeItem* pTI);
	HRESULT GetLoadedItem(ITreeItem** ppI);

	HRESULT SetCode(ebHCODE hCode);
	HRESULT GetCode(ebHCODE *phCode);

	void	GetInitCaretPos (int & ix, int & iy, int & fSelect);
	CString	GetParentName(void);
	CString	GetScriptName(void);
	void	SetDirty(BOOL f);
	BOOL	GetDirty(void);
	BOOL	GetInitNew(void);
	BOOL	GetEditOnly(void);
	void	SetEditOnly(BOOL fEdit);
	//////////////////////////////////////////////////////
	// Properties Selected
	void	SetSelectedItem(ITreeItem* pTI);
	HRESULT GetSelectedItem(ITreeItem** ppI); 
	BOOL	IsLabelEdit_Selected(void);
	int		GetPopUpMenuID(void);
	BOOL	GetInitNew_Selected(void);
	CString GetScriptName_Selected(void);
	CString GetParentName_Selected(void);
	BOOL	IsScript_Selected(void);
	BOOL	IsFunction_Selected(void);
	BOOL	IsFunction(void);
	BOOL	IsScript(void);
	BOOL	IsTreeFocused(void);
	BOOL	IsDebuggerFocused(void);

	////////////////////////////
	// Zum eventuellen Start nach ProectClose/Open, Runtimeerror neues Script
	void	SetStartScript(LPCSTR lpcstr) { 
		ASSERT(lpcstr); if (NULL == lpcstr) return; m_strStartScript = lpcstr; 
	}

	// Zugriff von DebuggerCtrl
	BOOL	GenerateCaption(LPSTR lpstr = NULL);
	int		AskSave(void);
	BOOL	DeleteIfNew(void);
	void	GetTreeRect(RECT *prect);
	void	GetDebuggerRect(RECT *prect);
	void	GetViewRectTree(RECT *prect);
	void	GetViewRectDebugger(RECT *prect);
	HRESULT RunThread (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	
	HRESULT GetGeneralScripts(IObjectManagement **pp);
	HRESULT GetInfoGeneralScripts(IStreamInfo **ppISI);
	HRESULT GetFilterScripts(IObjectManagement **pp);
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI);
	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI);

	HRESULT EnumFunctions(HTREEITEM hItem);
	// Zugriff von Splitter
	BOOL GetInit(void) { return m_fInit; }

	HRESULT OpenOnGo(void);
	HRESULT ResetDebuggerIfOnClose(void);
	void	ResetItems(void);

	BOOL	IsRBTreeMenu();
	void	SetRBTreeMenu(BOOL f);

private:
	HRESULT InitTreeView(IStreamInfo *pISI);
	HRESULT ResetTreeViewIfOnClose();
	BOOL GetFormerManagement (UINT uiManID,
										IObjectManagement *pIOM, 
										IStreamInfo *pISI,
										IObjectManagement **ppIOM, 
										IStreamInfo **ppISI);

	BOOL ModifyMenu						(UINT uiIDTest1, UINT uiIDTest2, UINT uiNewID);
	BOOL ModifyImportInsertMenu_ObjFeat	(void);
	BOOL ModifyImportInsertMenu_Filter	(void);
	BOOL ModifyImportInsertMenu_General	(void);
	///////////////////////////
	// Zugriff auf Splittermember Debugger
	CDebuggerCtrl *		GetDebuggerCtrl(void);
	CRelMacroTreeBox *	GetTreeCtrl(void);
	////////////////////////////
	// Zum eventuellen Start nach ProectClose/Open, Runtimeerror neues Script
	CString m_strStartScript;
	UINT	m_uiStartManID;
	///////////////////////////
	// Sonstige Membervariablen
	CToolBar		m_wndProjectToolBar;	// Toolbar
	CFrameToolBar	m_wndToolBar;		// Toolbar
	CStatusBar		m_wndStatusBar;		// StatusBar
	CNotifBar		m_wndNotifBar;		// ComboToolbar
	HICON			m_hIcon;
	CFont *			m_pSBOldFont;
	int				m_ID_TIMER;
	int				m_iFocus;
	BOOL			m_fInit;

// MRUList-Verwaltung
	UINT 	m_uiMruID;		// MenuID
	struct tagMRUMENU *m_pMRUMenu;	

// Zum richtigen Schliessen des Debuggers
	UINT m_uiWMClose;

// TreeItems
	ITreeItem* m_pILoadedItem;
	ITreeItem* m_pISelItem;

// Sonstige Memberfunktionen
// Initialisierung
	HRESULT CreateMRU (void);
	BOOL CreateProjectToolbar(void);
	BOOL CreateToolbar(void);
	BOOL CreateNotifBar(void);
	BOOL CreateStatusbar(void);
	void SetFontStatusbar(void);
	void SetDebuggerIcon(UINT uiIcon = IDI_MACRO_DEFAULT);
	void SetWindowPosition(void);
	void SetToolbarPos(void);
	void SetWindowSize(void);
	
// Resets
	void ResetDebuggerIcon(void);
	void ResetFontStatusbar(void);
	void EndMRUHandling (void);
	
// Hilfsfunktionen Persistenz
	int AskSaveChanges (LPCSTR lpcstrNext);
	int AskSaveAs (BOOL fRemove);
	BOOL OnDebugMRU(UINT uiID, UINT uiNotifCode);
	HRESULT QuerySaveAs(BOOL fRemove);

	UINT FileDialog (LPCSTR pcPath, CString & strFileName, BOOL fOpen, BOOL fImport, BOOL &fLink);
	UINT FileDialog (LPCSTR pcPath, CString & strFileName, BOOL fOpen = true, LPCSTR lpcstr = NULL);
	UINT OpenFileDialog (LPCSTR pcPath, CString &strFileName, BOOL &fLink);
	BOOL Enable(void);

	HRESULT DeleteLabelEdit(void);
	int Save(LPCSTR lpcstrNext = NULL);
	BOOL Open(LPCSTR lpcstr = NULL);
	BOOL Insert(); 
	BOOL FunctionInsert(void);
	BOOL FunctionInsert(LPCSTR lpcstrType, LPCSTR lpcstrDecl, LPCSTR lpcstrName, LPCSTR lpcstrParams, LPCSTR lpcstrComment);
	int	MessageInsertFunction(LPCSTR lpcstrName);
	BOOL Remove(void);
	BOOL New(void);
	BOOL OpenOther(void);
	BOOL OpenExtern(LPCSTR lpcstr = NULL, BOOL fOpen = true);
	BOOL OpenFromMRU (UINT uiID);
	BOOL SaveLoaded(BOOL fOnImport = false);
	BOOL SaveRelated(void);
	BOOL SaveAs(DWORD dSaveOptions = 0);
	HRESULT ImportAll(void);
	HRESULT SaveAs(ITreeItem *pIT, UINT uiSave, LPCSTR lpcstr, ebHCODE hCode, LPSTR lpstrText, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	BOOL Import();
	BOOL ImportInProject();
	BOOL Delete(void);
	BOOL OpenFile(LPCSTR lpcstr = NULL);
	BOOL NewFile(void);
	BOOL OpenSelected(void);
	BOOL ImportSelectedItem(REFIID riid, LPCSTR lpcstr);
	BOOL ImportSelected(REFIID riid, LPCSTR lpcstr);
	BOOL SaveAsSelected(UINT uiSave, LPCSTR lpcstr, DWORD dSaveOptions = 0);
	BOOL SaveAsLoaded(UINT uiSave, LPCSTR lpcstr, DWORD dSaveOptions = 0);

	BOOL CreateExternItem(LPCSTR lpcstr, REFIID riid, ITreeItem **ppProjScript);
	HRESULT CreateItem(LPCSTR lpcstr, REFIID riid, ITreeItem **ppProjScript);
	BOOL OpenItem(ITreeItem *pITreeItem, ebHCODE *phCode, LPSTR *lplpstr);
	BOOL NewItem(ITreeItem *pITreeItem, LPSTR *lplpstr);
	BOOL ImportItem(ITreeItem *pITreeItem, REFIID riid, LPCSTR lpcstrImport, ebHCODE *phCode, LPSTR *lplpstr);

	HRESULT OnGo();
	HRESULT OnTracein();
	HRESULT OnTraceover(void);

	BOOL SetReadyStatusbarText(void);

// Registry
	BOOL ReadRegSettingsWindow (RECT *pRect, RECT *pRectDebugger, RECT *pRectTree);
	BOOL ReadRegSettingsWindow (LPCSTR lpcstrKey, RECT *pRect);
	BOOL SaveRegSettingsWindow(LPCSTR lpstrKey, RECT & Rect);
	BOOL SaveRegSettingsWindow(void);
	BOOL ParseRectangleInfo (LPSTR pInfo, RECT *pRect);

	void GetDockStyleFromBarStyle(CToolBar* pBar, UINT *puiStyle);
	void Dockingbars(void);
	void DockControlBarLeftOf(CToolBar* pBar,CToolBar* pLeftOf);
	void FixedupSaveBarState (LPCTSTR lpszProfileName);
};

HRESULT CreateDebugger(CWnd *pWnd, LPCSTR lpcstr, BOOL fOpenFile, UINT, IObjectManagement *pIOM, IStreamInfo *pISI, CSplit **);

#define	SIZE_WATCHWINDOWHEIGHT	60	
#define	SIZE_XBORDER			GetSystemMetrics(SM_CXBORDER)
#define	SIZE_YBORDER			GetSystemMetrics(SM_CYBORDER)

/////////////////////////////////////////////////////////////////////////////
