// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:40:03 
//
// @doc
// @module MapInfoDataSource.h | Declaration of the <c CMapInfoDataSource> class

#if !defined(_MAPINFODATASOURCE_H__BE495D7B_A313_4538_9F92_AF8C39FF4E45__INCLUDED_)
#define _MAPINFODATASOURCE_H__BE495D7B_A313_4538_9F92_AF8C39FF4E45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stlex/pointainer.h>
#include "MapInfoLayer.h"
#include "MapInfoAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// repräsentiert sämtliche zu exportierenden Layer
class CMapInfoDataSource
{
public:
// die Menge aller MapInfo Layer 
	typedef multimap<INT_PTR, CMapInfoLayer *> CMapInfoLayerMap;
	typedef pointainer<CMapInfoLayerMap, clean_pair_second<CMapInfoLayerMap> > CMapInfoLayers;

	CMapInfoDataSource() : m_rgMode(OMOverwrite) {}
	~CMapInfoDataSource() {}

	HRESULT CreateLayer (INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, CMapInfoLayer **ppLayer);
	HRESULT GetLayer (INT_PTR lIdent, OBJECTTYPE rgType, CMapInfoLayer **ppLayer);
	HRESULT CloseAll();
	HRESULT DeleteAllFiles(); 
	
	bool SetRootDir (LPCSTR pcRootDir, OutMode rgMode)
	{
		m_strRootDir = pcRootDir;
		m_rgMode = rgMode;
		return true;
	}
	LPCSTR GetRootDir() { return m_strRootDir.c_str(); }

// Attribute
	HRESULT GetAttribute (INT_PTR lMCode)
	{
		return m_Attribs.GetAttribute(DEX_GetFeatureIdent(lMCode), lMCode);
	}
	HRESULT AddAttribute (INT_PTR lMCode, LPCSTR pcName, int iTyp, int iLen)
	{
		return m_Attribs.AddAttribute(DEX_GetFeatureIdent(lMCode), lMCode, pcName, iTyp, iLen);
	}
	HRESULT GetAttributes (INT_PTR lIdent, CMapInfoLayerAttributes **ppMap)
	{
		return m_Attribs.GetAttributes(lIdent, ppMap);
	}

private:
	os_string m_strRootDir;
	OutMode m_rgMode;
	CMapInfoLayers m_Layers;
	CMapInfoAttributes m_Attribs;
};

#endif // !defined(_MAPINFODATASOURCE_H__BE495D7B_A313_4538_9F92_AF8C39FF4E45__INCLUDED_)
