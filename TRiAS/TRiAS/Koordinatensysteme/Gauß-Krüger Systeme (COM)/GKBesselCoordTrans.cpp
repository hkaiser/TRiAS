// @doc
// @module GKBesselCoordTrans.cpp | Implementation of CGKBesselCoordTrans

#include "stdafx.h"

#include <Com/PropertyHelper.h>
//#include <TDBGeo.h>
//#include <TDBGeo_i.c>

#include "GKCtf_COM.h"
#include "GKBesselCoordTrans.h"
#include "Strings.h"
#include "Wrapper.h"

#include "CtfGeoGK.h"
#include "CTFExContext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Das folgende nur eingeschränktem Kundenkreis zugänglich machen
// Der Ellipsoidübergang wird mit RegEntry
//		HKCU\Software\uve\TRiAS\Config\AllowExtendedCoords:REG_DWORD:ALLOW_COOKIE
// bzw. SysAdminMode erlaubt.
//
#define ALLOW_COOKIE	DWORD(0x0023484b)

/////////////////////////////////////////////////////////////////////////////////
//// EllipsoidÜbergänge für GK-Koordinaten
//
/////////////////////////////////////////////////////////////////////////////////
//// Rechnet Koords (geod!) des 'native' Ellipsoids in GK Koordinaten des jeweils 
//// anderen Ellipsoids um
//// in : geod
//// out : gk
//void CGKBesselCoordTrans::ConvertEllipse (
//	int iStrBreite, int iMeridian, long double dYIn, long double dXIn,
//	long double *pdYOut, long double *pdXOut)
//{
//	ASSERT(NULL != pdXOut);
//	ASSERT(NULL != pdYOut);
//
//long double dYGeod;
//long double dXGeod;
//
//	if (m_rgChangeEllipse == m_rgEllipseNative) {
//	// kein Ellipsoid-Übergang notwendig
//		geogau (HA, HB, iStrBreite, iMeridian, dYIn, dXIn, KS, pdYOut, pdXOut);
//	} 
//	else {
//		gaugeo (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, &dYGeod, &dXGeod);
//
//	long double dX, dY;
//	long double dXOffset, dYOffset;
//
//	// in GK Koordinaten umrechnen
//		geogau (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, &dY, &dX);
//
//		switch (m_rgChangeEllipse) {
//		case CTFELLIPSE_Bessel:
//			{
//			// (ELLIPSE_BESSEL)
//			// kein Übergang
//				ASSERT(CTFELLIPSE_Bessel == m_rgChangeEllipse);	// snh
//			}
//			break;
//
//		case CTFELLIPSE_Krassovsky:
//			{
//			// (ELLIPSE_BESSEL)
//			// Übergang BesselGK-->KrassovskyGK
//				ASSERT(m_fAllowChangeEllipse);
//
//			// Ellipsoidparameter müssen stimmen, da eine hin/zurück-
//			// Konvertierung eingespart worden ist
//				ASSERT(HA == HA_BESSEL);
//				ASSERT(HB == HB_BESSEL);
//				ASSERT(KS == KS_BESSEL);
//
//				modko_B (dYGeod, dXGeod, &dYOffset, &dXOffset);
//				*pdXOut = dX + dXOffset;
//				*pdYOut = dY + dYOffset;
//			}
//			break;
//
//		case CTFELLIPSE_Etrs89:
//			{
//			// (ELLIPSE_BESSEL)
//			// Übergang BesselGK-->Etrs89UTM
//				ASSERT(m_fAllowChangeEllipse);
//
//			// zuerst BesselGK-->KrassovskyGK
//			long double dXOut, dYOut;
//			long double dOffsetX, dOffsetY;
//
//				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
//						dY, dX, KS_BESSEL, &dYOut, &dXOut);
//				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
//				dXOut = dX + dOffsetX;
//				dYOut = dY + dOffsetY;
//
//			// dann KrassovskyGK-->Etrs89UTM
//				KrassGrs80 (dYOut, dXOut, pdYOut, pdXOut);
//			}
//			break;
//		}
//	}
//}
//
/////////////////////////////////////////////////////////////////////////////////
//// Rechnet GK des jeweils anderen Ellipsoids in 'native' Koordinaten (geod) um
//void CGKBesselCoordTrans::InvConvertEllipse (
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
//			// (ELLIPSE_BESSEL)
//			// kein Übergang
//				ASSERT(CTFELLIPSE_Bessel == m_rgChangeEllipse);	// snh
//			}
//			break;
//
//		case CTFELLIPSE_Krassovsky:
//			{
//			// (ELLIPSE_BESSEL)
//			// Übergang KrassovskyGK-->BesselGK
//				ASSERT(m_fAllowChangeEllipse);
//
//				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
//						dY, dX, KS_BESSEL, &dYOut, &dXOut);
//				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
//				dXOut = dX - dOffsetX;
//				dYOut = dY - dOffsetY;
//			}
//			break;
//
//		case CTFELLIPSE_Etrs89:
//			{
//			// (ELLIPSE_BESSEL)
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
//				modko_B (dYT, dXT, &dOffsetY, &dOffsetX);
//				dXOut -= dOffsetX;
//				dYOut -= dOffsetY;
//			}
//			break;
//		}
//
//	// in geodätische Koordinaten umsetzen
//		gaugeo (HA, HB, iStrBreite, iMeridian, dYOut, dXOut, KS, pdYOut, pdXOut);
//	}
//}


