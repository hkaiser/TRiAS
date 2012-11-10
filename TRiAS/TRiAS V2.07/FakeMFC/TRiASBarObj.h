// TRiASBarObj.h : Declaration of the CTRiASToolBar

#include <toolguid.h>
#include <itoolbar.h>
#include <dtoolbar.h>

class CMainFrame;	// forward declaration only
class CTRiASToolBar;

/////////////////////////////////////////////////////////////////////////////
// CTRiASToolBarObj - Interfaces für CTRiASToolBar
typedef CComConnectionPointContainerImpl CComToolBarCPC;
//typedef CComConnectionPointContainerImpl<CComDynamicArrayCONNECTDATA> CComToolBarCPC;

/////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterface's
DefineSmartInterface2(DControlToolBarButton, IID_DControlToolBarButton);

class CTRiASToolBarObj : 
	public ITRiASToolBar,
	public IPersistStreamInit,
	public IControlToolBar,
	public CComDualImpl<DControlToolBar, &IID_DControlToolBar, &LIBID_ToolBarLib, 
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_DControlToolBar>,
	public CComToolBarCPC,
	public CComObjectRoot,
	public CComCoClass<CTRiASToolBarObj, &CLSID_TRiASToolBar>,
	public CObject
{
	DECLARE_DYNCREATE(CTRiASToolBarObj)

public:
	typedef map<UINT, WDControlToolBarButton, less<UINT> > CButtons;

		CTRiASToolBarObj() :
			m_cpTRiASBarNotifySink(this, &IID_ITRiASBarNotifySink)
			{ m_pToolBar = NULL; }
		~CTRiASToolBarObj();

// unterstützte Interface's
	BEGIN_COM_MAP(CTRiASToolBarObj)
		COM_INTERFACE_ENTRY(IControlToolBar)
		COM_INTERFACE_ENTRY(ITRiASToolBar)
		COM_INTERFACE_ENTRY2(ITRiASBar, ITRiASToolBar)
		COM_INTERFACE_ENTRY_IID(IID_IConnectionPointContainer, CComToolBarCPC)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_IID(IID_DControlToolBar, DControlToolBar)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASBaseClass, DControlToolBar)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// unterstützte ConnectionPoints
	CComConnectionPoint<> m_cpTRiASBarNotifySink;
	BEGIN_CONNECTION_POINT_MAP(CTRiASToolBarObj)
		CONNECTION_POINT_ENTRY(m_cpTRiASBarNotifySink)
	END_CONNECTION_POINT_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASToolBarObj)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASBAROBJ_REG)	// registry

	HRESULT FinalConstruct (void);

protected:
// Connections informieren/abfragen
	HRESULT OnRequestAddButtons (int iIndex, const TBBUTTON *pBttn, int iCnt);
	HRESULT OnAddedButtons (int iIndex, const TBBUTTON *pBttn, int iCnt);
	HRESULT OnRequestDeleteItem (UINT uiCtrlID, DWORD dwStyle);
	HRESULT OnDeletedItem (UINT uiCtrlID);

	HRESULT InsertButtonToList (UINT iCmdID, DControlToolBarButton *pIBttn);

// Positionierung
	typedef enum {
		MOVESIZEACTION_LEFT = 0,
		MOVESIZEACTION_TOP = 1,
		MOVESIZEACTION_WIDTH = 2,
		MOVESIZEACTION_HEIGHT = 3,
		MOVESIZEACTION_GETLEFT = 4,
		MOVESIZEACTION_GETTOP = 5,
		MOVESIZEACTION_GETWIDTH = 6,
		MOVESIZEACTION_GETHEIGHT = 7,
	} MOVESIZEACTION;
	long MoveSize (MOVESIZEACTION iAction, long x = 0, long y = 0, long cx = 0, long cy = 0);

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

