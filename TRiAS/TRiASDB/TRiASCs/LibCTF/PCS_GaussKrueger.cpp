#include "stdafx.h"
#include "LibCTFImpl.h"

///////////////////////////////////////////////////////////////////////////////
// lokale Konstanten
const double CTPCSGaussKrueger::m_p2 = 1.0/2.0;
const double CTPCSGaussKrueger::m_p6 = 1.0/6.0;
const double CTPCSGaussKrueger::m_p12 = 1.0/12.0;
const double CTPCSGaussKrueger::m_p20 = 1.0/20.0;
const double CTPCSGaussKrueger::m_p30 = 1.0/30.0;
const double CTPCSGaussKrueger::m_p42 = 1.0/42.0;
const double CTPCSGaussKrueger::m_p360 = 1.0/360.0;

/****************************************************************
 * 	 Original Walter:
 * Input:
 * HA     - grosse Halbachse des Ellips. in m R*8
 * HB     - kleine Halbachse des Ellips. in m R*8
 * STRBR  - Streifenbreite in Grad            I*4
 * L0     - Mittelmeridian in Grad            I*4
 * M      - Vergroesserungsverhaeltnis        R*8
 * X      - Gauss-Krueger-Hochwert in m       R*8
 * Y      - Gauss-Krueger-Rechtswert in m     R*8
 * Output:
 * B      - geogr. Breite des Pkt. in "       R*8
 * L      - geogr. Laenge des Pkt. in "       R*8
 * Aufgabenstellung, Hintergrund:
 * Die Funktionen GAUGEO.f (Gauss-Krueger-Koordinaten zu
 * geographischen Koordinaten) und GEOGAU.f (geographische
 * Koordinaten zu Gauss-Krueger-Koordinaten) sind nach
 * den Formeln von K. Hubeny: 'Isotherme Koordinatensysteme
 * und konforme Abbildungen des Rotationsellipsoides',
 * Mitteilungen der geodaetischen Institute der TU Graz,
 * Folge 27, 1977, S.49 f. und S.213ff. programmiert.
 * Die Meridianbogenlaengen werden durch Integration aus
 * Koenig/Weise: 'Mathematische Grundlagen der hoeheren
 * Geodaesie und Kartographie', Springer Verlag, 1951, S.19
 * erhalten.
 * Die geographischen Koordinaten werden B und L, die des
 * Mittelmeridians L0 genannt. Die Gauss-Krueger-Koordinaten
 * werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
 * Beide Formeln liefern bei Hin- und Rueckrechnung bei
 * unserer geographischen Breite bis zu 3 Grad Abstand vom
 * Mittelmeridian eine Genauigkeit unter 0.00001 mm, bei
 * 6 Grad Abstand in X knapp 1mm.
 * 
 * In GEOGAU werden die Koeffizienten der Potenzen von Delta L
 * bei der Breite B gebildet (Glieder mit Potenzen von Delta B
 * entfallen); die Meridinbogenlaenge G wird vom Aequator aus
 * gerechnet.
 * In GAUGEO wird bei der Fusspunktbreite BF (sie wird durch
 * Iteration ermittelt) entwickelt.
 ****************************************************************/

HRESULT CTPCSGaussKrueger::IsValid() 
{
HRESULT hr = CTransform::IsValid();

	if (S_OK != hr) 
		return hr;
	if (0 != m_iZoneWidth && 3 != m_iZoneWidth && 6 != m_iZoneWidth)
		return S_FALSE;
	return m_scaleAtOrigin > 0 ? S_OK : S_FALSE;
}

HRESULT CTPCSGaussKrueger::SetParameters( long nParams, double *pParam ) 
{
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	m_latOrigin = pParam[tcsPP_GaussKrueger_LatitudeOfNaturalOrigin];
	m_lonOrigin = pParam[tcsPP_GaussKrueger_LongitudeOfNaturalOrigin];
	m_scaleAtOrigin = pParam[tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin];
	m_falseEasting = pParam[tcsPP_GaussKrueger_FalseEasting];
	m_falseNorthing = pParam[tcsPP_GaussKrueger_FalseNorthing];
	m_iZoneWidth = pParam[tcsPP_GaussKrueger_ZoneWidth];
	return S_OK;
}

