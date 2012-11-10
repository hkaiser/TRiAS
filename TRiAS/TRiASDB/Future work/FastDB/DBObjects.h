// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.02.2000 11:46:22 
//
// @doc
// @module DBObjects.h | Declaration of the <c CDBObjects> class

#if !defined(_DBOBJECTS_H__5162CFF5_94B5_4706_A702_E6014019C247__INCLUDED_)
#define _DBOBJECTS_H__5162CFF5_94B5_4706_A702_E6014019C247__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Tabellendefintion für TRiASMemDB
class CDBDatabase;
class CDBObject;
class CDBClass;
class CDBFeatureDesc;
class CDBFeature;

/////////////////////////////////////////////////////////////////////////////
// Datenbankklasse
class CDBDatabase :
	public dbDatabase
{
public:
	void handleError (dbErrorClass error, char const* msg, int arg);

	bool IsDirty() { return modified; }
	void SetDirty(bool fFlag) { modified = fFlag; }

	bool IsOpened() { return opened; }
};
#define FASTDATABASE_VERSION_100		100
#define LASTKNOWN_FASTDATABASE_VERSION	FASTDATABASE_VERSION_100

///////////////////////////////////////////////////////////////////////////////
// Datenbankeingenschaften
class CDBHeader
{
public:
	CDBHeader() :
		m_pKey(""), m_rgType(PROPERTY_TYPE_Normal)
	{
		m_Data.append(0);
	}

	char *m_pKey;			// Name der Eigenschaft
	dbArray<byte> m_Data;	// gestreamter Variant
	int4 m_rgType;			// PROPERTY_TYPE

	HRESULT SetValue (VARIANT Val);
	HRESULT GetValue (VARIANT *pVal);

	TYPE_DESCRIPTOR((
		KEY2(m_pKey, INDEXED|HASHED, "KEY"), 
		FIELD2(m_Data, "DATA"),
		FIELD2(m_rgType, "TYPE")
	));
};

///////////////////////////////////////////////////////////////////////////////
// eine Objektklassenbeschreibung
class CDBClass
{
public:
	CDBClass() :
		m_pOKS(g_cbNil), m_pName(g_cbNil), m_pDesc(g_cbNil),
		m_lPoints(0), m_lLines(0), m_lAreas(0), m_lTexts(0), m_fROMode(false),
		m_pGeometryName(g_cbNil), m_pPrimaryKey(g_cbNil)
	{
	}

	const char *m_pOKS;		// Objektklassenschlüssel
	const char *m_pName;	// kurzer Beschreibungstext
	const char *m_pDesc;	// langer Beschreibungstext
	int4 m_lPoints;			// Zähler der zugehöörigen Objekte
	int4 m_lLines;
	int4 m_lAreas;
	int4 m_lTexts; 
	byte m_fROMode;			// Objektklasse ist schreibgeschützt
	const char *m_pGeometryName;	// Name des Geometriefeldes
	const char *m_pPrimaryKey;		// Name des Schlüsselfeldes

    dbArray<dbReference<CDBObject> > objects;				// zugehörige Objekte
    dbArray<dbReference<CDBFeatureDesc> > featuredescs;		// zugehörige ObjektEigenschaften

	TYPE_DESCRIPTOR((
		KEY2(m_pOKS, INDEXED|HASHED, "OKS"), 
		KEY2(m_pName, INDEXED|HASHED, "NAME"),
		FIELD2(m_pDesc, "DESCRIPTION"),
		FIELD2(m_lPoints, "POINTCOUNT"),
		FIELD2(m_lLines, "LINECOUNT"),
		FIELD2(m_lAreas, "AREACOUNT"),
		FIELD2(m_lTexts, "TEXTCOUNT"),
		FIELD2(m_fROMode, "ROMODE"),
		FIELD2(m_pGeometryName, "GEOMETRYNAME"),
		FIELD2(m_pPrimaryKey, "PRIMARYKEY"),
		RELATION(objects, objclass),
		RELATION(featuredescs, objclass)
	));
};

