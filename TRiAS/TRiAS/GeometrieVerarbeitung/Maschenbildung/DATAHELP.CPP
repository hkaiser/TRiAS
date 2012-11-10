// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CPP

#include "pheader.h"		// vorübers. Header

#include <ospace/com/iterenum.h>

#include <Com/MemoryHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/ManageGlobalMemory.h>

#include <triashelper.h>		
#include <eonrguid.h>
#include <initguid.h>

#include <propactn.h>
#include <hpp/datahelp.hpp>		// zugeh. Header

//#if _MSC_VER >= 1200
//#include <Com/PropertyActionBaseDataImpl.cpp>
//#endif // _MSC_VER >= 1200

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
		if (FAILED(hr)) _com_issue_error (hr);

	// wieder zurück positionieren
	LARGE_INTEGER li;

		LISet32 (li, 0L);
		hr = IStream -> Seek (li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr)) _com_issue_error (hr);

		*ppIStream = IStream.detach();		// Resultat

	} catch (_com_error& hr) {
		return _COM_ERROR (hr);
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
		if (NOERROR != hr) _com_issue_error (hr);	// Format nicht vorhanden

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg);
		if (FAILED(hr)) _com_issue_error (hr);

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, ppIEnumOut);
		if (FAILED(hr)) _com_issue_error (hr);

		ReleaseStgMedium (&stg);

	} catch (_com_error& hr_result) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR (hr_result);
	}	

return NOERROR;
}

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