HRESULT CTPCSGaussKrueger::GetDefaults( long nParams, double *pParam ) 
{
	_ASSERTE( tcsPP_SizeOfParameterSet == nParams );
	pParam[tcsPP_GaussKrueger_LatitudeOfNaturalOrigin] = m_latOrigin;
	pParam[tcsPP_GaussKrueger_LongitudeOfNaturalOrigin] = m_lonOrigin;
	pParam[tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin] = m_scaleAtOrigin;
	pParam[tcsPP_GaussKrueger_FalseEasting] = m_falseEasting;
	pParam[tcsPP_GaussKrueger_FalseNorthing] = m_falseNorthing;
	pParam[tcsPP_GaussKrueger_ZoneWidth] = m_iZoneWidth;
	return S_OK;
}

HRESULT CTPCSGaussKrueger::TransformInverse(long nCoords, LPTCSDBLCOORD pData) 
{
double Lat, Lon, R, H;
double dFalseEasting, dLonOrigin;

	if (m_iZoneWidth > 0) {
	double dMinX = pData->c1;

		if (nCoords > 1) {
		// kleinsten Rechtswert bestimmen
			for (long i = 0; i < nCoords; ++i) {
				if (dMinX < pData[i].c1)
					dMinX = pData[i].c1;
			}
		}
		RETURN_FAILED_HRESULT(GetLonOriginGK(dMinX, dLonOrigin));
		RETURN_FAILED_HRESULT(GetFalseEastingGK(dMinX, dFalseEasting));
	}
	else {
		dFalseEasting = m_falseEasting;
		dLonOrigin = m_lonOrigin;
	}

	for (long i = 0; i < nCoords; i++, pData++) {
		R = pData->c1;
		H = pData->c2;
		R -= dFalseEasting;
		H -= m_falseNorthing;
		R /= m_scaleXOut;
		H /= m_scaleYOut;
		gaugeo (m_MeSelf, H, R, Lat, Lon);
		Lon *= m_scaleXIn;
		Lat *= m_scaleYIn;
		Lon += dLonOrigin;
		Lat += m_latOrigin;
		pData->c1 = Lon;
		pData->c2 = Lat;
	}
	return S_OK;
}

HRESULT CTPCSGaussKrueger::Transform(long nCoords, LPTCSDBLCOORD pData) 
{
double Lat, Lon, R, H;
double dFalseEasting, dLonOrigin;

	if (m_iZoneWidth > 0) {
	double dMinX = pData->c1;

		if (nCoords > 1) {
		// kleinsten Rechtswert bestimmen
			for (long i = 0; i < nCoords; ++i) {
				if (dMinX < pData[i].c1)
					dMinX = pData[i].c1;
			}
		}
		RETURN_FAILED_HRESULT(GetLonOriginGeod(dMinX, dLonOrigin));
		RETURN_FAILED_HRESULT(GetFalseEastingGeod(dMinX, dFalseEasting));
	}
	else {
		dFalseEasting = m_falseEasting;
		dLonOrigin = m_lonOrigin;
	}

	for (long i = 0; i < nCoords; i++, pData++) {
		Lon = pData->c1;
		Lat = pData->c2;
		Lon -= dLonOrigin;
		Lat -= m_latOrigin;
		Lon /= m_scaleXIn;
		Lat /= m_scaleYIn;
		geogau (m_MeSelf, Lat, Lon, H, R);
		R *= m_scaleXOut;
		H *= m_scaleXOut;
		R += dFalseEasting;
		H += m_falseNorthing;
		pData->c1 = R;
		pData->c2 = H;
	}
	return S_OK;
}

