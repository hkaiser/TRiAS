// Module enthaelt die Exportierten Routinen einer Koordinatentransformation
// File: BESSELGK.CXX

#include "besslgkp.hxx"
#include "besslres.h"

#include "coordpar.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
extern "C" void FUNCTYPE PASCAL geogau (double, double, short, short, double, double, long double *, long double *);
extern "C" void FUNCTYPE PASCAL gaugeo (double, double, short, short, double, double, long double *, long double *);
extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, double);

bool GetMeridianGK (DoublePair *pDP, int &riMeridian);

extern "C" char g_pDLLName[260];
extern "C" extern HINSTANCE g_hInstance;

///////////////////////////////////////////////////////////////////////////////
// Schnittstellenfunktionen für Koordinatentransformationen -------------------

// Parameter der Koordinatentransformationen ----------------------------------
UINT __DexCmd = NULL;
HWND __hWndM = NULL;
UINT __DexNotify = NULL;

extern "C" COORDTRANSFORMMODE g_CTFMode;	// wenn GK, dann Meridian automatisch auswählen
extern "C" int g_iMeridian = 12;			// Meridian für GK
extern "C" int g_iStrBreite = 3;			// Streifenbreite für GK
extern "C" int g_iPrec = 0;					// Darstellungsgenauigkeit
extern "C" bool g_fInitialized = false;		// CTF wurde ordnungsgemäß geladen
extern "C" double g_dScale = 1.0;			// zusätzlicher Skalierungskoeffizient

extern "C" int g_iMeridianDB = 12;			// Meridian für GK in GeoDB
extern "C" int g_iStrBreiteDB = 3;			// Streifenbreite für GK in GeoDB

///////////////////////////////////////////////////////////////////////////////
double HA = 6377397.155;	// große Ellipsoid-Halbachse
double HB = 6356078.96325;	// kleine Ellipsoid-Halbachse

extern "C"
BOOL PASCAL EXPORTCTF CoordTransLoad (HWND hWnd) 
{
// voreinstellen auf entsprechenden Ellipsoid
#if defined(ELLIPSE_BESSEL)
	HA = 6377397.155;
	HB = 6356078.96325;
#elif defined(ELLIPSE_KRASSOVSKY)
	HA = 6378245.0;
	HB = 6356863.01877;
#else
#error "No Ellipsoid defined."
#endif // ELLIPSE_...

// bilden des ResourceFiles
ResourceFile RF (g_pDLLName);

// Registrieren der Message
	__DexCmd = RegisterWindowMessage (ResString (ResID (IDS_DEXMESSAGE, &RF), 30));
	__hWndM = hWnd;

	if (__DexCmd == 0 || __hWndM == 0) 
		return FALSE;

// Parameter lesen
HeaderEntryX HE (ResString (ResID (IDS_SHOWGKCOORDS, &RF), 30));
long lMode = HE.EntryLong(0);

	switch (lMode) {
	case 1:
		g_CTFMode = CTFMODE_SelectMeridian;
		break;

	case 0:
	default:
		g_CTFMode = CTFMODE_AutoMeridian;
		break;
	}

// Mittelmeridian und Streifenbreite der GeoDB aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFSTREIFEN, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) 
			g_iStrBreiteDB = (short)HE.EntryLong (3L);
		else
			g_iStrBreiteDB = 3;

	// PlausibilitätsTest
		if (g_iStrBreiteDB != 3 && g_iStrBreiteDB != 6)	
			g_iStrBreiteDB = 3;
	}
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFMERIDIAN, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) 
			g_iMeridianDB = (short)HE.EntryLong (12L);
		else
			g_iMeridianDB = 12;

	// PlausibilitätsTest
		if (g_iStrBreiteDB == 3 && (g_iMeridianDB / 3) * 3 != g_iMeridianDB)
			g_iMeridianDB = 12;		// fehlerhafter Mittelmeridian
		else if (g_iStrBreiteDB == 6 && ((g_iMeridianDB -3) / 6) * 6 != g_iMeridianDB -3)
			g_iMeridianDB = 15;		// fehlerhafter Mittelmeridian
	}

