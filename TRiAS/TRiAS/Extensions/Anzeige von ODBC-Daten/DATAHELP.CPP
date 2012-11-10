// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CPP

#include "pheader.h"		// vorübers. Header

#include <ospace/com/iterenum.h>
//#include <triashelper.h>		
// #include <eonrguid.h>
// #include <initguid.h>

#include <propactn.h>
#include <hpp/datahelp.hpp>		// zugeh. Header

#if _MSC_VER >= 1200
#include <Com/PropertyActionBaseDataImpl.cpp>
#endif // _MSC_VER >= 1200

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	try {
	WPersistStream IPersStr = pIUnk;	// throws hr

	// den Enumerator wegschreiben
		hr = OleSaveToStream (IPersStr, IStream);
		if (FAILED(hr)) throw hr;

	// wieder zurück positionieren
	LARGE_INTEGER li;

		LISet32 (li, 0L);
		hr = IStream -> Seek (li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr)) throw hr;

		*ppIStream = IStream.detach();		// Resultat

	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, IEnumObjectsByNumber **ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	*ppEnumOut = NULL;

return OleLoadFromStream (pIStream, IID_IEnumObjectsByNumber, (LPVOID *)ppEnumOut);
}

// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnumObjectsByNumber *pEnum, IDataObject *pDataObj)
{
	if (!pEnum || !pDataObj)
		return E_POINTER;

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
	if (FAILED(hr)) return hr;

return NOERROR;
}

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumObjectsByNumber **ppIEnumOut)
{
	if (!pIDataObj || !ppIEnumOut)
		return E_POINTER;
		
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	 // Testen, ob das gewünschte Format überhaupt da ist

		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects);
		if (NOERROR != hr) throw hr;	// Format nicht vorhanden

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg);
		if (FAILED(hr)) throw hr;

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, ppIEnumOut);
		if (FAILED(hr)) throw hr;

		ReleaseStgMedium (&stg);

	} catch (HRESULT hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return hr_result;
	}	

return NOERROR;
}

// fje
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
	return S_OK;
}

HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv)
{
	if (NULL == pIDO) return E_POINTER;

STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDO -> QueryGetData ((FORMATETC *)pcfe);

		if (S_OK != hr) return hr;	// Format nicht vorhanden
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
	return S_OK;
}
// fje


