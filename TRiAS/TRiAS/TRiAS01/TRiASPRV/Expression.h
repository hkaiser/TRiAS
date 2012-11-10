// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 07.06.2001 20:09:19 
//
// @doc
// @module Expression.h | Declaration of the expression hierarchy classes

#if !defined(_EXPRESSION_H__6F865D4B_1DE2_4EF4_8DA7_0D986FBF3DE1__INCLUDED_)
#define _EXPRESSION_H__6F865D4B_1DE2_4EF4_8DA7_0D986FBF3DE1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Basisklassen

// Operationen, die eine abhängige Operation haben
class ATL_NO_VTABLE CSingleBaseExpression :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ITRiASExpression
{
protected:
// nicht direkt instantiieren
	CSingleBaseExpression()	{}

public:
	HRESULT Init (ITRiASExpression *pIBase) 
	{ 
		m_Base = pIBase; 
		return S_OK;
	}

// Interface map
	BEGIN_COM_MAP(CSingleBaseExpression)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(m_Base != NULL);
		return m_Base -> Calculate(hPrjHandle, lONr, pvValue);
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(m_Base != NULL);
		return m_Base -> GetTypeInfo(pulColSize, pType, pbPrec);
	}

protected:
	CComPtr<ITRiASExpression> m_Base;
};

// Operationen, die zwei abhängige Operationen haben
class ATL_NO_VTABLE CDualBaseExpression :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ITRiASExpression
{
protected:
// nicht direkt instantiieren
	CDualBaseExpression() {}

public:
	HRESULT Init (ITRiASExpression *pILeft, ITRiASExpression *pIRight)
	{
		m_Left = pILeft;
		m_Right = pIRight;
		return S_OK;
	}

// Interface map
	BEGIN_COM_MAP(CDualBaseExpression)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvLeft, VARIANT *pvRight)
	{
		_ASSERTE(m_Left != NULL && (NULL == pvRight || m_Right != NULL));
		RETURN_ERROR(m_Left -> Calculate(hPrjHandle, lONr, pvLeft));
		if (NULL != pvRight)
			RETURN_ERROR(m_Right -> Calculate(hPrjHandle, lONr, pvRight));
		return S_OK;
	}

protected:
	CComPtr<ITRiASExpression> m_Left;
	CComPtr<ITRiASExpression> m_Right;
};

///////////////////////////////////////////////////////////////////////////////
// Konstanter Ausdruck
class ATL_NO_VTABLE CConstantExpression :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ITRiASExpression
{
public:
	HRESULT Init (VARIANT vValue, ULONG ulColSize, BYTE bPrec) 
	{
		m_ulColSize = ulColSize;
		m_bPrec = bPrec;
		return ::VariantCopy(&m_vValue, &vValue);
	}

// Interface map
	BEGIN_COM_MAP(CConstantExpression)
		COM_INTERFACE_ENTRY(ITRiASExpression)
	END_COM_MAP()

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);
		return ::VariantCopy(pvValue, &m_vValue);
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = m_ulColSize;
		*pType = DBTYPE(V_VT(&m_vValue));		// DBTYPE == VARTYPE
		*pbPrec = m_bPrec;
		return S_OK;
	}

private:
	CComVariant m_vValue;
	ULONG m_ulColSize;
	BYTE m_bPrec;
};

///////////////////////////////////////////////////////////////////////////////
// Logische Operationen
template<typename pred>
class ATL_NO_VTABLE CLogicPrefixExpression :
	public CDualBaseExpression
{
public:
	HRESULT Init (ITRiASExpression *pIToTest, ITRiASExpression *pIDummy)
	{
		_ASSERTE(NULL == pIDummy)
		return CDualBaseExpression::Init(pIToTest, pIDummy);
	}

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);

	CComVariant vValue;

		RETURN_ERROR(CDualBaseExpression::Calculate (hPrjHandle, lONr, &vValue, NULL));

		V_VT(pvValue) = VT_BOOL;
		V_BOOL(pvValue) = pred()(VT_EMPTY, V_VT(&vValue)) ? VARIANT_TRUE : VARIANT_FALSE;
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(VARIANT_BOOL);
		*pType = DBTYPE_BOOL;
		*pbPrec = ~0;
		return S_OK;
	}
};

