// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 14:15:00 
//
// @doc
// @module ArcViewDataSource.h | Declaration of the <c CArcViewDataSource> class

#if !defined(_ARCVIEWDATASOURCE_H__E7EFD63E_1355_4DCE_AC20_01F1E4B2343D__INCLUDED_)
#define _ARCVIEWDATASOURCE_H__E7EFD63E_1355_4DCE_AC20_01F1E4B2343D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stlex/pointainer.h>
#include "ArcViewLayer.h"
#include "ArcViewAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// repräsentiert sämtliche zu exportierenden Layer
class CArcViewDataSource
{
public:
// die Menge aller ArcView Layer 
	typedef multimap<INT_PTR, CArcViewLayer *> CArcViewLayerMap;
	typedef pointainer<CArcViewLayerMap, clean_pair_second<CArcViewLayerMap> > CArcViewLayers;

	CArcViewDataSource() : m_rgMode(OMOverwrite) {}
	~CArcViewDataSource() {}

	enum OPENMODE {
		OPENMODE_Create,
		OPENMODE_Append,
	};

	HRESULT OpenLayer (INT_PTR lIdent, LPCSTR pcName, OBJECTTYPE rgType, OPENMODE rgMode, CArcViewLayer **ppLayer);
	HRESULT GetLayer (INT_PTR lIdent, OBJECTTYPE rgType, CArcViewLayer **ppLayer = NULL);
	HRESULT GetLayer (LPCSTR pcName, OBJECTTYPE rgType, CArcViewLayer **ppLayer = NULL);
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
	HRESULT GetAttributes (INT_PTR lIdent, CArcViewLayerAttributes **ppMap)
	{
		return m_Attribs.GetAttributes(lIdent, ppMap);
	}

private:
	os_string m_strRootDir;
	OutMode m_rgMode;
	CArcViewLayers m_Layers;
	CArcViewAttributes m_Attribs;
};


#endif // !defined(_ARCVIEWDATASOURCE_H__E7EFD63E_1355_4DCE_AC20_01F1E4B2343D__INCLUDED_)
