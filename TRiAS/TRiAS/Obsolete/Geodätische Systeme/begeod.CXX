// Module enthaelt die Exportierten Routinen einer Koordinatentransformation
// File: BEGEOD.CXX

#include "begeodp.hxx"

#include "begeod.h"
//#include "begeodr.h"

#include <dblpair.hxx>
#include <ctype.h>
#if !defined(WIN32)
#include <tchar.h>
#endif

#include "ctfgeogk.h"
#include "numeditx.hxx"
#include "coordpar.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, int iPrec, double);

extern "C" char g_pDLLName[260];

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die MittelMeridian berechnen 
bool GetMeridianGeod (double dX, int &riMeridian);
bool GetMeridianGK (double dX, int &riMeridian);

// Schnittstellenfunktionen für Koordinatentransformationen -------------------
UINT __DexCmd = 0;
UINT __DexNotify = 0;
HWND __hWndM = NULL;

///////////////////////////////////////////////////////////////////////////////
// Ellipsoid-Halbachsen des internen Koordinatensystemes
double HA = 0.0, HB = 0.0, KS = 1.0;

COORDTRANSFORMTYPE g_CTFType = CTF_Native;				// Geod-Koordinaten anzeigen
COORDTRANSFORMMODE g_CTFMode = CTFMODE_AutoMeridian;	// wenn GK, dann Meridian automatiosch auswählen

int g_iMeridian = 12;			// Meridian für GK
int g_iStrBreite = 3;			// Streifenbreite für GK
int g_iPrec = 0;				// Darstellungsgenauigkeit

bool g_fInitialized = false;	// CTF wurde ordnungsgemäß geladen

///////////////////////////////////////////////////////////////////////////////
// Das folgende nur eingeschränktem Kundenkreis zugänglich machen
// Der Ellipsoidübergang wird mit RegEntry
//		HKCU\Software\uve\TRiAS\Config\AllowExtendedCoords:REG_DWORD:ALLOW_COOKIE
// bzw. SysAdminMode erlaubt.
//
#define ALLOW_COOKIE	DWORD(0x0023484b)
bool g_fAllowChangeEllipse = false;							// EllipsoidWechsel erlauben
COORDTRANSELLIPSE g_rgChangeEllipse = CTFELLIPSE_Unknown;	// Ellipsoid der externen Koordinaten
COORDTRANSELLIPSE g_rgEllipseNative = CTFELLIPSE_Unknown;	// Ellipsoid der internen Koordinaten

///////////////////////////////////////////////////////////////////////////////
// EllipsoidÜbergänge für GK-Koordinaten

