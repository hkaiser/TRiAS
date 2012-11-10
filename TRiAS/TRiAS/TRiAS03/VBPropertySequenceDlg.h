// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 12:26:35 
//
// @doc
// @module VBGeoComponentDlg.h | Declaration of the <c CVBGeoComponentDlg> class

#if !defined(_VBPROPERTYSEQUENCEDLG_H__F9722FA1_1104_489A_809D_9FFA7103273E__INCLUDED_)
#define _VBPROPERTYSEQUENCEDLG_H__F9722FA1_1104_489A_809D_9FFA7103273E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

#include <Atl/Ciid.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(GeoComponent);

/////////////////////////////////////////////////////////////////////////////
// B501ED48-4BA6-4917-BE14-75E01A620F95
EXTERN_C const GUID __declspec(selectany) CLSID_VBGeoComponentDlg = 
	{ 0xB501ED48, 0x4BA6, 0x4917, 0xBE, 0x14, 0x75, 0xE0, 0x1A, 0x62, 0x0F, 0x95 };

/////////////////////////////////////////////////////////////////////////////
// CVBGeoComponentDlg dialog

class CVBGeoComponentDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVBGeoComponentDlg, &CLSID_VBGeoComponentDlg>,
	public WTL::CAxPropertyPageImpl<CVBGeoComponentDlg>,
	IDispatchImpl<IGeoComponentUICallback, &IID_IGeoComponentUICallback,
		&LIBID_TRiAS, TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>
{
// Construction
public:
	CVBGeoComponentDlg();
	~CVBGeoComponentDlg();

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CVBGeoComponentDlg)
		COM_INTERFACE_ENTRY(IGeoComponentUICallback)
		COM_INTERFACE_ENTRY2(IDispatch, IGeoComponentUICallback)
	END_COM_MAP()

// Dialog Data
	enum { IDD = IDD_VBPROPERTYSEQUENCE_OPTIONS };

	typedef WTL::CAxPropertyPageImpl<CVBGeoComponentDlg> base_t;
	BEGIN_MSG_MAP_EX(CVBGeoComponentDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		CHAIN_MSG_MAP(base_t)
	END_MSG_MAP()

// Overrides
public:
	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/);
	void OnDestroy();
	BOOL OnSetActive();
	BOOL OnKillActive();
	int OnWizardBack();
	int OnWizardNext();
	BOOL OnWizardFinish();

	BOOL OnTranslateAccelerator(LPMSG lpMsg);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	void SetGeoComponent (IGeoComponent *pIGeoComponent) 
	{ m_EmbeddedObj = pIGeoComponent; }
	void SetInitData(REFGUID rGuid, long lIndex)
	{ m_Guid = rGuid; m_lIndex = lIndex; }

	void ResetCallbackLoop();

	static CVBGeoComponentDlg *CreateInstance (LPCSTR pcCaption, REFGUID rGuid, long lIndex);

// IGeoComponentUICallback
public:
	STDMETHODIMP OnStatusChange();
	STDMETHODIMP TranslateAccelerator(long Wnd, long Msg, long wParam, 
		long lParam, long Time, long PosX, long PosY, VARIANT_BOOL *pfResult);

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	HRESULT ShowControl(WTL::CRect &rrcPos);
	HRESULT HideControl();
	void DestroyControl();

private:
	DWORD m_dwFlags;
	CIID m_Guid;					// Guid des Wrappercontrols
	HWND m_hControlWnd;				// Wrapperfenster des Controls
	WGeoComponent m_EmbeddedObj;	// externe Geokomponente
	long m_lIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_VBPROPERTYSEQUENCEDLG_H__F9722FA1_1104_489A_809D_9FFA7103273E__INCLUDED_)
