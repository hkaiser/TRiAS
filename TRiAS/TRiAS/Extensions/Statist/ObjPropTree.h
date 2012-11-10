// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.01.2001 12:29:09 
//
// @doc
// @module ObjPropTree.h | Declaration of the <c CPopupTree> class

#if !defined(_OBJPROPTREE_H__F12FB868_6229_4F78_A51E_DC22274706A7__INCLUDED_)
#define _OBJPROPTREE_H__F12FB868_6229_4F78_A51E_DC22274706A7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <atlctl.h>

#include "resource.h"       // main symbols
#include "PopupTreeEventCP.h"
#include "PopupTreeDlg.h"

///////////////////////////////////////////////////////////////////////////////
// Zwischenräume zwischen den Controls
#define GAP_LABEL	5
#define GAP_EDIT	6
#define GAP_BUTTON	6
#define GAP_SMALLBUTTON	2

///////////////////////////////////////////////////////////////////////////////
// spezielle Creator-Funktion: das Control darf sich nur erzeugen lassen, wenn
// es im Addressraum von TRiAS erzeugt wird
//template <class T1>
//class CComCreatorTRiAS
//{
//public:
//	static HRESULT WINAPI CreateInstance(void* pv, REFIID riid, LPVOID* ppv)
//	{
//		ATLASSERT(*ppv == NULL);
//
//	HRESULT hRes = E_OUTOFMEMORY;
//	T1* p = NULL;
//
//#if !defined(_DEBUG)
//		if (NULL == g_pDexExtensionProc) return E_UNEXPECTED;	// nur bei gestartetem TRiAS laden
//#endif // defined(_DEBUG)
//
//		ATLTRY(p = new T1(pv))
//		if (p != NULL)
//		{
//			p->SetVoid(pv);
//			p->InternalFinalConstructAddRef();
//			hRes = p->FinalConstruct();
//			p->InternalFinalConstructRelease();
//			if (hRes == S_OK)
//				hRes = p->QueryInterface(riid, ppv);
//			if (hRes != S_OK)
//				delete p;
//		}
//		return hRes;
//	}
//};

///////////////////////////////////////////////////////////////////////////////
// CHoveredBitmapButton
class CHoveredBitmapButton :
	public CBitmapButton
{
public:
	CHoveredBitmapButton(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = NULL) :
		CBitmapButton(dwExtendedStyle, hImageList)
	{
	}

	BEGIN_MSG_MAP_EX(CHoveredBitmapButton)
		MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnFocus)

		CHAIN_MSG_MAP(CBitmapButton)
	END_MSG_MAP()

	LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CBitmapButton::OnFocus(uMsg, wParam, lParam, bHandled);
		if (m_fFocus)
			SetImages(2, 1, 2, 3);
		else
			SetImages(4, 1, 0, 3);
		return 1;
	}

	BOOL LoadImages(UINT uiBmpID)
	{
	CImageList imgList;
	CBitmap bmp;

		imgList.Create(15, 21, ILC_COLOR8, 0, 5);
		bmp.LoadMappedBitmap(uiBmpID);
		_ASSERTE(!imgList.IsNull());
		_ASSERTE(!bmp.IsNull());

		imgList.Add(bmp);

		SetImageList(imgList);
		SetImages(4, 1, 0, 3);
		return TRUE;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CPopupTree
#define WM_SHOWPOPUPDIALOG	(WM_USER+5432)

class ATL_NO_VTABLE CPopupTree : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CPopupTree, IPopupTree, &IID_IPopupTree, &LIBID_TRiASStatistics>,
	public CComCompositeControl<CPopupTree>,
	public IPersistStreamInitImpl<CPopupTree>,
	public IOleControlImpl<CPopupTree>,
	public IOleObjectImpl<CPopupTree>,
	public IOleInPlaceActiveObjectImpl<CPopupTree>,
	public IViewObjectExImpl<CPopupTree>,
	public IOleInPlaceObjectWindowlessImpl<CPopupTree>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPopupTree>,
	public IPersistStorageImpl<CPopupTree>,
	public ISpecifyPropertyPagesImpl<CPopupTree>,
	public IQuickActivateImpl<CPopupTree>,
	public IDataObjectImpl<CPopupTree>,
	public IProvideClassInfo2Impl<&CLSID_PopupTree, &DIID__IPopupTreeEvents, 
		&LIBID_TRiASStatistics, TYPELIB_STATIST_MAJOR_VERSION, TYPELIB_STATIST_MINOR_VERSION>,
	public IPropertyNotifySinkCP<CPopupTree>,
	public CComCoClass<CPopupTree, &CLSID_PopupTree>,
	public CProxy_IPopupTreeEvents<CPopupTree>
{
public:
	CPopupTree() :
		m_bttnSelObjProp(BMPBTN_HOVER|BMPBTN_AUTOSIZE), m_rgToShow(POPUPTREEMODE_SHOWOBJPROPS),
		m_pActDlg(NULL)
	{
		m_fIsInitialized = FALSE;
		m_bWindowOnly = TRUE;
		m_bValid = FALSE;
		CalcExtent(m_sizeExtent);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJPROPTREE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	
// Das Control darf sich nur erzeugen lassen, wenn es im Addressraum von TRiAS erzeugt wird
	HRESULT FinalConstruct()
	{
#if !defined(_DEBUG)	// nur bei gestartetem TRiAS laden
		return (NULL == g_pDexExtensionProc) ? E_UNEXPECTED : S_OK;
#else
		return S_OK;
#endif // defined(_DEBUG)
	}
	void FinalRelease()
	{
	}

public:
//	typedef CComCreator2<CComCreatorTRiAS<CComObject<CPopupTree> >, CComCreatorTRiAS<CComAggObject<CPopupTree> > > _CreatorClass;
	BEGIN_COM_MAP(CPopupTree)
		COM_INTERFACE_ENTRY(IPopupTree)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IViewObjectEx)
		COM_INTERFACE_ENTRY(IViewObject2)
		COM_INTERFACE_ENTRY(IViewObject)
		COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceObject)
		COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
		COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
		COM_INTERFACE_ENTRY(IOleControl)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
		COM_INTERFACE_ENTRY(IQuickActivate)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IDataObject)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_PROP_MAP(CPopupTree)
		PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
		PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
		PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)
		PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
		PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
		PROP_ENTRY("TabStop", DISPID_TABSTOP, CLSID_NULL)
		PROP_ENTRY("Valid", DISPID_VALID, CLSID_NULL)
		PROP_ENTRY("ButtonTooltipText", 100, CLSID_NULL)
		PROP_ENTRY("PopupTreeMode", 101, CLSID_NULL)
		PROP_ENTRY("HasSelection", 102, CLSID_NULL)
		PROP_ENTRY("Selection", 103, CLSID_NULL)
		// Example entries
		// PROP_ENTRY("Property Description", dispid, clsid)
		// PROP_PAGE(CLSID_StockColorPage)
	END_PROP_MAP()

	BEGIN_CONNECTION_POINT_MAP(CPopupTree)
		CONNECTION_POINT_ENTRY(DIID__IPopupTreeEvents)
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP_EX(CPopupTree)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDC_SELECT_OBJPROP, BN_CLICKED, OnSelectObjProp)
		CHAIN_MSG_MAP(CComCompositeControl<CPopupTree>)
	END_MSG_MAP()
	// Handler prototypes:
	//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	BEGIN_DDX_MAP(CPopupTree)
	END_DDX_MAP()

	BEGIN_SINK_MAP(CPopupTree)
		//Make sure the Event Handlers have __stdcall calling convention
	END_SINK_MAP()

