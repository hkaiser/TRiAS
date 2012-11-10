// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.05.2000 17:12:43
//
// @doc
// @module ShapeLayer.cpp | Implementation of the <c CShapeLayer> class

#include "StdAfx.h"

#include "Strings.h"
#include "TRiASHP.h"

#include <Shapelib/Shapefil.h>
#include "ShapeLayer.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Liefert Objekttypen
OBJECTTYPE CShapeLayer::GetTypes() 
{
OBJECTTYPE rgType = OBJECTTYPE_Unknown;
int nShapeType = 0;
int iCnt = 0;

	SHPGetInfo (m_hSHP, &iCnt, &nShapeType, NULL, NULL);
	switch (nShapeType) {
	case SHPT_POINT:
	case SHPT_POINTM:
	case SHPT_POINTZ:
		rgType = OBJECTTYPE_Point;
		break;

	case SHPT_MULTIPOINT:
	case SHPT_MULTIPOINTM:
	case SHPT_MULTIPOINTZ:
		break;

	case SHPT_ARC:
	case SHPT_ARCM:
	case SHPT_ARCZ:
		rgType = OBJECTTYPE_Line;
		break;

	case SHPT_POLYGON:
	case SHPT_POLYGONZ:
	case SHPT_POLYGONM:
		rgType = OBJECTTYPE_Area;
		break;
	}

	_ASSERTE(OBJECTTYPE_Unknown != rgType || iCnt == 0);
	return rgType;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert umschließendes Rechteck
HRESULT CShapeLayer::GetBoundingRect (double *pdXMin, double *pdYMin, double *pdXMax, double *pdYMax)
{
	_ASSERTE(NULL != pdXMin && NULL != pdXMax && NULL != pdYMin && NULL != pdYMax);
	if (!(NULL != pdXMin && NULL != pdXMax && NULL != pdYMin && NULL != pdYMax))
		return E_POINTER;

double dMin[4], dMax[4];

	SHPGetInfo (m_hSHP, NULL, NULL, dMin, dMax);

	*pdXMin = dMin[0];
	*pdYMin = dMin[1];
	*pdXMax = dMax[0];
	*pdYMax = dMax[1];
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektanzahl
int CShapeLayer::GetObjectCount()
{
int iCnt = 0;

	SHPGetInfo (m_hSHP, &iCnt, NULL, NULL, NULL);
	return iCnt;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung aller Felder der Datenquelle
HRESULT CShapeLayer::InitFields()
{
	COM_TRY {
	// ShapeID erzeugen und einbauen
		m_Fields.push_back (new CShapeFieldID());

	// sämtliche zugehörigen Felder einbauen
		for (int i = 0; i < DBFGetFieldCount(m_hDBF); ++i) 
			m_Fields.push_back (new CShapeField (m_hDBF, i, m_fUpdate));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CShapeField
FEATURETYPE CShapeField::GetFeatureType (DBFFieldType rgShapeType)
{
FEATURETYPE rgType = FEATURETYPE_Unknown;

	if (!m_fUpdate)
		rgType = FEATURETYPE_ReadOnly;

	switch (rgShapeType) {
	case FTString:
		rgType = FEATURETYPE(rgType|FEATURETYPE_Object|DATATYPE_FROM_VT(VT_BSTR));
		break;

	case FTInteger:
		rgType = FEATURETYPE(rgType|FEATURETYPE_Object|DATATYPE_FROM_VT(VT_I4));
		break;

	case FTDouble:
		rgType = FEATURETYPE(rgType|FEATURETYPE_Object|DATATYPE_FROM_VT(VT_R8));
		break;

	case FTLogical:
		rgType = FEATURETYPE(rgType|FEATURETYPE_Object|DATATYPE_FROM_VT(VT_BOOL));
		break;

	case FTInvalid:
		break;
	}
	return rgType;
}

///////////////////////////////////////////////////////////////////////////////
// ein Attribut lesen/schreiben
HRESULT CShapeField::Eval (int iShape, BSTR *pbstrVal)
{
	_ASSERTE(IsValid() && iShape >= 0 && NULL != pbstrVal);
	if (NULL == pbstrVal)
		return E_POINTER;
	*pbstrVal = NULL;

	if (!IsValid())
		return E_UNEXPECTED;
	if (0 > iShape)
		return E_INVALIDARG;

	COM_TRY {
	LPCSTR pcAttr = DBFReadStringAttribute (m_hDBF, iShape, m_iField);

		if (NULL == pcAttr || '\0' == *pcAttr) 
			return TRIASDB_E_NOSUCHFEATURE;

	CComBSTR bstrVal (pcAttr);

		*pbstrVal = bstrVal.Detach();

	} COM_CATCH;
	return S_OK;
}

#if defined(_READWRITE)
HRESULT CShapeField::Update (int iShape, BSTR bstrValue)
{
	_ASSERTE(IsValid() && iShape >= 0 && NULL != bstrVal);
	if (NULL == pbstrVal)
		return E_POINTER;
	*pbstrVal = NULL;

	if (!IsValid())
		return E_UNEXPECTED;
	if (0 > iShape)
		return E_INVALIDARG;

	USES_CONVERSION;
	return DBFWriteStringAttribute (m_hDBF, iShape, m_iField, OLE2A(bstrVal)) ? S_OK : E_UNEXPECTED;
}
#endif // defined(_READWRITE)
