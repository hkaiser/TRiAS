// MainFrm.h : interface of the CMainFrame class
//

///////////////////////////////////////////////////////////////////////////////
#include <xtensnn.h>
#include <itoolbar.h>
#include <ospace/views/views.h>

#if defined(_USE_SEC_CLASSES)
#include <secdll.h>
#include <sectlf.h>
#include <sbarcust.h>
#else
#define SECToplevelFrame CFrameWnd
#define SECCustomStatusBar CStatusBar
#endif // _USE_SEC_CLASSES

template<class T> class IEnum;		// forward declaration only

/////////////////////////////////////////////////////////////////////////////
// Der ID der ersten generierten Toolbar (MainToolBar)
#define FIRST_TOOLBAR_ID (AFX_IDW_TOOLBAR+5)

///////////////////////////////////////////////////////////////////////////////
// Map, die den ToolBarID's die Toolbars selbst zuordnet
typedef map<UINT, WTRiASToolBar, less<UINT> > TRiASBarsMap;

///////////////////////////////////////////////////////////////////////////////
// View, die aus der ToolbarMap lediglich die Toolbars liefert
typedef map_values<UINT, WTRiASToolBar, less<UINT> > TRiASBars;

class CTRiASToolBar;	// forward declaration
class CTRiASView;

class CMainFrame : 
	public SECToplevelFrame
{
protected:
	void GetFullScreenTBCaption (CString &rStr);
	void AdjustStatusbarForFullScreen (void);
	void ResetStatusbarFromFullScreen (void);
	void AdjustToolbarsForFullScreen (void);
	void ResetToolbarsFromFullScreen (void);

	void GetBlownUpSize (int *pcx, int* pcy);
	void GetBlownUpPosition (int *px, int *py);

	HRESULT CreateToolBar (ITRiASToolBar **ppITools, UINT *puiID = NULL);
	HRESULT InitToolBar (ITRiASToolBar *pITools, 
				LPCSTR pcCaption, DWORD dwStyle, 
				HINSTANCE hInst, UINT uiID, int iCnt, 
				const TBBUTTON *pBttns, int iBttnCnt, 
				ITRiASUIOwner *pIOwner);

	HRESULT DisconnectMainToolBar (ITRiASBar *pIToolBar);
	HRESULT ConnectMainToolBar (ITRiASBar *pIToolBar);

	HRESULT SetFocusItem (UINT uiName, UINT uiCmdID);

protected: // create from serialization only
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	HRESULT InstallToolBars (void);
	HRESULT FreeToolBars (void);
	HRESULT LoadToolbarState (LPCSTR pcKeyName = NULL, LPCSTR pcFileName = NULL);
	HRESULT SaveToolbarState (LPCSTR pcKeyName = NULL, LPCSTR pcFileName = NULL);
	HRESULT InstallStatusBar (void);
	HRESULT FreeStatusBar (void);
	HRESULT HideFloatingBars (void);

	HRESULT CreateMainToolBar (ITRiASToolBar **ppIToolBar = NULL);
	HRESULT CreateStandardToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar = NULL);
	HRESULT CreateGeoViewToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar = NULL);
	HRESULT CreateGeoClassToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar = NULL);
	HRESULT CreateFullScreenToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar = NULL);
	HRESULT CreateCoordsToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar);
	HRESULT DockControlBarLeftOf (ITRiASToolBar *pIBar, ITRiASToolBar *pILeftOf);

	UINT GetNextBarID (void);
	bool ShowToolTips (void) { return m_fShowToolTips ? true : false; }
	void NotifyAboutToolTips (void) { DEXN_ShowToolTips(ShowToolTips()); }

	HRESULT GetTRiASToolBar (UINT uiID, ITRiASToolBar **ppIToolBar);
	HRESULT GetTRiASToolBar (LPCSTR pcName, ITRiASToolBar **ppIToolBar);

