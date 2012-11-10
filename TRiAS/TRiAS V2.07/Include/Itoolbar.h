// Interfacedeklarationen für Toolbars etc. -----------------------------------
// File: ITOOLBAR.H

#if !defined(_ITOOLBAR_H)
#define _ITOOLBAR_H

///////////////////////////////////////////////////////////////////////////////
// CmdUI Interface, über welches der Status der einzelnen UserInterfaceObjekte 
// beeinflußt werden kann.
// 07963838-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TRiASToolUI, 0x07963838L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 0796383A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TRiASMenuUI, 0x0796383AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 0796383B-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TRiASStatusUI, 0x0796383BL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
#undef INTERFACE
#define INTERFACE ITRiASCmdUI

// 07963839-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASCmdUI, 0x07963839L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASCmdUI, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASCmdUI methods
	STDMETHOD(put_IsEnabled) (THIS_ VARIANT_BOOL fEnable) PURE;
	STDMETHOD(put_CheckState) (THIS_ int iState) PURE; 
	STDMETHOD(put_IsOn) (THIS_ VARIANT_BOOL fOn) PURE;
	STDMETHOD(put_Text) (THIS_ BSTR bstrNewText) PURE;

	STDMETHOD(get_CmdID) (THIS_ int *puiID) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface welches durch (Tool-, Status-, etc.) Bar implementiert ist.
#undef INTERFACE
#define INTERFACE ITRiASBar

// 07963850-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TRiASBar, 0x07963850L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// 07963851-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASBar, 0x07963851L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASBar, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBar specific functions ***
	STDMETHOD(GetBarStyle) (THIS_ LPSTR pName, ULONG ulLen, ULONG *pulWritten/*=NULL*/, DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/) PURE;
	STDMETHOD(SetBarStyle) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay) PURE;
	STDMETHOD(FloatBar) (THIS_ POINT pt, DWORD dwStyle) PURE;
	STDMETHOD(DockBar) (THIS_ UINT uiWhere, LPCRECT pcRc/*=NULL*/) PURE;
	STDMETHOD(IsFloating) (THIS) PURE;
	STDMETHOD(GetBarID) (THIS_ UINT *puiID) PURE;
	STDMETHOD(GetBarHandle) (THIS_ HWND *phWnd) PURE;
	STDMETHOD(GetItemRect) (THIS_ int iIndex, LPRECT pRc) PURE;
	STDMETHOD(CommandToIndex) (THIS_ UINT uiID, int *piIndex) PURE;
	STDMETHOD(DeleteItem) (THIS_ int iIndex) PURE;

	STDMETHOD(OnCmdMsg) (THIS_ UINT nID, int nCode, void *pExtra1, void *pReserved) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface welches durch Toolbar implementiert ist.
#undef INTERFACE
#define INTERFACE ITRiASToolBar

struct ITRiASUIOwner;		// forward declaration only

// 07963835-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TRiASToolBar, 0x07963835L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// 07963836-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASToolBar, 0x07963836L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASToolBar, ITRiASBar)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBar specific functions ***
	STDMETHOD(GetBarStyle) (THIS_ LPSTR pName, ULONG ulLen, ULONG *pulWritten/*=NULL*/, DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/) PURE;
	STDMETHOD(SetBarStyle) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay) PURE;
	STDMETHOD(FloatBar) (THIS_ POINT pt, DWORD dwStyle) PURE;
	STDMETHOD(DockBar) (THIS_ UINT uiWhere, LPCRECT pcRc/*=NULL*/) PURE;
	STDMETHOD(IsFloating) (THIS) PURE;
	STDMETHOD(GetBarID) (UINT *puiID) PURE;
	STDMETHOD(GetBarHandle) (THIS_ HWND *phWnd) PURE;
	STDMETHOD(GetItemRect) (THIS_ int iIndex, LPRECT pRc) PURE;
	STDMETHOD(CommandToIndex) (THIS_ UINT uiID, int *piIndex) PURE;
	STDMETHOD(DeleteItem) (THIS_ int iIndex) PURE;

	STDMETHOD(OnCmdMsg) (THIS_ UINT nID, int nCode, void *pExtra1, void *pReserved) PURE;

// *** ITRiASToolBar specific functions ***
	STDMETHOD(GetButtonStyle) (THIS_ int iIndex, UINT *puiStyle) PURE;
	STDMETHOD(SetButtonStyle) (THIS_ int iIndex, UINT uiStyle) PURE;
	STDMETHOD(AddBitmap) (THIS_ HINSTANCE hInst, UINT uiRsc, int NumButtons, int *pIOffset/*=NULL*/) PURE;
	STDMETHOD(AddButtons) (THIS_ const TBBUTTON *pBttns, int iCnt, ITRiASUIOwner *pIOwner) PURE;
	STDMETHOD(InsertButton) (THIS_ int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pIOwner) PURE;
	STDMETHOD(GetButton) (THIS_ int iIndex, TBBUTTON *pBttn/*=NULL*/, ITRiASUIOwner **pIOwner/*=NULL*/) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface welches durch Toolbar implementiert ist.
#undef INTERFACE
#define INTERFACE ITRiASStatusBar

