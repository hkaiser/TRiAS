// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 21:11:20 
//
// @doc
// @module IGetAsOLEDBRowsetImpl.h | Declaration of the <c IGetAsOLEDBRowsetImpl> class

#if !defined(_IGETASOLEDBROWSETIMPL_H__DABE8DB6_9DE6_40C6_918E_B2F86F1FA0BA__INCLUDED_)
#define _IGETASOLEDBROWSETIMPL_H__DABE8DB6_9DE6_40C6_918E_B2F86F1FA0BA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include <idl/IGetAsOLEDBRowset.h>

template <class T>
class ATL_NO_VTABLE IGetAsOLEDBRowsetImpl : 
	public _IGetAsOLEDBRowset
{
public:
	STDMETHOD(GetAsRowset)(
		IUnknown *pUnkCreator, IUnknown *pUnkOuter, REFIID riid, LONG *pcRowsAffected, IUnknown **ppRowset)
	{
		if (!ppRowset || !pcRowsAffected)
			return E_POINTER;

		*ppRowset = 0;
		*pcRowsAffected = 0;

	T *pT = (T *)this;

		return pT -> AsRowset(pUnkCreator, pUnkOuter, riid, pcRowsAffected, ppRowset);
	}

// The following function can be called by the object that implements AsRowset() to
// create a "standard" rowset object of its choice, it handles all the crap that 
// needs to be done to get the rowset object created and wired up to the rest of
// the provider properly.
	template <class RowsetClass> 
	HRESULT CreateRowset(IUnknown *pUnkCreator, IUnknown *pUnkOuter, REFIID riid, 
		IUnknown **ppRowset, RowsetClass *& pRowsetObj)
	{
		if (ppRowset != NULL)
			*ppRowset = NULL;

		if ((pUnkOuter != NULL) && !InlineIsEqualUnknown(riid))
			return DB_E_NOAGGREGATION;

	CComPolyObject<RowsetClass> * pPolyObj = NULL;
	HRESULT hr = CComPolyObject<RowsetClass>::CreateInstance(pUnkOuter, &pPolyObj);

		if (FAILED(hr)) return hr;
		
	// Ref the created COM object and Auto release it on failure
	CComPtr<IUnknown> spUnk;
		
		hr = pPolyObj -> QueryInterface(&spUnk);
		if (FAILED(hr)) {
			delete pPolyObj; // must hand delete as it is not ref'd
			return hr;
		}
		
	// Get a pointer to the Rowset instance
		pRowsetObj = &(pPolyObj->m_contained);


	// Rowsets have their properties initialised from their creators.
	// Unfortunately we can't do that as our creator object could be in a different
	// appartment.
	// Instead we call FInit with a new copy of our creator class, which will get 
	// our rowset's property map set up correctly. We then call get properties on
	// the COM interface to our creator and set the properties in ourself...
	// Long winded, but it should work...
	CComObject<RowsetClass::_RowsetCreatorClass> dummy; 
		
		dummy.InternalAddRef();  // bump ref count to 1
		dummy.FinalConstruct();

		if (FAILED(hr = pRowsetObj->FInit(&dummy)))
			return hr;

	CComQIPtr<ICommandProperties> spCommandProps(pUnkCreator);

	// what if our creator isn't a command?
		if (spCommandProps)	{
		ULONG cPropSets = 0;
		DBPROPSET *pPropSets = 0;
		 
		// Passing 0 as the first argument means give us all properties...
			hr = spCommandProps->GetProperties(0, 0, &cPropSets, &pPropSets);

			if (SUCCEEDED(hr)) {
			const GUID* ppGuid[1];
			
				ppGuid[0] = &DBPROPSET_ROWSET;

			// Call SetProperties.	The true in the last parameter indicates
			// the special behavior that takes place on rowset creation (i.e.
			// it succeeds as long as any of the properties were not marked
			// as DBPROPS_REQUIRED.

				hr = pRowsetObj->SetProperties(0, cPropSets, pPropSets, 1, ppGuid, true);
				ReleasePropertyStructures(cPropSets, pPropSets);	// do a recursive free on all of the data in the pPropSets structure
			}
		}
		else {
			ATLTRACE2(atlTraceDBProvider, 0, "IGetAsOLEDBRowsetImpl::CreateRowset - pUnkCreator isn't a command\n");
		}
	
		if (FAILED(hr))
			return hr;

		pRowsetObj->SetSite(pUnkCreator);
		if (InlineIsEqualGUID(riid, IID_NULL) || ppRowset == NULL) {
			if (ppRowset != NULL)
				*ppRowset = NULL;
			return hr;
		}

		hr = pPolyObj->QueryInterface(riid, (void**)ppRowset);

	// Note: We don't bother to copy the bindings from the command to the rowset. This is
	// against the rules of OLE DB which say that if you set up bindings in the command
	// then they're available in the rowset. We never do that, so it shouldn't matter. 
	// It's a problem for us to copy the bindings as we cant just to the memory copy that
	// the standard templates do as our rowsets and commands are potentially in different
	// appartments...

	// This is the code from the standard templates that does the binding copy, we'd need
	// to concoct some COM way of doing this if we wanted to do it...
	/*
		for (iBind = 0; iBind < pT->m_rgBindings.GetSize(); iBind++) {
			T::_BindType* pBind = NULL;
			T::_BindType* pBindSrc = NULL;
			ATLTRY(pBind = new T::_BindType);
			if (pBind == NULL)
			{
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to allocate memory for new Binding\n");
				return E_OUTOFMEMORY;
			}
			// auto cleanup on failure
			CAutoMemRelease<T::_BindType> amr(pBind);
			pBindSrc = pT->m_rgBindings.GetValueAt(iBind);
			if (pBindSrc == NULL)
			{
				ATLTRACE2(atlTraceDBProvider, 0, "The map appears to be corrupted, failing!!\n");
				return E_FAIL;
			}
			if (!pRowsetObj->m_rgBindings.Add(pT->m_rgBindings.GetKeyAt(iBind), pBind))
			{
				ATLTRACE2(atlTraceDBProvider, 0, "Failed to add hAccessor to Map\n");
				return E_OUTOFMEMORY;
			}
			if (pBindSrc->cBindings)
			{
				ATLTRY(pBind->pBindings = new DBBINDING[pBindSrc->cBindings])
				if (pBind->pBindings == NULL)
				{
					ATLTRACE2(atlTraceDBProvider, 0, "Failed to Allocate dbbinding Array\n");
					// We added it, must now remove on failure
					pRowsetObj->m_rgBindings.Remove(pT->m_rgBindings.GetKeyAt(iBind));
					return E_OUTOFMEMORY;
				}
			}
			else
			{
				pBind->pBindings = NULL; // NULL Accessor
			}

			pBind->dwAccessorFlags = pBindSrc->dwAccessorFlags;
			pBind->cBindings = pBindSrc->cBindings;
			pBind->dwRef = 1;
			memcpy(pBind->pBindings, pBindSrc->pBindings, (pBindSrc->cBindings)*sizeof(DBBINDING));
			pBind = amr.Detach();
		}
	*/
		return hr;
	}

private: 
	void ReleasePropertyStructures(ULONG cPropSets, DBPROPSET* pPropSets)
	{
	DBPROPSET *pPropSet = pPropSets;

		for (size_t setIndex = 0; setIndex < cPropSets; setIndex++) {
			if (pPropSet) {
				CoTaskMemFree(pPropSet->rgProperties);
			
			DBPROPSET *pLastSet = pPropSet;

				pPropSet++;
				CoTaskMemFree(pLastSet);
			}			 
		}
	}
};

#endif // !defined(_IGETASOLEDBROWSETIMPL_H__DABE8DB6_9DE6_40C6_918E_B2F86F1FA0BA__INCLUDED_)
