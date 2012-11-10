// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.04.2000 09:14:29 
//
// @doc
// @module FreeMapForCompressedStream.h | Declaration of the <c CFreeMapForCompressedStream> class

#if !defined(_FREEMAPFORCOMPRESSEDSTREAM_H__4383DBB7_26AA_4CC6_A582_8299401764CB__INCLUDED_)
#define _FREEMAPFORCOMPRESSEDSTREAM_H__4383DBB7_26AA_4CC6_A582_8299401764CB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include <d_lib/d_lib.h>		// debug/tracing support

///////////////////////////////////////////////////////////////////////////////
// Daten in einen Stream Schreiben/von dort lesen
template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
	return pIStm -> Read (&riVal, sizeof(T), NULL);
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T const &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Map, die den freien Platz in einem Stream verwaltet
class CFreeMapForCompressedStream 
{
public:
	typedef multimap<ULONG, ULONG, less<ULONG> > CSizeMap;
	typedef CSizeMap::value_type value_type;

	CFreeMapForCompressedStream() : m_ulEndOfStream(0), m_ulChunkDelta(0) {}
	~CFreeMapForCompressedStream() {}

	CFreeMapForCompressedStream &operator= (const CFreeMapForCompressedStream &rhs)
	{
		if (&rhs != this) {
			m_ulEndOfStream = rhs.GetEndOfStream();
			m_ulChunkDelta = rhs.GetChunkDelta();
			m_SizeMap = rhs.GetSizeMap();
		}
		return *this;
	}

	enum FREEMAPCONSTS { 
		CHUNK_DELTA = 128, 
	
	// Versionsinfos
		FREEMAP_SIGNATURE = 0x50414d46,				// "FMAP"
		FREEMAP_VERSION_100 = 0x0100,
		FREEMAP_LASTVERSION = FREEMAP_VERSION_100,
	};

	HRESULT Initialize (ULONG ulEndOfStream = 0, ULONG ulChunkDelta = CHUNK_DELTA)
	{
		m_ulEndOfStream = ulEndOfStream;
		m_ulChunkDelta = ulChunkDelta;
		return S_OK;
	}

	bool Allocate (ULONG ulSize, pair<ULONG, ULONG> &p, bool &rfNew)
	{
		_ASSERTE(0 != m_ulChunkDelta);
		ulSize = ((ulSize/m_ulChunkDelta)+1)*m_ulChunkDelta;

	CSizeMap::iterator it = m_SizeMap.lower_bound(ulSize);	// first element that is not less than

		if (it != m_SizeMap.end()) {
			p.first = (*it).second;
			p.second = (*it).first;
			rfNew = false;		// wiederverwendeter slot
			m_SizeMap.erase(it);			// dieser Bereich ist jetzt nicht mehr frei
			return true;
		}

	// keine freien Blöcke der gewünschten Größe vorhanden
		p.first = m_ulEndOfStream;
		p.second = ulSize;
		rfNew = true;			// neuer slot
		m_ulEndOfStream += ulSize;
		return true;
	}
	bool Free (const pair<ULONG, ULONG> &p)
	{
	// Versuchen slot mit Nachbarslots zu vereinigen
	CSizeMap::value_type tofree (p.second, p.first);
	CSizeMap::iterator itleft = m_SizeMap.end(), itright = m_SizeMap.end();

		if (FindOffsets (p, itleft, itright)) {
			if (itright != m_SizeMap.end()) {
			// nächstfolgender slot ist auch frei
				tofree.first += (*itright).first;	// Offset bleibt gleich, size wird größer
				m_SizeMap.erase(itright);
			}

			if (itleft != m_SizeMap.end()) {
			// vorhergehender slot ist auch frei
				tofree.first += (*itleft).first;	// size wird größer
				tofree.second = (*itleft).second;	// offset steht auf vorherigem slot
				m_SizeMap.erase(itleft);
			}
		}

	// jetzt Gesamtbereich einfügen
	size_t iSize = m_SizeMap.size();

		m_SizeMap.insert (tofree);
		return (m_SizeMap.size() - iSize != 0) ? true : false;
	}

// Speichern/Laden dieser Struktur
	HRESULT Load (IStream *pIStrm)
	{
	// Signatur und Version prüfen
	ULONG ulSignature = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulSignature));
		if (ulSignature != FREEMAP_SIGNATURE) return E_UNEXPECTED;

	ULONG ulVersion = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulVersion));
		if (ulVersion > FREEMAP_LASTVERSION) return E_UNEXPECTED;

	// eigentliche Daten speichern
	ULONG ulCnt = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, m_ulEndOfStream));
		RETURN_FAILED_HRESULT(LoadData (pIStrm, m_ulChunkDelta));
		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulCnt));
		for (ULONG ul = 0; ul < ulCnt; ul++) {
		CSizeMap::value_type p;

			RETURN_FAILED_HRESULT(LoadData (pIStrm, p));
			m_SizeMap.insert (p);
		}
		return S_OK;
	}
	HRESULT Save (IStream *pIStrm)
	{
	// Signatur und Version speichern
		RETURN_FAILED_HRESULT(SaveData (pIStrm, FREEMAP_SIGNATURE));
		RETURN_FAILED_HRESULT(SaveData (pIStrm, FREEMAP_LASTVERSION));

	// eigentliche Daten speichern
	size_t ulCnt = m_SizeMap.size();

		RETURN_FAILED_HRESULT(SaveData (pIStrm, m_ulEndOfStream));
		RETURN_FAILED_HRESULT(SaveData (pIStrm, m_ulChunkDelta));
		RETURN_FAILED_HRESULT(SaveData (pIStrm, ulCnt));
		for (CSizeMap::iterator it = m_SizeMap.begin(); it != m_SizeMap.end(); ++it) {
		CSizeMap::value_type p = *it;
		
			RETURN_FAILED_HRESULT(SaveData (pIStrm, p));
			D_OUTF2(1, " offset: %08x", p.second, ", size: %04d", p.first);
		}
		return S_OK;
	}

	ULONG GetEndOfStream() const { return m_ulEndOfStream; }
	ULONG GetChunkDelta() const { return m_ulChunkDelta; }
	const CSizeMap &GetSizeMap() const { return m_SizeMap; }

protected:
// vorhergehenden und gegebenen slot finden
	bool FindOffsets (const pair<ULONG, ULONG> &p, CSizeMap::iterator &ritleft, CSizeMap::iterator &ritright)
	{
	int iFoundSomeThing = 0;

		for (CSizeMap::iterator it = m_SizeMap.begin(); it != m_SizeMap.end(); ++it) {
		// auf vorgehenden slot vergleichen
			if ((*it).second + (*it).first == p.first) {
				ritleft = it;
				if (++iFoundSomeThing == 2)
					break;	// beide gefunden
			}

		// auf nachfolgenden slot vergleichen
			if ((*it).second == p.first+p.second) {
				ritright = it;
				if (++iFoundSomeThing == 2)
					break;
			}
		}
		return iFoundSomeThing > 0 ? true : false;
	}

private:
	ULONG m_ulEndOfStream;
	ULONG m_ulChunkDelta;

	CSizeMap m_SizeMap;
};

#endif // !defined(_FREEMAPFORCOMPRESSEDSTREAM_H__4383DBB7_26AA_4CC6_A582_8299401764CB__INCLUDED_)
