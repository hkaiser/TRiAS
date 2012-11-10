// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 07/07/1998 02:56:13 PM
//
// @doc
// @module FindInMapOrCreateObject.h | Objekte in Maps verwalten etc.

#if !defined(_FINDINMAPORCREATEOBJECT_H__D0418425_1562_11D2_9E8D_006008447800__INCLUDED_)
#define _FINDINMAPORCREATEOBJECT_H__D0418425_1562_11D2_9E8D_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Finden eines Objektes in einer ObjectMap oder neu erzeugen mit definierten
// Parametern
template<class T>
struct binary_initialize
	: public os_binary_function<T, T, HRESULT>
{
	typedef T binary_inititialize_target;
};

template<class T, class Predicate>
inline HRESULT FindObjectInMap (
	ITRiASObjectHandleMap *pIMap, INT_PTR &rlHandle, T &rObj, Predicate &initpred)
{
	if (NULL != pIMap && SUCCEEDED(pIMap -> GetObject (rlHandle, rObj.ppu()))) 
		return initpred(rObj, false);	// teilweise initialisierung, wenn Objekt bereits existiert
	return E_FAIL;
}

template<class T, class Predicate>
inline HRESULT FindInMapOrCreateObject (
	ITRiASObjectHandleMap *pIMap, INT_PTR &rlHandle, T &rObj, CLSID riid, Predicate &initpred)
{
	COM_TRY {
		if (NULL == pIMap || NULL == rlHandle || FAILED(pIMap -> GetObject (rlHandle, rObj.ppu()))) {
		// neues Objekt erzeugen und initialisieren
			rObj = T(riid);
			THROW_FAILED_HRESULT(initpred(rObj, true));	// vollständige Initialisierung

		// jetzt in der lokalen Tabelle des Bezugsobjektes eintragen
			if (NULL != pIMap) {	// neuen Eintrag in Tabelle erzeugen
				VERIFY(S_OK == pIMap -> GetObjectHandle (vtMissing, rObj, OBJECTMAPMODE_CreateObjectHandle, &rlHandle));
			}
		} else {
		// Objekt existiert breits
			THROW_FAILED_HRESULT(initpred(rObj, false));	// teilweise initialisierung
			return S_FALSE;
		}
	} COM_CATCH;
	return S_OK;
}

template<class T, class Predicate>
inline HRESULT FindInMapOrCreateObjectEx (
	ITRiASObjectHandleMap *pIMap, INT_PTR lONrOrIdent, INT_PTR &rlHandle, T &rObj, 
	CLSID riid, Predicate &initpred, OBJECTMAPMODE rgMode = OBJECTMAPMODE_CreateObjectHandle)
{
HRESULT hr = S_OK;

	COM_TRY {
//		_ASSERTE(NULL != lONrOrIdent);
		if (NULL == pIMap || FAILED(pIMap -> GetObject (lONrOrIdent, rObj.ppu()))) {
		// neues Objekt erzeugen und initialisieren
#if defined(_DEBUG)
		INT_PTR lHandleCopy = rlHandle;
#endif // _DEBUG

			rObj = T(riid);			// neues Objekt erzeugen
			hr = initpred(rObj, lONrOrIdent, rlHandle, true);		// vollständige Initialisierung
			THROW_FAILED_HRESULT(hr);
			_ASSERTE(S_OK == hr || S_FALSE == hr || TRIASDB_I_OBJECTS_NOT_EXISTS == hr);	// entweder bereits exitistent oder gar nicht vorhanden

		// jetzt in der lokalen Tabelle des Bezugsobjektes eintragen
			if (S_OK == hr && NULL != pIMap) {	
			// neuen Eintrag in Tabelle erzeugen, wenn es notwendig ist
			HRESULT hr2 = pIMap -> GetObjectHandle (CComVariant(lONrOrIdent), rObj, rgMode, &rlHandle);

				_ASSERTE((NULL == lHandleCopy && SUCCEEDED(hr2)) || S_OK == hr2);
				_ASSERTE(NULL == lHandleCopy || lHandleCopy == rlHandle);		// Zugriffsnummer darf sich nicht ändern, wenn vorhanden
			}

		} else {
		// Objekt existiert breits
			THROW_FAILED_HRESULT(initpred(rObj, lONrOrIdent, rlHandle, false));	// teilweise initialisierung
			return S_FALSE;
		}

	} COM_CATCH;
	return hr;
}

