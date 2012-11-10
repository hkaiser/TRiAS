// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.07.2000 19:37:52
//
// @doc
// @module ArcViewAttribute.cpp | Implementation of the <c CArcViewAttribute> class

#include "stdafx.h"
#include "ArcViewImpl.h"

#include <Errinstx.hxx>

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "ArcViewExport.h"
#include "ArcViewAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion
/* static */
DBFFieldType CArcViewAttribute::GetDBFType(int iTyp)
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
int CArcViewAttribute::GetIndexFromObjType (int iObjTyp)
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
HRESULT CArcViewAttributes::GetAttributes (INT_PTR lIdent, CArcViewLayerAttributes **ppMap) 
{
map<INT_PTR, CArcViewLayerAttributes>::iterator it = find (lIdent);

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
HRESULT CArcViewAttributes::GetAttribute (INT_PTR lIdent, INT_PTR lMCode, os_string *pAttrName)
{
CArcViewLayerAttributes *pAttrMap = NULL;

	if (S_OK == GetAttributes (lIdent, &pAttrMap)) {
	CArcViewLayerAttributes::iterator it = pAttrMap -> find (lMCode);

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
HRESULT CArcViewAttributes::AddAttribute (
	INT_PTR lIdent, INT_PTR lMCode, LPCSTR pcAttrName, int iTyp, int iLen)
{
	if (S_OK == GetAttribute(lIdent, lMCode))
		return E_FAIL;		// diese Kombination existiert bereits

// in Map nach Attributen für den Layer suchen
CArcViewLayerAttributes *pAttrMap = NULL;

	if (S_OK != GetAttributes (lIdent, &pAttrMap)) {
	pair<iterator, bool> p = insert(value_type (lIdent, CArcViewLayerAttributes()));

		if (!p.second)
			return E_OUTOFMEMORY;
		pAttrMap = &(*p.first).second;
	}
	_ASSERTE(NULL != pAttrMap);	

// in layerspezifischer Map nach dem Feld suchen
CArcViewLayerAttributes::iterator it = pAttrMap -> find (lMCode);

	if (it == pAttrMap -> end()) {
	os_string strName (CorrectName(pcAttrName));
	pair<CArcViewLayerAttributes::iterator, bool> p = pAttrMap -> insert (
		CArcViewLayerAttributes::value_type (lMCode, 
		CArcViewAttribute(strName.c_str(), iTyp, iLen)));

		if (!p.second)
			return E_OUTOFMEMORY;
	} 
	return S_OK;
}

