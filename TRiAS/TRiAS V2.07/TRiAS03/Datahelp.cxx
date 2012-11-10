// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs03.h>
#include <eonrguid.h>
#include <oprpguid.h>
#include <xtsnguid.h>

#include <propactn.h>
#include <selobwnd.h>
#include <clsfyprp.h>

#include "DataHelp.h"
#include "enumonr.hxx"

// #define _DEBUG_ISTREAM
#if defined(_DEBUG_ISTREAM)
#include "strmhelp.hxx"
#endif // _DEBUG

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(ObjectProps);		// WObjectProps
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(PropertyTemplate);

///////////////////////////////////////////////////////////////////////////////
// STGMEDIUM enthält einen serialisierten EnumLONG, dazu können die folgenden
// Helperroutinen verwendet werden.

// Funktionen für EnumLONG ////////////////////////////////////////////////////
// Serialisieren/DeSerialisieren eines IUnknowns ------------------------------
HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk, IStream **ppIStream)
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

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, REFIID riid, LPVOID *ppEnumOut)
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

// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnum<LONG> *pEnum, IDataObject *pDataObj)
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

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut)
{
	return GetEnumLONGData (pIDataObj, IID_IEnumLONG, (LPVOID *)ppIEnumOut);
}

HRESULT GetEnumLONGData (IDataObject *pIDataObj, REFIID riid, LPVOID *ppv)
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

// Hinzufügen eines HWND zu einem IDataObject ---------------------------------
HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj)
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

// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feObjectWindow);
		if (S_OK != hr) _com_issue_error(hr);	// Format nicht vorhanden

		if (NULL == phWnd)
			return S_OK;				// nur Abfragen, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feObjectWindow, &stg);
		if (FAILED(hr)) _com_issue_error(hr);

	// HWND aus STGMEDIUM herauskopieren
	HWND *phWndGlobal = (HWND *)GlobalLock (stg.hGlobal);

		if (NULL == phWndGlobal)
			throw ResultFromScode (E_UNEXPECTED);

		*phWnd = *phWndGlobal;
		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(hr_result);
	}	

return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// StreamHelper
HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

HRESULT LoadString (IStream *pIStm, os_string &rStr)
{
long lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

char cbBuffer[256];

	TX_ASSERT(lCnt < sizeof(cbBuffer));
	hr = pIStm -> Read (cbBuffer, lCnt, NULL);
	if (FAILED(hr)) return hr;

	rStr = cbBuffer;
	return S_OK;
}

HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

HRESULT SaveString (IStream *pIStm, os_string str)
{
long lCnt = str.size()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

DWORD GetSizeMax (os_string &rStr)
{
	return rStr.size() + sizeof(long) + 1;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für TARGETMERKMAL 
HRESULT ClonePropertyTemplate (
	LPCSTR pcName, IPropertyTemplate **ppITempl)
{
	try {
	// Liste aller Objekteigenschaften besorgen
	WObjectProps IProps;
	BOOL fMustReInit = DEX_GetObjectProps (IProps.ppi());

		if (NULL != (IUnknown *)IProps) {
		// evtl. alle ObjProps installieren
			if (fMustReInit) {
				IProps -> OnNewReferenceObject (-1L);	// alles bisherige löschen
				THROW_FAILED_HRESULT(IProps -> OnNewReferenceObject (0L)); 
				DEX_SetMustInitOPFs(FALSE);
			}
		}

	WEnumObjProps IEnum;

		THROW_FAILED_HRESULT(IProps -> EnumObjectProps (IEnum.ppi()));

	// Wiederfinden der gegebenen Objekteigenschaft
	WObjectProperty IProp;

		THROW_FAILED_HRESULT(IEnum -> FindByName (pcName, IProp.ppi()));

	// Erzeugen der neuen Instanz der Objekteigenschaft
	WPropertyTemplate ITempl (IProp);

		if (SUCCEEDED(IProp -> QueryInterface (IID_IPropertyTemplate, ITempl.ppv()))) 
		{
			THROW_FAILED_HRESULT(ITempl -> CloneTemplate (ppITempl));
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Speichern einer Objekteigenschaft in einem DataObject als Stream 
HRESULT SetObjPropTemplate (
	os_string &strObjPropName, os_string &strObjProp, IDataObject *pIDO)
{
STGMEDIUM stg;

	ZeroMemory (&stg, sizeof(STGMEDIUM));
	try {
	// PropertyTemplate generieren und initialisieren
	WPropertyTemplate ITempl;
	HRESULT hr = ClonePropertyTemplate (strObjPropName.c_str(), ITempl.ppi());

		if (FAILED(hr)) return S_OK;	// ObjProp unterstützt diese Operation nicht

	// Initialisieren dieser Objekteigenschaft mit unserem Template
		THROW_FAILED_HRESULT(ITempl -> SetTemplate (strObjProp.c_str()));

	// Stream mit PropertyTemplate generieren
	WStream IStream;

		THROW_FAILED_HRESULT(CreateStreamOnHGlobalFromIUnknown (ITempl, IStream.ppi()));

	// diesen Stream im DataObject setzen
		stg.tymed = TYMED_ISTREAM;
		stg.pstm = IStream.detach();
		stg.pUnkForRelease = NULL;
		
		THROW_FAILED_HRESULT(pIDO -> SetData ((FORMATETC *)&c_feClassifyObjects, &stg, true));

	} catch (_com_error &e) {
		if (NULL != stg.pstm)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
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

#if 0
/////////////////////////////////////////////////////////////////////////////
// Wiedereinlesen einer Objekteigenschaft aus einem DataObject 
HRESULT CreateObjPropFromStream (ITriasXtensionSite *pXtnSite, IStream *pIStream, IObjectProperty **ppIOProp)
{
	if (NULL == ppIOProp) return E_POINTER;

	*ppIOProp = NULL;

// Die ganze folgende Abfolge könnte durch OleReadFromStream (...)
// ersetzt werden, wenn unsere ObjektEigenschaft mit CoCreateInstance erzeugbar wäre.
	try {
	// Einlesen des CLSID der Objekteigenschaft
	GUID guid;

		THROW_FAILED_HRESULT(ReadClassStm (pIStream, &guid));

	// Objekteigenschaft neu erzeugen
	WObjectProperty IOProp;

		THROW_FAILED_HRESULT(pXtnSite -> CreateInstance (NULL, guid, IID_IObjectProperty, IOProp.ppv()));

	// Objekteigenschaft initialisieren
		{
		WPersistStream IPersStr (IOProp);

			THROW_FAILED_HRESULT(IPersStr -> Load (pIStream));
		}
		*ppIOProp = IOProp.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT GetObjProperty (ITriasXtensionSite *pXtnSite, IDataObject *pIDataObj, IObjectProperty **ppIOProp)
{
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feClassifyObjects);

		if (S_OK != hr) _com_issue_error(hr);	// Format nicht vorhanden

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feClassifyObjects, &stg));

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		THROW_FAILED_HRESULT(CreateObjPropFromStream (pXtnSite, stg.pstm, ppIOProp));

		ReleaseStgMedium (&stg);

	} catch (_com_error &e) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}
	return S_OK;
}
#endif // 0
