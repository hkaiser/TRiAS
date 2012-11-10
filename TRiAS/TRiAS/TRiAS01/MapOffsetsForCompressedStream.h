// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.04.2000 21:56:29 
//
// @doc
// @module MapOffsetsForCompressedStream.h | Declaration of the <c CMapOffsetsForCompressedStream> class

#if !defined(_MAPOFFSETSFORCOMPRESSEDSTREAM_H__2453CD5A_864F_4575_A466_909AC8BB497B__INCLUDED_)
#define _MAPOFFSETSFORCOMPRESSEDSTREAM_H__2453CD5A_864F_4575_A466_909AC8BB497B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <d_lib/d_lib.h>		// debug/tracing support

///////////////////////////////////////////////////////////////////////////////
// 
class CMapOffsetPair :
	public pair<ULONG, ULONG>
{
public:
	CMapOffsetPair(ULONG ulFirst = 0, ULONG ulSecond = 0) { first = ulFirst; second = ulSecond; }
	CMapOffsetPair(const pair<ULONG, ULONG> &p) { first = p.first; second = p.second; }

	bool operator!() { return 0 == first && 0 == second; }
	bool IsValid() { return !!(*this); }
};

class CMapOffsets :
	public vector<CMapOffsetPair>
{
public:
	typedef vector<CMapOffsetPair> CMapOffsetsBase;
	typedef CMapOffsetPair value_type;

// Anfangs 4 Einträge in OffsetTable
	CMapOffsets() : vector<CMapOffsetPair>(4), m_ulBlockSize(0) {}
	~CMapOffsets() {}

	CMapOffsets &operator= (const CMapOffsets &rhs) 
	{
		if (&rhs != this) {
			*((CMapOffsetsBase *)this) = rhs;
			m_ulBlockSize = rhs.GetBlockSize();
		}
		return *this;
	}

	enum MAPOFFSETCONSTS { 
	// Versionsinfos
		MAPOFFSET_SIGNATURE = 0x46464f4d,				// "MOFF"
		MAPOFFSET_VERSION_100 = 0x0100,
		MAPOFFSET_LASTVERSION = MAPOFFSET_VERSION_100,
	};

	HRESULT Initialize (ULONG ulBlockSize) { m_ulBlockSize = ulBlockSize; return S_OK; }

// Helperfunktionen
	ULONG GetBlockSize() const { return m_ulBlockSize; }
	ULONG AlignToBlockOffset (ULONG ulPos) { return (ulPos/m_ulBlockSize)*m_ulBlockSize; }

// Zugriffsfunktionen
	value_type GetOffsetAndSize(ULONG ulOffset) 
	{ 
	int iIndex = ulOffset/m_ulBlockSize;

		if (iIndex >= size())
			return value_type(0, 0);
		return (*this)[iIndex]; 
	}
	void SetOffsetAndSize (ULONG ulOffset, const value_type &p) 
	{ 
	int iIndex = ulOffset/m_ulBlockSize;

		if (iIndex >= size())
			resize(max(iIndex+1UL, 2UL*size(), less<ULONG>()));
		(*this)[iIndex] = p; 
	}

// Persistenz
	HRESULT Load (IStream *pIStrm)
	{
	// Signatur und Version prüfen
	ULONG ulSignature = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulSignature));
		if (ulSignature != MAPOFFSET_SIGNATURE) return E_UNEXPECTED;

	ULONG ulVersion = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulVersion));
		if (ulVersion > MAPOFFSET_LASTVERSION) return E_UNEXPECTED;

	// eigentliche Daten speichern
	ULONG ulCnt = 0;

		RETURN_FAILED_HRESULT(LoadData (pIStrm, m_ulBlockSize));
		RETURN_FAILED_HRESULT(LoadData (pIStrm, ulCnt));
		for (ULONG ul = 0; ul < ulCnt; ul++) {
		CMapOffsetPair p;

			RETURN_FAILED_HRESULT(LoadData (pIStrm, p));
			if (ul >= size())
				resize(max(4UL, 2UL*size(), less<ULONG>()));
			(*this)[ul] = p;
		}
		return S_OK;
	}
	HRESULT Save (IStream *pIStrm)
	{
	// Signatur und Version speichern
		RETURN_FAILED_HRESULT(SaveData (pIStrm, MAPOFFSET_SIGNATURE));
		RETURN_FAILED_HRESULT(SaveData (pIStrm, MAPOFFSET_LASTVERSION));

	// eigentliche Daten speichern
	ULONG ulCnt = size();

		RETURN_FAILED_HRESULT(SaveData (pIStrm, m_ulBlockSize));
		RETURN_FAILED_HRESULT(SaveData (pIStrm, ulCnt));
		for (iterator it = begin(); it != end(); ++it) {
		CMapOffsetPair p = *it;

			RETURN_FAILED_HRESULT(SaveData (pIStrm, p));
			D_OUTF2(1, " offset: %08x", p.first, ", size: %04d", p.second);
		}
		return S_OK;
	}

private:
	ULONG m_ulBlockSize;		// PageGröße
};

#endif // !defined(_MAPOFFSETSFORCOMPRESSEDSTREAM_H__2453CD5A_864F_4575_A466_909AC8BB497B__INCLUDED_)