// ITRiASToolBar specific functions 
	STDMETHOD(GetButtonStyle) (THIS_ int iIndex, UINT *puiStyle);
	STDMETHOD(SetButtonStyle) (THIS_ int iIndex, UINT uiStyle);
	STDMETHOD(AddBitmap) (THIS_ HINSTANCE hInst, UINT uiRsc, int iNumButtons, int *piOffset/*=NULL*/);
	STDMETHOD(AddButtons) (THIS_ const TBBUTTON *pBttns, int iCnt, ITRiASUIOwner *pIOwner);
	STDMETHOD(InsertButton) (THIS_ int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pIOwner);
	STDMETHOD(GetButton) (THIS_ int iIndex, TBBUTTON *pBttn/*=NULL*/, ITRiASUIOwner **pIOwner/*=NULL*/);

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
	STDMETHOD(GetClassID) (CLSID *pClassID);

// IPersistStreamInit functions
	STDMETHOD(IsDirty) (THIS);
	STDMETHOD(Load) (THIS_ LPSTREAM pStrm);
	STDMETHOD(Save) (THIS_ LPSTREAM pStrm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax) (THIS_ ULARGE_INTEGER * pcbSize);
	STDMETHOD(InitNew) (THIS);

///////////////////////////////////////////////////////////////////////////////
// _ITRiASBaseClass methods
    STDMETHOD(get_isA)(THIS_ long *plRTTI);
    STDMETHOD(get_Parent)(THIS_ IDispatch **ppIBase);
    STDMETHOD(put_Parent)(THIS_ IDispatch *pIBase);
    STDMETHOD(get_Application)(THIS_ IDispatch **ppIApp);
    STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Properties) (THIS_ DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, DTRiASProperty **ppIProp);

// IControlToolBar methods
    STDMETHOD(get_Name)(THIS_ BSTR *pbstrName);
    STDMETHOD(put_Name)(THIS_ BSTR bstrName);
    STDMETHOD(get_Width)(THIS_ long *piWidth);
    STDMETHOD(put_Width)(THIS_ long iWidth);
    STDMETHOD(get_Height)(THIS_ long *piHeight);
    STDMETHOD(put_Height)(THIS_ long iHeight);
    STDMETHOD(get_Left)(THIS_ long *piLeft);
    STDMETHOD(put_Left)(THIS_ long iLeft);
    STDMETHOD(get_Top)(THIS_ long *piTop);
    STDMETHOD(put_Top)(THIS_ long iTop);
    STDMETHOD(get_DockState)(THIS_ DOCKSTATE *prgState);
    STDMETHOD(put_DockState)(THIS_ DOCKSTATE rgState);
    STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL *pfVisible);
    STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL fVisible);
    STDMETHOD(get_Style)(THIS_ long FAR* pdwStyle);
    STDMETHOD(put_Style)(THIS_ long dwStyle);
    STDMETHOD(ToolBarButtons)(THIS_ DControlToolBarButtons **ppIBttns);
    STDMETHOD(Reset)(THIS);
    STDMETHOD(InsertButton)(THIS_ int iIndex, DControlToolBarButton *pIBttn,
							DToolBarUIOwner *pIUIOwner, IUnknown *pIInstCtrl);
    STDMETHOD(DeleteButton)(THIS_ int iIndex);
    STDMETHOD(Remove)(THIS);

	STDMETHOD(GetButton)(THIS_ int iIndex, DControlToolBarButton **ppIBttn);
	STDMETHOD(AddButton)(THIS_ int iIndex, DToolBarUIOwner *pIUIOwner, VARIANT vBttnTmpl, DControlToolBarButton **ppIBttn);

    STDMETHOD(get_CtrlID)(THIS_ int *piCtrlID);
    STDMETHOD(put_CtrlID)(THIS_ int iCtrlID);
    STDMETHOD(get_StyleEx)(THIS_ long FAR* pdwStyleEx);
    STDMETHOD(put_StyleEx)(THIS_ long dwStyleEx);

	CTRiASToolBar *GetToolBar() { return m_pToolBar; }

private:
	CTRiASToolBar *m_pToolBar;		// zugehörige Toolbar
	CButtons m_mapBttns;

protected:
	CComPtr<IDispatch> m_Parent;	// für Einbindung in OleAutomation
	CComPtr<IDispatch> m_App;
};
