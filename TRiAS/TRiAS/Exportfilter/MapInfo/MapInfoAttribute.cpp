// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:42:11 
//
// @doc
// @module MapInfoAttribute.cpp | Definition of the <c CMapInfoAttribute> class

#include "stdafx.h"
#include "MapInfoImpl.h"

#include <Errinstx.hxx>

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "MapInfoExport.h"
#include "MapInfoAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion
/* static */
DBFFieldType CMapInfoAttribute::GetDBFType(int iTyp)
{
	switch (tolower(iTyp)) {
	case 'a':	
		return FTString;		// erstmal nur Zeichnketten

	case 'i':
		return FTInteger;

	case 'f':
		return FTDouble;
		
	default:
		break;
	}
	return FTInvalid;
}

/* static */
int CMapInfoAttribute::GetIndexFromObjType (int iObjTyp)
{
int iIndex = -1;

	switch (iObjTyp) {
	case OT_PUNKT:
		iIndex = 0;
		break;

	case OT_KANTE:
		iIndex = 1;
		break;

	case OT_FLAECHE:
		iIndex = 2;
		break;

	case OT_TEXT:
		iIndex = 3;
		break;
	}
	_ASSERTE(-1 != iIndex);
	return iIndex;
}

///////////////////////////////////////////////////////////////////////////////
// Finden der Liste aller zu einer Objektklasse gehörenden Attribute
HRESULT CMapInfoAttributes::GetAttributes (INT_PTR lIdent, CMapInfoLayerAttributes **ppMap) 
{
map<INT_PTR, CMapInfoLayerAttributes>::iterator it = find (lIdent);

	if (it != end()) {
		if (NULL != ppMap)
			*ppMap = &(*it).second;
		return S_OK;
	}
	*ppMap = NULL;
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// finden eines Attributes einer Objektklasse
HRESULT CMapInfoAttributes::GetAttribute (INT_PTR lIdent, INT_PTR lMCode, os_string *pAttrName)
{
CMapInfoLayerAttributes *pAttrMap = NULL;

	if (S_OK == GetAttributes (lIdent, &pAttrMap)) {
	CMapInfoLayerAttributes::iterator it = pAttrMap -> find (lMCode);

		if (it != pAttrMap -> end()) {
			if (NULL != pAttrName)
				*pAttrName = (*it).second.GetName();
			return S_OK;
		}
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen eines Attributes einer Objektklasse
HRESULT CMapInfoAttributes::AddAttribute (
	INT_PTR lIdent, INT_PTR lMCode, LPCSTR pcAttrName, int iTyp, int iLen)
{
	if (S_OK == GetAttribute(lIdent, lMCode))
		return E_FAIL;		// diese Kombination existiert bereits

// in Map nach Attributen für den Layer suchen
CMapInfoLayerAttributes *pAttrMap = NULL;

	if (S_OK != GetAttributes (lIdent, &pAttrMap)) {
	pair<iterator, bool> p = insert(value_type (lIdent, CMapInfoLayerAttributes()));

		if (!p.second)
			return E_OUTOFMEMORY;
		pAttrMap = &(*p.first).second;
	}
	_ASSERTE(NULL != pAttrMap);	

// in layerspezifischer Map nach dem Feld suchen
CMapInfoLayerAttributes::iterator it = pAttrMap -> find (lMCode);

	if (it == pAttrMap -> end()) {
	pair<CMapInfoLayerAttributes::iterator, bool> p = pAttrMap -> insert (CMapInfoLayerAttributes::value_type (lMCode, CMapInfoAttribute(pcAttrName, iTyp, iLen)));

		if (!p.second)
			return E_OUTOFMEMORY;
	} 
	return S_OK;
}

