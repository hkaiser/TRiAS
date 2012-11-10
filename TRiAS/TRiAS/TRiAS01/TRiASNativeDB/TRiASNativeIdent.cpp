// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 11:50:59 
//
// @doc
// @module TRiASNativeIdent.cpp | Definition of the <c CTRiASNativeIdent> class

#include "StdAfx.h"
#include "TRiASNativeDB.h"

#include <NativeIdent.h>
#include <NativeMerkmal.h>
#include <DBMsg.hmc>

#include "Strings.h"
#include "Util.h"
#include "Wrapper.h"

#include "TRiASNativeIdent.h"
#include "TRiASNativeObjects.h"
#include "TRiASNativeAttributes.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

using namespace trias_nativeident;
using namespace trias_nativemerkmal;

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeIdent

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeIdent::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeIdent::FinalRelease()
{

}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CTRiASNativeIdent::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASNativeIdent ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASNativeIdent

// Implementation of get_Name
STDMETHODIMP CTRiASNativeIdent::get_Name(INT_PTR PrjHandle, INT_PTR lIdent, BSTR *pbstrName)
{
	if (NULL == PrjHandle || NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pbstrName)
		return E_POINTER;
	*pbstrName = NULL;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

char cbBuffer[_MAX_PATH];
HRESULT hr = Ident.GetName(cbBuffer, sizeof(cbBuffer));

	if (SUCCEEDED(hr)) {
	CComBSTR bstrName(cbBuffer);

		*pbstrName = bstrName.Detach();
	}
	return hr;
}

// Implementation of put_Name
STDMETHODIMP CTRiASNativeIdent::put_Name(INT_PTR PrjHandle, INT_PTR lIdent, BSTR bstrName)
{
	if (NULL == PrjHandle || NULL == lIdent || NULL == bstrName || 0 == SysStringLen(bstrName))
		return E_INVALIDARG;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Ident.SetName(OLE2A(bstrName));
}

// Implementation of get_OKS
STDMETHODIMP CTRiASNativeIdent::get_OKS(INT_PTR PrjHandle, INT_PTR lIdent, BSTR *pbstrOKS)
{
	if (NULL == PrjHandle || NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pbstrOKS)
		return E_POINTER;
	*pbstrOKS = NULL;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

char cbBuffer[_MAX_PATH];
HRESULT hr = Ident.GetOKS(cbBuffer, sizeof(cbBuffer));

	if (SUCCEEDED(hr)) {
	CComBSTR bstrOKS(cbBuffer);

		*pbstrOKS = bstrOKS.Detach();
	}
	return hr;
}

// Implementation of put_OKS
STDMETHODIMP CTRiASNativeIdent::put_OKS(INT_PTR PrjHandle, INT_PTR lIdent, BSTR bstrOKS)
{
	if (NULL == PrjHandle || NULL == lIdent || NULL == bstrOKS || 0 == SysStringLen(bstrOKS))
		return E_INVALIDARG;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Ident.SetOKS(OLE2A(bstrOKS));
}

// Implementation of get_Description
STDMETHODIMP CTRiASNativeIdent::get_Description(INT_PTR PrjHandle, INT_PTR lIdent, BSTR *pbstrDesc)
{
	if (NULL == PrjHandle || NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pbstrDesc)
		return E_POINTER;
	*pbstrDesc = NULL;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

char cbBuffer[_MAX_PATH];
HRESULT hr = Ident.GetDescription(cbBuffer, sizeof(cbBuffer));

	if (SUCCEEDED(hr)) {
	CComBSTR bstrDesc(cbBuffer);

		*pbstrDesc = bstrDesc.Detach();
	}
	return hr;
}

// Implementation of put_Description
STDMETHODIMP CTRiASNativeIdent::put_Description(INT_PTR PrjHandle, INT_PTR lIdent, BSTR bstrDesc)
{
	if (NULL == PrjHandle || NULL == lIdent || NULL == bstrDesc || 0 == SysStringLen(bstrDesc))
		return E_INVALIDARG;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Ident.SetDescription(OLE2A(bstrDesc));
}

// Implementation of GetMetaData
STDMETHODIMP CTRiASNativeIdent::GetMetaData(
	INT_PTR PrjHandle, INT_PTR lIdent, BSTR *pbstrName, BSTR *pbstrDesc, BSTR *pbstrOKS)
{
	if (NULL == PrjHandle || NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pbstrDesc || NULL == pbstrOKS || NULL == pbstrName)
		return E_POINTER;
	*pbstrOKS = NULL;
	*pbstrName = NULL;
	*pbstrDesc = NULL;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

char cbBuffer[_MAX_PATH];
HRESULT hr = S_OK;

	hr = Ident.GetOKS(cbBuffer, sizeof(cbBuffer));
	if (SUCCEEDED(hr)) {
	CComBSTR bstrOKS(cbBuffer);

		*pbstrOKS = bstrOKS.Detach();
	}
	hr = Ident.GetName(cbBuffer, sizeof(cbBuffer));
	if (SUCCEEDED(hr)) {
	CComBSTR bstrName(cbBuffer);

		*pbstrName = bstrName.Detach();
	}
	hr = Ident.GetDescription(cbBuffer, sizeof(cbBuffer));
	if (SUCCEEDED(hr)) {
	CComBSTR bstrDesc(cbBuffer);

		*pbstrDesc = bstrDesc.Detach();
	}
	return hr;
}

