///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCSPointEnum.h | Description goes here

#if !defined(_TRIASCSPOINTENUM_H__C77EE754_4183_11D2_8C7E_006097A8F384__INCLUDED_)
#define _TRIASCSPOINTENUM_H__C77EE754_4183_11D2_8C7E_006097A8F384__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCSPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointEnum
class ATL_NO_VTABLE CTRiASCSPointEnum :
public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSPointEnum, &CLSID_TRiASCSPointEnum>,
	public IEnumVARIANT
{
public:
	CTRiASCSPointEnum()	// Argument damit ich weiss woher das ding hier kommt
	{
		m_nIndex = 0;	// ganz am Anfang
	}
	~CTRiASCSPointEnum()
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();
	DECLARE_NO_REGISTRY()

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASCSPointEnum)
	BEGIN_COM_MAP(CTRiASCSPointEnum)
		COM_INTERFACE_ENTRY(IEnumVARIANT)
	END_COM_MAP()

// IEnumVARIANT
public:
	STDMETHOD(Next)(/* [in] */ ULONG celt, /* [length_is][size_is][out] */ VARIANT __RPC_FAR * rgVar, /* [out] */ ULONG __RPC_FAR * pCeltFetched);
	STDMETHOD(Skip)(/* [in] */ ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(/* [out] */ IEnumVARIANT __RPC_FAR * __RPC_FAR * ppEnum);

// Not Interfaced
	void Init (_DGMPoints *pIPoints)
	{
		m_wParent = pIPoints;
	}

private:
	W_DGMPoints	m_wParent;	// wo gibts die Daten
	long m_nIndex;	// aktuelle Position
};

#endif // !defined(_TRIASCSPOINTENUM_H__C77EE754_4183_11D2_8C7E_006097A8F384__INCLUDED_)
