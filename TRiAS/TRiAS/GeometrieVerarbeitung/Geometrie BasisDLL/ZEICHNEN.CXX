// Funktionen zum Zeichnen
// File: ZEICHNEN.CXX
// W. Mörtl


#include "GeometrP.hxx"

#include <drawobj.hxx>
#include <dragline.hxx>
#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)

#include "zeichnen.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
        
    
extern HWND __hWndM;
extern UINT __DexxCmd;
extern UINT __DexCmd;
          


// --------------------------------------------------------------------------------------------
// Linie mit den BS-Punkten APt und EPt auf dem Bildschirm zeichnen
bool _GEOMETR_EXPORT DrawLine (Point APt, Point EPt, pWindow pW)
{
DragLineObject* DRO = new DragLineObject (APt);	// Linie mit Anfangspunkt APt

	if (! DRO)
	{
		DEX_Error (RC_zeichnen, EC_NOMEMORY);
		return false;
	}

	DRO->ChangeRop (ROP_Invert);	// das von DRO überzeichnete Gebiet wird invertiert
	DRO->Process (EPt);			// EPt ist der Endpunkt der zu zeichnenden Linie
	pW->Draw (DRO);				// Linie vom new-Parameter bis Process-Parameter zeichnen
	DELETE_OBJ (DRO);

	return true;

} // DrawLine


// --------------------------------------------------------------------------------------------
// Linie mit den DB-Punkten AP und EP auf dem Bildschirm zeichnen
bool _GEOMETR_EXPORT DrawLine (EPunkt& AP, EPunkt& EP, bool bKipp, pWindow pW)
{
Point APt = BSKoordinaten (AP.X(), AP.Y(), bKipp);
Point EPt = BSKoordinaten (EP.X(), EP.Y(), bKipp);

	return DrawLine (APt, EPt, pW);

} // DrawLine


// --------------------------------------------------------------------------------------------
// Polygon mit dem KoOrd-Vektor plXK,plYK der Länge lAnz auf dem Bildschirm zeichnen;
// für bKipp == true sind die y-Koordinaten vorher an der Bildschirmhöhe zu kippen, der
// Referenzpunkt RefPkt kann für Objekte verwendet werden, die von CPolygonObject abgeleitet
// werden
bool _GEOMETR_EXPORT DrawPolygon (EPunkt& RefPkt, KoOrd* plXK, KoOrd* plYK, long lAnz,
								  bool bKipp, pWindow pW)
{
	_ASSERTE (plXK != 0);
	_ASSERTE (plYK != 0);

	if (!plXK || !plYK) return false;

Point Pt;
Point* pPoly = new Point [lAnz];

	if (! pPoly)
	{
		DEX_Error (RC_zeichnen, EC_NOMEMORY);
		return false;
	}

	for (long i = 0; i < lAnz; i++)
		pPoly[i] = BSKoordinaten (plXK[i], plYK[i], bKipp);

Point ptRef = BSKoordinaten (RefPkt.X(), RefPkt.Y(), bKipp);
Pen P (SolidLine, 1, Color(BLACK));
CPolygonObject* pCPO = new CPolygonObject (ptRef, pPoly, lAnz, &P);

	if (! pCPO)
	{
		DEX_Error (RC_zeichnen, EC_NOMEMORY);
		return false;
	}

	pCPO->ChangeRop (ROP_Invert);	// das von pCPO überzeichnete Gebiet wird invertiert
	pW->Draw (pCPO);				// Polygonobjekt zeichnen

	DELETE_OBJ (pCPO);
	DELETE_VEC (pPoly);

	return true;

} // DrawPolygon


