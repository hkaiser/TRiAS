// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.05.2001 10:18:54 
//
// @doc
// @module TRiASNativeObjects.h | Declaration of the <c CTRiASNativeObjects> class

#if !defined(_TRIASNATIVEOBJECTS_H__C2B8E4B3_737C_4983_B88E_862485F765F4__INCLUDED_)
#define _TRIASNATIVEOBJECTS_H__C2B8E4B3_737C_4983_B88E_862485F765F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/CieThis.h>
#include <NativeIdent.h>

#include "resource.h"       // main symbols
#include "Util.h"

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für unsortierte Objektmenge
template<typename T = INT_PTR, typename Container = vector<T> >
class CObjectsCollectionOnSTLImpl :
	public ICollectionOnSTLImpl<
		IDispatchImpl<ITRiASEnumNativeObjects, &IID_ITRiASEnumNativeObjects, &LIBID_TRiASNativeDB, 
			TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>, 
		Container, T, _Copy<T>,
		CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _CopyVariantFromPtr<T>, Container > >
{
public:
	typedef T _BaseType;
	typedef Container _ContainerType;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeObjects
template<typename T, typename Base, const CLSID *pclsid>
class ATL_NO_VTABLE CTRiASNativeObjects : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<T, pclsid>,
	public ISupportErrorInfo,
	public Base
{
public:
	typedef Base _CollectionBase;

	CTRiASNativeObjects()
	{
	}

	DECLARE_NOT_AGGREGATABLE(CTRiASNativeObjects)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void FinalRelease()
	{
	}

	BEGIN_COM_MAP(CTRiASNativeObjects)
		COM_INTERFACE_ENTRY(ITRiASEnumNativeObjects)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS_EX(*pclsid)
	END_COM_MAP()

// alle Objekte einer Objektklasse in der Reihenfolge ihrer Objektnummern sammeln
	HRESULT FInitFromClass (HPROJECT hPr, INT_PTR lIdent, DWORD dwTypes, 
		ITRiASExpression *pIExpr)
	{
		_ASSERTE(NULL != hPr);
		_ASSERTE(NULL != lIdent);

	trias_nativeident::CNativeIdent Ident(hPr, lIdent, dwTypes);

		return Ident.GetObjects(dwTypes, m_coll, NULL, pIExpr);
	}

// alle Objekte einer Objektklasse in der Reihenfolge ihrer Guids sammeln
	HRESULT FInitFromGuid (HPROJECT hPr, INT_PTR lIdent, DWORD dwTypes, 
		ITRiASExpression *pIExpr)
	{
		_ASSERTE(NULL != hPr);
		_ASSERTE(NULL != lIdent);

	trias_nativeident::CNativeIdent Ident(hPr, lIdent, dwTypes);

		return Ident.GetObjectsFromGuid(dwTypes, m_coll, NULL, pIExpr);
	}

// alle Objekte in Sortierreihenfolge eines Attributes liefern
	HRESULT FInitFromAttrib (HPROJECT hPr, INT_PTR lIdent, INT_PTR lAttrib, 
		BSTR bstrStart, BSTR bstrEnd, DBRANGEENUM rgRange)
	{
		_ASSERTE(NULL != hPr);
		_ASSERTE(NULL != lAttrib);

		USES_CONVERSION;

	trias_nativemerkmal::CNativeMerkmal Attrib (hPr, lAttrib);
	LPCSTR pcStart = (NULL != bstrStart) ? OLE2A(bstrStart) : NULL;
	LPCSTR pcEnd = (NULL != bstrEnd) ? OLE2A(bstrEnd) : NULL;

		return Attrib.GetObjects (m_coll, lIdent, pcStart, pcEnd, 
			(trias_nativemerkmal::CNativeMerkmal::RANGEENUM)rgRange);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		return riid==IID_ITRiASEnumNativeObjects ? S_OK : S_FALSE;
	}

// ITRiASNativeObjects
public:

// thread save collection methods
	STDMETHOD(get_Count)(long* pcount)
	{
	ObjectLock l(this);

		return _CollectionBase::get_Count(pcount);
	}
	STDMETHOD(get_Item)(long Index, INT_PTR *pvar)
	{
	ObjectLock l(this);

		return _CollectionBase::get_Item(Index, pvar);
	}
	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
	ObjectLock l(this);

		return _CollectionBase::get__NewEnum(ppUnk);
	}
};

///////////////////////////////////////////////////////////////////////////////
// nicht sortierende Objektmenge 
class CTRiASNativeObjectsVector :
	public CTRiASNativeObjects<CTRiASNativeObjectsVector, 
		CObjectsCollectionOnSTLImpl<INT_PTR, vector<INT_PTR> >, 
			&CLSID_TRiASNativeObjects>
{
public:
};

///////////////////////////////////////////////////////////////////////////////
// sortierende Objektmenge (Ascending)
class CTRiASNativeObjectsSet :
	public CTRiASNativeObjects<CTRiASNativeObjectsSet, 
		CObjectsCollectionOnSTLImpl<INT_PTR, set<INT_PTR> >, 
			&CLSID_TRiASNativeObjectsSorted>
{
public:
};

///////////////////////////////////////////////////////////////////////////////
// sortierende Objektmenge (Descending)
class CTRiASNativeObjectsSetDesc :
	public CTRiASNativeObjects<CTRiASNativeObjectsSetDesc, 
		CObjectsCollectionOnSTLImpl<INT_PTR, set<INT_PTR, greater<INT_PTR> > >, 
			&CLSID_TRiASNativeObjectsSortedDesc>
{
public:
};

#endif // !defined(_TRIASNATIVEOBJECTS_H__C2B8E4B3_737C_4983_B88E_862485F765F4__INCLUDED_)
