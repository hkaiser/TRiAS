// MainFrm.h : interface of the CMainFrame class
//

///////////////////////////////////////////////////////////////////////////////
//
#include <xtensnn.h>
#include <itoolbar.h>
#include <ospace/views/views.h>

#if defined(_USE_SEC_CLASSES)
#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <sectlf.h>
#include <sbarcust.h>
#if defined(_SEC_USE_TABWND)
#include <tabwnd.h>
#endif // _SEC_USE_TABWND
#if defined(_SEC_SUBCLASS_ORWND)
#include <ot_AdvDockingWindows.h>
#endif // _SEC_SEC_SUBCLASS_ORWND
#else
#define SECToplevelFrame CFrameWnd
#define CMainStatusBar CStatusBar
#endif // _USE_SEC_CLASSES

///////////////////////////////////////////////////////////////////////////////
// Verwaltung aller DockingTabFenster

#if defined(_USE_DOCKEDTABWINDOW)
#include <ospace/std/map>
#include <ospace/stlex/pointainer.h>
#include <Com/GuidHelpers.h>

#include <SidManageTabs.h>
#include "DockingTabFrame.h"

///////////////////////////////////////////////////////////////////////////////
// Infos, die zu einem DockingTabFrame benötigt werden
class CMainFrame;

template<typename DockingTabFrameT>
class CDockingTabFrameWrapper :
	public DockingTabFrameT
{
public:
	CDockingTabFrameWrapper() :	m_dwShouldBeAddedToMenu(0) {}
	~CDockingTabFrameWrapper() {}

	bool GetShouldBeAddedToMenu() { return m_dwShouldBeAddedToMenu ? true : false; }

	bool CreateFromRegistry(CMainFrame *pParent, REFGUID guidSid);

private:
	DWORD m_dwShouldBeAddedToMenu;
};

class CManageDockingTabFrames
{
public:
	CManageDockingTabFrames() {}
	~CManageDockingTabFrames() {}

	CDockingTabFrameWrapper<CDockingTabFrame> *GetTabInfo(REFGUID guidSid);

	template<typename DockingTabFrameT>
	CDockingTabFrameWrapper<CDockingTabFrame> *CreateTabInfo(
		CMainFrame *pParent, REFGUID guidSid, DockingTabFrameT *);

	void OnContextMenu(int &i, CMenu *pPopup);
	void InitToolbarMenu(int &i, CMenu *pMenu);
	void OnUpdateToolBarPopup(CCmdUI* pCmdUI);
	bool OnToolbarCommand (CMainFrame *pFrame, UINT nID);

protected:
	
private:
	typedef 
		map<GUID, CDockingTabFrameWrapper<CDockingTabFrame> *, less<GUID> > 
		CDockingTabFrameMap;
	typedef 
		pointainer<CDockingTabFrameMap, clean_pair_second<CDockingTabFrameMap> >
		CDockingTabFrames;
	typedef 
		pair<GUID, CDockingTabFrameWrapper<CDockingTabFrame> *>
		CDockingTabFramesType;
	CDockingTabFrames m_Frames;
};

#endif // defined(_USE_DOCKEDTABWINDOW)

#if defined(_USE_SEC_CLASSES)
/////////////////////////////////////////////////////////////////////////////
// TRiAS-Statusbar
class CMainStatusBar :
	public SECCustomStatusBar
{
protected:
	CString m_strProgressText;

public:
	ULONG SetProgressStep(ULONG ulStep)						// Schrittweite setzen
	{
		_ASSERTE(m_pProgressCtrl != NULL);
		if (m_pProgressCtrl != NULL)
			return m_pProgressCtrl->SetStep(ulStep);
		return 0L;
	}
	void SetProgressColors(COLORREF fgnd,COLORREF bgnd)		// Farben setzen
	{
		_ASSERTE(m_pProgressCtrl != NULL);
		if (m_pProgressCtrl != NULL)
			m_pProgressCtrl->SetColors(fgnd, bgnd);
	}
	void SetProgressFont(CFont* pFont,BOOL bRedraw)			// Font einstellen
	{
		_ASSERTE(m_pProgressCtrl != NULL);
		if (m_pProgressCtrl != NULL)
			m_pProgressCtrl->SetFont(pFont, bRedraw);
	}
	void SetProgressExStyle(DWORD dwExNewStyle)
	{
		_ASSERTE(m_pProgressCtrl != NULL);
		if (m_pProgressCtrl != NULL)
			m_pProgressCtrl->SetExStyle(dwExNewStyle);
	}
	void SetProgressText (LPCSTR pcText)
	{
		m_strProgressText = pcText;
	}
	CString GetProgressText() { return m_strProgressText; }

	void UpdateStatusBar(BOOL fInvalidate) { if (fInvalidate) InvalidateRect(NULL); UpdateWindow(); }
};
#endif // _USE_SEC_CLASSES

