// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 23:39:44 
//
// @doc
// @module MapHelpers.h | Helperklassen/Routinen für diverse Maps

#if !defined(__MAPHELPERS_H__C7719CF0_B5D4_11d2_98E3_0060085FC1CE)
#define __MAPHELPERS_H__C7719CF0_B5D4_11d2_98E3_0060085FC1CE

#include <com/MkHelper.h>

template<class T> 
class binary_initialize : 
	public os_binary_function<T, bool, HRESULT> 
{
	typedef T binary_inititialize_target;
};

template<class T, class Predicate>
inline HRESULT FindObjectInMap (
	ITRiASObjectHandleMap *pIMap, INT_PTR &rlHandle, T &rObj, Predicate &initpred)
{
	if (NULL != pIMap && SUCCEEDED(pIMap  ->  GetObject (rlHandle, rObj.ppu()))) 
		return initpred(rObj, false);	// teilweise initialisierung, wenn Objekt bereits existiert
	return E_FAIL;
}

template <class T, class Predicate>
inline HRESULT FindInMapOrCreateObject(
	ITRiASObjectHandleMap *pIMap, IMoniker *pMkObject, INT_PTR &rlHandle, T &rObj, 
	CLSID riid, Predicate &initpred) 
{
	_ASSERTE(NULL != pIMap);

CComBSTR strObjName;
	
	RETURN_FAILED_HRESULT(MkGetDisplayName (pMkObject, CLEARED(strObjName)));

HRESULT	hrCreated = pIMap -> GetObjectHandle (CComVariant(strObjName), rObj, OBJECTMAPMODE_GetObjectHandle, &rlHandle);

	if(S_FALSE == hrCreated) {
	// Objekt existiert bereits
		RETURN_FAILED_HRESULT(pIMap -> GetObject(rlHandle, rObj.ppu()));
	} 
	else if (TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED == hrCreated) {
	// Objekt neu basteln
		rObj = T(riid);
		RETURN_FAILED_HRESULT(initpred(rObj, true));
		RETURN_FAILED_HRESULT(hrCreated = pIMap -> GetObjectHandle (CComVariant(strObjName), rObj, OBJECTMAPMODE_CreateObjectHandle, &rlHandle));
		RETURN_EXPR_TRUE(S_FALSE == hrCreated, E_UNEXPECTED);
	} 
	else {
		_ASSERTE( SUCCEEDED(E_UNEXPECTED) );
		return E_UNEXPECTED;
	}
	return hrCreated;
}

///////////////////////////////////////////////////////////////////////////////
// derzeit verwendet für evtl. bereits existierende GDOObject-Objekte und GDOFeature-Objekte
template <class T, class Predicate>
inline HRESULT FindInMapOrCreateObject(
	ITRiASObjectHandleMap *pIMap, IMoniker *pMkObject, INT_PTR &rlHandle, T &rObj, 
	IClassFactory *pIClsFact, Predicate &initpred) 
{
	_ASSERTE(NULL != pIMap);

CComBSTR strObjName;
	
	RETURN_FAILED_HRESULT(MkGetDisplayName (pMkObject, CLEARED(strObjName)));

HRESULT	hrCreated = pIMap -> GetObjectHandle (CComVariant(strObjName), NULL, OBJECTMAPMODE_GetObjectHandle, &rlHandle);

	if(S_FALSE == hrCreated) {
	// Objekt existiert bereits
		RETURN_FAILED_HRESULT(pIMap -> GetObject (rlHandle, rObj.ppu()));
	} 
	else if (TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED == hrCreated) {
	// Objekt neu basteln
	OBJECTMAPMODE rgMode = OBJECTMAPMODE(OBJECTMAPMODE_CreateObjectHandle|OBJECTMAPMODE_UsePredefinedHandle);

		RETURN_FAILED_HRESULT(pIClsFact -> CreateInstance (NULL, rObj.GetIID(), rObj.ppv()));	// neues Objekt erzeugen
		RETURN_FAILED_HRESULT(initpred(rObj, true));
		RETURN_FAILED_HRESULT(hrCreated = pIMap -> GetObjectHandle (CComVariant(strObjName), rObj, rgMode, &rlHandle));
		RETURN_FAILED_HRESULT(WTRiASHandle(rObj) -> PutHandle(rlHandle));
		RETURN_EXPR_TRUE(S_FALSE == hrCreated, E_UNEXPECTED);
	} 
	else {
		_ASSERTE(SUCCEEDED(E_UNEXPECTED));
		return E_UNEXPECTED;
	}
	return hrCreated;
}

