// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.06.2002 09:53:20 
//
// @doc
// @module MkSABiSTabChildWindow.cpp | Definition of the <c CMkSABiSTabChildWindow> class

#include "stdafx.h"
#include "TRSABIS.h"

#include <Com/MkBase.h>
#include <Com/MkBase.cpp>

#include "SABiSTabChildWindow.h"
#include "MkSABiSTabChildWindow.h"

/////////////////////////////////////////////////////////////////////////////
// CMkSABiSTabChildWindow

#undef CHECKOUTPOINTER
#undef CHECKINPOINTER

#define CHECKINPOINTER(x) if (NULL != x) {} else { return E_POINTER; }
#define CHECKOUTPOINTER(x) if (NULL != x) { *(x) = NULL; } else { return E_POINTER; }

///////////////////////////////////////////////////////////////////////////////
// IMoniker
STDMETHODIMP CMkSABiSTabChildWindow::BindToObject(IBindCtx *pbc, IMoniker *pmkToLeft, 
	REFIID riidResult, void **ppvResult)
{
	CHECKOUTPOINTER(ppvResult);
	CHECKINPOINTER(pbc);
	
	if (NULL == pmkToLeft) {
		COM_TRY {
		CComObject<CSabisTabChildWindow> *pWnd = NULL;

			THROW_FAILED_HRESULT(CComObject<CSabisTabChildWindow>::CreateInstance(&pWnd));

		WUnknown Unk (pWnd->GetUnknown());	// pending AddRef

			THROW_FAILED_HRESULT(pWnd -> RegisterTabWindow(m_bstrInit, m_fUse2ndOne));
			THROW_FAILED_HRESULT(pWnd -> CreateClientWindow());
			THROW_FAILED_HRESULT(pWnd -> QueryInterface (riidResult, ppvResult));
		
		} COM_CATCH;
		return S_OK;
	}
	return E_UNEXPECTED;
}

STDMETHODIMP CMkSABiSTabChildWindow::GetDisplayName (IBindCtx *pbc, IMoniker *pmkToLeft, 
	LPOLESTR *ppszDisplayName)
{
	CHECKOUTPOINTER(ppszDisplayName);
	CHECKINPOINTER(pbc);
	
HRESULT hr = E_OUTOFMEMORY;
	
// Name = "TRiAS.MkSABiSTabChildWindow.1:bstrInit", bstrInit ist der Text auf der TabLasche
const size_t PREFIX_LEN = ocslen (ProgID());

	*ppszDisplayName = (LPOLESTR)CoTaskMemAlloc((PREFIX_LEN+1 + m_bstrInit.Length()+1 + 3) * sizeof(OLECHAR));
	if (NULL != *ppszDisplayName) {
		ocscpy (*ppszDisplayName, ProgID());
		(*ppszDisplayName)[PREFIX_LEN] = ':';

		ocscpy (&((*ppszDisplayName)[PREFIX_LEN + 1]), m_fUse2ndOne ? L"{2}" : L"{1}");
		ocscpy (&((*ppszDisplayName)[PREFIX_LEN + 4]), m_bstrInit);
		hr = S_OK;
	}
	return hr;
}

STDMETHODIMP CMkSABiSTabChildWindow::ParseDisplayName(
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

	// feststellen, welches der SABiS-Fenster erzeugt werden soll
		if (L'{' == m_bstrInit[0] && L'}' == m_bstrInit[2]) {
		CComBSTR bstr (&m_bstrInit[3]);

			_ASSERTE(L'1' == m_bstrInit[1] || L'2' == m_bstrInit[1]);
			m_fUse2ndOne = (L'2' == m_bstrInit[1]) ? true : false;
			m_bstrInit = bstr.Detach();
		}

	// Calculate cchEaten and hand out ourselves
		*pchEaten = &pszDisplayParam[nInitLen] - pszDisplayName;
		(*ppmkOut = this)->AddRef();
		return S_OK;
	}
	return MK_E_SYNTAX;
}