#if defined(_USE_OPTIMIZED_GKTRANS)
void CTPCSGaussKrueger::geogau (ELLIPSPAR const &el, double B, double L, double &H, double &R) 
{
	H = 0.0;
	R = 0.0;

long double db = B;
long double dl = L;
long double dl2 = dl*dl;
long double dl4 = dl2*dl2;
long double dl6 = dl4*dl2;

long double c = (el.m_HA / el.m_HB) * el.m_HA;
long double e2 = (el.m_HA * el.m_HA) / (el.m_HB*el.m_HB) - 1;

long double hm = (el.m_HA + el.m_HB) * m_p2;

long double n = (el.m_HA - el.m_HB) / (el.m_HA + el.m_HB);
long double n2 = n*n;
long double n3 = n2*n;
long double n4 = n3*n;
long double n5 = n4*n;

long double aA0 = 1.0 + n2/4.0 + n4/64.0;
long double aA1 = 3.0*m_p2*(-n + n3/8.0 + n5/64.0);
long double aA2 = (15.0/16.0) * (n2 - n4/4.0);
long double aA3 = (35.0/48.0) * (-n3 + (5.0/16.0) * n5);
long double aA4 = (315.0/512.0) * n4;
long double aA5 = -(693.0/1280.0) * n5;

long double co = cosl(db);
long double co2 = co*co;
long double si = 1.0 - co2;						// sin(bf) = 1 - cos²(bf)
long double si2 = si*si;
long double si3 = si2*si;
long double co3 = co2*co;

long double sin2 = 2*si*co;						// sin(2*bf) = 2*sin(bf)*cos(bf)
long double cos2 = co2 - si2;					// cos(2*bf) = cos²(bf) - sin²(bf)
long double sin3 = 3*si - 4*si3;				// sin(3*bf) = 3*sin(bf) - 4*sin³(bf)
long double cos3 = 4*co3 - 3*co;				// cos(3*bf) = 4*cos³(bf) - 3*cos(bf)
long double sin4 = 2*sin2*cos2;					// sin(4*bf) = 2*sin(2*bf)*cos(2*bf)
long double cos4 = cos2*cos2 - sin2*sin2;		// cos(4*bf) = cos²(2*bf) - sin²(2*bf)
long double sin5 = 16*si2*si3 - 20*si3 + 5*si;	// sin(5*bf) = 16*sin5(bf) - 20*sin³(bf) + 5*sin(bf)
long double cos5 = 16*co2*co3 - 20*co3 + 5*co;	// cos(5*bf) = 16*cos5(bf) - 20*cos³(bf) + 5*cos(bf) 

//long double sin6 = 2*sin3*cos3;				// sin(6*bf) = 2*sin(3*bf)*cos(3*bf)
//long double sin8 = 2*sin4*cos4;				// sin(8*bf) = 2*sin(4*bf)*cos(4*bf)
//long double sin10 = 2*sin5*cos5;				// sin(10*bf) = 2*sin(5*bf)*cos(5*bf)

long double g = (aA0*db + aA1*sin2 + aA2*sin4 + 2*(aA3*sin3*cos3 + aA4*sin4*cos4 + aA5*sin5*cos5)) * hm;

long double coB = cosl(B);
long double coB2 = coB*coB;
long double t = tanl(B);
long double t2 = t*t;
long double eta2 = e2*coB2;
long double eta4 = eta2*eta2;
long double v2 = 1.0+eta2;
long double v = sqrtl (v2);
long double cv = c/v;

long double aB1 = m_p2*cv*t*coB2;
long double bh1 = m_p12*aB1*coB2;
long double aB3 = bh1 * (5.0 - t2 + 9.0*eta2 + 4.0*eta4);
long double aB5 = m_p30*bh1*coB2* (61.0 - 58.0*t2 + t2*t2);

long double aB0 = cv*coB;
long double bh2 = m_p6*aB0*coB2;
long double aB2 = bh2 * (1.0 - t2 + eta2);
long double bh3 = m_p20*bh2*coB2;
long double aB4 = bh3 * (5.0 - 18.0*t2 + t2*t2+ 14.0*eta2 - 58.0*t2*eta2);
long double bh4 = m_p42*bh3*coB2;
long double aB6 = bh4 * (61.0 - 479.0*t2 + 179.0*t2*t2 - t2*t2*t2);

	R = (aB0 + aB2*dl2 + aB4*dl4 + aB6*dl6) * dl * m_scaleAtOrigin;
	H = (g + aB1*dl2 + aB3*dl4 + aB5*dl6) * m_scaleAtOrigin;
}

