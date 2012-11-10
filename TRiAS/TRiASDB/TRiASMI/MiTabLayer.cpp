// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 14:34:46 
//
// @doc
// @module MiTabLayer.cpp | Definition of the <c CMiTabLayer> class

#include "StdAfx.h"

#include "Strings.h"
#include "TRiASMI.h"

#include "MiTabLayer.h"
#include "TRiASMIObjects.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// required initialization
HRESULT CMiTabLayer::EnsureInitialized(ITRiASObjects *pIObjs)
{
	if (NULL == m_pObjs) {
		RETURN_FAILED_HRESULT(QueryImplementation(pIObjs, &m_pObjs));
		return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Objekttypen
OBJECTTYPE CMiTabLayer::GetTypes() 
{
OBJECTTYPE rgType = OBJECTTYPE_Unknown;
int iPoints = 0;
int iLines = 0;
int iAreas = 0;
int iTexts = 0;

	if (-1 == ((IMapInfoFile *)m_hMIF) -> GetFeatureCountByType(iPoints, iLines, iAreas, iTexts, TRUE))
		return OBJECTTYPE_Unknown;

	if (0 != iPoints)
		SetType(rgType, OBJECTTYPE_Point);
	if (0 != iLines)
		SetType(rgType, OBJECTTYPE_Line);
	if (0 != iAreas)
		SetType(rgType, OBJECTTYPE_Area);
	if (0 != iTexts)
		SetType(rgType, OBJECTTYPE_Text);

	_ASSERTE(OBJECTTYPE_Unknown != rgType || (iPoints+iLines+iAreas+iTexts) == 0);
	return rgType;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert umschließendes Rechteck
HRESULT CMiTabLayer::GetBoundingRect (double *pdXMin, double *pdYMin, double *pdXMax, double *pdYMax, bool fTransform)
{
	_ASSERTE(NULL != pdXMin && NULL != pdXMax && NULL != pdYMin && NULL != pdYMax);
	if (!(NULL != pdXMin && NULL != pdXMax && NULL != pdYMin && NULL != pdYMax))
		return E_POINTER;

// bei der zugehörigen Objektklasse das Koordinatensystem sicherstellen
	THROW_FAILED_HRESULT(m_pObjs -> InitCoordSystem());

// Envelope bestimmen
double dXMin = 0.0;
double dYMin = 0.0;
double dXMax = 0.0;
double dYMax = 0.0;

	if (-1 == ((IMapInfoFile *)m_hMIF) -> GetBounds (dXMin, dYMin, dXMax, dYMax))
		return TRIASMI_E_NO_VALID_ENVELOPE;

	if (fTransform) {
	// in Projektkoordinatensystem umrechnen
		COM_TRY {
		// CS-Transformator besorgen
		WTRiASCSTransform CST (GetPropertyFrom (GetDatabase(), g_cbTRiASCSTransform, (IDispatch *)NULL), false);

			_ASSERTE(CST.IsValid());

		WTRiASSimpleRectangle Rect (CLSID_TRiASCSRectangleGeometry);
		CSID cssGuid;
		 	
			THROW_FAILED_HRESULT(WPersistStreamInit(Rect) -> InitNew());
			THROW_FAILED_HRESULT(Rect -> SetRect (dXMin, dYMin, dXMax, dYMax));
			THROW_FAILED_HRESULT(GetCSSGuid(cssGuid));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(Rect) -> Transform (cssGuid, CST));
			THROW_FAILED_HRESULT(Rect -> GetRect (&dXMin, &dYMin, &dXMax, &dYMax));

		} COM_CATCH;
	}
	
	*pdXMin = dXMin;
	*pdYMin = dYMin;
	*pdXMax = dXMax;
	*pdYMax = dYMax;
	return S_OK;
}

// Liefert das übergeordnete Datenbank-Objekt
IDispatch *CMiTabLayer::GetDatabase()
{
	if (NULL == m_pObjs)
		return NULL;

WTRiASDatabase DBase;

	if (FAILED(FindSpecificParent(m_pObjs -> GetControllingUnknown(), DBase.ppi())))
		return NULL;

	return DBase.detach();
}

HRESULT CMiTabLayer::GetCSSGuid(CSID &rGuid)
{
	if (NULL == m_pObjs)
		return E_UNEXPECTED;

	rGuid = (CSID &)m_pObjs -> GetCSSGuid();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung aller Felder der Datenquelle
HRESULT CMiTabLayer::InitFields()
{
	COM_TRY {
	// ShapeID erzeugen und einbauen
		m_Fields.push_back (new CMiTabFieldID());

	// sämtliche zugehörigen Felder einbauen
		for (int i = 0; i < mitab_c_get_field_count(m_hMIF); ++i) 
			m_Fields.push_back (new CMiTabField (m_hMIF, i, m_fUpdate));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// MiTabObject: Objekttyp bestimmen
OBJECTTYPE CMiTabObject::GetObjectType()
{
	switch (mitab_c_get_type(m_rObj)) {
	case TABFC_Point:
	case TABFC_FontPoint:
	case TABFC_CustomPoint:
		return OBJECTTYPE_Point;

	case TABFC_Polyline:
		return OBJECTTYPE_Line;

	case TABFC_Region:
	case TABFC_Rectangle:
		return OBJECTTYPE_Area;

	case TABFC_Text:
		return OBJECTTYPE_Text;
		
	case TABFC_NoGeom:
	case TABFC_Arc:
	case TABFC_Ellipse:
		break;				// not supported yet
	}
	return OBJECTTYPE_Unknown;
}


///////////////////////////////////////////////////////////////////////////////
// CMiTabField
FEATURETYPE CMiTabField::GetFeatureType (int rgFieldType)
{
FEATURETYPE rgType = FEATURETYPE_Object;

	if (!m_fUpdate)
		rgType = FEATURETYPE(rgType|FEATURETYPE_ReadOnly);

	switch (rgFieldType) {
	case TABFT_Char:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_BSTR));
		break;

	case TABFT_Integer:
	case TABFT_SmallInt:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_I4));
		break;

	case TABFT_Float:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_R8));
		break;

	case TABFT_Date:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_DATE));
		break;

	case TABFT_Decimal:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_DECIMAL));
		break;

	case TABFT_Logical:
		rgType = FEATURETYPE(rgType|DATATYPE_FROM_VT(VT_BOOL));
		break;

	default:
		rgType = FEATURETYPE_Unknown;
		break;
	}
	return rgType;
}

