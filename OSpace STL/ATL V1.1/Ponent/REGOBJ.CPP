// RegObj.cpp : Implementation of CregisterApp and DLL registration.

#include "stdafx.h"
#include "register.h"
#include "RegObj.h"

STDMETHODIMP CDLLRegObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (InlineIsEqualGUID(riid,IID_IRegistrar))
		return S_OK;
	return S_FALSE;
}

STDMETHODIMP CDLLRegObject::AddReplacement(BSTR key, BSTR item)
{
	return CRegObject::AddReplacement(key, item);
}

STDMETHODIMP CDLLRegObject::ClearReplacements()
{
	return CRegObject::ClearReplacements();
}

STDMETHODIMP CDLLRegObject::ResourceRegister(BSTR resFileName, VARIANT ID,  VARIANT type)
{
	CRegException re;
	HRESULT hr =  CRegObject::ResourceRegister(resFileName, ID, type, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::ResourceUnregister(BSTR resFileName, VARIANT ID, VARIANT type)
{
	CRegException re;
	HRESULT hr =  CRegObject::ResourceUnregister(resFileName, ID, type, re);
	if FAILED(hr)
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::FileUnregister(BSTR fileName)
{
	CRegException re;
	HRESULT hr =  CRegObject::FileUnregister(fileName, re);
	if FAILED(hr)
		ReportToIError(re);
	return hr;
}
STDMETHODIMP CDLLRegObject::FileRegister(BSTR fileName)
{
	CRegException re;
	HRESULT hr =  CRegObject::FileRegister(fileName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::StringRegister(BSTR data)
{
	CRegException re;
	HRESULT hr = CRegObject::StringRegister(data, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::StringUnregister(BSTR data)
{
	CRegException re;
	HRESULT hr = CRegObject::StringUnregister(data, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::AddKey(BSTR keyName)
{
	CRegException re;
	HRESULT hr = CRegObject::AddKey(keyName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::DeleteKey(BSTR keyName)
{
	CRegException re;
	HRESULT hr = CRegObject::DeleteKey(keyName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::AddKeyValue(BSTR keyName, BSTR valueName, VARIANT value)
{
	CRegException re;
	HRESULT hr = CRegObject::SetKeyValue(keyName, valueName, value, re, TRUE);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::GetKeyValue(BSTR keyName, BSTR valueName, VARIANT* pvalue)
{
	CRegException re;
	HRESULT hr = CRegObject::GetKeyValue(keyName, valueName, pvalue, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CDLLRegObject::SetKeyValue(BSTR keyName, BSTR valueName, VARIANT value)
{
	CRegException re;
	HRESULT hr = CRegObject::SetKeyValue(keyName, valueName, value, re, FALSE);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

void CDLLRegObject::ReportToIError(CRegException& rEx)
{
	TCHAR           szDesc[2*_MAX_PATH];
	TCHAR           szPosition[_MAX_PATH];

	if (!LoadString(_Module.m_hInst, rEx.m_nID, szDesc, _MAX_PATH))
	{
		ATLTRACE(_T("Unable to load resource string %d\n"), rEx.m_nID);
		return;
	}

	if (-1 != rEx.m_cLines)
	{
		wsprintf(szPosition, _T(" @ Line %d"), rEx.m_cLines);
		lstrcat(szDesc, szPosition);
	}
	Error(szDesc, IID_IRegistrar);
}
