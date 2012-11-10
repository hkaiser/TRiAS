#ifndef __MASKEDIT_H_
#define __MASKEDIT_H_

#include "resource.h"       // main symbols
#include "CPMaskEdit.h"

#define	MAX_MASK_LEN	256

/////////////////////////////////////////////////////////////////////////////
// CMaskEdit
class ATL_NO_VTABLE CMaskEdit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMaskEdit, &CLSID_MaskEdit>,
	public CComControl<CMaskEdit>,
	public CStockPropImpl<CMaskEdit, IMaskEdit, &IID_IMaskEdit, &LIBID_UICtrlLib>,
	public IProvideClassInfo2Impl<&CLSID_MaskEdit, &DIID__DMaskEditEvents, &LIBID_UICtrlLib>,
	public IPersistStreamInitImpl<CMaskEdit>,
	public IPersistStorageImpl<CMaskEdit>,
	public IQuickActivateImpl<CMaskEdit>,
	public IOleControlImpl<CMaskEdit>,
	public IOleObjectImpl<CMaskEdit>,
	public IOleInPlaceActiveObjectImpl<CMaskEdit>,
	public IViewObjectExImpl<CMaskEdit>,
	public IOleInPlaceObjectWindowlessImpl<CMaskEdit>,
	public IDataObjectImpl<CMaskEdit>,
	public ISupportErrorInfo,
	public CProxy_DMaskEditEvents<CMaskEdit>,
	public IConnectionPointContainerImpl<CMaskEdit>,
	public IPropertyNotifySinkCP<CMaskEdit>,
	public ISpecifyPropertyPagesImpl<CMaskEdit>,
	public IRunnableObjectImpl<CMaskEdit>
{
	TCHAR		m_chCodeTable[256];
	TCHAR		m_strMask[MAX_MASK_LEN];
	UINT		m_nMaskLen;					// Länge *ohne* '\0'
	TCHAR		m_strDisplay[MAX_MASK_LEN];
	TCHAR		m_strUndo[MAX_MASK_LEN];
	TCHAR		m_chEscape;
	TCHAR		m_chPrompt;
	HRESULT		ParseMaskString(LPCTSTR lpszMask );
	HRESULT		InitCodetable();
	bool		IsCharValid(UINT nPos, TCHAR& ch );
	bool		m_bReadOnly;
	bool		m_bInsertMode;

//	UINT	GetRepaintPos( UINT iIndex);
	UINT	GetPrevDataPos( UINT nOldPos );
	UINT	GetNextDataPos( UINT nOldPos );
	UINT	SetCursorPos( UINT nOldPos, int nDirection, int startSel = -1 );

	void	PushChar( UINT nStartPos, TCHAR ch, bool bRefreshDisplay = TRUE );
	void	PullChar( UINT nFromPos, UINT nToPos, bool bSetUndoBuffer = TRUE );
	void	RefreshDisplay();
	void	GetSel( UINT& nStartPos, UINT& nEndPos );
	void	SetSel( int nStartPos, int nEndPos );
	void	SetModify( bool bModify);
	void	BuildDisplayString();

public:
	CContainedWindow m_ctlEdit;

	CMaskEdit()
		: m_ctlEdit(_T("Edit"), this, 1)
		, m_nMaskLen(0)
		, m_bReadOnly(false)
		, m_bInsertMode(false)
		, m_chPrompt(_T('0'))
		, m_chEscape(_T('\\'))
	{
		SIZEL	pxSize;
		pxSize.cx = 100;
		pxSize.cy = 50;
		AtlPixelToHiMetric( &pxSize, &m_sizeExtent );
		m_bWindowOnly = TRUE;
		InitCodetable();
		memset(m_strMask,0,sizeof(m_strMask));
	}
	virtual HRESULT FinalConstruct();
	virtual HRESULT FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MASKEDIT)
	DECLARE_NOT_AGGREGATABLE(CMaskEdit)

	BEGIN_COM_MAP(CMaskEdit)
		COM_INTERFACE_ENTRY(IMaskEdit)
		COM_INTERFACE_ENTRY(IDispatch)
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
		COM_INTERFACE_ENTRY_IMPL(IRunnableObject)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_PROPERTY_MAP(CMaskEdit)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
		PROP_ENTRY("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL)
		PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
		// Example entries
		// PROP_ENTRY("Property Description", dispid, clsid)
		PROP_ENTRY(_T("MaskEdit"),1,CLSID_PpgMaskEdit)
		PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
		PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
		PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
//		PROP_PAGE(CLSID_StockColorPage)
//		PROP_PAGE(CLSID_StockFontPage)
	END_PROPERTY_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMaskEdit)
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
		CONNECTION_POINT_ENTRY(DIID__DMaskEditEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP(CMaskEdit)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
	ALT_MSG_MAP(1)
		// Replace this with message map entries for subclassed Edit
		MESSAGE_HANDLER(WM_CHAR, OnChar )
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown )
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkGnd)
	END_MSG_MAP()

	LRESULT OnEraseBkGnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		HDC	hdc = (HDC) wParam;
		RECT	rc;
		GetClientRect(&rc);
		HBRUSH	hBr = ::CreateSolidBrush(m_clrBackColor);
		::FillRect(hdc,&rc,hBr);
		::DeleteObject(hBr);
		return 0;
	}
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		m_ctlEdit.SetFocus();
		return 0;
	}
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return 0;
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		m_ctlEdit.SetWindowPos(NULL,0,0,LOWORD(lParam),HIWORD(lParam),SWP_NOMOVE | SWP_NOZORDER);
		return 0;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		DWORD	dwStyle = WS_CHILD | WS_VISIBLE;// | WS_BORDER;
		DWORD	dwStyleEx = 0; //WS_EX_CLIENTEDGE; //WS_EX_TRANSPARENT;
		m_ctlEdit.Create(m_hWnd, rc, NULL, dwStyle, dwStyleEx );
		return 0;
	}
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus) {
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}
//IOleInPlaceActiveObjectImpl::TranslateAccelerator
	STDMETHOD (TranslateAccelerator)( LPMSG lpmsg ) {
//		return IOleInPlaceActiveObjectImpl<CMaskEdit>::TranslateAccelerator( lpmsg );
		return E_NOTIMPL;
	}
