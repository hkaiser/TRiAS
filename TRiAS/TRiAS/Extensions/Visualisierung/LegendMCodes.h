// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.08.2000 22:07:05 
//
// @doc
// @module LegendMCodes.h | Declaration of the <c CLegendMCodes> class

#if !defined(_LEGENDMCODES_H__C81872CC_6CC6_41F9_821E_7BA68F06FFCC__INCLUDED_)
#define _LEGENDMCODES_H__C81872CC_6CC6_41F9_821E_7BA68F06FFCC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/set>

///////////////////////////////////////////////////////////////////////////////
// Menge aller MCodes, in denen Überschriften der Legende in einer Ansicht
// gespeichert sind
class CLegendMCodes :
	public set<INT_PTR, less<INT_PTR> >
{
public:
	CLegendMCodes (INT_PTR lMCode, LPCSTR pcView) : 
		m_lMCode(lMCode), m_strView(pcView) 
	{
	}
	~CLegendMCodes () 
	{ 
	}

// MCodes aus Merkmal holen
	HRESULT ExtractMCodes(LPCSTR pcMaster = NULL)
	{
	char cbBuffer[5*_MAX_PATH];

	// MasterAttribut lesen
		if (NULL == pcMaster) {
			cbBuffer[0] = '\0';
			if (!ReadTextMerkmal (TT_Sicht, (INT_PTR)m_strView.c_str(), m_lMCode, cbBuffer, sizeof(cbBuffer)))
				return S_FALSE;		// no MCodes at all
		} else {
			strcpy (cbBuffer, pcMaster);
		}

	// Anzahl der Merkmale holen
	LPSTR pMWert = cbBuffer;
	int iCnt = (int)strtoul (pMWert, &pMWert, 10);

		if (0 == iCnt) 
			return S_FALSE;

	// einzelne Merkmale extrahieren
		for (int i = 0; i < iCnt; i++) {
			while (*pMWert && !isdigit(*pMWert))
				pMWert++;
			if (*pMWert == '\0')
				break;
			insert(strtoul (pMWert, &pMWert, 10));
		}
		return (size() > 0) ? S_OK : S_FALSE;
	}

// schreibt die gespeicherten MCodes weg
	HRESULT WriteMCodes()
	{
		if (0 == size())
			return S_FALSE;

	// Attribut zusammenbauen
	os_string strMCodes;
	char cbBuffer[64];

		strMCodes = ultoa (size(), cbBuffer, 10);
		for (iterator it = begin(); it != end(); ++it) {
			strMCodes += ",";
			strMCodes += ultoa (*it, cbBuffer, 10);
		}

	// an der Ansicht wegschreiben
		if (!WriteTextMerkmal (TT_Sicht, (INT_PTR)m_strView.c_str(), m_lMCode, strMCodes.c_str()))
			return S_FALSE;

		return S_OK;
	}

// Testet, ob ein MCode bekannt ist
	bool HasMCode (INT_PTR lMCode)
	{
		return (end() != find (lMCode)) ? true : false;
	}

// Fügt MCode hinzu
	bool AddMCode (INT_PTR lMCode)
	{
	pair<iterator, bool> p = insert (lMCode);

		return p.second;
	}

private:
	INT_PTR m_lMCode;
	os_string m_strView;
};

#endif // !defined(_LEGENDMCODES_H__C81872CC_6CC6_41F9_821E_7BA68F06FFCC__INCLUDED_)