// Mittelmeridian und Streifenbreite der _Anzeige_ aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFSTREIFENVIEW, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) 
			g_iStrBreite = (short)HE.EntryLong (3L);
		else
			g_iStrBreite = g_iStrBreiteDB;

	// PlausibilitätsTest
		if (g_iStrBreite != 3 && g_iStrBreite != 6)	
			g_iStrBreite = g_iStrBreiteDB;
	}
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFMERIDIANVIEW, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) 
			g_iMeridian = (short)HE.EntryLong (12L);
		else
			g_iMeridian = g_iMeridianDB;

	// PlausibilitätsTest
		if (g_iStrBreite == 3 && (g_iMeridian / 3) * 3 != g_iMeridian)
			g_iMeridian = g_iMeridianDB;		// fehlerhafter Mittelmeridian
		else if (g_iStrBreite == 6 && ((g_iMeridian -3) / 6) * 6 != g_iMeridian -3)
			g_iMeridian = g_iMeridianDB;		// fehlerhafter Mittelmeridian
	}

// DarstellungsGenauigkeit aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFPRECISION, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) 
			g_iPrec = (short)HE.EntryLong (0);
		else
			g_iPrec = 0;
	}

// SkalierungsKoeffizienten aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFSCALING, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED)
			g_dScale = fabs(HE.EntryDouble (1.0));
		else
			g_dScale = 1.0;
	}
	if (g_dScale == 0.0) g_dScale = 1.0;

	g_fInitialized = true;

return TRUE;
}

extern "C"
BOOL PASCAL EXPORTCTF  CoordTransUnLoad (void)
{
	g_fInitialized = false;
	return TRUE;
}

// Liefern der Beschreibungsinformation für diese Koordinatentransformation ---
extern "C"
BOOL PASCAL EXPORTCTF  CoordTransDescription (COORDTRANSDESC *pCTD)
{
ResourceFile RF (g_pDLLName);

#if defined(ELLIPSE_BESSEL)
	if (CTFMODE_AutoMeridian == g_CTFMode) {
		wsprintf (pCTD -> pDesc, 
			 ResString (ResID (IDS_DESCRIPTIONBESSELAUTO, &RF), 120), 
			 g_iStrBreite);
	} else {
		wsprintf (pCTD -> pDesc, 
			 ResString (ResID (IDS_DESCRIPTIONBESSEL, &RF), 120), 
			 g_iMeridian, g_iStrBreite);
	}
#else if defined(ELLIPSE_KRASSOVSKY)
	if (CTFMODE_AutoMeridian == g_CTFMode) {
		wsprintf (pCTD -> pDesc, 
			 ResString (ResID (IDS_DESCRIPTIONKRASSOVSKYAUTO, &RF), 120), 
			 g_iStrBreite);
	} else {
		wsprintf (pCTD -> pDesc, 
			 ResString (ResID (IDS_DESCRIPTIONKRASSOVSKY, &RF), 120), 
			 g_iMeridian, g_iStrBreite);
	}
#endif 

return TRUE;
}

extern "C"
BOOL PASCAL EXPORTCTF  CoordTransMode (COORDTRANSMODE *)
{
	return TRUE;
}

// Liefern des KoordinatenVerhältnisses für ein in DB-Koordinaten gegebenes 
// Rechteck (BildAusschnitt)
extern "C"
double PASCAL EXPORTCTF CoordTransAspectRatio (
		const DoublePair *, const DoublePair *)
{
	return 1.0;
}