///////////////////////////////////////////////////////////////////////////////
// Rechnet Koords (geod!) des 'native' Ellipsoids in GK Koordinaten des jeweils 
// anderen Ellipsoids um
void ConvertEllipse (
	int iStrBreite, int iMeridian, long double dYGeod, long double dXGeod,
	long double *pdYOut, long double *pdXOut)
{
	TX_ASSERT(NULL != pdXOut);
	TX_ASSERT(NULL != pdYOut);

	if (g_rgChangeEllipse == g_rgEllipseNative) {
	// kein Ellipsoid-Übergang notwendig
		geogau (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, pdYOut, pdXOut);
	} else {
	long double dX, dY;
	long double dXOffset, dYOffset;

	// in GK Koordinaten umrechnen
		geogau (HA, HB, iStrBreite, iMeridian, dYGeod, dXGeod, KS, &dY, &dX);

		switch (g_rgChangeEllipse) {
		case CTFELLIPSE_Bessel:
			{
#if defined(ELLIPSE_BESSEL)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Bessel == g_rgChangeEllipse);	// snh
#elif defined(ELLIPSE_KRASSOVSKI)
			// Übergang KrassovskyGK-->BesselGK
				TX_ASSERT(g_fAllowChangeEllipse);

			long double dXOut, dYOut;

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dY, dX, KS_BESSEL, &dYOut, &dXOut);
				modko_B (dYOut, dXOut, &dYOffset, &dXOffset);
				*pdXOut = dX - dXOffset;
				*pdYOut = dY - dYOffset;
#elif defined(ELLIPSE_ETRS89)
			// Übergang Etrs89UTM-->BesselGK
				TX_ASSERT(g_fAllowChangeEllipse);

			// zuerst Etrs89Geod-->KrassovskyGeod
			long double dXOut, dYOut;

				Grs80Krass (dYGeod, dXGeod, &dYOut, &dXOut);
				geogau (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_KRASSOVSKY, &dYOut, &dXOut);

			// dann KrassovskyGK-->BesselGK
			long double dXT, dYT;

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_BESSEL, &dYT, &dXT);
				modko_B (dYT, dXT, &dYOffset, &dXOffset);
				*pdXOut = dXOut - dXOffset;
				*pdYOut = dYOut - dYOffset;
#endif //ELLIPSES
			}
			break;

		case CTFELLIPSE_Krassovsky:
			{
#if defined(ELLIPSE_BESSEL)
			// Übergang BesselGK-->KrassovskyGK
				TX_ASSERT(g_fAllowChangeEllipse);

			// Ellipsoidparameter müssen stimmen, da eine hin/zurück-
			// Konvertierung eingespart worden ist
				TX_ASSERT(HA == HA_BESSEL);
				TX_ASSERT(HB == HB_BESSEL);
				TX_ASSERT(KS == KS_BESSEL);

				modko_B (dYGeod, dXGeod, &dYOffset, &dXOffset);
				*pdXOut = dX + dXOffset;
				*pdYOut = dY + dYOffset;
#elif defined(ELLIPSE_KRASSOVSKI)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Krassovsky == g_rgChangeEllipse);	// snh
#elif defined(ELLIPSE_ETRS89)
			// Übergang Etrs89UTM-->KrassovskyGK
				TX_ASSERT(g_fAllowChangeEllipse);

			long double dXOut, dYOut;

				Grs80Krass (dYGeod, dXGeod, &dYOut, &dXOut);
				geogau (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_KRASSOVSKY, pdYOut, pdXOut);
#endif //ELLIPSES
			}
			break;

		case CTFELLIPSE_Etrs89:
			{
#if defined(ELLIPSE_BESSEL)
			// Übergang BesselGK-->Etrs89UTM
				TX_ASSERT(g_fAllowChangeEllipse);

			// zuerst BesselGK-->KrassovskyGK
			long double dXOut, dYOut;
			long double dOffsetX, dOffsetY;

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dY, dX, KS_BESSEL, &dYOut, &dXOut);
				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
				dXOut = dX + dOffsetX;
				dYOut = dY + dOffsetY;

			// dann KrassovskyGK-->Etrs89UTM
				gaugeo (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_KRASSOVSKY, &dYOut, &dXOut);
				KrassGrs80 (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_ETRS89, pdYOut, pdXOut);
#elif defined(ELLIPSE_KRASSOVSKI)
			// Übergang KrassovskyGK-->Etrs89UTM
				TX_ASSERT(g_fAllowChangeEllipse);

			long double dXOut, dYOut;

				gaugeo (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dY, dX, KS_KRASSOVSKY, &dYOut, &dXOut);
				KrassGrs80 (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_ETRS89, pdYOut, pdXOut);
#elif defined(ELLIPSE_ETRS89)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Etrs89 == g_rgChangeEllipse);	// snh
#endif //ELLIPSES
			}
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Rechnet GK des jeweils anderen Ellipsoids in 'native' Koordinaten (geod) um
void InvConvertEllipse (
	int iStrBreite, int iMeridian, long double dY, long double dX,
	long double *pdYOut, long double *pdXOut)
{
	TX_ASSERT(NULL != pdXOut);
	TX_ASSERT(NULL != pdYOut);

	if (g_rgEllipseNative == g_rgChangeEllipse) {
	// kein Ellipsoid-Übergang notwendig
		gaugeo (HA, HB, iStrBreite, iMeridian, dY, dX, KS, pdYOut, pdXOut);
	} else {
	long double dXOut, dYOut;
	long double dOffsetX, dOffsetY;

		switch (g_rgChangeEllipse) {	// ZielEllipse
		case CTFELLIPSE_Bessel:
			{
#if defined(ELLIPSE_BESSEL)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Bessel == g_rgChangeEllipse);	// snh
#elif defined(ELLIPSE_KRASSOVSKI)
			// Übergang BesselGK-->KrassovskyGK
				TX_ASSERT(g_fAllowChangeEllipse);

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dY, dX, KS_BESSEL, &dYOut, &dXOut);
				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
				dXOut = dX + dOffsetX;
				dYOut = dY + dOffsetY;
#elif defined(ELLIPSE_ETRS89)
			// Übergang BesselGK-->Etrs89UTM
				TX_ASSERT(g_fAllowChangeEllipse);

			// zuerst BesselGK-->KrassovskyGK
				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dY, dX, KS_BESSEL, &dYOut, &dXOut);
				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
				dX += dOffsetX;
				dY += dOffsetY;

			// dann KrassovskyGK-->Etrs89UTM
				gaugeo (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dY, dX, KS_KRASSOVSKY, &dYOut, &dXOut);
				KrassGrs80 (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_ETRS89, &dYOut, &dXOut);
#endif //ELLIPSES
			}
			break;

		case CTFELLIPSE_Krassovsky:
			{
#if defined(ELLIPSE_BESSEL)
			// Übergang KrassovskyGK-->BesselGK
				TX_ASSERT(g_fAllowChangeEllipse);

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dY, dX, KS_BESSEL, &dYOut, &dXOut);
				modko_B (dYOut, dXOut, &dOffsetY, &dOffsetX);
				dXOut = dX - dOffsetX;
				dYOut = dY - dOffsetY;
#elif defined(ELLIPSE_KRASSOVSKI)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Krassovsky == g_rgChangeEllipse);	// snh
#elif defined(ELLIPSE_ETRS89)
			// Übergang KrassovskyGK-->Etrs89UTM
				TX_ASSERT(g_fAllowChangeEllipse);
				gaugeo (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dY, dX, KS_KRASSOVSKY, &dYOut, &dXOut);
				KrassGrs80 (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_ETRS89, &dYOut, &dXOut);
#endif //ELLIPSES
			}
			break;

		case CTFELLIPSE_Etrs89:
			{
#if defined(ELLIPSE_BESSEL)
			// Übergang Etrs89UTM-->BesselGK
				TX_ASSERT(g_fAllowChangeEllipse);

			// zuerst Etrs89UTM-->KrassovskyGK
				gaugeo (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dY, dX, KS_ETRS89, &dYOut, &dXOut);
				Grs80Krass (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_KRASSOVSKY, &dYOut, &dXOut);

			// dann KrassovskyGK-->BesselGK
			long double dXT, dYT;

				gaugeo (HA_BESSEL, HB_BESSEL, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_BESSEL, &dYT, &dXT);
				modko_B (dYT, dXT, &dOffsetY, &dOffsetX);
				dXOut -= dOffsetX;
				dYOut -= dOffsetY;
#elif defined(ELLIPSE_KRASSOVSKI)
			// Übergang Etrs89UTM-->KrassovskyGK
				TX_ASSERT(g_fAllowChangeEllipse);

				gaugeo (HA_ETRS89, HB_ETRS89, iStrBreite, iMeridian, 
						dY, dX, KS_ETRS89, &dYOut, &dXOut);
				Grs80Krass (dYOut, dXOut, &dYOut, &dXOut);
				geogau (HA_KRASSOVSKY, HB_KRASSOVSKY, iStrBreite, iMeridian, 
						dYOut, dXOut, KS_KRASSOVSKY, &dYOut, &dXOut);
#elif defined(ELLIPSE_ETRS89)
			// kein Übergang
				TX_ASSERT(CTFELLIPSE_Etrs89 == g_rgChangeEllipse);	// snh
#endif //ELLIPSES
			}
			break;
		}

	// in geodätische Koordinaten umsetzen
		gaugeo (HA, HB, iStrBreite, iMeridian, dYOut, dXOut, KS, pdYOut, pdXOut);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Hier gehts los
