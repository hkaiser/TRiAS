// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 22.04.99 15:06:23
//
// @doc
// @module PropertyActionBase.cpp | Funktionen für Handling des IDataObject's für 
// PropertySequences/PropertyChoices etc.

#include <Com/PropertyActionBaseData.h>
#include <Com/PropertyActionBaseDataImpl.cpp>
#include <Com/PropertyActionBase.h>
#include <Com/MemoryHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/ManageGlobalMemory.h>

#include <PacketNumber.h>
#include <ObjectPropertyInSeq.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);

namespace PropActBase {

///////////////////////////////////////////////////////////////////////////////
// STGMEDIUM enthält einen serialisierten EnumLONG, dazu können die folgenden
// Helperroutinen verwendet werden.

	// Serialisieren/DeSerialisieren eines IUnknowns 
	inline HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk, IStream **ppIStream)
	{
		if (NULL == ppIStream) 
			return E_POINTER;
		*ppIStream = NULL;

	// neuen Stream anlegen
	WStream IStream;

		RETURN_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, true, IStream.ppi()));
		COM_TRY {
		WPersistStream IPersStr (pIUnk);	// throws hr
		WStream StrClone;

		// den Enumerator wegschreiben
			THROW_FAILED_HRESULT(IStream->Clone(StrClone.ppi()));
			THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, StrClone));

		LARGE_INTEGER li;

			LISet32(li, 0L);
			THROW_FAILED_HRESULT(IStream -> Seek (li, SEEK_SET, NULL));

			*ppIStream = IStream.detach();		// Resultat

		} COM_CATCH;
		return S_OK;
	}

	// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
	inline HRESULT CreateEnumLONGFromStream (IStream *pIStream, REFIID riid, LPVOID *ppEnumOut)
	{
		if (NULL == ppEnumOut) 
			return E_POINTER;

		*ppEnumOut = NULL;
		COM_TRY {
		WStream StrClone;

			THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
			THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, riid, ppEnumOut));

		} COM_CATCH;
		return S_OK;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Helper für IEnumLONG

	// Hinzufügen eines EnumLONG zu einem IDataObject 
	HRESULT SetEnumObjects (IUnknown *pEnum, IDataObject *pDataObj)
	{
	// den Stream im DataObject setzen
	STGMEDIUM stg;

		ZeroMemory (&stg, sizeof(STGMEDIUM));
		COM_TRY {
		// Stream mit EnumLONG generieren
		WStream IStream;

			THROW_FAILED_HRESULT(CreateStreamOnHGlobalFromIUnknown (pEnum, IStream.ppi()));

			stg.tymed = TYMED_ISTREAM;
			stg.pstm = IStream.detach();
			stg.pUnkForRelease = NULL;

			THROW_FAILED_HRESULT(pDataObj -> SetData ((FORMATETC *)&c_feSelectedObjects, &stg, true));

		} COM_CATCH_OP(
			if (NULL != stg.pstm)
				ReleaseStgMedium (&stg);
		);
		return S_OK;
	}

	// Lesen eines EnumLONG aus einem DataObjekt 
	HRESULT GetEnumObjects (IDataObject *pIDataObj, REFIID riid, void **ppv)
	{
		if (NULL == pIDataObj) 
			return E_INVALIDARG;

	HRESULT hr = E_FAIL;
	STGMEDIUM stg;

		ZeroMemory (&stg, sizeof(STGMEDIUM));
		COM_TRY {
		// Testen, ob das gewünschte Format überhaupt da ist
			THROW_FAILED_HRESULT(hr = pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects));
			if (S_OK != hr) return hr;

			if (NULL == ppv)
				return S_OK;				// nur abfragen, ob Format vorhanden ist

		// Daten vom DataObject geben lassen
			THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg));

		// einlesen des Enumerators aus den erhaltenen STGMEDIUM
			THROW_FAILED_HRESULT(CreateEnumLONGFromStream (stg.pstm, riid, ppv));
			ReleaseStgMedium (&stg);

		} COM_CATCH_OP(
			if (TYMED_NULL != stg.tymed)
				ReleaseStgMedium (&stg);
		);
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
		if (NULL == pcfe || NULL == pIDO) 
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
// Initialisierung aus PropertyBagString
	HRESULT InitFromDataFormatETC (IUnknown *pIUnk, IDataObject *pIDO, const FORMATETC *pcfmt)
	{
		COM_TRY {
		CComVariant vData;

			if (SUCCEEDED(GetVariantData (pIDO, pcfmt, &vData))) {
				THROW_FAILED_HRESULT(vData.ChangeType (VT_BSTR));

				if (0 == SysStringLen (V_BSTR(&vData)))
					return S_FALSE;

			__Interface<IParseStringPairs> Bag (CLSID_ParseStringPairs);
			CComVariant v (DISP_E_PARAMNOTFOUND, VT_ERROR);	// no error log
			LONG lCount = 0;
			CComBSTR bstrData;

				if (*V_BSTR(&vData) != L';') 		// Data müssen mit ";PropActData" anfangen
					bstrData = L";PropActData;";

				bstrData += V_BSTR(&vData);

				THROW_FAILED_HRESULT(Bag -> put_Pattern (CComBSTR(L";%1=%2")));
				THROW_FAILED_HRESULT(Bag -> Parse (bstrData, &lCount));
				THROW_FAILED_HRESULT(Bag -> InitObject (pIUnk, v));
			}
		} COM_CATCH;
		return S_OK;
	}

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

// Hinzufügen eines HWND zu einem IDataObject 
	HRESULT SetHWND (HWND hWnd, IDataObject *pDataObj, const FORMATETC *pcfe)
	{
	STGMEDIUM stg;

		ZeroMemory (&stg, sizeof(STGMEDIUM));
		COM_TRY {
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

		} COM_CATCH_OP(
			if (TYMED_NULL != stg.tymed)
				ReleaseStgMedium (&stg);
		);
		return S_OK;
	}

// Lesen eines HWND aus einem DataObjekt 
	HRESULT GetHWND (IDataObject *pIDataObj, const FORMATETC *pcfe, HWND *phWnd)
	{
	HRESULT hr = E_FAIL;
	STGMEDIUM stg;

		ZeroMemory (&stg, sizeof(STGMEDIUM));
		COM_TRY {
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

		} COM_CATCH_OP(
			if (TYMED_NULL != stg.tymed)
				ReleaseStgMedium (&stg);
		);
		return S_OK;
	}

// Funktionen, die eine Objekteigenschaft schreiben/lesen
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

	HRESULT SetObjectProperty (IDataObject *pIDO, LPCSTR pcBuffer)
	{
		RETURN_FAILED_HRESULT(SetVariantData(CComVariant(pcBuffer), pIDO, &c_feDestObjectProperty));
		return S_OK;
	}

	HRESULT SetObjectProperty (IDataObject *pIDO, IObjectProperty *pIObjProp)
	{
	char cbBuffer[_MAX_PATH];

		RETURN_FAILED_HRESULT(pIObjProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL));
		RETURN_FAILED_HRESULT(SetObjectProperty (pIDO, cbBuffer));
		return S_OK;
	}

}	// namespace PropActBase
