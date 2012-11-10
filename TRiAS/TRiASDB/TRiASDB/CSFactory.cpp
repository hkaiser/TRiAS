// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 09/10/1998 03:26:34 PM
//
// @doc
// @module CSFactory.cpp | Workspace-Koordinatensystem, wird aus Projekt gelesen

#include "stdafx.h"

#include <LocaleHelpers.h>
#include <Com/PropertyHelper.h>

#include "GlobalVars.h"
#include "Strings.h"
#include "Wrapper.h"

#include "CSFactory.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSPCS);
DefineSmartInterface(TRiASCSDatumTransformation);

namespace {
	inline
	bool IsDHDNDerived(TRIASCSGEODETICDATUM rgDatum)
	{
		switch (rgDatum) {
		case tcsGD_DeutscheHauptdreiecksnetz:
		case tcsGD_DeutscheHauptdreiecksnetzAblN:
		case tcsGD_DeutscheHauptdreiecksnetzAblM:
		case tcsGD_DeutscheHauptdreiecksnetzAblS:
		case tcsGD_DeutscheHauptdreiecksnetzRd83:
		case tcsGD_DeutscheHauptdreiecksnetzPd83:
		case tcsGD_DeutscheHauptdreiecksnetzRd83DHDN:
		case tcsGD_DeutscheHauptdreiecksnetzDHDN:
		case tcsGD_DeutscheHauptdreiecksnetzAblN2:
		case tcsGD_DeutscheHauptdreiecksnetzAblS2:
			return true;

		default:
			break;
		}
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen des Koordinatensystemes für das übergebene Projekt
HRESULT CCSFactory::RetrieveCS (ITRiASPropertyBase *pIPropBase, ITRiASCS **ppICS)
{
	if (NULL == ppICS) return E_POINTER;
	COM_TRY {
	// Koordinatensystem erzeugen
	WTRiASCS CS (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(ReInitCS (pIPropBase, CS));

	// Resultat liefern
		*ppICS = CS.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen des Koordinatensystemes für das übergebene Projekt
HRESULT CCSFactory::ReInitCS (ITRiASPropertyBase *pIPropBase, ITRiASCS *pICS)
{
	if (NULL == pICS) 
		return E_POINTER;

	COM_TRY {
	// alles wird aus den Properties des Projektes gelesen
		if (!m_Props)
		{
			THROW_FAILED_HRESULT(pIPropBase -> get_Properties(m_Props.ppi()));
		}

	CComBSTR bstrTcfName (GetProperty(m_Props, CComBSTR(g_cbCoordTcfName), g_bstrNil));

		if (0 == bstrTcfName.Length() || FAILED(pICS->LoadFromFile(bstrTcfName))) {
		// initiale Variablen aus Koordinatensystemtyp bestimmen
			THROW_FAILED_HRESULT(InitDataFromProject());

		// Typ des CoordSystems setzen
			THROW_FAILED_HRESULT(pICS -> put_CoordSystemType(GetType()));

		// Geodätische Grundlage initialisieren
			{
			WTRiASCSGCS GCS;

				THROW_FAILED_HRESULT(pICS -> get_GeographicCS(GCS.ppi()));
				THROW_FAILED_HRESULT(GCS -> put_GeodeticDatum(GetGeodDatum()));
				THROW_FAILED_HRESULT(GCS -> put_PrimeMeridian(GetPrimeMeridian()));
				THROW_FAILED_HRESULT(GCS -> put_UnitOfAngle(GetUnitOfAngle()));
			}

		// Datumsparameter einstellen
			{
			WTRiASCSDatumTransformation DTrans;

				THROW_FAILED_HRESULT(pICS -> get_DatumTransformation(DTrans.ppi()));
				THROW_FAILED_HRESULT(DTrans -> put_GeodeticDatum(GetGeodDatum()));
				THROW_FAILED_HRESULT(DTrans -> put_TransformationAlgorithm(tcsDTA_PositionVector7ParamTransformation));
			}

		// projektives Koordinatensystem beachten
			if (IsProjected()) {
			WTRiASCSPCS PCS;

				THROW_FAILED_HRESULT(pICS -> get_ProjectedCS (PCS.ppi()));
			
			// Projektionsparameter festlegen
				THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(GetProjectionAlgorithm()));
				THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, GetScaleFactor()));

			double dLongitude = GetLongitude();

				if (0 != dLongitude) {
					_ASSERTE(tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin == tcsPP_GaussKrueger_LatitudeOfNaturalOrigin);
					_ASSERTE(tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin == tcsPP_GaussKrueger_LongitudeOfNaturalOrigin);
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, GetLatitude()));
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, dLongitude));

					_ASSERTE(tcsPP_CylindricEquirectangular_FalseEasting == tcsPP_GaussKrueger_FalseEasting);
					_ASSERTE(tcsPP_CylindricEquirectangular_FalseNorthing == tcsPP_GaussKrueger_FalseNorthing);
					_ASSERTE(tcsPP_CylindricEquirectangular_FalseEasting == tcsPP_CassiniSoldner_FalseEasting);
					_ASSERTE(tcsPP_CylindricEquirectangular_FalseNorthing == tcsPP_CassiniSoldner_FalseNorthing);
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_FalseEasting, GetFalseX()));
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing, GetFalseY()));
				}
				else {
				// AutoMode Projektion
					_ASSERTE(tcsPA_GaussKrueger == GetProjectionAlgorithm());

					_ASSERTE(tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin == tcsPP_GaussKrueger_LatitudeOfNaturalOrigin);
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, GetLatitude()));
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_ZoneWidth, GetZoneWidth()));

					_ASSERTE(tcsPP_CylindricEquirectangular_FalseNorthing == tcsPP_GaussKrueger_FalseNorthing);
					_ASSERTE(tcsPP_CylindricEquirectangular_FalseNorthing == tcsPP_CassiniSoldner_FalseNorthing);
					THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing, GetFalseY()));
				}

				THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(GetUnitOfLength()));
			}
		}
			
	// CS ist jetzt gültig
		THROW_FAILED_HRESULT(pICS -> Recompute());

	} COM_CATCH;
	return S_OK;
}

