// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/08/1998 12:34:58 PM
//
// @doc
// @module CookieHelper.cpp | Implementation of the <c CCookieHelper> class

#include "stdafx.h"

#include "Helper.h"
#include "CookieHelper.h"

/////////////////////////////////////////////////////////////////////////////
// CCookieHelper

STDMETHODIMP CCookieHelper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICookieHelper,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CCookieHelper::CreateCookieHolder(BSTR bstrName, INT_PTR FirstCookie, INT_PTR *pCookieHolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pCookieHolder)
		return E_POINTER;

CLockCS lock(*this);

	if (S_OK == GetCookieHolder (bstrName, pCookieHolder, true))		// evtl. AddRef'n
		return S_FALSE;

pair<CCookieHolders::iterator, bool> p = m_Holders.insert(CCookieHolders::value_type(m_dwCookie, CCookieData(FirstCookie, bstrName)));

	if (!p.second)
		RETURN_FAILED_HRESULT(E_FAIL);

// wiederfinden
CCookieHolders::iterator it = m_Holders.find (m_dwCookie);

	ASSERT(it != m_Holders.end());
	RETURN_FAILED_HRESULT(Fire_CookieHolderInitialized((*it).second.GetName(), FirstCookie));

	*pCookieHolder = m_dwCookie++;
	return S_OK;
}

STDMETHODIMP CCookieHelper::GetNextCookie(INT_PTR CookieHolder, INT_PTR *pNewCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pNewCookie)
		return E_POINTER;

CLockCS lock(*this);
CCookieHolders::iterator it = m_Holders.find (CookieHolder);

	if (it == m_Holders.end())
		RETURN_FAILED_HRESULT(E_INVALIDARG);

	*pNewCookie = (*it).second.GetNextCookie();
	ASSERT(0 != *pNewCookie);

	RETURN_FAILED_HRESULT(Fire_IssuedNextCookie ((*it).second.GetName(), *pNewCookie));
	return S_OK;
}

STDMETHODIMP CCookieHelper::DeleteCookieHolder(INT_PTR CookieHolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CLockCS lock(*this);
CCookieHolders::iterator it = m_Holders.find (CookieHolder);

	if (it == m_Holders.end())
		RETURN_FAILED_HRESULT(E_INVALIDARG);

	if (0 == (*it).second.Release())
		m_Holders.erase (it);		// wenn's der letzte war
	return S_OK;
}

STDMETHODIMP CCookieHelper::GetCookieHolder(BSTR Name, INT_PTR *pCookieHolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return GetCookieHolder (Name, pCookieHolder, false);
}

HRESULT CCookieHelper::GetCookieHolder (BSTR Name, INT_PTR *pCookieHolder, bool fAddRef)
{
	if (NULL == pCookieHolder)
		return E_POINTER;

CLockCS lock(*this);

	for (CCookieHolders::iterator it = m_Holders.begin(); it != m_Holders.end(); ++it)
	{
		if (!wcscmp((*it).second.GetName(), Name)) {
			*pCookieHolder = (*it).first;
			if (fAddRef)
				(*it).second.AddRef();
			return S_OK;	// found required CookieHolder
		}
	}
	return S_FALSE;		// not found 
}

STDMETHODIMP CCookieHelper::SetInitialCookie(INT_PTR CookieHolder, INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CLockCS lock(*this);
CCookieHolders::iterator it = m_Holders.find (CookieHolder);

	if (it == m_Holders.end())
		RETURN_FAILED_HRESULT(E_INVALIDARG);

	(*it).second.SetInitialCookie(newVal);

	RETURN_FAILED_HRESULT(Fire_CookieHolderInitialized((*it).second.GetName(), newVal));
	return S_OK;
}

STDMETHODIMP CCookieHelper::GetLastCookie(INT_PTR CookieHolder, INT_PTR *pLastCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CLockCS lock(*this);
CCookieHolders::iterator it = m_Holders.find (CookieHolder);

	if (it == m_Holders.end())
		RETURN_FAILED_HRESULT(E_INVALIDARG);

	*pLastCookie = (*it).second.GetLastCookie();
	return S_OK;
}
