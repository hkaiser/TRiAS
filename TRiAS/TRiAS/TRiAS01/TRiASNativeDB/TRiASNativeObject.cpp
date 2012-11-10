// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:57:40 
//
// @doc
// @module TRiASNativeObject.cpp | Definition of the <c CTRiASNativeObject> class

#include "StdAfx.h"
#include "TRiASNativeDB.h"

#include <Atl/Ciid.h>

#include <NativeObject.h>
#include <NativeIdent.h>

#include "TRiASNativeObject.h"

using namespace trias_nativeobject;

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeObject

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CTRiASNativeObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASNativeObject ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeObject::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeObject::FinalRelease()
{
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASNativeObject

// Implementation of get_Guid
STDMETHODIMP CTRiASNativeObject::get_Guid(INT_PTR hPrjHandle, INT_PTR lONr, BSTR *pbstrGuid)
{
	if (NULL == pbstrGuid)
		return E_POINTER;
	*pbstrGuid = NULL;

CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

CIID Guid;

	RETURN_FAILED_HRESULT(Obj.GetObjectGUID(&Guid));
	*pbstrGuid = CComBSTR(Guid).Detach();
	return S_OK;
}

// Implementation of put_Guid
STDMETHODIMP CTRiASNativeObject::put_Guid(INT_PTR hPrjHandle, INT_PTR lONr, BSTR bstrGuid)
{
	if (NULL == bstrGuid)
		return E_INVALIDARG;		// Guid kann nicht gelöscht werden

CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

CIID Guid (bstrGuid, CIID::INITCIID_InitFromGuid);

	return Obj.SetObjectGUID(Guid);
}

// Implementation of get_Attribute
STDMETHODIMP CTRiASNativeObject::get_Attribute(
	INT_PTR hPrjHandle, INT_PTR lONr, INT_PTR hAttrib, BSTR *pbstrAttrVal)
{
	if (NULL == pbstrAttrVal)
		return E_POINTER;
	*pbstrAttrVal = NULL;

CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

	return Obj.GetTextMerkmal(hAttrib, pbstrAttrVal);
}

// Implementation of put_Attribute
STDMETHODIMP CTRiASNativeObject::put_Attribute(
	INT_PTR hPrjHandle, INT_PTR lONr, INT_PTR hAttrib, BSTR bstrAttrVal)
{
CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

	return Obj.PutTextMerkmal(hAttrib, bstrAttrVal);
}

// Implementation of GetGeometry
STDMETHODIMP CTRiASNativeObject::GetGeometry(
	INT_PTR hPrjHandle, INT_PTR lONr, BSTR bstrGeomName, SAFEARRAY **ppGeom)
{
	if (NULL == ppGeom)
		return E_POINTER;
	*ppGeom = NULL;

CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Obj.GetGeometry(OLE2A(bstrGeomName), ppGeom);
}

// Implementation of PutGeometry
STDMETHODIMP CTRiASNativeObject::PutGeometry(
	INT_PTR hPrjHandle, INT_PTR lONr, DWORD dwType, BSTR bstrGeomName, SAFEARRAY *pGeom)
{
CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Obj.PutGeometry(NULL, dwType, OLE2A(bstrGeomName), pGeom);
}


// Implementation of GetGeometryWKT
STDMETHODIMP CTRiASNativeObject::GetGeometryWKT(
	INT_PTR hPrjHandle, INT_PTR lONr, BSTR bstrGeomName, BSTR *pbstrGeomWKT)
{
	if (NULL == pbstrGeomWKT)
		return E_POINTER;
	*pbstrGeomWKT = NULL;

CNativeObject Obj (reinterpret_cast<HPROJECT>(hPrjHandle), lONr);

	if (!Obj)
		return E_INVALIDARG;

	USES_CONVERSION;
	return Obj.GetGeometryWKT(OLE2A(bstrGeomName), pbstrGeomWKT);
}

// Implementation of PutGeometryWKT
STDMETHODIMP CTRiASNativeObject::PutGeometryWKT(INT_PTR PrjHandle, INT_PTR Obj, DWORD ObjType, BSTR GeomName, BSTR GeomWKT)
{
	return E_NOTIMPL;
}

