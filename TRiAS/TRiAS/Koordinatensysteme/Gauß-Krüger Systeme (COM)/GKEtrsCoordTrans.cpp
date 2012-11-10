///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GKEtrsCoordTrans.cpp | Implementation of the CGKEtrsCoordTrans
// class

#include "stdafx.h"

#include <Com/PropertyHelper.h>

#include "GKCtf_COM.h"
#include "GKEtrsCoordTrans.h"
#include "Strings.h"

#include "CtfGeoGK.h"
#include "CTFExContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// externe Funktionen
extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, int iPrec, double);

/////////////////////////////////////////////////////////////////////////////////
//// EllipsoidÜbergänge für GK-Koordinaten
//
/////////////////////////////////////////////////////////////////////////////////
//// Rechnet Koords (gk!) des 'native' Ellipsoids in GK Koordinaten des jeweils 
//// anderen Ellipsoids um
//void CGKEtrsCoordTrans::ConvertEllipse (
//	int iStrBreite, int iMeridian, long double dYGeod, long double dXGeod,
//	long double *pdYOut, long double *pdXOut)
//{
//	ASSERT(NULL != pdXOut);
//	ASSERT(NULL != pdYOut);
//
//	if (m_rgChangeEllipse == m_rgEllipseNative) {
//	// kein Ellipsoid-Übergang notwendig
//		geogau (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, pdYOut, pdXOut);
//	} 
//	else {
//	long double dX, dY;
//	long double dXOffset, dYOffset;
//
//	// in GK Koordinaten umrechnen
//		geogau (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, &dY, &dX);
//
//		switch (m_rgChangeEllipse) {
//		case CTFELLIPSE_Bessel:
//			{
//			// (ELLIPSE_ETRS89)
//			// Übergang Etrs89UTM-->BesselGK
//				ASSERT(m_fAllowChangeEllipse);
//
//			// zuerst Etrs89UTM-->KrassovskyGK
//			long double dXOut, dYOut;
//
//				Grs80Krass (dY, dX, &dYOut, &dXOut);
//
//			// dann KrassovskyGK-->BesselGK
//			long double dXT, dYT;
//
//				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
//						dYOut, dXOut, KS_BESSEL, &dYT, &dXT);
//				modko_B (dYT, dXT, &dYOffset, &dXOffset);
//				*pdXOut = dXOut - dXOffset;
//				*pdYOut = dYOut - dYOffset;
//			}
//			break;
//
//		case CTFELLIPSE_Krassovsky:
//			{
//			// (ELLIPSE_ETRS89)
//			// Übergang Etrs89UTM-->KrassovskyGK
//				ASSERT(m_fAllowChangeEllipse);
//				Grs80Krass (dY, dX, pdYOut, pdXOut);
//			}
//			break;
//
//		case CTFELLIPSE_Etrs89:
//			{
//			// (ELLIPSE_ETRS89)
//			// kein Übergang
//				ASSERT(CTFELLIPSE_Etrs89 == m_rgChangeEllipse);	// snh
//			}
//			break;
//		}
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Rechnet GK des jeweils anderen Ellipsoids in 'native' Koordinaten (geod) um
//void CGKEtrsCoordTrans::InvConvertEllipse (
//	int iStrBreite, int iMeridian, long double dY, long double dX,
//	long double *pdYOut, long double *pdXOut)
//{
//	ASSERT(NULL != pdXOut);
//	ASSERT(NULL != pdYOut);
//
//	if (m_rgEllipseNative == m_rgChangeEllipse) {
//	// kein Ellipsoid-Übergang notwendig
//		gaugeo (HA, HB, iStrBreite, iMeridian, dY, dX, KS, pdYOut, pdXOut);
//	} 
//	else {
//	long double dXOut, dYOut;
//	long double dOffsetX, dOffsetY;
//
//		switch (m_rgChangeEllipse) {	// ZielEllipse
//		case CTFELLIPSE_Bessel:
//			{
//			// (ELLIPSE_ETRS89)
//			// Übergang BesselGK-->Etrs89UTM
//				ASSERT(m_fAllowChangeEllipse);
//
//			// zuerst BesselGK-->KrassovskyGK
//			long double dXOut, dYOut;
//
//				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
//						dY, dX, KS_BESSEL, &dYOut, &dXOut);
//				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
//				dX += dOffsetX;
//				dY += dOffsetY;
//
//			// dann KrassovskyGK-->Etrs89UTM
//				KrassGrs80 (dY, dX, &dYOut, &dXOut);
//			}
//			break;
//
//		case CTFELLIPSE_Krassovsky:
//			{
//			// (ELLIPSE_ETRS89)
//			// Übergang KrassovskyGK-->Etrs89UTM
//				ASSERT(m_fAllowChangeEllipse);
//				KrassGrs80 (dY, dX, &dYOut, &dXOut);
//			}
//			break;
//
//		case CTFELLIPSE_Etrs89:
//			{
//			// (ELLIPSE_ETRS89)
//			// kein Übergang
//				ASSERT(CTFELLIPSE_Etrs89 == m_rgChangeEllipse);	// snh
//			}
//			break;
//		}
//
//	// in geodätische Koordinaten umsetzen
//		gaugeo (HA, HB, iStrBreite, iMeridian, dYOut, dXOut, KS, pdYOut, pdXOut);
//	}
//}

