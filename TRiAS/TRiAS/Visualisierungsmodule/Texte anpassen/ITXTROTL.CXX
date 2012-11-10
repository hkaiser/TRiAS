// Implementation der eigentlichen Interfaceobjekte fuer VisModule ------------
// File: ITXTROTL.CXX

#include "txtrotlp.hxx"

#include <vismguid.h>

#include "icustom.hxx"	
#include "txtrotl.h"
#include "itxtrotl.hxx"

// globale Daten --------------------------------------------------------------
UINT __DexCmd = 0;
extern "C" HWND __hWndM = NULL;

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
        	delete (CTextRotIVisModule *)m_pIVisModule;
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
 *  bool            true if the function is successful, false otherwise.
 */

BOOL CVisModule :: FInit (void)
{
LPUNKNOWN pIUnknown = (LPUNKNOWN)this;

	if (m_punkOuter != NULL)
		pIUnknown = m_punkOuter;

// Allocate contained interfaces.
	m_pIVisModule = new CTextRotIVisModule (this, pIUnknown);
	if (m_pIVisModule && !((CTextRotIVisModule *)m_pIVisModule) -> FInit()) {
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



// Konstruktor/Destruktor für CTextRotIVisModule ----------------------------------
CTextRotIVisModule :: CTextRotIVisModule (LPVOID pObj, LPUNKNOWN punkOuter)
{
	m_cRef = 0;
	m_pObj = pObj;
	m_punkOuter = punkOuter;
	m_dAspect = 1.0;

	__DexCmd = 0;
	m_pRF = NULL;
}

CTextRotIVisModule :: ~CTextRotIVisModule(void)
{
	DELETE_OBJ (m_pRF);
}


extern "C" char FAR g_pDLLName[_MAX_PATH] = "";	// Name dieses Modules

BOOL CTextRotIVisModule :: FInit (void)
{
	m_pRF = new ResourceFile (g_pDLLName);	// diese DLL
	if (m_pRF == NULL) return false;
	
// KommunikationsMessage mit TRIAS registrieren
	__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));

return __DexCmd != 0;
}

// sonstige InterfaceMember ---------------------------------------------------
STDMETHODIMP CTextRotIVisModule :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	return m_punkOuter -> QueryInterface(riid, ppv);
}


STDMETHODIMP_(ULONG) CTextRotIVisModule :: AddRef(void)
{
	++m_cRef;
	return m_punkOuter -> AddRef();
}

STDMETHODIMP_(ULONG) CTextRotIVisModule :: Release(void)
{
	--m_cRef;
	return m_punkOuter -> Release();
}


// NotifikationsempfängerFunktionen -------------------------------------------
STDMETHODIMP_(void) CTextRotIVisModule :: OnProjectChange (
		HWND __hWndM, PROJECTCHANGE rgPC, char * /*pPrName*/)
{
}


STDMETHODIMP_(void) CTextRotIVisModule :: OnViewChange (
		HWND /*__hWndM*/, VIEWCHANGE /*rgVC*/, char * /*pView*/)
{
}


STDMETHODIMP_(void) CTextRotIVisModule :: OnPaletteChange (
		HWND /*__hWndM*/, HPALETTE /*hPal*/)
{
}


// Die eigentlichen ArbeitsTiere dieses Interfaces ----------------------------

// diese Funktion liefert die ObjektNummer des abhängigen Textobjektes --------
extern "C" BOOL PASCAL _VMD_EXPORT FindLinkedTextObject (
			long lONr, long lRCode, short iRTyp, void *pData)
{
	if ((0 == lRCode || -1L == lRCode) && iRTyp == RTBegleitO) {
		*(long *)pData = lONr;		// ObjektNummer merken
		return false;				// Enumeration abbrechen
	}
	return true;
}


#if defined(_DEBUGPUTPOINT)
static HWND s_hWnd;
void PutPunkt (long lIdent, long lX, long lY);
#else
// Rausgenerieren
#define PutPunkt(a,b,c)
#endif