//IOleObjectImpl::GetMiscStatus
	STDMETHOD (GetMiscStatus)(  DWORD dwAspect, DWORD* pdwStatus ) {
		return IOleObjectImpl<CMaskEdit>::GetMiscStatus( dwAspect, pdwStatus );
	}
//IOleObjectImpl::DoVerbHide
	STDMETHOD (DoVerbHide)(LPCRECT /* prcPosRect */, HWND /* hwndParent */) {
		UIDeactivate();
		if (m_hWnd)
			//EnableWindow(FALSE);
			ShowWindow(SW_HIDE);
		return S_OK;
	}
	STDMETHOD(OnChanged)(DISPID id) {
		return S_OK;
	}
	STDMETHOD(SetClientSite)( IOleClientSite* pClientSite ) {
		return IOleObjectImpl<CMaskEdit>::SetClientSite( pClientSite );
	}
// IMaskEdit
public:
	STDMETHOD(get_Text)(short DelimterCharacter, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Text)(short DelimterCharacter, /*[in]*/ BSTR newVal);
	STDMETHOD(get_EscapeChar)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_PromptChar)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_PromptChar)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Mask)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Mask)(/*[in]*/ BSTR newVal);
	HRESULT OnDraw(ATL_DRAWINFO& di);

	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrBackColor;
	OLE_COLOR m_clrBorderColor;
	BOOL m_bValid;
	BOOL m_bTabStop;
	BOOL m_bBorderVisible;
	long m_nBorderStyle;
	bool isMaskChar( int n );
};

inline bool isMaskLiteral( TCHAR c ) {
	return (UINT) c > _T(' ');
}

inline bool CMaskEdit::isMaskChar( int n ) {
	long c = (long) m_strMask[n];
	c = ( 256 + c ) % 256;
	return c < _T(' ');
}

inline void	CMaskEdit::GetSel( UINT& nStartPos, UINT& nEndPos ) {
	DWORD	s, e;
	::SendMessage( m_ctlEdit.m_hWnd, EM_GETSEL, (WPARAM) &s, (LPARAM) &e );
	nStartPos = s;
	nEndPos = e;
}

inline void CMaskEdit::SetSel( int nStartPos, int nEndPos ) {
	::SendMessage( m_ctlEdit.m_hWnd, EM_SETSEL, (WPARAM) nStartPos, (LPARAM) nEndPos );
}

inline void CMaskEdit::SetModify( bool bModify) {
	::SendMessage( m_ctlEdit.m_hWnd, EM_SETMODIFY, (WPARAM) (UINT) bModify, (LPARAM) 0 );
}

inline void CMaskEdit::RefreshDisplay() {
	if( ::IsWindow( m_ctlEdit.m_hWnd ) )
		m_ctlEdit.SetWindowText(m_strDisplay);
//	m_ctlEdit.Invalidate();
//	FireTextChanged();
//	if(!m_bReadOnly)
//		SetModify(TRUE);
}

#endif //__MASKEDIT_H_
