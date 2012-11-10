// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2001 12:35:49 
//
// @doc
// @module PCS_CassiniSoldner.cpp | Definition of the <c CTPCS_CassiniSoldner> class

#include "stdafx.h"

#include "LibCTFImpl.h"

HRESULT CTPCSCassiniSoldner::IsValid() 
{
HRESULT hr = CTransform::IsValid();

	return SUCCEEDED(hr) ? IsInitialized() : hr;
}

HRESULT CTPCSCassiniSoldner::EvalParams()
{
	if (m_MeSelf.m_HB > m_MeSelf.m_HA) 
		return GCS_E_INVALIDELLIPSOID;		// kleine Halbachse groesser grosse Halbachse

	if (m_latOrigin > 324000.0) 
		return PCS_E_INAVLIDPARAMETER;		// B0 groesser 90 Grad

	return S_OK;
}

HRESULT CTPCSCassiniSoldner::SetParameters (long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);

// Parameter kopieren
	m_latOrigin = pParam[tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin];
	m_lonOrigin = pParam[tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin];
	m_falseEasting = pParam[tcsPP_CassiniSoldner_FalseEasting];
	m_falseNorthing = pParam[tcsPP_CassiniSoldner_FalseNorthing];

// weitere Parameter berechnen
	if (S_OK != EvalParams())
		return E_UNEXPECTED;

	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTPCSCassiniSoldner::GetDefaults (long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	pParam[tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin] = m_latOrigin;
	pParam[tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin] = m_lonOrigin;
	pParam[tcsPP_CassiniSoldner_FalseEasting] = m_falseEasting;
	pParam[tcsPP_CassiniSoldner_FalseNorthing] = m_falseNorthing;

// weitere Parameter berechnen
	if (S_OK != EvalParams())
		return E_UNEXPECTED;

	m_fIsInitialized = true;
	return S_OK;
}

// geod --> proj
HRESULT CTPCSCassiniSoldner::Transform (long nCoords, LPTCSDBLCOORD pData) 
{
	if (S_OK != IsInitialized())
		return S_FALSE;

	_ASSERTE(0 < nCoords);

double Lat, Lon, R, H;
double lonOrigin = m_lonOrigin / m_scaleXIn;
double latOrigin = m_latOrigin / m_scaleYIn;

	for(long i = 0; i < nCoords; i++, pData++) {
		Lon = pData->c1;
		Lat = pData->c2;
		Lon /= m_scaleXIn;
		Lat /= m_scaleYIn;
		Lon -= lonOrigin;
		Lat -= latOrigin;
		RETURN_FAILED_HRESULT(geoeso (Lat, Lon, R, H));
		R *= m_scaleXOut;
		H *= m_scaleXOut;
		R += m_falseEasting;
		H += m_falseNorthing;
		pData->c1 = R;
		pData->c2 = H;
	}
	return S_OK;
}

// proj --> geod
HRESULT CTPCSCassiniSoldner::TransformInverse (long nCoords, LPTCSDBLCOORD pData) 
{
	if (S_OK != IsInitialized())
		return S_FALSE;

double Lat, Lon, R, H;
double lonOrigin = m_lonOrigin / m_scaleXOut;
double latOrigin = m_latOrigin / m_scaleYOut;

	for (long i = 0; i < nCoords; i++, pData++) {
		R = pData->c1;
		H = pData->c2;
		R -= m_falseEasting;
		H -= m_falseNorthing;
		R /= m_scaleXOut;
		H /= m_scaleYOut;
		RETURN_FAILED_HRESULT(esogeo (R, H, Lat, Lon));
		Lon *= m_scaleXIn;
		Lat *= m_scaleYIn;
		Lon += lonOrigin;
		Lat += latOrigin;
		pData->c1 = Lon;
		pData->c2 = Lat;
	}
	return S_OK;
}

