// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.06.99 15:09:40 
//
// @doc
// @module PersistEnumPropStream.h | Declaration of the <c CPersistEnumPropStream> class

#if !defined(_PERSISTENUMPROPSTREAM_H__0C9FD810_2A36_11D3_94F6_0080C786297B__INCLUDED_)
#define _PERSISTENUMPROPSTREAM_H__0C9FD810_2A36_11D3_94F6_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropertyBagOnStream.h>
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
// Helper
inline void Clear (STATPROPSTG *pData) { TIDY(pData, lpwstrName); }
typedef CStruct<STATPROPSTG> CStatPropStg;

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden eines Enumerators mit callback für jedes 
// geladene Objekt
template<class E, class Predicate>
inline HRESULT LoadEnumeratedItemsEx (
	E EnumToLoad, IStream *pStm, const FMTID *pfmtid, Predicate &pred, bool fUseZLib = false)
{
	ASSERT(!!EnumToLoad);		// Enumerator muß initialisiert sein

// jetzt einlesen
WPropertyBag Bag;
WEnumSTATPROPSTG Enum;

	RETURN_FAILED_HRESULT(::OpenPropertyBagOnIStream (pStm, *pfmtid, Bag.ppi(), Enum.ppi(), fUseZLib));

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
			_ASSERTE(V_VT(&vVal) == VT_BLOB_OBJECT);

		Predicate::unary_initialize_target Item;

			if (SUCCEEDED(::OleLoadFromBlob (&V_BLOB(&vVal), Item.GetIID(), Item.ppv())))
			{
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
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden eines Enumerators (wrapper für 'einfache' Form)
template<class E, class T>
inline HRESULT LoadEnumeratedItems (
	E EnumToLoad, IStream *pStm, const FMTID *pfmtid, T *, bool fUseZLib = false)
{
CDefaultInitItem<T> pred;

	return LoadEnumeratedItemsEx (EnumToLoad, pStm, pfmtid, pred, fUseZLib);
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Speichern eines Enumerators
template<class E, class Predicate>
inline HRESULT SaveEnumeratedItemsEx (
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

		THROW_FAILED_HRESULT(::CreatePropertyBagOnIStream (pStm, *pfmtid, Bag.ppi()));

	WEnumVARIANT Enum;
	CComVariant var;
	CComBSTR bstrName;

		if (SUCCEEDED(EnumToSave -> _NewEnum (Enum.ppu()))) {
		// einzelne Properties wegschreiben
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &var, NULL); /**/)
			{
				if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) {
				CComQIPtr<IPersistStream, &IID_IPersistStream> ps (V_UNKNOWN(&var));
				CBlob blobData;

					if (NULL != ps.p && SUCCEEDED(::OleSafeToBlob (ps, &blobData))) {
					CPropVariant vVal;

						V_VT(&vVal) = VT_BLOB_OBJECT;
						blobData.Detach(&V_BLOB(&vVal));

					// Namen des Objektes abfragen
					Predicate::binary_initialize_target Obj (V_UNKNOWN(&var));

						if (SUCCEEDED(pred (Obj, CLEARED(&bstrName)))) {
							_ASSERTE(bstrName.Length() > 0);
							Bag -> Write (bstrName, reinterpret_cast<VARIANT *>(&vVal));
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
inline HRESULT SaveEnumeratedItems (
	E EnumToSave, IStream *pStm, const FMTID *pfmtid, T *, ULARGE_INTEGER *pli = NULL)
{
CDefaultGetItemName<T> pred;

	return SaveEnumeratedItemsEx (EnumToSave, pStm, pfmtid, pred, pli);
}

#endif // !defined(_PERSISTENUMPROPSTREAM_H__0C9FD810_2A36_11D3_94F6_0080C786297B__INCLUDED_)
