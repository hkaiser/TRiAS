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

	// Stream mit Variant generieren
	WStream IStream;

		RETURN_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, true, IStream.ppi()));
		RETURN_FAILED_HRESULT(rv.WriteToStream (IStream));	// Variant dort rein schreiben

	LARGE_INTEGER li;

		LISet32(li, 0L);
		RETURN_FAILED_HRESULT(IStream -> Seek (li, SEEK_SET, NULL));

	// diesen Stream im DataObject setzen
	STGMEDIUM stg;

		stg.tymed = TYMED_ISTREAM;
		stg.pstm = IStream.detach();
		stg.pUnkForRelease = NULL;

	HRESULT hr = pIDO -> SetData ((FORMATETC *)pcfe, &stg, true);

		if (FAILED(hr)) {
			ReleaseStgMedium (&stg);
			return hr;
		}
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

		// einlesen des Enumerators aus den erhaltenen STGMEDIUM
			THROW_FAILED_HRESULT(pv -> ReadFromStream (stg.pstm));
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

}	// namespace PropActBase
