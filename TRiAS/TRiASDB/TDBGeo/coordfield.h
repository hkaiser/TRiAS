///////////////////////////////////////////////////////////////////////////
// @doc
// @module coordfield.h | Description goes here

#if !defined(_COORDFIELD_H__C77EE753_4183_11D2_8C7E_006097A8F384__INCLUDED_)
#define _COORDFIELD_H__C77EE753_4183_11D2_8C7E_006097A8F384__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// class definition for coordfield
// wrapper class for storing x,y,z-data in a field	(storing mechanism may be exchanged)
// definitons are inline for fast usage

const ULONG c_nNewPlaces = 128;
const ULONG c_nInitPlaces = 10;	// die mittlere Stützpunktanzahl ist 5-8

#include <float.h>		// DBL_MAX #AK981119

// Implementation as double field (should be the fastest)
class CCoordField
{
public:
	CCoordField()
	{
	// this entries will force methods to allocate new mem
		m_nMaxCount = 0;
		m_nUsed		 = 0;
		m_pCoords   = NULL;
	}
	~CCoordField()
	{
		delete m_pCoords;
		m_pCoords = NULL;
	}

	HRESULT SetPlace(ULONG newMaxCount) // try to allocate mem for newMaxIndex entries
	{
		// sorry, but i really need more
		if (newMaxCount > m_nMaxCount)
		{
		CSCOORD *t_pCoords = NULL;

			ATLTRY(t_pCoords = new CSCOORD[newMaxCount]);
			if (NULL == t_pCoords)		// oops, you lost all your credits try again
				return E_OUTOFMEMORY;

			if (NULL != m_pCoords)
			{
			// don't leave memleaks
				memcpy(t_pCoords, m_pCoords, m_nUsed * sizeof(CSCOORD));
				delete m_pCoords;
			}
			m_pCoords = t_pCoords;		// use new mem
			m_nMaxCount = newMaxCount;	// great, i can use more mem
		}
		return S_OK;					// thanks to you
	}

// Get a pointer to data (ATTN: not thread  safe!)
	HRESULT Get (ULONG index, CSCOORD **ppCoords)
	{
	// be careful not tested pointer parameter (in release)
		_ASSERTE(ppCoords);
		if (index >= m_nUsed)
			return POINTS_E_INDEXTOLARGE_R;	// where should i get it from

		*ppCoords = &m_pCoords[index];	// ok, nicht gerade vorsichtig
		return S_OK;
	}

// neue KoordinatenAnzahl berechnen
	ULONG CalcNewCoordCount (ULONG ulCnt)
	{
		if (0 == m_nMaxCount)	// erstmal klein anfangen
			return max(c_nInitPlaces, ulCnt);
		return max(m_nMaxCount + c_nNewPlaces, m_nMaxCount + ulCnt);
	}

	HRESULT Add (ULONG index, CSCOORD * pCoords, ULONG ulCnt = 1)
	{
		_ASSERTE(pCoords);

	// gültige Operation
		if (- 1 == index)
			index = m_nUsed;

		if (index > m_nUsed)
			return POINTS_E_INDEXTOLARGE_A;		// or i will get leaks in the block

	// Puffer ausgereizt
	CSCOORD * t_pCoords = NULL;	// targetcoords

		if (m_nUsed + ulCnt > m_nMaxCount)
		{
		// define new size
		ULONG newMaxCount = CalcNewCoordCount (ulCnt);

			ATLTRY(t_pCoords = new CSCOORD[newMaxCount]);
			if (NULL == t_pCoords)		// oops, you lost all your credits try again
				return E_OUTOFMEMORY;

		// copy firstpart
			memcpy(t_pCoords, m_pCoords, index * sizeof(CSCOORD));
			m_nMaxCount = newMaxCount;
		} else
			t_pCoords = m_pCoords;

	// use mem
	// shift last entries
		memmove(& t_pCoords[index + ulCnt], & m_pCoords[index], (m_nUsed - index) * sizeof(CSCOORD));

	// copy entry
		memcpy(& t_pCoords[index], pCoords, ulCnt * sizeof(CSCOORD));

	// now we've some entries more
		m_nUsed += ulCnt;

	// say good bye to good old buffer (if neccesary)
		if (t_pCoords != m_pCoords)
		{
			delete m_pCoords;
			m_pCoords = t_pCoords;
		}
		return S_OK;
	}

