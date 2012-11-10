// Module enthaelt die Exportierten Routinen einer Koordinatentransformation
// File: DEFAULT.CXX

#include "defaultp.hxx"

#include "default.h"

extern "C" LPSTR FAR WINAPI DtoACTF (LPSTR, LPSTR, double);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Schnittstellenfunktionen für Koordinatentransformationen -------------------
extern char FAR g_pDLLName[];

extern "C" {

UINT __DexCmd = 0;
HWND __hWndM = 0;
double __dK = 1.0;
short __lP = 0;

// Initialisieren der Koordinatentransfromation nach dem erfolgreichen Laden
// der CTF-DLL
bool FAR PASCAL EXPORTCTF CoordTransLoad (HWND hWnd) 
{
// bilden des ResourceFiles
ResourceFile RF (g_pDLLName);

	__hWndM = NULL;

// SkalierungsKoeffizienten aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFSCALING, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) __dK = fabs(HE.EntryDouble (1.0));
		else				  __dK = 1.0;
	}
	if (__dK == 0.0) __dK = 1.0;

// DarstellungsGenauigkeit aus Header holen
	{
	HeaderEntryX HE (ResString (ResID (IDS_CTFPRECISION, &RF), 17));

		if (HE.Status() == HE_UNMODIFIED) __lP = (short)HE.EntryLong (0);
		else				  __lP = 0;
	}

return true;
}

// De-Initialisieren der DLL vor dem Freigeben durch TRIAS(R)
bool FAR PASCAL EXPORTCTF CoordTransUnLoad (void)
{
	return true;
}

// Liefert die Beschreibungsinformationen zu dieser Koordinatentransformation--
bool FAR PASCAL EXPORTCTF CoordTransDescription (COORDTRANSDESC *pCTD)
{
ResourceFile RF (g_pDLLName);

	strncpy (pCTD -> pDesc, 
		 ResString (ResID (IDS_DESCRIPTION, &RF), 120), 
		 pCTD -> iLen);

return true;
}

/*
bool FAR PASCAL EXPORTCTF CoordTransMode (COORDTRANSMODE *)
{
	return true;
}
*/

// Diese Funktion liefert einen Skalierungswert für einen gegebenen 
// Bildausschnitt, der die Darstellungs-Isotropie des Bildes gewährleistet
double FAR PASCAL EXPORTCTF CoordTransAspectRatio (const DoublePair *, 
						 const DoublePair *)
{
	return 1.0;	// im Normalfall keine Anisotropie
}

// Transformation eines Koordinatenpaares aus Datenbasiskoordinaten in 
// projektionsspezifische Koordinaten
bool FAR PASCAL EXPORTCTF Transform (DoublePair *pDB, short iNum)
{
	if (__dK == 1.0) return true;	// nothing to do

	for (short i = 0; i < iNum; i++) {
		pDB[i].X() /= __dK;
		pDB[i].Y() /= __dK;
	}
	return true;
}

// Transformation eines projektionsspezifischen Koordinatenpaares in
// Datenbasiskoordinaten
bool FAR PASCAL EXPORTCTF InvTransform (DoublePair *pDB, short iNum)
{
	if (__dK == 1.0) return true;	// nothing to do

	for (short i = 0; i < iNum; i++) {
		pDB[i].X() *= __dK;
		pDB[i].Y() *= __dK;
	}
	return true;
}

// Berechnen des Abstandes zweier in Datenbasiskoordinaten gegebenen Punkte ---
double FAR PASCAL EXPORTCTF CoordTransDistance (const DoublePair *pP1, 
					      const DoublePair *pP2)
{
double DeltaX = (pP2 -> Width() - pP1 -> Width()) / __dK;
double DeltaY = (pP2 -> Height() - pP1 -> Height()) / __dK;

// hier: karthesischer Abstand
double s = DeltaX*DeltaX + DeltaY*DeltaY;

	return s != 0.0 ? sqrt (s) : 0.0;
}

// Berechnen eine Punktes, der gegebenen Abstand von einem anderen Punkt hat
bool FAR WINAPI EXPORTCTF CoordTransRectangle (const DoublePair *pIn, 
					       const DoublePair *pDelta,
					       DoublePair *pOut)
{
	pOut -> X() = pIn -> Width() + (pDelta -> Width() * __dK);
	pOut -> Y() = pIn -> Height() + (pDelta -> Height() * __dK);

return true;
}

// Konvertieren eines KoordinatenWertes in die entsprechende Darstellungsform -
char * FAR PASCAL EXPORTCTF CoordTransToString (double Value, bool, char *pBuffer, short)
{
char pFormat[20];

	wsprintf (pFormat, "%%%d.%df", __lP+8, __lP);

char *pReturn = DtoACTF (pBuffer, pFormat, Value /* /__dK */);

	if (NULL != pReturn) {
	// evtl. führende leerzeichen entfernen
	int iCnt = 0;
	char *pT = pReturn;

		while (*pT) {
			if (*pT != ' ')
				break;
			pT++;
			iCnt++;
		}
		if (iCnt > 0) 
			memmove (pReturn, &pReturn[iCnt], strlen(pReturn)-iCnt+1);	// NullByte mitkopieren
	}
	return pReturn;	
}

// Konvertieren eines in der Darstellungsform gegeben Koordinatenwertes -------
double FAR PASCAL EXPORTCTF CoordTransToValue (char *pBuffer)
{
	return atof (pBuffer) /* *__dK */;
}

// Metrische/eigene Koordinaten -----------------------------------------------
bool FAR PASCAL EXPORTCTF CoordTransIsMetric (void)
{
	return true;
}

// KonvertierungsRoutinen werden nicht benötigt, da alles bereits metrisch ist 
bool FAR PASCAL EXPORTCTF CoordTransNative (DoublePair *pDB, short iNum)
{
	if (__dK == 1.0) return true;	// nothing to do

	for (int i = 0; i < iNum; i++) {
		pDB[i].X() *= __dK;
		pDB[i].Y() *= __dK;
	}

	return true;
}


bool FAR PASCAL EXPORTCTF CoordTransMetric (DoublePair *pDB, short iNum)
{
	if (__dK == 1.0) return true;	// nothing to do

	for (int i = 0; i < iNum; i++) {
		pDB[i].X() /= __dK;
		pDB[i].Y() /= __dK;
	}

	return true;
}

#if defined(WIN32)

bool PASCAL CoordTransNativeParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

	*ppData = NULL;

return true;
}

bool PASCAL CoordTransMetricParam (DoublePair *pP, LPVOID *ppData)
{
	TX_ASSERT(NULL != ppData);
	if (NULL == ppData) return false;

	*ppData = NULL;

return true;
}

// KonvertierungsRoutinen von/in metrische Koordinaten (parametrisierbar)
bool PASCAL CoordTransNativeEx (DoublePair *pP, short iNum, LPVOID pData)
{
	return CoordTransNative (pP, iNum);
}

bool PASCAL CoordTransMetricEx (DoublePair *pP, short iNum, LPVOID pData)
{
	return CoordTransMetric (pP, iNum);
}

#endif // WIN32

}	// extern "C"