// --------------------------------------------------------------------------------------------
// mehrere Polygone auf dem Bildschirm zeichnen;
// die DB-Koordinaten sind in den Vektoren plXK und plYK der Länge lAnz enthalten, die
// Länge der einzelnen Polygone ist in piPolyCounts ausgewiesen, für bKipp == true sind die
// y-Koordinaten vorher an der Bildschirmhöhe zu kippen, der Referenzpunkt RefPkt kann für
// Objekte verwendet werden, die von CPolygonObject abgeleitet werden
bool _GEOMETR_EXPORT DrawPolyPolygon (EPunkt& RefPkt, KoOrd* plXK, KoOrd* plYK,
									const int* piPolyCounts, long lAnz, bool bKipp, pWindow pW)
{
	_ASSERTE (plXK != 0);
	_ASSERTE (plYK != 0);
	_ASSERTE (piPolyCounts != 0);

	if (!plXK || !plYK || !piPolyCounts) return false;

Point Pt;
Point* pPolyPoly = new Point [lAnz];

	if (! pPolyPoly)
	{
		DEX_Error (RC_zeichnen, EC_NOMEMORY);
		return false;
	}

	for (long i = 0; i < lAnz; i++)
		pPolyPoly[i] = BSKoordinaten (plXK[i], plYK[i], bKipp);

Point ptRef = BSKoordinaten (RefPkt.X(), RefPkt.Y(), bKipp);
Pen P (SolidLine, 1, Color(BLACK));
CPolyPolygonObject* pCPPO = new CPolyPolygonObject (ptRef, pPolyPoly, piPolyCounts, lAnz, &P);

	if (! pCPPO)
	{
		DEX_Error (RC_zeichnen, EC_NOMEMORY);
		return false;
	}

	pCPPO->ChangeRop (ROP_Invert);	// das von pCPPO überzeichnete Gebiet wird invertiert
	pW->Draw (pCPPO);				// alle Polygonobjekte zeichnen

	DELETE_OBJ (pCPPO);
	DELETE_VEC (pPolyPoly);

	return true;
} // DrawPolyPolygon


// --------------------------------------------------------------------------------------------
// Kante komplett auf dem Bildschirm neuzeichnen
void _GEOMETR_EXPORT KanteNeuZeichnen (EKante* pK, pWindow pW)
{
	_ASSERTE (pK != 0);

long lA = pK->ASP ();
EPunkt EP1;
EPunkt EP2 = pK->SP(lA-1);

	while (lA > 1)
	{
		EP1 = EP2;
		EP2 = pK->SP(lA-2);
		DrawLine (EP2, EP1, false, pW);
		lA--;
	}
} // KanteNeuZeichnen


// --------------------------------------------------------------------------------------------
// Polygon plXK/plYK der Länge lAnz vom Anfangsindex lAnfInd auf dem Bildschirm neu zeichnen
void _GEOMETR_EXPORT KanteNeuZeichnen (KoOrd* plXK, KoOrd* plYK, long lAnfInd, long lAnz,
									   pWindow pW)
{
	_ASSERTE (plXK != 0);
	_ASSERTE (plYK != 0);
/*
long lA = lAnfInd + lAnz - 1;
EPunkt EP1, EP2;		// Startwerte für die while-Schleife

	EP2.X() = plXK[lA];
	EP2.Y() = plYK[lA];

	while (lA >= 1)
	{
		EP1.X() = EP2.X();
		EP1.Y() = EP2.Y();
		EP2.X() = plXK[lA-1];
		EP2.Y() = plYK[lA-1];
		DrawLine (EP2, EP1, false, pW);
		lA--;
	}
*/
long lA = lAnfInd;
EPunkt EP1, EP2;	// Endpunkte für DrawLine()

	EP2.X() = plXK[lA];
	EP2.Y() = plYK[lA];

	while (lAnz >= 2)
	{
		EP1.X() = EP2.X();
		EP1.Y() = EP2.Y();
		EP2.X() = plXK[lA+1];
		EP2.Y() = plYK[lA+1];
		DrawLine (EP2, EP1, false, pW);
		lA++;
		lAnz--;
	}
} // KanteNeuZeichnen


// --------------------------------------------------------------------------------------------
// temporäres pIOG-Objekt auf dem Bildschirm neu zeichnen;
// return-Wert:
//	true:	es wurde gezeichnet
//	false:	es wurde nicht gezeichnet
bool _GEOMETR_EXPORT DrawTemporaryObject (IObjektGeometrie* pIOG, pWindow pW)
{
	if (! pIOG) return false;

short iOT;
long lCnt;

	pIOG->GetObjTyp (&iOT);
    pIOG->GetCnt (&lCnt);

	if ((OT_KANTE != iOT && OT_FLAECHE != iOT) || lCnt < 2)
		return false;

KoOrd* plXK; KoOrd* plYK;

    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

	if (OT_KANTE == iOT)
		KanteNeuZeichnen (plXK, plYK, 0, lCnt, pW);
	else
	{
	short iKCnt;
	long* plCnt;

		pIOG->GetKCnt (&iKCnt);
		pIOG->GetLPCnt (&plCnt);

	long lAInd = 0;		// 1. Index der i-ten Kontur

		for (int i = 0; i < iKCnt; i++)
		{
			if (i > 0) lAInd += plCnt[i-1];
			KanteNeuZeichnen (plXK, plYK, lAInd, plCnt[i], pW);
		}
	}

	return true;

} // DrawTemporaryObject


