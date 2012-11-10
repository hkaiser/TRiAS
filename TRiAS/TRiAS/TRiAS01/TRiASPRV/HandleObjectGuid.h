// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 09:04:37 
//
// @doc
// @module HandleObjectGuid.h | Declaration of the <c CHandleObjectGuid> class

#if !defined(_HANDLEOBJECTGUID_H__34ED4399_5C80_48C7_A5D8_D0486EB751E1__INCLUDED_)
#define _HANDLEOBJECTGUID_H__34ED4399_5C80_48C7_A5D8_D0486EB751E1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CHandleObjectGuid

class ATL_NO_VTABLE CHandleObjectGuid : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CHandleObjectGuid, &CLSID_HandleObjectGuid>,
	public IHandleDataAccess,
	public ITRiASExpression
{
public:
// Construction
	CHandleObjectGuid() {}
	~CHandleObjectGuid() {}

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
	BEGIN_COM_MAP(CHandleObjectGuid)
		COM_INTERFACE_ENTRY(IHandleDataAccess)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

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

	CComBSTR bstrGuid;
	
		RETURN_ERROR(m_ObjectService -> get_Guid(hPrjHandle, lONr, &bstrGuid));
	
	GUID *pGuid = reinterpret_cast<GUID *>(SysAllocStringByteLen(NULL, sizeof(GUID)));

		if (NULL == pGuid)
			return E_OUTOFMEMORY;

		RETURN_ERROR(IIDFromString (bstrGuid, pGuid));
		*ppData = pGuid;
		return S_OK;
	}
	STDMETHODIMP StoreData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBindCur, ULONG ulSize, void *pData)
	{
		_ASSERTE(m_ObjectService != NULL);
		return DB_E_READONLYACCESSOR;
	}
	STDMETHODIMP GetDataLength (void *pData, ULONG *pulLen)
	{
		_ASSERTE(NULL != pulLen);
		_ASSERTE(NULL != pData);

		*pulLen = sizeof(GUID);
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

		V_VT(pvValue) = VT_EMPTY;
		if (SUCCEEDED(m_ObjectService -> get_Guid(hPrjHandle, lONr, &V_BSTR(pvValue))))
			V_VT(pvValue) = VT_BSTR;
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(GUID);
		*pType = DBTYPE_GUID;
		*pbPrec = ~0;
		return S_OK;
	}

private:
	CComPtr<ITRiASNativeObject> m_ObjectService;
};

#endif // !defined(_HANDLEOBJECTGUID_H__34ED4399_5C80_48C7_A5D8_D0486EB751E1__INCLUDED_)
