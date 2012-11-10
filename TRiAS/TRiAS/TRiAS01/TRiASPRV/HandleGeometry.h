// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 11:59:42 
//
// @doc
// @module HandleGeometry.h | Declaration of the <c CHandleGeometry> class

#if !defined(_HANDLEGEOMETRY_H__6C314B01_55CF_44F3_85FD_6CA6E3BA78C7__INCLUDED_)
#define _HANDLEGEOMETRY_H__6C314B01_55CF_44F3_85FD_6CA6E3BA78C7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/SafeArray.h>

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CHandleGeometry

class ATL_NO_VTABLE CHandleGeometry : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CHandleGeometry, &CLSID_HandleGeometry>,
	public IHandleDataAccess,
	public ITRiASExpression
{
public:
// Construction
	CHandleGeometry() : m_dwType(0) {}
	~CHandleGeometry() {}

// Initialisation
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_ObjectService.CoCreateInstance(CLSID_TRiASNativeObject));
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void FinalRelease()
	{
		m_ObjectService = NULL;
	}

// Operations
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CHandleGeometry)
		COM_INTERFACE_ENTRY(IHandleDataAccess)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

	void SetTargetType(DWORD dwType) { m_dwType = dwType; }

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// IHandleDataAccess
	STDMETHODIMP FetchData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBindCur, void **ppData)
	{
		_ASSERTE(m_ObjectService != NULL);
		_ASSERTE(NULL == *ppData);

	SAFEARRAY *psaResult = NULL;
	HRESULT hr = m_ObjectService -> GetGeometry (hPrjHandle, lONr, CComBSTR(L"Geometry"), &psaResult);

		if (FAILED(hr)) return hr;

	CSafeArray sa (VT_UI1);

		if (!sa.Attach (psaResult))
			return E_INVALIDARG;

		{
		CSafeArrayLock<BYTE> lock(sa);

			*ppData = SysAllocStringByteLen(NULL, lock.Size());
			if (NULL == *ppData) return E_OUTOFMEMORY;

			memcpy (*ppData, lock, lock.Size());
		}
		return S_OK;	
	}
	STDMETHODIMP StoreData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBindCur, ULONG ulSize, void *pData)
	{
		return DB_E_READONLYACCESSOR;
	}
	STDMETHODIMP GetDataLength (void *pData, ULONG *pulLen)
	{
		_ASSERTE(NULL != pulLen);
		_ASSERTE(NULL != pData);

		*pulLen = SysStringByteLen((BSTR)pData);
		return S_OK;
	}
	STDMETHODIMP ReleaseData (void *pData)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP get_MustIndirectGetData(VARIANT_BOOL *pfValue)
	{
		_ASSERTE(NULL != pfValue);

		*pfValue = VARIANT_FALSE;
		return S_OK;
	}
	STDMETHODIMP get_MustIndirectCompareData(VARIANT_BOOL *pfValue)
	{
		_ASSERTE(NULL != pfValue);

		*pfValue = VARIANT_TRUE;
		return S_OK;
	}

// ITRiASExpression
	STDMETHODIMP Calculate(INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(m_ObjectService != NULL);
		_ASSERTE(NULL != pvValue);

	SAFEARRAY *psaResult = NULL;
	
		V_VT(pvValue) = VT_EMPTY;
		if (SUCCEEDED(m_ObjectService -> GetGeometry (hPrjHandle, lONr, CComBSTR(L"Geometry"), &psaResult))) {
			V_VT(pvValue) = VT_UI1|VT_ARRAY;
			V_ARRAY(pvValue) = psaResult;
		}
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = ~0;
		*pType = DBTYPE_BYTES;
		*pbPrec = ~0;
		return S_OK;
	}

private:
	CComPtr<ITRiASNativeObject> m_ObjectService;
	DWORD m_dwType;		// Bezugs-Geometrietyp
};

#endif // !defined(_HANDLEGEOMETRY_H__6C314B01_55CF_44F3_85FD_6CA6E3BA78C7__INCLUDED_)