///////////////////////////////////////////////////////////////////////////////
// derzeit verwendet für neu zu erzeugende GDOObject-Objekte 
template <class T, class Predicate>
inline HRESULT FindInMapOrCreateObject( 
	ITRiASObjectHandleMap *pIMap, INT_PTR &rlHandle, T &rObj, CLSID riid, Predicate &initpred)
{
	_ASSERTE(NULL != pIMap);
	COM_TRY {
		if (FAILED(pIMap -> GetObject (rlHandle, rObj.ppu()))) {
		// neues Objekt erzeugen und initialisieren
			rObj = T(riid);
			THROW_FAILED_HRESULT(initpred(rObj, true));	// vollständige Initialisierung

		// jetzt in der Tabelle des Bezugsobjektes eintragen
		WMoniker pMk;
		CComBSTR strObjName;

			RETURN_FAILED_HRESULT(MkGetMoniker (rObj, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, pMk.ppi()));
			RETURN_FAILED_HRESULT(MkGetDisplayName (pMk, CLEARED(strObjName)));

		HRESULT	hrCreated;

			RETURN_FAILED_HRESULT(hrCreated = pIMap -> GetObjectHandle (CComVariant(strObjName), rObj, OBJECTMAPMODE_CreateObjectHandle, &rlHandle));
			if (S_OK == hrCreated) {
				RETURN_FAILED_HRESULT(WTRiASHandle(rObj) -> PutHandle(rlHandle));
			} else {		// ==> S_FALSE ==> Objekt existiert bereits unter diesem Namen in der Map
				RETURN_FAILED_HRESULT(pIMap -> GetObject (rlHandle, rObj.ppu()));
			}

#if defined(_DEBUG)
		T testObj;

			_ASSERTE(SUCCEEDED(pIMap -> GetObject (rlHandle, testObj.ppu())));
			_ASSERTE(rObj == testObj);
#endif
			return hrCreated;
		} else {
			// Objekt existiert bereits
			THROW_FAILED_HRESULT(initpred(rObj, false));	// teilweise initialisierung
			return S_FALSE;
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// derzeit verwendet für GDOFeature-Objekte
//template <class T, class Predicate>
//inline HRESULT FindInMapOrCreateObject(
//	ITRiASObjectHandleMap *pIMap, INT_PTR &rlHandle, T &rObj, IClassFactory *pIClsFact, Predicate &initpred) 
//{
//	_ASSERTE(NULL != pIMap);
//
//HRESULT	hrCreated = E_FAIL;
//
//	if (NULL != rlHandle) {		// evtl. existiert dieses Objekt schon
//		hrCreated = pIMap -> GetObject (rlHandle, rObj.ppu());
//	}
//
//	if (TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED == hrCreated) {
//	// Objekt neu basteln
//		RETURN_FAILED_HRESULT(pIClsFact -> CreateInstance (NULL, rObj.GetIID(), rObj.ppv()));	// neues Objekt erzeugen
//		RETURN_FAILED_HRESULT(initpred(rObj, true));
//		RETURN_FAILED_HRESULT(hrCreated = pIMap -> GetObjectHandle (vtMissing, rObj, OBJECTMAPMODE_CreateObjectHandle, &rlHandle));
//		RETURN_EXPR_TRUE(S_FALSE == hrCreated, E_UNEXPECTED);
//	} 
//	else {
//		_ASSERTE(SUCCEEDED(E_UNEXPECTED));
//		return E_UNEXPECTED;
//	}
//	return hrCreated;
//}

#endif // __MAPHELPERS_H__C7719CF0_B5D4_11d2_98E3_0060085FC1CE

