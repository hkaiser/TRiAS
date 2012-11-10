// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 21.03.2002 22:34:47 
//
// @doc
// @module PgrTile.h | Declaration of the <c CPgrTile> class

#if !defined(_PGRTILE_H__C69F630E_34E1_448F_862D_07C27BF25C25__INCLUDED_)
#define _PGRTILE_H__C69F630E_34E1_448F_862D_07C27BF25C25__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// hält Informationen zu einer PolyGIS Rasterkachel
class CPgrTile
{
public:
	CPgrTile() {}
	~CPgrTile() {}

	template <typename CmpKachelT>
	BOOL LoadTile (CFile &rFile, CmpKachelT *, CSize &rSize, CPictException *e = NULL)
	{
	CmpKachelT Tile;

		if (sizeof(CmpKachelT) != rFile.Read(&Tile, sizeof(CmpKachelT))) {
			if (NULL != e) {
				e->m_cause = CPictException::errMissingInfo;
				e->m_strPictName = rFile.GetFileName();
			}
			return FALSE;
		}
		if (MAGIC_PGR_KACHEL != Tile.iMagic) {
			if (NULL != e) {
				e->m_cause = CPictException::errFormat;
				e->m_strPictName = rFile.GetFileName();
			}
			return FALSE;
		}

		m_dXMin = Tile.dXMin;
		m_dYMin = Tile.dYMin;
		m_dXMax = Tile.dXMax;
		m_dYMax = Tile.dYMax;
		m_lOffset = Tile.lOffset;
		m_lBytes = Tile.lByteCount;

		rSize.cx = Tile.lSizeX;
		rSize.cy = Tile.lSizeY;
		return TRUE;
	}

	BOOL LoadTile2 (CFile &rFilePgr, CFile &rFileMap, CSize &rSize, 
		long &rlOffset, CPictException *e = NULL);

	double GetXMin() { return m_dXMin; }
	double GetYMin() { return m_dYMin; }
	double GetXMax() { return m_dXMax; }
	double GetYMax() { return m_dYMax; }
	
	double GetWidth() { return m_dXMax-m_dXMin; }
	double GetHeight() { return m_dYMax-m_dYMin; }

	long GetOffset() { return m_lOffset; }
	long GetByteCount() { return m_lBytes; }

// Umrechnen der Realkoordinaten in Pixelkoordinaten innerhalb des Gesamtbildes
	bool CalcBounds (double dXMin, double dSizeX, double dYMin, double dSizeY)
	{
		_ASSERTE(0 != dSizeX && 0 != dSizeY);
		if (0 == dSizeX || 0 == dSizeY)
			return false;

		m_dXMin = (m_dXMin-dXMin)/dSizeX * TILE_SIZE_X;
		m_dXMax = (m_dXMax-dXMin)/dSizeX * TILE_SIZE_X;
		m_dYMin = (m_dYMin-dYMin)/dSizeY * TILE_SIZE_Y;
		m_dYMax = (m_dYMax-dYMin)/dSizeY * TILE_SIZE_Y;
		return true;
	}

private:
	double m_dXMin;		// umschließendes Rechteck (nach dem Laden: reale Koords)
	double m_dYMin;		// dann wird in Pixelkoordinaten umgerechnet, über die
	double m_dXMax;		// dann auch im Baum gespeichert wird.
	double m_dYMax;

	long m_lOffset;		// Start in der maps.dat
	long m_lBytes;		// Größe in der maps.dat
};

#endif // !defined(_PGRTILE_H__C69F630E_34E1_448F_862D_07C27BF25C25__INCLUDED_)