/////////////////////////////////////////////////////////////////////////////
// 
template<class T> class IEnum;		// forward declaration only

/////////////////////////////////////////////////////////////////////////////
// Der ID der ersten generierten Toolbar (MainToolBar)
#define FIRST_TOOLBAR_ID (AFX_IDW_TOOLBAR+6)

///////////////////////////////////////////////////////////////////////////////
// Map, die den ToolBarID's die Toolbars selbst zuordnet
typedef map<UINT, WTRiASToolBar, less<UINT> > TRiASBarsMap;

///////////////////////////////////////////////////////////////////////////////
// View, die aus der ToolbarMap lediglich die Toolbars liefert
typedef map_values<UINT, WTRiASToolBar, less<UINT> > TRiASBars;

class CTRiASToolBar;		// forward declaration
class CTRiASView;
class CManageConnections;

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
	HRESULT CreateConnectFilterToolBar (ITRiASUIOwner *pIUIOwner, ITRiASToolBar **ppIToolBar);
	HRESULT DockControlBarLeftOf (ITRiASToolBar *pIBar, ITRiASToolBar *pILeftOf);

	UINT GetNextBarID (void);
	bool ShowToolTips (void) { return m_fShowToolTips ? true : false; }
	void EnableToolTips (BOOL fFlag) { m_fShowToolTips = fFlag; DEXN_ShowToolTips(m_fShowToolTips); }
	void NotifyAboutToolTips (void) { DEXN_ShowToolTips(ShowToolTips()); }

	HRESULT GetTRiASToolBar (UINT uiID, ITRiASToolBar **ppIToolBar);
	HRESULT GetTRiASToolBar (LPCSTR pcName, ITRiASToolBar **ppIToolBar);

// Operations
public:
	HRESULT AddNewBar (ITRiASBar *pBar);
	HRESULT RemoveBar (ITRiASBar *pBar);
	HRESULT RemapBarID (ITRiASBar *pBar, UINT uiOldID, UINT uiNewID);

//	void ShowToolBarDlg (void) { OnToolbars(); }
	void OnViewFullScreen (void);
	void FixedupSaveBarState (LPCTSTR lpszProfileName) const;
	void FixedupLoadBarState (LPCSTR pcKeyName);
	void OnManageConnections (void);
	void OnManageConnectFilters();
	void OnShowConnectFilters();
	void OnCreateConnectFilter(HWND hWnd = NULL);

	CTRiASView *CreateSubclassedView (CCreateContext* pContext, HWND hWndView);
#if defined(_SEC_USE_TABWND)
	void OnDeleteSubclassedView (HWND hWndView);
#endif // defined(_SEC_USE_TABWND)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMainFrame (void);
	virtual ~CMainFrame();

	void SetDepUnk (IUnknown *pIUnk);

	HRESULT GetEnumTRiASToolBars (IEnumITRiASBar **ppIEnum, LONG *plCount = NULL);
	bool IsFullScreen (void) { return m_bBlownUpMode ? true : false; }
	bool InitToolbarMenu (CMenu *pMenu);
	bool OnToolbarCommand (UINT nID);

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
	HRESULT RemoveHiddenButtons (ITRiASToolBar *pITBar, const UINT *puiIDs, int iCnt);

	void DefineDefaultToolBar (
		UINT nID, LPCTSTR lpszTitle, const TBBUTTON *pBttns, UINT nBtnCount, 
		DWORD dwAlignment = CBRS_ALIGN_ANY, UINT nDockBarID = AFX_IDW_DOCKBAR_TOP, 
		UINT nDockNextToID = 0,	BOOL bDocked = TRUE, BOOL bVisible = TRUE);

	HRESULT CreateToolBar (LPCSTR pcCaption, ITRiASToolBar **ppITools);

	BOOL CoolLookEnabled (void);
	void EnableCoolLook (BOOL fFlag);

