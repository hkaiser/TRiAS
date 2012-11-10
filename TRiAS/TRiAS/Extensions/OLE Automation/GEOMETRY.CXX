// Allgemeine Funktionen zur Geometrieverwaltung ------------------------------
// File: GEOMETRY.CXX

#include "precomp.hxx"

#include <limits.h>
#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obj.hxx"		// CGeoObject
#include "array.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// lokale Funktionen ----------------------------------------------------------
static OBJGEOMETRIE *GetObjectGeometrie (long lONr, IUnknown *pICS);
static void dtOBJGEOMETRIE (OBJGEOMETRIE *& pOG); 
static bool OffsetGeometrie (short iOTyp, OBJGEOMETRIE *pOG, double dX, double dY);
static bool EvalSchwerPunkt (OBJGEOMETRIE *pOG, double &rdX, double &rdY);

bool CGeoObject :: GetGeometryPt (double &rdX, double &rdY, IUnknown *pICS)
{
// 1. Geometrie entsprechend ObjektTyp besorgen
OBJGEOMETRIE *pOG = GetObjectGeometrie (m_lONr, pICS);
bool fResult = true;

	if (pOG == NULL) return false;

	switch (pOG -> iObjTyp) {
	case OGPunkt:
	case OGText:
	case OGLabel:
		rdX = ((double *)(pOG -> pdblX))[0];
		rdY = ((double *)(pOG -> pdblY))[0];
		break;
		
	case OGLinie:
		{	// mittlere Koordinate benutzen
		long iMiddle = pOG -> lCnt / 2;
		
			rdX = ((double __huge *)(pOG -> pdblX))[iMiddle];
			rdY = ((double __huge *)(pOG -> pdblY))[iMiddle];
		}
		break;
		
	case OGFlaeche:
		if (!EvalSchwerPunkt (pOG, rdX, rdY))
			fResult = false;
		break;
		
	default:
		rdX = 0;
		rdY = 0;
		fResult = false;
		break;
	}
	dtOBJGEOMETRIE (pOG);	// Speicher freigeben

return fResult;
}

short CGeoObject :: GetStatistik (long &rlCnt, short &riKCnt)
{
OBJSTATISTIK os;

	INITSTRUCT (os, OBJSTATISTIK);
	os.lONr = m_lONr;
	if (!DEX_GetObjStatistik (os))
		return OGUnknown;
		
	switch (os.iObjTyp) {
	case OGPunkt:
		rlCnt = 1;
		riKCnt = 1;
		break;

	case OGLinie:
		rlCnt = os.lCnt;
		riKCnt = 1;
		break;
		
	case OGFlaeche:		
		rlCnt = os.lCnt;
		riKCnt = os.iKCnt;
		break;

	case OGLabel:
	case OGText:
		rlCnt = 1;
		riKCnt = os.iKCnt;
		break;

	default:
		rlCnt = 0;
		riKCnt = 0;
		return OGUnknown;
	}
	
return os.iObjTyp;	// liefert ObjektTyp
}

bool CGeoObject::GetGeometry (short iOTyp, long lCnt, double __huge *pX, 
	double __huge *pY, short iKCnt, long *pC, IUnknown *pICS)
{
GEOMETRIEWITHCS gcs;
OBJGEOMETRIE og;

	INITSTRUCT (gcs, GEOMETRIEWITHCS);
	gcs.pOG = &og;
	gcs.pICS = pICS;

	INITSTRUCT (og, OBJGEOMETRIE);
	og.lONr = m_lONr;
	og.iFlags = OGConverted;
	og.lCnt = lCnt;
	og.pdblX = pX;
	og.pdblY = pY;

	if (iOTyp == OGText || iOTyp == OGLabel) {
		og.plCnt = NULL;	// Text selbst nicht anfordern
		og.iKCnt = 0;
	} else {
		og.plCnt = pC;
		og.iKCnt = iKCnt;
	}
	
	if (!DEX_GetObjGeometrie (gcs) || iOTyp != og.iObjTyp) 
		return false;
	
	switch (iOTyp) {
	case OGLabel:
	case OGText:		// besondere Behandlung des Konturfeldes
		break;

	case OGPunkt:
	case OGLinie:
		if (pC) pC[0] = og.lCnt;	// eine Kontur mit lCnt Stützpunkten
		break;
	}
	return true;
}