double CCSFactory::RetrieveLongitude()
{
	_ASSERTE(m_rgType == tcsCS_Projected);
	_ASSERTE(m_rgDatum != tcsCS_Undefined);
	_ASSERTE(m_Props.IsValid());

CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordMeridian), g_bstrNil));

	if (bstrValue.Length() > 0) {
		USES_CONVERSION;

	CSetLocale locale("C");
	double lT = atof(OLE2A(bstrValue));

		if (0 != lT)
			return lT * 3600;

	CComBSTR bstrShowGK (GetProperty (m_Props, CComBSTR(g_cbCoordAutoMeridian), g_bstrNil));
	
		if (bstrShowGK.Length() > 0 && 0 != atol(OLE2A(bstrShowGK))) {
		CComBSTR bstrZoneWidth (GetProperty (m_Props, CComBSTR(g_cbCoordStrBreite), g_bstrNil));

			if (bstrZoneWidth.Length() > 0) {
				m_dZoneWidth = atof (OLE2A(bstrZoneWidth));
				return 0;	// kein Mittelmeridian
			}
		}
		_ASSERTE(0 != lT);
	}

// wenn nicht gegeben, Standard annehmen
	return IsDHDNDerived(m_rgDatum) ? 12.0 * 3600 : 15.0 * 3600;		// sekunden
}

double CCSFactory::RetrieveLatitude()
{
	_ASSERTE(m_rgType == tcsCS_Projected);
	_ASSERTE(m_rgDatum != tcsCS_Undefined);
	_ASSERTE(m_Props.IsValid());

CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordLatitude), g_bstrNil));

	if (bstrValue.Length() > 0) {
		USES_CONVERSION;

	CSetLocale locale("C");
	double lT = atof(OLE2A(bstrValue));

		if (0 != lT)
			return lT * 3600;
		_ASSERTE(0 != lT);
	}
	return 0.0;	// wenn nicht gegeben, Standard annehmen
}