// Implementation of SetMetaData
STDMETHODIMP CTRiASNativeIdent::SetMetaData(
	INT_PTR PrjHandle, INT_PTR lIdent, BSTR bstrName, BSTR bstrDesc, BSTR bstrOKS)
{
	if (NULL == PrjHandle || NULL == lIdent)
		return E_INVALIDARG;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(PrjHandle), lIdent);

	if (!Ident)
		return E_INVALIDARG;

	USES_CONVERSION;

	if (NULL != bstrOKS)
		RETURN_FAILED_HRESULT(Ident.SetOKS(OLE2A(bstrOKS)));
	if (NULL != bstrName)
		RETURN_FAILED_HRESULT(Ident.SetName(OLE2A(bstrName)));
	if (NULL != bstrDesc)
		RETURN_FAILED_HRESULT(Ident.SetDescription(OLE2A(bstrDesc)));

	return S_OK;
}

// Liefert alle einer Objektklasse zugeordneten Objekteigenschaften
STDMETHODIMP CTRiASNativeIdent::get_Attributes(
	INT_PTR hPr, INT_PTR lIdent, ITRiASEnumNativeAttributes **ppVal)
{
	if (NULL == hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == ppVal)
		return E_POINTER;
	*ppVal = NULL;

	COM_TRY {
	// Enumerator erzeugen
	CComObject<CTRiASNativeAttributes> *pAttribs = NULL;
	WTRiASEnumNativeAttributes Enum;

		THROW_FAILED_HRESULT(CComObject<CTRiASNativeAttributes>::CreateInstance(&pAttribs));
		Enum = pAttribs;		// bump RefCnt

	// Enumerator füllen
		THROW_FAILED_HRESULT(pAttribs -> FInit(reinterpret_cast<HPROJECT>(hPr), lIdent));

	// Enumerator liefern
		*ppVal = Enum.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASNativeIdent::GetAttribute(
	INT_PTR hPrjHandle, INT_PTR lIdent, BSTR bstrName, VARIANT_BOOL fCaseSensitive, INT_PTR *plMCode)
{
	USES_CONVERSION;
	return CNativeMerkmal::FindFromName(reinterpret_cast<HPROJECT>(hPrjHandle), OLE2A(bstrName), lIdent, fCaseSensitive, plMCode);
}

STDMETHODIMP CTRiASNativeIdent::PutAttribute(
	INT_PTR hPrjHandle, INT_PTR lIdent, BSTR bstrName, INT_PTR *plMCode)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == plMCode)
		return E_POINTER;
	*plMCode = NULL;

// ggf. Attribut wiederfinden
	USES_CONVERSION;

LPCSTR pcName = OLE2A(bstrName);
INT_PTR lMCode = 0;
HRESULT hr = CNativeMerkmal::FindFromName(reinterpret_cast<HPROJECT>(hPrjHandle), pcName, lIdent, VARIANT_TRUE, &lMCode);

	if (FAILED(hr)) {
	// neu erzeugen
	CNativeMerkmal Attrib(reinterpret_cast<HPROJECT>(hPrjHandle), lMCode, TRUE);

		if (!Attrib)
			return E_UNEXPECTED;
		RETURN_FAILED_HRESULT(Attrib.SetName(pcName));
	}
	*plMCode = lMCode;
	return S_OK;
}

// Implementation of DestroyAttribute
STDMETHODIMP CTRiASNativeIdent::DestroyAttribute(INT_PTR hPrjHandle, INT_PTR lIdent, BSTR bstrName)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;

// ggf. Attribut wiederfinden
INT_PTR lMCode = 0;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CNativeMerkmal::FindFromName(reinterpret_cast<HPROJECT>(hPrjHandle), OLE2A(bstrName), lIdent, VARIANT_TRUE, &lMCode));

