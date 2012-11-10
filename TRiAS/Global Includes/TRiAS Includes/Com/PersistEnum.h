// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/30/1998 01:39:27 PM
//
// @doc
// @module PersistEnum.h | Speichern und laden eines Enumerators (aller seiner Elemente)

#if !defined(_PERSISTENUM_H__9A869E24_584B_11D2_9ED0_006008447800__INCLUDED_)
#define _PERSISTENUM_H__9A869E24_584B_11D2_9ED0_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden der Enumeratoren
template <class E, class T>
inline HRESULT LoadEnumeratedItems (E EnumToLoad, IStream *pStm, const FMTID *, T *)
{
	ASSERT(EnumToLoad.IsValid());		// Enumerator muß initialisiert sein

LONG lCnt = 0;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lCnt));
	if (lCnt > 0) {
	// alle ViewItems laden und zu dieser Ansicht hinzufügen
	__Interface<T> Item;

		for (long i = 0; i < lCnt; ++i)
		{
			if (SUCCEEDED(::OleLoadFromStream (pStm, Item.GetIID(), Item.ppv())))
			{
				RETURN_FAILED_HRESULT(EnumToLoad -> _Add(Item, VARIANT_TRUE));
			}
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Laden eines Enumerators mit callback für jedes 
// geladene Objekt
template<class T> 
class unary_initialize : 
	public os_unary_function<T, HRESULT> 
{
	typedef T unary_inititialize_target;
};

template <class E, class Predicate>
inline HRESULT LoadEnumeratedItemsEx (E EnumToLoad, IStream *pStm, const FMTID *, const Predicate &pred)
{
	ASSERT(EnumToLoad.IsValid());		// Enumerator muß initialisiert sein

LONG lCnt = 0;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lCnt));
	if (lCnt > 0) {
	// alle ViewItems laden und zu dieser Ansicht hinzufügen
	Predicate::unary_initialize_target Item;

		for (long i = 0; i < lCnt; ++i)
		{
			if (SUCCEEDED(::OleLoadFromStream (pStm, Item.GetIID(), Item.ppv())))
			{
			// evtl. zusätzliche Initialisierungen durchführen
				if (FAILED(pred(Item)))
					continue;		// dieser soll's wohl doch nicht sein
				RETURN_FAILED_HRESULT(EnumToLoad -> _Add(Item, VARIANT_TRUE));
			}
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion fürs Speichern der Enumeratoren
template<class E, class T>
inline HRESULT SaveEnumeratedItems (
	E EnumToSave, IStream *pStm, const FMTID *, T *, ULARGE_INTEGER *pli = NULL)
{
// evtl. aktuelle Position merken
	if (NULL != pli) {
	LARGE_INTEGER li;

		li.QuadPart = 0;
		pStm -> Seek (li, STREAM_SEEK_CUR, pli);
	}

// jetzt wegschreiben
LONG lCnt;
WEnumVARIANT Enum;
CComVariant var;

	if (SUCCEEDED(EnumToSave -> _NewEnum (Enum.ppu()))) {
	// Anzahl der Properties wegschreiben
		RETURN_FAILED_HRESULT(EnumToSave -> get_Count (&lCnt));
		RETURN_FAILED_HRESULT(SaveLong (pStm, lCnt));

	// einzelne Properties wegschreiben
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &var, NULL); /**/)
		{
			if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) {
			CComQIPtr<IPersistStream, &IID_IPersistStream> ps (V_UNKNOWN(&var));

				if (NULL != ps.p) ::OleSaveToStream (ps, pStm);
			}
		}
#pragma MESSAGE("TODO: Gespeicherte Anzahl der Items bei aufgetretenen Fehlern ggf. koorigieren.")
	}
	return S_OK;
}

#endif // !defined(_PERSISTENUM_H__9A869E24_584B_11D2_9ED0_006008447800__INCLUDED_)
