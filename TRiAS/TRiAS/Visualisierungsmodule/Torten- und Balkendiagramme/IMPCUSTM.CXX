// Implementation der eigentlichen Interfaceobjekte fuer VisModule ------------
// File: IMPCUSTM.CXX

#include "tortenp.hxx"

#include <icustom.hxx>
#include <vismguid.h>

#include "impcustm.hxx"
#include "paltree.hxx"

#include <resstrg.h>
#include <protos.h>
#include "tortenid.h"
#include "torten.h"

#if !defined(WIN32)
#include <tchar.h>
#endif // !WIN32

#define YYLMAX	2048

OLECHAR *VMDWideString (const char *strIn);

// globale Daten --------------------------------------------------------------
UINT __DexCmd = 0;

/*
 * Parameters (Constructor):
 *  punkOuter       LPUNKNOWN of a controlling unknown, if it exists.
 *  pfnDestroy      LPFNDESTROYED to call when an object is destroyed.
 */

CVisModule :: CVisModule (LPUNKNOWN punkOuter, LPFNDESTROYED pfnDestroy)
{
	m_cRef = 0;
	m_punkOuter = punkOuter;
	m_pfnDestroy = pfnDestroy;

// NULL any contained interfaces initially.
	m_pIVisModule = NULL;
}


CVisModule :: ~CVisModule (void)
{
// Free contained interfaces.
	if (m_pIVisModule!= NULL)		// Interface does not free itself.
        	delete (CTortenVisModule *)m_pIVisModule;
}


/*
 * FInit
 *
 * Purpose:
 *  Performs any intiailization of a CKoala that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful, FALSE otherwise.
 */

BOOL CVisModule :: FInit (void)
{
LPUNKNOWN pIUnknown = (LPUNKNOWN)this;

	if (m_punkOuter != NULL)
		pIUnknown = m_punkOuter;

// Allocate contained interfaces.
	m_pIVisModule = new CTortenVisModule (this, pIUnknown);
	if (m_pIVisModule && !((CTortenVisModule *)m_pIVisModule) -> FInit()) {
		delete m_pIVisModule;
		return NULL;
	}

return m_pIVisModule != NULL;
}


// IUnknownMember von CVisModule ----------------------------------------------
STDMETHODIMP CVisModule :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	*ppv = NULL;

/*
 * The only calls we get here for IUnknown are either in a non-aggregated
 * case or when we're created in an aggregation, so in either we always
 * return our IUnknown for IID_IUnknown.
 */
	if (IsEqualIID (riid, IID_IUnknown))
		*ppv = (LPVOID)this;

	if (IsEqualIID(riid, IID_IVisModule))
		*ppv = (LPVOID)m_pIVisModule;

// AddRef any interface we'll return.
	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CVisModule :: AddRef (void)
{
	return ++m_cRef;
}


STDMETHODIMP_(ULONG) CVisModule :: Release (void)
{
ULONG       cRefT;

	cRefT = --m_cRef;

	if (m_cRef == 0) {
        /*
         * Tell the housing that an object is going away so it can
         * shut down if appropriate.
         */
		if (m_pfnDestroy != NULL)
			(*m_pfnDestroy)();

		delete this;
	}

return cRefT;
}



// Konstruktor/Destruktor für CTortenVisModule ----------------------------------
CTortenVisModule :: CTortenVisModule (LPVOID pObj, LPUNKNOWN punkOuter)
{
	m_cRef = 0;
	m_pObj = pObj;
	m_punkOuter = punkOuter;
	__DexCmd = 0;
	m_pRF = NULL;
	m_pActProject = NULL;
	m_hPal = 0;
}

CTortenVisModule :: ~CTortenVisModule(void)
{
	DELETE_OBJ (m_pRF);
	DELETE_OBJ (m_pPalT);
	DELETE_OBJ (m_pActProject);
}


extern "C" char FAR g_pDLLName[];	// Name dieses Modules