//
//       *****************************************************************
//       * Soldnersche zu geographischen Koordinaten                     *
//       *****************************************************************
//       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
//       Dokumentationsnummer: -
//       Autor:                Major, Walter
//       Datum:                06-Nov-90
//       Modulname:            *** ESOGEO ***
//       Routinenummer:        -
//       Programmiersprache:   Fortran-77
//       Verwendete Funktionen und Unterprogramme
//       libF77      :         DCOS,DTAN,DSQRT
//       libpbv.a    :         -
//       libgd.a     :         -
//       libuni.a    :         -
//       libdbn.a    :         -
//       libdbr.a    :         -
//       libzipedb.a :         -
//       Common-Bloecke:       -
//       -----------------------------------------------------------------
//       Aufruf:               IRC=ESOGEO (HA,HB,B0,L0,X,Y,B,L)
//
//                             ESOGEO - FUNCTION                       I*4
//                             IRC    - Rueckkehrcode                  I*4
//
//       Parameter:
//               Input:     HA     - grosse Halbachse des Ellips. in m R*8
//                          HB     - kleine Halbachse des Ellips. in m R*8
//                          B0     - geogr. Breite des Bezugspkt. in " R*8
//                          L0     - geogr. Laenge des Bezugspkt. in " R*8
//                          X      - Soldnerscher Hochwert in m        R*8
//                          Y      - Soldnerscher Rechtswert in m      R*8
//               Output:    B      - geogr. Breite des Pkt. in "       R*8
//                          L      - geogr. Laenge des Pkt. in "       R*8
//       Aufgabenstellung, Hintergrund:
//          Die Funktionen ESOGEO.f (rechtwinklige ellipsoidische
//          Koordinaten - auch Soldnerkoordinaten genannt zu
//          geographischen Koordinaten) und GEOESO.f ( geographische
//          Koordinaten zu rechtwinkligen ellipsoidischen Koordinaten)
//          sind nach den Formeln von S.Heitz: 'Koordinaten auf
//          geodaetischen Bezugsflaechen', Ferd. Duemmlers Verlag
//          Bonn 1985 S.131f. und W. Grossmann: 'Geodaetische Rech-
//          nungen und Abbildungen in der Landesvermessung', Wiss.
//          Verlagsanstalt K.G. Hannover 1949 S.84ff. programmiert.
//          Die geographischen Koordinaten werden B und L, die des
//          Bezugspunktes B0 und L0 genannt. Die Soldnerkoordinaten
//          werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
//          Beide Formeln liefern bei Hin- und Rueckrechnung bei
//          unserer geographischen Breite und einen maximalen
//          Radius von 100 km um den Bezugspunkt wenige Zehntel-
//          millimeter bzw. wenige 0.00001 Bogensekunden Differenz.
//	    Müggelturm :
//Walter(?):		Y = R = 5406523,677, X = H = 5805415,899
//
//		52°25'07.1338"  188707.1338 (Bessel)
//		13°37'37.9332"   49057.9332
//
//          In GEOESO werden die Koeffizienten der Potenzen von Delta L
//          bei der Breite B gebildet (Glieder mit Potenzen von Delta B
//          entfallen); die Meridinbogenlaenge B-B0 wird an der Stelle
//          (B+B0)*0.5 entwickelt.
//          In ESOGEO wird bei der Fusspunktbreite BF (sie wird mit
//          zwei Naeherungen ermittelt) entwickelt.
//       Fehlerbehandlung:
//          ESOGEO=EOKAY  i.O.
//                =EACHS  kleine Halbachse groesser grosse Halbachse
//                =EBREIT B0 groesser 90 Grad
//       -----------------------------------------------------------------
//

