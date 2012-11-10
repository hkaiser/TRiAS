// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 26.09.2000 07:58:28 
//
// @doc
// @module TRiASCSDistanceService.cpp | Definition of the <c CDistanceService> class

#include "stdafx.h"
#include "TRiASCs.h"

#include <Atl/Ciid.h>
#include <McKinney/OleType.h>

#include "LibCTF/LIBCTFImpl.h"
#include "EPSGMgr.h"
#include "MeasureTime.h"

#include "TRiASCsImpl.h"
#include "TRiASCoordSystem.h"
#include "TRiASCoordTransform.h"
#include "TRiASCSDistanceService.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSDatumTransformation);
DefineSmartInterface(TRiASCSPCS);

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSDistanceService

STDMETHODIMP CTRiASCSDistanceService::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASCSDistanceService
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung et.al.
HRESULT CTRiASCSDistanceService::FinalConstruct()
{
	COM_TRY {
	// Ausgabekoordinatensystem anlegen und initialisieren (WGS84, UTM 9/6, Meter)
	WTRiASCS CSOut (CLSID_TRiASCS);

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

	// da ACCURACY_Sphere == m_rgAcc, haben wir es mit einem geodätischen System zu tun
		THROW_FAILED_HRESULT(CSOut -> put_CoordSystemType(tcsCS_Geographic));
		THROW_FAILED_HRESULT(CSOut -> Recompute());

	// TransformPipe initialisieren
	WTRiASCSTransform CSS(CLSID_TRiASCSTransform);

		THROW_FAILED_HRESULT(CSS -> putref_OutputCS(CSOut));
		m_CSS = CSS;
		
	} COM_CATCH;
	return S_OK;
}

void CTRiASCSDistanceService::FinalRelease()
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

