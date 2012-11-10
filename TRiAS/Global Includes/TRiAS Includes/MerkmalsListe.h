// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/25/1998 09:22:34 AM
//
// @doc
// @module MerkmalsListe.h | Liste aller Merkmale eines Objektes bzw. eines Projektes/Datenbank
// $Log: $

#if !defined(_MERKMALSLISTE_H__071744B3_F3A0_11D1_862D_00600875138A__INCLUDED_)
#define _MERKMALSLISTE_H__071744B3_F3A0_11D1_862D_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// alle Features eines Objektes enumerieren

class CObjectMerkmalsListe :
	public CMerkmalsListe
{
private:
	bool m_fAll;
	bool m_fIsSystem;
	INT_PTR m_lONr;

public:
	CObjectMerkmalsListe(INT_PTR lONr, BOOL fSystem = TRUE, BOOL fAll = FALSE)
		: CMerkmalsListe(fSystem, fAll), m_lONr(lONr) {}
	~CObjectMerkmalsListe() {}

// Memberfunktionen
	_TRIAS02_ENTRY HRESULT EnumMerkmale (BOOL (CALLBACK *pFcn)(INT_PTR, void *), void *pData);
	_TRIAS02_ENTRY HRESULT EnumMerkmaleEx (BOOL (CALLBACK *pFcn)(INT_PTR, DWORD, void *), void *pData);
	_TRIAS02_ENTRY HRESULT GetMerkmalsText (INT_PTR lMCode);

	BOOL IsSystem (void) { return m_fIsSystem ? TRUE : FALSE; }
	BOOL ContainesAll (void) { return m_fAll ? TRUE : FALSE; }
};

#endif // !defined(_MERKMALSLISTE_H__071744B3_F3A0_11D1_862D_00600875138A__INCLUDED_)