BOOL CTortenVisModule :: FInit (void)
{
// PalettenBaum anlegen
	m_pPalT = new CVisPaletteTree;
	if (m_pPalT == NULL) return FALSE;
		
	m_pRF = new ResourceFile (g_pDLLName);	// diese DLL
	if (m_pRF == NULL) return FALSE;
	
// KommunikationsMessage mit TRIAS registrieren
	__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));

return __DexCmd != 0;
}

// sonstige InterfaceMember ---------------------------------------------------
STDMETHODIMP CTortenVisModule :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	return m_punkOuter -> QueryInterface(riid, ppv);
}


STDMETHODIMP_(ULONG) CTortenVisModule :: AddRef(void)
{
	++m_cRef;
	return m_punkOuter -> AddRef();
}

STDMETHODIMP_(ULONG) CTortenVisModule :: Release(void)
{
	--m_cRef;
	return m_punkOuter -> Release();
}


// NotifikationsempfängerFunktionen -------------------------------------------
STDMETHODIMP_(void) CTortenVisModule :: OnProjectChange (
		HWND __hWndM, PROJECTCHANGE rgPC, char *pPrName)
{
// Paletten dieses Projektes einlesen
	m_pPalT -> EveryDelete();	// alle alten Paletten freigeben

	if (rgPC == PROJECTCHANGE_OPENED) {
	// ProjektNamen merken
		DELETE_OBJ (m_pActProject);
		m_pActProject = new char [_MAX_PATH];
		if (m_pActProject)
			strcpy (m_pActProject, pPrName);
			
	// Storage finden
	LPSTORAGE pIStorage;
	HRESULT hr = OpenProjectPaletteStorage (__hWndM, pPrName, &pIStorage);
	
		if (FAILED(hr)) return;
		
	ResString resPals (ResID (IDS_TORTENPALETTEN, m_pRF), 40);

		m_pPalT -> LoadPalettes (pIStorage, resPals);
		pIStorage -> Commit (STGC_DEFAULT);	// evtl. StandardPalette erzeugt
		pIStorage -> Release();

	} else if (rgPC == PROJECTCHANGE_CLOSED) {
		m_hPal = 0;	// alte Palette vergessen
	}
}


STDMETHODIMP_(void) CTortenVisModule :: OnViewChange (
		HWND hWndM, VIEWCHANGE rgVC, char *pView)
{
}


STDMETHODIMP_(void) CTortenVisModule :: OnPaletteChange (HWND /*hWndM*/, HPALETTE hPal)
{
	if (m_pPalT) m_pPalT -> RetrievePalette (hPal);
	m_hPal = hPal;		// Palette des Hauptfensters merken
}


STDMETHODIMP CTortenVisModule :: SymbolizeObject (
		HWND hWndM, long &rlONr, short &iOType, char *pBuffer, short iLen)
{
	return ResultFromScode (E_NOTIMPL);
}


// Die eigentlichen ArbeitsTiere dieses Interfaces ----------------------------
//
// Typ 0:	VollkreisTorte
// Typ 1:	HalbkreisTorte oberer Halbkreis
// Typ 2:	HalbkreisTorte unterer Halbkreis

