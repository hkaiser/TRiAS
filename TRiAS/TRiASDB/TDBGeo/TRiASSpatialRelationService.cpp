// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.01.2002 13:12:05 
//
// @doc
// @module TRiASSpatialRelationService.cpp | Definition of the <c CTRiASSpatialRelationService> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include "TDBGeoImpl.h"

#include "TRiASCSStorageService.h"
#include "TRiASSpatialRelationService.h"

#include "GeometryObjects.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASSpatialRelationService

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CTRiASSpatialRelationService::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASSpatialRelationService ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung et.al.
HRESULT CTRiASSpatialRelationService::FinalConstruct()
{
	COM_TRY {
	// Ausgabekoordinatensystem anlegen und initialisieren (WGS84, UTM 9/6, Meter)
	WTRiASCS CSOut (CLSID_TRIASCS);

		THROW_FAILED_HRESULT(CSOut -> put_CoordSystemType(tcsCS_Projected));

	// Geodätische Grundlage initialisieren
		{
		WTRiASCSGCS GCS;

			THROW_FAILED_HRESULT(CSOut -> get_GeographicCS(GCS.ppi()));
			THROW_FAILED_HRESULT(GCS -> put_GeodeticDatum(tcsGD_WorldGeodeticSystem1984));
			THROW_FAILED_HRESULT(GCS -> put_PrimeMeridian(tcsPM_Greenwich));
			THROW_FAILED_HRESULT(GCS -> put_UnitOfAngle(tcsUOA_Second));
		}

	// Datumsparameter einstellen
		{
		WTRiASCSDatumTransformation DTrans;

			THROW_FAILED_HRESULT(CSOut -> get_DatumTransformation(DTrans.ppi()));
			THROW_FAILED_HRESULT(DTrans -> put_GeodeticDatum(tcsGD_WorldGeodeticSystem1984));
			THROW_FAILED_HRESULT(DTrans -> put_TransformationAlgorithm(tcsDTA_PositionVector7ParamTransformation));
		}
	
	// projektives Koordinatensystem beachten
		{
		WTRiASCSPCS PCS;

			THROW_FAILED_HRESULT(CSOut -> get_ProjectedCS (PCS.ppi()));
		
		// Projektionsparameter festlegen
			THROW_FAILED_HRESULT(PCS -> put_ProjectionAlgorithm(tcsPA_TransverseMercator));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin, 0.9996));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, 0.0));		// Höhe
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, 9*3600.0));

			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_FalseEasting, 0.0));
			THROW_FAILED_HRESULT(PCS -> put_ProjectionParameter(tcsPP_TransverseMercator_FalseNorthing, 3500000.0));
			THROW_FAILED_HRESULT(PCS -> put_UnitOfLength(tcsUOL_Metre));
		}

	// CS ist jetzt gültig
	CComBSTR bstrCat, bstrDesc;

		ERROR_EXPR_FALSE(bstrCat.LoadString(IDS_DEFAULT_CS_CATEGORY), E_UNEXPECTED);
		ERROR_EXPR_FALSE(bstrDesc.LoadString(IDS_DEFAULT_CS_DESCRIPTION), E_UNEXPECTED);
		THROW_FAILED_HRESULT(CSOut -> put_Category(bstrCat));
		THROW_FAILED_HRESULT(CSOut -> put_Description(bstrCat));

		THROW_FAILED_HRESULT(CSOut -> put_CoordSystemType(tcsCS_Geographic));
		THROW_FAILED_HRESULT(CSOut -> Recompute());

	// TransformPipe initialisieren
	WTRiASCSTransform CSS(CLSID_TRiASCSTransform);

		THROW_FAILED_HRESULT(CSS -> putref_OutputCS(CSOut));
		m_CSS = CSS;
		
	} COM_CATCH;
	return S_OK;
}

void CTRiASSpatialRelationService::FinalRelease()
{
	COM_TRY {
	// Koordinatensystem freigeben
		if (m_CSS.IsValid())
		{
			THROW_FAILED_HRESULT(m_CSS -> ShutDown());
			m_CSS.Assign(NULL);
		}
	} COM_CATCH_NORETURN;
}

