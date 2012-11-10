// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 21.03.2002 12:59:07 
//
// @doc
// @module PgrHolder.cpp | Definition of the <c CPgrHolder> class

#include "stdafx.h"

#include <pgr.h>
#include <ospace/file/path.h>
#include <ospace/std/vector>

#include "LPictImpl.h"
#include "PgrHolder.h"

///////////////////////////////////////////////////////////////////////////////
// Laden aller Kachelinfos (alte Struktur)
BOOL CPgrTileHolder::LoadTiles (CFile &rFile, PGRHEADEROLD &rHdr, CPictException *e)
{
// Größe des Bildes voreinstellen
	SetMBR(rHdr.dXMin, rHdr.dYMin, rHdr.dXMax, rHdr.dYMax);

// Baum initialisieren, dazu Dateigröße feststellen
long lCurrent = rFile.Seek(0, CFile::current);
long lEnd = rFile.Seek(0, CFile::end);

	rFile.Seek(lCurrent, CFile::begin);

double dTreeMin[2] = { 0, 0 };
double dTreeMax[2] = { rHdr.iCountX*TILE_SIZE_X, rHdr.iCountY*TILE_SIZE_Y };

	_ASSERTE(0 == (lEnd-lCurrent)%sizeof(CMPKACHELOLD));
	m_treeTiles.Init((lEnd-lCurrent)/sizeof(CMPKACHELOLD), dTreeMin, dTreeMax);

// alle Kacheln laden und im Tree speichern
	do {
	// Kachel laden
	CPgrTile Tile;
	CSize szTile;

		if (!Tile.LoadTile(rFile, (CMPKACHELOLD *)NULL, szTile, e)) 
			break;		// Dateiende
		
		_ASSERTE(szTile.cx == TILE_SIZE_X);
		_ASSERTE(szTile.cy == TILE_SIZE_Y);

	// Kachelgröße prüfen
		if (0 == m_lTileSizeX) {
			m_lTileSizeX = szTile.cx;
			m_dTileX = Tile.GetXMax()-Tile.GetXMin();
		} 
		else {
			_ASSERTE(m_lTileSizeX == szTile.cx);
			_ASSERTE(m_dTileX == Tile.GetXMax()-Tile.GetXMin());
		}
		if (0 == m_lTileSizeY) {
			m_lTileSizeY = szTile.cy;
			m_dTileY = Tile.GetYMax()-Tile.GetYMin();
		}
		else {
			_ASSERTE(m_lTileSizeY == szTile.cy);
			_ASSERTE(m_dTileY == Tile.GetYMax()-Tile.GetYMin());
		}

	// kumulative Infos aufsammeln
		m_dMinT[0] = min(m_dMinT[0], Tile.GetXMin());
		m_dMinT[1] = min(m_dMinT[1], Tile.GetYMin());
		m_dMaxT[0] = max(m_dMaxT[0], Tile.GetXMax());
		m_dMaxT[1] = max(m_dMaxT[1], Tile.GetYMax());

	} while (true);

// Kacheln in den Baum laden
	rFile.Seek(lCurrent, CFile::begin);
	do {
	// Kachel laden
	CPgrTile Tile;
	CSize szTile;

		if (!Tile.LoadTile(rFile, (CMPKACHELOLD *)NULL, szTile, e)) 
			break;		// Dateiende
		
	// Kacheln müssen in den Baum passen
		_ASSERTE(Tile.GetXMin() >= m_dMinT[0] && Tile.GetXMax() <= m_dMaxT[0]);
		_ASSERTE(Tile.GetYMin() >= m_dMinT[1] && Tile.GetYMax() <= m_dMaxT[1]);

	// Pixelcontainer dieser Kachel berechnen
		Tile.CalcBounds(m_dMin[0], m_dTileX, m_dMin[1], m_dTileY);

	// im Baum speichern
		if (!m_treeTiles.AddTile (&Tile)) {
			if (NULL != e) {
				e->m_cause = CPictException::errMemory;
				e->m_strPictName = rFile.GetFileName();
			}
			return FALSE;
		}

	} while (true);

// Tree zurechtstutzen
	m_treeTiles.TrimExtraNodes();
	m_fLoaded = true;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Laden aller Kachelinfos (neue Struktur)
BOOL CPgrTileHolder::LoadTiles (CFile &rFile, PGRHEADER &rHdr, CPictException *e)
{
// Größe des Baumes voreinstellen
	SetMBR(rHdr.dXMin, rHdr.dYMin, rHdr.dXMax, rHdr.dYMax);

// Anzahl der Kacheln bestimmen, dazu Dateigröße feststellen
long lCurrent = rFile.Seek(0, CFile::current);
long lEnd = rFile.Seek(0, CFile::end);

	rFile.Seek(lCurrent, CFile::begin);
	_ASSERTE(0 == (lEnd-lCurrent)%sizeof(CMPKACHEL));

long lTileCount = (lEnd-lCurrent)/sizeof(CMPKACHEL);

// alle Kacheln laden und umschließendes Rechteck berechnen
#if defined(_DEBUG)
long lCountTiles = 0;
#endif // defined(_DEBUG)

	do {
	// Kachel laden
	CPgrTile Tile;
	CSize szTile;

		if (!Tile.LoadTile(rFile, (CMPKACHEL *)NULL, szTile, e)) 
			break;		// Dateiende
		
#if defined(_DEBUG)
		++lCountTiles;
#endif // defined(_DEBUG)

		_ASSERTE(szTile.cx == TILE_SIZE_X);
		_ASSERTE(szTile.cy == TILE_SIZE_Y);

	// Kachelgröße prüfen
		if (0 == m_lTileSizeX) {
			m_lTileSizeX = szTile.cx;
			m_dTileX = Tile.GetXMax()-Tile.GetXMin();
		} 
		else {
			_ASSERTE(m_lTileSizeX == szTile.cx);
			_ASSERTE(m_dTileX == Tile.GetXMax()-Tile.GetXMin());
		}
		if (0 == m_lTileSizeY) {
			m_lTileSizeY = szTile.cy;
			m_dTileY = Tile.GetYMax()-Tile.GetYMin();
		}
		else {
			_ASSERTE(m_lTileSizeY == szTile.cy);
			_ASSERTE(m_dTileY == Tile.GetYMax()-Tile.GetYMin());
		}

	// kumulative Infos aufsammeln
		m_dMinT[0] = min(m_dMinT[0], Tile.GetXMin());
		m_dMinT[1] = min(m_dMinT[1], Tile.GetYMin());
		m_dMaxT[0] = max(m_dMaxT[0], Tile.GetXMax());
		m_dMaxT[1] = max(m_dMaxT[1], Tile.GetYMax());

	} while (true);
	_ASSERTE(lCountTiles == lTileCount);

// Baum initialisieren (vor dem erstem AddTile)
double dTreeMin[2] = { 0, 0 };
double dTreeMax[2] = { GetSizeX(), GetSizeY() };

	m_treeTiles.Init(lTileCount, dTreeMin, dTreeMax);

// Kachel in den Baum laden
	rFile.Seek(lCurrent, CFile::begin);
	do {
	// Kachel laden
	CPgrTile Tile;
	CSize szTile;

		if (!Tile.LoadTile(rFile, (CMPKACHEL *)NULL, szTile, e)) 
			break;		// Dateiende
		
	// Kacheln müssen in den Baum passen
		_ASSERTE(Tile.GetXMin() >= m_dMinT[0] && Tile.GetXMax() <= m_dMaxT[0]);
		_ASSERTE(Tile.GetYMin() >= m_dMinT[1] && Tile.GetYMax() <= m_dMaxT[1]);

	// Pixelcontainer dieser Kachel berechnen
		Tile.CalcBounds(m_dMin[0], m_dTileX, m_dMin[1], m_dTileY);

	// im Baum speichern
		if (!m_treeTiles.AddTile (&Tile)) {
			if (NULL != e) {
				e->m_cause = CPictException::errMemory;
				e->m_strPictName = rFile.GetFileName();
			}
			return FALSE;
		}
	} while (true);

// Tree zurechtstutzen
	m_treeTiles.TrimExtraNodes();
	m_fLoaded = true;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Laden aller Kachelinfos 
BOOL CPgrTileHolder::ReadTilesFromFile(LPCSTR pcName, unsigned long lExpectedCount, 
	vector<CPgrTile> &rTiles)
{
CFile pgrCache;

	if (!pgrCache.Open((LPCTSTR)pcName, 
		CFile::modeRead|CFile::shareDenyWrite|CFile::typeBinary)) 
	{
		return FALSE;
	}

long lSignature = 0;
long lVersion = 0;

	if (sizeof(long) != pgrCache.Read(&lSignature, sizeof(long)) ||
		sizeof(long) != pgrCache.Read(&lVersion, sizeof(long)))
		return FALSE;

	if (PGR_HOLDER_SIGNATURE != lSignature || 
		(lVersion & ~PGR_HOLDER_MINORVERSION_MASK) > PGR_HOLDER_LASTKNOWN_VERSION)
		return FALSE;		// falsche Version 

unsigned long lTileCount = 0;

	if (sizeof(long) != pgrCache.Read(&lTileCount, sizeof(unsigned long)) ||
		lExpectedCount != lTileCount)
		return FALSE;

	if (2*sizeof(double) == pgrCache.Read(m_dMinT, 2*sizeof(double)) &&
		2*sizeof(double) == pgrCache.Read(m_dMaxT, 2*sizeof(double)) && 
		sizeof(double) == pgrCache.Read(&m_dTileX, sizeof(double)) &&
		sizeof(double) == pgrCache.Read(&m_dTileY, sizeof(double)) &&
		sizeof(long) == pgrCache.Read(&m_lTileSizeX, sizeof(long)) &&
		sizeof(long) == pgrCache.Read(&m_lTileSizeY, sizeof(long)))
	{
		for (unsigned long iCnt = 0; iCnt < lTileCount; ++iCnt) {
		CPgrTile Tile;

			if (sizeof(CPgrTile) != pgrCache.Read(&Tile, sizeof(CPgrTile)))
				return FALSE;
			ATLTRY(rTiles.push_back(Tile));
		}
	}
	return TRUE;
}

BOOL CPgrTileHolder::LoadTiles (CFile &rFilePgr, CFile &rFileMap, 
	PGRHEADER2 &rHdr, CPictException *e)
{
// Größe des Bildes voreinstellen
	SetMBR(rHdr.dXMin, rHdr.dYMin, rHdr.dXMax, rHdr.dYMax);

// Anzahl der Kacheln bestimmen, dazu Dateigröße feststellen
long lCurrent = rFilePgr.Seek(0, CFile::current);
long lEnd = rFilePgr.Seek(0, CFile::end);

	rFilePgr.Seek(lCurrent, CFile::begin);
	_ASSERTE(0 == (lEnd-lCurrent+6)%sizeof(CMPKACHEL2));

unsigned long lTileCount = (lEnd-lCurrent+6)/sizeof(CMPKACHEL2)-1;
vector<CPgrTile> Tiles;
os_path pgrcachepath = (LPCTSTR)rFileMap.GetFilePath();

	pgrcachepath.extension("pgrcache");

// Versuchen, Cache zu laden
	if (-1 != GetFileAttributes((LPCSTR)pgrcachepath)) 
		ReadTilesFromFile ((LPCSTR)pgrcachepath, lTileCount, Tiles);

// ggf. immer wieder auf die herkömmliche Tour
	if (lTileCount != Tiles.size()) {
	// alle Kacheln laden und umschließendes Rechteck berechnen
	long lOffset = 0;

		do {
		// Kachel laden
		CPgrTile Tile;
		CSize szTile;

			if (!Tile.LoadTile2(rFilePgr, rFileMap, szTile, lOffset, e)) 
				break;		// Dateiende
			Tiles.push_back(Tile);

			_ASSERTE(szTile.cx == TILE_SIZE_X);
			_ASSERTE(szTile.cy == TILE_SIZE_Y);

		// Kachelgröße prüfen
			if (0 == m_lTileSizeX) {
				m_lTileSizeX = szTile.cx;
				m_dTileX = Tile.GetXMax()-Tile.GetXMin();
			} 
			else {
				_ASSERTE(m_lTileSizeX == szTile.cx);
				_ASSERTE(m_dTileX == Tile.GetXMax()-Tile.GetXMin());
			}
			if (0 == m_lTileSizeY) {
				m_lTileSizeY = szTile.cy;
				m_dTileY = Tile.GetYMax()-Tile.GetYMin();
			}
			else {
				_ASSERTE(m_lTileSizeY == szTile.cy);
				_ASSERTE(m_dTileY == Tile.GetYMax()-Tile.GetYMin());
			}

		// kumulative Infos aufsammeln
			m_dMinT[0] = min(m_dMinT[0], Tile.GetXMin());
			m_dMinT[1] = min(m_dMinT[1], Tile.GetYMin());
			m_dMaxT[0] = max(m_dMaxT[0], Tile.GetXMax());
			m_dMaxT[1] = max(m_dMaxT[1], Tile.GetYMax());

		} while (true);
		_ASSERTE(Tiles.size() == lTileCount);

	// Datei neu erzeugen und Cache wegschreiben
	CFile pgrCache;

		if (pgrCache.Open((LPCTSTR)pgrcachepath, CFile::modeCreate|
				CFile::modeReadWrite|CFile::shareDenyWrite|CFile::typeBinary))
		{
			TRY {
			// Versoinsinfo
				pgrCache.Write(&PGR_HOLDER_SIGNATURE, sizeof(long));
				pgrCache.Write(&PGR_HOLDER_VERSION, sizeof(long));

			// Container etc.
				pgrCache.Write(&lTileCount, sizeof(unsigned long));

				pgrCache.Write(m_dMinT, 2*sizeof(double));
				pgrCache.Write(m_dMaxT, 2*sizeof(double));
				pgrCache.Write(&m_dTileX, sizeof(double));
				pgrCache.Write(&m_dTileY, sizeof(double));
				pgrCache.Write(&m_lTileSizeX, sizeof(long));
				pgrCache.Write(&m_lTileSizeY, sizeof(long));

			// Kachelinfos
				pgrCache.Write(Tiles.begin(), lTileCount*sizeof(CPgrTile));

			} CATCH (CFileException, fe) {
				pgrCache.Close();
				DeleteFile((LPCSTR)pgrcachepath);
				if (NULL != e) {
					e->m_cause = CPictException::errMemory;
					e->m_strPictName = rFilePgr.GetFileName();
				}
				return FALSE;
			} END_CATCH;
		}
	}

// Baum initialisieren (vor dem erstem AddTile)
double dTreeMin[2] = { 0, 0 };
double dTreeMax[2] = { GetSizeX(), GetSizeY() };

	m_treeTiles.Init(lTileCount, dTreeMin, dTreeMax);

// Kachel in den Baum laden
vector<CPgrTile>::iterator end = Tiles.end();

	for (vector<CPgrTile>::iterator it = Tiles.begin(); it != end; ++it) {
	// Kacheln müssen in den Baum passen
		_ASSERTE((*it).GetXMin() >= m_dMinT[0] && (*it).GetXMax() <= m_dMaxT[0]);
		_ASSERTE((*it).GetYMin() >= m_dMinT[1] && (*it).GetYMax() <= m_dMaxT[1]);

	// Pixelcontainer dieser Kachel berechnen
		(*it).CalcBounds(m_dMin[0], m_dTileX, m_dMin[1], m_dTileY);

	// im Baum speichern
		if (!m_treeTiles.AddTile (&(*it))) {
			if (NULL != e) {
				e->m_cause = CPictException::errMemory;
				e->m_strPictName = rFilePgr.GetFileName();
			}
			return FALSE;
		}
	} 

// Tree zurechtstutzen
	m_treeTiles.TrimExtraNodes();
	m_fLoaded = true;
	return TRUE;
}

