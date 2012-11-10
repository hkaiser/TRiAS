// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 19.05.2001 22:41:55 
//
// @doc
// @module HandleNativeAttribute.h | Declaration of the <c CHandleNativeAttribute> class

#if !defined(_HANDLENATIVEATTRIBUTE_H__9EDA4AAC_5858_4F9E_8D9F_8B1AE01C1CDB__INCLUDED_)
#define _HANDLENATIVEATTRIBUTE_H__9EDA4AAC_5858_4F9E_8D9F_8B1AE01C1CDB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CHandleNativeAttribute

class ATL_NO_VTABLE CHandleNativeAttribute : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CHandleNativeAttribute, &CLSID_HandleNativeAttribute>,
	public IHandleDataAccess,
	public ITRiASExpression
{
public:
// Construction
	CHandleNativeAttribute() : m_lMCode(0) {}
	~CHandleNativeAttribute() {}

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

	HRESULT SetAttributeHandle (INT_PTR lMCode)
	{
		m_lMCode = lMCode;
		return S_OK;
	}

// Interface map
	BEGIN_COM_MAP(CHandleNativeAttribute)
		COM_INTERFACE_ENTRY(IHandleDataAccess)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

public:
// IHandleDataAccess
	STDMETHODIMP FetchData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBindCur, void **ppData)
	{
		_ASSERTE(m_ObjectService != NULL);
		_ASSERTE(NULL != m_lMCode);
		_ASSERTE(NULL == *ppData);

		return m_ObjectService -> get_Attribute(hPrjHandle, lONr, m_lMCode, (BSTR *)ppData);
	}
	STDMETHODIMP StoreData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBindCur, ULONG ulSize, void *pData)
	{
		_ASSERTE(m_ObjectService != NULL);
		_ASSERTE(NULL != m_lMCode);
		return DB_E_READONLYACCESSOR;
	}
	STDMETHODIMP GetDataLength (void *pData, ULONG *pulLen)
	{
		_ASSERTE(NULL != pulLen);
		_ASSERTE(NULL != pData);

		*pulLen = SysStringLen((BSTR)pData) * sizeof(OLECHAR);		// Nullbyte nicht mitzählen
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
		_ASSERTE(NULL != m_lMCode);
		_ASSERTE(NULL != pvValue);

		V_VT(pvValue) = VT_EMPTY;
		if (SUCCEEDED(m_ObjectService -> get_Attribute(hPrjHandle, lONr, m_lMCode, &V_BSTR(pvValue)))) 
			V_VT(pvValue) = VT_BSTR;
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = LONG_MAX;
		*pType = DBTYPE_WSTR;
		*pbPrec = ~0;
		return S_OK;
	}

private:
	CComPtr<ITRiASNativeObject> m_ObjectService;
	INT_PTR m_lMCode;
};

#endif // !defined(_HANDLENATIVEATTRIBUTE_H__9EDA4AAC_5858_4F9E_8D9F_8B1AE01C1CDB__INCLUDED_)