template<class T, class Predicate>
inline HRESULT FindInMapOrCreateObjectEx (
	ITRiASObjectHandleMap *pIMap, INT_PTR lONrOrIdent, INT_PTR &rlHandle, T &rObj, 
	IClassFactory *pIClsFact, Predicate &initpred, OBJECTMAPMODE rgMode = OBJECTMAPMODE_CreateObjectHandle)
{
HRESULT hr = S_OK;

	COM_TRY {
//		_ASSERTE(NULL != lONrOrIdent);
		if (NULL == pIMap || FAILED(pIMap -> GetObject (lONrOrIdent, rObj.ppu()))) {
		// neues Objekt erzeugen und initialisieren
#if defined(_DEBUG)
		INT_PTR lHandleCopy = rlHandle;
#endif // _DEBUG

			THROW_FAILED_HRESULT(pIClsFact -> CreateInstance (NULL, rObj.GetIID(), rObj.ppv()));	// neues Objekt erzeugen
			hr = initpred(rObj, lONrOrIdent, rlHandle, true);		// vollständige Initialisierung
			THROW_FAILED_HRESULT(hr);
			_ASSERTE(S_OK == hr || S_FALSE == hr || TRIASDB_I_OBJECTS_NOT_EXISTS == hr);	// entweder bereits exitistent oder gar nicht vorhanden

		// jetzt in der lokalen Tabelle des Bezugsobjektes eintragen
			if (S_OK == hr && NULL != pIMap) {	
			// neuen Eintrag in Tabelle erzeugen, wenn es notwendig ist
			HRESULT hr2 = pIMap -> GetObjectHandle (CComVariant(lONrOrIdent), rObj, rgMode, &rlHandle);

				_ASSERTE((NULL == lHandleCopy && SUCCEEDED(hr2)) || S_OK == hr2);
				_ASSERTE(NULL == lHandleCopy || lHandleCopy == rlHandle);		// Zugriffsnummer darf sich nicht ändern, wenn vorhanden
			}

		} else {
		// Objekt existiert breits
			THROW_FAILED_HRESULT(initpred(rObj, lONrOrIdent, rlHandle, false));	// teilweise initialisierung
			return S_FALSE;
		}

	} COM_CATCH;
	return hr;
}

// Ein Objekt gezielt neu erzeugen
template<class T, class Predicate>
inline HRESULT CreateObjectEx (
	ITRiASObjectHandleMap *pIMap, INT_PTR lONrOrIdent, INT_PTR &rlHandle, T &rObj, 
	CLSID riid, Predicate &createpred)
{
HRESULT hr = S_OK;

	COM_TRY {
		if (NULL == pIMap || FAILED(pIMap -> GetObject (lONrOrIdent, rObj.ppu()))) {
		// neues Objekt erzeugen und initialisieren
#if defined(_DEBUG)
		INT_PTR lHandleCopy = rlHandle;
#endif // _DEBUG

			rObj = T(riid);			// neues Objekt erzeugen
			hr = createpred(rObj, lONrOrIdent, rlHandle);		// vollständige Initialisierung
			THROW_FAILED_HRESULT(hr);

		// jetzt in der lokalen Tabelle des Bezugsobjektes eintragen
			if (NULL != pIMap) {	
			// neuen Eintrag in Tabelle erzeugen, wenn es notwendig ist
			HRESULT hr2 = pIMap -> GetObjectHandle (CComVariant(lONrOrIdent), rObj, OBJECTMAPMODE_CreateObjectHandle, &rlHandle);

				_ASSERTE((NULL == lHandleCopy && SUCCEEDED(hr2)) || S_OK == hr2);
				_ASSERTE(NULL == lHandleCopy || lHandleCopy == rlHandle);		// Zugriffsnummer darf sich nicht ändern, wenn vorhanden
			}

		} else {
		// Objekt existiert breits
			_ASSERTE(SUCCEEDED(E_FAIL));		// snh
			THROW_FAILED_HRESULT(E_FAIL);
		}

	} COM_CATCH;
	return hr;
}

#endif // !defined(_FINDINMAPORCREATEOBJECT_H__D0418425_1562_11D2_9E8D_006008447800__INCLUDED_)