void CTPCSGaussKrueger::gaugeo ( ELLIPSPAR const &el, double H, double R, double &B, double &L ) 
{
	B = 0.0;
	L = 0.0;

long double xi = H / m_scaleAtOrigin;
long double yi = R / (m_scaleAtOrigin * 100000.0);
long double y2 = yi*yi;
long double y4 = y2*y2;
long double y6 = y4*y2;

long double n = (el.m_HA-el.m_HB)/(el.m_HA+el.m_HB);
long double n2 = n*n;
long double n3 = n2*n;
long double n4 = n3*n;
long double n5 = n4*n;

long double aA0 = 1.0 + n2/4.0 + n4/64.0;
long double aA1 = 3.0 * m_p2 * (-n + n3/8.0 + n5/64.0);
long double aA2 = (15.0/16.0) * (n2-n4/4.0);
long double aA3 = (35.0/48.0) * (-n3 + (5.0/16.0) * n5);
long double aA4 = (315.0/512.0) * n4;
long double aA5 = -(693.0/1280.0) * n5;

long double c = (el.m_HA/el.m_HB) * el.m_HA;
long double e2 = (el.m_HA*el.m_HA) / (el.m_HB*el.m_HB) - 1.0;

long double hm = (el.m_HA+el.m_HB) * m_p2;

long double g = 0.0;
long double bf = 0.0;
long double v = 0.0;
long double v2 = 1.0;
long double vc = 1.0/aA0;
long double eta2 = 0.0;
long double co = 0.0;
long double dDelta = xi;

	while (dDelta > 0.00001 || dDelta < -0.00001) {		// fabsl(xi-g)
		bf += dDelta*vc*v2;
		co = cosl(bf);
	
	long double co2 = co*co;

		eta2 = e2*co2;
		v2 = 1.0+eta2;
		v = sqrtl (v2);
		vc = v/c;

	long double si = 1.0 - co2;						// sin(bf) = 1 - cos²(bf)
	long double si2 = si*si;
	long double si3 = si2*si;
	long double co3 = co2*co;

	long double sin2 = 2*si*co;						// sin(2*bf) = 2*sin(bf)*cos(bf)
	long double cos2 = co2 - si2;					// cos(2*bf) = cos²(bf) - sin²(bf)
	long double sin3 = 3*si - 4*si3;				// sin(3*bf) = 3*sin(bf) - 4*sin³(bf)
	long double cos3 = 4*co3 - 3*co;				// cos(3*bf) = 4*cos³(bf) - 3*cos(bf)
	long double sin4 = 2*sin2*cos2;					// sin(4*bf) = 2*sin(2*bf)*cos(2*bf)
	long double cos4 = cos2*cos2 - sin2*sin2;		// cos(4*bf) = cos²(2*bf) - sin²(2*bf)
	long double sin5 = 16*si2*si3 - 20*si3 + 5*si;	// sin(5*bf) = 16*sin5(bf) - 20*sin³(bf) + 5*sin(bf)
	long double cos5 = 16*co2*co3 - 20*co3 + 5*co;	// cos(5*bf) = 16*cos5(bf) - 20*cos³(bf) + 5*cos(bf) 

//	long double sin6 = 2*sin3*cos3;					// sin(6*bf) = 2*sin(3*bf)*cos(3*bf)
//	long double sin8 = 2*sin4*cos4;					// sin(8*bf) = 2*sin(4*bf)*cos(4*bf)
//	long double sin10 = 2*sin5*cos5;				// sin(10*bf) = 2*sin(5*bf)*cos(5*bf)

		g = (aA0*bf + aA1*sin2 + aA2*sin4 + 2*(aA3*sin3*cos3 + aA4*sin4*cos4 + aA5*sin5*cos5)) * hm;
		dDelta = xi - g;
	}

long double t = tanl (bf);
long double t2 = t*t;
long double t4 = t2*t2;

long double eta4 = eta2*eta2;
long double vc2 = vc*vc*10000000000.0;

long double aB0 = vc/co*100000.0;

long double bh1 = m_p2*vc2*t;
long double aB1 = bh1 * (-1.0 - eta2);
long double aB3 = (5.0 + 3.0*t2 + 6.0*eta2 - 3.0*eta4 - 6.0*t2*eta2 - 9.0*t2*eta4) * m_p12*bh1*vc2;
long double aB5 = (-61.0 - 90.0*t2 - 45.0*t4 - 92.0*eta2 + 147.0*t2*eta2 + 45.0*t4*eta2) * m_p360*bh1*vc2*vc2;

long double bh2 = m_p6*vc2*aB0;
long double aB2 = (-1.0 - 2.0*t2 - eta2) * bh2;

long double bh3 = m_p20*bh2*vc2;
long double aB4 = (5.0 + 28.0*t2 + 24.0*t4 + 6.0*eta2 + 8.0*t2*eta2) * bh3;

long double bh4 = m_p42*bh3*vc2;
long double aB6 = (61.0 - 662.0*t2 - 1320.0*t4 - 720.0*t4*t2) * bh4;

	B = (bf + aB1*y2 + aB3*y4 + aB5*y6);
	L = (aB0 + aB2*y2 + aB4*y4 + aB6*y6) * yi;
}