HRESULT CTRiASCSDistanceService::InitCachedValues()
{
	COM_TRY {
	// benötigte Ellipsoid-Parameter festellen
	WTRiASCS CS;
	WTRiASCSGCS GCS;
	double dHa, dF;
	
		THROW_FAILED_HRESULT(m_CSS -> get_OutputCS(CS.ppi()));
		THROW_FAILED_HRESULT(CS -> get_GeographicCS(GCS.ppi()));
		THROW_FAILED_HRESULT(GCS -> get_SemiMajorAxis(&dHa));
		THROW_FAILED_HRESULT(GCS -> get_Flattening(&dF));

		m_EP.SetMajorAxis(dHa);
		m_EP.SetFlattening(dF);

	// Maßeinheit der Abstandswerte
	WTRiASCSPCS PCS;

		if (SUCCEEDED(CS -> get_ProjectedCS(PCS.ppi()))) {
		// nur, wenn eine Projektion gegeben ist (sollte aber)
			THROW_FAILED_HRESULT(PCS -> get_UnitOfLength(&m_rgUoL));
		}
		else
			m_rgUoL = tcsUOL_Metre;

	// Maßeinheit der Winkel
		if (FAILED(GCS -> get_UnitOfAngle(&m_rgUoA))) 
			m_rgUoA = tcsUOA_Second;

	// Umrechnungen der Maßeinheiten vorinitialisieren
	LPCPARAMETERSET	p = _EM.GetParameters (tcsCType_UOL, m_rgUoL); 

		_ASSERTE(NULL != p);
		m_dConvertUoL = (NULL != p) ? p->p[1] / p->p[0] : 1.0;

		p = _EM.GetParameters(tcsCType_UOA, m_rgUoA);
		_ASSERTE(NULL != p);
		m_dConvertUoA = (NULL != p) ? p->p[1] / p->p[0] : 1.0;
		
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
// Implementation of put_Accuracy
STDMETHODIMP CTRiASCSDistanceService::put_Accuracy(DIST_ACCURACY newVal)
{
	if (m_rgAcc != newVal) {
	WTRiASCS CSOut;

		RETURN_FAILED_HRESULT(m_CSS -> get_OutputCS(CSOut.ppi()));

		switch (newVal)	{
		case ACCURACY_Planar:
			RETURN_FAILED_HRESULT(CSOut -> put_CoordSystemType(tcsCS_Projected));
			m_rgAcc = newVal;
			break;

		case ACCURACY_SphericArithMean:			// ACCURACY_Spheric
		case ACCURACY_SphericMajorAxis:
		case ACCURACY_SphericGeomMean:
		case ACCURACY_SphericHarmMean:
		case ACCURACY_SphericVolume:
		case ACCURACY_SphericArea:
		case ACCURACY_SphericGeomMeanCurvatureRadii:
		case ACCURACY_Ellipsoidal1:				// ACCURACY_Ellipsoidal
		case ACCURACY_Ellipsoidal2:
			RETURN_FAILED_HRESULT(CSOut -> put_CoordSystemType(tcsCS_Geographic));
			m_rgAcc = newVal;
			break;

		default:
			MAKE_ERROR(CS_E_INVALIDACCURACYTYPE);
			break;
		}

	// KoordinatensystemPipe neu berechnen
		RETURN_FAILED_HRESULT(CSOut -> Recompute());
	}
	return S_OK;
}

// Implementation of get_Accuracy
STDMETHODIMP CTRiASCSDistanceService::get_Accuracy(DIST_ACCURACY *pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_rgAcc;
	return S_OK;
}

// Implementation of putref_TransformPipe
STDMETHODIMP CTRiASCSDistanceService::putref_TransformPipe(ITRiASCSTransform *newVal)
{
	ATLTRY(m_CSS = newVal);
	ERROR_EXPR_FALSE(NULL == newVal || m_CSS.IsValid(), E_INVALIDARG);
	return S_OK;
}

// Implementation of get_TransformPipe
STDMETHODIMP CTRiASCSDistanceService::get_TransformPipe(ITRiASCSTransform **pVal)
{
	CHECKOUTPOINTER(pVal);
	(*pVal = m_CSS) -> AddRef();
	return S_OK;
}

// Implementation of get_LastTime
STDMETHODIMP CTRiASCSDistanceService::get_LastTime(double *pVal)
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_timeLastTime;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methoden
STDMETHODIMP CTRiASCSDistanceService::GetDistancePts(
	VARIANT CS1, VARIANT Pts1, VARIANT CS2, VARIANT Pts2, double *pDist)
{
	CHECKOUTPOINTER(pDist);
	COM_TRY {
	// Zeitmessung initialisieren
	CMeasureTime Time;

		m_timeLastTime = 0.;

	// hier gehts los
	CIID Guid1, Guid2;

		THROW_FAILED_HRESULT(RetrieveCSGuid(CS1, &Guid1));
		THROW_FAILED_HRESULT(RetrieveCSGuid(CS2, &Guid2));
	
	// ersten Koordinatenpunkt isolieren
	SAFEARRAY *pArray = NULL;

		ERROR_EXPR_FALSE(V_ISARRAY(&Pts1) && V_R8(&Pts1), E_INVALIDARG);
		pArray = V_ISBYREF(&Pts1) ? *Pts1.pparray : Pts1.parray;
		ERROR_EXPR_FALSE(NULL != pArray, E_INVALIDARG);

	MC::ArrayDouble	pt1;

		ERROR_EXPR_FALSE(pt1.Attach (pArray), E_INVALIDARG);
		ERROR_EXPR_FALSE(0 == pt1.Elements() % 3, CST_E_INVALIDCOORDCOUNT);

	// zweiten Koordinatenpunkt isolieren
		ERROR_EXPR_FALSE(V_ISARRAY(&Pts2) && V_R8(&Pts2), E_INVALIDARG);
		pArray = V_ISBYREF(&Pts2) ? *Pts2.pparray : Pts2.parray;
		ERROR_EXPR_FALSE(NULL != pArray, E_INVALIDARG);

	MC::ArrayDouble	pt2;

		ERROR_EXPR_FALSE(pt2.Attach (pArray), E_INVALIDARG);
		ERROR_EXPR_FALSE(0 == pt2.Elements() % 3, CST_E_INVALIDCOORDCOUNT);

	// jetzt eigentliche Berechnungen durchführen
		THROW_FAILED_HRESULT(CalculateDistance (Guid1, (CSCOORD *)&pt1[0], Guid2, (CSCOORD *)&pt2[0], pDist));

		m_timeLastTime = Time.GetElapsedTime();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Guid eines übergebenen Koordinatensystemes bestimmen
inline void __InitPointer (CIID *p) { *p = GUID_NULL; }		// specializing template for CHECKOUTPOINTER()

HRESULT CTRiASCSDistanceService::RetrieveCSGuid(VARIANT vCSArg, CIID *pGuid)
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

///////////////////////////////////////////////////////////////////////////////
// Abstandsberechnugn für 'raw' Daten
HRESULT CTRiASCSDistanceService::CalculateDistance (
	REFGUID rGuid1, CSCOORD *pPt1, REFGUID rGuid2, CSCOORD *pPt2, double *pDist)
{
	CHECKOUTPOINTER(pDist);

// gecachte Werte neu initialisieren
	RETURN_FAILED_HRESULT(InitCachedValues());

// direkt auf das Transformationsobjekt zugreifen
CTRiASCoordTransform *pCSS;

	RETURN_FAILED_HRESULT(QueryImplementation(m_CSS, &pCSS));

// Koordinaten inplace ins BezugsSystem konvertieren
	RETURN_FAILED_HRESULT(pCSS -> Transform(rGuid1, 1, pPt1));
	RETURN_FAILED_HRESULT(pCSS -> Transform(rGuid2, 1, pPt2));

// jetzt Abstand berechnen
	switch (m_rgAcc) {
	case ACCURACY_Planar:
		RETURN_FAILED_HRESULT(CalculateDistancePlanar(pPt1, pPt2, pDist));
		break;

	case ACCURACY_SphericMajorAxis:
	case ACCURACY_SphericArithMean:
	case ACCURACY_SphericGeomMean:
	case ACCURACY_SphericHarmMean:
	case ACCURACY_SphericVolume:
	case ACCURACY_SphericArea:
	case ACCURACY_SphericGeomMeanCurvatureRadii:
		RETURN_FAILED_HRESULT(CalculateDistanceSpheric(pPt1, pPt2, pDist));
		break;

	case ACCURACY_Ellipsoidal1:
		RETURN_FAILED_HRESULT(CalculateDistanceEllipsoidal1(pPt1, pPt2, pDist));
		break;

	case ACCURACY_Ellipsoidal2:
		RETURN_FAILED_HRESULT(CalculateDistanceEllipsoidal2(pPt1, pPt2, pDist));
		break;

	default:
		MAKE_ERROR(CS_E_INVALIDACCURACYTYPE);
		break;
	}
	return S_OK;
}

// Implementation of CalculateDistancePlanar
HRESULT CTRiASCSDistanceService::CalculateDistancePlanar(CSCOORD *pPt1, CSCOORD *pPt2, double *pDist)
{
	_ASSERTE(NULL != pDist);

// Pythagoras, Resultat liefern
	*pDist = sqrt(Sqr(pPt2->X - pPt1->X) + Sqr(pPt2->Y - pPt1->Y));
	return S_OK;
}

// Implementation of CalculateDistanceSpheric
HRESULT CTRiASCSDistanceService::CalculateDistanceSpheric(CSCOORD *pPt1, CSCOORD *pPt2, double *pDist)
{
	_ASSERTE(NULL != pDist);

double dLon1 = InvCorrectValueOfAngle(pPt1 -> X);
double dLon2 = InvCorrectValueOfAngle(pPt2 -> X);

double dLat1 = InvCorrectValueOfAngle(pPt1 -> Y);
double dLat2 = InvCorrectValueOfAngle(pPt2 -> Y);

/*<	dlon = lon2 - lon1 >*/
double dDeltaLon = (dLon2 - dLon1)/2;
/*<	dlat = lat2 - lat1 >*/
double dDeltaLat = (dLat2 - dLat1)/2;
/*<	a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2 >*/
double dA = Sqr(sin(dDeltaLat)) + cos(dLat1) * cos(dLat2) * Sqr(sin(dDeltaLon));
/*<	c = 2 * atan2( sqrt(a), sqrt(1-a) ) >*/
double dC = 2 * atan2(sqrt(dA), sqrt(1-dA));
/*<	d = R * c >*/
double dDist = m_EP.Radius(m_rgAcc, dLat1) * dC;

// Maßeinheit korrigieren, Resultat liefern
	*pDist = CorrectValueOfLength(dDist);
	return S_OK;
}

/* 
   original comment:
   *** SOLUTION OF THE GEODETIC INVERSE PROBLEM AFTER T.VINCENTY 
   *** MODIFIED RAINSFORD'S METHOD WITH HELMERT'S ELLIPTICAL TERMS 
   *** EFFECTIVE IN ANY AZIMUTH AND AT ANY DISTANCE SHORT OF ANTIPODAL 
   *** STANDPOINT/FOREPOINT MUST NOT BE THE GEOGRAPHIC POLE 

   *** A IS THE SEMI-MAJOR AXIS OF THE REFERENCE ELLIPSOID 
   *** F IS THE FLATTENING (NOT RECIPROCAL) OF THE REFERNECE ELLIPSOID 
   *** LATITUDES AND LONGITUDES IN RADIANS POSITIVE NORTH AND EAST 
   *** FORWARD AZIMUTHS AT BOTH POINTS RETURNED IN RADIANS FROM NORTH 

   *** PROGRAMMED FOR CDC-6600 BY LCDR L.PFEIFER NGS ROCKVILLE MD 18FEB75 
   *** MODIFIED FOR IBM SYSTEM 360 BY JOHN G GERGEN NGS ROCKVILLE MD 7507 
*/

HRESULT CTRiASCSDistanceService::CalculateDistanceEllipsoidal1 (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist)
{
	_ASSERTE(NULL != pDist);
	
double dLon1 = InvCorrectValueOfAngle(pPt1 -> X);
double dLon2 = InvCorrectValueOfAngle(pPt2 -> X);

double dLat1 = InvCorrectValueOfAngle(pPt1 -> Y);
double dLat2 = InvCorrectValueOfAngle(pPt2 -> Y);

// jetzt eigentliche Iteration	
const double eps = 5e-14;

/*<       R=1.D0-F >*/
double r = 1.0 - m_EP.Flatening();
/*<       TU1=R*DSIN(GLAT1)/DCOS(GLAT1) >*/
double tu1 = r * sin(dLat1) / cos(dLat1);
/*<       TU2=R*DSIN(GLAT2)/DCOS(GLAT2) >*/
double tu2 = r * sin(dLat2) / cos(dLat2);

/*<       CU1=1./DSQRT(TU1*TU1+1.) >*/
double cu1 = 1.0 / sqrt(Sqr(tu1) + 1.0);
/*<       SU1=CU1*TU1 >*/
double su1 = cu1 * tu1;
/*<       CU2=1./DSQRT(TU2*TU2+1.) >*/
double cu2 = 1.0 / sqrt(Sqr(tu2) + 1.0);

/*<       S=CU1*CU2 >*/
double dDist = cu1 * cu2;
/*<       BAZ=S*TU2 >*/
double dBackAzimuth = dDist * tu2;
/*<       FAZ=BAZ*TU1 >*/
double dForwardAzimuth = dBackAzimuth * tu1;

/*<       X=GLON2-GLON1 >*/
double dX = dLon2 - dLon2;

double dSx, dSy, dCx, dCy, dCz, dY, dC2a;
double c, d, e;

	do {
	/*<   100 SX=DSIN(X) >*/
		dSx = sin(dX);
	/*<       CX=DCOS(X) >*/
		dCx = cos(dX);
	/*<       TU1=CU2*SX >*/
		tu1 = cu2 * dSx;
	/*<       TU2=BAZ-SU1*CU2*CX >*/
		tu2 = dBackAzimuth - su1 * cu2 * dCx;
	/*<       SY=DSQRT(TU1*TU1+TU2*TU2) >*/
		dSy = sqrt(Sqr(tu1) + Sqr(tu2));
	/*<       CY=S*CX+FAZ >*/
		dCy = dDist * dCx + dForwardAzimuth;
	/*<       Y=DATAN2(SY,CY) >*/
		dY = atan2(dSy, dCy);

	/*<       SA=S*SX/SY >*/
	double sa = dDist * dSx / dSy;
		
	/*<       C2A=-SA*SA+1. >*/
		dC2a = -Sqr(sa) + 1;
	/*<       CZ=FAZ+FAZ >*/
		dCz = dForwardAzimuth + dForwardAzimuth;
	/*<       IF(C2A.GT.0.)CZ=-CZ/C2A+CY >*/
		if (dC2a > 0)
			dCz = -dCz/dC2a + dCy;

	/*<       E=CZ*CZ*2.-1. >*/
		e = 2*Sqr(dCz) - 1.0;
	/*<       C=((-3.*C2A+4.)*F+4.)*C2A*F/16. >*/
		c = ((-3*dC2a + 4) * m_EP.Flatening() + 4.0) * dC2a * m_EP.Flatening()/16.0;
	/*<       D=X >*/
		d = dX;
		
	/*<       X=((E*CY*C+CZ)*SY*C+Y)*SA >*/
		dX = ((e * dCy * c + dCz) * dSy * c + dY) * sa;
	/*<       X=(1.-C)*X*F+GLON2-GLON1 >*/
		dX = (1.0 - c) * dX * m_EP.Flatening() + dLon2 - dLon1;
		
	/*<       IF(DABS(D-X).GT.EPS) GO TO 100 >*/
	} while (fabs(d - dX) > eps);

/*<       FAZ=DATAN2(TU1,TU2) >*/
//	dForwardAzimuth = atan2(tu1, tu2);
/*<       BAZ=DATAN2(CU1*SX,BAZ*CX-SU1*CU2)+PI >*/
//	dBackAzimuth = atan2(cu1 * dSx, dBackAzimuth * dCx - su1 * cu2) + PI;
	
/*<       X=DSQRT((1./R/R-1.)*C2A+1.)+1. >*/
	dX = sqrt((1.0 / r / r - 1.0) * dC2a + 1.0) + 1.0;
/*<       X=(X-2.)/X >*/
	dX = (dX - 2.0) / dX;

/*<       C=1.-X >*/
/*<       C=(X*X/4.+1.)/C >*/
	c = (Sqr(dX)/4.0 + 1.0) / (1.0 - dX);
/*<       D=(0.375*X*X-1.)*X >*/
	d = (0.375*Sqr(dX) - 1.0) * dX;
	
/*<       X=E*CY >*/
	dX = e * dCy;
/*<       S=1.-E-E >*/
	dDist = 1.0 - e - e;
/*<       S=((((SY*SY*4.-3.)*S*CZ*D/6.-X)*D/4.+CZ)*SY*D+Y)*C*A*R >*/
	dDist = ((((4*Sqr(dSy) -3.0) * dDist * dCz * d/6.0 - dX) * d/4.0 + dCz) * dSy * d + dY) * c * m_EP.Ha() * r;

/*<       RETURN >*/
/*<       END >*/

// Maßeinheit korrigieren, Resultat liefern
	*pDist = CorrectValueOfLength(dDist);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// from proj.4 package
HRESULT CTRiASCSDistanceService::CalculateDistanceEllipsoidal2 (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist)
{
	_ASSERTE(NULL != pDist);
	
double dLon1 = InvCorrectValueOfAngle(pPt1 -> X);
double dLon2 = InvCorrectValueOfAngle(pPt2 -> X);

double dLat1 = InvCorrectValueOfAngle(pPt1 -> Y);
double dLat2 = InvCorrectValueOfAngle(pPt2 -> Y);

double th1, th2;
//double tandlammp, u, v;
double onef = m_EP.OneF();

	if (m_EP.IsEllipse()) {
		th1 = atan(onef * tan(dLat1));
		th2 = atan(onef * tan(dLat2));
	} else {
		th1 = dLat1;
		th2 = dLat2;
	}

double thm = (th1 + th2) / 2.;
double dthm = (th2 - th1) / 2.;
double dlam = adjust_lon(dLon2 - dLon1);
const double DTOL = 1e-12;

	if (fabs(dlam) < DTOL && fabs(dthm) < DTOL) {
//		al12 = al21 = 0.
	// Maßeinheit korrigieren, Resultat liefern
		*pDist = CorrectValueOfLength(0.);
		return S_OK;
	}

double sindlamm = sin(dlam / 2.);
double costhm = cos(thm);	
double sinthm = sin(thm);
double cosdthm = cos(dthm);	
double sindthm = sin(dthm);

double L = Sqr(sindthm) + (Sqr(cosdthm) - Sqr(sinthm)) * Sqr(sindlamm);
double cosd = 1. - L - L;
double d = acos(cosd);
double S = 0.;

	if (m_EP.IsEllipse()) {
	double E = cosd + cosd;
	double sind = sin(d);
	double Y = sinthm * cosdthm;

		Y *= (Y + Y) / (1. - L);

	double T = sindthm * costhm;

		T *= (T + T) / L;

	double X = Y + T;

		Y -= T;
		T = d / sind;

	double D = 4. * Sqr(T);
	double A = D * E;
	double B = D + D;
	
		S = m_EP.Ha() * sind * (T - (onef/4.) * (T * X - Y) +
			Sqr(onef)/64. * (X * (A + (T - .5 * (A - E)) * X) -
			Y * (B + E * Y) + D * X * Y));
//		tandlammp = tan(.5 * (dlam - .25 * (Y + Y - E * (4. - X)) *
//			(f2 * T + f64 * (32. * T - (20. * T - A)
//			* X - (B + 4.) * Y)) * tan(dlam)));
	} else {
		S = m_EP.Ha() * d;
//		tandlammp = tan(dlamm);
	}
//
//double u = atan2(sindthm, (tandlammp * costhm));
//double v = atan2(cosdthm, (tandlammp * sinthm));
//
//	al12 = adjlon(TWOPI + v - u);
//	al21 = adjlon(TWOPI - v - u);

// Maßeinheit korrigieren, Resultat liefern
	*pDist = CorrectValueOfLength(S);
	return S_OK;
}

///* *** SOLUTION OF THE GEODETIC DIRECT PROBLEM AFTER T.VINCENTY */
///* *** MODIFIED RAINSFORD'S METHOD WITH HELMERT'S ELLIPTICAL TERMS */
///* *** EFFECTIVE IN ANY AZIMUTH AND AT ANY DISTANCE SHORT OF ANTIPODAL */
//
///* *** A IS THE SEMI-MAJOR AXIS OF THE REFERENCE ELLIPSOID */
///* *** F IS THE FLATTENING OF THE REFERENCE ELLIPSOID */
///* *** LATITUDES AND LONGITUDES IN RADIANS POSITIVE NORTH AND EAST */
///* *** AZIMUTHS IN RADIANS CLOCKWISE FROM NORTH */
///* *** GEODESIC DISTANCE S ASSUMED IN UNITS OF SEMI-MAJOR AXIS A */
//
///* *** PROGRAMMED FOR CDC-6600 BY LCDR L.PFEIFER NGS ROCKVILLE MD 20FEB75 */
///* *** MODIFIED FOR SYSTEM 360 BY JOHN G GERGEN NGS ROCKVILLE MD 750608 */
//int dirct1_(double glat1, double glon1, double faz, double s, double *pglat2, double *pglon2, double *pbaz)
//{
//// Initialized data 
//const double eps = 5e-14;
//
//	/* System generated locals */
//	doublereal d__1;
//
//// Local variables 
//static double c__, d__, e, r__, x, y, cf, sa, cu, sf, cy, cz, su, tu, sy, c2a;
//
//	r__ = 1. - elipsoid_1.f;
//	tu = r__ * sin(glat1) / cos(glat1);
//	sf = sin(faz);
//	cf = cos(faz);
//
//	*pbaz = 0.0;
//	if (cf != 0.0)
//		*pbaz = atan2(tu, cf) * 2.0;
//
//	cu = 1.0 / sqrt(tu * tu + 1.0);
//	su = tu * cu;
//	sa = cu * sf;
//	c2a = -sa * sa + 1.;
//	x = sqrt((1.0 / r__ / r__ - 1.0) * c2a + 1.0) + 1.0;
//	x = (x - 2.0) / x;
//	c__ = 1.0 - x;
//	c__ = (x * x / 4.0 + 1) / c__;
//	d__ = (x * 0.375 * x - 1.) * x;
//	tu = s / r__ / elipsoid_1.a / c__;
//	y = tu;
//
//	do {
//		sy = sin(y);
//		cy = cos(y);
//		cz = cos(*pbaz + y);
//		e = cz * cz * 2.0 - 1.0;
//		c__ = y;
//		x = e * cy;
//		y = e + e - 1.;
//		y = (((sy * sy * 4.0 - 3.0) * y * cz * d__ / 6.0 + x) * d__ / 4.0 - cz) * sy * d__ + tu;
//	} while ((d__1 = y - c__, abs(d__1)) > eps);
//
//	*pbaz = cu * cy * cf - su * sy;
//	c__ = r__ * sqrt(sa * sa + *pbaz * *pbaz);
//	d__ = su * cy + cu * sy * cf;
//	*glat2 = atan2(d__, c__);
//
//	c__ = cu * cy - su * sy * cf;
//	x = atan2(sy * sf, c__);
//	c__ = ((c2a * -3.0 + 4.0) * elipsoid_1.f + 4.0) * c2a * elipsoid_1.f / 16.0;
//	d__ = ((e * cy * c__ + cz) * sy * c__ + y) * sa;
//	*pglon2 = *glon1 + x -(1. - c__) * d__ * elipsoid_1.f;
//
//	*pbaz = atan2(sa, *pbaz) + const_1.pi;
//
//	return 0;
//} 
