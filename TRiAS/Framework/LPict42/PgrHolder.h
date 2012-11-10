// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 21.03.2002 12:08:56 
//
// @doc
// @module PgrHolder.h | Declaration of the <c CPgrHolder> class

#if !defined(_PGRHOLDER_H__53B76F66_4823_47F4_A3F6_197605E60242__INCLUDED_)
#define _PGRHOLDER_H__53B76F66_4823_47F4_A3F6_197605E60242__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <pgr.h>
#include <float.h>

#include "PgrTile.h"
#include "SpatialTree.h"

///////////////////////////////////////////////////////////////////////////////
// hält die Informationen einer PolyGIS *.pgr Datei
class CPgrTileHolder
{
public:
	CPgrTileHolder() 
	{
		Clear();
	}
	~CPgrTileHolder() {}

	BOOL LoadTiles (CFile &rFile, PGRHEADEROLD &rHdr, CPictException *e = NULL);
	BOOL LoadTiles (CFile &rFile, PGRHEADER &rHdr, CPictException *e = NULL);
	BOOL LoadTiles (CFile &rFile, CFile &rFileMap, PGRHEADER2 &rHdr, CPictException *e = NULL);

	void Clear()
	{
		m_treeTiles.Clear();
		m_dMin[0] = m_dMin[1] = DBL_MAX;	// Vorgaben aus PgrHeader
		m_dMax[0] = m_dMax[1] = DBL_MIN;
		m_dMinT[0] = m_dMinT[1] = DBL_MAX;	// aufgesammeltes aus einzelnen Kacheln
		m_dMaxT[0] = m_dMaxT[1] = DBL_MIN;

		m_dTileX = 0.0;
		m_dTileY = 0.0;
		m_lTileSizeX = 0;
		m_lTileSizeY = 0;

		m_fLoaded = false;
	}

	bool operator! () { return !m_fLoaded; }

	long GetSizeX() 
	{ 
		_ASSERTE(0 != m_dTileX); 
		return (long)(((m_dMaxT[0]-m_dMinT[0]) / m_dTileX) * m_lTileSizeX + 0.5); 
	}
	double GetRealSizeX()
	{
		return m_dMaxT[0]-m_dMinT[0];
	}

	long GetSizeY() 
	{ 
		_ASSERTE(0 != m_dTileY); 
		return (long)(((m_dMaxT[1]-m_dMinT[1]) / m_dTileY) * m_lTileSizeY + 0.5); 
	}
	double GetRealSizeY()
	{
		return m_dMaxT[1]-m_dMinT[1];
	}

	double GetXResolution() 
	{ 
		_ASSERTE(0 != m_lTileSizeX);
		return m_dTileX/m_lTileSizeX; 
	}
	double GetYResolution() 
	{ 
		_ASSERTE(0 != m_lTileSizeY);
		return m_dTileY/m_lTileSizeY; 
	}

	long GetTileSizeX() { return (long)m_dTileX; }
	long GetTileSizeY() { return (long)m_dTileY; }

	void SetMBR (double dXMin, double dYMin, double dXMax, double dYMax)
	{
		m_dMin[0] = dXMin;
		m_dMin[1] = dYMin;
		m_dMax[0] = dXMax;
		m_dMax[1] = dYMax;
	}
	void GetMBR (double &rdXMin, double &rdYMin, double &rdXMax, double &rdYMax)
	{
		rdXMin = m_dMinT[0];
		rdYMin = m_dMinT[1];
		rdXMax = m_dMaxT[0];
		rdYMax = m_dMaxT[1];
	}

// Enumeration der zu zeichnenden Kacheln
	HRESULT EnumTiles (DRAWTILEPROC pfcnDraw, CDC *pDC, CRect const &rcSrc, 
		CRect const &rcDest)
	{
	double dMin[2] = { rcSrc.left, rcSrc.bottom };
	double dMax[2] = { rcSrc.right, rcSrc.top };

		return m_treeTiles.TileSearch(dMin, dMax, pfcnDraw, pDC, rcSrc, rcDest);
	}

	BOOL ReadTilesFromFile(LPCSTR pcName, unsigned long lExpectedCount, vector<CPgrTile> &rTiles);

private:
	CSpatialTree m_treeTiles;

// umschließendes Rechteck
	double m_dMin[2];			// Vorgaben aus PgrHeader (für SpatialTree)
	double m_dMax[2];

	double m_dMinT[2];			// aufgesammeltes aus einzelnen Kacheln
	double m_dMaxT[2];

	double m_dTileX;			// reale Kachelausdehnung
	double m_dTileY;

	long m_lTileSizeX;			// Kachelpixelgröße
	long m_lTileSizeY;

	bool m_fLoaded;
};

const long PGR_HOLDER_SIGNATURE	= 0x43524750;		// PGRC
const long PGR_HOLDER_LASTKNOWN_VERSION = 0x0100;
const long PGR_HOLDER_VERSION = PGR_HOLDER_LASTKNOWN_VERSION;
const long PGR_HOLDER_MINORVERSION_MASK = 0xff;

#endif // !defined(_PGRHOLDER_H__53B76F66_4823_47F4_A3F6_197605E60242__INCLUDED_)
