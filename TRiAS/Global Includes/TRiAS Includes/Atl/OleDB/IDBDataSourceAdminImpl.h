// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.06.2001 16:47:32 
//
// @doc
// @module IDBDataSourceAdminImpl.h | Declaration of the <c CIDBDataSourceAdminImpl> class

#if !defined(_IDBDATASOURCEADMINIMPL_H__84D668C2_E837_4912_9018_1ECB725FA7D4__INCLUDED_)
#define _IDBDATASOURCEADMINIMPL_H__84D668C2_E837_4912_9018_1ECB725FA7D4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// IDBDataSourceAdmin
template<
	typename T, 
	const GUID *pInitPropSetGuid = &DBPROPSET_DBINIT,
	const GUID *pCreatePropSetGuid = &GUID_NULL
>
class ATL_NO_VTABLE IDBDataSourceAdminImpl :
	public IDBDataSourceAdmin
{
public:
	STDMETHODIMP CreateDataSource(ULONG cPropertySets, DBPROPSET rgPropertySets[],
            IUnknown *pUnkOuter, REFIID riid, IUnknown **ppDBSession)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::CreateDataSource\n");

	T *pT = static_cast<T *>(this);
	HRESULT hr;

		if (pT->m_dwStatus & DSF_INITIALIZED)
			return DB_E_ALREADYINITIALIZED;

	// properties setzen (if applicable)
		if (cPropertySets != 0) {
		DBPROPSET* pdbPropSet = NULL;

			hr = pT->CUtlProps<T>::SetPropertiesArgChk(cPropertySets, rgPropertySets);
			if(FAILED(hr)) return hr;

		// Note that m_pCUtlProps knows about initialization, so we don't have to here.
		const GUID **ppGuid = NULL;
		const GUID *pGroup[1];
		int iCnt = 1;
	
			pGroup[0] = &DBPROPSET_DBINITALL;
			if (!InlineIsEqualGUID(*pInitPropSetGuid, DBPROPSET_DBINIT))
				pGroup[iCnt++] = pInitPropSetGuid;
			if (!InlineIsEqualGUID(*pCreatePropSetGuid, GUID_NULL)) 
				pGroup[iCnt++] = pCreatePropSetGuid;

		ULONG ulSets = pT->CUtlProps<T>::GetSupportedSetsInGroup(iCnt, pGroup, &ppGuid);

			hr = pT->CUtlProps<T>::SetProperties(0, cPropertySets, rgPropertySets, ulSets, ppGuid);
			CoTaskMemFree(ppGuid);
		}

	// datastore erzeugen und eröffnen
		hr = pT->CreateAndOpenDatasource();
		if (FAILED(hr)) return hr;

		_ASSERTE(pT->m_dwStatus & DSF_INITIALIZED);		// muß jetzt initialisiert sein

	// session über neuem datastore erzeugen
		return pT->CreateSession(pUnkOuter, riid, ppDBSession);
	}
	STDMETHODIMP DestroyDataSource(void)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::DestroyDataSource\n");

	T *pT = static_cast<T *>(this);

		if (!(pT->m_dwStatus & DSF_INITIALIZED))
			return E_UNEXPECTED;

		if (0 != pT->m_cSessionsOpen) {
			ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::DestroyDataSource called with Open Sessions\n");
			return DB_E_OBJECTOPEN;
		}

	// zerlegen des datastore
		return pT -> CloseAndDestroyDatasource();
	}
	STDMETHODIMP GetCreationProperties(ULONG cPropertySets, const DBPROPIDSET rgPropertySets[],
            ULONG *pcPropertyInfoSets, DBPROPINFOSET **prgPropertyInfoSets, OLECHAR **ppDescBuffer)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::GetCreationProperties\n");

	T *pT = static_cast<T *>(this);

		if(pT->m_dwStatus & DSF_INITIALIZED)
			return DB_E_ALREADYINITIALIZED;

		if (pT->m_pCUtlPropInfo == NULL) {
		// Go ahead and create the m_pCUtlPropInfo but do not change the
		// Initialized status of the provider (see IDBInitialize::Initialize).
			ATLTRACE2(atlTraceDBProvider, 0, "m_pCUtlPropInfo == NULL\n");

			pT->Lock();
			ATLTRY(pT->m_pCUtlPropInfo = new CUtlPropInfo<T>())
			pT->Unlock();
			if (pT->m_pCUtlPropInfo == NULL)
			{
				ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::GetCreationProperties: OOM\n");
				return E_OUTOFMEMORY;
			}

		HRESULT hr = pT->m_pCUtlPropInfo->FInit();

			if (hr != S_OK)	{
				pT->Lock();
				delete pT->m_pCUtlPropInfo;
				pT->m_pCUtlPropInfo = NULL;
				pT->Unlock();
			}
		}
		
	// Initialize
		if (pcPropertyInfoSets)
			*pcPropertyInfoSets = 0;
		if (prgPropertyInfoSets)
			*prgPropertyInfoSets = NULL;
		if (ppDescBuffer)
			*ppDescBuffer = NULL;
		
	// Check Arguments
		if (((cPropertySets > 0) && !rgPropertySets) || !pcPropertyInfoSets || !prgPropertyInfoSets)
			return E_INVALIDARG;
		
	// New argument check for > 1 cPropertyIDs and NULL pointer for array of property ids.
	const DWORD SPECIAL_GROUP	= 1;
	const DWORD SPECIAL_SINGLE	= 2;
	const DWORD SPECIALS		= SPECIAL_GROUP | SPECIAL_SINGLE;
	DWORD dwSpecial = 0;

		for(ULONG ul = 0; ul < cPropertySets; ul++) {
			if ((rgPropertySets[ul].guidPropertySet == DBPROPSET_DATASOURCEALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_DATASOURCEINFOALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_DBINITALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_SESSIONALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_VIEWALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_COLUMNALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_CONSTRAINTALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_INDEXALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_TABLEALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_TRUSTEEALL) ||
				(rgPropertySets[ul].guidPropertySet == DBPROPSET_ROWSETALL))
				dwSpecial |= SPECIAL_GROUP;
			else
				dwSpecial |= SPECIAL_SINGLE;
			
			if ((dwSpecial == SPECIALS) || (rgPropertySets[ul].cPropertyIDs && !(rgPropertySets[ul].rgPropertyIDs)))
				return E_INVALIDARG;
		}
		
		return pT->m_pCUtlPropInfo->GetPropertyInfo(cPropertySets, rgPropertySets,
					pcPropertyInfoSets, prgPropertyInfoSets,
					ppDescBuffer, false, InlineIsEqualGUID(*pCreatePropSetGuid, GUID_NULL) ? NULL : pCreatePropSetGuid);
	}
	STDMETHODIMP ModifyDataSource(ULONG cPropertySets, DBPROPSET rgPropertySets[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::ModifyDataSource\n");

	HRESULT hr;
	DBPROPSET* pdbPropSet = NULL;
	ULONG iProp;

	T *pT = static_cast<T *>(this);
		
	// Quick return if the Count of Properties is 0
		if (0 == cPropertySets)
			return S_OK;
		
		hr = pT->CUtlProps<T>::SetPropertiesArgChk(cPropertySets, rgPropertySets);
		if (FAILED(hr)) return hr;

	// We need to handle the DBINIT properties specially after being initialized.
	// - they should be treated as NOTSETTABLE at this point.
		if (!(pT->m_dwStatus & DSF_INITIALIZED))
			return E_UNEXPECTED;	// not initialized

		if (0 != pT->m_cSessionsOpen) {
			ATLTRACE2(atlTraceDBProvider, 0, "IDBDataSourceAdminImpl::ModifyDataSource called with Open Sessions\n");
			return DB_E_OBJECTOPEN;
		}

		_ASSERTE(0 != cPropertySets);
		
	BOOL fFoundDBINIT = FALSE;
		
	// Allocate a DBPROPSET structure of equal size
		ATLTRY(pdbPropSet = new DBPROPSET[cPropertySets])
		if (pdbPropSet == NULL)
			return E_OUTOFMEMORY;
			
		for(ULONG iNewSet = 0, iSet = 0; iSet < cPropertySets; iSet++)	{
		// Remove any DBPROPSET_DBINIT values and mark them all as not settable
			if ((InlineIsEqualGUID(rgPropertySets[iSet].guidPropertySet, DBPROPSET_DBINIT)) ||
				(InlineIsEqualGUID(rgPropertySets[iSet].guidPropertySet, *pInitPropSetGuid)))
			{
				fFoundDBINIT = TRUE;
				for(iProp = 0; iProp < rgPropertySets[iSet].cProperties; iProp++)
					rgPropertySets[iSet].rgProperties[iProp].dwStatus = DBPROPSTATUS_NOTSETTABLE;
			}
			else {
			// If not DBPROPSET_DBINIT then copy the DBPROPSET values
				memcpy(&pdbPropSet[iNewSet++], &rgPropertySets[iSet], sizeof(DBPROPSET));
			}
		}
			
	// If we have no propertyset to pass on to the property handler, we
	// can exit
		if (iNewSet == 0) 
			hr = DB_E_ERRORSOCCURRED;
		else {
		// MRD - Updated to support custom property sets
		const GUID **ppGuid = NULL;
		const GUID *ppGroups[3];
		int iCnt = 1;
				
			ppGroups[0] = &DBPROPSET_DBINITALL;
			if (!InlineIsEqualGUID(*pInitPropSetGuid, DBPROPSET_DBINIT))
				ppGroups[iCnt++] = pInitPropSetGuid;
			if (!InlineIsEqualGUID(*pCreatePropSetGuid, GUID_NULL)) 
				ppGroups[iCnt++] = pCreatePropSetGuid;

		ULONG ulSets = pT->CUtlProps<T>::GetSupportedSetsInGroup(iCnt, ppGroups, &ppGuid);

			hr = pT->CUtlProps<T>::SetProperties(0, cPropertySets, rgPropertySets, ulSets, ppGuid);
			CoTaskMemFree(ppGuid);
				
		// If we have determined that one of the property sets was DBINIT, we may
		// need to fixup the returned hr value.
			if (fFoundDBINIT && SUCCEEDED(hr))
				hr = DB_S_ERRORSOCCURRED;
		}
		delete[] pdbPropSet;
		return hr;
	}

protected:
	HRESULT CreateAndOpenDatasource()
	{
		return DB_E_NOTSUPPORTED;	// overload to implement CreateDataSource
	}
	HRESULT CloseAndDestroyDatasource()
	{
		return DB_E_NOTSUPPORTED;	// overload to implement DestroyDataSource
	}
};

#endif // !defined(_IDBDATASOURCEADMINIMPL_H__84D668C2_E837_4912_9018_1ECB725FA7D4__INCLUDED_)
