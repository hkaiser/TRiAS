// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.06.99 14:36:08 
//
// @doc
// @module TRiASUtil.h | Helper Funktionen

#if !defined(_TRIASUTIL_H__DE7F5860_27D5_11D3_94F1_0080C786297B__INCLUDED_)
#define _TRIASUTIL_H__DE7F5860_27D5_11D3_94F1_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Finden eines besonderen Parents in der Objekthierarchie über einem gegebenen
// Objekt
template<class T>
inline HRESULT FindSpecificParent (T ParentIn, REFIID riid, void **ppIObj)
{
__Interface<IDispatch> Parent(ParentIn);

	while (Parent.IsValid()) {
		if (SUCCEEDED(Parent -> QueryInterface(riid, ppIObj)))
			return S_OK;			// gesuchtes Objekt gefunden

	// eine Etage weiter hoch
	__Interface<ITRiASBase> ParT;

		if (FAILED(Parent -> QueryInterface(ParT.ppi())))
			return E_UNEXPECTED;	// snh

		RETURN_FAILED_HRESULT(ParT -> get_Parent (Parent.ppi()));
	}
	return E_UNEXPECTED;
}

template<class T1, class T2>
inline HRESULT FindSpecificParent (T1 ParentIn, T2 **ppIObj)
{
	return FindSpecificParent (ParentIn, __uuidof(T2), reinterpret_cast<void **>(ppIObj));
}

///////////////////////////////////////////////////////////////////////////////
// Handle der übergeordneten Datenbank abfragen
template<class T>
inline HRESULT GetDatabaseHandle (T Child, HPROJECT *phPr, IDispatch **ppIDisp = NULL)
{
	COM_TRY {
	__Interface<ITRiASDatabase> DBase;

		THROW_FAILED_HRESULT(FindSpecificParent(Child, DBase.ppi()))
		THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)phPr));

		if (NULL != ppIDisp)
			*ppIDisp = DBase.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Handle der übergeordneten Datenbank abfragen
template<class T>
inline HRESULT GetDatabaseOrProjectHandle (T Child, HPROJECT *phPr, IDispatch **ppIDisp = NULL)
{
	COM_TRY {
	__Interface<ITRiASDatabase> DBase;

		if (SUCCEEDED(FindSpecificParent (Child, DBase.ppi()))) {
		// 'normale' Objektklasse
			RETURN_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)phPr));
			if (NULL != ppIDisp)
				*ppIDisp = DBase.detach();
		} 
		else {
		// evtl. Zuordnungsobjektklasse
		__Interface<ITRiASProject> Prj;

			RETURN_FAILED_HRESULT(FindSpecificParent (Child, Prj.ppi()));
			*phPr = HACTPROJECT;
			if (NULL != ppIDisp)
				*ppIDisp = Prj.detach();
		}

	} COM_CATCH;
	return S_OK;
}

#endif // !defined(_TRIASUTIL_H__DE7F5860_27D5_11D3_94F1_0080C786297B__INCLUDED_)