#else

void CTPCSGaussKrueger::geogau (ELLIPSPAR const &el, double B, double L, double &H, double &R) 
{
	long double
		t = 0,
		t2 = 0,
		eta4 = 0,
		v2 = 0,
		bh1 = 0,
		bh2 = 0,
		bh3 = 0,
		bh4 = 0,
		v = 0,
		co = 0,
		co2 = 0,
		e2 = 0,
		g = 0,
		eta2 = 0,
		hm = 0,
		cv = 0,
		c = 0,
		n = 0,
		n2 = 0,
		n3 = 0,
		n4 = 0,
		n5 = 0,
		db = 0,
		dl = 0,
		dl2 = 0,
		dl4 = 0,
		dl6 = 0;
		
	long double aA[6];
	long double aB[7];

	memset(aA,0,sizeof(aA));
	memset(aB,0,sizeof(aB));

	H = 0.0;
	R = 0.0;

	db = B;
	dl = L;
	dl2 = dl*dl;
	dl4 = dl2*dl2;
	dl6 = dl4*dl2;

	c = (el.m_HA/el.m_HB)*el.m_HA;
	e2 = (el.m_HA*el.m_HA-el.m_HB*el.m_HB)/(el.m_HB*el.m_HB);

	hm = (el.m_HA+el.m_HB)*m_p2;

	n = (el.m_HA-el.m_HB)/(el.m_HA+el.m_HB);
	n2 = n*n;
	n3 = n2*n;
	n4 = n3*n;
	n5 = n4*n;

	aA[0] = 1.0+n2/4.0+n4/64.0;
	aA[1] = 3.0*m_p2*(-n+n3/8.0+n5/64.0);
	aA[2] = (15.0/16.0)*(n2-n4/4.0);
	aA[3] = (35.0/48.0)*(-n3+(5.0/16.0)*n5);
	aA[4] = (315.0/512.0)*n4;
	aA[5] = -(693.0/1280.0)*n5;

	g = aA[0]*db + aA[1]*sinl(2.0*db) + aA[2]*sinl(4.0*db);
	g += aA[3]*sinl(6.0*db) + aA[4]*sinl(8.0*db) + aA[5]*sinl(10.0*db);
	g *= hm;

	co = cosl (B);
	co2 = co*co;
	t = tanl (B);
	t2 = t*t;
	eta2 = e2*co2;
	eta4 = eta2*eta2;
	v2 = 1.0+eta2;
	v = sqrtl (v2);
	cv = c/v;

	aB[1] = m_p2*cv*t*co2;
	bh1 = m_p12*aB[1]*co2;
	aB[3] = bh1* (5.0 - t2 + 9.0*eta2 + 4.0*eta4);
	aB[5] = m_p30*bh1*co2* (61.0 - 58.0*t2 + t2*t2);

	aB[0] = cv*co;
	bh2 = m_p6*aB[0]*co2;
	aB[2] = bh2 * (1.0 - t2 + eta2);
	bh3 = m_p20*bh2*co2;
	aB[4] = bh3 * (5.0 - 18.0*t2 + t2*t2+ 14.0*eta2 - 58.0*t2*eta2);
	bh4 = m_p42*bh3*co2;
	aB[6] = bh4 * (61.0 - 479.0*t2 + 179.0*t2*t2 - t2*t2*t2);

	R = (aB[0] + aB[2]*dl2 + aB[4]*dl4 + aB[6]*dl6) * dl * m_scaleAtOrigin;
	H = (g + aB[1]*dl2 + aB[3]*dl4 + aB[5]*dl6) * m_scaleAtOrigin;
}