HRESULT CTPCSCassiniSoldner::esogeo (double Y, double X, double &rB, double &rL)
{
long double B0B, CO, T, T2, TKL, C, ETA2, V2, V, VC, VC2;
long double CO0, V20, V0, BFN;
long double BM, COM, ETA2M, V2M, VM, VC2M, TM, T2M;
long double YV, B01, B03, B05;
long double B10, B02, B04, HIL;

// Ausgangswerte berechnen:
	C = (m_MeSelf.Ha()/m_MeSelf.Hb()) * m_MeSelf.Ha();
	B0B = m_latOrigin/m_scaleYIn;

// genäherte Fußpunktbreite
	CO0 = cos(B0B);
	V20 = 1.0 + m_MeSelf.Excentricity() * Sqr(CO0);
	V0 = sqrt(V20);
	BFN = B0B + (V20*V0/C)*X;
	BM = (BFN + B0B)/2.0;

// 2. Näherung für Fußpunktbreite
	CO0 = cos(BM);
	V20 = 1.0 + m_MeSelf.Excentricity() * Sqr(CO0);
	V0 = sqrt(V20);
	BFN = B0B + (V20*V0/C)*X;		// für mittlere Breite
	BM = (BFN + B0B) / 2.0;

	COM = cos(BM);
	ETA2M = m_MeSelf.Excentricity() * Sqr(COM);
	V2M = 1.0 + ETA2M;
	VM = sqrt(V2M);
	VC2M = V2M/Sqr(C);
	TM = tan(BM);
	T2M = Sqr(TM);				// für Fusspunktbreite

	CO = cos(BFN);
	T = tan(BFN);
	ETA2 = m_MeSelf.Excentricity() * Sqr(CO);
	V2 = 1.0 + ETA2;
	V = sqrt(V2);
	VC = (V/C)*100000.0;		// fuer Rechenschaerfe *100000
	VC2 = Sqr(VC);
	T2 = Sqr(T);
	TKL = 1.0 + T2;

// Koeffizienten berechnen:
// für L:
	B01 = VC*CO*TKL;
	B03 = -B01*VC2*T2/3.0;
	B05 = -B03*VC2 * (1.0 + 3.0*T2) / 5.0;

// für B:
	HIL = Sqr(X) * VC2M * ETA2M * (1.0 - T2M + ETA2M + 4.0*ETA2M*T2M)/8.0;
	B10 = (V2M*VM/C) * (1.0-HIL);
	B02 = -VC2*V2*T / 2.0;
	B04 = -B02*VC2*(1.0 + 3.0*T2 + ETA2 - 9.0*ETA2*T2)/12.0;

	YV = Y/100000.0;		// fuer Rechenschärfe /100000

// Länge L berechnen
	rL = B01*YV + B03*Cube(YV) + B05*Sqr(YV)*Cube(YV);
//	*L =*L * 3600.0;

// Breite B berechnen
	rB = B10*X + B02*Sqr(YV) + B04*Sqr(YV)*Sqr(YV);
//	*B = *B * 3600.0;
//
	return S_OK;
}

//
//      *****************************************************************
//      * geographischen Koordinaten zu Soldnerschen                    *
//      *****************************************************************
//      (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
//      Dokumentationsnummer: -
//      Autor:                Major, Walter
//      Datum:                06-Nov-90
//      Modulname:            *** GEOESO ***
//      Routinenummer:        -
//      Programmiersprache:   Fortran-77
//      Verwendete Funktionen und Unterprogramme
//      libF77      :         DCOS,DTAN,DSQRT
//      libpbv.a    :         -
//      libgd.a     :         -
//      libuni.a    :         -
//      libdbn.a    :         -
//      libdbr.a    :         -
//      libzipedb.a :         -
//      Common-Bloecke:       -
//      -----------------------------------------------------------------
//      Aufruf:               IRC=GEOESO (HA,HB,B0,L0,B,L,X,Y)
//
//                            GEOESO - FUNCTION                       I*4
//                            IRC    - Rueckkehrcode                  I*4
//
//      Parameter:
//              Input:     HA     - grosse Halbachse des Ellips. in m R*8
//                         HB     - kleine Halbachse des Ellips. in m R*8
//                         B0     - geogr. Breite des Bezugspkt. in " R*8
//                         L0     - geogr. Laenge des Bezugspkt. in " R*8
//                         B      - geogr. Breite des Pkt. in "       R*8
//                         L      - geogr. Laenge des Pkt. in "       R*8
//              Output:    X      - Soldnerscher Hochwert in m        R*8
//                         Y      - Soldnerscher Rechtswert in m      R*8
//      Aufgabenstellung, Hintergrund:
//         Die Funktionen ESOGEO.f (rechtwinklige ellipsoidische
//         Koordinaten - auch Soldnerkoordinaten genannt zu
//         geographischen Koordinaten) und GEOESO.f ( geographische
//         Koordinaten zu rechtwinkligen ellipsoidischen Koordinaten)
//         sind nach den Formeln von S.Heitz: 'Koordinaten auf
//         geodaetischen Bezugsflaechen', Ferd. Duemmlers Verlag
//         Bonn 1985 S.131f. und W. Grossmann: 'Geodaetische Rech-
//         nungen und Abbildungen in der Landesvermessung', Wiss.
//         Verlagsanstalt K.G. Hannover 1949 S.84ff. programmiert.
//         Die geographischen Koordinaten werden B und L, die des
//         Bezugspunktes B0 und L0 genannt. Die Soldnerkoordinaten
//         werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
//         Beide Formeln liefern bei Hin- und Rueckrechnung bei
//         unserer geographischen Breite und einen maximalen
//         Radius von 100 km um den Bezugspunkt wenige Zehntel-
//         millimeter bzw. wenige 0.00001 Bogensekunden Differenz.
//         In GEOESO werden die Koeffizienten der Potenzen von Delta L
//         bei der Breite B gebildet (Glieder mit Potenzen von Delta B
//         entfallen); die Meridinbogenlaenge B-B0 wird an der Stelle
//         (B+B0)*0.5 entwickelt.
//         In ESOGEO wird bei der Fusspunktbreite BF (sie wird mit
//         zwei Naeherungen ermittelt) entwickelt.
//      Fehlerbehandlung:
//         GEOESO=EOKAY  i.O.
//               =EACHS  kleine Halbachse groesser grosse Halbachse
//               =EBREIT B0 groesser 90 Grad
//      -----------------------------------------------------------------
//

