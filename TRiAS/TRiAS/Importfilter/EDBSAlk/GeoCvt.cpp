// ArcConversion.cpp : Implementation of CArcConversion
#include "stdafx.h"
#include "MetaData.h"
#include "GeoCvt.h"
#include <math.h>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(NULL==(x)){}else{delete(x);(x)=NULL;}
#endif // DELETE_OBJ

#include <COM\SafeArray.h>


//#fje980727//=====================================================================
//#include "W:\Projekte\GeoCvt\GeometryConversionService.h"
//#include "W:\Projekte\GeoCvt\GeometryConversionService_i.c"
//extern IArcConversion *g_pIArcConversion;

const double Pi = 3.141592653589793238462643383279502884197169399;


void ConvertArc1(double StartX, double StartY, double OriginX, double OriginY, double EndX, double EndY, SAFEARRAY ** PolyLineArc)
{
/*
	HRESULT hResult;

	if( !g_pIArcConversion ) {
		hResult = CoCreateInstance( CLSID_ArcConversion, NULL, CLSCTX_LOCAL_SERVER, IID_IArcConversion, (LPVOID *)&g_pIArcConversion );
		if (FAILED(hResult))
			return;
		g_pIArcConversion->put_Anisotropy( 1.0 );
		g_pIArcConversion->put_Precision( g_pMetaData->dArcPrecision );
	}
	if (FAILED(g_pIArcConversion -> Convert1(
			StartX, StartY,
			OriginX, OriginY,
			EndX, EndY,
			PolyLineArc )))
		return;
*/
			CArcConversion cvt;
			cvt.put_Anisotropy( 1.0 );
			cvt.put_Precision( g_pMetaData->dArcPrecision );
			cvt.Convert1(
					StartX, StartY,
					OriginX, OriginY,
					EndX, EndY,
					PolyLineArc );

}			




/////////////////////////////////////////////////////////////////////////////
// CArcConversion
CArcConversion::CArcConversion()
{
	m_dAnisotropy = 1,0;
	m_dPrecision = -4.0;
}


CArcConversion::Convert1(double StartX, double StartY, double OriginX, double OriginY, double EndX, double EndY, SAFEARRAY ** PolyLineArc)
{

//bool KreisbogenApprox (EFlaeche* pBE, double OriginX, double OriginY, double StartX, double StartY, double EndX,
//					   double EndY, DoublePair dUF, double dPrec)

//	TX_ASSERT (pBE != NULL);
//	TX_ASSERT (dPrec > 0);

//	if (! pBE || dPrec <= 0) return false;

//double m_dAnisotropy = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten

	OriginX *= m_dAnisotropy;
	StartX *= m_dAnisotropy;
	EndX *= m_dAnisotropy;
//	dPrec *= dUF.Y();

double dxa = OriginX - EndX;
double dya = OriginY - EndY;
double dxb = StartX - OriginX;
double dyb = StartY - OriginY;
double dxc = EndX - StartX;
double dyc = EndY - StartY;
double cq = dxc*dxc + dyc*dyc;			// c² (c ist die Basis des gleichschenkligen Dreiecks)
// a und b müßten eigentlich beide gleich der Pufferbreite sein; durch die Digitalgeometrie ist
// dies aber nicht garantiert, deshalb nachfolgend die Mittelbildung
double dRadius = (sqrt(dxa*dxa + dya*dya) + sqrt(dxb*dxb + dyb*dyb)) / 2.;

//=== Berechnung des Startwinkels der Strecke (OriginX,OriginY)-(StartX,StartY) ==========================
double dSinStartW = (StartY - OriginY) / dRadius;
	if (dSinStartW > 1.) dSinStartW = 1.;
	if (dSinStartW < -1.) dSinStartW = -1.;

double dStartW = asin (dSinStartW);	// Anstiegswinkels der Strecke (OriginX,OriginY)-(StartX,StartY)											
									// asin liefert Werte zwischen -90° und +90°, deshalb noch
									// evtl. Transformationen entspr. der Quadranten
	if (StartX < OriginX)					
		dStartW = Pi - dStartW;
	else if (StartY < OriginY)
		dStartW = 2.*Pi + dStartW;

//=== Berechnung des Endwinkels der Strecke (OriginX,OriginY)-(EndX,EndY) ==========================
double dSinEndW = (EndY - OriginY) / dRadius;
	if (dSinEndW > 1.) dSinEndW = 1.;
	if (dSinEndW < -1.) dSinEndW = -1.;

double dEndW = asin (dSinEndW);	// Anstiegswinkels der Strecke (OriginX,OriginY)-(StartX,StartY)											
									// asin liefert Werte zwischen -90° und +90°, deshalb noch
									// evtl. Transformationen entspr. der Quadranten
	if (EndX < OriginX)					
		dEndW = Pi - dEndW;
	else if (EndY < OriginY)
		dEndW = 2.*Pi + dEndW;

//==================================================================
/*double dCosSekW = 1. - cq/(2.*dRadius*dRadius);	// Cosinus des Kreisbogenwinkels (mit Kosinussatz)


	if (dCosSekW > 1. )
		dCosSekW = 1.;
	if (dCosSekW < -1. )
		dCosSekW = -1.;

double dSekW = acos(dCosSekW);		// Sektorwinkel (acos liefert 0 ... Pi)
*/
//=== Sektorenwinkel ===============================================================================
double dSekW = dEndW - dStartW;
	if( dSekW < 0 )
		dSekW += 2 * Pi;

double dSegW;
double dBogLaenge;
short iKAnz;

//=== Anzahl der Stützpunkte =======================================================================
	if( m_dPrecision < 0 ) {	// Angabe in Bogenmaß
		iKAnz = (short)ceil(dSekW / ((-m_dPrecision / 360) * 2 * Pi));
	}
	else {
		dBogLaenge = dSekW * dRadius;	// Länge des Kreisbogens
		iKAnz = (short) floor (dBogLaenge/m_dPrecision);	// Anzahl der Kanten
	}

	if( iKAnz  != 0 )  	// sonst braucht nichts mehr berechnet zu werden
		dSegW = dSekW / iKAnz;					// Winkel eines n-Eck-Segmentes

	CSafeArray sa (VT_R8, (iKAnz + 1) * 2 );
	{
		CSafeArrayLock<double> data(sa);
double dWi = dStartW;
		*((double*)data) = StartX;
		*((double*)data+1) = StartY;
		*((double*)data+iKAnz*2) = EndX;
		*((double*)data+iKAnz*2+1) = EndY;
		for (short i = 1; i < iKAnz; i++) {
			dWi += dSegW;
			*((double*)data+i*2) = (OriginX + dRadius*cos(dWi))/m_dAnisotropy;
			*((double*)data+i*2+1) = OriginY + dRadius*sin(dWi);
		}
	}
	*PolyLineArc = sa.Detach();
	return S_OK;
}

CArcConversion::get_Precision(double * pVal)
{
	*pVal = m_dPrecision;

	return S_OK;
}

CArcConversion::put_Precision(double newVal)
{
	m_dPrecision = newVal;

	return S_OK;
}

CArcConversion::get_Anisotropy(double * pVal)
{
	*pVal = m_dAnisotropy;

	return S_OK;
}

CArcConversion::put_Anisotropy(double newVal)
{
	m_dAnisotropy = newVal;

	return S_OK;
}