///////////////////////////////////////////////////////////////////////////////
// Guid eines übergebenen Koordinatensystemes bestimmen
inline void __InitPointer (CIID *p) { *p = GUID_NULL; }		// specializing template for CHECKOUTPOINTER()

HRESULT CTRiASSpatialRelationService::RetrieveCSGuid(VARIANT vCSArg, CIID *pGuid)
{
	CHECKOUTPOINTER(pGuid);
	COM_TRY {
	CComVariant vCS;
	CIID Guid;

		if (SUCCEEDED(vCS.ChangeType(VT_DISPATCH, &vCSArg))) {
		// Koordinatensystem ist direkt gegeben
		WTRiASCS CS (V_DISPATCH(&vCS));
		CComBSTR bstrGuid;
		CComVariant v;

			THROW_FAILED_HRESULT(CS -> get_GUID(&bstrGuid));
			if (FAILED(m_CSS -> get_Item (CComVariant(bstrGuid), &v))) {
			// Koordinatensystem als Eingangssystem zum Transformationsobjekt hinzufügen
				THROW_FAILED_HRESULT(m_CSS -> AddInputCS(CS));
				THROW_FAILED_HRESULT(CS -> Recompute());			// Transformationsobjekt neu berechnen
			}
			Guid = CIID(bstrGuid);
		}
		else {
			THROW_FAILED_HRESULT(vCS.ChangeType(VT_BSTR, &vCSArg));	// muß jetzt als BSTR da sein
			Guid = CIID(V_BSTR(&vCS));
		}

	// Guid liefern 
		ERROR_EXPR_TRUE(!Guid, E_INVALIDARG);			// muß ein Guid sein
		*pGuid = Guid;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASSpatialRelationService

// Implementation of Equals
STDMETHODIMP CTRiASSpatialRelationService::Equals(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *equals)
{
	if (NULL == equals)
		return E_POINTER;
	*equals = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*equals = (rgPosition == EQUAL) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Touches
STDMETHODIMP CTRiASSpatialRelationService::Touches(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *touches)
{
	if (NULL == touches)
		return E_POINTER;
	*touches = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*touches = (rgPosition == TOUCH) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Contains
STDMETHODIMP CTRiASSpatialRelationService::Contains(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *contains)
{
	if (NULL == contains)
		return E_POINTER;
	*contains = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*contains = (rgPosition == CONTAIN) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Within
STDMETHODIMP CTRiASSpatialRelationService::Within(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *within)
{
	if (NULL == within)
		return E_POINTER;
	*within = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*within = (rgPosition == WITHIN) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Disjoint
STDMETHODIMP CTRiASSpatialRelationService::Disjoint(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *disjoint)
{
	if (NULL == disjoint)
		return E_POINTER;
	*disjoint = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*disjoint = (rgPosition == DISJOINT) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Crosses
STDMETHODIMP CTRiASSpatialRelationService::Crosses(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *crosses)
{
	if (NULL == crosses)
		return E_POINTER;
	*crosses = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*crosses = (rgPosition == ENTER) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Overlaps
STDMETHODIMP CTRiASSpatialRelationService::Overlaps(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *overlaps)
{
	if (NULL == overlaps)
		return E_POINTER;
	*overlaps = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*overlaps = (rgPosition == OVERLAP) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Intersects
STDMETHODIMP CTRiASSpatialRelationService::Intersects(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	VARIANT_BOOL *intersects)
{
	if (NULL == intersects)
		return E_POINTER;
	*intersects = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*intersects = (rgPosition == INTERSECT) ? VARIANT_TRUE : VARIANT_FALSE;

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of Relate
STDMETHODIMP CTRiASSpatialRelationService::Relate(VARIANT CS1, 
	IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, SPATIALRELATION rgPattern, 
	VARIANT_BOOL *isrelated)
{
	if (NULL == isrelated)
		return E_POINTER;
	*isrelated = VARIANT_FALSE;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		switch (rgPosition) {
		case WITHIN:
			*isrelated = (rgPattern & SPATIALRELATION_Within) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case CONTAIN:
			*isrelated = (rgPattern & SPATIALRELATION_Contains) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case OVERLAP:
			*isrelated = (rgPattern & SPATIALRELATION_Overlaps) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case ENTER:
			*isrelated = (rgPattern & SPATIALRELATION_Crosses) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case TOUCH:
			*isrelated = (rgPattern & SPATIALRELATION_Touches) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case EQUAL:
			*isrelated = (rgPattern & SPATIALRELATION_Equals) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case DISJOINT:
			*isrelated = (rgPattern & SPATIALRELATION_Disjoint) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case INTERSECT:
			*isrelated = (rgPattern & SPATIALRELATION_Intersects) ? 
				VARIANT_TRUE : VARIANT_FALSE;
			break;

		case UNCLEAR:
			break;
		}

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

SPATIALRELATION OGCToSpatialRelation(OGCWMPosit rgPosition)
{
	switch (rgPosition) {
	case WITHIN:
		return SPATIALRELATION_Within;

	case CONTAIN:
		return SPATIALRELATION_Contains;

	case OVERLAP:
		return SPATIALRELATION_Overlaps;

	case ENTER:
		return SPATIALRELATION_Crosses;

	case TOUCH:
		return SPATIALRELATION_Touches;

	case EQUAL:
		return SPATIALRELATION_Equals;

	case DISJOINT:
		return SPATIALRELATION_Disjoint;

	case INTERSECT:
		return SPATIALRELATION_Intersects;

	case UNCLEAR:
		break;
	}
	return SPATIALRELATION_Unknown;
}

// Implementation of GetSpatialRelation
STDMETHODIMP CTRiASSpatialRelationService::GetSpatialRelation(
	VARIANT CS1, IDispatch *GeomOne, VARIANT CS2, IDispatch *GeomTwo, 
	SPATIALRELATION *prgPattern)
{
	if (NULL == prgPattern)
		return E_POINTER;
	*prgPattern = SPATIALRELATION_Unknown;

WMObjekt<KoOrdT> *pObj1 = NULL;
WMObjekt<KoOrdT> *pObj2 = NULL;

	COM_TRY {
	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// Geometrien ins ZielCS konvertieren
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomOne)->Transform(*(CSID *)&Guid1, m_CSS));
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(GeomTwo)->Transform(*(CSID *)&Guid2, m_CSS));

	// Geometrie aus COM-Objekt in WMObjekt<> auspacken
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomOne, &pObj1));
		THROW_FAILED_HRESULT(ConvertToGeometry(GeomTwo, &pObj2));

	OGCWMPosit rgPosition = UNCLEAR;

		THROW_FAILED_HRESULT(CalcTopRelation(pObj1, pObj2, &rgPosition));
		*prgPattern = OGCToSpatialRelation(rgPosition);

	} COM_CATCH_OP((
		delete pObj1,
		delete pObj2
	));

	delete pObj1;
	delete pObj2;
	return S_OK;
}

// Implementation of putref_TransformPipe
STDMETHODIMP CTRiASSpatialRelationService::putref_TransformPipe(ITRiASCSTransform *newVal)
{
// altes System freigeben
	if (m_CSS.IsValid()) {
		RETURN_FAILED_HRESULT(m_CSS->ShutDown());
		m_CSS.Assign(NULL);
	}

	ATLTRY(m_CSS = newVal);
	ERROR_EXPR_FALSE(NULL == newVal || m_CSS.IsValid(), E_INVALIDARG);
	return S_OK;
}

// Implementation of get_TransformPipe
STDMETHODIMP CTRiASSpatialRelationService::get_TransformPipe(ITRiASCSTransform **pVal)
{
	CHECKOUTPOINTER(pVal);
	(*pVal = m_CSS) -> AddRef();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion zur Bestimmung der OGC toprel
OGCWMPosit TRiAStoOGCRelations (WMObjTyp rgOT1, WMObjTyp rgOT2, WMPosit posLage)
{
	if (AUSSERH == posLage)	
		return DISJOINT;

	if (AUSSERHB == posLage || KONTUR == posLage)
		return TOUCH;

	if (UMSCHL == posLage || UMSCHLB == posLage)
		return CONTAIN;

	if (INNERH == posLage)
		return WITHIN;

	if (GLEICH == posLage)
		return EQUAL;

	switch (rgOT1) {
	case OT_PUNKT:		// Bezugsobjekt ist Punkt
		switch (rgOT2) {
		case OT_PUNKT:
			_ASSERTE(AUSSERH == posLage || GLEICH == posLage);
			break;

		case OT_KANTE:
			_ASSERTE(AUSSERH == posLage || AUSSERHB == posLage || UMSCHLB == posLage);
			break;

		case OT_FLAECHE:
			_ASSERTE(AUSSERH == posLage || AUSSERHB == posLage || UMSCHL == posLage);
			break;
		}
		break;

		
	case OT_KANTE:		// Bezugsobjekt ist Kante
		switch (rgOT2) {
		case OT_PUNKT:
			_ASSERTE(AUSSERH == posLage || GLEICH == posLage);
			break;
	
		case OT_KANTE:
		// dieser Programmzweig dürfte gar nicht erreicht werden, da bei der
		// Kombination Kante/Kante direkt mit LinesLocation() die OGC-Relation
		// ermittelt wird 
			_ASSERTE(false);
			break;

		case OT_FLAECHE:
			if (INNAUSS == posLage)
				return ENTER;

			_ASSERTE(INNAUSS == posLage);
			break;
		}
		break;
		

	case OT_FLAECHE:	// Bezugsobjekt ist Fläche
		switch (rgOT2) {
		case OT_PUNKT:
			_ASSERTE(AUSSERH == posLage || GLEICH == posLage);
			break;
	
		case OT_KANTE:
			if (INNERHB == posLage)
				return WITHIN;
			else if (INNAUSS == posLage)
				return ENTER;

			_ASSERTE(INNERHB == posLage || INNAUSS == posLage);
			break;

		case OT_FLAECHE:
			if (INNERHB == posLage)
				return WITHIN;
			else if (INNAUSS == posLage)
				return OVERLAP;

			_ASSERTE(INNAUSS == posLage || INNERHB == posLage);
			break;
		}
		break;

	default:
		_ASSERTE(false);
		break;
	}
	return UNCLEAR;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion ermittelt topologische relation zwischen zwei gegebenen 
// Objekten
HRESULT CTRiASSpatialRelationService::CalcTopRelation(
	WMObjekt<KoOrdT> *pObj2, WMObjekt<KoOrdT> *pObj1, OGCWMPosit *prgPosition)
{
	_ASSERTE(NULL != *prgPosition);
	_ASSERTE(NULL != pObj1 && NULL != pObj2);

	*prgPosition = UNCLEAR;

WMPosit posLage = UNKLAR;
WMObjTyp iOTAkt = pObj1->isA();	// Objekttyp des Bezugsobjektes
WMObjTyp iOT = pObj2->isA();	// Objekttyp des zu testenden Objektes

	switch (iOTAkt) {
	case OT_PUNKT:			// Bezugsobjekt ist Punkt
		switch (iOT) {
		case OT_PUNKT:
			if (*(WMPunkt<KoOrdT> *)pObj1 == *(WMPunkt<KoOrdT> *)pObj2)
				posLage = GLEICH;
			else 
				posLage = AUSSERH;
			TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;
	
		case OT_KANTE:
		// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: 
		// Wie liegt die pEO-Kante bezüglich des _pAO-Punktes? Dafür habe ich 
		// aber keine Routine.
			posLage = ((WMPunkt<KoOrdT> *)pObj1)->PunktAufKante ((WMKante<KoOrdT> *)pObj2);
			if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
				posLage = UMSCHLB;	// Ergebnis von PunktAufKante() modifiziert werden
			else if (KONTUR == posLage)
				posLage = AUSSERHB;

			*prgPosition = TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;

		case OT_FLAECHE:
		// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: 
		// Wie liegt die pEO-Fläche bez. des _pAO-Punktes? Dafür habe ich aber 
		// keine Routine.

		// eine Fläche kann nicht innerhalb eines Punktes liegen
			posLage = pObj1->EnthaltenIn ((WMFlaeche<KoOrdT> *)pObj2);
			if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
				posLage = UMSCHL;	// Ergebnis von EnthaltenIn() modifiziert werden (12.04.99)
			else if (KONTUR == posLage)		// 12.04.99
				posLage = AUSSERHB;

			*prgPosition = TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;

		default:
			_ASSERTE(false);
			break;
		}
		break;
		

	case OT_KANTE:			// Bezugsobjekt ist Kante
		switch (iOT) {
		case OT_PUNKT:
			posLage = ((WMPunkt<KoOrdT> *)pObj2)->PunktAufKante ((WMKante<KoOrdT> *)pObj1);
			*prgPosition = TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;
	
		case OT_KANTE:
			*prgPosition = ((WMKante<KoOrdT> *)pObj2)->LinesLocation ((WMKante<KoOrdT> *)pObj1);
			break;

		case OT_FLAECHE:
		// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: 
		// Wie liegt die pEO-Fläche bez. der _pAO-Kante? Dafür habe ich aber 
		// keine Routine.
			posLage = pObj1->EnthaltenIn ((WMFlaeche<KoOrdT> *)pObj2);
			if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
				posLage = UMSCHL;	// Ergebnis von EnthaltenIn() modifiziert werden
			else if (INNERHB == posLage)
				posLage = UMSCHLB;
			else if (KONTUR == posLage)
				posLage = AUSSERHB;
			else if (UMSCHL == posLage)
				posLage = AUSSERH;
			else if (UMSCHLB == posLage)
				posLage = AUSSERHB;

			*prgPosition = TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;

		default:
			_ASSERTE(false);
			break;
		}
		break;
		

	case OT_FLAECHE:	// Bezugsobjekt ist Fläche
		switch (iOT) {
		case OT_PUNKT:
		case OT_KANTE:
		case OT_FLAECHE:
			posLage = pObj2->EnthaltenIn ((WMFlaeche<KoOrdT> *)pObj1);
			*prgPosition = TRiAStoOGCRelations (iOTAkt, iOT, posLage);
			break;

		default:
			_ASSERTE(false);
			break;
		}
		break;

	default:
		_ASSERTE(false);
		break;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren einer IDispatch-Geometrie in ein intern verwendetes entsprechendes
// Objekt
HRESULT CTRiASSpatialRelationService::ConvertToGeometry (
	IDispatch *pIGeometry, WMObjekt<KoOrdT> **ppGeometry)
{
GEOMETRYTYPE rgType = GEOMETRYTYPE_Unknown;

	RETURN_FAILED_HRESULT(CTRiASCSStorageService::RetrieveGeometryType(pIGeometry, &rgType));
	switch (rgType) {
	case GEOMETRYTYPE_Point:
		return ConvertToPoint (pIGeometry, ppGeometry);

	case GEOMETRYTYPE_Line:
		return ConvertToLine (pIGeometry, ppGeometry);

	case GEOMETRYTYPE_Boundary:
	case GEOMETRYTYPE_Area:
		return ConvertToArea (pIGeometry, ppGeometry);

	default:
		break;
	}
	return TGEO_E_UNKNOWN_OBJECTTYPE;
}

HRESULT CTRiASSpatialRelationService::ConvertToPoint (IDispatch *pIGeometry,
	WMObjekt<KoOrdT> **ppGeometry)
{
	if (NULL == ppGeometry)
		return E_POINTER;
	*ppGeometry = NULL;

	COM_TRY {
	WTRiASSimplePoint Point (pIGeometry);
	double dX[3] = { 0.0, 0.0, 0.0 };

		THROW_FAILED_HRESULT(Point -> GetPoint(dX));

	WMPunkt<KoOrdT> *pPt = new WMPunkt<KoOrdT>(dX[0], dX[1]);

		*ppGeometry = pPt;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASSpatialRelationService::ConvertToLine (IDispatch *pIGeometry,
	WMObjekt<KoOrdT> **ppGeometry)
{
	if (NULL == ppGeometry)
		return E_POINTER;
	*ppGeometry = NULL;

KoOrdT *pCoords = NULL;

	COM_TRY {
	W_DGMPolylineGeometry Line (pIGeometry);
	W_DGMPoints pts;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Line -> get_Points(pts.ppi()));
		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));

		pCoords = new KoOrdT[3*lCnt];
		THROW_FAILED_HRESULT(WTRiASSimplePoints(pts) -> GetPoints(1, lCnt, pCoords));

		*ppGeometry = new WMKante<KoOrdT>(pCoords, lCnt);

	} COM_CATCH_OP(delete pCoords);
	delete pCoords;
	return S_OK;
}

namespace {
	long KantenAnz (IDispatch *pIGeometry) 
	{
	long lCnt = 0;

		COM_TRY {
		W_DGMBoundaryGeometry geom;

			if (SUCCEEDED(pIGeometry->QueryInterface(geom.ppi()))) {
			W_DGMGeometryCollection coll;

				THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));
				THROW_FAILED_HRESULT(coll -> get_Count(&lCnt));
				lCnt++;			// Außenkontur hinzufügen

			} else {
				lCnt = 1;		// nur Außenkontur
			}
		} COM_CATCH_RETURN(lCnt);
		return lCnt;
	}

	template <typename KoOrdT>
	HRESULT GetArea (_DGMPolylineGeometry *pILine, WMFlaeche<KoOrdT> **ppGeometry)
	{
		_ASSERTE(NULL != ppGeometry);

	KoOrdT *pCoords = NULL;

		*ppGeometry = NULL;
		COM_TRY {
		W_DGMPoints pts;
		long lCnt = 0;

			THROW_FAILED_HRESULT(pILine -> get_Points(pts.ppi()));
			THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));

			pCoords = new KoOrdT[3*lCnt];
			THROW_FAILED_HRESULT(WTRiASSimplePoints(pts) -> GetPoints(1, lCnt, pCoords));

		WMKante<KoOrdT> Kante(pCoords, lCnt);

			*ppGeometry = new WMFlaeche<KoOrdT>(&Kante, 1);

		} COM_CATCH_OP(delete pCoords);

		delete pCoords;
		return S_OK;
	}
}

HRESULT CTRiASSpatialRelationService::ConvertToArea (IDispatch *pIGeometry,
	WMObjekt<KoOrdT> **ppGeometry)
{
	if (NULL == ppGeometry)
		return E_POINTER;
	*ppGeometry = NULL;

WMFlaeche<KoOrdT> *pArea = NULL;

	COM_TRY {
	WTRiASSimpleRectangle Rect;

		if (SUCCEEDED(pIGeometry->QueryInterface(Rect.ppi()))) {
		// Rechteck als Fläche auswerten
		double dX[5], dY[5];

			THROW_FAILED_HRESULT(Rect->GetRect(&dX[0], &dY[0], &dX[1], &dY[2]));
			dX[3] = dX[4] = dX[0];
			dX[2] = dX[1];
			dY[1] = dY[4] = dY[0];
			dY[3] = dY[2];
			*ppGeometry = new WMFlaeche<KoOrdT>(dX, dY, 5);
		}
		else {
		// sonstiges Flächenobjekt
		long lKCnt = KantenAnz(pIGeometry);

			if (1 < lKCnt) {
			// Fläche mit Löchern
			W_DGMBoundaryGeometry Area(pIGeometry);
			__Interface<IDispatch> ext;

				THROW_FAILED_HRESULT(Area -> get_Exterior(ext.ppi()));
				THROW_FAILED_HRESULT(GetArea(W_DGMPolylineGeometry(ext), &pArea));

			W_DGMGeometryCollection Coll;
			WEnumVARIANT Enum;

				THROW_FAILED_HRESULT(Area -> get_Holes(Coll.ppi()));
				THROW_FAILED_HRESULT(Coll -> get_NewEnum (Enum.ppu()));

			CComVariant var;

				for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&var), NULL); /**/) {
					if (FAILED(var.ChangeType(VT_DISPATCH)))
						continue;

				WMFlaeche<KoOrdT> *pHole = NULL;

					COM_TRY {
						THROW_FAILED_HRESULT(GetArea (W_DGMPolylineGeometry(V_DISPATCH(&var)), &pHole));
						pArea -> AddKante(*pHole, 1, -1);
					} COM_CATCH_OP(delete pHole);
					delete pHole;
				}
				*ppGeometry = pArea;
				pArea = NULL;
			}
			else {
			// nur eine Kontur
				_ASSERTE(1 == lKCnt);

			// ganz normal wie eine Polyline behandeln
				THROW_FAILED_HRESULT(GetArea(W_DGMPolylineGeometry(pIGeometry), 
					(WMFlaeche<KoOrdT> **)ppGeometry));
			}
		}
	} COM_CATCH_OP(delete pArea);
	return S_OK;
}