// Generieren eines Tortendiagrammes auf der Grundlage der gegebenen MerkmalsCodes
STDMETHODIMP CTortenVisModule :: DrawObject (
		HWND hWndM, HDC hDC, HDC hTargetDC, long lONr, short &fDrawFlags,
		VisInfo *pVI, char *pVisString)
{
	if (fDrawFlags & (DF_Blinking|DF_Analyze))	// beim Blinken nicht zeichnen
		return ResultFromScode (VISMODULE_S_OBJECTISDRAWN);

	__hWndM = hWndM;
		
// wenn noch keine Palette gegeben ist, dann diese holen und mergen		
	if (m_hPal == 0) {
		m_hPal = DEX_GetActivePalette();
		if (m_hPal != 0 && m_pPalT) 
			m_pPalT -> RetrievePalette (m_hPal);
		fDrawFlags |= DO_ColorChanged;		// Palette neu 'realizen'
	}

// 1. Analyse des pVisStrings, generieren des MCodeFeldes
// Dieses String hat folgendes Format:
// Anzahl der Parameter(N),Item1,Item2,...,ItemN
// Wobei Item entweder ein MerkmalsCode: % INTEGER oder
//		       ein MerkmalsWert: STRING ist.
char **ppMWerte = NULL;		// MerkmalsWerte
short iCnt = 0;
char cDel = ',';
HRESULT hr = ParseVisString (__hWndM, pVisString, lONr, &iCnt, &ppMWerte, cDel);

	if (FAILED(hr)) return hr;
	
// 2. TortenParameter definieren
long *pSectors = new long [iCnt+1];
short iSectors = 0;
long lRadius = 0;

	if (pSectors == NULL) return ResultFromScode(E_OUTOFMEMORY);
	iSectors = GetSectors (ppMWerte, iCnt, lRadius, pSectors, cDel);
	if (iSectors <= 0 || lRadius == 0) 
		return ResultFromScode(VISMODULE_E_GENERALERROR);
	
// 4. Punkt berechnen, an dem gezeichnet werden soll
POINT ptPoint;
SIZE szSize;

	hr = GetPoint (__hWndM, lONr, &ptPoint);	// Bezugspunkt besorgen
	if (SUCCEEDED(hr)) {
	// 5. Berechnen der realen Größe der Ausgabe
		EvalSize (__hWndM, hTargetDC, lRadius, &szSize);

	// 6. Torte malen
	RECT rcEA;
		
		DEX_GetExposedArea (rcEA);
		hr = ResultFromScode (VISMODULE_S_OBJECTISDRAWN);
		if (!(ptPoint.x - szSize.cx > rcEA.right || 
		      ptPoint.x + szSize.cx < rcEA.left ||
		      ptPoint.y - szSize.cy > rcEA.top ||
		      ptPoint.y + szSize.cy < rcEA.bottom))
		{
		// nur zeichnen, wenn im ClippingRect
			if (!DrawGraphic (pVI, hDC, hTargetDC, ptPoint, szSize, 
					  iSectors, pSectors, ppMWerte))
				hr = ResultFromScode (VISMODULE_E_GENERALERROR);
		}
	}	
	DELETE_OBJ (pSectors);
	while (--iCnt >= 0) {
		DELETE_OBJ (ppMWerte[iCnt]);
	}
	DELETE_OBJ (ppMWerte);
	
return hr;
}


// sonstige Member ------------------------------------------------------------
HRESULT CTortenVisModule :: ParseVisString (HWND __hWnd, char *pVisString, long lONr, 
					  short *pCnt, char ***pppMWerte, char &cDel)
{
// Parameter initialisieren
	*pCnt = 0;
	*pppMWerte = NULL;
	
// Anzahl der Parameter besorgen
char *pStr = NULL;
short iCnt = (short)strtol (pVisString, &pStr, 10);	// erster Wert ist Anzahl
char cbDel[2];

	if (iCnt <= 0 || *pStr == '\0') 
		return ResultFromScode(VISMODULE_E_GENERALERROR);

	cbDel[0] = *pStr;	// String simulieren, Trennzeichen
	cbDel[1] = '\0';
	cDel = *pStr;

	*pppMWerte = new char * [iCnt];
	if (*pppMWerte == NULL) 
		return ResultFromScode(E_OUTOFMEMORY);
	
// Parameter herauslösen
short nSucc = 0;

	for (short i = 0; i < iCnt; i++) {
	// Speicher für MerkmalsWert anlegen
		(*pppMWerte)[i] = new char [YYLMAX];

		if (*++pStr == '\0') {
			DELETE_OBJ ((*pppMWerte)[i]);
			break;
		}

		if (*pStr == '%') {
		// MerkmalsCode gegeben
		long lMCode = strtol (++pStr, &pStr, 10);
		
			if (!ReadTextMerkmal (__hWnd, TT_Objekt, lONr, 
					     lMCode, (*pppMWerte)[i]))
			{
				DELETE_OBJ ((*pppMWerte)[i]);
			}
		} else {
		// MerkmalsWert direkt gegeben
			if ((*pppMWerte)[i] != NULL) {
			// nächstes Item umkopieren
			char *pTmp = strpbrk (pStr, cbDel);
			
				if (pTmp) {
					*pTmp = '\0';
					strcpy ((*pppMWerte)[i], pStr);
					pStr = pTmp;
				} else if (*pStr) {
				// letztes Item
					strcpy ((*pppMWerte)[i], pStr);
					while (*++pStr)
						;
				} else {
				// Fehler
					DELETE_OBJ ((*pppMWerte)[i]);
					break;
				}
			}
		}
		nSucc++;	// Zähler der gültigen Einträge
	}
	*pCnt = nSucc;
	
return NOERROR;
}