///////////////////////////////////////////////////////////////////////////////
// ein Attribut lesen/schreiben
HRESULT CMiTabField::Eval (int iFeatureid, BSTR *pbstrVal)
{
	_ASSERTE(IsValid() && iFeatureid >= 0 && NULL != pbstrVal);
	if (NULL == pbstrVal)
		return E_POINTER;
	*pbstrVal = NULL;

	if (!IsValid())
		return E_UNEXPECTED;
	if (0 > iFeatureid)
		return E_INVALIDARG;

	COM_TRY {
	CMiTabObject Obj (mitab_c_read_feature(m_hMIF, iFeatureid));

		if (!Obj.IsValid())
			return TRIASDB_E_NOSUCHFEATURE;
			
	LPCSTR pcAttr = mitab_c_get_field_as_string(Obj, m_iField);

		if (NULL == pcAttr || '\0' == *pcAttr) 
			return TRIASDB_E_NOSUCHFEATURE;

	CComBSTR bstrVal (pcAttr);

		*pbstrVal = bstrVal.Detach();

	} COM_CATCH;
	return S_OK;
}

#if defined(_READWRITE)
HRESULT CMiTabField::Update (int iFeatureId, BSTR bstrValue)
{
	_ASSERTE(IsValid() && iFeatureId >= 0 && NULL != bstrValue);

	if (!IsValid())
		return E_UNEXPECTED;
	if (0 > iFeatureId)
		return E_INVALIDARG;

	USES_CONVERSION;

CMiTabObject Obj (mitab_c_read_feature(m_hMIF, iFeatureid));

	if (!Obj.IsValid())
		return TRIASDB_E_NOSUCHFEATURE;
	mitab_c_set_field (Obj, m_iField, OLE2A(bstrVal);
	return S_OK;
}
#endif // defined(_READWRITE)

