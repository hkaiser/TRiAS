// TRiASCSUI.h : Declaration of the CTRiASCSUI

#ifndef __TRIASCSUI_H_
#define __TRIASCSUI_H_

#include "commctrl.h"
#include "atl/AtlCtrl_Tree.h"

class AtlImageList {
	HIMAGELIST	m_hImgList;
	SIZE		m_size;
	void Destroy() {
		if( m_hImgList )
			ImageList_Destroy(m_hImgList);
		m_hImgList = NULL;
	}
public:
	AtlImageList( int cx = 0, int cy = 0 ) : m_hImgList(NULL) { m_size.cx = cx; m_size.cy = cy; }
	virtual ~AtlImageList() { Destroy(); }
	bool Load( HINSTANCE hResrc, LPCTSTR lpszResrc, int nImages ) {
		HBITMAP	hbm = ::LoadBitmap( hResrc, lpszResrc );
		_ASSERTE( hbm );
		if( !hbm )
			return false;
		Destroy();
		_ASSERTE( 0 != m_size.cx && 0 != m_size.cy );
		m_hImgList = ImageList_Create( m_size.cx, m_size.cy, FALSE, nImages, 0 );
		ImageList_Add( m_hImgList, hbm, (HBITMAP) NULL );
		::DeleteObject( hbm );
		return true;
	}
	operator HIMAGELIST() const {
		return m_hImgList;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSUI
class ATL_NO_VTABLE CTRiASCSUI : 
	public CComObjectRootEx<CComObjectThreadModel>
	, public CComCoClass<CTRiASCSUI, &CLSID_TRiASCSUI>
	, public CComControl<CTRiASCSUI>
	, public CStockPropImpl<CTRiASCSUI, ITRiASCSUI, &IID_ITRiASCSUI, &LIBID_TRIASCS>
	, public IProvideClassInfo2Impl<&CLSID_TRiASCSUI, NULL, &LIBID_TRIASCS>
	, public IPersistStreamInitImpl<CTRiASCSUI>
	, public IPersistStorageImpl<CTRiASCSUI>
	, public IQuickActivateImpl<CTRiASCSUI>
	, public IOleControlImpl<CTRiASCSUI>
	, public IOleClientSite
	, public IOleObjectImpl<CTRiASCSUI>
	, public IOleInPlaceActiveObjectImpl<CTRiASCSUI>
	, public IViewObjectExImpl<CTRiASCSUI>
	, public IOleInPlaceObjectWindowlessImpl<CTRiASCSUI>
	, public IDataObjectImpl<CTRiASCSUI>
	, public IConnectionPointContainerImpl<CTRiASCSUI>
	, public IPropertyNotifySinkCP<CTRiASCSUI>
	, public ISpecifyPropertyPagesImpl<CTRiASCSUI>
{
//	WUnknown	m_cs;				// aggregiertes Objekt (TRiASCS)
	WTRiASCSSet	m_csSet;
	AtlImageList	m_imgList;
	HRESULT	ClearTree( CAtlTreeCursor& item );
	HRESULT	FillTree( WTRiASCSSet& csSet, CAtlTreeCursor& root );
	HRESULT SetImage( CAtlTreeCursor& item );
public:
	CComPtr<IFontDisp>	m_pFont;
	CAtlTreeCtrl			m_tree;
	CTRiASCSUI()
		: m_tree(_T("SysTreeView32"), this, 1)
		, m_imgList( 16, 16 )
	{
		m_bWindowOnly = TRUE; 
	}
	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSUI)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CTRiASCSUI)
		COM_INTERFACE_ENTRY(ITRiASCSUI)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
		COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
		COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
		COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
		COM_INTERFACE_ENTRY_IMPL(IOleControl)
		COM_INTERFACE_ENTRY_IMPL(IOleObject)
		COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
		COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
		COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
		COM_INTERFACE_ENTRY_IMPL(IDataObject)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
//		COM_INTERFACE_ENTRY_AGGREGATE(IID_ITRiASCS, m_cs.p)
	END_COM_MAP()

	BEGIN_PROPERTY_MAP(CTRiASCSUI)
		// Example entries
		// PROP_ENTRY("Property Description", dispid, clsid)
//		PROP_PAGE(CLSID_TRiASCSPpg)
//		PROP_PAGE(CLSID_TRiASGCSPpg)
//		PROP_PAGE(CLSID_TRiASPCSPpg)
	END_PROPERTY_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASCSUI)
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP(CTRiASCSUI)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
	ALT_MSG_MAP(1)
		// Replace this with message map entries for subclassed SysTreeView32
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnDblClick)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
//		MESSAGE_HANDLER(WM_NOTIFY, OnNotify)
	END_MSG_MAP()

	LRESULT OnNotify( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDblClick( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return 0;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		m_tree.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE );
		LONG	wndStyle = ::GetWindowLong( m_tree.m_hWnd, GWL_STYLE );
		wndStyle |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;
		::SetWindowLong( m_tree.m_hWnd, GWL_STYLE, wndStyle );
		m_imgList.Load( _Module.GetResourceInstance(), MAKEINTRESOURCE( IDB_BITMAP_CS ), 8 );
		m_tree.SetImageList( m_imgList );
		CAtlTreeCursor	hkcu = m_tree.InsertItem( _T("HKCU"), NULL, TVI_LAST, 0 );
		FillTree( m_csSet, hkcu );
		return 0;
	}
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip) {
		IOleInPlaceObjectWindowlessImpl<CTRiASCSUI>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_tree.m_hWnd, NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus) {
		CSTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}
// IOleClientSite
	STDMETHOD(SaveObject)() {
		return E_NOTIMPL;
	}
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker ** ppmk ) { 
		return E_NOTIMPL;
	}
	STDMETHOD(GetContainer)( LPOLECONTAINER FAR* ppContainer ) { 
		return E_NOTIMPL;
	}
	STDMETHOD(ShowObject)() { 
		return E_NOTIMPL;
	}
	STDMETHOD(OnShowWindow)( BOOL fShow ) { 
		return E_NOTIMPL;
	}
	STDMETHOD(RequestNewObjectLayout)() { 
		return E_NOTIMPL;
	}
// ITRiASCSUI
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);

};

#endif //__TRIASCSUI_H_
