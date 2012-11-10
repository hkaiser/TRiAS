// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/17/1998 05:47:18 PM
//
// @doc
// @module PersistEnumPropStg.h | Speichern und laden eines Enumerators (aller seiner 
// Elemente mit Hilfe eines PropertyStg-Objektes)

#if !defined(_PERSISTENUMPROPSTG_H__7CD55715_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _PERSISTENUMPROPSTG_H__7CD55715_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/PropertyBagOnStream.h>
#include <Com/PropertyBagOnStorage.h>
#include <Com/DefaultInitItem.h>

#include <Com/VariantHelpers.h>
#include <Com/CStructHelper.h>

#if !defined(_FMTID_ENUMERATEDITEMS)
#define _FMTID_ENUMERATEDITEMS

///////////////////////////////////////////////////////////////////////////////
// {7CD55716-6427-11D2-9EDE-006008447800}
extern "C" const FMTID __declspec(selectany) FMTID_EnumeratedItems = 
	{0x7cd55716,0x6427,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

#endif // _FMTID_ENUMERATEDITEMS

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden eines Enumerators mit callback für jedes 
// geladene Objekt
template<class E, class Predicate>
inline HRESULT LoadEnumeratedItemsStgEx (
	E EnumToLoad, IStream *pStm, const FMTID *pfmtid, Predicate &pred, bool fUseZLib = false)
{
	ASSERT(!!EnumToLoad);		// Enumerator muß initialisiert sein

// jetzt einlesen
WPropertyBag Bag;
WEnumSTATPROPSTG Enum;

	RETURN_FAILED_HRESULT(::OpenPropertyBagOnIStorage (pStm, *pfmtid, Bag.ppi(), Enum.ppi(), fUseZLib));

// einzelne Properties einlesen
CStatPropStg stg;

	for (Enum -> Reset(); S_OK == Enum -> Next (1, &stg, NULL); /**/)
	{
	CPropVariant vVal;

		if (NULL == stg.lpwstrName) {
//			_ASSERTE(NULL != stg.lpwstrName);	// PropStg: no name for entry given
			continue;							// Property muß Namen zugeordnet haben
		}

		if (SUCCEEDED(Bag -> Read (stg.lpwstrName, reinterpret_cast<VARIANT *>(CLEARED(&vVal)), NULL))) { 
		Predicate::unary_initialize_target Item;
		HRESULT hr = S_OK;

			if (V_ISBLOB_OBJECT(&vVal)) {
			// Objekt als Blob gespeichert
				if (FAILED(hr = ::OleLoadFromBlob (&V_BLOB_OBJECT(&vVal), Item.GetIID(), Item.ppv()))) {
					_ASSERTE(SUCCEEDED(hr));
					continue;
				}
			} else if (V_ISSTREAMED_OBJECT(&vVal)) {
			// Objekt über IPersistStream gespeichert
				if (FAILED(hr = ::OleLoadFromStream (V_STREAMED_OBJECT(&vVal), Item.GetIID(), Item.ppv()))) {
					_ASSERTE(SUCCEEDED(hr));
					continue;
				}
			} else {
				_ASSERTE(V_ISBLOB_OBJECT(&vVal) || V_ISSTREAMED_OBJECT(&vVal));
			}

		// evtl. zusätzliche Initialisierungen durchführen
			if (FAILED(pred(Item)))
				continue;		// dieser soll's wohl doch nicht sein

		// evtl. existierende Kopie im Enumerator sauber ersetzen
		Predicate::unary_initialize_target Dummy;
		CComVariant vName (stg.lpwstrName);		// ist gleichzeitig Name des Objektes

			if (SUCCEEDED(EnumToLoad -> Item (vName, Dummy.ppi())))
				EnumToLoad -> Remove (vName);
			EnumToLoad -> _Add (Item, VARIANT_TRUE);
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden eines Enumerators (wrapper für 'einfache Form')
template<class E, class T>
inline HRESULT LoadEnumeratedItemsStg (
	E EnumToLoad, IStream *pStm, const FMTID *pfmtid, T *, bool fUseZLib = false)
{
CDefaultInitItem<T> pred;

	return LoadEnumeratedItemsStgEx (EnumToLoad, pStm, pfmtid, pred, fUseZLib);
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Speichern eines Enumerators
template<class E, class Predicate>
inline HRESULT SaveEnumeratedItemsStgEx (
	E EnumToSave, IStream *pStm, const FMTID *pfmtid, Predicate &pred, ULARGE_INTEGER *pli = NULL)
{
// evtl. aktuelle Position merken
	if (NULL != pli) {
	LARGE_INTEGER li;

		li.QuadPart = 0;
		pStm -> Seek (li, STREAM_SEEK_CUR, pli);
	}

// jetzt wegschreiben
	COM_TRY {
	WPropertyBag Bag;
	WStorage Stg;

		THROW_FAILED_HRESULT(::CreatePropertyBagOnIStorage (pStm, *pfmtid, Bag.ppi(), Stg.ppi()));

	WEnumVARIANT Enum;
	CComVariant var;
	CComBSTR bstrName;

		if (SUCCEEDED(EnumToSave -> _NewEnum (Enum.ppu()))) {
		// einzelne Properties wegschreiben
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/)
			{
				if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) {
				CComQIPtr<IPersistStream, &IID_IPersistStream> ps (V_UNKNOWN(&var));
				Predicate::binary_initialize_target Obj (V_UNKNOWN(&var));		// Namen des Objektes abfragen

					if (SUCCEEDED(pred (Obj, CLEARED(&bstrName)))) {
						_ASSERTE(bstrName.Length() > 0);	// Name muß gegeben sein
						_ASSERTE(NULL != ps.p);				// Objekt muß IPersistStream unterstützen

					// Stream anlegen und IStream geben lassen, danach speichern
					CPropVariant vVal;

						V_VT(&vVal) = VT_STREAMED_OBJECT;
						V_STREAMED_OBJECT(&vVal) = NULL;
						if (SUCCEEDED(Bag -> Write (bstrName, reinterpret_cast<VARIANT *>(&vVal))) &&
							SUCCEEDED(Bag -> Read (bstrName, reinterpret_cast<VARIANT *>(CLEARED(&vVal)), NULL))) 
						{
							THROW_FAILED_HRESULT(::OleSaveToStream (ps, V_STREAMED_OBJECT(&vVal)));
						}
					}
				}
			}
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Speichern eines Enumerators (wrapper für einfache Form)
template<class E, class T>
inline HRESULT SaveEnumeratedItemsStg (
	E EnumToSave, IStream *pStm, const FMTID *pfmtid, T *, ULARGE_INTEGER *pli = NULL)
{
CDefaultGetItemName<T> pred;

	return SaveEnumeratedItemsStgEx (EnumToSave, pStm, pfmtid, pred, pli);
}

#endif // !defined(_PERSISTENUMPROPSTG_H__7CD55715_6427_11D2_9EDE_006008447800__INCLUDED_)