double CCSFactory::RetrieveFalseX (void)
{
	_ASSERTE(m_rgType == tcsCS_Projected);
	_ASSERTE(m_Props.IsValid());

	if (m_fIsUserDefined || IsCassiniSoldner()) {
	// Rechtwinklige zylindrische Projektion oder Soldner
	CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordFalseX), g_bstrNil));

		if (bstrValue.Length() > 0) {
			USES_CONVERSION;

		CSetLocale locale("C");
		double lT = atof(OLE2A(bstrValue));

			if (0 != lT)
				return - lT;
			_ASSERTE(0 != lT);
		}
// ...durchfallen lassen, damit Mittelmeridian und FalseX übereinstimmen
//		return 0.0;		// kein Offset
		
	} else if (IsTransverseMercator()) {
	// Gauß-Krüger Projektion
		if (0 == m_dMeridian && 0 != m_dZoneWidth)
			return 0.0;			// kein FalseEasting, da AutoMode

		_ASSERTE(0.0 != m_dMeridian);

	CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordStrBreite), g_bstrNil));

		if (bstrValue.Length() > 0) {
		CSetLocale locale("C");
		long lStr = _wtol(bstrValue);
		long lZone = 0;

			_ASSERTE(3 == lStr || 6 == lStr);
			if (3 == lStr) {
			CComBSTR bstrTcfName (GetProperty (m_Props, CComBSTR(g_cbCoordTcfName), g_bstrNil));

				if (bstrTcfName == L"BesD") {
				// BesD hat seine eigene Streifen-Nummerierung
					_ASSERTE(37800.0 == m_dMeridian);
					return 1500000.0;
				}
				else {
					lZone = (long)((m_dMeridian / 3600) / 3.0 + 0.5);		// #AK981020
					return lZone * 1000000.0 + 500000.0;
				}
			} else if (6 == lStr) {
				lZone = (long)(((m_dMeridian / 3600) + 3.0) / 6.0 + 0.5);	// #AK981020
				return lZone * 1000000.0 + 500000.0;
			}
		}
	}

// wenn nicht gegeben, Standard annehmen
	return IsDHDNDerived(m_rgDatum) ? 4500000.0 : 3500000.0;
}

double CCSFactory::RetrieveFalseY (void)
{
	_ASSERTE(m_rgType == tcsCS_Projected);
	_ASSERTE(m_Props.IsValid());

	if (m_fIsUserDefined || IsCassiniSoldner()) {
	// Rechtwinklige zylindrische Projektion oder Soldner
	CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordFalseY), g_bstrNil));

		if (bstrValue.Length() > 0) {
			USES_CONVERSION;

		CSetLocale locale("C");
		double lT = atof(OLE2A(bstrValue));

			if (0 != lT)
				return - lT;
			_ASSERTE(0 != lT);
		}
		return 0.0;		// kein Offset
		
	} else {
	// Gauß-Krüger Projektion
		return 0.0;		// kein Offset im Hochwert
	}
}

double CCSFactory::RetrieveScaleAtNaturalOrigin (double dScaleDefault)
{
	_ASSERTE(m_rgType == tcsCS_Projected);
	_ASSERTE(m_Props.IsValid());

	if (m_fIsUserDefined) {
	// Rechtwinklige zylindrische Projektion
	CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordScaleAtOrig), g_bstrNil));

		if (bstrValue.Length() > 0) {
		CSetLocale locale("C");

			USES_CONVERSION;
			return atof (OLE2A(bstrValue));
		}
		return dScaleDefault;		// kein besonderer StauchungsFaktor
		
	} 
	else {
	// Gauß-Krüger/UTM Projektion
		return dScaleDefault;		// kein besonderer StauchungsFaktor
	}
}

