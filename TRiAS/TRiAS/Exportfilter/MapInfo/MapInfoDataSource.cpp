// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:45:44 
//
// @doc
// @module MapInfoDataSource.cpp | Definition of the <c CMapInfoDataSource> class

#include "StdAfx.h"

#include <ospace/file/path.h>

#include "Strings.h"
#include "MapInfoImpl.h"
#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "MapInfo.hmc"
#include "MapInfoDataSource.h"

namespace {
///////////////////////////////////////////////////////////////////////////////
// s‰mtliche Sonderzeichen ('.', '/', '\\' etc.) im Namen ersetzen
	os_string CorrectName (LPCSTR pcName)
	{
	os_string strName (pcName);
	size_t iLen = strName.size();

		for (int i = 0; i < iLen; i++) {
		char c = strName[i];

			switch (c) {
			case '.':
			case '\\':
			case '/':
			case ':':
			case '!':
				strName[i] = '_';
				break;

			case '\0':		// Ende des Strings
				break;

			default:
				if (c > ' ')
					strName[i] = c;
				else
					strName[i] = '_';
				break;
			}
		}
		return strName;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Neuen Layer erzeugen
HRESULT CMapInfoDataSource::CreateLayer (
	INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, CMapInfoLayer **ppLayer)
{
	_ASSERTE(NULL != pcName);
	if (NULL == pcName) 
		return E_POINTER;

	_ASSERTE(S_OK != GetLayer (lIdent, rgType, ppLayer));		// darf noch nicht existieren

// Figure out what type of layer we need
os_string strName (CorrectName(pcName));
int nShapeType = -1;

	if (rgType == OBJECTTYPE_Line) {
		nShapeType = SHPT_ARC;
		strName += "_l";
	} else if (rgType == OBJECTTYPE_Point) {
		nShapeType = SHPT_POINT;
		strName += "_p";
	} else if (rgType == OBJECTTYPE_Text) {
		nShapeType = SHPT_POINT;
		strName += "_t";
	} else if (rgType == OBJECTTYPE_Area) {
		nShapeType = SHPT_POLYGON;
		strName += "_a";
	} else 
		return MAPINFO_E_BADOBJECTTYPE;

// Verify uniqueness of the Shapename
	for (CMapInfoLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) {
		if ((*it).second -> GetName() == strName) 
			return MAPINFO_W_LAYERNAME_NOT_UNIQUE;		// Layername muﬂ unique sein
	}

// Create the shapefile
 	COM_TRY {
	os_path dir (m_strRootDir);
	os_path path (strName);

	// vollst‰ndigen Dateinamen bauen
		path.extension(g_cbShp);
		if (dir.has_directory()) 
			path.directory(dir.directory());
		if (dir.has_drive()) 
			path.drive(*dir.drive().c_str());
		else if (dir.has_unc())
			path.unc(dir.unc(), dir.share());

	// craete/open the shape file
	os_string strShp (path);
	SHPHandle hSHP = NULL;

		if (OMOverwrite == m_rgMode) 
			hSHP = SHPCreate (strShp.c_str(), nShapeType);
		else
			hSHP = SHPOpen (strShp.c_str(), "rb+");

		if (NULL == hSHP) 
			return MAPINFO_E_OPENFILE_FAILED;

	// Create/Open the DBF file
		path.extension(g_cbDbf);

	os_string strDbf (path);
	DBFHandle hDBF = NULL;

		if (OMOverwrite == m_rgMode)
			hDBF = DBFCreate(strDbf.c_str());
		else
			hDBF = DBFOpen(strDbf.c_str(), "rb+");

		if (NULL == hDBF) 
			return MAPINFO_E_OPENFILE_FAILED;

// Create the layer object and add layer to data source layer list
	os_string strRoot(path);
	CMapInfoLayer *poLayer = new CMapInfoLayer (pcName, rgType, strRoot, hSHP, hDBF);

		m_Layers.insert (lIdent, poLayer);
		if (NULL != ppLayer)
			*ppLayer = poLayer;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// bestimmten Layer wiederfinden
HRESULT CMapInfoDataSource::GetLayer(INT_PTR lIdent, OBJECTTYPE rgType, CMapInfoLayer **ppLayer)
{
CMapInfoLayers::iterator it = m_Layers.find(lIdent);

	if (it != m_Layers.end()) {
		while ((*it).first == lIdent) {
			if (rgType == (*it).second -> GetType()) {
				if (NULL != ppLayer)
					*ppLayer = (*it).second;
				return S_OK;
			}
			++it;
		} 
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// schlieﬂen aller Dateien, freigeben s‰mtlicher Resourcen
HRESULT CMapInfoDataSource::CloseAll()
{
	m_Layers.clear();		// einfach alles freigeben
	return S_OK;
}

HRESULT CMapInfoDataSource::DeleteAllFiles()
{
	for (CMapInfoLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) 
		(*it).second -> CloseAndDeleteFiles();		// Layer schlieﬂen

// jetzt alles freigeben
	m_Layers.clear();
	return S_OK;
}

