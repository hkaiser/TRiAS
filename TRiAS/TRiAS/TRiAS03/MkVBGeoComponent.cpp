// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 19:32:40 
//
// @doc
// @module MkVBGeoComponent.cpp | Definition of the <c CMkVBGeoComponent> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/MkBase.h>
#include <Com/MkBase.cpp>

#include <triastlb.h>

#include "VBPropertySequence.h"
#include "MkVBGeoComponent.h"

/////////////////////////////////////////////////////////////////////////////
// CMkVBGeoComponent

#undef CHECKOUTPOINTER
#undef CHECKINPOINTER

#define CHECKINPOINTER(x) if (NULL != x) {} else { return E_POINTER; }
#define CHECKOUTPOINTER(x) if (NULL != x) { *(x) = NULL; } else { return E_POINTER; }

///////////////////////////////////////////////////////////////////////////////
// IMoniker
STDMETHODIMP CMkVBGeoComponent::BindToObject(IBindCtx *pbc, IMoniker *pmkToLeft, 
	REFIID riidResult, void **ppvResult)
{
	CHECKOUTPOINTER(ppvResult);
	CHECKINPOINTER(pbc);
	
	if (NULL == pmkToLeft) {
		COM_TRY {
		CComObject<CVBGeoComponent> *pPA = NULL;

			THROW_FAILED_HRESULT(CComObject<CVBGeoComponent>::CreateInstance(&pPA));

		WUnknown Unk (pPA->GetUnknown());	// pending AddRef

			THROW_FAILED_HRESULT(pPA -> CreateEmbeddedAction(m_bstrInit));
			THROW_FAILED_HRESULT(pPA -> QueryInterface(riidResult, ppvResult));

		} COM_CATCH;
		return S_OK;
	}
	return E_UNEXPECTED;
}

STDMETHODIMP CMkVBGeoComponent::GetDisplayName (IBindCtx *pbc, IMoniker *pmkToLeft, 
	LPOLESTR *ppszDisplayName)
{
	CHECKOUTPOINTER(ppszDisplayName);
	CHECKINPOINTER(pbc);
	
HRESULT hr = E_OUTOFMEMORY;
	
// Name = "TRiAS.VBGeoComponent.1:bstrInit", bstrInit ist der ProgId der eigentlichen PA
const size_t PREFIX_LEN = ocslen (ProgID());

	*ppszDisplayName = (LPOLESTR)CoTaskMemAlloc((PREFIX_LEN+1 + m_bstrInit.Length()+1 + 3) * sizeof(OLECHAR));
	if (NULL != *ppszDisplayName) {
		ocscpy (*ppszDisplayName, ProgID());
		(*ppszDisplayName)[PREFIX_LEN] = ':';

		ocscpy (&((*ppszDisplayName)[PREFIX_LEN + 1]), m_bstrInit);
		hr = S_OK;
	}
	return hr;
}

STDMETHODIMP CMkVBGeoComponent::ParseDisplayName(
	IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR pszDisplayName, ULONG *pchEaten, 
	IMoniker **ppmkOut)
{
	CHECKOUTPOINTER(ppmkOut);
	CHECKOUTPOINTER(pchEaten);
	CHECKINPOINTER(pbc);
	CHECKINPOINTER(pszDisplayName);
	CHECKINPOINTER(pchEaten);
	
	if (NULL != pmkToLeft)
		return E_UNEXPECTED;
	
const wchar_t *pszDisplayParam = 0;

	if (CComMonikerBase::MatchesProgID(pszDisplayName, &pszDisplayParam)) {
	// save remaining initstring, search EOS or '!'
	size_t nInitLen = 0;

		while (OLECHAR('!') != pszDisplayParam[nInitLen] && 0 != pszDisplayParam[nInitLen])
			++nInitLen;
		m_bstrInit = CComBSTR(nInitLen, pszDisplayParam);

	// Calculate cchEaten and hand out ourselves
		*pchEaten = &pszDisplayParam[nInitLen] - pszDisplayName;
		(*ppmkOut = this)->AddRef();
		return S_OK;
	}
	return MK_E_SYNTAX;
}