TRIASCSGEODETICDATUM CCSFactory::RetrieveDHDNDatum()
{
long lDHDNType = GetProperty (m_Props, CComBSTR(g_cbCoordDHDNType), 
	long(tcsGD_DeutscheHauptdreiecksnetz));		// Standard ist 40/83

	switch (lDHDNType) {
	case tcsGD_DeutscheHauptdreiecksnetzAblN:
	case tcsGD_DeutscheHauptdreiecksnetzAblM:
	case tcsGD_DeutscheHauptdreiecksnetzAblS:
	case tcsGD_DeutscheHauptdreiecksnetzRd83:
	case tcsGD_DeutscheHauptdreiecksnetzPd83:
	case tcsGD_DeutscheHauptdreiecksnetzRd83DHDN:
	case tcsGD_DeutscheHauptdreiecksnetzAblN2:
	case tcsGD_DeutscheHauptdreiecksnetzAblS2:
	case tcsGD_DeutscheHauptdreiecksnetzDHDN:
	case tcsGD_DeutscheHauptdreiecksnetzBesD:
	case tcsGD_DeutscheHauptdreiecksnetz:
		return TRIASCSGEODETICDATUM(lDHDNType);

	default:
		break;
	}
	return tcsGD_DeutscheHauptdreiecksnetzRd83DHDN;
}

HRESULT CCSFactory::InitDataFromProject (void)
{
	_ASSERTE(m_Props.IsValid());

	COM_TRY {
	CComBSTR bstrValue (GetProperty (m_Props, CComBSTR(g_cbCoordTransform), g_bstrNil));

		m_fIsUserDefined = false;
		if (bstrValue == g_cbBESSELGK) {
			m_fIsTransverseMercator = true;
			m_rgType = tcsCS_Projected;
			m_rgProj = tcsPA_GaussKrueger;
			m_rgDatum = RetrieveDHDNDatum();
			m_dMeridian = RetrieveLongitude();
			m_dFalseX = RetrieveFalseX();
			m_dFalseY = RetrieveFalseY();				// #AK981020
			m_dScale = RetrieveScaleAtNaturalOrigin();

		} else if (bstrValue == g_cbKRASSGK) {
			m_fIsTransverseMercator = true;
			m_rgType = tcsCS_Projected;
			m_rgProj = tcsPA_GaussKrueger;
			m_rgDatum = tcsGD_Pulkovo1942;
			m_dMeridian = RetrieveLongitude();
			m_dFalseX = RetrieveFalseX();
			m_dFalseY = RetrieveFalseY();				// #AK981020
			m_dScale = RetrieveScaleAtNaturalOrigin();

		} else if (bstrValue == g_cbETRSGK) {
			m_fIsTransverseMercator = true;
			m_rgType = tcsCS_Projected;
			m_rgProj = tcsPA_GaussKrueger;
			m_rgDatum = tcsGD_WorldGeodeticSystem1984;
			m_dMeridian = RetrieveLongitude();
			m_dFalseX = RetrieveFalseX();
			m_dFalseY = RetrieveFalseY();				// #AK981020
			m_dScale = RetrieveScaleAtNaturalOrigin(0.9996);

		} else if (bstrValue == g_cbBEGEOD) {
			m_rgType = tcsCS_Geographic;
			m_rgDatum = RetrieveDHDNDatum();

		} else if (bstrValue == g_cbKRGEOD) {
			m_rgType = tcsCS_Geographic;
			m_rgDatum = tcsGD_Pulkovo1942;

		} else if (bstrValue == g_cbETRSGEOD) {
			m_rgType = tcsCS_Geographic;
			m_rgDatum = tcsGD_WorldGeodeticSystem1984;

		} else if (bstrValue == g_cbCassiniSoldner) {
			m_fIsCassiniSoldner = true;
			m_rgType = tcsCS_Projected;
			m_rgProj = tcsPA_CassiniSoldner;
			m_rgDatum = RetrieveDHDNDatum();
			m_dMeridian = RetrieveLongitude();
			m_dBreite = RetrieveLatitude();
			m_dFalseX = RetrieveFalseX();
			m_dFalseY = RetrieveFalseY();				// #AK981020
			m_dScale = 1.0;

		} else {
			m_fIsUserDefined = true;
			m_rgType = tcsCS_Projected;
			m_rgProj = tcsPA_CylindricEquirectangular;
			m_rgDatum = RetrieveDHDNDatum();
			m_dFalseX = RetrieveFalseX();
			m_dFalseY = RetrieveFalseY();
			m_dMeridian = RetrieveLongitude();
			m_dBreite = RetrieveLatitude();
			m_dScale = RetrieveScaleAtNaturalOrigin();
		}

	} COM_CATCH;
	return S_OK;
}