short CTortenVisModule :: GetSectors (char **ppMWerte, short iCnt, 
				    long &lRadius, long *pSectors, char cDel)
{
	if (pSectors == NULL) return 0;
	
// erster MWert ist geforderter Durchmesser, iRadius in [0.01 mm]
	if (ppMWerte[0] == NULL || *ppMWerte[0] == '\0')
		return 0;

	lRadius = long(atof (ppMWerte[0]) * 100);
	
// Sektoren konvertieren
short nSucc = 0;
double dNextVal = 0L;
char *pEnd = NULL;

	for (short i = 1; i < iCnt; i++) {
		if (ppMWerte[i] == NULL)
			continue;

		dNextVal = strtod (ppMWerte[i], &pEnd);
		if (*pEnd == ',' && cDel != ',') {	// Komma als DezimalPunkt
			*pEnd = '.';			// DezimalPunkt setzen
			dNextVal = strtod (ppMWerte[i], &pEnd);	// nochmal
		}
		if (pEnd == ppMWerte[i])	// nichts sinnvolles gefunden
			*ppMWerte[i] = '\0';

		pSectors[i-1] = (long)(dNextVal*VALUE_SCALING);
		nSucc++;
	}
	pSectors[i] = 0;	// letztes Element ausnullen
	
return nSucc;
}


HRESULT CTortenVisModule :: GetPoint (HWND __hWndM, long lONr, POINT *pszPt)
{
// 1. Geometrie entsprechend ObjektTyp besorgen
OBJGEOMETRIE *pOG = GetObjectGeometrie (__hWndM, lONr);
HRESULT fResult = NOERROR;
POINTL szPointl;

	if (pOG == NULL) return ResultFromScode (E_OUTOFMEMORY);

	switch (pOG -> iObjTyp) {
	case OGPunkt:
		szPointl.x = ((long *)(pOG -> pdblX))[0];
		szPointl.y = ((long *)(pOG -> pdblY))[0];
		break;
		
	case OGLinie:
		{	// mittlere Koordinate benutzen
		short iMiddle = (short)pOG -> lCnt / 2;
		
			szPointl.x = ((long *)(pOG -> pdblX))[iMiddle];
			szPointl.y = ((long *)(pOG -> pdblY))[iMiddle];
		}
		break;
		
	case OGFlaeche:
		if (!EvalSchwerPunkt (pOG, &szPointl))
			fResult = ResultFromScode (VISMODULE_E_GENERALERROR);
		break;
		
	default:
		szPointl.x = 0;
		szPointl.y = 0;
		fResult = ResultFromScode (VISMODULE_E_GENERALERROR);
		break;
	}
	dtOBJGEOMETRIE (pOG);	// Speicher freigeben

// Koordinate in BildKoordinaten umrechnen
	if (SUCCEEDED(fResult)) {
	COORDCONVERT CC;
	
		CC.lpPkt = (long *)&szPointl;
		CC.lpPt = pszPt;
		DEX_OCtoDCEx (CC);
	}

return fResult;
}


// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster -----
static SIZE GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
SIZE szSize;

	if (hDC != NULL) hDCloc = hDC;
	else		 hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc)) {
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		short HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		short VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		short HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		short VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			szSize.cx = HorzRes/HorzSize;
			szSize.cy = VertRes/VertSize;	
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		szSize.cx = 100;
		szSize.cy = 100;	
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		szSize.cx = 10;
		szSize.cy = 10;	
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		szSize.cx = 40;
		szSize.cy = 40;	
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		szSize.cx = 4;
		szSize.cy = 4;	
		break;
		
	case MM_TWIPS:
		szSize.cx = 57;
		szSize.cy = 57;	
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) ReleaseDC (NULL, hDCloc);

return szSize;
}


// Berechnen der realen Ausdehnung der Grafik auf dem TargetDevice ------------
BOOL CTortenVisModule :: EvalSize (HWND __hWndM, HDC hTargetDC, 
				 long lRadius, SIZE *pSize)
{
SIZE szDots = GetDotsPerMM (hTargetDC);
double dM;

	DEX_GetActiveScaling (dM);		// Maßstabs-Verhälnis
	pSize -> cx = (short)(((long)szDots.cx * lRadius) / (100 * dM));
	pSize -> cy = (short)(((long)szDots.cy * lRadius) / (100 * dM));

return TRUE;	
}


// Zeichnen eines Symboles entsprechend SymbolTyp -----------------------------
COLORREF crefPieColors[MAXPIECOLORS] = {
	RGB (255,   0,   0),		// rot
	RGB (  0, 255,   0),		// grün
	RGB (  0,   0, 255),		// blau
	RGB (255, 255,   0),		// gelb
	RGB (255,   0, 255),		// magenta
	RGB (  0, 255, 255),		// cyan
	RGB (255, 255, 255),		// weiß
	RGB (128, 128, 128),		// grau
	RGB (128,   0,   0),		// dunkelrot
	RGB (  0, 128,   0),		// dunkelgrün
	RGB (  0,   0, 128),		// dunkelblau
	RGB (128, 128,   0),		// dunkelgelb
	RGB (128,   0, 128),		// dunkelmagenta
	RGB (  0, 128, 128),		// dunkelcyan
	RGB (196, 196, 196),		// hellgrau
	RGB (  0,   0,   0),		// schwarz
};


BOOL CTortenVisModule :: DrawGraphic (VisInfo *pVI, HDC hDC, HDC hTargetDC, 
				    POINT szPoint, SIZE szSize, 
				    short iSectors, long *pSectors, char **ppMWerte)
{
	switch (pVI -> Style() & TORTEN_TYPEMASK) {
	case TORTEN_FULLCIRCLE:		// VollKreisTorte
	case TORTEN_UPPERHALF:		// obere HalbkreisTorte
	case TORTEN_LOWERHALF:		// untere HalbkreisTorte
		return DrawTorte (pVI, hDC, hTargetDC, szPoint, szSize, 
				  iSectors, pSectors, ppMWerte);

	case TORTEN_BALKENHOCHPOS:	// Säulendiagramm nach oben
	case TORTEN_BALKENROT:		// Säulendiagramm drehbar
		return DrawBalkenHochPos (pVI, hDC, hTargetDC, szPoint, szSize, 
					  iSectors, pSectors, ppMWerte, BMNormal);

	case TORTEN_BALKENHOCHPOSLOG:	// Säulendiagramm nach oben, logarithmisch
	case TORTEN_BALKENROTLOG:	// Säulendiagramm drehbar, logarithmisch
		return DrawBalkenHochPos (pVI, hDC, hTargetDC, szPoint, szSize, 
					  iSectors, pSectors, ppMWerte, BMLog);

	case TORTEN_BALKENHOCHPOSEXP:	// Säulendiagramm nach oben, exponentiell
		return DrawBalkenHochPos (pVI, hDC, hTargetDC, szPoint, szSize, 
					  iSectors, pSectors, ppMWerte, BMExp);

	case TORTEN_BALKENHOCHNEG:	// Säulendiagramm nch unten
	case TORTEN_BALKENQUERPOS:	// Säulendiagramm nach rechts
	case TORTEN_BALKENQUERNEG:	// Säulendiagramm nach links

	case TORTEN_SAEULEHOCH:
	case TORTEN_SAEULEQUER:
	default:
		break;
	}
	
return TRUE;
}