typedef CLogicPrefixExpression<equal_to<VARTYPE> > CIsNullExpression;
typedef CLogicPrefixExpression<not_equal_to<VARTYPE> > CIsNotNullExpression;

///////////////////////////////////////////////////////////////////////////////
// Negation
class ATL_NO_VTABLE CNotExpression :
	public CSingleBaseExpression
{
public:
	HRESULT Init (ITRiASExpression *pIToTest)
	{
		return CSingleBaseExpression::Init(pIToTest);
	}

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);

		RETURN_ERROR(CSingleBaseExpression::Calculate (hPrjHandle, lONr, pvValue));
		_ASSERTE(V_ISBOOL(pvValue));

		V_BOOL(pvValue) = V_BOOL(pvValue) ? VARIANT_FALSE : VARIANT_TRUE;		// negate
		return S_OK;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(VARIANT_BOOL);
		*pType = DBTYPE_BOOL;
		*pbPrec = ~0;
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Vergleichsoperationen, Basisklasse
template<typename pred>
class ATL_NO_VTABLE CCompareExpression :
	public CDualBaseExpression
{
public:
	HRESULT Init(ITRiASExpression *pILeft, ITRiASExpression *pIRight) 
	{
		return CDualBaseExpression::Init(pILeft, pIRight);
	}

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);

	CComVariant vLeft, vRight;

		RETURN_ERROR(CDualBaseExpression::Calculate (hPrjHandle, lONr, &vLeft, &vRight));
		if (pred()(vLeft, vRight)) {
			V_VT(pvValue) = VT_BOOL;
			V_BOOL(pvValue) = VARIANT_TRUE;
			return S_OK;
		}
		else if (SUCCEEDED(vLeft.ChangeType(VT_I4)) && SUCCEEDED(vRight.ChangeType(VT_I4))) {
			V_VT(pvValue) = VT_BOOL;
			V_BOOL(pvValue) = pred()(vLeft, vRight) ? VARIANT_TRUE : VARIANT_FALSE;
			return S_OK;
		}
		else if (SUCCEEDED(vLeft.ChangeType(VT_BSTR)) && SUCCEEDED(vRight.ChangeType(VT_BSTR))) {
			V_VT(pvValue) = VT_BOOL;
			V_BOOL(pvValue) = pred()(vLeft, vRight) ? VARIANT_TRUE : VARIANT_FALSE;
			return S_OK;
		}
		return TRIASOLEDB_E_SQL_TYPEMISMATCH;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(VARIANT_BOOL);
		*pType = DBTYPE_BOOL;
		*pbPrec = ~0;
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// konkrete Vergleichsoperatoren
typedef CCompareExpression<equal_to<CComVariant> > CEqualExpression;
typedef CCompareExpression<not_equal_to<CComVariant> > CNotEqualExpression;
typedef CCompareExpression<greater<CComVariant> > CGreaterExpression;
typedef CCompareExpression<less<CComVariant> > CLessExpression;
typedef CCompareExpression<less_equal<CComVariant> > CLessEqualExpression;
typedef CCompareExpression<greater_equal<CComVariant> > CGreaterEqualExpression;

// erstmal Identität prüfen
inline bool Like (const CComVariant &rvLeft, const CComVariant &rvRight)
{
	return rvLeft == rvRight;
}

template<class T>
class like_to : 
	public os_binary_function<T, T, bool>
{
public:
	bool operator()(const T& x, const T& y) const
	{
		return Like(x, y);
	}
};
typedef CCompareExpression<like_to<CComVariant> > CLikeExpression;

///////////////////////////////////////////////////////////////////////////////
// Mathematische Grundrechenarten, BasisKlasse
template<const VARTYPE vt>
inline long GetValue (const VARIANT *pvVal);

template<> 
inline long GetValue<VT_I4> (const VARIANT *pvVal)
{
	return V_I4(pvVal);
}
template<> 
inline long GetValue<VT_BOOL> (const VARIANT *pvVal)
{
	return V_BOOL(pvVal);
}

template<const VARTYPE vt>
inline void SetValue (VARIANT *pvVal, long);