// Message handlers
	LRESULT OnInitDialog(HWND hFocus, LPARAM lParam);
	LRESULT OnSelectObjProp(WORD wNotifyCode, int iCtrlId, HWND hCtrl);

	LRESULT ShowStatFuncDlg (LPCSTR pcPreSelect);
	LRESULT ShowObjPropDlg (LPCSTR pcPreSelect);

// Event handlers
	STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	{
		if (dispid == DISPID_AMBIENT_BACKCOLOR)
		{
			SetBackgroundColorFromAmbient();
			FireViewChange();
		}
		return IOleControlImpl<CPopupTree>::OnAmbientPropertyChange(dispid);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IPopupTree,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IOleObject
	STDMETHOD(SetExtent)(DWORD dwDrawAspect, SIZEL *psizel)
	{
	HRESULT hr = IOleObjectImpl<CPopupTree>::SetExtent(dwDrawAspect, psizel);

		if (SUCCEEDED(hr))
			AdjustSizes();
		return hr;
	}

	HRESULT FireOnChanged(DISPID dispID)
	{
		if (DISPID_CAPTION == dispID)
			UpdateCaption();
		return CComCompositeControl<CPopupTree>::FireOnChanged(dispID);
	}

// fire events
	void OnItemSelected()
	{
		m_bValid = TRUE;
		Fire_OnItemSelected();
	}
	void OnCanceledSelection()
	{
		Fire_OnCanceledSelection();
	}

// IPopupTree
public:
	STDMETHODIMP get_ButtonTooltipText (BSTR *pbstrTTText);
	STDMETHODIMP put_ButtonTooltipText (BSTR bstrTTText);
	STDMETHODIMP get_PopupTreeMode (POPUPTREEMODE *prgMode);
	STDMETHODIMP put_PopupTreeMode (POPUPTREEMODE rgMode);

	STDMETHODIMP get_HasSelection (VARIANT_BOOL *pfHasSel);
	STDMETHODIMP get_Selection (REFIID riid, IUnknown **ppIUnk);
	STDMETHODIMP SetSelection(BSTR bstrSelection);

public:
	CComBSTR m_bstrCaption;
	POPUPTREEMODE m_rgToShow;

	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	BOOL m_bTabStop;
	BOOL m_bValid;
	BOOL m_fIsInitialized;

	enum { IDD = IDD_POPUPTREECTRL };

	void SetActDlg(CPopupTreeDlgBase *pActDlg)
	{
		_ASSERTE(NULL == m_pActDlg || NULL == pActDlg);
		m_pActDlg = pActDlg;
	}

protected:
	BOOL AdjustSizes();
	BOOL UpdateCaption();

private:
	CStatic m_ftLabel;
	CEdit m_sleSelItem;
	CHoveredBitmapButton m_bttnSelObjProp;
	CHoveredBitmapButton m_bttnCustBttn;
	int m_iMaxEditRight;
	int m_iMinEditRight;

	CPopupTreeDlgBase *m_pActDlg;
	WUnknown m_SelObject;
};

#endif // !defined(_OBJPROPTREE_H__F12FB868_6229_4F78_A51E_DC22274706A7__INCLUDED_)