CNativeMerkmal Attrib(reinterpret_cast<HPROJECT>(hPrjHandle), lMCode);

	if (!Attrib)
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(Attrib.Delete(true));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Objekte dieser Objektklasse
STDMETHODIMP CTRiASNativeIdent::get_Objects(
	INT_PTR hPrjHandle, INT_PTR lIdent, DWORD dwTypes, ITRiASExpression *pIExpr,
	ITRiASEnumNativeObjects **ppVal)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == ppVal)
		return E_POINTER;
	*ppVal = NULL;

	COM_TRY {
	// Enumerator erzeugen
	WTRiASEnumNativeObjects Enum;

		if (dwTypes & COLLECTIONTYPE_SortedONr) {
			if (dwTypes & COLLECTIONTYPE_Descending) {
			CComObject<CTRiASNativeObjectsSetDesc> *pObjects = NULL;

				THROW_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSetDesc>::CreateInstance(&pObjects));
				Enum = pObjects;		// bump RefCnt

			// Enumerator füllen
				THROW_FAILED_HRESULT(pObjects -> FInitFromClass(reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, dwTypes & ~COLLECTIONTYPE_Mask, pIExpr));
			}
			else {
			CComObject<CTRiASNativeObjectsSet> *pObjects = NULL;

				THROW_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSet>::CreateInstance(&pObjects));
				Enum = pObjects;		// bump RefCnt

			// Enumerator füllen
				THROW_FAILED_HRESULT(pObjects -> FInitFromClass(reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, dwTypes & ~COLLECTIONTYPE_Mask, pIExpr));
			}
		} 
		else if (dwTypes & COLLECTIONTYPE_SortedGuid) {
		CComObject<CTRiASNativeObjectsVector> *pObjects = NULL;

			THROW_FAILED_HRESULT(CComObject<CTRiASNativeObjectsVector>::CreateInstance(&pObjects));
			Enum = pObjects;		// bump RefCnt

		// Enumerator füllen
			THROW_FAILED_HRESULT(pObjects -> FInitFromGuid(reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, dwTypes & ~COLLECTIONTYPE_Mask, pIExpr));
		} 
		else {
			_ASSERTE((dwTypes & COLLECTIONTYPE_Mask) == COLLECTIONTYPE_NotSorted);

		CComObject<CTRiASNativeObjectsVector> *pObjects = NULL;

			THROW_FAILED_HRESULT(CComObject<CTRiASNativeObjectsVector>::CreateInstance(&pObjects));
			Enum = pObjects;		// bump RefCnt

		// Enumerator füllen
			THROW_FAILED_HRESULT(pObjects -> FInitFromClass(reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, dwTypes & ~COLLECTIONTYPE_Mask, pIExpr));
		}

	// Enumerator liefern
		*ppVal = Enum.detach();

	} COM_CATCH;
	return S_OK;
}

// Implementation of get_Types
STDMETHODIMP CTRiASNativeIdent::get_Types(INT_PTR hPrjHandle, INT_PTR lIdent, DWORD *pdwTypes)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pdwTypes)
		return E_POINTER;
	*pdwTypes = 0;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	if (!Ident)
		return E_INVALIDARG;

	return Ident.GetObjectTypesAndCounts(CNativeIdent::LOOKUPSPEED_INFINITE, *pdwTypes);
}


// Implementation of get_Counts
STDMETHODIMP CTRiASNativeIdent::get_Counts(
	INT_PTR hPrjHandle, INT_PTR lIdent, 
	DWORD *pdwPoints, DWORD *pdwLines, DWORD *pdwAreas, DWORD *pdwTexts, DWORD *pdwCounts)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pdwPoints || NULL == pdwLines || NULL == pdwAreas || NULL == pdwTexts || NULL == pdwCounts)
		return E_POINTER;
	*pdwPoints = 0;
	*pdwLines = 0;
	*pdwAreas = 0;
	*pdwTexts = 0;
	*pdwCounts = 0;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	if (!Ident)
		return E_INVALIDARG;

long lCounts[4];
DWORD dwTypes = 0;

	memset (lCounts, 0, _countof(lCounts)*sizeof(long));

HRESULT hr = Ident.GetObjectTypesAndCounts(CNativeIdent::LOOKUPSPEED_INFINITE, dwTypes, lCounts);

	if (FAILED(hr)) return hr;

	*pdwPoints = lCounts[0];
	*pdwLines = lCounts[1];
	*pdwAreas = lCounts[2];
	*pdwTexts = lCounts[3];
	*pdwCounts = lCounts[0] + lCounts[1] + lCounts[2] + lCounts[3];
	return S_OK;
}

// Implementation of get_CreationDate
STDMETHODIMP CTRiASNativeIdent::get_CreationDate(INT_PTR hPrjHandle, INT_PTR lIdent, DATE *pdCreationDate)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pdCreationDate)
		return E_POINTER;
	*pdCreationDate = 0;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	if (!Ident)
		return E_INVALIDARG;

	return Ident.GetCreationDate(pdCreationDate);
}

// Implementation of get_ModificationDate
STDMETHODIMP CTRiASNativeIdent::get_ModificationDate(INT_PTR hPrjHandle, INT_PTR lIdent, DATE *pdModificationDate)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pdModificationDate)
		return E_POINTER;
	*pdModificationDate = 0;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	if (!Ident)
		return E_INVALIDARG;

	return Ident.GetModificationDate(pdModificationDate);
}

// Implementation of get_Guid
STDMETHODIMP CTRiASNativeIdent::get_Guid(INT_PTR hPrjHandle, INT_PTR lIdent, GUID *pGuid)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == lIdent)
		return E_INVALIDARG;
	if (NULL == pGuid)
		return E_POINTER;
	*pGuid = GUID_NULL;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	if (!Ident)
		return E_INVALIDARG;

	return Ident.GetIdentGUID((_GUID *)pGuid);
}