// 0796386C-3123-101C-BB62-00AA0018497C
// DEFINE_GUID(CLSID_TRiASStatusBar, 0x0796386CL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// 0796386D-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASStatusBar, 0x0796386DL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASStatusBar, ITRiASBar)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBar specific functions ***
	STDMETHOD(GetBarStyle) (THIS_ LPSTR pName, ULONG ulLen, ULONG *pulWritten/*=NULL*/, DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/) PURE;
	STDMETHOD(SetBarStyle) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay) PURE;
	STDMETHOD(FloatBar) (THIS_ POINT pt, DWORD dwStyle) PURE;
	STDMETHOD(DockBar) (THIS_ UINT uiWhere, LPCRECT pcRc/*=NULL*/) PURE;
	STDMETHOD(IsFloating) (THIS) PURE;
	STDMETHOD(GetBarID) (UINT *puiID) PURE;
	STDMETHOD(GetBarHandle) (THIS_ HWND *phWnd) PURE;
	STDMETHOD(GetItemRect) (THIS_ int iIndex, LPRECT pRc) PURE;
	STDMETHOD(CommandToIndex) (THIS_ UINT uiID, int *piIndex) PURE;
	STDMETHOD(DeleteItem) (THIS_ int iIndex) PURE;

	STDMETHOD(OnCmdMsg) (THIS_ UINT nID, int nCode, void *pExtra1, void *pReserved) PURE;

// *** ITRiASStatusBar specific functions ***
	STDMETHOD(SetSimple) (THIS_ BOOL fSimple) PURE;
	STDMETHOD(GetPanes) (THIS_ int iCnt, int *piWitdhs/*=NULL*/, int *piRetrieved/*=NULL*/) PURE;
	STDMETHOD(SetPanes) (THIS_ const int *piWitdhs, int iCnt) PURE;
	STDMETHOD(AddPanes) (THIS_ const int *piWidths, int iCnt, ITRiASUIOwner *pIOwner) PURE;
	STDMETHOD(InsertPane) (THIS_ int iIndex, int iWidth, ITRiASUIOwner *pIOwner) PURE;
	STDMETHOD(GetPaneInfo) (THIS_ int iIndex, UINT *puiID/*=NULL*/, int *piWidth/*=NULL*/) PURE;
	STDMETHOD(SetPaneInfo) (THIS_ int iIndex, UINT uiID, int iWidth) PURE;
	STDMETHOD(GetPaneText) (THIS_ int iIndex, LPSTR pText, ULONG ulLen, DWORD *pdwStyle/*=NULL*/) PURE;
	STDMETHOD(SetPaneText) (THIS_ int iIndex, LPCSTR pcText, DWORD dwStyle, BOOL fUpdate) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// Interface welches durch den Nutzer einer Toolbar implementiert ist.
#undef INTERFACE
#define INTERFACE ITRiASUIOwner

// 07963837-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASUIOwner, 0x07963837L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASUIOwner, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASUIOwner specific functions ***
	STDMETHOD(OnUpdateUI) (THIS_ ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI) PURE;
	STDMETHOD(OnSelect) (THIS_ ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten/*=NULL*/) PURE;
	STDMETHOD(OnCommand) (THIS_ ITRiASBar *pIBar, UINT uiID, int nCode) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface welches durch den Nutzer einer Toolbar implementiert ist.
#undef INTERFACE
#define INTERFACE IEnumITRiASBar

// 07963853-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumITRiASBar, 0x07963853L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IEnumITRiASBar, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IEnumTRiASBars specific functions ***
	STDMETHOD (Next) (THIS_ ULONG celt, ITRiASBar **rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD (Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD (Reset) (THIS) PURE;
	STDMETHOD (Clone) (THIS_ IEnumITRiASBar **ppenm) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface über welches Toolbars von außen verfügbar werden
#undef INTERFACE
#define INTERFACE ITRiASBarContainer

// 07963855-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASBarContainer, 0x07963855L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASBarContainer, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBarContainer specific functions ***
	STDMETHOD(EnumTRiASBars) (THIS_ IEnumITRiASBar **ppEnum) PURE;
	STDMETHOD(FindTRiASBar) (THIS_ LPCSTR pcName, ITRiASBar **pIBar) PURE;
	STDMETHOD(AddTRiASBar) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, ITRiASBar **pIBar) PURE;
	STDMETHOD(DeleteTRiASBar) (THIS_ LPCSTR pcName) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface über welches Toolbars die Außenwelt darüber informieren, bzw. 
// nachfragen, daß(ob) etwas geändert werden soll(darf) 
#undef INTERFACE
#define INTERFACE ITRiASBarNotifySink

// 07963856-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASBarNotifySink, 0x07963856L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASBarNotifySink, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBarNotifySink specific functions ***
	STDMETHOD(OnRequestAddButtons) (THIS_ ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt) PURE;
	STDMETHOD(OnAddedButtons) (THIS_ ITRiASBar *pIBar, int iIndex, const TBBUTTON *pBttn, int iCnt) PURE;
	STDMETHOD(OnRequestDeleteItem) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle) PURE;
	STDMETHOD(OnDeletedItem) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface, welches verwendet wird, um in eine TRiASToolBar ein beliebiges
// anderes WindowsControl (ComboBox etc.) einzubauen.
#undef INTERFACE
#define INTERFACE ITRiASBarInstallControl

// 07963859-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASBarInstallControl, 0x07963859L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASBarInstallControl, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASBarInstallControl specific functions ***
	STDMETHOD(InstallControl) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle) PURE;
	STDMETHOD(GetConnectedControl) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle, UINT *puiConnID) PURE;
	STDMETHOD(GetAdjustedInfo) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle, TBBUTTON *pBttn) PURE;
	STDMETHOD(AdjustControl) (THIS_ ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Flags für dwStyleEx
#define TRIASTOOLBAR_PREDEFINED		0x80000000L		// vordefinierte ToolBar
#define TRIASTOOLBAR_HIDDENTAG		0x40000000L		// Flag für FullScreenMode

#define TRIASTOOLBAR_FLAGS			0xF0000000L		// alle Flags zusammen

#endif // _ITOOLBAR_H