bool FAR PASCAL EXPORTCTF CoordTransLoad (HWND hWnd) 
{
// voreinstellen auf Bessel, Gauß/Krüger 6(12)
#if defined(ELLIPSE_BESSEL)
	HA = HA_BESSEL;
	HB = HB_BESSEL;
	KS = KS_BESSEL;
	g_rgChangeEllipse = CTFELLIPSE_Bessel;
	g_rgEllipseNative = CTFELLIPSE_Bessel;
	g_iMeridian = DEF_MERIDIAN_BESSEL;			// Meridian für GK
	g_iStrBreite = DEF_STRBREITE_BESSEL;		// Streifenbreite für GK
#elif defined(ELLIPSE_KRASSOVSKI)
	HA = HA_KRASSOVSKY;
	HB = HB_KRASSOVSKY;
	KS = KS_KRASSOVSKY;
	g_rgChangeEllipse = CTFELLIPSE_Krassovsky;
	g_rgEllipseNative = CTFELLIPSE_Krassovsky;
	g_iMeridian = DEF_MERIDIAN_KRASSOVSKY;		// Meridian für GK
	g_iStrBreite = DEF_STRBREITE_KRASSOVSKY;	// Streifenbreite für GK
#elif defined(ELLIPSE_ETRS89)
	HA = HA_ETRS89;
	HB = HB_ETRS89;
	KS = KS_ETRS89;
	g_rgChangeEllipse = CTFELLIPSE_Etrs89;
	g_rgEllipseNative = CTFELLIPSE_Etrs89;
	g_iMeridian = DEF_MERIDIAN_ETRS89;			// Meridian für GK
	g_iStrBreite = DEF_STRBREITE_ETRS89;		// Streifenbreite für GK
#else
#error "No Ellipse defined!"
#endif

	g_fAllowChangeEllipse = false;

// bilden des ResourceFiles
ResourceFile RF (g_pDLLName);

// Registrieren der Message (für alle Fälle)
	__DexCmd = RegisterWindowMessage (ResString (ResID (IDS_DEXMESSAGE, &RF), 30));
	__DexNotify = RegisterWindowMessage (TEXT("TriasNotification"));
	__hWndM = hWnd;

	if (__DexCmd == 0 || 0 == __DexNotify || __hWndM == 0) 
		return false;

// Testen, ob Ellipsoidübergang erlaubt werden kann
	if (DEX_QueryMode() & QMSysAdmin) {
		g_fAllowChangeEllipse = true;
	} else {
	CRegKey regAllow;

		if (ERROR_SUCCESS == regAllow.Open(HKEY_CURRENT_USER, TEXT("Software")) && 
			ERROR_SUCCESS == regAllow.Open(regAllow, TEXT("uve")) &&
			ERROR_SUCCESS == regAllow.Open(regAllow, TEXT("TRiAS")) &&
			ERROR_SUCCESS == regAllow.Open(regAllow, TEXT("Config")))
		{
		DWORD dwData = 0L;

			if (ERROR_SUCCESS == regAllow.QueryValue (dwData, TEXT("AllowExtendedCoords")))
				g_fAllowChangeEllipse = (ALLOW_COOKIE == dwData) ? true : false;
		}
	}

// Parameter lesen
HeaderEntryX HE (ResString (ResID (IDS_SHOWGKCOORDS, &RF), 30));
long lMode = HE.EntryLong(0);

	switch (lMode) {
	case 1:
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_SelectMeridian;
		break;

	case 2:
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_AutoMeridian;
		break;

	case (1 | 0x04):
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_SelectMeridian;
		if (g_fAllowChangeEllipse) {
#if defined(ELLIPSE_BESSEL)
			g_rgChangeEllipse = CTFELLIPSE_Krassovsky;
#elif defined(ELLIPSE_KRASSOVSKI)
			g_rgChangeEllipse = CTFELLIPSE_Etrs89;
#elif defined(ELLIPSE_ETRS89)
			g_rgChangeEllipse = CTFELLIPSE_Bessel;
#endif
		}
		break;

	case (2 | 0x04):
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_AutoMeridian;
		if (g_fAllowChangeEllipse) {
#if defined(ELLIPSE_BESSEL)
			g_rgChangeEllipse = CTFELLIPSE_Krassovsky;
#elif defined(ELLIPSE_KRASSOVSKI)
			g_rgChangeEllipse = CTFELLIPSE_Etrs89;
#elif defined(ELLIPSE_ETRS89)
			g_rgChangeEllipse = CTFELLIPSE_Bessel;
#endif
		}
		break;

	case (1 | 0x08):
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_SelectMeridian;
		if (g_fAllowChangeEllipse) {
#if defined(ELLIPSE_BESSEL)
			g_rgChangeEllipse = CTFELLIPSE_Etrs89;
#elif defined(ELLIPSE_KRASSOVSKI)
			g_rgChangeEllipse = CTFELLIPSE_Bessel;
#elif defined(ELLIPSE_ETRS89)
			g_rgChangeEllipse = CTFELLIPSE_Krassovsky;
#endif
		}
		break;

	case (2 | 0x08):
		g_CTFType = CTF_TransMercator;
		g_CTFMode = CTFMODE_AutoMeridian;
		if (g_fAllowChangeEllipse) {
#if defined(ELLIPSE_BESSEL)
			g_rgChangeEllipse = CTFELLIPSE_Etrs89;
#elif defined(ELLIPSE_KRASSOVSKI)
			g_rgChangeEllipse = CTFELLIPSE_Bessel;
#elif defined(ELLIPSE_ETRS89)
			g_rgChangeEllipse = CTFELLIPSE_Krassovsky;
#endif
		}
		break;

	case 0:
	default:
		g_CTFType = CTF_Native;
		g_CTFMode = CTFMODE_AutoMeridian;
		break;
	}

	{	// NEU: immer konfigurierbar (#HK950823)
	HeaderEntryX heMeridian (ResString (ResID (IDS_COORDMERIDIAN, &RF), 30));
	HeaderEntryX heBreite (ResString (ResID (IDS_COORDSTRBREITE, &RF), 30));

		g_iStrBreite = (int)heBreite.EntryLong(g_iStrBreite);
		if (g_iStrBreite != 3 && g_iStrBreite != 6) 
		{
			g_iStrBreite = 3;
		}

		g_iMeridian = (int)heMeridian.EntryLong(g_iMeridian);
		if (3 == g_iStrBreite && (g_iMeridian / 3) * 3 != g_iMeridian)
		{
			g_iMeridian = 12;	// fehlerhafter Mittelmeridian
		}
		else if (6 == g_iStrBreite && 
			 ((g_iMeridian -3) / 6) * 6 != g_iMeridian -3)
		{
			g_iMeridian = 15;	// fehlerhafter Mittelmeridian
		}
	}
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFPRECISION, &RF), 17));

		g_iPrec = (int)HE.EntryLong(0);
	}

	g_fInitialized = true;

