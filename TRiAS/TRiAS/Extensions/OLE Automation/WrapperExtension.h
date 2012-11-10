// WrapperExtension.h: Definition of the CWrapperExtension class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_)
#define AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "oleautor.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// DTRiASExtension wrapper class

#if !defined(_countof)
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif // !_countof

// Namen der DispFunktionen
const LPCOLESTR s_pcoleDTRiASExtensionNames[] = 
{
	L"LoadExtension", 
	L"UnloadingExtension", 
	L"UnloadExtension",
};

#define DISPID_LOADEXTENSION		0
#define DISPID_UNLOADINGEXTENSION	1
#define DISPID_UNLOADEXTENSION		2

class DTRiASExtensionWrapper : 
	public COleDispatchDriver
{
public:
	DTRiASExtensionWrapper(void);
	HRESULT FInit (IDispatch *pIDisp);

// Attributes
private:
// DispatchID's 
	LCID m_lcid;
	DISPID m_dwDispId[_countof(s_pcoleDTRiASExtensionNames)];

// Operations
public:
	HRESULT LoadExtension(LPDISPATCH pIApp, const VARIANT& vDocDisp);
	HRESULT UnloadingExtension(VARIANT_BOOL fMayDeny, VARIANT_BOOL *pfDoNotUnload);
	HRESULT UnloadExtension();
};

/////////////////////////////////////////////////////////////////////////////
// CWrapperExtension

EXTERN_C const GUID IID_IInitDTRiASExtension;

class CWrapperExtension : 
	public IInitDTRiASExtension,
	public CTriasExtension,
	public CComCoClass<CWrapperExtension, &CLSID_WrapperExtension>
{
private:
	DTRiASExtension *m_pIExt;
	DTRiASExtensionWrapper *m_pExtWrapper;
	HPROJECT m_hPr;
	WUnknown m_Ext;		// Haupterweiterung festhalten

static LONG m_lCntExts;

public:
	CWrapperExtension(void);
	~CWrapperExtension(void);

	BEGIN_COM_MAP(CWrapperExtension)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(IInitDTRiASExtension)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_WRAPPEREXTENSION_RGS)

public:
// CTriasExtension
	STDMETHOD_(HDEX, LoadExtension) (TRIASLOADEX *pTL, HWND hWnd);
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

// IInitDTRiASExtension
	STDMETHOD(InitDTRiASExtension) (IUnknown *pIUnk, long hPr);
	STDMETHOD(InitDTRiASExtensionRegKey) (BSTR bstrRegKey, long hPr);
};

#endif // !defined(AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_)
