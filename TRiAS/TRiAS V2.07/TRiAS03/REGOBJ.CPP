// RegObj.cpp : Implementation of CregisterApp and DLL registration.

#include "trias03p.hxx"

#include "TRiASHelper.h"
#include "RegObj.h"

#if defined(__ATL_20_USED__)
#include "static\\statreg.cpp"
#endif 

STDMETHODIMP CTRiASRegObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (InlineIsEqualGUID(riid, IID_ITRiASRegistryHelper))
		return S_OK;
	return S_FALSE;
}

STDMETHODIMP CTRiASRegObject::AddReplacement(BSTR key, BSTR item)
{
	return CRegObject::AddReplacement(key, item);
}

STDMETHODIMP CTRiASRegObject::ClearReplacements()
{
	return CRegObject::ClearReplacements();
}

STDMETHODIMP CTRiASRegObject::ResourceRegister(BSTR resFileName, VARIANT ID,  VARIANT type)
{
	CRegException re;
	HRESULT hr =  CRegObject::ResourceRegister(resFileName, ID, type, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::ResourceUnregister(BSTR resFileName, VARIANT ID, VARIANT type)
{
	CRegException re;
	HRESULT hr =  CRegObject::ResourceUnregister(resFileName, ID, type, re);
	if FAILED(hr)
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::FileUnregister(BSTR fileName)
{
	CRegException re;
	HRESULT hr =  CRegObject::FileUnregister(fileName, re);
	if FAILED(hr)
		ReportToIError(re);
	return hr;
}
STDMETHODIMP CTRiASRegObject::FileRegister(BSTR fileName)
{
	CRegException re;
	HRESULT hr =  CRegObject::FileRegister(fileName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::StringRegister(BSTR data)
{
	CRegException re;
	HRESULT hr = CRegObject::StringRegister(data, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::StringUnregister(BSTR data)
{
	CRegException re;
	HRESULT hr = CRegObject::StringUnregister(data, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::AddKey(BSTR keyName)
{
	CRegException re;
	HRESULT hr = CRegObject::AddKey(keyName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::DeleteKey(BSTR keyName)
{
	CRegException re;
	HRESULT hr = CRegObject::DeleteKey(keyName, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::AddKeyValue(BSTR keyName, BSTR valueName, VARIANT value)
{
	CRegException re;
	HRESULT hr = CRegObject::SetKeyValue(keyName, valueName, value, re, TRUE);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::GetKeyValue(BSTR keyName, BSTR valueName, VARIANT* pvalue)
{
	CRegException re;
	HRESULT hr = CRegObject::GetKeyValue(keyName, valueName, pvalue, re);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

STDMETHODIMP CTRiASRegObject::SetKeyValue(BSTR keyName, BSTR valueName, VARIANT value)
{
	CRegException re;
	HRESULT hr = CRegObject::SetKeyValue(keyName, valueName, value, re, FALSE);
	if (FAILED(hr))
		ReportToIError(re);
	return hr;
}

void CTRiASRegObject::ReportToIError(CRegException& rEx)
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
	Error(szDesc, IID_ITRiASRegistryHelper);
}