HRESULT CTPCSCassiniSoldner::geoeso(double B, double L, double &rY, double &rX)
{
long double CO, T, T2, TKL, C, L0L, B0B, ETA2, V, V2, CV, CV3, VKL, FA;
long double DB, DL, BM, COM, V2M, VM, ETA2M, TM, HIM;
long double B01, B20, B40, B10, B30, B50;

// Ausgangswerte berechnen:
	C = (m_MeSelf.Ha()/m_MeSelf.Hb()) * m_MeSelf.Ha();
	B0B = m_latOrigin/m_scaleYIn;
	L0L = m_lonOrigin/m_scaleXIn;

// für mittlere Breite
	BM = (B + 2*B0B)/2;
	COM = cos(BM);
	TM = tan(BM);
	ETA2M = m_MeSelf.Excentricity() * Sqr(COM);
	V2M = 1.0 + ETA2M;
	VM = sqrt(V2M);

// für gegebene Breite
	CO = cos(B + B0B);
	T = tan(B + B0B);
	ETA2 = m_MeSelf.Excentricity() * Sqr(CO);
	V2 = 1.0 + ETA2;
	V = sqrt(V2);
	VKL = 1.0 - V2;
	CV = C/V;
	CV3 = CV/V2;
	T2 = Sqr(T);
	TKL = 1.0-T2;
	FA = CV*CO*T;

// Delta B und Delta L berechnen (im Bogenmaß)
    DB = B;	// - B0B;
    DL = L;	// - L0L;

// Koeffizienten berechnen
// für X
    HIM = 1.0 - Sqr(TM) + ETA2M + 4.0*ETA2M*Sqr(TM);
    B01 = C/(V2M*VM);
    B01 = B01 * (1.0 + (Sqr(DB)/(8.0*Sqr(V2M))) * ETA2M*HIM);
    B20 = FA*CO/2.0;
    B40 = B20*Sqr(CO) * (5.0 - T2 + 5.0*ETA2) / 12.0;

// für Y
    B10 = CV*CO;
    B30 = -B10 * Sqr(CO) * T2 / 6.0;
    B50 = B30 * Sqr(CO) * (8.0+T2) / 20.0;

// X berechnen
	rX = B01*DB + B20*Sqr(DL) + B40 * Sqr(DL) * Sqr(DL);

// Y berechnen
	rY = B10*DL + B30*Cube(DL) + B50 * Sqr(DL) * Cube(DL);
	return S_OK;
}
