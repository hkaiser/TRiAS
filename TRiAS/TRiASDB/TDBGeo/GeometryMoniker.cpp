// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.05.2000 09:29:50
//
// @doc
// @module GeometryMoniker.cpp | Implementation of the <c CGeometryMoniker> class

#include "stdafx.h"

#include <Com/MkBase.h>
#include <Com/MkBase.cpp>

#include "TDBGeoImpl.h"
#include "GeometryMoniker.h"

/////////////////////////////////////////////////////////////////////////////
// CGeometryMoniker

const size_t GUID_LEN = 38;		// "{...}"

#undef CHECKOUTPOINTER
#undef CHECKINPOINTER

#define CHECKINPOINTER(x) if (NULL != x) {} else { return E_POINTER; }
#define CHECKOUTPOINTER(x) if (NULL != x) { *(x) = NULL; } else { return E_POINTER; }

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSGeometryProperties);
DefineSmartInterface(PersistStreamInit);

// IMoniker
STDMETHODIMP CGeometryMoniker::BindToObject(IBindCtx *pbc, IMoniker *pmkToLeft, REFIID riidResult, void **ppvResult)
{
	CHECKOUTPOINTER(ppvResult);
	CHECKINPOINTER(pbc);
	
	if (NULL == pmkToLeft) {
		COM_TRY {
		WTRiASCSGeometryProperties Props (m_Guid);

			THROW_FAILED_HRESULT(WPersistStreamInit(Props) -> InitNew());
			THROW_FAILED_HRESULT(Props -> put_InitString (m_bstrInit));
			THROW_FAILED_HRESULT(Props -> QueryInterface (riidResult, ppvResult));
		
		} COM_CATCH;
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CGeometryMoniker::GetDisplayName (IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR *ppszDisplayName)
{
	CHECKOUTPOINTER(ppszDisplayName);
	CHECKINPOINTER(pbc);
	
HRESULT hr = E_OUTOFMEMORY;
	
// Name = "TRiAS.MkGeometry.1:{05F56161-0622-11D2-90BA-00104B2168FE}:bstrInit"
const size_t PREFIX_LEN = ocslen (ProgID());

	*ppszDisplayName = (LPOLESTR)CoTaskMemAlloc((PREFIX_LEN + 1 + GUID_LEN +1 + m_bstrInit.Length()) * sizeof(OLECHAR));
	if (NULL != *ppszDisplayName) {
		ocscpy (*ppszDisplayName, ProgID());
		(*ppszDisplayName)[PREFIX_LEN] = ':';
		StringFromGUID2 (m_Guid, *ppszDisplayName + PREFIX_LEN + 1, GUID_LEN + 1);
		(*ppszDisplayName)[PREFIX_LEN + 1 + GUID_LEN] = ':';
		ocscpy (&((*ppszDisplayName)[PREFIX_LEN + 1 + GUID_LEN + 1]), m_bstrInit);
		hr = S_OK;
	}
	return hr;
}

STDMETHODIMP CGeometryMoniker::ParseDisplayName(
	IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
{
	CHECKOUTPOINTER(ppmkOut);
	CHECKOUTPOINTER(pchEaten);
	CHECKINPOINTER(pbc);
	CHECKINPOINTER(pszDisplayName);
	CHECKINPOINTER(pchEaten);
	
	if (pmkToLeft)
		return E_UNEXPECTED;
	
const wchar_t *pszDisplayParam = 0;

	if (CComMonikerBase::MatchesProgID(pszDisplayName, &pszDisplayParam)) {
	// Pull out param up to first ":" or end of string
	size_t nParamLen = 0;
	
		while (OLECHAR(':') != pszDisplayParam[nParamLen] && 0 != pszDisplayParam[nParamLen])
			++nParamLen;
		
	// convert CLSID
	HRESULT hr = MK_E_SYNTAX;
	CComBSTR bstrGuid (nParamLen, pszDisplayParam);

		m_Guid = CIID(bstrGuid);
		if (!m_Guid) {	// Check for ProgID
		// NOTE: This doesn't resolve on the machine of the guy to the left.
		//		 It only resolves on the machine the 'TRiAS.MkGeometry.1' is running.
			m_Guid = CIID(const_cast<LPOLESTR>(pszDisplayParam), CIID::INITCIID_InitFromProgId);
		}

	// save remaining initstring
		if (!!m_Guid) {
		// search EOS or '!'
		size_t nInitLen = nParamLen;

			while (OLECHAR('!') != pszDisplayParam[nInitLen] && 0 != pszDisplayParam[nInitLen])
				++nInitLen;
			m_bstrInit = CComBSTR(nInitLen - nParamLen, &pszDisplayParam[nParamLen] +1);

		// Calculate cchEaten and hand out ourselves
			*pchEaten = &pszDisplayParam[nInitLen] - pszDisplayName;
			(*ppmkOut = this)->AddRef();
			return S_OK;
		}
		return hr;
	}
	return MK_E_SYNTAX;
}

