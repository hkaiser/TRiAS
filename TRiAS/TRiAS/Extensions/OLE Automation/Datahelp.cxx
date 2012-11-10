// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "precomp.hxx"

#define _TRIAS03_ENTRY 
#include <eonrguid.h>
#include <oprpguid.h>

#include <propactn.h>
#include <selobwnd.h>

#include "Strings.h"
#include "GlobalFuncs.h"

// #define _DEBUG_ISTREAM
#if defined(_DEBUG_ISTREAM)
#include "strmhelp.hxx"
#endif // _DEBUG

DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);

// Funktionen für EnumLONG ////////////////////////////////////////////////////
// Serialisieren/DeSerialisieren eines IUnknowns ------------------------------
HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk, IStream **ppIStream)
{
	*ppIStream = NULL;

// neuen Stream anlegen
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());
	
	if (FAILED(hr)) return hr;

#if defined(_DEBUG_ISTREAM)
	IStream = new CStreamWrapper (IStream);
#endif // _DEBUG

	try {
	WPersistStream IPersStr = pIUnk;	// throws hr
	WStream StrClone;

	// den Enumerator wegschreiben
		THROW_FAILED_HRESULT(IStream->Clone(StrClone.ppi()));
		THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, StrClone));

	LARGE_INTEGER li;

		LISet32(li, 0L);
		THROW_FAILED_HRESULT(IStream -> Seek (li, SEEK_SET, NULL));

		*ppIStream = IStream.detach();		// Resultat

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, IEnumLONG **ppEnumOut)
{
	if (NULL == ppEnumOut) 
		return E_POINTER;

	*ppEnumOut = NULL;
	try {
	WStream StrClone;

		THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
		THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, IID_IEnumLONG, (LPVOID *)ppEnumOut));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateMonikerFromStream (IStream *pIStream, IMoniker **ppIMk)
{
	if (NULL == ppIMk) 
		return E_POINTER;

	*ppIMk = NULL;

	try {
	WStream StrClone;

		THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
		THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, IID_IMoniker, (LPVOID *)ppIMk));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnumLONG *pEnum, IDataObject *pDataObj)
{
// Stream mit EnumLONG generieren
WStream IStream;
HRESULT hr = CreateStreamOnHGlobalFromIUnknown (pEnum, IStream.ppi());

	if (FAILED(hr)) return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_ISTREAM;
	stg.pstm = IStream.detach();
	stg.pUnkForRelease = NULL;

	hr = pDataObj -> SetData ((FORMATETC *)&c_feSelectedObjects, &stg, true);
	if (FAILED(hr)) {
		ReleaseStgMedium (&stg);
		return hr;
	}

return NOERROR;
}

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumLONG **ppIEnumOut)
{
	if (NULL == pIDataObj) return E_POINTER;

STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects);

		if (NOERROR != hr) return hr;	// Format nicht vorhanden
		if (NULL == ppIEnumOut) return S_OK;	// nur nachfragen

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg);
		if (FAILED(hr)) _com_issue_error(hr);

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, ppIEnumOut);
		if (FAILED(hr)) _com_issue_error(hr);

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Moniker in DataObject ablegen und wieder rausholen 
HRESULT SetMonikerData (IMoniker *pIMk, IDataObject *pIDO, const FORMATETC *pcfe)
{
// Stream mit EnumLONG generieren
WStream IStream;
HRESULT hr = CreateStreamOnHGlobalFromIUnknown (pIMk, IStream.ppi());

	if (FAILED(hr)) return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_ISTREAM;
	stg.pstm = IStream.detach();
	stg.pUnkForRelease = NULL;

	hr = pIDO -> SetData ((FORMATETC *)pcfe, &stg, true);
	if (FAILED(hr)) {
		ReleaseStgMedium (&stg);
		return hr;
	}

return NOERROR;
}

HRESULT GetMonikerData (IDataObject *pIDO, const FORMATETC *pcfe, IMoniker **ppIMk)
{
	if (NULL == pIDO) return E_POINTER;

STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDO -> QueryGetData ((FORMATETC *)pcfe);

		if (NOERROR != hr) return hr;	// Format nicht vorhanden
		if (NULL == ppIMk) return S_OK;	// nur nachfragen

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDO -> GetData ((FORMATETC *)pcfe, &stg));

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		THROW_FAILED_HRESULT(CreateMonikerFromStream (stg.pstm, ppIMk));

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// BindMkObject: binden eines Objektes über einen Moniker im DataObject
HRESULT BindMonikerFromDataObject (
	IDataObject *pIDO, const FORMATETC *pcfe, REFIID riid, LPVOID *ppv)
{
// Moniker aus DataObject herauslesen
WMoniker mkData;
HRESULT hr = GetMonikerData (pIDO, pcfe, mkData.ppi());

	if (FAILED(hr)) return hr;

// Objekt über Moniker instantiieren
	return BindMoniker (mkData, 0, riid, ppv);
}

///////////////////////////////////////////////////////////////////////////////
// Schreiben/Lesen eines Variant
HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe)
{
// Stream mit Variant generieren
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());

	if (FAILED(hr)) return hr;

// Variant dort rein schreiben
	hr = rv.WriteToStream (IStream);
	if (FAILED(hr)) return hr;

LARGE_INTEGER li;

	LISet32(li, 0L);
	hr = IStream -> Seek (li, SEEK_SET, NULL);
	if (FAILED(hr))	return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_ISTREAM;
	stg.pstm = IStream.detach();
	stg.pUnkForRelease = NULL;

	hr = pIDO -> SetData ((FORMATETC *)pcfe, &stg, true);
	if (FAILED(hr)) {
		ReleaseStgMedium (&stg);
		return hr;
	}

return NOERROR;
}

HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv)
{
	if (NULL == pIDO) return E_POINTER;

STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDO -> QueryGetData ((FORMATETC *)pcfe);

		if (NOERROR != hr) return hr;	// Format nicht vorhanden
		if (NULL == pv) return S_OK;	// nur nachfragen

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDO -> GetData ((FORMATETC *)pcfe, &stg));

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		THROW_FAILED_HRESULT(pv -> ReadFromStream (stg.pstm));

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	

return NOERROR;
}

