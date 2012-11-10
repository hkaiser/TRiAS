// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.05.2001 10:54:50 
//
// @doc
// @module TRiASNativeAttribute.cpp | Definition of the <c CTRiASNativeAttribute> class

#include "StdAfx.h"
#include "TRiASNativeDB.h"

#include <NativeMerkmal.h>

#include "Wrapper.h"

#include "TRiASNativeObjects.h"
#include "TRiASNativeAttribute.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

using namespace trias_nativemerkmal;

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeAttribute

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeAttribute::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeAttribute::FinalRelease()
{
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

STDMETHODIMP CTRiASNativeAttribute::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASNativeAttribute ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASNativeAttribute

// Implementation of get_Name
STDMETHODIMP CTRiASNativeAttribute::get_Name(INT_PTR PrjHandle, INT_PTR lAttrib, BSTR *pbstrName)
{
	if (NULL == PrjHandle || NULL == lAttrib)
		return E_INVALIDARG;
	if (NULL == pbstrName)
		return E_POINTER;
	*pbstrName = NULL;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

char cbBuffer[_MAX_PATH];
HRESULT hr = Attrib.GetName(cbBuffer, sizeof(cbBuffer));

	if (SUCCEEDED(hr)) {
	CComBSTR bstrName(cbBuffer);

		*pbstrName = bstrName.Detach();
	}
	return hr;
}

// Implementation of put_Name
STDMETHODIMP CTRiASNativeAttribute::put_Name(INT_PTR PrjHandle, INT_PTR lAttrib, BSTR bstrName)
{
	if (NULL == PrjHandle || NULL == lAttrib || NULL == bstrName || 0 == SysStringLen(bstrName))
		return E_INVALIDARG;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

	USES_CONVERSION;
	return Attrib.SetName(OLE2A(bstrName));
}

// Implementation of get_Description
STDMETHODIMP CTRiASNativeAttribute::get_Description(INT_PTR PrjHandle, INT_PTR lAttrib, BSTR *pbstrDesc)
{
	if (NULL == PrjHandle || NULL == lAttrib)
		return E_INVALIDARG;
	if (NULL == pbstrDesc)
		return E_POINTER;
	*pbstrDesc = NULL;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

char cbBuffer[_MAX_PATH];
HRESULT hr = Attrib.GetDescription(cbBuffer, sizeof(cbBuffer));

	if (SUCCEEDED(hr)) {
	CComBSTR bstrDesc(cbBuffer);

		*pbstrDesc = bstrDesc.Detach();
	}
	return hr;
}

// Implementation of put_Description
STDMETHODIMP CTRiASNativeAttribute::put_Description(INT_PTR PrjHandle, INT_PTR lAttrib, BSTR bstrDesc)
{
	if (NULL == PrjHandle || NULL == lAttrib || NULL == bstrDesc || 0 == SysStringLen(bstrDesc))
		return E_INVALIDARG;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

	USES_CONVERSION;
	return Attrib.SetDescription(OLE2A(bstrDesc));
}

// Implementation of GetMetaData
STDMETHODIMP CTRiASNativeAttribute::GetMetaData(
	INT_PTR PrjHandle, INT_PTR lAttrib, BSTR *pbstrName, BSTR *pbstrDesc)
{
	if (NULL == PrjHandle || NULL == lAttrib)
		return E_INVALIDARG;
	if (NULL == pbstrDesc  || NULL == pbstrName)
		return E_POINTER;
	*pbstrName = NULL;
	*pbstrDesc = NULL;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

char cbBuffer[_MAX_PATH];
HRESULT hr = S_OK;

	hr = Attrib.GetName(cbBuffer, sizeof(cbBuffer));
	if (SUCCEEDED(hr)) {
	CComBSTR bstrName(cbBuffer);

		*pbstrName = bstrName.Detach();
	}
	hr = Attrib.GetDescription(cbBuffer, sizeof(cbBuffer));
	if (SUCCEEDED(hr)) {
	CComBSTR bstrDesc(cbBuffer);

		*pbstrDesc = bstrDesc.Detach();
	}
	return hr;
}

// Implementation of SetMetaData
STDMETHODIMP CTRiASNativeAttribute::SetMetaData(
	INT_PTR PrjHandle, INT_PTR lAttrib, BSTR bstrName, BSTR bstrDesc)
{
	if (NULL == PrjHandle || NULL == lAttrib)
		return E_INVALIDARG;

CNativeMerkmal Attrib (reinterpret_cast<HPROJECT>(PrjHandle), lAttrib);

	USES_CONVERSION;

	if (NULL != bstrName)
		RETURN_FAILED_HRESULT(Attrib.SetName(OLE2A(bstrName)));
	if (NULL != bstrDesc)
		RETURN_FAILED_HRESULT(Attrib.SetDescription(OLE2A(bstrDesc)));

	return S_OK;
}

// Implementation of get_Objects
STDMETHODIMP CTRiASNativeAttribute::get_Objects(
	INT_PTR hPrjHandle, INT_PTR lIdent, INT_PTR lAttrib, BSTR bstrStart, BSTR bstrEnd, 
	DBRANGEENUM rgRange, ITRiASEnumNativeObjects **ppVal)
{
	if (NULL == hPrjHandle || NULL == lAttrib)
		return E_INVALIDARG;
	if (NULL == ppVal)
		return E_POINTER;
	*ppVal = NULL;

	COM_TRY {
	// Enumerator erzeugen
	WTRiASEnumNativeObjects Enum;
	CComObject<CTRiASNativeObjectsVector> *pObjects = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASNativeObjectsVector>::CreateInstance(&pObjects));
		Enum = pObjects;		// bump RefCnt

	// Enumerator füllen
		THROW_FAILED_HRESULT(pObjects -> FInitFromAttrib(reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, lAttrib, bstrStart, bstrEnd, rgRange));

	// Enumerator liefern
		*ppVal = Enum.detach();

	} COM_CATCH;
	return S_OK;
}

