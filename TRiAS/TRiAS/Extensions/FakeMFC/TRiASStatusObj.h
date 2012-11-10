// TRiASStatusObj.h : Declaration of the CTRiASStatusBarObj

#include <toolguid.h>
#include <itoolbar.h>

class CMainFrame;	// forward declaration only

/////////////////////////////////////////////////////////////////////////////
// CTRiASStatusBarObj - Interfaces für CTRiASStatusBar
#if defined(__ATL_20_USED__)
#include "CPTRiASBarNotifySink.h"		// ConnPntProxy
typedef IConnectionPointContainerImpl<class CTRiASStatusBarObj> CComStatusBarCPC;
#else
typedef CComConnectionPointContainerImpl CComStatusBarCPC;
#endif // __ATL_20_USED__

class CTRiASStatusBarObj : 
	public ITRiASStatusBar,
	public IPersistStreamInit,
#if defined(__ATL_20_USED__)
	public CProxyITRiASBarNotifySink<CTRiASStatusBarObj>,
#endif // __ATL_20_USED__
	public CComStatusBarCPC,
	public CComObjectRoot
{
public:
		CTRiASStatusBarObj()
#if !defined(__ATL_20_USED__)
			: m_cpTRiASBarNotifySink(this, &IID_ITRiASBarNotifySink)
#endif // !__ATL_20_USED__
			{ m_pStatusBar = NULL; }
		~CTRiASStatusBarObj();

// unterstützte Interface's
	BEGIN_COM_MAP(CTRiASStatusBarObj)
		COM_INTERFACE_ENTRY(ITRiASStatusBar)
		COM_INTERFACE_ENTRY2(ITRiASBar, ITRiASStatusBar)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
#if !defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IID(IID_IConnectionPointContainer, CComStatusBarCPC)
#else
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#endif // __ATL_20_USED__
	END_COM_MAP()

// unterstützte ConnectionPoints
#if !defined(__ATL_20_USED__)
	CComConnectionPoint<> m_cpTRiASBarNotifySink;
	BEGIN_CONNECTION_POINT_MAP(CTRiASStatusBarObj)
		CONNECTION_POINT_ENTRY(m_cpTRiASBarNotifySink)
	END_CONNECTION_POINT_MAP()

protected:
// Connections informieren/abfragen
	HRESULT OnRequestDeleteItem (UINT uiCtrlID, DWORD dwStyle);
	HRESULT OnDeletedItem (UINT uiCtrlID);
#else
 	BEGIN_CONNECTION_POINT_MAP(CTRiASStatusBarObj)
		CONNECTION_POINT_ENTRY(IID_ITRiASBarNotifySink)
	END_CONNECTION_POINT_MAP()

protected:
// Connections informieren/abfragen
	HRESULT OnRequestDeleteItem (UINT uiCtrlID, DWORD dwStyle)
		{ return Fire_OnRequestDeleteItem(this, uiCtrlID, dwStyle); }
	HRESULT OnDeletedItem (UINT uiCtrlID)
		{ return Fire_OnDeletedItem(this, uiCtrlID); }
#endif

	DECLARE_AGGREGATABLE(CTRiASStatusBarObj)

	HRESULT FinalConstruct (void);

public:
///////////////////////////////////////////////////////////////////////////////
// ITRiASBar specific functions 
	STDMETHOD(GetBarStyle) (THIS_ LPSTR pName, ULONG uiLen, ULONG *pulWritten/*=NULL*/, DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/);
	STDMETHOD(SetBarStyle) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay);
	STDMETHOD(FloatBar) (THIS_ POINT pt, DWORD dwStyle);
	STDMETHOD(DockBar) (THIS_ UINT uiWhere, LPCRECT pcRc/*=NULL*/);
	STDMETHOD(IsFloating) (THIS);
	STDMETHOD(GetBarID) (UINT *puiID);
	STDMETHOD(GetBarHandle) (THIS_ HWND *phWnd);
	STDMETHOD(GetItemRect) (THIS_ int iIndex, LPRECT pRc);
	STDMETHOD(CommandToIndex) (THIS_ UINT uiID, int *piIndex);
	STDMETHOD(DeleteItem) (THIS_ int iIndex);

	STDMETHOD(OnCmdMsg) (THIS_ UINT uiID, int nCode, void *pExtra1, void *pExtra2);

// ITRiASStatusBar specific functions 
	STDMETHOD(SetSimple) (THIS_ BOOL fSimple);
	STDMETHOD(GetPanes) (THIS_ int iCnt, int *piWitdhs/*=NULL*/, int *piRetrieved/*=NULL*/);
	STDMETHOD(SetPanes) (THIS_ const int *piWitdhs, int iCnt);
	STDMETHOD(AddPanes) (THIS_ const int *piWidths, int iCnt, ITRiASUIOwner *pIOwner);
	STDMETHOD(InsertPane) (THIS_ int iIndex, int iWidth, ITRiASUIOwner *pIOwner);
	STDMETHOD(GetPaneInfo) (THIS_ int iIndex, UINT *puiID/*=NULL*/, int *piWidth/*=NULL*/);
	STDMETHOD(SetPaneInfo) (THIS_ int iIndex, UINT uiID, int iWidth);
	STDMETHOD(GetPaneText) (THIS_ int iIndex, LPSTR pText, ULONG ulLen, DWORD *pdwStyle/*=NULL*/);
	STDMETHOD(SetPaneText) (THIS_ int iIndex, LPCSTR pcText, DWORD dwStyle, BOOL fUpdate);

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
	STDMETHOD(GetClassID) (CLSID *pClassID);

// IPersistStreamInit functions
	STDMETHOD(IsDirty) (THIS);
	STDMETHOD(Load) (THIS_ LPSTREAM pStrm);
	STDMETHOD(Save) (THIS_ LPSTREAM pStrm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax) (THIS_ ULARGE_INTEGER * pcbSize);
	STDMETHOD(InitNew) (THIS);

private:
	CTRiASStatusBar *m_pStatusBar;		// zugehörige Toolbar
};