bool CGeoObject::GetTextObjectText (BSTR *pbstrText)
{
long lCnt = 1;
short iKCnt = 0;
int iOTyp = GetStatistik (lCnt, iKCnt);

	if (OGText != iOTyp && OGLabel != iOTyp)
		return false;

GETTEXTDATA GTD;

	GTD.dwSize = sizeof(GETTEXTDATA);
	GTD.m_lONr = m_lONr;
	GTD.m_pText = new char[iKCnt+2];
	GTD.m_iLen = iKCnt+1;

bool fRet = false;

	if (DEX_GetTextObjectText(GTD)) {
		USES_CONVERSION;

	CComBSTR bstr;

		if (OGLabel == iOTyp) 
			bstr = "@@";

		bstr += A2OLE(GTD.m_pText);
		*pbstrText = bstr.Detach();

		fRet = true;
	}
	delete GTD.m_pText;

	return fRet;
}

bool CGeoObject::PutTextObjectText (BSTR bstrText)
{
	if (INVALID_ONR == m_lONr)
		return false;

PUTTEXTDATAEX PTD;

	USES_CONVERSION;
	INITSTRUCT(PTD, PUTTEXTDATAEX);

os_string str = OLE2A(bstrText);
bool fIndObjProp = false;

	if (!strncmp ("@@", str.c_str(), 2)) {
		str = str.substr (2);
		fIndObjProp = true;
	}

	PTD.m_lONr = m_lONr;
	PTD.m_pcText = str.c_str();
	PTD.m_fIndObjProp = fIndObjProp;

	return DEX_PutTextObjectText (PTD);
}

// ObjektGeometrie verändern: Punkte/Texte wie erwartet, Linien und Flächen 
// werden verschoben
bool CGeoObject :: PutGeometryPt (short iOTyp, double dX, double dY, 
	short iMode, IUnknown *pICS)
{
	if (m_lONr != INVALID_ONR) {
	short iTargetType = DEX_GetObjectType(m_lONr);
	
		if (iTargetType != iOTyp && iTargetType != OGUnknown)
			return false;		// falscher Objekttyp
	}

	switch (iOTyp) {
	case OGPunkt:
	case OGText:
	case OGLabel:
		{
		GEOMETRIEWITHCS gcs;
		OBJGEOMETRIE og;

			INITSTRUCT (gcs, GEOMETRIEWITHCS);
			gcs.pOG = &og;
			gcs.pICS = pICS;

			INITSTRUCT (og, OBJGEOMETRIE);
			og.lONr = m_lONr;
			og.iFlags = (OGConverted|iMode);
			og.iObjTyp = iOTyp;
			og.pdblX = &dX;
			og.pdblY = &dY;
			og.lCnt = 1;
			return DEX_ModObjGeometrie (gcs);
		}
		break;

	case OGLinie:
	case OGFlaeche:	
		if (m_lONr != INVALID_ONR) {	// nur bei existierendem Objekt
		OBJGEOMETRIE *pOG = GetObjectGeometrie (m_lONr, pICS);

			if (pOG == NULL) return false;

		bool fResult = OffsetGeometrie (iOTyp, pOG, dX, dY);

			if (fResult) {
				pOG -> iFlags |= iMode;
				fResult = DEX_ModObjGeometrie (*pOG);
			}
			dtOBJGEOMETRIE (pOG);
			return fResult;
		}
		break;
	}

return false;		// alles ok
}

bool CGeoObject :: PutGeometry (short iOTyp, long lCnt, double __huge *pX, 
	double __huge *pY, short iKCnt, long *pC, short iMode, IUnknown *pICS)
{
GEOMETRIEWITHCS gcs;
OBJGEOMETRIE og;

	INITSTRUCT(gcs, GEOMETRIEWITHCS);
	gcs.pOG = &og;
	gcs.pICS = pICS;

	iMode |= OGConverted;
	INITSTRUCT (og, OBJGEOMETRIE);
	og.lONr = m_lONr;
	og.lIdent = GetObjIdentEx();
	og.iFlags = iMode;
	og.lCnt = lCnt;
	og.pdblX = pX;
	og.pdblY = pY;
	og.iObjTyp = iOTyp;

	if (iOTyp == OGText || iOTyp == OGLabel) {
		og.plCnt = NULL;	// Text selbst nicht schreiben
		og.iKCnt = 0;
	} else {
		og.plCnt = pC;
		og.iKCnt = iKCnt;
	}
	return DEX_ModObjGeometrieEx(DEX_GetObjectProject(m_lONr), gcs);
}