// Transformation der DB-Koordinaten in (Real-)Projektionskoordinaten ---------
extern "C"
BOOL PASCAL EXPORTCTF  Transform (DoublePair *pDP, short iNum)
{
long double b, l;
long double XOut, YOut;
int Lm;

	if (g_iStrBreiteDB != g_iStrBreite ||		// andere Streifenbreite
		CTFMODE_AutoMeridian == g_CTFMode ||	// automatische Berechnung des Meridians
		g_iMeridianDB != g_iMeridian)			// oder anderer Meridian
	{
		for (int i = 0; i < iNum; i++, pDP++) {

			gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pDP -> Y(), pDP -> X(), &b, &l);

			if (CTFMODE_AutoMeridian == g_CTFMode) {
				if (g_iStrBreite == 3)
					Lm = (short)((l/3600.0 + 1.5)/3) * 3;
				else
					Lm = ((short)((l/3600.0)/6) * 6) + 3;
			} else
				Lm = g_iMeridian;

			if (Lm != g_iMeridianDB) {
				geogau (HA, HB, g_iStrBreite, Lm, double(b), double(l), &YOut, &XOut);
				pDP -> X() = double(XOut)/g_dScale;
				pDP -> Y() = double(YOut)/g_dScale;
			} else {
				pDP -> X() /= g_dScale;
				pDP -> Y() /= g_dScale;
			}
		}
	} else {
		for (int i = 0; i < iNum; i++, pDP++) {
			pDP -> X() /= g_dScale;
			pDP -> Y() /= g_dScale;
		}
	}
				
return TRUE;
}

// Transfromation von (Real-)Projektionskoordinaten in DB-Koordinaten ---------
extern "C"
BOOL PASCAL EXPORTCTF InvTransform (DoublePair *pDP, short iNum)
{
long double b, l;
long double XOut, YOut;

	for (int i = 0; i < iNum; i++) {
	double &dX = pDP[i].X();
	double &dY = pDP[i].Y();

	// PlausibilitätsTest
		if (dY < -8000000.0 || dY > 8000000.0) return FALSE;
		if (dX < 0 || dX > 7000000.0) return FALSE;

	// eigentliche Konvertierung
		dX *= g_dScale;
		dY *= g_dScale;

	short Lm;
	
		if (CTFMODE_AutoMeridian == g_CTFMode) {
			if (g_iStrBreite == 3)
				Lm = (short)(dX/1000000.0) * 3;
			else
				Lm = ((short)(dX/1000000.0) * 6) - 3;
		} else
			Lm = g_iMeridian;

		if (g_iStrBreite != g_iStrBreiteDB || Lm != g_iMeridianDB) {
			gaugeo (HA, HB, g_iStrBreite, Lm, dY, dX, &b, &l);
			geogau (HA, HB, g_iStrBreiteDB, g_iMeridianDB, double(b), double(l), &YOut, &XOut);
			dX = double(XOut);
			dY = double(YOut);
		}
	}

return TRUE;                
}

// Berechnen des Abstandes zweier in DB-Koordinaten gegebenen Punkte ----------
extern "C"
double PASCAL EXPORTCTF  CoordTransDistance (const DoublePair *pP1, 
					   const DoublePair *pP2)
{
double DeltaX = (pP2 -> Width() - pP1 -> Width()) / g_dScale;
double DeltaY = (pP2 -> Height() - pP1 -> Height()) / g_dScale;

	return sqrt (DeltaX*DeltaX + DeltaY*DeltaY);
}

// Berechnen eines Punktes, der  gegebenen Abstand von einem anderen Punkt hat
extern "C"
BOOL PASCAL EXPORTCTF  CoordTransRectangle (const DoublePair *pIn,
					  const DoublePair *pDelta,
					  DoublePair *pOut)
{
	pOut -> Width() = pIn -> Width() + (pDelta -> Width() * g_dScale);
	pOut -> Height() = pIn -> Height() + (pDelta -> Height() * g_dScale);

return TRUE;
}

