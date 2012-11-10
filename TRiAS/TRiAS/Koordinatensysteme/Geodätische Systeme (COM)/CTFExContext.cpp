// @doc
// @module CTFExContext.cpp | Implementation of CCTFExContext

#include "stdafx.h"

#include "GeodCtf_COM.h"
#include "Strings.h"

#include "CTFExContext.h"


/////////////////////////////////////////////////////////////////////////////
// CCTFExContext

STDMETHODIMP CCTFExContext::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICTFExContext,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCTFExContext::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

CString str;

	VERIFY(str.LoadString (IDS_EXCONTEXT_DESC));
	if (str.IsEmpty())
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CComBSTR bstr (str);

	if (!bstr)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CCTFExContext::get_Meridian(int * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = m_iMeridian;
	return S_OK;
}

STDMETHODIMP CCTFExContext::put_Meridian(int newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_iMeridian = newVal;
	return S_OK;
}
