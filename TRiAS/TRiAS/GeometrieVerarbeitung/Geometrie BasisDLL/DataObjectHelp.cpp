// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DataObjectHelp.cpp
// H. Kaiser


#include "GeometrP.hxx"		// precompiled header

#include <propactn.h>		// c_feSelectedObjects
#include <selobwnd.h>		// c_feObjectWindow
#include <PacketNumber.h>	// c_cbPacketNumber

#include <eonrguid.h>		// IID_IEnumLONG

#if _TRiAS_VER >= 0x0300
#include <Com/PropertyActionBaseDataImpl.cpp>
#endif // _TRiAS_VER >= 0x0300

#include "DataObjectHelp.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);



///////////////////////////////////////////////////////////////////////////////////////////////
// STGMEDIUM enthält einen serialisierten EnumLONG, dazu können die folgenden Helperroutinen
// verwendet werden.

// --------------------------------------------------------------------------------------------
// Funktionen für EnumLONG
// Serialisieren/DeSerialisieren eines IUnknowns
HRESULT _GEOMETR_EXPORT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk,
														   IStream **ppIStream)
{
	if (NULL == ppIStream) 
		return E_POINTER;
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

return S_OK;
}


// --------------------------------------------------------------------------------------------
// die folgende Funktion ist das konkrete Äquivalent für 'OleLoadFromStream'
HRESULT _GEOMETR_EXPORT CreateEnumLONGFromStream (IStream *pIStream, REFIID riid,
												  LPVOID *ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	*ppEnumOut = NULL;

	try {
	WStream StrClone;

		THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
		THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, riid, ppEnumOut));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Hinzufügen eines EnumLONG zu einem IDataObject
HRESULT _GEOMETR_EXPORT SetEnumLONGData (IEnum<LONG> *pEnum, IDataObject *pDataObj)
{
// den Stream im DataObject setzen
STGMEDIUM stg;

	ZeroMemory (&stg, sizeof(STGMEDIUM));
	try {
	// Stream mit EnumLONG generieren
	WStream IStream;

		THROW_FAILED_HRESULT(CreateStreamOnHGlobalFromIUnknown (pEnum, IStream.ppi()));

		stg.tymed = TYMED_ISTREAM;
		stg.pstm = IStream.detach();
		stg.pUnkForRelease = NULL;

		THROW_FAILED_HRESULT(pDataObj -> SetData ((FORMATETC *)&c_feSelectedObjects, &stg, true));

	} catch (_com_error &e) {
		if (NULL != stg.pstm)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Lesen eines EnumLONG aus einem DataObjekt
HRESULT _GEOMETR_EXPORT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut)
{
	return GetEnumLONGData (pIDataObj, IID_IEnumLONG, (LPVOID *)ppIEnumOut);
}


// --------------------------------------------------------------------------------------------
HRESULT _GEOMETR_EXPORT GetEnumLONGData (IDataObject *pIDataObj, REFIID riid, LPVOID *ppv)
{
	if (NULL == pIDataObj) return E_POINTER;

HRESULT hr = E_FAIL;
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects);
		if (S_OK != hr) _com_issue_error(hr);	// Format nicht vorhanden

		if (NULL == ppv)	
			return S_OK;				// nur abfragen, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg);
		if (FAILED(hr)) _com_issue_error(hr);

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, riid, ppv);
		if (FAILED(hr)) _com_issue_error(hr);

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Hinzufügen eines HWND zu einem IDataObject
HRESULT _GEOMETR_EXPORT SetHWNDData (HWND hWnd, IDataObject *pDataObj)
{
STGMEDIUM stg;

	ZeroMemory (&stg, sizeof(STGMEDIUM));
	try {
	// hGlobal erzeugen
	HGLOBAL hGlobal = GlobalAlloc (GHND, sizeof(HWND));

		if (!hGlobal) _com_issue_error(E_OUTOFMEMORY);

	HWND *pHWnd = (HWND *)GlobalLock (hGlobal);

		if (NULL == pHWnd) _com_issue_error(E_OUTOFMEMORY);

		*pHWnd = hWnd;
		GlobalUnlock (hGlobal);

	// diesen hGlobal im DataObject setzen
	STGMEDIUM stg;

		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hGlobal;
		stg.pUnkForRelease = NULL;

		THROW_FAILED_HRESULT(pDataObj -> SetData ((FORMATETC *)&c_feObjectWindow, &stg, true));

	} catch (_com_error &e) {
		if (NULL != stg.hGlobal)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Lesen eines EnumLONG aus einem DataObjekt
HRESULT _GEOMETR_EXPORT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feObjectWindow);
		if (S_OK != hr) _com_issue_error(hr);	// Format nicht vorhanden

		if (NULL == phWnd)
			return S_OK;				// nur Abfrage, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feObjectWindow, &stg);
		if (FAILED(hr)) _com_issue_error(hr);

	// HWND aus STGMEDIUM herauskopieren
	HWND *phWndGlobal = (HWND *)GlobalLock (stg.hGlobal);

		if (NULL == phWndGlobal)
			throw ResultFromScode (E_UNEXPECTED);

		*phWnd = *phWndGlobal;
		ReleaseStgMedium (&stg);

	}
	catch (_com_error& hr_result)
	{
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	

	return S_OK;
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
		_ASSERTE(TYMED_ISTREAM == stg.tymed);	// sollte ein Stream sein

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
	LARGE_INTEGER li;

		li.QuadPart = 0;
		THROW_FAILED_HRESULT(stg.pstm -> Seek(li, STREAM_SEEK_SET, NULL));
		THROW_FAILED_HRESULT(pv -> ReadFromStream (stg.pstm));

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Paketnummer behandeln
HRESULT _GEOMETR_EXPORT GetPacketNumber (IDataObject *pIDO, long *plNumber)
{
	if (NULL == plNumber) 
		return E_POINTER;
	*plNumber = 0L;

CComVariant vNumber;

	if (SUCCEEDED(GetVariantData(pIDO, &c_fePacketNumber, &vNumber))) {
		RETURN_FAILED_HRESULT(vNumber.ChangeType(VT_I4));
		*plNumber = V_I4(&vNumber);
	}
	return S_OK;
}

HRESULT _GEOMETR_EXPORT SetPacketNumber (IDataObject *pIDO, long lNumber)
{
	RETURN_FAILED_HRESULT(SetVariantData(CComVariant(lNumber), pIDO, &c_fePacketNumber));
	return S_OK;
}

