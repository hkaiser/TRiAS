// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.06.2001 09:00:33 
//
// @doc
// @module HandleExpression.h | Declaration of the <c CHandleExpression> class

#if !defined(_HANDLEEXPRESSION_H__0CA2433D_5883_4A25_A49F_23BFA9C87C0E__INCLUDED_)
#define _HANDLEEXPRESSION_H__0CA2433D_5883_4A25_A49F_23BFA9C87C0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CHandleExpression

class ATL_NO_VTABLE CHandleExpression : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CHandleExpression, &CLSID_HandleExpression>,
	public IHandleDataAccess,
	public ITRiASExpression
{
public:
// Construction
	CHandleExpression() {}
	~CHandleExpression() {}

// Initialisation
	HRESULT CHandleExpression::FinalConstruct()
	{
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void CHandleExpression::FinalRelease()
	{
	}

// Operations
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT SetExpression (ITRiASExpression *pIExpr)
	{
		m_Expr = pIExpr;
		return S_OK;
	}

// Interface map
	BEGIN_COM_MAP(CHandleExpression)
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
	STDMETHODIMP FetchData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBinding, void **ppData)
	{
		_ASSERTE(NULL == *ppData);

	CComVariant vValue;

		RETURN_ERROR(m_Expr -> Calculate(hPrjHandle, lONr, &vValue));
		RETURN_ERROR(vValue.ChangeType(VT_BSTR));
		*ppData = V_BSTR(&vValue);
		V_VT(&vValue) = VT_EMPTY;		// detach
		return S_OK;
	}
	STDMETHODIMP StoreData(INT_PTR hPrjHandle, INT_PTR lONr, DBBINDING *pBinding, ULONG ulSize, void *pData)
	{
		return E_NOTIMPL;
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
	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(m_Expr != NULL);
		return m_Expr -> Calculate(hPrjHandle, lONr, pvValue);
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(m_Expr != NULL);
		return m_Expr -> GetTypeInfo (pulColSize, pType, pbPrec);
	}

private:
	CComPtr<ITRiASExpression> m_Expr;
};

#endif // !defined(_HANDLEEXPRESSION_H__0CA2433D_5883_4A25_A49F_23BFA9C87C0E__INCLUDED_)
