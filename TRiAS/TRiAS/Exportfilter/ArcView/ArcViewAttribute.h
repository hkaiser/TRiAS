// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.07.2000 19:02:09 
//
// @doc
// @module ArcViewAttribute.h | Declaration of the <c CArcViewAttribute> class

#if !defined(_ARCVIEWATTRIBUTE_H__BB488A5F_F08B_4B39_B775_DD3F33F2C5F9__INCLUDED_)
#define _ARCVIEWATTRIBUTE_H__BB488A5F_F08B_4B39_B775_DD3F33F2C5F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ein Attribut eines ArcViewLayers
class CArcViewAttribute
{
public:
	CArcViewAttribute(LPCSTR pcName, int iTyp, int iLen) :
		m_strName(pcName), m_iTyp(GetDBFType(iTyp)), m_iLen(iLen) 
	{
		for (int i = 0; i < _countof(m_iField); ++i)
			m_iField[i] = -1;
	}
	~CArcViewAttribute() {}

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
typedef map<INT_PTR, CArcViewAttribute> CArcViewLayerAttributes;		// MCode --> AttributeName
typedef map<INT_PTR, CArcViewLayerAttributes> CArcViewAttributesBase;	// Ident --> CArcViewLayerAttributes

class CArcViewAttributes :
	public CArcViewAttributesBase
{
public:
	CArcViewAttributes() {}
	~CArcViewAttributes() {}

	HRESULT GetAttributes (INT_PTR lIdent, CArcViewLayerAttributes **ppMap = NULL);

	HRESULT GetAttribute (INT_PTR lIdent, INT_PTR lMCode, os_string *pAttrName = NULL);
	HRESULT AddAttribute (INT_PTR lIdent, INT_PTR lMCode, LPCSTR pcAttrName, int iTyp, int iLen);
};

#endif // !defined(_ARCVIEWATTRIBUTE_H__BB488A5F_F08B_4B39_B775_DD3F33F2C5F9__INCLUDED_)
