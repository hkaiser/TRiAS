// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "featurep.hxx"

#include <eonrguid.h>
#include <oprpguid.h>

#include <propactn.h>
#include <clsfyprp.h>

#include "enumonr.hxx"

// #define _DEBUG_ISTREAM
#if defined(_DEBUG_ISTREAM)
#include "strmhelp.hxx"
#endif // _DEBUG

DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);

// Funktionen für EnumLONG ////////////////////////////////////////////////////
// Serialisieren/DeSerialisieren eines IUnknowns ------------------------------
HRESULT CreateStreamOnHGlobalFromIUnknown (
		IUnknown *pIUnk, REFCLSID rClsID, IStream **ppIStream)
{
	*ppIStream = NULL;

// neuen Stream anlegen
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());
	
	if (FAILED(hr)) return hr;

#if defined(_DEBUG_ISTREAM)
	IStream = new CStreamWrapper (IStream);
#endif // _DEBUG

WPersistStream IPersStr = pIUnk;

	if (FAILED(GetLastHRESULT())) return GetLastHRESULT();

// den Enumerator wegschreiben
	hr = OleSaveToStream (IPersStr, IStream);
	if (FAILED(hr)) return hr;

// wieder zurück positionieren
LARGE_INTEGER li;

	LISet32 (li, 0L);
	hr = IStream -> Seek (li, STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) return hr;

	*ppIStream = IStream.detach();		// Resultat

return NOERROR;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (
		IStream *pIStream, REFCLSID rClsID, IEnum<LONG> **ppEnumOut)
{
HRESULT hr = ResultFromScode (E_FAIL);
CEnumObjectNumbers *pEnum = NULL; 

	*ppEnumOut = NULL;
	try {
	// Die ganze folgende Abfolge könnte durch 
	//	OleReadFromStream (...)
	// ersetzt werden, wenn unser Objekt CLSID_EnumObjectsByNumber
	// mit CoCreateInstance erzeugbar wäre.
	// Testen, ob dieser Stream wirklich was für uns enthält
	GUID guid;

		hr = ReadClassStm (pIStream, &guid);
		if (FAILED(hr)) throw hr;

		if (!(guid == rClsID))
		    	throw (hr = ResultFromScode (E_FAIL));	// falscher GUID

	// EnumeratorObjekt erzeugen
		pEnum = CEnumObjectNumbers::CreateInstance();
		if (NULL == pEnum) throw (hr = ResultFromScode (E_OUTOFMEMORY));

	// Enum füllen
	WPersistStream IPersStr = pEnum;

		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();

		hr = IPersStr -> Load (pIStream);
		if (FAILED(hr)) throw hr;

		*ppEnumOut = pEnum;	// übernimmt RefCnt

	} catch (HRESULT hr_result) {
		RELEASE(pEnum);
		return hr_result;
	}

return NOERROR;
}

// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnum<LONG> *pEnum, REFCLSID rClsID, IDataObject *pDataObj)
{
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

// lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetEnumLONGData (
		IDataObject *pIDataObj, REFCLSID rClsID, IEnum<LONG> **ppIEnumOut)
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

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, rClsID, ppIEnumOut);
		if (FAILED(hr)) throw hr;

		ReleaseStgMedium (&stg);

	} catch (HRESULT hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return hr_result;
	}	

return NOERROR;
}

// Funktionen für TARGETMERKMAL ///////////////////////////////////////////////
HRESULT ClonePropertyTemplate (ITriasXtensionSite *pXtnSite, LPCSTR pcName,
			       IPropertyTemplate **ppITempl)
{
HRESULT hr = ResultFromScode (E_FAIL);
WObjectProps IProps = pXtnSite;

	if (FAILED(GetLastHRESULT())) return GetLastHRESULT();

// Liste aller Objekteigenschaften besorgen
WEnumObjProps IEnum;

	hr = IProps -> EnumObjectProps (IEnum.ppi());
	if (FAILED(hr)) return hr;

// Wiederfinden der gegebenen Objekteigenschaft
WObjectProperty IProp;

	hr = IEnum -> FindByName (pcName, IProp.ppi());
	if (FAILED(hr)) return hr;

// Erzeugen der neuen Instanz der Objekteigenschaft
WPropertyTemplate ITempl = IProp;

	if (SUCCEEDED(GetLastHRESULT())) 
		hr = ITempl -> CloneTemplate (ppITempl);

return hr;
}

// Speichern einer Objekteigenschaft in einem DataObject als Stream -----------
HRESULT SetObjPropTemplate (ITriasXtensionSite *pXtnSite, os_string &strObjPropName, 
			    os_string &strObjProp, IDataObject *pIDO)
{
HRESULT hr = ResultFromScode (E_FAIL);

// PropertyTemplate generieren und initialisieren
WPropertyTemplate ITempl;

	hr = ClonePropertyTemplate (pXtnSite, strObjPropName.c_str(), ITempl.ppi());
	if (FAILED(hr)) return hr;

// Initialisieren dieser Objekteigenschaft mit unserem Template
	if (FAILED(GetLastHRESULT())) return GetLastHRESULT();
	ITempl -> SetTemplate (strObjProp.c_str());

// Stream mit PropertyTemplate generieren
WStream IStream;

	hr = CreateStreamOnHGlobalFromIUnknown (ITempl, CLSID_ObjPropFeature, IStream.ppi());
	if (FAILED(hr)) return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_ISTREAM;
	stg.pstm = IStream.detach();
	stg.pUnkForRelease = NULL;
	
	hr = pIDO -> SetData ((FORMATETC *)&c_feClassifyObjects, &stg, true);
	if (FAILED(hr)) return hr;

return NOERROR;
}

// Wiedereinlesen einer Objekteigenschaft aus einem DataObject ----------------
HRESULT CreateObjPropFromStream (ITriasXtensionSite *pXtnSite, 
			IStream *pIStream, IObjectProperty **ppIOProp)
{
	*ppIOProp = NULL;

// Die ganze folgende Abfolge könnte durch 
//	OleReadFromStream (...)
// ersetzt werden, wenn unsere ObjektEigenschaft
// mit CoCreateInstance erzeugbar wäre.
// Einlesen des CLSID der Objekteigenschaft
GUID guid;
HRESULT hr = ReadClassStm (pIStream, &guid);
	
	if (FAILED(hr)) return hr;

// Objekteigenschaft neu erzeugen
WObjectProperty IOProp;

	hr = pXtnSite -> CreateInstance (NULL, guid, 
			IID_IObjectProperty, IOProp.ppv());
	if (FAILED(hr)) return hr;	// nicht erzeugbar oder kein Template

// Objekteigenschaft initialisieren
	{
	WPersistStream IPersStr = IOProp;

		if (FAILED(GetLastHRESULT())) return GetLastHRESULT();

		hr = IPersStr -> Load (pIStream);
		if (FAILED(hr)) return hr;
	}

	*ppIOProp = IOProp.detach();

return NOERROR;
}

HRESULT GetObjProperty (ITriasXtensionSite *pXtnSite, 
		IDataObject *pIDataObj, IObjectProperty **ppIOProp)
{
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feClassifyObjects);
		if (NOERROR != hr) throw hr;	// Format nicht vorhanden

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feClassifyObjects, &stg);
		if (FAILED(hr)) throw hr;

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateObjPropFromStream (pXtnSite, stg.pstm, ppIOProp);
		if (FAILED(hr)) throw hr;

		ReleaseStgMedium (&stg);

	} catch (HRESULT hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return hr_result;
	}

return NOERROR;
}