// Statusbar steuern
	BOOL IsProgressControlActive() const { return m_wndStatusBar.IsProgressControlActive(); } 
	void StepProgress() { m_wndStatusBar.StepProgress(); }
	void SetProgress(int iPos) { m_wndStatusBar.SetProgress(iPos); }
	BOOL InitializeProgressControl(LPCTSTR pcszMsg = NULL, int iLow = 0, int iHigh = 100, BOOL bResetPos = TRUE)
		{ return m_wndStatusBar.InitializeProgressControl (pcszMsg, iLow, iHigh, bResetPos); }
	void UninitializeProgressControl() { m_wndStatusBar.UninitializeProgressControl(); }
	ULONG SetProgressStep(ULONG ulStep)						// Schrittweite setzen
		{ return m_wndStatusBar.SetProgressStep(ulStep); }
	void SetProgressColors(COLORREF fgnd,COLORREF bgnd)		// Farben setzen
		{ m_wndStatusBar.SetProgressColors(fgnd, bgnd); }
	void SetProgressFont()			// Font einstellen
		{ m_wndStatusBar.SetProgressFont (m_wndStatusBar.GetFont(), FALSE); }
	void SetProgressExStyle(DWORD dwExNewStyle)
		{ m_wndStatusBar.SetProgressExStyle(dwExNewStyle); }
	void SetProgressText(LPCSTR pcText)	{ m_wndStatusBar.SetProgressText (pcText); }
	CString GetProgressText() { return m_wndStatusBar.GetProgressText(); }
	void UpdateStatusBar(BOOL fInvalidate = FALSE) { m_wndStatusBar.UpdateStatusBar(fInvalidate); }

// Creates the caption text font for the application name
	void CreateCaptionAppFont (CFont& font);
#endif // _USE_SEC_CLASSES

	BOOL ManageConnectionsIsOpen() { return NULL != m_pManageConnections; }
	void RefreshConnections();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	IUnknown *m_pITRiASExt;				// unsere Erweiterung
	CMainStatusBar m_wndStatusBar;

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
//	afx_msg void OnToolbars();
#if defined(_USE_PRINT_PREVIEW)
	afx_msg void OnPrintPreview();
#endif // defined(_USE_PRINT_PREVIEW)

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

#if defined(_SEC_USE_TABWND)
	BEGIN_INTERFACE_PART(TRiASConnectionEvents, ITRiASConnectionEvents)
		STDMETHOD(GetTypeInfoCount)(UINT* pctinfo);
		STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
		STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
		STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr);

		STDMETHOD(CreatingConnection)(BSTR Name, VARIANT_BOOL *pVal);
		STDMETHOD(ConnectionToCreate)(BSTR Name);
		STDMETHOD(ConnectionCreated)(IDispatch *pIConn);
		STDMETHOD(OpeningConnection)(BSTR Name, VARIANT_BOOL *pVal);
		STDMETHOD(ConnectionToOpen)(BSTR Name);
		STDMETHOD(ConnectionOpened)(IDispatch *pIConn);
		STDMETHOD(ClosingConnection)(IDispatch *pIConn, VARIANT_BOOL *pVal);
		STDMETHOD(ConnectionToClose)(IDispatch *pIConn);
		STDMETHOD(ConnectionClosed)(BSTR Name);
		STDMETHOD(DeletingConnection)(IDispatch *pIConn, VARIANT_BOOL *pVal);
		STDMETHOD(ConnectionToDelete)(IDispatch *pIConn);
		STDMETHOD(ConnectionDeleted)(BSTR Name);
		STDMETHOD(RenamingConnection)(BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal);
		STDMETHOD(ConnectionToRename)(BSTR OldName, BSTR NewName);
		STDMETHOD(ConnectionRenamed)(IDispatch *pIConn);
		STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
		STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
		STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);
	END_INTERFACE_PART(TRiASConnectionEvents)

	BEGIN_INTERFACE_PART(TRiASProjectEvents, ITRiASProjectEvents)
		STDMETHOD(GetTypeInfoCount)(UINT* pctinfo);
		STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
		STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
		STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr);

		STDMETHOD(ProjectToCreate)(BSTR Name);
		STDMETHOD(ProjectCreated)(IDispatch *pIPrj);
		STDMETHOD(OpeningProject)(BSTR Name, VARIANT_BOOL *pVal);
		STDMETHOD(ProjectToOpen)(BSTR Name);
		STDMETHOD(ProjectOpened)(IDispatch *pIPrj);
		STDMETHOD(ClosingProject)(IDispatch *pIPrj, VARIANT_BOOL *pVal);
		STDMETHOD(ProjectToClose)(IDispatch *pIPrj);
		STDMETHOD(ProjectClosed)(BSTR Name);
		STDMETHOD(Save)(IDispatch *pIPrj, IUnknown *Stg, VARIANT_BOOL fSameAsLoad);
		STDMETHOD(SaveCompleted)(IDispatch *pIPrj, VARIANT Stg);
		STDMETHOD(HandsOffStorage)(IDispatch *pIPrj);
	END_INTERFACE_PART(TRiASProjectEvents)