// Operations
public:
	HRESULT AddNewBar (ITRiASBar *pBar);
	HRESULT RemoveBar (ITRiASBar *pBar);
	HRESULT RemapBarID (ITRiASBar *pBar, UINT uiOldID, UINT uiNewID);

	void ShowToolBarDlg (void) { OnToolbars(); }
	void OnViewFullScreen (void);
	void FixedupSaveBarState (LPCTSTR lpszProfileName) const;
	void FixedupLoadBarState (LPCSTR pcKeyName);

	CTRiASView *CreateSubclassedView (CCreateContext* pContext, HWND hWndView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	CMainFrame (void);
	virtual ~CMainFrame();

	void SetDepUnk (IUnknown *pIUnk);

	HRESULT GetEnumTRiASToolBars (IEnumITRiASBar **ppIEnum, LONG *plCount = NULL);
	bool IsFullScreen (void) { return m_bBlownUpMode ? true : false; }

#if defined(_USE_SEC_CLASSES)
// zusätzliche Funktionen für SECToolBars
// Bitmap zu ButtonPool hinzufügen
	HRESULT AddBitmap (HINSTANCE hInst, UINT uiRsc, int iBttnCnt, int *piOffset);
	HRESULT AddButtons (CTRiASToolBar *pBar, int iBttnCnt, const TBBUTTON *pBttns, ITRiASUIOwner *pUIOwner);
	HRESULT InsertButton (CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pUIOwner);
	HRESULT DeleteButton (CTRiASToolBar *pBar, int iIndex);
	HRESULT GetButton (const CTRiASToolBar *pBar, int iIndex, TBBUTTON *pBttn);
	HRESULT GetUIOwner (CTRiASToolBar *pBar, int iIndex, ITRiASUIOwner **ppIOwner);
	HRESULT ResetToolBar (CTRiASToolBar *pBar);

	void DefineDefaultToolBar (
		UINT nID, LPCTSTR lpszTitle, const TBBUTTON *pBttns, UINT nBtnCount, 
		DWORD dwAlignment = CBRS_ALIGN_ANY, UINT nDockBarID = AFX_IDW_DOCKBAR_TOP, 
		UINT nDockNextToID = 0,	BOOL bDocked = TRUE, BOOL bVisible = TRUE);

	HRESULT CreateToolBar (LPCSTR pcCaption, ITRiASToolBar **ppITools);

	BOOL CoolLookEnabled (void);
#endif // _USE_SEC_CLASSES

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	IUnknown *m_pITRiASExt;			// unsere Erweiterung
	SECCustomStatusBar m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg void OnCommandToolBarPopup(UINT nID);
	afx_msg void OnUpdateToolBarPopup(CCmdUI* pCmdUI);

	//{{AFX_MSG(CMainFrame)
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnClose();
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnToolbars();
	afx_msg void OnToolbarCustomize();
	afx_msg void OnUpdateToolbarCustomize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolbars(CCmdUI* pCmdUI);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnIdleUpdateCmdUI();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LONG OnToolBarWndNotify(UINT wParam, LONG lParam);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG

public:
	afx_msg void OnEditScaling();
	afx_msg void OnSelectActview();
	afx_msg void OnNcDestroy();
	afx_msg void OnContextMenu(CWnd *pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
#if defined(_USE_SEC_CLASSES)
	void RecalcLayout (BOOL fNotify = TRUE);
	void ResetInvalidDockbars (CControlBar *pBar = NULL);
#endif // _USE_SEC_CLASSES

protected:
	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(TRiASBarNotifySink, ITRiASBarNotifySink)
		STDMETHOD(OnRequestAddButtons) (THIS_ ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt);
		STDMETHOD(OnAddedButtons) (THIS_ ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt);
		STDMETHOD(OnRequestDeleteItem) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle);
		STDMETHOD(OnDeletedItem) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID);
	END_INTERFACE_PART(TRiASBarNotifySink)

public:		// data members

private:
	bool m_bBlownUpMode;		// BlowUpMode
	CRect m_rNonBlownUpRect;
	HACCEL m_hAccelEsc;
	HACCEL m_hAccelMisc;

	DWORD m_dwCookie;			// Connection zu MainToolbar

	UINT m_uiBarID;				// nächster Verfügbarer ID
	CCriticalSection m_Sync;	// synchronisieren aller Threads
	TRiASBarsMap m_mapBars;		// installierte Toolbars
	bool m_fShowToolTips;		// ToolTips anzeigen
};

/////////////////////////////////////////////////////////////////////////////
