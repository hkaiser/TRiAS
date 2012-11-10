// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/04/1998 09:53:13 PM
//
// @doc
// @module TRiASOptionDlg.h | Declaration of the <c CTRiASOptionDlg> class

#if !defined(_TRIASOPTIONDLG_H__A3307F45_5BC3_11D2_9ED5_006008447800__INCLUDED_)
#define _TRIASOPTIONDLG_H__A3307F45_5BC3_11D2_9ED5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "StdCtrlDlg.h"

#include "CPTRiASOptionDlgCallback.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASOptionDlg
class ATL_NO_VTABLE IXTRiASOptionDlg :
	public ITRiASOptionDlg
{
public:
	STDMETHOD(Unadvise)(/*[in]*/ DWORD Cookie);
	STDMETHOD(Advise)(/*[in]*/ IUnknown *pConn, /*[out, retval]*/ DWORD *Cookie);
};

class ATL_NO_VTABLE CTRiASOptionDlg : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public IConnectionPointContainerImpl<CTRiASOptionDlg>,
	public CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>,
	public CComCoClass<CTRiASOptionDlg, &CLSID_TRiASOptionDlg>,
	public IDispatchImpl<IXTRiASOptionDlg, &IID_ITRiASOptionDlg, &LIBID_TRIASUI,
		TYPELIB_TRIASUI_VERSION_MAJOR, TYPELIB_TRIASUI_VERSION_MINOR>
{
public:
	CTRiASOptionDlg()
	{
		m_pDlg = NULL;
		m_pUnkPpg = NULL;
		m_fIsInitialized = false;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOPTIONDLG)

	BEGIN_COM_MAP(CTRiASOptionDlg)
		COM_INTERFACE_ENTRY(ITRiASOptionDlg)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASOptionDlg)
		CONNECTION_POINT_ENTRY(IID_ITRiASOptionDlgCallback)
	END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	HRESULT FinalConstruct();
	void FinalRelease()
	{
		if (NULL != m_pDlg) {
			m_pDlg -> m_pOuterUnknown = NULL;		// endless recursion verhindern
			m_pDlg -> ShutDown();
		}
		if (NULL != m_pUnkPpg) m_pUnkPpg->Release();
	}

///////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// ITRiASOptionDlg
public:
	STDMETHOD(RefreshAllItems)();
	STDMETHOD(RefreshItem)(/*[in]*/ ULONG Item);
	STDMETHOD(InsertFolderItem)(/*[in]*/ BSTR Name, /*[in]*/ ULONG ulParent, /*[out, retval]*/ ULONG *puiItem);
	STDMETHOD(GetItemObject)(/*[in]*/ ULONG ulItem, /*[out, retval]*/ IUnknown **ppIObj);
	STDMETHOD(GetItemName)(/*[in]*/ ULONG Item, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetNextItem)(/*[in]*/ ULONG Item, /*[in]*/ NEXTITEMMODE Mode, /*[out, retval]*/ ULONG *NextItem);
	STDMETHOD(GetChildItem)(/*[in]*/ ULONG ulParent, /*[out, retval]*/ ULONG *pulChild);
	STDMETHOD(SelectItem)(/*[in]*/ ULONG uiID, /*[in]*/ VARIANT_BOOL fSelect);
	STDMETHOD(get_HasApply)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HasApply)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_MultiSelect)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_MultiSelect)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_HasButtons)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HasButtons)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_HasLines)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HasLines)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_WordWrap)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_WordWrap)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Caption)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Caption)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ActItem)(/*[out]*/ ULONG *pVal);
	STDMETHOD(SetFirstVisible)(/*[in]*/ ULONG Item);
	STDMETHOD(GetParentItem)(/*[in]*/ ULONG ulChild, /*[out, retval]*/ ULONG *pulParent);

	STDMETHOD(InsertItemObject)(/*[in]*/ IUnknown *pIObj, /*[in]*/ BSTR Name, /*[in, optional, defaultvalue]*/ ULONG ulParent, /*[in, optional, defaultvalue]*/ IDispatch *pPict, /*[out, retval]*/ ULONG *puiID);
	STDMETHOD(InsertItemName)(/*[in]*/ BSTR Type, /*[in]*/ BSTR Name, /*[in, optional, defaultvalue]*/ ULONG ulParent, /*[out, retval]*/ ULONG *puiID);
	STDMETHOD(Show)(/*[in]*/ INT_PTR hWndParent, /*[in]*/ SHOWCOMMAND rgCmd, /*[out, retval]*/ VARIANT_BOOL *pvResult);

	STDMETHOD(get_ContextHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(put_ContextHandle)(/*[in]*/ INT_PTR newVal);

// support for IID_ITRiASOptionDlgCallback
	HRESULT Fire_OnInitDialog()	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnInitDialog (this); }
	HRESULT Fire_OnGetDispInfoChildren(ULONG ulItem, int *piChildren)	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnGetDispInfoChildren(this, ulItem, piChildren); }
	HRESULT Fire_OnGetDispInfoImage(ULONG ulItem, IDispatch **ppIPict)
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnGetDispInfoImage(this, ulItem, ppIPict); }
	HRESULT Fire_OnGetDispInfoExpandedImage(ULONG ulItem, IDispatch **ppIPict)
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnGetDispInfoExpandedImage(this, ulItem, ppIPict); }
	HRESULT Fire_OnGetDispInfoText(ULONG ulItem, BSTR *pbstrText)	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnGetDispInfoText (this, ulItem, pbstrText); }

	HRESULT Fire_OnQueryContextMenu(ULONG ulItem, INT_PTR hMenu, UINT uiFirst, UINT uiLast, UINT *puiLastID)	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnQueryContextMenu (this, ulItem, hMenu, uiFirst, uiLast, puiLastID); }
	HRESULT Fire_OnGetCommandString(ULONG ulItem, UINT uiCmd, DWORD dwFlags, BSTR *pbstrDesc)	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnGetCommandString (this, ulItem, uiCmd, dwFlags, pbstrDesc); }
	HRESULT Fire_OnInvokeCommand(ULONG ulItem, INT_PTR hWnd, UINT uiCmd)	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnInvokeCommand (this, ulItem, hWnd, uiCmd); }

	HRESULT Fire_OnOk()	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnOk (this); }
	HRESULT Fire_OnCancel()	
		{ return CProxyITRiASOptionDlgCallback<CTRiASOptionDlg>::Fire_OnCancel (this); }

private:
	CStdCtrlDlg *m_pDlg;
	LPUNKNOWN m_pUnkPpg;
	bool m_fIsInitialized;
};

///////////////////////////////////////////////////////////////////////////////
// Version des PersistStream-Formates
const long TRIASOPTIONDLG_SIGNATURE = 0x4454504F;	// "OPTD"
const long TRIASOPTIONDLG_VERSION = 0x0100L;
const long LASTKNOWN_TRIASOPTIONDLG_VERSION = TRIASOPTIONDLG_VERSION;

#endif // !defined(_TRIASOPTIONDLG_H__A3307F45_5BC3_11D2_9ED5_006008447800__INCLUDED_)