#endif // defined(_SEC_USE_TABWND)

#if defined(_USE_DOCKEDTABWINDOW)
	void OnOpenDocument();
	void OnClosingDocument();
#endif // defined(_USE_DOCKEDTABWINDOW)

#if defined(_SEC_USE_TABWND)
public:
	HRESULT ConnectProject(ITRiASDBEngine *pIDBEng);
	HRESULT DisconnectProject(ITRiASDBEngine *pIDBEng);

	HRESULT ConnectConnections(ITRiASProject *pIPrj);
	HRESULT DisconnectConnections(ITRiASProject *pIPrj);
	HRESULT AddConnection (ITRiASConnection *pIConn);
	HRESULT RemoveConnection (ITRiASConnection *pIConn);
#endif // defined(_SEC_USE_TABWND)

#if defined(_SEC_SUBCLASS_ORWND)
	BOOL CreateDockableORWnd (CWnd *pWnd);
	BOOL FreeDockableORWnd (CWnd *pWnd);
#endif // _SEC_SUBCLASS_ORWND

public:		// data members

private:
	BOOL m_bBlownUpMode;		// BlowUpMode
	CRect m_rNonBlownUpRect;
	HACCEL m_hAccelEsc;
	HACCEL m_hAccelMisc;

	DWORD m_dwCookie;			// Connection zu MainToolbar

	UINT m_uiBarID;				// nächster Verfügbarer ID
	CCriticalSection m_Sync;	// synchronisieren aller Threads
	TRiASBarsMap m_mapBars;		// installierte Toolbars
	BOOL m_fShowToolTips;		// ToolTips anzeigen

	CManageConnections *m_pManageConnections;		// Dialog ManageConnections ist derzeit angezeigt

#if defined(_SEC_USE_TABWND)
	SECTabWnd m_tabWnd;			// Tabfenster für alle Datenquellen
	DWORD m_dwPrjCookie;
	DWORD m_dwConnCookie;
#endif // defined(_SEC_USE_TABWND)

#if defined(_SEC_SUBCLASS_ORWND)
	SECLayoutDockFactory m_LFactory;
    SECFrameDockingFeature m_dockFeat;
#endif // _SEC_SUBCLASS_ORWND

#if defined(_USE_DOCKEDTABWINDOW)
	friend CManageDockingTabFrames;
	CManageDockingTabFrames m_TabFrames;

	CDockingProjectTabFrame m_tabDockedWnd;		// Legende etc.
	CDockingTabFrame m_tabOverviewWnd;			// Gesamtübersichten
	CDockingTabFrame m_tabSABiSWnd;				// SABiS

public:
	bool ProjectBarIsVisible();
	bool OverviewBarIsVisible();
	bool SABiSBarIsVisible();
	bool SABiSBar2IsVisible();
	bool GenericBarIsVisible(REFGUID guidSid);

	CDockingTabFrame *GetTabbedBar (REFGUID guidSid);
	CDockingProjectTabFrame *GetProjectInfoBar() { return (CDockingProjectTabFrame *)GetTabbedBar(SID_ManageProjectTabs); }
	CDockingTabFrame *GetOverviewBar() { return GetTabbedBar(SID_ManageOverviewTabs); }
	CDockingTabFrame *GetSABiSBar() { return GetTabbedBar(SID_ManageSABiSTabs); }
	CDockingTabFrame *GetSABiSBar2() { return GetTabbedBar(SID_ManageSABiSTabs2); }
#endif // defined(_USE_DOCKEDTABWINDOW)

public:
	friend class CFakeMFCExtension;
};

/////////////////////////////////////////////////////////////////////////////