return true;
}

bool FAR PASCAL EXPORTCTF CoordTransUnLoad (void)
{
	g_fInitialized = false;
	return true;
}

bool FAR PASCAL EXPORTCTF CoordTransDescription (COORDTRANSDESC *pCTD)
{
ResourceFile RF (g_pDLLName);
string strDesc;

	if (CTF_Native == g_CTFType) {
		strDesc = ResString (ResID (IDS_DESCRIPTION, &RF), 120);
	} else {
		if (CTFMODE_AutoMeridian == g_CTFMode) {
			wsprintf (pCTD -> pDesc, 
				 ResString (ResID (IDS_DESCRIPTIONGKAUTO, &RF), 120), 
				 g_iStrBreite);
		} else {
			wsprintf (pCTD -> pDesc, 
				 ResString (ResID (IDS_DESCRIPTIONGK, &RF), 120), 
				 g_iMeridian, g_iStrBreite);
		}
		strDesc = pCTD -> pDesc;
	}

	if (g_rgEllipseNative != g_rgChangeEllipse) {
	UINT uiResID = 0L;

		switch (g_rgChangeEllipse) {
		case CTFELLIPSE_Bessel:
			uiResID = IDS_BESSEL_ELLIPSE;
			break;

		case CTFELLIPSE_Krassovsky:
			uiResID = IDS_KRASSOVSKY_ELLIPSE;
			break;

		case CTFELLIPSE_Etrs89:
			uiResID = IDS_ETRS89_ELLIPSE;
			break;
		}
		TX_ASSERT(0 != uiResID);
		strDesc += ResString (ResID (uiResID, &RF), 120);
	}

	strncpy (pCTD -> pDesc, strDesc.c_str(), pCTD -> iLen);
	pCTD -> pDesc[pCTD -> iLen-1] = '\0';

	return true;
}

