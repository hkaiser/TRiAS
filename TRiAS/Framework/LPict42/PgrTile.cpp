// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 16.07.2002 15:14:03 
//
// @doc
// @module PgrTile.cpp | Definition of the <c CPgrTile> class

#include "stdafx.h"

#include <pgr.h>

#include "LPictImpl.h"
#include "PgrTile.h"

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CPgrTile::LoadTile2 (CFile &rFilePgr, CFile &rFileMap, CSize &rSize, 
	long &rlOffset, CPictException *e)
{
CMPKACHEL2 Tile;

	if (sizeof(CMPKACHEL2) != rFilePgr.Read(&Tile, sizeof(CMPKACHEL2))) {
		if (NULL != e) {
			e->m_cause = CPictException::errMissingInfo;
			e->m_strPictName = rFilePgr.GetFileName();
		}
		return FALSE;
	}
	if (MAGIC_PGR2 != Tile.iMagic) {
		if (NULL != e) {
			e->m_cause = CPictException::errFormat;
			e->m_strPictName = rFilePgr.GetFileName();
		}
		return FALSE;
	}

	m_dXMin = Tile.dXMin;
	m_dYMin = Tile.dYMin;
	m_dXMax = Tile.dXMax;
	m_dYMax = Tile.dYMax;
	m_lBytes = Tile.lByteCount;

unsigned char cFillByte;

	rFileMap.Seek(rlOffset, CFile::begin);
	rFileMap.Read(&cFillByte, 1);

	rlOffset += cFillByte;
	m_lOffset = rlOffset;
	rlOffset += m_lBytes;

	rSize.cx = Tile.lSizeX;
	rSize.cy = Tile.lSizeY;
	return TRUE;
}