STDMETHODIMP CTextRotIVisModule :: SymbolizeObject (
		HWND hWndM, long &rlONr, short &iOType,
		char *pBuffer, short /*iLen*/)
{
	__hWndM = hWndM;

// wenn nicht Linie, dann weiter
	if (OGLinie != iOType && OGFlaeche != iOType)
		return ResultFromScode (VISMODULE_E_BADOBJECTTYPE);
		
#if defined(_DEBUGPUTPOINT)
	s_hWnd = __hWndM;
#endif

// aktuellen Aspekt besorgen
	DEX_GetActiveAspect (m_dAspect);

// Abhängiges Textobjekt (ONr und Geometrie) besorgen
long lTONr = -1;	// abhängiges Textobjekt der Linie
ENUMRELATIONOBJS ERO;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = rlONr;
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitO;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedTextObject;
	ERO.pData = &lTONr;
	DEX_EnumRelationObjects (ERO);

	if (lTONr == -1L) 	// kein abhängiges Textobjekt vorhanden
		return ResultFromScode (VISMODULE_E_BADOBJECTTYPE);

// Bestimmen des TextContainers in der aktuellen Vergrößerung
RECTL rclT;

	DEX_GetObjContainer (lTONr, rclT);
	
// Linien-/FlächenGeometrie besorgen
OBJGEOMETRIE *pOG = GetObjectGeometrie (__hWndM, rlONr);

	if (pOG == NULL) return ResultFromScode (E_OUTOFMEMORY);
	
// notwendigen Textwinkel berechnen
long lCnt = (iOType == OGLinie) ? pOG -> lCnt : pOG -> plCnt[0];	// nur Außenkontur bei Flächen
long lArc = EvalArc (rclT.left, rclT.top, rclT.right, lCnt, m_dAspect, 
		     (long *)pOG -> pdblX, (long *)pOG -> pdblY);

	dtOBJGEOMETRIE (pOG);
	if (lArc == 0)		// nichts zu ändern, Fehler vortäuschen
		return ResultFromScode (VISMODULE_E_BADOBJECTTYPE);
		
// Resultate setzen
ResString resFormat (ResID (IDS_TEXTROTFORMAT, m_pRF), 40);

	wsprintf (pBuffer, resFormat, lArc);
	rlONr = lTONr;
	iOType = OGText;
	return NOERROR;
}


STDMETHODIMP CTextRotIVisModule :: DrawObject (
		HWND /*__hWndM*/, HDC /*hDC*/, HDC /*hTargetDC*/, 
		long /*lONr*/, short & /*fDrawFlags*/,
		VisInfo * /*pVI*/, char * /*pVisString*/)
{
	return ResultFromScode (E_NOTIMPL);
}


STDMETHODIMP CTextRotIVisModule :: QueryParameters (
			HWND /*__hWndM*/, long /*lONr*/, 
			VisInfo * /*pVI*/, char * /*pVisStr*/, 
			char * /*pBuffer*/, short /*iLen*/, 
			short *piOTypes)
{
	*piOTypes = (OTLinie|OTFlaeche);	// muß Objekte setzen, die behandelt werden sollen
	
return NOERROR;
}


// Berechnen des Winkels, um den ein abhängier Text gedreht werden muß, damit
// er exakt parallel zur BezugsLinie steht.
const double PI = 3.14159265359;

static long FindSection (long lTX, long lTY, long lCnt, long *pLX,  long *pLY);
static long GetLot (long lPX, long lPY, long *pX, long *pY, long &lLotX, long &lLotY);

long EvalArc (long lTX1, long lTX2, long lTY, long lCnt, double dAspect, long *pLX, long *pLY)
{
	PutPunkt (12345678L, lTX1, lTY);
	PutPunkt (12345678L, lTX2, lTY);

// finden der Strecken, an dem Text ausgerichtet werden soll
long lNum1 = FindSection (lTX1, lTY, lCnt, pLX, pLY);
long lNum2 = FindSection (lTX2, lTY, lCnt, pLX, pLY);

	if (lNum1 == -1 || lNum2 == -1) 
		return 0L;	// nichts machen

	if (lNum2 < lNum1 && lNum2 > 0) 
		lNum2--;
	else
		lNum2++;
	
	PutPunkt (12345672, pLX[lNum1], pLY[lNum1]);
	PutPunkt (12345672, pLX[lNum2], pLY[lNum2]);

// Winkel berechnen, iNum liegt zwischen 0 und iCnt-1
long ldX = pLX[lNum2] - pLX[lNum1];
	
	if (ldX == 0) 
		return -900;	// senkrecht nach oben
	
long ldY = pLY[lNum2] - pLY[lNum1];
long lArc = -long((1800.0/PI) * atan2(double(ldY), double(ldX)*dAspect));	// ansonsten normal berechnen

	if (lArc > 900 && lArc <= 1800) 
		lArc -= 1800;		// im 1. und 4. Quadranten
	if (lArc < -900 && lArc >= -1800)
		lArc += 1800;

	return lArc;
}


// Abstand zweier Punkte ------------------------------------------------------
inline long lAbs (long lT) { return (lT > 0) ? lT : -lT; }
inline long lMin (long l1, long l2) { return (l1 > l2) ? l2 : l1; }

inline double sqr (double x) { return x*x; }

inline long Distance (long lX1, long lY1, long lX2, long lY2)
{
//	return lAbs(lX2-lX1) + lAbs(lY2-lY1);
	return long(sqrt(sqr(lX2-lX1)+sqr(lY2-lY1)));
}

inline bool isInside (long l0, long l1, long l2)
{
	if (l1 < l2) 
		return (l1 <= l0 && l0 <= l2);
	return (l2 <= l0 && l0 <= l1);
}

