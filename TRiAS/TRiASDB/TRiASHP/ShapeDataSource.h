// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.05.2000 17:07:59 
//
// @doc
// @module ShapeDataSource.h | Declaration of the <c CShapeDataSource> class

#if !defined(_SHAPEDATASOURCE_H__D343DDA2_4F02_401B_9195_3706F7652D67__INCLUDED_)
#define _SHAPEDATASOURCE_H__D343DDA2_4F02_401B_9195_3706F7652D67__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stlex/pointainer.h>
#include "ShapeLayer.h"

///////////////////////////////////////////////////////////////////////////////
// Eine Shape-Datenquelle (alle *.shp -Dateien eines Verzeichnisses)
class CShapeDataSource 
{
public:
	typedef pointainer<vector<CShapeLayer *> > CShapeLayers;
	friend class CLayerIterator;

	CShapeDataSource() :
		m_fOpened(false), m_fUpdatable(false), m_fDeniedToOpen(false)
	{
	}
	~CShapeDataSource()
	{
		_ASSERTE(!IsOpened());		// sollte geschlossen worden sein
	}

	HRESULT Open (const char *pcDirName, bool fUpdate, bool fTestOpen = false);
	HRESULT OpenFile (const char *pcFileName, bool fUpdate, bool fTestOpen);
	HRESULT Close();

	const char *GetName() { return m_strName.c_str(); }
	int GetLayerCount() { return m_Layers.size(); }

	CShapeLayer *GetLayer (int iLayer)
	{
		_ASSERTE(0 <= iLayer && iLayer < m_Layers.size());
		return (0 <= iLayer && iLayer < m_Layers.size()) ? m_Layers[iLayer] : NULL;
	}
#if defined(_READWRITE)
	CShapeLayer *CreateLayer (const char *pcName, OBJECTTYPE rgType = OBJECTTYPE_Unknown, ITRiASCSTransform *pSpatRef = NULL);
#endif // defined(_READWRITE)

	int TestCapability (const char *);
	bool IsOpened() { return m_fOpened; }

protected:
	CShapeLayers & GetLayers() { return m_Layers; }

private:
	CShapeLayers m_Layers;	// sämtliche Shapedateien dieser Datenquelle
	os_string m_strName;	// Name der Datenquelle

	bool m_fOpened;			// Datenbank erfolgreich geöffnet
	bool m_fUpdatable;		// r/o bzw. beschreibbar geöffnet
	bool m_fDeniedToOpen;	// einmal nachfragen reicht...
};

///////////////////////////////////////////////////////////////////////////////
// Iterator über die einzelnen Layer
class CLayerIterator 
{
public:
	CLayerIterator (CShapeDataSource &rDS) : 
		m_rDS(rDS), m_it (rDS.GetLayers().begin())
	{
	}
	~CLayerIterator()
	{
	}

	CShapeLayer *GetFirstLayer() { m_it = m_rDS.GetLayers().begin(); return (*m_it); }
	CShapeLayer *GetNextLayer() { ++m_it; return (m_it != m_rDS.GetLayers().begin()) ? (*m_it) : NULL; }
	
private:
	CShapeDataSource &m_rDS;
	CShapeDataSource::CShapeLayers::iterator m_it;
};

#endif // !defined(_SHAPEDATASOURCE_H__D343DDA2_4F02_401B_9195_3706F7652D67__INCLUDED_)
