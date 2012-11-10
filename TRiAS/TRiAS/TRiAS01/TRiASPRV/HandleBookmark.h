// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 08:43:09 
//
// @doc
// @module HandleBookmark.h | Declaration of the <c CHandleBookmark> class

#if !defined(_HANDLEBOOKMARK_H__28C3E8C1_26A1_46A9_B63E_931539B71205__INCLUDED_)
#define _HANDLEBOOKMARK_H__28C3E8C1_26A1_46A9_B63E_931539B71205__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CHandleBookmark

class ATL_NO_VTABLE CHandleBookmark : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CHandleBookmark, &CLSID_HandleBookmark>,
	public IHandleDataAccess,
	public ITRiASExpression
{
public:
// Construction
	CHandleBookmark() {}
	~CHandleBookmark() {}

// Initialisation

// Operations
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CHandleBookmark)
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
		_ASSERTE(NULL == *ppData);

	INT_PTR *pObjNr = reinterpret_cast<INT_PTR *>(SysAllocStringByteLen(NULL, sizeof(INT_PTR)));

		if (NULL == pObjNr)
			return E_OUTOFMEMORY;

		*(INT_PTR *)pObjNr = lONr;		// Objektnummer _ist_ der Bookmark
		*ppData = pObjNr;
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

		*pulLen = sizeof(INT_PTR);
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
		_ASSERTE(NULL != pvValue);

		V_VT(pvValue) = VT_I4;
		V_I4(pvValue) = lONr;
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(DWORD);
		*pType = DBTYPE_UI4;
		*pbPrec = 10;
		return S_OK;
	}
};

#endif // !defined(_HANDLEBOOKMARK_H__28C3E8C1_26A1_46A9_B63E_931539B71205__INCLUDED_)
