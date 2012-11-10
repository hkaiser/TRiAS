// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/25/1998 09:29:39 AM
//
// @doc
// @module MerkmalsListe.cpp | Liste aller Merkmale eines Projektes/Datenbank
// $Log: $

#include "trias02p.hxx"

#include <MerkmalsListe.h>

CObjektMerkmalsListe::CObjektMerkmalsListe(ITRiASDatabase *pDB, BOOL fSystem, BOOL fAll)
	: m_DB(pDB), m_fIsSystem(fSystem), m_fAll(fAll)
{
}

CObjektMerkmalsListe::~CObjektMerkmalsListe()
{
}

// Memberfunktionen
HRESULT CObjektMerkmalsListe::EnumMerkmale (BOOL (CALLBACK *pFcn)(long, void *), void *pData)
{
	return S_OK;
}

HRESULT CObjektMerkmalsListe::EnumMerkmaleEx (BOOL (CALLBACK *pFcn)(long, DWORD, void *), void *pData)
{
	return S_OK;
}

