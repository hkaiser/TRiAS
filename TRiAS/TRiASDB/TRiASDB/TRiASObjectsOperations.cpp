// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 11/16/1998 01:46:58 PM
//
// @doc
// @module TRiASObjectsOperations.cpp | Allgemeine Operationen über Objektmengen

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/EnumVariantIterators.h>

#include "TRiASDBGuids.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASObject.h"
#include "TRiASObjects.h"
#include "TRiASObjectsOperations.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASObjectsOperations, CTRiASObjectsOperations)

/////////////////////////////////////////////////////////////////////////////
// hier benötigte Datentypen
typedef __InEnumIterator<ITRiASObject, ITRiASObjects> InEnumObjs;
typedef __OutEnumIterator<ITRiASObject, ITRiASObjects> OutEnumObjs;

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsOperations

STDMETHODIMP CTRiASObjectsOperationsFunc::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASObjectsOperations,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// funktionales Interface

STDMETHODIMP CTRiASObjectsOperationsFunc::MakeNewObjects(
	IDispatch *pIParent, BSTR bstrName, BSTR bstrType, OBJECTSCOLLECTIONTYPE rgCollType, 
	ITRiASObjects **ppIObjsOut)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObjsOut) return E_POINTER;

HRESULT hr_result = S_OK;

	COM_TRY {
	CIID ClsId (bstrType, CIID::INITCIID_InitFromProgId);

		if (!ClsId) {
			ClsId = CLSID_TRiASObjects;		// Notanker
			hr_result = S_FALSE;
		}

	WTRiASObjects Item (ClsId);		// throws hr

		THROW_FAILED_HRESULT(WPersistStreamInit(Item) -> InitNew());
		THROW_FAILED_HRESULT(Item -> put_Parent(pIParent));

	WDispatch dispApp;
	
		_com_dispatch_propget(pIParent, DISPID_APPLICATION, VT_DISPATCH, dispApp.ppv());

		THROW_FAILED_HRESULT(Item -> put_Application(dispApp));
		THROW_FAILED_HRESULT(Item -> put_CollectionType(rgCollType));
		THROW_FAILED_HRESULT(Item -> put_Name(bstrName));
		*ppIObjsOut = Item.detach();

	} COM_CATCH;
	return hr_result;
}

STDMETHODIMP CTRiASObjectsOperationsFunc::Union(
	ITRiASObjects *pIObjs1, ITRiASObjects *pIObjs2, BSTR bstrName, BSTR bstrType,
	OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjsOut)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs1 || NULL == pIObjs2) return E_INVALIDARG;
	if (NULL == ppIObjsOut) return E_POINTER;

	COM_TRY {
	WTRiASObjects ObjsOut;
	WDispatch dispParent;

		_com_dispatch_propget(pIObjs1, DISPID_PARENT, VT_DISPATCH, dispParent.ppv());
		THROW_FAILED_HRESULT(MakeNewObjects (dispParent, bstrName, bstrType, rgType, ObjsOut.ppi()));
		set_union(InEnumObjs(pIObjs1), InEnumObjs(), 
				  InEnumObjs(pIObjs2), InEnumObjs(), 
				  OutEnumObjs(ObjsOut), less<WTRiASObject>());
		*ppIObjsOut = ObjsOut.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsOperationsFunc::Intersection(
	ITRiASObjects *pIObjs1, ITRiASObjects *pIObjs2, BSTR bstrName, BSTR bstrType,
	OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjsOut)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs1 || NULL == pIObjs2) return E_INVALIDARG;
	if (NULL == ppIObjsOut) return E_POINTER;

	COM_TRY {
	WTRiASObjects ObjsOut;
	WDispatch dispParent;

		_com_dispatch_propget(pIObjs1, DISPID_PARENT, VT_DISPATCH, dispParent.ppv());
		THROW_FAILED_HRESULT(MakeNewObjects (dispParent, bstrName, bstrType, rgType, ObjsOut.ppi()));
		set_intersection(InEnumObjs(pIObjs1), InEnumObjs(), 
						 InEnumObjs(pIObjs2), InEnumObjs(), 
						 OutEnumObjs(ObjsOut), less<WTRiASObject>());
		*ppIObjsOut = ObjsOut.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsOperationsFunc::Difference(
	ITRiASObjects *pIObjs1, ITRiASObjects *pIObjs2, BSTR bstrName, BSTR bstrType,
	OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjsOut)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs1 || NULL == pIObjs2) return E_INVALIDARG;
	if (NULL == ppIObjsOut) return E_POINTER;

	COM_TRY {
	WTRiASObjects ObjsOut;
	WDispatch dispParent;

		_com_dispatch_propget(pIObjs1, DISPID_PARENT, VT_DISPATCH, dispParent.ppv());
		THROW_FAILED_HRESULT(MakeNewObjects (dispParent, bstrName, bstrType, rgType, ObjsOut.ppi()));
		set_difference(InEnumObjs(pIObjs1), InEnumObjs(), 
					   InEnumObjs(pIObjs2), InEnumObjs(), 
					   OutEnumObjs(ObjsOut), less<WTRiASObject>());
		*ppIObjsOut = ObjsOut.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsOperationsFunc::SymmetricDifference(
	ITRiASObjects *pIObjs1, ITRiASObjects *pIObjs2, BSTR bstrName, BSTR bstrType,
	OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjsOut)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs1 || NULL == pIObjs2) return E_INVALIDARG;
	if (NULL == ppIObjsOut) return E_POINTER;

	COM_TRY {
	WTRiASObjects ObjsOut;
	WDispatch dispParent;

		_com_dispatch_propget(pIObjs1, DISPID_PARENT, VT_DISPATCH, dispParent.ppv());
		THROW_FAILED_HRESULT(MakeNewObjects (dispParent, bstrName, bstrType, rgType, ObjsOut.ppi()));
		set_symmetric_difference(InEnumObjs(pIObjs1), InEnumObjs(), 
								 InEnumObjs(pIObjs2), InEnumObjs(), 
								 OutEnumObjs(ObjsOut), less<WTRiASObject>());
		*ppIObjsOut = ObjsOut.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASObjectsOperationsFunc::Includes(
	ITRiASObjects *pIObjs1, ITRiASObjects *pIObjs2, VARIANT_BOOL *pfIncludes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs1 || NULL == pIObjs2) return E_INVALIDARG;
	if (NULL == pfIncludes) return E_POINTER;

	COM_TRY {
		*pfIncludes = includes(InEnumObjs(pIObjs1), InEnumObjs(), 
							   InEnumObjs(pIObjs2), InEnumObjs(),
							   less<WTRiASObject>()) ? VARIANT_TRUE : VARIANT_FALSE;
	} COM_CATCH;
	return S_OK;
}