/////////////////////////////////////////////////////////////////////////////
// CGKBesselCoordTrans
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

void CGKBesselCoordTrans::InitVars (ITRiASProperties *pIProps)
{
// voreinstellen auf Bessel, Gauß/Krüger 6(12)
// (ELLIPSE_BESSEL)
//	HA = HA_BESSEL;
//	HB = HB_BESSEL;
long lMode = GetProperty (pIProps, g_cbShowGKCoords, 1L , LOCALE_ENGLISH);

	m_rgNativeDatum = TRIASCSGEODETICDATUM(GetProperty (pIProps, g_cbCoordDHDNType, 
		long(tcsGD_DeutscheHauptdreiecksnetz)));	// Standard ist 40/83

	if (!IsDHDNDerived(m_rgNativeDatum))
		m_rgNativeDatum = tcsGD_DeutscheHauptdreiecksnetzRd83DHDN;

	KS = KS_BESSEL;
	m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Bessel;
	m_rgEllipseNative = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Bessel;
	m_iMeridian = DEF_MERIDIAN_BESSEL;			// Meridian für GK
	m_iStrBreite = DEF_STRBREITE_BESSEL;		// Streifenbreite für GK

	switch (lMode) {	// JG990126 
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
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;

	case (2 | 0x04):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;

	case (1 | 0x08):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_SelectMeridian;
		if (m_fAllowChangeEllipse)
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Etrs89;
		break;

	case (2 | 0x08):
		m_CTFType = CTF_TransMercator;
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Etrs89;
		break;

	case 0:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		break;

	case 0x04:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Krassovsky;
		break;

	case 0x08:
		m_CTFType = CTF_Geodetical;	
		m_CTFMode = CTFMODE_AutoMeridian;
		if (m_fAllowChangeEllipse) 
			m_rgChangeEllipse = (CCoordTrans::COORDTRANSELLIPSE)CTFELLIPSE_Etrs89;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransformInit

/////////////////////////////////////////////////////////////////////////////
// ICoordTransform
// Properties
STDMETHODIMP CGKBesselCoordTrans::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CHECKPOINTER(pVal);

CString	strDesc, text;
char cbStrBreite[16];
char cbMeridian[16];

	if (CTF_Geodetical == m_CTFType) {
	// 'Geodätische Koordinaten - '
		VERIFY (strDesc.LoadString (IDS_DESCRIPTION));
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

CString CGKBesselCoordTrans::GetEllipseStrings()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CString str;
CString strT;

	VERIFY(strT.LoadString (IDS_BESSEL_ELLIPSE));
	str = strT;
	VERIFY(strT.LoadString (IDS_KRASSOVSKY_ELLIPSE));
	str += '\n';
	str += strT;
	VERIFY(strT.LoadString (IDS_ETRS89_ELLIPSE));
	str += '\n';
	str += strT;
	return str;
}

// JG990125
CString CGKBesselCoordTrans::GetCoordTypeString(
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

CString CGKBesselCoordTrans::GetInternalCoordTypeString()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CString str;

	VERIFY(str.LoadString(IDS_INTERNALKOORDS_DLG));
	return str;
}

TRIASCSGEODETICDATUM CGKBesselCoordTrans::GetGeodDatum(int rgEllipse,
	bool fNativeEllipe)
{
TRIASCSGEODETICDATUM rgDatum = tcsGD_Undefined;

	switch (rgEllipse) {
	case CTFELLIPSE_Krassovsky:
		rgDatum = tcsGD_Pulkovo1942;
		break;

	case CTFELLIPSE_Bessel:
		if (fNativeEllipe)	// nach außen ist's immer das neue
			rgDatum = m_rgNativeDatum;
		else
			rgDatum = tcsGD_DeutscheHauptdreiecksnetz;
		break;

	case CTFELLIPSE_Etrs89:
		rgDatum = tcsGD_EuropeanTerrestrialReferenceSystem89;		
		break;
	}

	_ASSERTE(tcsGD_Undefined != rgDatum);
	return rgDatum;
}

double CGKBesselCoordTrans::GetScaleFactor(int rgEllipse)
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