// Konvertieren eines KoordinatenWertes in die entsprechende Darstellungsform -
extern "C"
char * PASCAL EXPORTCTF  CoordTransToString (double Value, BOOL, char *pBuffer, short)
{
char pFormat[20];

	wsprintf (pFormat, "%%%d.%df", g_iPrec+8, g_iPrec);
	return DtoACTF (pBuffer, pFormat, Value);
}

// Konvertieren eines in der Darstellungsform gegeben Koordinatenwertes -------
extern "C"
double PASCAL EXPORTCTF  CoordTransToValue (char *pBuffer)
{
	return atof (pBuffer);
}

// Metrische/eigene Koordinaten -----------------------------------------------
extern "C"
BOOL PASCAL EXPORTCTF  CoordTransIsMetric (void)
{
	return TRUE;
}

// KonvertierungsRoutinen werden nicht benötigt, da alles bereits metrisch ist 
extern "C"
BOOL PASCAL EXPORTCTF  CoordTransNative (DoublePair *pDP, short iNum)
{
long double b, l;
long double XOut, YOut;

// Parameter am 1. Punkt berechnen
int Lm = 0;

	if (CTFMODE_AutoMeridian == g_CTFMode) {
		if (g_iStrBreite == 3)
			Lm = (int)(pDP[0].X()/1000000.0) * 3;
		else
			Lm = ((int)(pDP[0].X()/1000000.0) * 6) - 3;
	} else
		Lm = g_iMeridian;

bool fConvert = (g_iStrBreite != g_iStrBreiteDB || Lm != g_iMeridianDB) ? true : false;

	for (int i = 0; i < iNum; i++) {
	double &dX = pDP[i].X();
	double &dY = pDP[i].Y();

	// PlausibilitätsTest
		if (dY < -8000000.0 || dY > 8000000.0) return FALSE;
		if (dX < 0 || dX > 7000000.0) return FALSE;

	// eigentliche Konvertierung
		dX *= g_dScale;
		dY *= g_dScale;

		if (fConvert) {
			gaugeo (HA, HB, g_iStrBreite, Lm, dY, dX, &b, &l);
			geogau (HA, HB, g_iStrBreiteDB, g_iMeridianDB, double(b), double(l), &YOut, &XOut);
			dX = double(XOut);
			dY = double(YOut);
		}
	}

	return TRUE;
}

extern "C"
BOOL PASCAL EXPORTCTF  CoordTransMetric (DoublePair *pDP, short iNum)
{
long double b, l;
long double XOut, YOut;
int Lm;

// Parameter für 1. Punkt bestimmen
	gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pDP[0].Y(), pDP[0].X(), &b, &l);

	if (CTFMODE_AutoMeridian == g_CTFMode) {
		if (g_iStrBreite == 3)
			Lm = (short)((l/3600.0 + 1.5)/3) * 3;
		else
			Lm = ((short)((l/3600.0)/6) * 6) + 3;
	} else
		Lm = g_iMeridian;

// jetzt alle Koordinaten konvertieren
	if (g_iStrBreiteDB != g_iStrBreite ||		// andere Streifenbreite
		CTFMODE_AutoMeridian == g_CTFMode ||	// automatische Berechnung des Meridians
		g_iMeridianDB != Lm)					// oder anderer Meridian
	{
		for (int i = 0; i < iNum; i++, pDP++) {
			gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pDP -> Y(), pDP -> X(), &b, &l);
			geogau (HA, HB, g_iStrBreite, Lm, double(b), double(l), &YOut, &XOut);
			pDP -> X() = double(XOut)/g_dScale;
			pDP -> Y() = double(YOut)/g_dScale;
		}

	} else {
		for (int i = 0; i < iNum; i++, pDP++) {
			pDP -> X() /= g_dScale;
			pDP -> Y() /= g_dScale;
		}
	}
				
	return TRUE;
}

#if defined(WIN32)

typedef struct tagTRANSFORMDATA {
	DWORD dwSize;
	int m_iMeridian;
} TRANSFORMDATA;

extern "C"
bool PASCAL CoordTransNativeParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

	*ppData = NULL;