bool FAR PASCAL EXPORTCTF CoordTransMode (COORDTRANSMODE *pCTM)
{
#if !defined(WIN32)
Window MWind (pCTM -> hWnd);
ResourceFile RF (g_pDLLName);
CCTFParams16 PDlg (&MWind, ResID (IDD_COORDDLG, &RF), 
		g_CTFType, g_CTFMode, g_iMeridian, g_iStrBreite);

	PDlg.Show (Centre);

return PDlg.Result();
#else
return true;
#endif // WIN32
}

///////////////////////////////////////////////////////////////////////////////
// Berechnnen des bildausschnittsabhängigen Isotropie-Koeffizienten 
// HilfsFunktionen ------------------------------------------------------------
inline long double Q (long double x) 
{
	return x * x; 
}

inline long double D (long double dX, long double dY) 
{ 
	return sqrtl (Q(dX) + Q(dY)); 
}

// Eingangskoordinaten LinksOben und RechtsUnten in Normalkoordinaten
double FAR PASCAL EXPORTCTF CoordTransAspectRatio (const DoublePair *pLO, 
						 const DoublePair *pRU)
{
// 1. Berechnen der mittleren Ausdehnungen des Rechteckes in geodätischen
//    Koordinaten
long double DeltaXGeod = pRU -> Width() - pLO -> Width();
long double DeltaYGeod = pLO -> Height() - pRU -> Height();

// 2. Berechnen der mittleren Ausdehnungen des Rechteckes in Gauß/Krüger
//    Koordinaten
// ACHTUNG: Es wird eine Konvertierung in Bessel: Gauß/Krüger 6(12) 
//          Koordinaten durchgeführt, da davon ausgegangen wird, daß die 
//          Koordinaten in unseren Breiten liegen.
// Gauß/Krüger Koordinaten
long double X1, Y1;	// links oben
long double X2, Y2;	// rechts unten
long double X3, Y3;	// links unten
long double X4, Y4;	// rechts oben

	geogau (HA, HB, g_iStrBreite, g_iMeridian, pLO -> Height(), pLO -> Width(), KS, &Y1, &X1);
	geogau (HA, HB, g_iStrBreite, g_iMeridian, pRU -> Height(), pRU -> Width(), KS, &Y2, &X2);
	geogau (HA, HB, g_iStrBreite, g_iMeridian, pRU -> Height(), pLO -> Width(), KS, &Y3, &X3);
	geogau (HA, HB, g_iStrBreite, g_iMeridian, pLO -> Height(), pRU -> Width(), KS, &Y4, &X4);

// mittlere Längen der Rechteck-Seiten in Gauß/Krüger Koordinaten
// links oben - rechts oben ./. links unten - rechts unten
long double DeltaXGK = (D(X1-X4, Y1-Y4) + D(X2-X3, Y2-Y3))/2;

// links oben - links unten ./.  rechts oben - rechts unten
long double DeltaYGK = (D(X1-X3, Y1-Y3) + D(X4-X2, Y4-Y2))/2;

	if (0 == DeltaYGK || 0 == DeltaXGeod) {
		TX_ASSERT(0 != DeltaYGK && 0 != DeltaXGeod);
		return 1.0;		// Fehler ! Division durch null
	}

// 3. Berechnen des Isotropiekoefizienten
	return fabs((double)((DeltaXGK * DeltaYGeod) / (DeltaXGeod * DeltaYGK)));
}

