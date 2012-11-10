// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:41:41 
//
// @doc
// @module MapInfoAttribute.h | Declaration of the <c CMapInfoAttribute> class

#if !defined(_MAPINFOATTRIBUTE_H__C5D81B96_B646_4709_A3C0_A4C3B9E1E5D7__INCLUDED_)
#define _MAPINFOATTRIBUTE_H__C5D81B96_B646_4709_A3C0_A4C3B9E1E5D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ein Attribut eines MapInfoLayers
class CMapInfoAttribute
{
public:
	CMapInfoAttribute(LPCSTR pcName, int iTyp, int iLen) :
		m_strName(pcName), m_iTyp(GetDBFType(iTyp)), m_iLen(iLen) 
	{
		for (int i = 0; i < _countof(m_iField); ++i)
			m_iField[i] = -1;
	}
	~CMapInfoAttribute() {}

	LPCSTR GetName() { return m_strName.c_str(); }
	DBFFieldType GetTyp() { return m_iTyp; }
	int GetLen() { return m_iLen; }
	int GetDecimals() { return (FTDouble == GetTyp()) ? 5 : 0; }	// willkürliche Festlegung

	int GetField(int iObjTyp) { return m_iField[GetIndexFromObjType(iObjTyp)]; }
	void SetField (int iField, int iObjTyp) { m_iField[GetIndexFromObjType(iObjTyp)] = iField; }

	static DBFFieldType GetDBFType(int iTyp);
	static GetIndexFromObjType (int iObjTyp);

private:
	os_string m_strName;
	DBFFieldType m_iTyp;
	int m_iLen;
	int m_iField[4];
};


///////////////////////////////////////////////////////////////////////////////
// die Menge aller Attribute (eines Layers bzw. des gesamten Exportes)
typedef map<INT_PTR, CMapInfoAttribute> CMapInfoLayerAttributes;		// MCode --> AttributeName
typedef map<INT_PTR, CMapInfoLayerAttributes> CMapInfoAttributesBase;	// Ident --> CMapInfoLayerAttributes

class CMapInfoAttributes :
	public CMapInfoAttributesBase
{
public:
	CMapInfoAttributes() {}
	~CMapInfoAttributes() {}

	HRESULT GetAttributes (INT_PTR lIdent, CMapInfoLayerAttributes **ppMap = NULL);

	HRESULT GetAttribute (INT_PTR lIdent, INT_PTR lMCode, os_string *pAttrName = NULL);
	HRESULT AddAttribute (INT_PTR lIdent, INT_PTR lMCode, LPCSTR pcAttrName, int iTyp, int iLen);
};

#endif // !defined(_MAPINFOATTRIBUTE_H__C5D81B96_B646_4709_A3C0_A4C3B9E1E5D7__INCLUDED_)