// Objekt auf einen gegebenen Mittelpunkt verschieben -------------------------
static bool OffsetGeometrie (short iOTyp, OBJGEOMETRIE *pOG, double dX, double dY)
{
	if (iOTyp == OGLinie) {	// mittlere Koordinate benutzen
	long iMiddle = pOG -> lCnt / 2;
	double dDeltaX = ((double __huge *)(pOG -> pdblX))[iMiddle] - dX;
	double dDeltaY = ((double __huge *)(pOG -> pdblY))[iMiddle] - dY;

		for (long i = 0; i < pOG -> lCnt; i++) {
			((double __huge *)(pOG -> pdblX))[i] -= dDeltaX;
			((double __huge *)(pOG -> pdblY))[i] -= dDeltaY;
		}
		return true;
	}
		
	if (iOTyp == OGFlaeche) {
	double dDeltaX, dDeltaY;

		if (!EvalSchwerPunkt (pOG, dDeltaX, dDeltaY))
			return false;
		
		dDeltaX -= dX;
		dDeltaY -= dY;

		for (long i = 0; i < pOG -> lCnt; i++) {
			((double __huge *)(pOG -> pdblX))[i] -= dDeltaX;
			((double __huge *)(pOG -> pdblY))[i] -= dDeltaY;
		}
		return true;
	}

return false;	// falscher ObjektTyp
}

// Objektgeometrie besorgen ---------------------------------------------------
static 
OBJGEOMETRIE *GetObjectGeometrie (long lONr, IUnknown *pICS)
{
// Eigenschaften des Objektes anfordern
GEOMETRIEWITHCS gcs;
OBJGEOMETRIE *pOG = new OBJGEOMETRIE;

	if (pOG == NULL) return NULL;

	INITSTRUCT(gcs, GEOMETRIEWITHCS);
	gcs.pOG = pOG;
	gcs.pICS = pICS;

	memset (pOG, '\0', sizeof (OBJGEOMETRIE));
	pOG -> dwSize = sizeof (OBJSTATISTIK);
	pOG -> lONr = lONr;
	DEX_GetObjStatistik (*pOG);

// Geometrie dazuholen
	pOG -> dwSize = sizeof(OBJGEOMETRIE);

// Felder anfordern
	pOG -> pdblX = new double __huge [pOG -> lCnt];
	pOG -> pdblY = new double __huge [pOG -> lCnt];
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
			((TEXTGEOMETRIE *)pOG) -> pText = new char [pOG -> iKCnt+1];
			if (((TEXTGEOMETRIE *)pOG) -> pText == NULL)
				return NULL;
		}
	}
	pOG -> iFlags |= OGConverted;
	DEX_GetObjGeometrie (*pOG);

return pOG;
}


// Freigeben der OBJGEOMETRIE-Struktur ----------------------------------------
static void dtOBJGEOMETRIE (OBJGEOMETRIE *& pOG)
{
	if (pOG == NULL) return;

// Geometriefelder freigeben
	if (pOG -> pdblX) delete (double __huge *)pOG -> pdblX;
	if (pOG -> pdblY) delete (double __huge *)pOG -> pdblY;
	
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


// Berechnet Flächenschwerpunkt einer Fläche ----------------------------------
static bool EvalSchwerPunkt (OBJGEOMETRIE *pOG, double &rdX, double &rdY) 
{
// teste Parameter der Fläche
	if (pOG == NULL || pOG ->  iObjTyp != OGFlaeche)
		return false;
		
long lSize = pOG -> plCnt[0];		// Anzahl Stützpunkte (Außenkontur)
double __huge *pX = (double __huge *)pOG -> pdblX;
double __huge *pY = (double __huge *)pOG -> pdblY;

	if (lSize <= 3 || pX == NULL || pY == NULL) return false;

	if (pX[0] != pX[lSize-1] || pY[0] != pY[lSize-1])
		return false;		// Kontur nicht geschlossen
		
// kleinste X/Y-Koordinate bestimmen
long lIndex;
double lXMin = LONG_MAX;
double lYMin = LONG_MAX;

	for (lIndex = 0; lIndex < lSize; lIndex++) {
		if (pX[lIndex] < lXMin) lXMin = pX[lIndex];
		if (pY[lIndex] < lYMin) lYMin = pY[lIndex];
	}	

// Schwerpunkt berechnen
double Xs = 0.0, Ys = 0.0, Xsi, Ysi, Inh;	// Schwerpunkt-Koordinaten
double dblF = 0.0;

	for (lIndex = 0; lIndex < (lSize - 1); lIndex++) {	// für alle Punkte der Folge
	double X1 = pX[lIndex] - lXMin;			// laufende Koordinaten
	double Y1 = pY[lIndex] - lYMin;
	double X2 = pX[lIndex+1] - lXMin;
	double Y2 = pY[lIndex+1] - lYMin;

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
	if (dblF == 0.0) return false;
	
	rdX = long(((Xs / dblF) + lXMin) * 10 + 0.5) / 10.0;	// Runden auf dm
	rdY = long(((Ys / dblF) + lYMin) * 10 + 0.5) / 10.0;

return true;
}