// Diese Funktion sucht die Strecke in einer Kante, die am nähesten an 
// einem vorgegebenen Punkt (lTX, lTY) liegt.
static long FindSection (long lTX, long lTY, long lCnt, long *pLX,  long *pLY)
{
// 1. Finden des am nächsten liegenden Knotenpunktes der Kante
long lOpt = -1;
long lDist = LONG_MAX;

	for (long lIndex = 0; lIndex < lCnt; lIndex++) {
	long lT = Distance (pLX[lIndex], pLY[lIndex], lTX, lTY);
	
		if (lT < lDist) {
			lDist = lT;
			lOpt = lIndex;
		}
	}
	if (lOpt == -1) return -1;		// Fehler
	if (lOpt == 0) return 0;
	if (lOpt == lCnt-1) return lCnt-2;	// alles klar
		
// 2. Auswählen der anliegenden Teilstrecke, die näher dran liegt
// dazu das Lot vom Punkt auf die Strecken fällen
long lLotX1, lLotY1, lLotX2, lLotY2;		// Koordinaten der LotPunkte
long lLotDist1 = GetLot (lTX, lTY, &pLX[lOpt-1], &pLY[lOpt-1], lLotX1, lLotY1);
long lLotDist2 = GetLot (lTX, lTY, &pLX[lOpt], &pLY[lOpt], lLotX2, lLotY2);

	if (lLotDist1 == 0) {
		if (lLotDist2 == 0) {
		// beide Lotpunkte liegen innerhalb der Strecken,
		// kleinster Abstand des Textes zu den Strecken zählt
		long lDist1 = Distance (lTX, lTY, lLotX1, lLotY1);
		long lDist2 = Distance (lTX, lTY, lLotX2, lLotY2);
		
			if (lDist1 < lDist2) {
				PutPunkt (12345670L, lLotX1, lLotY1);
				return lOpt -1;
			} else {
				PutPunkt (12345671L, lLotX2, lLotY2);
				return lOpt;
			}
		} else {
			PutPunkt (12345670L, lLotX1, lLotY1);
			return lOpt -1;	// Strecke 1
		}
	} else {
		if (lLotDist2 == 0) {
			PutPunkt (12345671L, lLotX2, lLotY2);
			return lOpt;	// Strecke 2
		} else {
		// beide LotPunkte liegen außerhalb der Strecken,
		// kleinster Abstand der Lotpunkte zur Strecke zählt
			if (lLotDist1 < lLotDist2) {
				PutPunkt (12345670L, lLotX1, lLotY1);
				return lOpt -1;
			} else {
				PutPunkt (12345671L, lLotX2, lLotY2);
				return lOpt;
			}
		}
	}
}


// Fällen des Lotes vom Punkt (lPX, lPY) auf die Gerade, auf der die Strecke 
// [(pX[0], pY[0]), (pX[1], pY[1])] liegt.
// Diese Funktion liefert 0, wenn der LotPunkt innerhalb der Strecke liegt,
// ansonsten liefert sie den Abstand des Lotpunktes zum jeweils näheren
// Streckenpunkt.
static long GetLot (long lPX, long lPY, long *pX, long *pY, long &lLotX, long &lLotY)
{
// 1. LotPunkt berechnen
double a1 = pY[0] - pY[1];
double b1 = pX[1] - pX[0];
double c1 = -(b1*pY[0] + a1*pX[0]);
double c2 = a1*lPY - b1*lPX;		// in 2. Geradengleichung eingesetzt
double dNenner = a1*a1 + b1*b1;

	lLotX = long(-(b1*c2 + a1*c1)/dNenner);
	lLotY = long((c2*a1 - b1*c1)/dNenner);
	
// 2. Testen, ob Lotpunkt innerhalb der Strecke liegt
	if (isInside (lLotX, pX[0], pX[1]))
		return 0;	// liegt innerhalb
		
// 3. Abstand zum näheren der beiden Stützpunkte liefern
long lDist1 = Distance (lLotX, lLotY, pX[0], pY[0]);
long lDist2 = Distance (lLotX, lLotY, pX[1], pY[1]);

	return lMin (lDist1, lDist2);
}


// sonstige Hilfsfunktionen ---------------------------------------------------
// Objektgeometrie besorgen ---------------------------------------------------
OBJGEOMETRIE *GetObjectGeometrie (HWND __hWndM, long lONr)
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


// Freigeben der OBJGEOMETRIE-Struktur ----------------------------------------
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


// erzeugen eines Punktobjektes (für TestZwecke) ------------------------------
#if defined(_DEBUGPUTPOINT)
void PutPunkt (long lIdent, long lX, long lY)
{
HWND __hWndM = s_hWnd;

OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = lIdent;
	OG.lCnt = 1;
	OG.iKCnt = 0;
	OG.iObjTyp = OGPunkt;
	OG.iFlags = OGNewObject|OGTempObject;
	OG.pdblX = &lX;
	OG.pdblY = &lY;
	OG.plCnt = NULL;
	
	DEX_ModObjGeometrie (OG);
}
#endif // _DEBUGPUTPOINT
