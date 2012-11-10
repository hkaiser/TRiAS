// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 14:19:51
//
// @doc
// @module ArcViewDataSource.cpp | Implementation of the <c CArcViewDataSource> class

#include "StdAfx.h"

#include <ospace/file/path.h>

#include "Strings.h"
#include "ArcViewImpl.h"
#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "ArcView.hmc"
#include "ArcViewExport.h"
#include "ArcViewDataSource.h"

///////////////////////////////////////////////////////////////////////////////
// Neuen Layer erzeugen
HRESULT CArcViewDataSource::OpenLayer (
	INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, OPENMODE rgMode,
	CArcViewLayer **ppLayer)
{
	_ASSERTE(NULL != pcName);
	if (NULL == pcName) 
		return E_POINTER;

	_ASSERTE(S_OK != GetLayer (lIdent, rgType, ppLayer));		// darf noch nicht existieren

// Verify uniqueness of the Shapename
os_string strName (CorrectName(pcName));
OutMode rgOutMode = m_rgMode;

	if (OPENMODE_Create == rgMode) {
	CArcViewLayers::iterator end = m_Layers.end();

		for (CArcViewLayers::iterator it = m_Layers.begin(); it != end; ++it) {
			if ((*it).second -> GetName() == strName && (*it).second -> GetType() == rgType) 
				return ARCVIEW_W_LAYERNAME_NOT_UNIQUE;		// Layername muﬂ unique sein
		}
	} else 
		rgOutMode = OMConcatinate;

// Figure out what type of layer we need
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
		return ARCVIEW_E_BADOBJECTTYPE;

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

		if (OMOverwrite == rgOutMode) 
			hSHP = SHPCreate (strShp.c_str(), nShapeType);
		else
			hSHP = SHPOpen (strShp.c_str(), "rb+");

		if (NULL == hSHP) 
			return ARCVIEW_E_OPENFILE_FAILED;

	// Create/Open the DBF file
		path.extension(g_cbDbf);

	os_string strDbf (path);
	DBFHandle hDBF = NULL;

		if (OMOverwrite == rgOutMode)
			hDBF = DBFCreate(strDbf.c_str());
		else
			hDBF = DBFOpen(strDbf.c_str(), "rb+");

		if (NULL == hDBF) 
			return ARCVIEW_E_OPENFILE_FAILED;

// Create the layer object and add layer to data source layer list
	os_string strRoot(path);
	CArcViewLayer *poLayer = NULL;
	
		poLayer = new CArcViewLayer (pcName, rgType, strRoot, hSHP, hDBF);
		m_Layers.insert (lIdent, poLayer);

		if (NULL != ppLayer)
			*ppLayer = poLayer;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// bestimmten Layer wiederfinden
HRESULT CArcViewDataSource::GetLayer(INT_PTR lIdent, OBJECTTYPE rgType, CArcViewLayer **ppLayer)
{
CArcViewLayers::iterator it = m_Layers.find(lIdent);

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

HRESULT CArcViewDataSource::GetLayer(LPCSTR pcName, OBJECTTYPE rgType, CArcViewLayer **ppLayer)
{
os_string strName (CorrectName(pcName));
CArcViewLayers::iterator end = m_Layers.end();

	for (CArcViewLayers::iterator it = m_Layers.begin(); it != end; ++it) {
		if ((*it).second -> GetName() == strName && 
			(*it).second -> GetType() == rgType) 
		{
			if (NULL != ppLayer)
				*ppLayer = (*it).second;
			return S_OK;
		}
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// schlieﬂen aller Dateien, freigeben s‰mtlicher Resourcen
HRESULT CArcViewDataSource::CloseAll()
{
	m_Layers.clear();		// einfach alles freigeben
	return S_OK;
}

HRESULT CArcViewDataSource::DeleteAllFiles()
{
	for (CArcViewLayers::iterator it = m_Layers.begin(); it != m_Layers.end(); ++it) 
		(*it).second -> CloseAndDeleteFiles();		// Layer schlieﬂen

// jetzt alles freigeben
	m_Layers.clear();
	return S_OK;
}