// Lesen eines Textmerkmales --------------------------------------------------
BOOL CTortenVisModule :: ReadTextMerkmal (HWND __hWndM, short iTTyp, 
					long lTarget, long lMCode, char *pText)
{
TARGETMERKMAL gm;

	gm.dwSize = sizeof(TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? _MAX_PATH : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return FALSE;

return TRUE;
}


// Objektgeometrie besorgen ---------------------------------------------------
OBJGEOMETRIE *CTortenVisModule :: GetObjectGeometrie (HWND __hWndM, long lONr)
{
// Eigenschaften des Objektes anfordern
OBJGEOMETRIE *pOG = new OBJGEOMETRIE;

	if (pOG == NULL) return NULL;

	memset (pOG, '\0', sizeof (OBJGEOMETRIE));
	pOG -> dwSize = sizeof (OBJSTATISTIK);
	pOG -> lONr = lONr;
	DEX_GetObjStatistik (*pOG);

// Geometrie dazuholen
	pOG -> dwSize = sizeof(OBJGEOMETRIE);

// Felder anfordern
	pOG -> pdblX = new long [pOG -> lCnt];
	pOG -> pdblY = new long [pOG -> lCnt];
	if (pOG -> pdblX == NULL || pOG -> pdblY == NULL) {
		DELETE_OBJ (pOG -> pdblX);
		return NULL;
	}
		
	if (pOG -> iKCnt > 0) {
		if (pOG -> iObjTyp == OGFlaeche) {
			pOG -> plCnt = new long [pOG -> iKCnt];
			if (pOG -> plCnt == NULL) 
				return NULL;
		} else if (pOG -> iObjTyp == OGText || pOG -> iObjTyp == OGLabel) {
			((TEXTGEOMETRIE *)pOG) -> pText = new char [pOG -> iKCnt];
			if (((TEXTGEOMETRIE *)pOG) -> pText == NULL)
				return NULL;
		}
	}
	DEX_GetObjGeometrie (*pOG);

return pOG;
}


// freigeben der OBJGEOMETRIE-Struktur ----------------------------------------
void dtOBJGEOMETRIE (OBJGEOMETRIE *& pOG)
{
	if (pOG == NULL) return;

// Geometriefelder freigeben
	if (pOG -> pdblX) delete (long *)pOG -> pdblX;
	if (pOG -> pdblY) delete (long *)pOG -> pdblY;
	
// Kontur-/bzw. Textfeld freigeben
	if (pOG -> iKCnt > 0) {
		if (pOG -> iObjTyp == OGFlaeche) {
			if (pOG -> plCnt)
				delete pOG -> plCnt;
		} else if (pOG -> iObjTyp == OGText || pOG -> iObjTyp == OGLabel) {
			if (((TEXTGEOMETRIE *)pOG) -> pText)
				delete ((TEXTGEOMETRIE *)pOG) -> pText;
		}
	}
// Struktur selbst freigeben
	DELETE_OBJ (pOG);
}


// Berechnet Flächenschwerpunkt der Fläche ------------------------------------
BOOL EvalSchwerPunkt (OBJGEOMETRIE *pOG, POINTL *pszPt) 
{
// teste Parameter der Fläche
	if (pOG == NULL || pOG ->  iObjTyp != OGFlaeche)
		return FALSE;
		
long lSize = pOG -> plCnt[0];		// Anzahl Stützpunkte (Außenkontur)
long *pX = (long *)pOG -> pdblX;
long *pY = (long *)pOG -> pdblY;

	if (lSize <= 3 || pX == NULL || pY == NULL) return FALSE;

	if (pX[0] != pX[lSize-1] || pY[0] != pY[lSize-1])
		return FALSE;		// Kontur nicht geschlossen
		
// kleinste X/Y-Koordinate bestimmen
long lIndex;
long lXMin = LONG_MAX;
long lYMin = LONG_MAX;

	for (lIndex = 0; lIndex < lSize; lIndex++) {
		if (pX[lIndex] < lXMin) lXMin = pX[lIndex];
		if (pY[lIndex] < lYMin) lYMin = pY[lIndex];
	}	

// Schwerpunkt berechnen
double Xs = 0.0, Ys = 0.0, Xsi, Ysi, Inh;	// Schwerpunkt-Koordinaten
double dblF = 0.0;

	for (lIndex = 0; lIndex < (lSize - 1); lIndex++) {	// für alle Punkte der Folge
	double X1 = double (pX[lIndex] - lXMin);	// laufende Koordinaten
	double Y1 = double (pY[lIndex] - lYMin);
	double X2 = double (pX[lIndex+1] - lXMin);
	double Y2 = double (pY[lIndex+1] - lYMin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {	   // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) /
				(3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 *Y2)) /
				(3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;
		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	      // Schwerpunkt
		Ys += Ysi * Inh;
		dblF += Inh;		      // Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (dblF == 0.0) return FALSE;
	
	pszPt -> x = long ((Xs / dblF) + lXMin + 0.5);
	pszPt -> y = long ((Ys / dblF) + lYMin + 0.5);

return TRUE;	
}


HRESULT CTortenVisModule :: OpenProjectPaletteStorage (HWND __hWndM,
				char *pPrName, LPSTORAGE *ppIStorage)
{
	*ppIStorage = NULL;		// für alle Fälle

HRESULT hr = NOERROR;
DWORD dwMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED;

	DEX_GetProjectStorage (*ppIStorage);
	if (*ppIStorage == NULL) {
	// altes ProjektStruktur, eigenes DocFile erzeugen/öffnen
	ResString resExt (ResID (IDS_VMDEXT, m_pRF), 10);
	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_DIR];
	char *pFName = new char [_MAX_FNAME];
	char *pSName = new char [_MAX_PATH];
	
		if (pDrive == NULL || pPath == NULL || pFName == NULL || pSName == NULL) {
			DELETE_OBJ (pDrive);
			DELETE_OBJ (pPath);
			DELETE_OBJ (pFName);
			return ResultFromScode (E_OUTOFMEMORY);
		}
			
	// DateiNamen zusammenbauen
		_splitpath (pPrName, pDrive, pPath, pFName, NULL);
		_makepath (pSName, pDrive, pPath, pFName, resExt);

	// Speicher freigeben
		DELETE_OBJ (pDrive);
		DELETE_OBJ (pPath);
		DELETE_OBJ (pFName);

		hr = StgOpenStorage (VMDWideString(pSName), NULL, dwMode, 0, 0, ppIStorage);
		if (FAILED(hr)) {
			if (GetScode(hr) == STG_E_FILENOTFOUND) {
			// neu anlegen
				dwMode |= STGM_CREATE;
				hr = StgCreateDocfile (VMDWideString(pSName), dwMode, 0, ppIStorage);
				DELETE_OBJ (pSName);
				if (FAILED(hr)) return hr;
				
			// GUID reinschreiben (Kontrollmöglichkeit)
				hr = WriteClassStg (*ppIStorage, CLSID_TortenPalette);
				if (FAILED(hr)) {
					(*ppIStorage) -> Release();
					return hr;
				}
			} else {
				DELETE_OBJ (pSName);
				return hr;
			}
		} else {
			DELETE_OBJ (pSName);
		}	

	CLSID clsid;
		
		hr = ReadClassStg (*ppIStorage, &clsid);
		if (FAILED(hr) || !IsEqualCLSID (clsid, CLSID_TortenPalette)) {
			(*ppIStorage) -> Release();
			return hr;
		}
	} 
	return hr;
}