int iMeridian = 0;

	if (!GetMeridianGK (pP, iMeridian))
		return false;

TRANSFORMDATA *pTD = (TRANSFORMDATA *)CoTaskMemAlloc (sizeof(TRANSFORMDATA));

	if (NULL == pTD) 
		return false;
	
	INITSTRUCT(*pTD, TRANSFORMDATA);
	pTD -> m_iMeridian = iMeridian;

	*ppData = pTD;

return true;
}

extern "C"
bool PASCAL CoordTransMetricParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

	*ppData = NULL;

int iMeridian = 0;

	if (!GetMeridianGK (pP, iMeridian))
		return false;

TRANSFORMDATA *pTD = (TRANSFORMDATA *)CoTaskMemAlloc (sizeof(TRANSFORMDATA));

	if (NULL == pTD) 
		return false;
	INITSTRUCT(*pTD, TRANSFORMDATA);
	pTD -> m_iMeridian = iMeridian;

	*ppData = pTD;

return true;
}

// KonvertierungsRoutinen von/in metrische Koordinaten (parametrisierbar)
extern "C"
bool PASCAL CoordTransNativeEx (DoublePair *pDP, short iNum, LPVOID pData)
{
	if (NULL == pData)
		return CoordTransNative (pDP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double b, l;
long double XOut, YOut;
int Lm;

	if (CTFMODE_AutoMeridian == g_CTFMode) 
		Lm = ((TRANSFORMDATA *)pData) -> m_iMeridian;
	else
		Lm = g_iMeridian;

	if (g_iStrBreite != g_iStrBreiteDB || Lm != g_iMeridianDB) {
	// andere Streifenbreite oder anderer Meridian
		for (int i = 0; i < iNum; i++) {
		double &dX = pDP[i].X();
		double &dY = pDP[i].Y();

		// PlausibilitätsTest
			if (dY < -8000000.0 || dY > 8000000.0) return FALSE;
			if (dX < 0 || dX > 7000000.0) return FALSE;

		// eigentliche Konvertierung
			dX *= g_dScale;
			dY *= g_dScale;
	
			gaugeo (HA, HB, g_iStrBreite, Lm, dY, dX, &b, &l);
			geogau (HA, HB, g_iStrBreiteDB, g_iMeridianDB, double(b), double(l), &YOut, &XOut);
			dX = double(XOut);
			dY = double(YOut);
		}
	} else {
		for (int i = 0; i < iNum; i++) {
			pDP[i].X() *= g_dScale;
			pDP[i].Y() *= g_dScale;
		}
	}

	return TRUE;                
}

extern "C"
bool PASCAL CoordTransMetricEx (DoublePair *pP, short iNum, LPVOID pData)
{
	if (NULL == pData)
		return CoordTransMetric (pP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double b, l;
long double XOut, YOut;
int iMeridian = ((TRANSFORMDATA *)pData) -> m_iMeridian;

	if (CTFMODE_AutoMeridian != g_CTFMode) 
		iMeridian = g_iMeridian;

	if (g_iStrBreiteDB != g_iStrBreite ||		// andere Streifenbreite
		g_iMeridianDB != iMeridian)				// oder anderer Meridian
	{
		for (int i = 0; i < iNum; i++, pP++) {

			gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pP -> Y(), pP -> X(), &b, &l);
			geogau (HA, HB, g_iStrBreite, iMeridian, double(b), double(l), &YOut, &XOut);
			pP -> X() = double(XOut)/g_dScale;
			pP -> Y() = double(YOut)/g_dScale;
		}

	} else {
		for (int i = 0; i < iNum; i++, pP++) {
			pP -> X() /= g_dScale;
			pP -> Y() /= g_dScale;
		}
	}

	return true;
}

extern "C"
bool PASCAL TransformEx (DoublePair *pDP, int iNum, LPVOID pData)
{
	if (NULL == pData)
		return Transform (pDP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double b, l;
long double XOut, YOut;
int Lm;

	if (CTFMODE_AutoMeridian == g_CTFMode)
		Lm = ((TRANSFORMDATA *)pData) -> m_iMeridian;
	else
		Lm = g_iMeridian;

	if (g_iStrBreiteDB != g_iStrBreite || g_iMeridianDB != Lm) {
	// andere Streifenbreite oder anderer Meridian
		for (int i = 0; i < iNum; i++, pDP++) {
			gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pDP -> Y(), pDP -> X(), &b, &l);
			geogau (HA, HB, g_iStrBreite, Lm, double(b), double(l), &YOut, &XOut);
			pDP -> X() = double(XOut)/g_dScale;
			pDP -> Y() = double(YOut)/g_dScale;
		}
	} else {
	// keine Umrechnung notwendig
		for (int i = 0; i < iNum; i++, pDP++) {
			pDP -> X() /= g_dScale;
			pDP -> Y() /= g_dScale;
		}
	}

return TRUE;
}

// Transfromation von (Real-)Projektionskoordinaten in DB-Koordinaten ---------
extern "C"
BOOL PASCAL InvTransformEx (DoublePair *pDP, int iNum, LPVOID pData)
{
	if (NULL == pData)
		return InvTransform (pDP, iNum);

	TX_ASSERT(sizeof(TRANSFORMDATA) == ((TRANSFORMDATA *)pData) -> dwSize);

long double b, l;
long double XOut, YOut;
int Lm;

	if (CTFMODE_AutoMeridian == g_CTFMode) 
		Lm = ((TRANSFORMDATA *)pData) -> m_iMeridian;
	else
		Lm = g_iMeridian;

	if (g_iStrBreite != g_iStrBreiteDB || Lm != g_iMeridianDB) {
	// andere Streifenbreite oder anderer Meridian
		for (int i = 0; i < iNum; i++) {
		double &dX = pDP[i].X();
		double &dY = pDP[i].Y();

		// PlausibilitätsTest
			if (dY < -8000000.0 || dY > 8000000.0) return FALSE;
			if (dX < 0 || dX > 7000000.0) return FALSE;

		// eigentliche Konvertierung
			dX *= g_dScale;
			dY *= g_dScale;
			gaugeo (HA, HB, g_iStrBreite, Lm, dY, dX, &b, &l);
			geogau (HA, HB, g_iStrBreiteDB, g_iMeridianDB, double(b), double(l), &YOut, &XOut);
			dX = double(XOut);
			dY = double(YOut);
		}
	} else {
		for (int i = 0; i < iNum; i++) {
			pDP[i].X() *= g_dScale;
			pDP[i].Y() *= g_dScale;
		}
	}

return TRUE;                
}

#endif // WIN32

// berechnet aus GK den Mittelmeridian ----------------------------------------
bool GetMeridianGK (DoublePair *pDP, int &riMeridian)
{
	if (CTFMODE_AutoMeridian == g_CTFMode) {
	double dX = pDP -> X();

		if (dX < 0 || dX > 7000000.0) 
			return false;

		if (3 == g_iStrBreite)
			riMeridian = (int)(dX/1000000.0) * 3;
		else
			riMeridian = (int)(dX/1000000.0) * 6 - 3;
	} else 
		riMeridian = g_iMeridian;		// vorgegebenen verwenden

/*	if (CTFMODE_AutoMeridian == g_CTFMode) {
	double dX = pDP -> X();

		if (dX < 0 || dX > 7000000.0) 
			return false;

	long double l, b;

		gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, pDP->Y(), dX, &b, &l);
		if (g_iStrBreite == 3)
			riMeridian = (int)((l/3600.0 + 1.5)/3) * 3;
		else
			riMeridian = ((int)((l/3600.0)/6) * 6) + 3;

	} else 
		riMeridian = g_iMeridian;		// vorgegebenen verwenden
*/
	return true;
}
