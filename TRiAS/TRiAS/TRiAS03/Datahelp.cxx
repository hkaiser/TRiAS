// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/MemoryHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/ManageGlobalMemory.h>

#include <funcs03.h>
#include <eonrguid.h>
#include <oprpguid.h>
#include <xtsnguid.h>

#include <propactn.h>
#include <selobwnd.h>
#include <clsfyprp.h>
#include <PacketNumber.h>
#include <ObjectPropertyInSeq.h>

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

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen eines HWND zu einem IDataObject 
HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj)
{
	return SetHWND (hWnd, pDataObj, &c_feObjectWindow);
}

HRESULT SetHWND (HWND hWnd, IDataObject *pDataObj, const FORMATETC *pcfe)
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

		THROW_FAILED_HRESULT(pDataObj -> SetData ((FORMATETC *)pcfe, &stg, true));

	} catch (_com_error &e) {
		if (NULL != stg.hGlobal)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Lesen eines HWND aus einem DataObjekt 
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
	return GetHWND (pIDataObj, &c_feObjectWindow, phWnd);
}

HRESULT GetHWND (IDataObject *pIDataObj, const FORMATETC *pcfe, HWND *phWnd)
{
HRESULT hr = ResultFromScode (E_FAIL);
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC *)pcfe);
		if (S_OK != hr) _com_issue_error(hr);	// Format nicht vorhanden

		if (NULL == phWnd)
			return S_OK;				// nur Abfragen, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)pcfe, &stg);
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
//HRESULT LoadLong (IStream *pIStm, long &riVal)
//{
//	return pIStm -> Read (&riVal, sizeof(long), NULL);
//}

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

//HRESULT SaveLong (IStream *pIStm, long iVal)
//{
//	return pIStm -> Write (&iVal, sizeof(long), NULL);
//}

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
	if (NULL == pIDO || NULL == pcfe)
		return E_INVALIDARG;

STGMEDIUM stg;

	ZeroMemory(&stg, sizeof(STGMEDIUM));
	COM_TRY {
		stg.tymed = pcfe->tymed;
		if (TYMED_ISTREAM == stg.tymed) {
		// Stream mit Variant generieren
		WStream IStream;
		
			THROW_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, true, IStream.ppi()));
			THROW_FAILED_HRESULT(rv.WriteToStream (IStream));

		LARGE_INTEGER li;

			LISet32(li, 0L);
			THROW_FAILED_HRESULT(IStream -> Seek (li, SEEK_SET, NULL));

		// diesen Stream im DataObject setzen
			stg.pstm = IStream.detach();
			stg.pUnkForRelease = NULL;
		}
		else if (TYMED_HGLOBAL == stg.tymed) {
		CGlobalMem Mem(sizeof(VARIANT));

			{
			CGlobalMem::Lock<VARIANT> lock(Mem);

				memcpy(lock, &rv, sizeof(VARIANT));
			}

		CComObject<CManageGlobalMemory> *pMem = NULL;
		WUnknown Unk;

			THROW_FAILED_HRESULT(CComObject<CManageGlobalMemory>::CreateInstance(&pMem));
			Unk = pMem;		// pending AddRef();

			if (V_ISUNKNOWN(&rv) || V_ISDISPATCH(&rv)) {
				V_UNKNOWN(&rv) -> AddRef();
				THROW_FAILED_HRESULT(pMem -> InitGlobalMem(Mem.GetHandle(), V_UNKNOWN(&rv)));
			}
			else {
				THROW_FAILED_HRESULT(pMem -> InitGlobalMem(Mem.GetHandle()));
			}

			stg.hGlobal = Mem.GetHandle();
			stg.pUnkForRelease = Unk.detach();
			Mem.Detach();
		}
		else {
			_ASSERTE(TYMED_ISTREAM == stg.tymed || TYMED_HGLOBAL == stg.tymed);
		}

		THROW_FAILED_HRESULT(pIDO -> SetData ((FORMATETC *)pcfe, &stg, true));

	} COM_CATCH_OP(
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium(&stg);
	);
	return S_OK;
}

HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv)
{
	if (NULL == pIDO || NULL == pcfe) 
		return E_INVALIDARG;

STGMEDIUM stg;

	ZeroMemory (&stg, sizeof(STGMEDIUM));
	COM_TRY {
	// Testen, ob das gewünschte Format überhaupt da ist
	HRESULT hr = pIDO -> QueryGetData ((FORMATETC *)pcfe);

		if (S_OK != hr) return hr;		// Format nicht vorhanden
		if (NULL == pv) return S_OK;	// nur nachfragen

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDO -> GetData ((FORMATETC *)pcfe, &stg));
		_ASSERTE(pcfe->tymed & stg.tymed);		// sollte enthalten sein

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		if (TYMED_ISTREAM == stg.tymed) {
		LARGE_INTEGER li;

			li.QuadPart = 0;
			THROW_FAILED_HRESULT(stg.pstm -> Seek(li, STREAM_SEEK_SET, NULL));
			THROW_FAILED_HRESULT(pv -> ReadFromStream (stg.pstm));
		}
		else if (TYMED_HGLOBAL == stg.tymed) {
		CGlobalMem Mem;

			Mem.Attach(stg.hGlobal);
			if (NULL != Mem.GetHandle()) {
			CGlobalMem::Lock<VARIANT> lock (Mem);

				memcpy (pv, lock, sizeof(VARIANT));
			}
			Mem.Detach();		// wird von ReleaseStgMedium freigegeben
		}	
		else {
			_ASSERTE(TYMED_ISTREAM == stg.tymed || TYMED_HGLOBAL == stg.tymed);
		}
		ReleaseStgMedium (&stg);

	} COM_CATCH_OP(
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Paketnummer behandeln
HRESULT GetPacketNumber (IDataObject *pIDO, long *plNumber)
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
HRESULT SetPacketNumber (IDataObject *pIDO, long lNumber)
{
	RETURN_FAILED_HRESULT(SetVariantData(CComVariant(lNumber), pIDO, &c_fePacketNumber));
	return S_OK;
}

// Paketnummer setzen/lesen
HRESULT GetObjectProperty (IDataObject *pIDO, IObjectProperty **ppIObjProp)
{
	if (NULL == ppIObjProp)
		return E_POINTER;
	*ppIObjProp = NULL;

CComVariant vObjProp;
HRESULT hr = E_FAIL;

	if (SUCCEEDED(GetVariantData(pIDO, &c_feDestObjectProperty, &vObjProp))) {
	// Liste der Objekteigenschaften initialisieren
	__Interface<IObjectProps> Props;

		DEX_GetObjectProps (Props.ppi());
		if (Props.IsValid() && SUCCEEDED(vObjProp.ChangeType(VT_BSTR))) {
		// evtl. alle ObjProps installieren
		__Interface<IEnumObjProps> EnumProps;
		
			hr = Props -> EnumObjectProps (EnumProps.ppi());
			if (SUCCEEDED(hr)) {
				USES_CONVERSION;
				hr = EnumProps -> FindByName (OLE2A(V_BSTR(&vObjProp)), ppIObjProp);
			}
		}
	}
	return hr;
}

HRESULT SetObjectProperty (IDataObject *pIDO, IObjectProperty *pIObjProp)
{
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(pIObjProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL));
	RETURN_FAILED_HRESULT(SetObjectProperty (pIDO, cbBuffer));
	return S_OK;
}

HRESULT SetObjectProperty (IDataObject *pIDO, LPCSTR pcName)
{
	RETURN_FAILED_HRESULT(SetVariantData(CComVariant(pcName), pIDO, &c_feDestObjectProperty));
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
