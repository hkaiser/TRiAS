// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 19:45:15 
//
// @doc
// @module TRiASNativeObjectsOperations.cpp | Definition of the <c CTRiASNativeObjectsOperations> class

#include "StdAfx.h"
#include "TRiASNativeDB.h"

#include <Com/ComBool.h>

#include "TRiASNativeObjects.h"
#include "TRiASNativeObjectsOperations.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeObjectsOperations

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CTRiASNativeObjectsOperations::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASNativeObjectsOperations ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Initialisation

// FinalConstruct implementation
HRESULT CTRiASNativeObjectsOperations::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

// FinalRelease implementation
void CTRiASNativeObjectsOperations::FinalRelease()
{

}

/////////////////////////////////////////////////////////////////////////////
// ITRiASNativeObjectsOperations

// Implementation of Union
STDMETHODIMP CTRiASNativeObjectsOperations::Union(
	ITRiASEnumNativeObjects *pIObjs1, ITRiASEnumNativeObjects *pIObjs2, ITRiASEnumNativeObjects **ppIObjsOut)
{
	if (NULL == pIObjs1 || NULL == pIObjs2)
		return E_INVALIDARG;
	if (NULL == ppIObjsOut)
		return E_POINTER;
	*ppIObjsOut = NULL;

// die Collections selbst besorgen
CTRiASNativeObjectsSet *pObjs1 = NULL, *pObjs2 = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs1, &pObjs1));
	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs2, &pObjs2));

// neue collection erzeugen
CComObject<CTRiASNativeObjectsSet> *pObjsOut = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSet>::CreateInstance(&pObjsOut));

CComPtr<ITRiASEnumNativeObjects> ObjsOut(pObjsOut);		// bump refcnt

	ATLTRY(set_union(pObjs1 -> m_coll.begin(), pObjs1 -> m_coll.end(), 
					 pObjs2 -> m_coll.begin(), pObjs2 -> m_coll.end(), 
					 inserter(pObjsOut->m_coll, pObjsOut -> m_coll.end()), less<INT_PTR>()));

	*ppIObjsOut = ObjsOut.Detach();
	return S_OK;
}

// Implementation of Intersection
STDMETHODIMP CTRiASNativeObjectsOperations::Intersection(
	ITRiASEnumNativeObjects *pIObjs1, ITRiASEnumNativeObjects *pIObjs2, ITRiASEnumNativeObjects **ppIObjsOut)
{
	if (NULL == pIObjs1 || NULL == pIObjs2)
		return E_INVALIDARG;
	if (NULL == ppIObjsOut)
		return E_POINTER;
	*ppIObjsOut = NULL;

// die Collections selbst besorgen
CTRiASNativeObjectsSet *pObjs1 = NULL, *pObjs2 = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs1, &pObjs1));
	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs2, &pObjs2));

// neue collection erzeugen
CComObject<CTRiASNativeObjectsSet> *pObjsOut = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSet>::CreateInstance(&pObjsOut));

CComPtr<ITRiASEnumNativeObjects> ObjsOut(pObjsOut);		// bump refcnt

	ATLTRY(set_intersection(pObjs1 -> m_coll.begin(), pObjs1 -> m_coll.end(), 
					pObjs2 -> m_coll.begin(), pObjs2 -> m_coll.end(), 
					inserter(pObjsOut->m_coll, pObjsOut -> m_coll.end()), less<INT_PTR>()));

	*ppIObjsOut = ObjsOut.Detach();
	return S_OK;
}

// Implementation of Difference
STDMETHODIMP CTRiASNativeObjectsOperations::Difference(
	ITRiASEnumNativeObjects *pIObjs1, ITRiASEnumNativeObjects *pIObjs2, ITRiASEnumNativeObjects **ppIObjsOut)
{
	if (NULL == pIObjs1 || NULL == pIObjs2)
		return E_INVALIDARG;
	if (NULL == ppIObjsOut)
		return E_POINTER;
	*ppIObjsOut = NULL;

// die Collections selbst besorgen
CTRiASNativeObjectsSet *pObjs1 = NULL, *pObjs2 = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs1, &pObjs1));
	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs2, &pObjs2));

// neue collection erzeugen
CComObject<CTRiASNativeObjectsSet> *pObjsOut = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSet>::CreateInstance(&pObjsOut));

CComPtr<ITRiASEnumNativeObjects> ObjsOut(pObjsOut);		// bump refcnt

	ATLTRY(set_difference(pObjs1 -> m_coll.begin(), pObjs1 -> m_coll.end(), 
					pObjs2 -> m_coll.begin(), pObjs2 -> m_coll.end(), 
					inserter(pObjsOut->m_coll, pObjsOut -> m_coll.end()), less<INT_PTR>()));

	*ppIObjsOut = ObjsOut.Detach();
	return S_OK;
}

// Implementation of SymmetricDifference
STDMETHODIMP CTRiASNativeObjectsOperations::SymmetricDifference(
	ITRiASEnumNativeObjects *pIObjs1, ITRiASEnumNativeObjects *pIObjs2, ITRiASEnumNativeObjects **ppIObjsOut)
{
	if (NULL == pIObjs1 || NULL == pIObjs2)
		return E_INVALIDARG;
	if (NULL == ppIObjsOut)
		return E_POINTER;
	*ppIObjsOut = NULL;

// die Collections selbst besorgen
CTRiASNativeObjectsSet *pObjs1 = NULL, *pObjs2 = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs1, &pObjs1));
	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs2, &pObjs2));

// neue collection erzeugen
CComObject<CTRiASNativeObjectsSet> *pObjsOut = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASNativeObjectsSet>::CreateInstance(&pObjsOut));

CComPtr<ITRiASEnumNativeObjects> ObjsOut(pObjsOut);		// bump refcnt

	ATLTRY(set_symmetric_difference(pObjs1 -> m_coll.begin(), pObjs1 -> m_coll.end(), 
					pObjs2 -> m_coll.begin(), pObjs2 -> m_coll.end(), 
					inserter(pObjsOut->m_coll, pObjsOut -> m_coll.end()), less<INT_PTR>()));

	*ppIObjsOut = ObjsOut.Detach();
	return S_OK;
}

// Implementation of Includes
STDMETHODIMP CTRiASNativeObjectsOperations::Includes(
	ITRiASEnumNativeObjects *pIObjs1, ITRiASEnumNativeObjects *pIObjs2, VARIANT_BOOL *pfIncludes)
{
	if (NULL == pIObjs1 || NULL == pIObjs2)
		return E_INVALIDARG;
	if (NULL == pfIncludes) 
		return E_POINTER;
	*pfIncludes = VARIANT_FALSE;

// die Collections selbst besorgen
CTRiASNativeObjectsSet *pObjs1 = NULL, *pObjs2 = NULL;

	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs1, &pObjs1));
	RETURN_FAILED_HRESULT(QueryImplementation(pIObjs2, &pObjs2));

CComBool fIncludes;

	ATLTRY(fIncludes = includes(
				pObjs1 -> m_coll.begin(), pObjs1 -> m_coll.end(), 
				pObjs2 -> m_coll.begin(), pObjs2 -> m_coll.end(), less<INT_PTR>()));

	*pfIncludes = fIncludes;
	return S_OK;
}