	HRESULT Remove(ULONG index)
	{
	// gültige Operation
		if (index >= m_nUsed)
			return POINTS_E_INDEXTOLARGE_R;		// what do you want to delete

	// shift last entries
		memmove(& m_pCoords[index], & m_pCoords[index + 1], (m_nUsed - index - 1) * sizeof(CSCOORD));

	// now we're one entry less
		 -- m_nUsed;
		return S_OK;
	}

// Laden aus IStream
	HRESULT Load(LPSTREAM pStm)
	{
	ULONG cnt = 0;								// wieviele Punkte

		RETURN_FAILED_HRESULT(LoadItem(pStm, cnt));

	// alle Einträge ungültig
		m_nUsed = 0;

	// neuen Speicher anfordern, falls notwendig
		if (cnt > m_nMaxCount)
		{
			RETURN_FAILED_HRESULT(SetPlace(cnt));
		}

		m_nUsed = cnt;
		RETURN_FAILED_HRESULT(pStm -> Read (m_pCoords, sizeof(CSCOORD) * cnt, NULL));
		return S_OK;
	}
	HRESULT Save(LPSTREAM pStm)
	{
	ULONG cnt = m_nUsed;								// wieviele Punkte

		RETURN_FAILED_HRESULT(SaveItem (pStm, cnt));
		RETURN_FAILED_HRESULT(pStm -> Write (m_pCoords, sizeof(CSCOORD) * cnt, NULL));
		return S_OK;
	}

	// Laden aus einem Memory Stream
	HRESULT Load(void * pvMem)
	{
	ULONG cnt = 0;								// wieviele Punkte

		LoadAndAdvance (cnt, pvMem);

	// alle Einträge ungültig
		m_nUsed = 0;

	// neuen Speicher anfordern, falls notwendig
		if (cnt > m_nMaxCount)
		{
			RETURN_FAILED_HRESULT(SetPlace(cnt));
		}
		m_nUsed = cnt;
		LoadAndAdvance(m_pCoords, pvMem, sizeof(CSCOORD) * cnt);
		return S_OK;
	}
	HRESULT Save(void * pvMem)
	{
	ULONG cnt = m_nUsed;								// wieviele Punkte

		SaveAndAdvance(pvMem, cnt);
		SaveAndAdvance(pvMem, m_pCoords, sizeof(CSCOORD) * cnt);
		return S_OK;
	}
	HRESULT SaveWkt(BSTR *pbstrWKT)
	{
	CComBSTR bstrWKT (L"");

		for (ULONG ul = 0; ul < m_nUsed; ++ul) 
			AppendPoint (bstrWKT, m_pCoords[ul].X, m_pCoords[ul].Y, ul != m_nUsed-1);
		*pbstrWKT = bstrWKT.Detach();
		return S_OK;
	}
	HRESULT SaveWkb(void *pvMem)
	{
		SaveAndAdvance(pvMem, m_nUsed);
		for (ULONG ul = 0; ul < m_nUsed; ++ul) {
			SaveAndAdvance(pvMem, m_pCoords[ul].X);
			SaveAndAdvance(pvMem, m_pCoords[ul].Y);
		}
		return S_OK;
	}
	ULONG GetCount()
	{
		return m_nUsed;
	}
	HRESULT GetEnvelope(CSCOORD & minVal, CSCOORD & maxVal)
	{
		if (0 == m_nUsed)
			return E_UNEXPECTED;

		ASSERT(NULL != m_pCoords);

	// Initialisieren
		minVal.X = minVal.Y = minVal.Z = INIT_DBL_MIN;
		maxVal.X = maxVal.Y = maxVal.Z = INIT_DBL_MAX;

		for (ULONG i = 0; i < m_nUsed; i++)
		{
			minVal.X = min(m_pCoords[i].X, minVal.X);
			minVal.Y = min(m_pCoords[i].Y, minVal.Y);
			minVal.Z = min(m_pCoords[i].Z, minVal.Z);

			maxVal.X = max(m_pCoords[i].X, maxVal.X);
			maxVal.Y = max(m_pCoords[i].Y, maxVal.Y);
			maxVal.Z = max(m_pCoords[i].Z, maxVal.Z);
		}
		return S_OK;
	}
	ULONG Count() { return GetCount(); }

protected:
// Members
	CSCOORD * 	m_pCoords;		// pointer to data
	ULONG		m_nMaxCount;	// place for m_nMaxIndex entries is available
	ULONG		m_nUsed;		// used entries
};

#endif // !defined(_COORDFIELD_H__C77EE753_4183_11D2_8C7E_006097A8F384__INCLUDED_)