/////////////////////////////////////////////////////////////////////////////
// CGKEtrsCoordTrans

void CGKEtrsCoordTrans::InitVars (ITRiASProperties *pIProps)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// voreinstellen auf Bessel, Gauß/Krüger 6(12)
// (ELLIPSE_ETRS89)
//	HA = HA_ETRS89;
//	HB = HB_ETRS89;
long lMode = GetProperty (pIProps, g_cbShowGKCoords, 1L , LOCALE_ENGLISH);

	KS = KS_ETRS89;
	m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Etrs89;
	m_rgEllipseNative = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Etrs89;
	m_iMeridian = DEF_MERIDIAN_ETRS89;			// Meridian für GK
	m_iStrBreite = DEF_STRBREITE_ETRS89;		// Streifenbreite für GK

	switch (lMode) {
	case 1:
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_SelectMeridian;
		break;

	default:
	case 2:
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_AutoMeridian;
		break;

	case (1 | 0x04):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_SelectMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Bessel;
		break;

	case (2 | 0x04):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Bessel;
		break;

	case (1 | 0x08):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_SelectMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;

	case (2 | 0x08):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse)
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;

	case 0:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		break;

	case 0x04:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Bessel;
		break;

	case 0x08:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse)
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Properties
STDMETHODIMP CGKEtrsCoordTrans::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pVal);