void CTPCSGaussKrueger::gaugeo (ELLIPSPAR const &el, double H, double R, double &B, double &L) 
{
	long double cor = 0,
			t = 0,
			t2 = 0,
			eta4 = 0,
			vc2 = 0,
			bh1 = 0,
			bh2 = 0,
			bh3 = 0,
			bh4 = 0,
			peps = 0,
			v = 0,
			co = 0,
			e2 = 0,
			g = 0,
			bf = 0,
			eta2 = 0,
			hm = 0,
			v2 = 0,
			vc = 0,
			c = 0,
			n = 0,
			n2 = 0,
			n3 = 0,
			n4 = 0,
			n5 = 0,
			xi = 0,
			yi = 0,
			y2 = 0,
			y4 = 0,
			y6 = 0;
	long double aA[6];
	long double aB[7];

	memset(aA,0,sizeof(aA));
	memset(aB,0,sizeof(aB));

	B = 0.0;
	L = 0.0;

	xi = H / m_scaleAtOrigin;
	yi = R / (m_scaleAtOrigin * 100000.0);
	y2 = yi*yi;
	y4 = y2*y2;
	y6 = y4*y2;

	n = (el.m_HA-el.m_HB)/(el.m_HA+el.m_HB);
	n2 = n*n;
	n3 = n2*n;
	n4 = n3*n;
	n5 = n4*n;
	aA[0] = 1.0+n2/4.0+n4/64.0;
	aA[1] = 3.0*m_p2*(-n+n3/8.0+n5/64.0);
	aA[2] = (15.0/16.0)*(n2-n4/4.0);
	aA[3] = (35.0/48.0)*(-n3+(5.0/16.0)*n5);
	aA[4] = (315.0/512.0)*n4;
	aA[5] = -(693.0/1280.0)*n5;

	peps = 0.00001;

	c = (el.m_HA/el.m_HB)*el.m_HA;
	e2 = (el.m_HA*el.m_HA-el.m_HB*el.m_HB)/(el.m_HB*el.m_HB);

	hm = (el.m_HA+el.m_HB)*m_p2;

	g = 0.0;
	bf = 0.0;
	v2 = 1.0;
	vc = 1.0/aA[0];
	while ((fabsl (xi-g)) > peps) {
		bf = bf+(xi-g)*vc*v2;
		co = cosl (bf);
		eta2 = e2*co*co;

		v2 = 1.0+eta2;
		v = sqrtl (v2);
		vc = v/c;
		g = aA[0]*bf+aA[1]*sinl(2.0*bf)+aA[2]*sinl(4.0*bf);
		g = g+aA[3]*sinl(6.0*bf)+aA[4]*sinl(8.0*bf)+aA[5]*sinl(10.0*bf);
		g = hm*g;
	}

	cor = 1.0/co;
	t = tanl (bf);
	t2 = t*t;
	eta4 = eta2*eta2;
	vc2 = vc*vc;

	bh1 = 10000000000.0*m_p2*vc2*t;
	aB[1] = bh1 * (-1.0 - eta2);
	aB[3] = 5.0 + 3.0*t2 + 6.0*eta2 - 3.0*eta4 - 6.0*t2*eta2;
	aB[3] = aB[3] - 9.0*t2*eta4;
	aB[3] = m_p12*bh1*vc2*10000000000.0*aB[3];
	aB[5] = -61.0 - 90.0*t2 - 45.0*t2*t2 - 92.0*eta2;
	aB[5] = aB[5] + 147.0*t2*eta2 + 45.0*t2*t2*eta2;
	aB[5] = m_p360*bh1*vc2*10000000000.0*vc2*10000000000.0*aB[5];

	aB[0] = vc*100000.0*cor;
	bh2 = m_p6*vc2*10000000000.0*aB[0];
	aB[2] = bh2 * (-1.0 - 2.0*t2 - eta2);
	bh3 = m_p20*bh2*vc2*10000000000.0;
	aB[4] = 5.0 + 28.0*t2 + 24.0*t2*t2 + 6.0*eta2 + 8.0*t2*eta2;
	aB[4] = aB[4]*bh3;
	bh4 = m_p42*bh3*vc2*10000000000.0;
	aB[6] = 61.0 - 662.0*t2 - 1320.0*t2*t2 - 720.0*t2*t2*t2;
	aB[6] = aB[6]*bh4;

	B = (bf + aB[1]*y2 + aB[3]*y4 + aB[5]*y6);
	L = (aB[0] + aB[2]*y2 + aB[4]*y4 + aB[6]*y6) * yi;
}

#endif // defined(_USE_OPTIMIZED_GKTRANS)

///////////////////////////////////////////////////////////////////////////////
// UIHelper

// Implementation of get_InputMask
HRESULT CTPCSGaussKrueger::get_InputMask(COORDELEMENT rgElement, BSTR *pbstrMask)
{
CComBSTR bstrMask (L"#######");

	if (m_lPrec > 0) {
		bstrMask += L".";
		for (long i = 0; i < m_lPrec; ++i)
			bstrMask += L"#";
	}
	*pbstrMask = bstrMask.Detach();
	return S_OK;
}