///////////////////////////////////////////////////////////////////////////////
// Umrechnung von Normalkoordinaten in Realkoordinaten
bool FAR PASCAL EXPORTCTF Transform (DoublePair *pDP, short iCnt)
{
	if (CTF_TransMercator == g_CTFType) {	// aus GKCoords konvertieren
	long double dXOut, dYOut;

		for (int i = 0; i < iCnt; i++, pDP++) {
		int iMeridian = g_iMeridian;

			if (!GetMeridianGeod (pDP -> X(), iMeridian))
				return NULL;

			ConvertEllipse (g_iStrBreite, iMeridian, pDP -> Y(), pDP -> X(), 
							&dYOut, &dXOut);

			pDP -> X() = double(dXOut);
			pDP -> Y() = double(dYOut);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Umrechnung von Realkoordinaten in Normalkoordinaten
bool FAR PASCAL EXPORTCTF InvTransform (DoublePair *pDP, short iCnt)
{
	if (CTF_TransMercator == g_CTFType) {	// aus GKCoords konvertieren
	long double dXOut, dYOut;
		
		for (int i = 0; i < iCnt; i++, pDP++) {
		int iMeridian = g_iMeridian;

			if (!GetMeridianGK (pDP -> X(), iMeridian))
				return false;

		// evtl. Ellipsoidübergang
			InvConvertEllipse (g_iStrBreite, iMeridian, 
				pDP -> Y(), pDP -> X(), &dYOut, &dXOut);

			pDP -> X() = double(dXOut);
			pDP -> Y() = double(dYOut);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnung des (karthesischen) Abstandes zweier gegebener Punkte
// Punkte sind in Normalkoordinaten gegeben
double FAR PASCAL EXPORTCTF CoordTransDistance (const DoublePair *pP1, 
					       const DoublePair *pP2)
{
// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
long double XMin, XMax, YMin, YMax;		// Gauß/Krüger Koordinaten
int iMeridian = g_iMeridian;

	if (!GetMeridianGeod (pP1 -> Width(), iMeridian))
		return false;
	
	geogau (HA, HB, g_iStrBreite, iMeridian, pP1 -> Height(), pP1 -> Width(), KS, &YMax, &XMin);
	geogau (HA, HB, g_iStrBreite, iMeridian, pP2 -> Height(), pP2 -> Width(), KS, &YMin, &XMax);

// Berechnung des Abstandes als karthesische Koordinaten
	return (double) D(XMax-XMin, YMax-YMin);
}

///////////////////////////////////////////////////////////////////////////////
// Berechnung des (Einzel-) Abstandes zweier gegebener Punkte
// Punkte sind in Normalkoordinaten gegeben
bool FAR PASCAL EXPORTCTF CoordTransDistanceEx (const DoublePair *pP1, 
	        const DoublePair *pP2, DoublePair *pDP)
{
// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
long double XMin, XMax, YMin, YMax;		// Gauß/Krüger Koordinaten
int iMeridian = g_iMeridian;

	if (!GetMeridianGeod (pP1 -> Width(), iMeridian))
		return false;
	
	geogau (HA, HB, g_iStrBreite, iMeridian, pP1 -> Height(), pP1 -> Width(), KS, &YMax, &XMin);
	geogau (HA, HB, g_iStrBreite, iMeridian, pP2 -> Height(), pP2 -> Width(), KS, &YMin, &XMax);

// Berechnung des Abstandes als karthesische Koordinaten
	pDP -> X() = (double)(XMax - XMin);
	pDP -> Y() = (double)(YMax - YMin);

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen eines Punktes, der  gegebenen Abstand von einem anderen Punkt hat
// Eingangspunkt ist in Normalkoordinaten gegeben
bool FAR PASCAL EXPORTCTF CoordTransRectangle (const DoublePair *pIn, const DoublePair *pDelta, DoublePair *pOut)
{
// 1. Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
long double XIn, YIn;		// Gauß/Krüger Koordinaten
int iMeridian = g_iMeridian;

	if (!GetMeridianGeod (pIn -> Width(), iMeridian))
		return false;

	geogau (HA, HB, g_iStrBreite, iMeridian, pIn -> Height(), pIn -> Width(), KS, &YIn, &XIn);

// 2. neuen Punkt berechnen
	XIn += pDelta -> Width();
	YIn += pDelta -> Height();

// 3. Koordinaten zurückkonvertieren
long double XOut, YOut;

	gaugeo (HA, HB, g_iStrBreite, iMeridian, double(YIn), double(XIn), KS, &YOut, &XOut);
	pOut -> X() = double(XOut);
	pOut -> Y() = double(YOut);

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren eines KoordinatenWertes in die entsprechende Darstellungsform 
char *FAR PASCAL EXPORTCTF CoordTransToString (double Value, bool isX,
					       char *pBuffer, short iLen)
{
short sign = Value < 0;

	Value = fabs(Value);

short lGrad = (short)(Value/3600.0);
short lMin = (short)(Value/60.0 - (double)lGrad * 60.0);
double dSek = Value - (double)lGrad * 3600.0 - (double)lMin * 60.0;

	if (dSek >= 60.0) {
		dSek -= 60.0;
		lMin++;
	}
	if (lMin >= 60) {
		lMin -= 60;
		lGrad++;
	}

char cbSek[32];
char cbTmp[_MAX_PATH];
char cbFormat[32];

#if defined(PRECISIONFORNATIVE)
	if (0 == g_iPrec)
		strcpy (cbFormat, "%02ld");
	else
		wsprintf (cbFormat, "%%02ld.%%0%dlu" /*"%%%02d.%df"*/, g_iPrec);
#else
	strcpy (cbFormat, "%02ld");
#endif // PRECISIONFORNATIVE

	DtoACTF (cbSek, cbFormat, g_iPrec, dSek);
	wsprintf (cbTmp, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, 
			isX ? (sign ? "wL" : "öL") : (sign ? "sB" : "nB"));

	if (pBuffer) {
		strncpy (pBuffer, cbTmp, iLen -1);
		pBuffer[iLen-1] = '\0';
	}
	return pBuffer;
}

static char *CoordTransToStringGK (double Value, BOOL, char *pBuffer, short)
{
char pFormat[20];

	if (0 == g_iPrec)
		strcpy (pFormat, "%ld");
	else
		wsprintf (pFormat, "%%ld.%%0%dlu" /*"%%%d.%df"*/, g_iPrec);
	return DtoACTF (pBuffer, pFormat, g_iPrec, Value);
}


char *FAR PASCAL EXPORTCTF CoordTransToStringEx (
		char *pBuffer, short iLen, bool isX, const DoublePair *pDP)
{
//long double dX, dY;

	if (CTF_TransMercator == g_CTFType) {
	// gewünschte Koordinate umsetzen
		if (isX) return CoordTransToStringGK (pDP -> Width(), true, pBuffer, iLen);
		else return CoordTransToStringGK (pDP -> Height(), false, pBuffer, iLen);
	} else {
	// gewünschte Koordinate umsetzen
		if (isX) return CoordTransToString (pDP -> Width(), true, pBuffer, iLen);
		else return CoordTransToString (pDP -> Height(), false, pBuffer, iLen);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren eines in der Darstellungsform gegeben Koordinatenwertes
static bool SkipWhites (char *& pS) 
{
	while (*pS) {
		if (isascii(*pS) && isdigit(*pS)) 
			break;
		pS++;
	}

return *pS != '\0';
}

static bool AtoI (char *& pS, short *iR)
{
	*iR = 0;
	while (*pS && isascii(*pS) && isdigit(*pS))
		*iR = (*iR*10) + *pS++ - '0';

return *pS != '\0';
}

double FAR PASCAL EXPORTCTF CoordTransToValue (char *pBuffer)
{
char *cptr = pBuffer;
short lGrad = 0;
short lMin = 0;

	SkipWhites (cptr);
	if (!AtoI (cptr, &lGrad) || !SkipWhites (cptr))
		return lGrad * 3600.0;
	if (!AtoI (cptr, &lMin) || !SkipWhites (cptr))
		return lGrad * 3600.0 + lMin * 60.0;

double dSek = atof (cptr);	//	AtoI (cptr, &lSek);

return lGrad * 3600.0 + lMin * 60.0 + dSek;
}

bool FAR PASCAL EXPORTCTF CoordTransToValueEx (
		DoublePair *pOut, const char *pBuffX, const char *pBuffY)
{
	if (CTF_TransMercator == g_CTFType) {
		pOut -> X() = atof ((char *)pBuffX);
		pOut -> Y() = atof ((char *)pBuffY);
	} else {
	// Strings sind bereits geodätische Koordinaten
		pOut -> X() = CoordTransToValue ((char *)pBuffX);
		pOut -> Y() = CoordTransToValue ((char *)pBuffY);
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sind Realkoordinaten metrische oder eigene Koordinaten ?
bool FAR PASCAL EXPORTCTF CoordTransIsMetric (void)
{
	return (g_CTFType == CTF_Native) ? false : true;
}

///////////////////////////////////////////////////////////////////////////////
// KonvertierungsRoutinen von/in metrische (Realkoordinaten) Koordinaten 
bool FAR PASCAL EXPORTCTF CoordTransNative (DoublePair *pP, short iNum)
{
int iMeridian = g_iMeridian;;

	if (iNum > 0) {
		if (!GetMeridianGK (pP[0].Width(), iMeridian))
			return false;
	}

long double dXOut, dYOut;

	for (int i = 0; i < iNum; i++) {
	// evtl. Ellipsoidübergang
		InvConvertEllipse (g_iStrBreite, iMeridian, 
			pP[i].Height(), pP[i].Width(), &dYOut, &dXOut);

		pP[i].X() = double(dXOut);
		pP[i].Y() = double(dYOut);
	}

return true;
}

bool FAR PASCAL EXPORTCTF CoordTransMetric (DoublePair *pP, short iNum)
{
// Konvertierung der Koordinaten in Bessel: Gauß/Krüger 3(12)
int iMeridian = g_iMeridian;

	if (iNum > 0) {
		if (!GetMeridianGeod (pP[0].Width(), iMeridian))
			return false;
	}

long double dXOut, dYOut;

	for (int i = 0; i < iNum; i++) {
		ConvertEllipse (g_iStrBreite, iMeridian, pP[i].Height(), pP[i].Width(), 
						&dYOut, &dXOut);

		pP[i].X() = double(dXOut);
		pP[i].Y() = double(dYOut);
	}

return true;
}

#if defined(WIN32)

typedef struct tagTRANSFORMDATA {
	DWORD dwSize;
	int m_iMeridian;
} TRANSFORMDATA;

bool PASCAL CoordTransNativeParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

int iMeridian = 0;

	if (!GetMeridianGK (pP -> Width(), iMeridian))
		return false;

TRANSFORMDATA *pTD = (TRANSFORMDATA *)CoTaskMemAlloc (sizeof(TRANSFORMDATA));

	if (NULL == pTD) return false;
	INITSTRUCT(*pTD, TRANSFORMDATA);
	pTD -> m_iMeridian = iMeridian;

	*ppData = pTD;

return true;
}

bool PASCAL CoordTransMetricParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

int iMeridian = 0;

	if (!GetMeridianGeod (pP -> Width(), iMeridian))
		return false;

TRANSFORMDATA *pTD = (TRANSFORMDATA *)CoTaskMemAlloc (sizeof(TRANSFORMDATA));

	if (NULL == pTD) return false;
	INITSTRUCT(*pTD, TRANSFORMDATA);
	pTD -> m_iMeridian = iMeridian;

	*ppData = pTD;

return true;
}

// KonvertierungsRoutinen von/in metrische RealKoordinaten (parametrisierbar)
bool PASCAL CoordTransNativeEx (DoublePair *pP, short iNum, LPVOID pData)
{
	if (NULL == pData)
		return CoordTransNative (pP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double dXOut, dYOut;

	for (short i = 0; i < iNum; i++) {
	// evtl. Ellipsoidübergang
		InvConvertEllipse (g_iStrBreite, ((TRANSFORMDATA *)pData) -> m_iMeridian, 
				pP[i].Height(), pP[i].Width(), &dYOut, &dXOut);
		
		pP[i].X() = double(dXOut);
		pP[i].Y() = double(dYOut);
	}

return true;
}

bool PASCAL CoordTransMetricEx (DoublePair *pP, short iNum, LPVOID pData)
{
	if (NULL == pData)
		return CoordTransMetric (pP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double dXOut, dYOut;

	for (short i = 0; i < iNum; i++) {
		ConvertEllipse (g_iStrBreite, ((TRANSFORMDATA *)pData) -> m_iMeridian, 
				pP[i].Height(), pP[i].Width(), &dYOut, &dXOut);

		pP[i].X() = double(dXOut);
		pP[i].Y() = double(dYOut);
	}

return true;
}

bool PASCAL TransformEx (DoublePair *pDP, int iNum, LPVOID pData)
{
	if (CTF_TransMercator == g_CTFType) {	// aus GKCoords konvertieren
		if (NULL == pData)
			return Transform (pDP, iNum);

		TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

	long double dXOut, dYOut;

		for (int i = 0; i < iNum; i++, pDP++) {
			ConvertEllipse (g_iStrBreite, ((TRANSFORMDATA *)pData) -> m_iMeridian, 
					pDP -> Y(), pDP -> X(), &dYOut, &dXOut);

			pDP -> X() = double(dXOut);
			pDP -> Y() = double(dYOut);
		}
	}

return true;
}

bool PASCAL InvTransformEx (DoublePair *pDP, int iNum, LPVOID pData)
{
	if (CTF_TransMercator == g_CTFType) {	// aus GKCoords konvertieren
		if (NULL == pData)
			return InvTransform (pDP, iNum);

		TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

	// in geodätische Koordinaten umsetzen
	long double dXOut, dYOut;

		for (int i = 0; i < iNum; i++, pDP++) {
		// evtl. Ellipsoidübergang
			InvConvertEllipse (g_iStrBreite, ((TRANSFORMDATA *)pData) -> m_iMeridian, 
					pDP->Y(), pDP->X(), &dYOut, &dXOut);
			
			pDP -> X() = double(dXOut);
			pDP -> Y() = double(dYOut);
		}
	}
	return true;
}

#endif // WIN32

// Funktionen, die MittelMeridian berechnen -----------------------------------
// Berechnet aus geod. Koordinate den ZielMeridian
bool GetMeridianGeod (double dX, int &riMeridian)
{
	if (CTFMODE_AutoMeridian == g_CTFMode) {
		if (3 == g_iStrBreite)
			riMeridian = (int)((dX/3600.0 + 1.5)/3) * 3;
		else
			riMeridian = (int)((dX/3600.0)/6) * 6 + 3;
	} else 
		riMeridian = g_iMeridian;		// vorgegebenen verwenden

return true;
}

// berechnet aus GK den Mittelmeridian ----------------------------------------
bool GetMeridianGK (double dX, int &riMeridian)
{
	if (CTFMODE_AutoMeridian == g_CTFMode) {
		if (dX < 0 || dX > 7000000.0) 
			return false;

		if (3 == g_iStrBreite)
			riMeridian = (int)(dX/1000000.0) * 3;
		else
			riMeridian = (int)(dX/1000000.0) * 6 - 3;
	} else 
		riMeridian = g_iMeridian;		// vorgegebenen verwenden

return true;
}

///////////////////////////////////////////////////////////////////////////////
