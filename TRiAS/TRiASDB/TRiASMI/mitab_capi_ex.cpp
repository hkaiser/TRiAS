// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 22:40:57 
//
// @doc
// @module mitab_capi_ex.cpp | Additional functions for the mitab C-API

#include "StdAfx.h"

#include <mitab/mitab.h>
#include "mitab_capi_ex.h"

#if MITAB_VERSION_INT == 1003000
// fehlt in V1.3.0
int MITAB_STDCALL
mitab_c_get_feature_id( mitab_feature feature)
{
    TABFeature	*poFeature = (TABFeature *) feature;
	return poFeature -> GetFID();
}
#endif

///////////////////////////////////////////////////////////////////////////////
// retrieve width of a field
#if MITAB_VERSION_INT < 1003000
// ab V1.3.0 vorhanden
int MITAB_STDCALL
mitab_c_get_field_width( mitab_handle handle, int field )
{
    IMapInfoFile	*poFile = (IMapInfoFile *) handle;
    OGRFeatureDefn      *poDefn;
    OGRFieldDefn        *poFDefn;

    if (poFile && 
        (poDefn = poFile->GetLayerDefn()) != NULL &&
        (poFDefn = poDefn->GetFieldDefn(field)) != NULL)
    {
        return poFDefn->GetWidth();
    }

    return -1;
}
#endif

/************************************************************************/
/*                          mitab_c_get_text()                          */
/************************************************************************/

/**
 * Get the text string on a TABFC_Text object.
 *
 * @param feature the mitab_feature object.
 */

#if MITAB_VERSION_INT < 1003000
// ab V1.3.0 vorhanden
const char * MITAB_STDCALL
mitab_c_get_text( mitab_feature feature )

{
    TABText	*poFeature = (TABText *) feature;

    if( poFeature->GetFeatureClass() == TABFC_Text )
        return poFeature->GetTextString();

	return NULL;
}
#endif

/************************************************************************/
/*                          mitab_c_get_text_angle()                    */
/************************************************************************/

/** 
 * Get a TABFC_Text text angle
 *
 * @param feature the mitab_feature object.
 */

#if MITAB_VERSION_INT < 1003000
// ab V1.3.0 vorhanden
double MITAB_STDCALL
mitab_c_get_text_angle( mitab_feature feature )

{
    TABText	*poFeature = (TABText *) feature;

    if( poFeature->GetFeatureClass() == TABFC_Text )
        return poFeature->GetTextAngle();
	return 0.0;
}
#endif

/************************************************************************/
/*                          mitab_c_get_text_alignment()                    */
/************************************************************************/

/** 
 * Get a TABFC_Text text alignment
 *
 * @param feature the mitab_feature object.
 */

TABTextJust MITAB_STDCALL
mitab_c_get_text_alignment( mitab_feature feature )

{
    TABText	*poFeature = (TABText *) feature;

    if( poFeature->GetFeatureClass() == TABFC_Text )
        return poFeature->GetTextJustification();
	return TABTJLeft;
}

/************************************************************************/
/*                          mitab_c_get_mbr()                           */
/************************************************************************/

/** 
 * Get minimum bounding rect of a feature
 *
 * @param feature the mitab_feature object.
 */

bool MITAB_STDCALL
mitab_c_get_mbr( mitab_feature feature, double &rdXMin, double &rdYMin, double &rdXMax, double &rdYMax)
{
    TABFeature	*poFeature = (TABText *) feature;

    if( poFeature->GetFeatureClass() != TABFCNoGeomFeature ) {
        poFeature->GetMBR(rdXMin, rdYMin, rdXMax, rdYMax);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// get raw coordinates of a feature
const OGRRawPoint * MITAB_STDCALL
mitab_c_get_raw_coords (mitab_feature feature, int iPart)
{
    TABFeature	*poFeature = (TABFeature *) feature;
    OGRGeometry *poGeom = NULL;

    if( poFeature->GetFeatureClass() == TABFC_Polyline )
    {
	// Polyline
        TABPolyline *poPolyline = (TABPolyline *)poFeature;
        OGRLineString *poLine = poPolyline->GetPartRef(iPart);
        if (poLine)
			return poLine -> getPoints();
    }
    else if( poFeature->GetFeatureClass() == TABFC_Region ) {
	// Region
        TABRegion *poRegion = (TABRegion *)poFeature;
        OGRLinearRing *poRing = poRegion->GetRingRef(iPart);
        if (poRing)
			return poRing -> getPoints();
    }
    else if ( (poGeom = poFeature->GetGeometryRef()) != NULL &&
              poGeom->getGeometryType() == wkbPoint)
    {
	// Single point: text and point objects
        if (iPart != 0)
            return NULL;  /* Invalid part number */

        OGRPoint *poPoint = (OGRPoint *)poGeom;
        if (poPoint)
			return poPoint -> getPoints();
    }
    else if ( poGeom && poGeom->getGeometryType() == wkbLineString) {
	// LineString: Arc object
        if (iPart != 0)
            return NULL;  /* Invalid part number */

        OGRLineString *poLine = (OGRLineString*)poGeom;
        if (poLine)
			return poLine -> getPoints();
    }
    else if ( poGeom && poGeom->getGeometryType() == wkbPolygon) {
	// Polygon: Rectangle or Ellipse object
        if (iPart != 0)
            return NULL;  /* Invalid part number */

        OGRPolygon *poPoly = (OGRPolygon*)poGeom;
        OGRLinearRing *poRing = poPoly->getExteriorRing();

        if (poRing)
			return poRing -> getPoints();
    }
    return NULL;  /* Requested info could not be returned */
}