template<> 
inline void SetValue<VT_I4> (VARIANT *pvVal, long lValue)
{
	V_I4(pvVal) = lValue;
}
template<> 
inline void SetValue<VT_BOOL> (VARIANT *pvVal, long lValue)
{
	V_BOOL(pvVal) = lValue ? VARIANT_TRUE : VARIANT_FALSE;
}

template<typename op, const ULONG SizeOf, const VARTYPE Type, const BYTE Prec>
class ATL_NO_VTABLE CMathOpExpression :
	public CDualBaseExpression
{
public:
	HRESULT Init(ITRiASExpression *pILeft, ITRiASExpression *pIRight) 
	{
		return CDualBaseExpression::Init(pILeft, pIRight);
	}

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);

	CComVariant vLeft, vRight;

		RETURN_ERROR(CDualBaseExpression::Calculate (hPrjHandle, lONr, &vLeft, &vRight));

		if (SUCCEEDED(vLeft.ChangeType(Type)) && SUCCEEDED(vRight.ChangeType(Type))) {
			V_VT(pvValue) = Type;
			SetValue<Type>(pvValue, op()(GetValue<Type>(&vLeft), GetValue<Type>(&vRight)));
			return S_OK;
		}
		return TRIASOLEDB_E_SQL_TYPEMISMATCH;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = SizeOf;
		*pType = DBTYPE(Type);
		*pbPrec = ~0;
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// konkrete mathematische Grundrechenarten
template<>
class ATL_NO_VTABLE CMathOpExpression<plus<long>, sizeof(DWORD), VT_I4, 10> :
	public CDualBaseExpression
{
public:
	HRESULT Init(ITRiASExpression *pILeft, ITRiASExpression *pIRight) 
	{
		return CDualBaseExpression::Init(pILeft, pIRight);
	}

	STDMETHODIMP Calculate (INT_PTR hPrjHandle, INT_PTR lONr, VARIANT *pvValue)
	{
		_ASSERTE(NULL != pvValue);

	CComVariant vLeft, vRight;

		RETURN_ERROR(CDualBaseExpression::Calculate (hPrjHandle, lONr, &vLeft, &vRight));

		if (SUCCEEDED(vLeft.ChangeType(VT_I4)) && SUCCEEDED(vRight.ChangeType(VT_I4))) {
			V_VT(pvValue) = VT_I4;
			V_I4(pvValue) = V_I4(&vLeft) + V_I4(&vRight);
			return S_OK;
		}
		else if (SUCCEEDED(vLeft.ChangeType(VT_BSTR)) && SUCCEEDED(vRight.ChangeType(VT_BSTR))) {
		CComBSTR bstr (V_BSTR(&vLeft));

			bstr.Append(V_BSTR(&vRight));
			V_VT(pvValue) = VT_BSTR;
			V_BSTR(pvValue) = bstr.Detach();
			return S_OK;
		}
		return TRIASOLEDB_E_SQL_TYPEMISMATCH;
	}
	STDMETHODIMP GetTypeInfo (ULONG *pulColSize, DBTYPE *pType, BYTE *pbPrec)
	{
		_ASSERTE(NULL != pulColSize && NULL != pType && NULL != pbPrec);
		*pulColSize = sizeof(DWORD);
		*pType = DBTYPE_I4;
		*pbPrec = 10;
		return S_OK;
	}
};

typedef CMathOpExpression<plus<long>, sizeof(DWORD), VT_I4, 10> CPlusExpression;
typedef CMathOpExpression<minus<long>, sizeof(DWORD), VT_I4, 10> CMinusExpression;
typedef CMathOpExpression<times<long>, sizeof(DWORD), VT_I4, 10> CTimesExpression;
typedef CMathOpExpression<divides<long>, sizeof(DWORD), VT_I4, 10> CDividesExpression;

typedef CMathOpExpression<logical_and<VARIANT_BOOL>, sizeof(VARIANT_BOOL), VT_BOOL, ~0> CAndExpression;
typedef CMathOpExpression<logical_or<VARIANT_BOOL>, sizeof(VARIANT_BOOL), VT_BOOL, ~0> COrExpression;

#endif // !defined(_EXPRESSION_H__6F865D4B_1DE2_4EF4_8DA7_0D986FBF3DE1__INCLUDED_)