// --------------------------------------------------------------------------------------------
// Größe eines Punktsymbols in BS-Pixel ermitteln; Rückgabe in iPixX bzw. iPixY
void _GEOMETR_EXPORT PointSymbolSize (ulong ulIdent, int& iPixX, int& iPixY)
{
double dQuot = 1.;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	if (!DEX_GetActiveScaling (dQuot))
		dQuot = 1.;

	if (dQuot > 0)
		dQuot *= 100.;	
	else
	{
		_ASSERTE (dQuot > 0);
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}

Point PLO, PRU;	// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) des umschreibenden
				//  Rechtecks des Punktsymbols
HANDLEVISINFO HVI;

	INITSTRUCT (HVI, HANDLEVISINFO);	// Initialisierung
	HVI.m_lIdent = ulIdent;				// Identifikator
	HVI.m_pDesc = 0;					// beschreibender Text
	HVI.m_pView = 0;					// SichtName (aktuelle Sicht: 0)

PVISINFO PVI;
SIZE sizePG;
				
	HVI.m_iVTyp = VTPunkt;				// VisInfoTyp
	HVI.m_pVI = &(PVI.m_VI);			// generischer Pointer auf VisInfo

	if (! DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
	{
		sizePG.cx = DEF_SIZE_PUNKT_X;
		sizePG.cy = DEF_SIZE_PUNKT_Y;
	}
	else
		sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)

// Größe des Punktsymbols in BS-Pixel in x- bzw. y-Richtung
Dimension dimDots = GetDotsPerMM (0);	// Pixel pro Millimeter für den Bildschirm

	iPixX = (int) (sizePG.cx * dimDots.Width() / dQuot);
	iPixY = (int) (sizePG.cy * dimDots.Height() / dQuot);

} // PointSymbolSize


// --------------------------------------------------------------------------------------------
// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster
Dimension _GEOMETR_EXPORT GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
Dimension dimD (0, 0);

	if (hDC)
		hDCloc = hDC;
	else
		hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc))
	{
		default:		// MM_ANISOTROPIC/MM_ISOTROPIC
		case MM_TEXT:	// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);	// Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);	// Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);		// Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);		// Höhe in Dots

			dimD = Dimension (HorzRes/HorzSize, VertRes/VertSize);
		}
			break;

		case MM_HIMETRIC:	// [0.01 mm]
			dimD = Dimension (100, 100);
			break;
		
		case MM_LOMETRIC:	// [0.1 mm]
			dimD = Dimension (10, 10);
			break;
		
		case MM_HIENGLISH:	// [0.001 inch]
			dimD = Dimension (40, 40);
			break;
		
		case MM_LOENGLISH:	// [0.01 inch]
			dimD = Dimension (4, 4);
			break;
		
		case MM_TWIPS:
			dimD = Dimension (57, 57);
			break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == 0)
		ReleaseDC (0, hDCloc);

	return dimD;
} // GetDotsPerMM


// --------------------------------------------------------------------------------------------
// Anzahl der Pixel in beiden Koordinatenrichtungen für aktuellen Bildschirm
Dimension _GEOMETR_EXPORT GetDots (HDC hDC)
{
HDC hDCloc;

	if (hDC)
		hDCloc = hDC;
	else
		hDCloc = GetDC (GetDesktopWindow());

int HorzRes = GetDeviceCaps (hDCloc, HORZRES);		// Breite in Dots
int VertRes = GetDeviceCaps (hDCloc, VERTRES);		// Höhe in Dots

// DC bei Bedarf wieder freigeben
	if (hDC == 0)
		ReleaseDC (0, hDCloc);

	return Dimension (HorzRes, VertRes);
} // GetDots
