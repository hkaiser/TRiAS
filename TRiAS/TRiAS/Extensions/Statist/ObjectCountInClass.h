// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 09:17:51 
//
// @doc
// @module ObjectCountInClass.h | Declaration of the <c CObjectCountInClass> class

#if !defined(_OBJECTCOUNTINCLASS_H__FA0C767B_2C08_42D6_8F06_317D96B47E59__INCLUDED_)
#define _OBJECTCOUNTINCLASS_H__FA0C767B_2C08_42D6_8F06_317D96B47E59__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "ObjectCountProviderCallback.h"

/////////////////////////////////////////////////////////////////////////////
// CObjectCountInClass

class ATL_NO_VTABLE CObjectCountInClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CObjectCountInClass, &CLSID_ObjectCountInClass>,
	public ISupportErrorInfo,
	public ITRiASNotificationSink,
	public IDispatchImpl<IValueProvider, &IID_IValueProvider, &LIBID_TRiASStatistics,
		TYPELIB_STATIST_MAJOR_VERSION, TYPELIB_STATIST_MINOR_VERSION>
{
public:
// Construction
	CObjectCountInClass();
	~CObjectCountInClass();

// Initialisation

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTCOUNTINCLASS)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// Interface map
	BEGIN_COM_MAP(CObjectCountInClass)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IValueProvider)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	void SetObjClass (HOBJECTS lIdent, OBJECTTYPE rgTypes = OBJECTTYPE_AllSimple) 
	{ 
		m_lIdent = lIdent; 
		m_rgTypes = rgTypes;
	}
	HRESULT SetXtsnSite (ITriasXtensionSite *pSite, IValueProviderCallback *pICallback);
	HRESULT DisConnectFromServer (void);

protected:
// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// IValueProvider
	STDMETHODIMP get_Name(BSTR *pbstrName);
	STDMETHODIMP get_Description(BSTR *pbstrName);
	STDMETHODIMP get_Flags(VALUEPROVIDERPROP *prgFlags);
	STDMETHODIMP get_Value(VARIANT *pvValue);

// ITRiASNotificationSink specific functions
	STDMETHOD(ServerEvent) (SERVEREVT se);
	STDMETHOD(ProjectEvent) (long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(OBJWNDEVT oe, long hORWnd);

private:
	HOBJECTS m_lIdent;
	OBJECTTYPE m_rgTypes;

	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;

	IValueProviderCallback *m_pICallback;
	BOOL m_fNeedsToDelete;
};

#endif // !defined(_OBJECTCOUNTINCLASS_H__FA0C767B_2C08_42D6_8F06_317D96B47E59__INCLUDED_)
