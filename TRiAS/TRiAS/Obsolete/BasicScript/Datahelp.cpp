// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "bscriptp.hxx"
#include "bscript.h"

#include <eonrguid.h>
#include <oprpguid.h>

#include "macrguid.h"
#include "imacorg.h"

#include "datahelp.h"

#define OS_NO_STREAM_SUPPORT

DefineSmartInterface(Stream);

// Funktionen für EnumLONG ////////////////////////////////////////////////////

// Serialisieren/DeSerialisieren eines IUnknowns 
// in diesem Falle ein IDataObject
HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk,// IEnum *, 
										   REFCLSID rClsID, 					
										   IStream **ppIStream)
{
	ASSERT(pIUnk);
	ASSERT(ppIStream);

	*ppIStream = NULL;

// neuen Stream anlegen, kreiert eine neuen Memoryblock der Größe NULL
// wird selbstständig wieder freigegen (true)
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());	
	if (FAILED(hr)) return hr;

	try {
	WPersistStream IPersStr (pIUnk);	// throws hr

	// den Enumerator wegschreiben
		hr = OleSaveToStream (IPersStr, IStream);
		if (FAILED(hr)) throw hr;

	// wieder zurück positionieren
	LARGE_INTEGER li;
		LISet32 (li, 0L);
		hr = IStream -> Seek (li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr)) throw hr;

		*ppIStream = IStream.detach();

	} catch (HRESULT hr) {
		if (*ppIStream) (*ppIStream) -> Release();
		*ppIStream = NULL;
		return hr;
	}

return NOERROR;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, 
								  IEnum<LONG> **ppEnumOut)
{
	ASSERT(pIStream);
	ASSERT(ppEnumOut);

HRESULT hr = NOERROR;

	*ppEnumOut = NULL;
	
	try {
		
		hr = OleLoadFromStream (pIStream, IID_IEnumLONG, (LPVOID *)ppEnumOut);  
		if (FAILED(hr)) throw hr;
	
	} catch (HRESULT hr_result) {
		if (*ppEnumOut) (*ppEnumOut) -> Release();
		return hr_result;
	}

return NOERROR;
}

// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnum<LONG> *pEnum, REFCLSID rClsID, IDataObject *pDataObj)
{
	ASSERT(pEnum);
	ASSERT(pDataObj);

// Stream mit EnumLONG generieren
WStream IStream;
HRESULT hr = CreateStreamOnHGlobalFromIUnknown (pEnum, rClsID, IStream.ppi());
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

// Dient zum Lesen der Daten (EnumLONG) vom Stream im Datenobjekt
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut)
{
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

	// Einlesen des Enumerators aus den erhaltenen STGMEDIUM
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

// Hinzufügen eines HWND zu einem IDataObject ---------------------------------
HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj)
{
// hGlobal erzeugen
HGLOBAL hGlobal = GlobalAlloc (GHND, sizeof(HWND));

	if (!hGlobal) return ResultFromScode (E_OUTOFMEMORY);

HWND *pHWnd = (HWND *)GlobalLock (hGlobal);

	if (NULL == pHWnd) return ResultFromScode (E_OUTOFMEMORY);

	*pHWnd = hWnd;
	GlobalUnlock (hGlobal);

// diesen hGlobal im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_HGLOBAL;
	stg.hGlobal = hGlobal;
	stg.pUnkForRelease = NULL;

HRESULT hr = pDataObj -> SetData ((FORMATETC *)&c_feObjectWindow, &stg, true);

	if (FAILED(hr)) return hr;

return NOERROR;
}

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feObjectWindow);
		if (NOERROR != hr) throw hr;	// Format nicht vorhanden

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feObjectWindow, &stg);
		if (FAILED(hr)) throw hr;

	// HWND aus STGMEDIUM herauskopieren
	HWND *phWndGlobal = (HWND *)GlobalLock (stg.hGlobal);

		if (NULL == phWndGlobal)
			throw ResultFromScode (E_UNEXPECTED);

		*phWnd = *phWndGlobal;
		ReleaseStgMedium (&stg);

	} catch (HRESULT hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return hr_result;
	}	

return NOERROR;
}
