// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.01.2001 20:15:28 
//
// @doc
// @module MiTabDatasource.h | Declaration of the <c CMiTabDatasource> class

#if !defined(_MITABDATASOURCE_H__11CFCEF5_D253_42AE_A542_C454A351949E__INCLUDED_)
#define _MITABDATASOURCE_H__11CFCEF5_D253_42AE_A542_C454A351949E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <mitab/mitab.h>
#include <ospace/stlex/pointainer.h>

#include "MiTabLayer.h"

// eine MapInfo Datenquelle
class CMiTabDatasource
{
public:
	typedef pointainer<vector<CMiTabLayer *> > CMiTabLayers;
	friend class CLayerIterator;

	CMiTabDatasource() :
		m_fOpened(false), m_fUpdatable(false)
	{
	}
	~CMiTabDatasource()
	{
		_ASSERTE(!IsOpened());		// sollte geschlossen worden sein
	}

	HRESULT Open (const char *pcDirName, bool fUpdate, bool fTestOpen = false);
	HRESULT OpenFile (const char *pcFileName, bool fUpdate, bool fTestOpen);
	HRESULT Close();

// Datenbank ist geöffnet
	bool IsOpened() { return m_fOpened; }

	const char *GetName() { return m_strName.c_str(); }
	int GetLayerCount() { return m_Layers.size(); }

	CMiTabLayer *GetLayer (int iLayer)
	{
		_ASSERTE(0 <= iLayer && iLayer < m_Layers.size());
		return (0 <= iLayer && iLayer < m_Layers.size()) ? m_Layers[iLayer] : NULL;
	}

protected:
	CMiTabLayers & GetLayers() { return m_Layers; }
	
private:
	CMiTabLayers m_Layers;	// sämtliche Shapedateien dieser Datenquelle
	os_string m_strName;	// Name der Datenquelle

	bool m_fOpened;			// Datenbank erfolgreich geöffnet
	bool m_fUpdatable;		// r/o bzw. beschreibbar geöffnet
};

///////////////////////////////////////////////////////////////////////////////
// Iterator über die einzelnen Layer
class CLayerIterator 
{
public:
	CLayerIterator (CMiTabDatasource &rDS) : 
		m_rDS(rDS), m_it (rDS.GetLayers().begin())
	{
	}
	~CLayerIterator()
	{
	}

	CMiTabLayer *GetFirstLayer() { m_it = m_rDS.GetLayers().begin(); return (*m_it); }
	CMiTabLayer *GetNextLayer() { ++m_it; return (m_it != m_rDS.GetLayers().begin()) ? (*m_it) : NULL; }
	
private:
	CMiTabDatasource &m_rDS;
	CMiTabDatasource::CMiTabLayers::iterator m_it;
};

#endif // !defined(_MITABDATASOURCE_H__11CFCEF5_D253_42AE_A542_C454A351949E__INCLUDED_)

