// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 14.03.2002 22:36:47 
//
// @doc
// @module SabisTabChildWindow.h | Declaration of the <c CSabisTabChildWindow> class

#if !defined(_SABISTABCHILDWINDOW_H__F9237CF5_8F5B_4B69_AD3D_BB8EA785D0AD__INCLUDED_)
#define _SABISTABCHILDWINDOW_H__F9237CF5_8F5B_4B69_AD3D_BB8EA785D0AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "TRiASTabChild.h"

#import "tlb/toolbar.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

/////////////////////////////////////////////////////////////////////////////
// CSabisTabChildWindow

class ATL_NO_VTABLE CSabisTabChildWindow : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CSabisTabChildWindow, &CLSID_SabisTabChildWindow>,
	public IDispatchImpl<CommonChildWindow2, &IID_CommonChildWindow2, &LIBID_TRSABiS>,
	public ISupportErrorInfo
{
public:
// Construction
	CSabisTabChildWindow();
	~CSabisTabChildWindow();

// Initialisation
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations
//	DECLARE_REGISTRY_RESOURCEID(IDR_SABISTABCHILDWINDOW)
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(CSabisTabChildWindow)
		COM_INTERFACE_ENTRY(CommonChildWindow2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// Operations
	HRESULT CreateClientWindow(bool fShow = false);
	bool ReShow();
	HRESULT DeleteWindow(bool fTabOnly = false);
	HRESULT DestroyWindow();
	HRESULT RegisterTabWindow(BSTR bstrInit, bool fUse2ndOne = false);
	void InitiateShutDown();

	bool ItsVisibleForMe() { return m_fIThinkItsVisible; }

	static HRESULT RegisterTabWindows();

// Implementation
protected:
// Attributes
	CTRiASTabChild *GetWindow(HWND hWndParent);
	HRESULT GetWindowRect(CRect& rect);
	static HRESULT RetrieveTabManager(bool fUse2ndOne, IManageTabWindows **ppITabs);

// Interfaces
public:
// CommonChildWindow2
	STDMETHODIMP put_BackColor (long cBkColor);
	STDMETHODIMP get_BackColor (long *cBkColor);
	STDMETHODIMP put_Caption (BSTR bstrCaption);
	STDMETHODIMP get_Caption (BSTR *pbstrCaption);
	STDMETHODIMP put_Enabled (VARIANT_BOOL fEnabled);
	STDMETHODIMP get_Enabled (VARIANT_BOOL *pfEnabled);
	STDMETHODIMP get_Height (long *plHeight);
	STDMETHODIMP put_Height (long lHeight);
	STDMETHODIMP get_hWnd (long *phWnd);
	STDMETHODIMP put_Icon (VARIANT vPict);
	STDMETHODIMP get_Left (long *plLeft);
	STDMETHODIMP put_Left (long lLeft);
	STDMETHODIMP Move (long X, long Y);
	STDMETHODIMP OnKeyDown (short *KeyCode, short *Shift);
	STDMETHODIMP put_Tag (BSTR bstrTag);
	STDMETHODIMP get_Tag (BSTR *pbstrTag);
	STDMETHODIMP get_Top (long *plTop);
	STDMETHODIMP put_Top (long lTop);
	STDMETHODIMP put_Visible (VARIANT_BOOL fVisible);
	STDMETHODIMP get_Visible (VARIANT_BOOL *pfVisible);
	STDMETHODIMP get_Width (long *plWidth);
	STDMETHODIMP put_Width (long lWIdth);
	STDMETHODIMP get_WindowState (long *plState);
	STDMETHODIMP put_WindowState (long lState);

// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

private:
	CComBSTR m_bstrTag;		// Tag zur Kennzeichnung des Fensters
	CComBSTR m_bstrInit;	// Name der Tablasche
	long m_cBkColor;		// evtl. Hintergrundfarbe
	CTRiASTabChild *m_pWnd;
	bool m_fIThinkItsVisible;
	bool m_fHasBkColor;
	bool m_fWasShownOnce;
	bool m_fUse2ndOne;
};

#endif // !defined(_SABISTABCHILDWINDOW_H__F9237CF5_8F5B_4B69_AD3D_BB8EA785D0AD__INCLUDED_)
