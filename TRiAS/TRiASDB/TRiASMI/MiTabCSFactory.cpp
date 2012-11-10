// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 10:23:05 
//
// @doc
// @module MiTabCSFactory.cpp | Definition of the <c CMiTabCSFactory> class

#include "StdAfx.h"

#include "Strings.h"
#include "MiTabCSFactory.h"

///////////////////////////////////////////////////////////////////////////////
// TRiASCS Koordinatensystem aus dem MapInfo Layer bestimmen
HRESULT CMiTabCSFactory::RetrieveCS (ITRiASCS **ppICS)
{
	TEST_OUT_PARAM(ppICS);

	_ASSERTE(NULL != m_pLayer);		// muß gegeben sein
	COM_TRY {
	WTRiASCS CS (CLSID_TRIASCS);
	OGRSpatialReference *pOgrSrs = m_pLayer -> GetSpatialRef();

		if (NULL != pOgrSrs) {
		// Koordinatensystem ist direkt gegeben
	    const char *pcProj = pOgrSrs -> GetAttrValue("PROJECTION");
		bool fIsGeographic = pOgrSrs -> IsGeographic();
		
		// geodätisches System
			THROW_FAILED_HRESULT(CS -> put_CoordSystemType(fIsGeographic ? tcsCS_Geographic : tcsCS_Projected));
			THROW_FAILED_HRESULT(InitGCS (pOgrSrs, CS));

			if (!fIsGeographic) {
			// projektives System initialisieren
				_ASSERTE(NULL == pcProj || pOgrSrs -> IsProjected());
				THROW_FAILED_HRESULT(InitPCS (pOgrSrs, pcProj, CS));
			}
		}
		else {
		// es wird ein NonEarth Koordinatensystem angenommen
			_ASSERTE(SUCCEEDED(E_NOTIMPL));		// not implemented yet
		}

	// Resultat liefern
		*ppICS = CS.detach();
				
	} COM_CATCH;
	return S_OK;
}

HRESULT CMiTabCSFactory::InitGCS (OGRSpatialReference *pOgrSrs, ITRiASCS *pICS)
{
// geod. Datum rauskriegen
TRIASCSGEODETICDATUM rgDatum = tcsGD_Undefined;

	THROW_FAILED_HRESULT(GetGeodDatum (pOgrSrs, &rgDatum));

// Koordinatensystem initialisieren
	COM_TRY {
	// Geodätische Grundlage initialisieren
	WTRiASCSGCS GCS;

		THROW_FAILED_HRESULT(pICS -> get_GeographicCS(GCS.ppi()));
		THROW_FAILED_HRESULT(GCS -> put_GeodeticDatum(rgDatum));

	TRIASCSPRIMEMERIDIAN rgPrimeMeridian = tcsPM_Undefined;

		THROW_FAILED_HRESULT(GetPrimeMeridian (pOgrSrs, &rgPrimeMeridian));
		THROW_FAILED_HRESULT(GCS -> put_PrimeMeridian(rgPrimeMeridian));
		THROW_FAILED_HRESULT(GCS -> put_UnitOfAngle(tcsUOA_Degree));

	// Datumsparameter einstellen
	WTRiASCSDatumTransformation DTrans;

		THROW_FAILED_HRESULT(pICS -> get_DatumTransformation(DTrans.ppi()));
		THROW_FAILED_HRESULT(DTrans -> put_GeodeticDatum(rgDatum));
		THROW_FAILED_HRESULT(DTrans -> put_TransformationAlgorithm(tcsDTA_PositionVector7ParamTransformation));

	double dX = 0.0;
	double dY = 0.0;
	double dZ = 0.0;

		if (S_OK == GetTranslations (pOgrSrs, &dX, &dY, &dZ)) {
			THROW_FAILED_HRESULT(DTrans -> put_Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation, dX));
			THROW_FAILED_HRESULT(DTrans -> put_Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation, dY));
			THROW_FAILED_HRESULT(DTrans -> put_Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation, dZ));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Bezugsellipsoid bestimmen