CString	strDesc, text;
char cbStrBreite[16];
char cbMeridian[16];

	if (CTF_Geodetical == m_CTFType) {
	// 'Geodätische Koordinaten - '
		ATLTRY (strDesc.LoadString (IDS_DESCRIPTION));
	} 
	else {
		wsprintf (cbStrBreite, "%d", m_iStrBreite);

		if (m_rgChangeEllipse != CTFELLIPSE_Etrs89) {
		// GK Projektion
			if (CTFMODE_AutoMeridian == m_CTFMode) {
			// 'Gauß/Krüger (%d° Streifen) - '
				AfxFormatString1 (strDesc, IDS_DESCRIPTIONGKAUTO, cbStrBreite);
			} 
			else {
			// 'Gauß/Krüger (%d/%d) - '
				wsprintf (cbMeridian, "%d", m_iMeridian);
				AfxFormatString2 (strDesc, IDS_DESCRIPTIONGK, cbMeridian, cbStrBreite);
			}
		}
		else {
		// UTM Projektion
			if (CTFMODE_AutoMeridian == m_CTFMode) {
			// 'UTM (%d° Streifen) - '
				AfxFormatString1 (strDesc, IDS_DESCRIPTIONUTMAUTO, cbStrBreite);
			} 
			else {
			// 'UTM (%d/%d) - '
				wsprintf (cbMeridian, "%d", m_iMeridian);
				AfxFormatString2 (strDesc, IDS_DESCRIPTIONUTM, cbMeridian, cbStrBreite);
			}
		}
	}

	/*if (m_rgEllipseNative != m_rgChangeEllipse) */{
		switch (m_rgChangeEllipse) {
		case CTFELLIPSE_Bessel:
		// 'Bessel-Ellipsoid [System 40/83]'
			VERIFY (text.LoadString (IDS_BESSEL_ELLIPSE));
			break;

		case CTFELLIPSE_Krassovsky:
		// 'Krassovsky-Ellipsoid [System 42/83]'
			VERIFY (text.LoadString (IDS_KRASSOVSKY_ELLIPSE));
			break;

		case CTFELLIPSE_Etrs89:
		// 'Ellipsoid des ETRS89'
			VERIFY (text.LoadString (IDS_ETRS89_ELLIPSE));
			break;
		}
		ASSERT (!text.IsEmpty());
		strDesc += ", ";
		strDesc += text;
	}

CComBSTR bstr (strDesc);

	if (!bstr)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}


CString CGKEtrsCoordTrans::GetEllipseStrings()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CString str;
CString strT;

	VERIFY(strT.LoadString (IDS_ETRS89_ELLIPSE));
	str = strT;
	VERIFY(strT.LoadString (IDS_BESSEL_ELLIPSE));
	str += '\n';
	str += strT;
	VERIFY(strT.LoadString (IDS_KRASSOVSKY_ELLIPSE));
	str += '\n';
	str += strT;
	return str;
}

CString CGKEtrsCoordTrans::GetCoordTypeString(
	int iEllipse, COORDTRANSFORMTYPE rgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

UINT uiResId = 0;

	if (CTF_TransMercator == rgType) {
		switch (iEllipse) {
		case CTFELLIPSE_Krassovsky:
		case CTFELLIPSE_Bessel:
			uiResId = IDS_GKCOORDS;
			break;

		case CTFELLIPSE_Etrs89:
			uiResId = IDS_UTMCOORDS;
			break;
		}
	}
	else {
		uiResId = IDS_GEODCOORDS;
	}
	_ASSERTE(0 != uiResId);

CString str;

	VERIFY(str.LoadString(uiResId));
	return str;
}

CString CGKEtrsCoordTrans::GetInternalCoordTypeString()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CString str;

	VERIFY(str.LoadString(IDS_INTERNALKOORDSUTM_DLG));
	return str;
}

TRIASCSGEODETICDATUM CGKEtrsCoordTrans::GetGeodDatum(int rgEllipse,
	bool fNativeEllipe)
{
TRIASCSGEODETICDATUM rgDatum = tcsGD_Undefined;

	switch (rgEllipse) {
	case CTFELLIPSE_Krassovsky:
		rgDatum = tcsGD_Pulkovo1942;
		break;

	case CTFELLIPSE_Bessel:
		rgDatum = tcsGD_DeutscheHauptdreiecksnetzRd83DHDN;
		break;

	case CTFELLIPSE_Etrs89:
		rgDatum = tcsGD_EuropeanTerrestrialReferenceSystem89;		
		break;
	}

	_ASSERTE(tcsGD_Undefined != rgDatum);
	return rgDatum;
}

double CGKEtrsCoordTrans::GetScaleFactor(int rgEllipse)
{
	switch (rgEllipse) {
	case CTFELLIPSE_Krassovsky:
		return KS_KRASSOVSKY;

	case CTFELLIPSE_Bessel:
		return KS_BESSEL;

	case CTFELLIPSE_Etrs89:
		return KS_ETRS89;
	}
	_ASSERTE(FALSE);
	return 1.0;
}