///////////////////////////////////////////////////////////////////////////////
// ein einzelnes Objekt 
class CDBObject
{
public:
	CDBObject() :
		m_rgType(OBJECTTYPE_Unknown)
	{
		CoCreateGuid(&m_objGuid);
		m_Geometry.append(0);
	}

	int4 m_rgType;					// Objekttyp (OBJECTTYPE)
	GUID m_objGuid;
	dbArray<byte> m_Geometry;		// GeometryBlob
	class CONTAINER {				// umschließendes Rechteck
	public:
		CONTAINER() { m_dXMin = m_dXMax = m_dYMin = m_dYMax = 0.0; }

		real8 m_dXMin, m_dXMax;
		real8 m_dYMin, m_dYMax;
	} m_Container;

    dbReference<CDBClass> objclass;					// Objektklasse
    dbArray<dbReference<CDBFeature> > features;		// zugehörige ObjektEigenschaften (Werte)

	TYPE_DESCRIPTOR((
		FIELD2(m_rgType, "TYPE"),
		RAWFIELD2(m_objGuid, "GUID"),
		FIELD2(m_Geometry, "GEOMETRY"),
		RAWFIELD2(m_Container, "CONTAINER"),
		RELATION(objclass, objects),
		OWNER(features, object)
	));
};

///////////////////////////////////////////////////////////////////////////////
// eine einzelne Objekteigenschaft (Beschreibung)
class CDBFeatureDesc
{
public:
	CDBFeatureDesc() :
		m_pName(""), m_pDesc("")
	{
	}

	char *m_pName;
	char *m_pDesc;
	int4 m_rgType;
	bool m_fROMode;

    dbReference<CDBClass> objclass;					// Objektklasse
    dbArray<dbReference<CDBFeature> > features;		// zugehörige ObjektEigenschaften (Werte)

	TYPE_DESCRIPTOR((
		KEY2(m_pName, INDEXED, "NAME"),
		FIELD2(m_pDesc, "DESCRIPTION"),
		FIELD2(m_rgType, "TYPE"),
		FIELD2(m_fROMode, "ROMODE"),
		RELATION(objclass, featuredescs),
		RELATION(features, featuredesc)
	));
};
 
///////////////////////////////////////////////////////////////////////////////
// eine einzelne Objekteigenschaft
class CDBFeature
{
public:
	CDBFeature() : m_pValue("")
	{
	}

	char *m_pValue;

    dbReference<CDBObject> object;				// Objekt, zu dem diese Objekteigenschaft gehört
    dbReference<CDBFeatureDesc> featuredesc;	// zugehörige Objekteigenschaftsbeschreibung

	TYPE_DESCRIPTOR((
		KEY2(m_pValue, INDEXED|HASHED, "VALUE"),
		RELATION(object, features),
		RELATION(featuredesc, features)
	));
};
 

///////////////////////////////////////////////////////////////////////////////
// Helperroutinen
inline
OBJECTTYPE GetTypes (dbCursor<CDBClass> &rCursor)
{
OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

	if (rCursor -> m_lPoints > 0)
		SetType (rgTypes, OBJECTTYPE_Point);
	if (rCursor -> m_lLines > 0)
		SetType (rgTypes, OBJECTTYPE_Line);
	if (rCursor -> m_lAreas > 0)
		SetType (rgTypes, OBJECTTYPE_Area);
	if (rCursor -> m_lTexts > 0)
		SetType (rgTypes, OBJECTTYPE_Text);
	return rgTypes;
}

inline 
long AdjustObjectCount (dbCursor<CDBClass> &rCursor, OBJECTTYPE rgType)
{
long lCnt = 0;

	switch (rgType) {
	case OBJECTTYPE_Point:
		lCnt = ++(rCursor -> m_lPoints);
		break;

	case OBJECTTYPE_Line:
		lCnt = ++(rCursor -> m_lLines);
		break;

	case OBJECTTYPE_Area:
		lCnt = ++(rCursor -> m_lAreas);
		break;

	case OBJECTTYPE_Text:
		lCnt = ++(rCursor -> m_lTexts);
		break;

	default:
		return 0;
	}
	return lCnt;
}

#endif // !defined(_DBOBJECTS_H__5162CFF5_94B5_4706_A702_E6014019C247__INCLUDED_)