HRESULT CMiTabCSFactory::GetGeodDatum (OGRSpatialReference *pOgrSrs, TRIASCSGEODETICDATUM *prgDatum)
{
	BEGIN_TEST_PARAMS()
		OUT_PARAM(prgDatum);
		IN_PARAM(pOgrSrs);
	END_OUT_PARAMS()

	*prgDatum = tcsGD_Undefined;

double dfSemiMajor = pOgrSrs -> GetSemiMajor();
double dfInvFlattening = pOgrSrs -> GetInvFlattening();
//const char *pszDatum = pOgrSrs -> GetAttrValue("DATUM");
TRIASCSGEODETICDATUM rgDatum = tcsGD_Undefined;

	if (ABS(dfSemiMajor - 6378245.0) < 0.01 && ABS(dfInvFlattening - 298.3) < 0.0001)
	{
		rgDatum = tcsGD_Pulkovo1942;				/* Krassovsky */
	}
	else if (ABS(dfSemiMajor - 6378388.0) < 0.01 && ABS(dfInvFlattening - 297.0) < 0.0001)
	{
		rgDatum = tcsGD_EuropeanDatum1950;			/* International 1924 */
	}
	else if (ABS(dfSemiMajor - 6377397.155) < 0.01 && ABS(dfInvFlattening - 299.1528128) < 0.0001)
	{
		rgDatum = tcsGD_DeutscheHauptdreiecksnetz;	/* Bessel(DHDN) */
	}
	else if (ABS(dfSemiMajor - 6378137) < 0.01 && ABS(dfInvFlattening - 298.257222101) < 0.000001)
	{
		rgDatum = tcsGD_EuropeanTerrestrialReferenceSystem89;	/* GRS 1980(ETRS89) */
	}
	else if (ABS(dfSemiMajor - 6378137.0) < 0.01 && ABS(dfInvFlattening - 298.257223563) < 0.000001)
	{
		rgDatum = tcsGD_WorldGeodeticSystem1984;
	}

	if (tcsGD_Undefined != rgDatum)
		*prgDatum = rgDatum;
	else {
		_ASSERTE(tcsGD_Undefined != rgDatum);
		*prgDatum = tcsGD_WorldGeodeticSystem1984;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// PrimeMeridian bestimmen
HRESULT CMiTabCSFactory::GetPrimeMeridian (
	OGRSpatialReference *pOgrSrs, TRIASCSPRIMEMERIDIAN *prgPrimeMeridian)
{
	BEGIN_TEST_PARAMS()
		OUT_PARAM(prgPrimeMeridian);
		IN_PARAM(pOgrSrs);
	END_OUT_PARAMS()

	*prgPrimeMeridian = tcsPM_Undefined;

TRIASCSPRIMEMERIDIAN rgPrimeMeridian = tcsPM_Undefined;
LPCSTR pcPrime = pOgrSrs -> GetAttrValue("PRIME");
double dPrime = 0.0;

	if (NULL != pcPrime)
		dPrime = atof(pcPrime);

	if (0.0 == dPrime)
		rgPrimeMeridian = tcsPM_Greenwich;
	else if (-9.0754862 == dPrime)
		rgPrimeMeridian = tcsPM_Lisbon;
	else if (2.5969213 == dPrime)
		rgPrimeMeridian = tcsPM_Paris;
	else if (-74.04513 == dPrime)
		rgPrimeMeridian = tcsPM_Bogota;
	else if (-3.411658 == dPrime)
		rgPrimeMeridian = tcsPM_Madrid;
	else if (12.27084 == dPrime)
		rgPrimeMeridian = tcsPM_Rome;
	else if (7.26225 == dPrime)
		rgPrimeMeridian = tcsPM_Bern;
	else if (106.482779 == dPrime)
		rgPrimeMeridian = tcsPM_Jakarta;
	else if (-17.4 == dPrime)
		rgPrimeMeridian = tcsPM_Ferro;
	else if (4.220471 == dPrime)
		rgPrimeMeridian = tcsPM_Brussels;
	else if (18.03298 == dPrime)
		rgPrimeMeridian = tcsPM_Stockholm;
	else if (23.4258815 == dPrime)
		rgPrimeMeridian = tcsPM_Athens;

	if (tcsPM_Undefined != rgPrimeMeridian)
		*prgPrimeMeridian = rgPrimeMeridian;
	else {
		_ASSERTE(tcsPM_Undefined != rgPrimeMeridian);
		*prgPrimeMeridian = tcsPM_Greenwich;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Transformationsparameter für Datum bestimmen
HRESULT CMiTabCSFactory::GetTranslations (
	OGRSpatialReference *pOgrSrs, double *pdX, double *pdY, double *pdZ)
{
	BEGIN_TEST_PARAMS()
		OUT_PARAM(pdX);
		OUT_PARAM(pdY);
		OUT_PARAM(pdZ);
		IN_PARAM(pOgrSrs);
	END_OUT_PARAMS()

OGR_SRSNode *poTOWGS84 = pOgrSrs -> GetAttrNode("TOWGS84");

	if (NULL != poTOWGS84 && poTOWGS84 -> GetChildCount() > 2) {
		*pdX = atof(poTOWGS84 -> GetChild(0) -> GetValue());
		*pdY = atof(poTOWGS84 -> GetChild(1) -> GetValue());
		*pdZ = atof(poTOWGS84 -> GetChild(2) -> GetValue());
		return S_OK;
	}
	return S_FALSE;		// WGS84 ?
}

///////////////////////////////////////////////////////////////////////////////
// Projektives Koordinatensystem initialisieren
HRESULT CMiTabCSFactory::InitPCS (OGRSpatialReference *pOgrSrs, LPCSTR pcProj, ITRiASCS *pICS)
{
	_ASSERTE(NULL != pcProj);		// muß ein projektives System sein
	COM_TRY {
	// Projektives Koordinatensystem 
	WTRiASCSPCS PCS;

		THROW_FAILED_HRESULT(pICS -> get_ProjectedCS(PCS.ppi()));

	// Projektionsparameter setzen (erstmal nur die, die wir implementiert haben)
		if (NULL == pcProj || EQUAL(pcProj, SRS_PT_EQUIRECTANGULAR)) {
		// zylindrisch äquirectangular
			_ASSERTE(NULL != pcProj || NULL != pOgrSrs -> GetAttrValue("LOCAL_CS"));
			
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(tcsPA_CylindricEquirectangular));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin, pOgrSrs -> GetProjParm (SRS_PP_LATITUDE_OF_ORIGIN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin, pOgrSrs -> GetProjParm (SRS_PP_CENTRAL_MERIDIAN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_CylindricEquirectangular_FalseEasting, pOgrSrs -> GetProjParm (SRS_PP_FALSE_EASTING, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_CylindricEquirectangular_FalseNorthing, pOgrSrs -> GetProjParm (SRS_PP_FALSE_NORTHING, 0.0)));
		} 
		else if (EQUAL(pcProj, SRS_PT_TRANSVERSE_MERCATOR)) {
		// Transverse Mercator
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(tcsPA_TransverseMercator));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin, pOgrSrs -> GetProjParm (SRS_PP_SCALE_FACTOR, 1.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, pOgrSrs -> GetProjParm (SRS_PP_LATITUDE_OF_ORIGIN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, pOgrSrs -> GetProjParm (SRS_PP_CENTRAL_MERIDIAN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_FalseEasting, pOgrSrs -> GetProjParm (SRS_PP_FALSE_EASTING, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_FalseNorthing, pOgrSrs -> GetProjParm (SRS_PP_FALSE_NORTHING, 0.0)));
		} 
		else if (EQUAL(pcProj, SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP))	{
		// Lambert konforme konische Abbildung mit 2 Standardparallelen
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(tcsPA_LambertConicConformal2SP));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_LatitudeOfFirstStandardParallel, pOgrSrs -> GetProjParm (SRS_PP_STANDARD_PARALLEL_1, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_LatitudeOfSecondStandardParallel, pOgrSrs -> GetProjParm (SRS_PP_STANDARD_PARALLEL_2, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_LatitudeOfFalseOrigin, pOgrSrs -> GetProjParm (SRS_PP_LATITUDE_OF_ORIGIN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_LongitudeOfFalseOrigin, pOgrSrs -> GetProjParm (SRS_PP_CENTRAL_MERIDIAN, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_EastingAtFalseOrigin, pOgrSrs -> GetProjParm (SRS_PP_FALSE_EASTING, 0.0)));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_LambertConicConformal2SP_NorthingAtFalseOrigin, pOgrSrs -> GetProjParm (SRS_PP_FALSE_NORTHING, 0.0)));
		}

	// UnitOfLength bestimmen
	TRIASCSUNITOFLENGTH rgUOL = tcsUOL_Undefined;

		THROW_FAILED_HRESULT(GetUnitOfLength (pOgrSrs, &rgUOL));
		THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(rgUOL));

	} COM_CATCH;
	return S_OK;
}

HRESULT CMiTabCSFactory::GetUnitOfLength (OGRSpatialReference *pOgrSrs, TRIASCSUNITOFLENGTH *prgUOL)
{
	BEGIN_TEST_PARAMS()
		OUT_PARAM(prgUOL);
		IN_PARAM(pOgrSrs);
	END_OUT_PARAMS()

	*prgUOL = tcsUOL_Undefined;

char *pszLinearUnits = NULL;
double dfLinearConv = pOgrSrs -> GetLinearUnits(&pszLinearUnits);
TRIASCSUNITOFLENGTH rgUOL = tcsUOL_Undefined;

	if (dfLinearConv == 1.0)
		rgUOL = tcsUOL_Metre;		// "m";
	else if (dfLinearConv == 1000.0)
		rgUOL = tcsUOL_KiloMetre;	// "km";
	else if (dfLinearConv == 0.0254 || EQUAL(pszLinearUnits,"Inch") || EQUAL(pszLinearUnits,"IINCH"))
		rgUOL = tcsUOL_Inch;		// "in"
	else if (dfLinearConv == atof(SRS_UL_FOOT_CONV) || EQUAL(pszLinearUnits, SRS_UL_FOOT))
		rgUOL = tcsUOL_Foot;		// "ft";
	else if (EQUAL(pszLinearUnits,"YARD") || EQUAL(pszLinearUnits, "IYARD") || dfLinearConv == 0.9144)
		rgUOL = tcsUOL_YardSears;
	else if (dfLinearConv == 0.001)
		rgUOL = tcsUOL_MilliMetre;	// "mm";
	else if (dfLinearConv == 0.01)
		rgUOL = tcsUOL_CentiMetre;	// "cm";
	else if (dfLinearConv == atof(SRS_UL_US_FOOT_CONV) || EQUAL(pszLinearUnits, SRS_UL_US_FOOT))
		rgUOL = tcsUOL_ModifiedAmericanFoot;	// "us-ft";
	else if (EQUAL(pszLinearUnits, SRS_UL_NAUTICAL_MILE))
		rgUOL = tcsUOL_NauticalMile;	// "kmi";
	else if (EQUAL(pszLinearUnits, "Mile") || EQUAL(pszLinearUnits, "IMILE"))
		rgUOL = tcsUOL_USSurveyMile;	// "mi"

	if (tcsUOL_Undefined != rgUOL)
		*prgUOL = rgUOL;
	else {
		_ASSERTE(tcsUOL_Undefined != rgUOL);
		*prgUOL = tcsUOL_Metre;
	}
	return S_OK;
}

