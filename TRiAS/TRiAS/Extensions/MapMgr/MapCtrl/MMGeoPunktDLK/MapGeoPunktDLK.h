// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 09:36:52 
//
// @doc
// @module MapGeoPunktDLK.h | Declaration of the <c CMapGeoPunktDLK> class

#if !defined(_MAPGEOPUNKTDLK_H__CBD6A95B_C5E5_42DE_A1CE_73B685BDF653__INCLUDED_)
#define _MAPGEOPUNKTDLK_H__CBD6A95B_C5E5_42DE_A1CE_73B685BDF653__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapGeoPunktDLK
class ATL_NO_VTABLE CMapGeoPunktDLK :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMapGeoPunktDLK, &CLSID_MapGeoPunktDLK>,
	public IConnectionPointContainerImpl<CMapGeoPunktDLK>,
	public IDispatchImpl<IMapGeoPunktDLK, &IID_IMapGeoPunktDLK, &LIBID_MMGEOPUNKTDLKLib>,
	public ITopoMapImpl
{
public:
	CMapGeoPunktDLK() {}
	~CMapGeoPunktDLK() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPGEOPUNKTDLK_RGS)

	BEGIN_COM_MAP(CMapGeoPunktDLK)
		COM_INTERFACE_ENTRY(IMapGeoPunktDLK)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMapGeoPunktDLK)
	END_CONNECTION_POINT_MAP()

public:
// IMapGeoPunktDLK
// IMapImport
	STDMETHOD(GetAltFileFilter)(/*[out]*/ BSTR* pFilter);
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid);

// KK001120
	STDMETHOD(GetAltFileTyp)(/*[out]*/ BSTR* pTyp);
	STDMETHOD(HaveMultiMap)(/*[out]*/ long* pYesNo);

// #HK020318
	STDMETHOD(BitmapIndex)(/*[out, retval]*/ long *plIndex);
	STDMETHOD(CorrectName)(/*[in]*/ BSTR bstrDestDir, /*[in]*/ BSTR bstrName, /*[out, retval]*/ BSTR *pbstrToWrite);
//	STDMETHOD(CorrectDirectory)(/*[in]*/ BSTR bstrDestDir, /*[out, retval]*/ BSTR *pbstrToWrite);
	STDMETHOD(GetDescription)(/*[out, retval]*/ BSTR *prgFlags);

// #HK011018
	STDMETHOD(NeedsCoordSystem)(/*[out, retval]*/ VARIANT_BOOL *pfNeedsCoordSys);
};

#endif // !defined(_MAPGEOPUNKTDLK_H__CBD6A95B_C5E5_42DE_A1CE_73B685BDF653__INCLUDED_)
