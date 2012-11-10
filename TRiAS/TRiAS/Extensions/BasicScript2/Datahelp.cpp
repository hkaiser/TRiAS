// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "bscriptp.hxx"
#include "bscript.h"

#include <eonrguid.h>
#include <oprpguid.h>
#include <Com/PropertyActionBaseDataImpl.cpp>

#include "macrguid.h"

#include "datahelp.h"

#define OS_NO_STREAM_SUPPORT

DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);

// Funktionen für EnumLONG ////////////////////////////////////////////////////

// Serialisieren/DeSerialisieren eines IUnknowns 
// in diesem Falle ein IDataObject
HRESULT CreateStreamOnHGlobalFromIUnknown (
	IUnknown *pIUnk, REFCLSID rClsID, IStream **ppIStream)
{
	ASSERT(NULL != pIUnk);
	ASSERT(NULL != ppIStream);

	*ppIStream = NULL;
	try	{
	// neuen Stream anlegen, kreiert eine neuen Memoryblock der Größe NULL
	// wird selbstständig wieder freigegen (true)
	WStream IStream;
	
		THROW_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, true, IStream.ppi()));

	// den Enumerator wegschreiben
	WPersistStream IPersStr (pIUnk);	// throws hr

		THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, IStream));

	// wieder zurück positionieren
	LARGE_INTEGER li;

		LISet32 (li, 0L);
		THROW_FAILED_HRESULT(IStream -> Seek (li, STREAM_SEEK_SET, NULL));

		*ppIStream = IStream.detach();
	} 
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, 
								  IEnum<LONG> **ppEnumOut)
{
	ASSERT(NULL != pIStream);
	ASSERT(NULL != ppEnumOut);

	if (NULL == ppEnumOut) 
		return E_POINTER;

	*ppEnumOut = NULL;
	return OleLoadFromStream (pIStream, IID_IEnumLONG, (LPVOID *)ppEnumOut);
}
// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateStringFromStream (IStream *pIStream, LPSTR lpstr, int iLen)
{
	ASSERT(pIStream);
	ASSERT(lpstr);
	ASSERT(0 < iLen);
	if (NULL == lpstr) return E_POINTER;
	if (0 == iLen) return E_INVALIDARG;

	USES_CONVERSION;

	*lpstr = '\0';

	try 
	{	// Variant liest sich selbst vom Stream
		CComVariant cv;// VariantInit()
		HRESULT hr = cv.ReadFromStream (pIStream);  
		if (FAILED(hr)) _com_issue_error(hr);
		// Richtigen Typ rausholen
		hr = cv.ChangeType (VT_BSTR);
		if (FAILED(hr)) _com_issue_error(hr);
		// Wert lesen
		CComBSTR bstr = cv.bstrVal; // SysAllocString(...
		LPSTR lpstrName = OLE2A(bstr.m_str);
		if (iLen < strlen(lpstrName)) _com_issue_error(E_INVALIDARG); 
		strcpy(lpstr, lpstrName);
		// in ~CComVariant() VariantClear()
	} // in ~CComBSTR() SysFreeString(m_str)
	catch (_com_error& e) 
	{
		return _COM_ERROR(e);
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
	if (NULL == pIDataObj)
		return S_FALSE;

HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		THROW_FAILED_HRESULT(pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects));

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg));

	// Einlesen des Enumerators aus den erhaltenen STGMEDIUM
		THROW_FAILED_HRESULT(CreateEnumLONGFromStream (stg.pstm, ppIEnumOut));
		ReleaseStgMedium (&stg);

	} catch (_com_error &e) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}	

return NOERROR;
}
// Dient zum Lesen der Daten (EnumLONG) vom Stream im Datenobjekt
HRESULT GetStringData (IDataObject *pIDataObj, LPSTR lpstr, int iLen)
{
	HRESULT hr = NOERROR;
	STGMEDIUM stg;
	memset (&stg, 0, sizeof(STGMEDIUM));
	
	try 
	{
	// Testen, ob das gewünschte Format überhaupt da ist
		THROW_FAILED_HRESULT(pIDataObj -> QueryGetData ((FORMATETC *)&c_feInitPropAct));

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feInitPropAct, &stg));

	// Einlesen des CComVariants aus den erhaltenen STGMEDIUM-Stream stg.pstm
		THROW_FAILED_HRESULT(CreateStringFromStream (stg.pstm, lpstr, iLen));

	// Freigeben Storagemedium
		ReleaseStgMedium (&stg);
	} 
	catch (_com_error& e) 
	{
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}	
	return hr;
}

// Hinzufügen eines HWND zu einem IDataObject ---------------------------------
HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj)
{
// hGlobal erzeugen
HGLOBAL hGlobal = GlobalAlloc (GHND, sizeof(HWND));

	if (!hGlobal) return E_OUTOFMEMORY;

HWND *pHWnd = (HWND *)GlobalLock (hGlobal);

	if (NULL == pHWnd) return E_OUTOFMEMORY;

	*pHWnd = hWnd;
	GlobalUnlock (hGlobal);

// diesen hGlobal im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_HGLOBAL;
	stg.hGlobal = hGlobal;
	stg.pUnkForRelease = NULL;
	return pDataObj -> SetData ((FORMATETC *)&c_feObjectWindow, &stg, true);
}

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
HRESULT hr = E_FAIL;
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		THROW_FAILED_HRESULT(pIDataObj -> QueryGetData ((FORMATETC *)&c_feObjectWindow));

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feObjectWindow, &stg));

	// HWND aus STGMEDIUM herauskopieren
	HWND *phWndGlobal = (HWND *)GlobalLock (stg.hGlobal);

		if (NULL == phWndGlobal)
			_com_issue_error(E_UNEXPECTED);

		*phWnd = *phWndGlobal;
		ReleaseStgMedium (&stg);

	} catch (_com_error &e) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}	
	return NOERROR;
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

