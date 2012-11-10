// Zeichnen eines Balkendiagrammes --------------------------------------------
// File DRAWBALK.CXX

#include "tortenp.hxx"

#include <resstrg.h>

#include <icustom.hxx>

#include "impcustm.hxx"
#include "paltree.hxx"
#include "fixupdc.hxx"

#include "torten.h"

extern "C" bool WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);

// Zeichnen eines Balkendigrammes ---------------------------------------------
// DrawBalken geht davon aus, daß der erste Wert in pSectors der BezugsWert ist
// auf den sich die gegebene Höhe in szSize bezieht
// Ein Balken erhält als Breite 1/10 dieser Höhe
//

static double EvalScaleKoeff (long *, short);
static double GetSector (long lVal, BALKENMODE bm);

// Drehen eines Punktes -------------------------------------------------------
inline void RotatePoint (Point &ptRes, CoOrd x, CoOrd y, Point &ptRot, 
			 double dSin, double dCos)
{
	ptRes.X() = (CoOrd)( (x - ptRot.X()) * dCos + (y - ptRot.Y()) * dSin + ptRot.X() + 0.5);
	ptRes.Y() = (CoOrd)(-(x - ptRot.X()) * dSin + (y - ptRot.Y()) * dCos + ptRot.Y() + 0.5);
}

// Drehen eines Rechteckes ----------------------------------------------------
static void RotateRect (double &dSinE, double &dCosE, Point *pPts, Point &ptRot, Rectangle &Rc)
{
	RotatePoint (pPts[0], Rc.Left(), Rc.Bottom(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[1], Rc.Left(), Rc.Top(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[2], Rc.Right(), Rc.Top(), ptRot, dSinE, dCosE);
	RotatePoint (pPts[3], Rc.Right(), Rc.Bottom(), ptRot, dSinE, dCosE);
}


BOOL CTortenVisModule :: DrawBalkenHochPos (VisInfo *pVI, HDC hDC, HDC hTargetDC, 
					  POINT ptPoint, SIZE szSize, 
					  short iSectors, long *pSectors, 
					  char **ppMWerte, BALKENMODE bm)
{
short iType = pVI -> Style();
BOOL fTempPal = FALSE;
BOOL fRot = FALSE;		// rotierbares Diagramm

	if ((iType & TORTEN_TYPEMASK) == TORTEN_BALKENROT ||
	    (iType & TORTEN_TYPEMASK) == TORTEN_BALKENROTLOG)
		fRot = TRUE;

short iRotOffset = fRot ? 2 : 1;
CVisPalette *pVPal = DefinitelyGetPalette (pVI, fTempPal);
 
	if (pVPal == NULL) return FALSE;
	
// Balkenparameter berechnen
short iWidth = szSize.cx/8;	// Breite der Balken
double dKoeff = 0.0;
CoOrd iLeft = ptPoint.x;	// äußere Abmessungen des Diagrammes
CoOrd iBottom = ptPoint.y;
Point ptRot (iLeft, iBottom);	// BezugsPunkt des Diagramms
short iEsc = iWidth/5;		// ZwischenRaum zwischen den Balken
short iY = 0;			// zusätzliche Verschiebung

	if (iEsc == 0) iEsc = 1;
	if (iType & TORTEN_OFFSET) iY = szSize.cy / 10;

// Variablen berechnen, erstes Element enthält BezugsHöhe
	dKoeff = double(szSize.cy)/(GetSector (pSectors[0], bm)/* * dMax */);
	iLeft -= MulDiv (iSectors-iRotOffset, iWidth+iEsc, 2);	// Bezugspunkt unten mitte

// zweites Element enthält evtl. Drehwinkel in 1/10 Grad
double dSin = 0.0, dCos = 1.0, dRot = 0.0;

	if (fRot) {
		dRot = pSectors[1]/VALUE_SCALING;
	
	double dPhi = -(dRot - 900) * PI/1800;
			
		dSin = sin (dPhi);
		dCos = cos (dPhi);
	}
	
// wenn Texte angezeigt werden sollen, dann Font generieren
pFont pF = NULL;
HFONT hOFont = 0;
HFONT hOTFont = 0;
UINT uiT = 0;		// bisheriges TextAlign
BOOL fRotFlag = FALSE;	// Texte müssen 'gewendet' werden

	if ((iType & TORTEN_TEXTSABS) && iWidth > 5) {
	ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		pF = new CVFont (Swiss, Dimension (0, -(8*iWidth)/10), rsArial);
#else
		pF = new Font (Swiss, Dimension (0, -(8*iWidth)/10), rsArial);
#endif //!defined(_TRIAS_OLDIMPLEMENTATION2)
		if (pF == NULL) 
			iType &= ~TORTEN_TEXTSABS;
		else {
		short iRot = -900;
		
			if (fRot) {
				iRot = -short(dRot);
				while (iRot < -900) { 
					iRot += 1800; fRotFlag = TRUE; 
				}
				while (iRot > 900) { 
					iRot -= 1800; fRotFlag = TRUE; 
				}
			}
			pF -> SetEscapement (iRot);
			pF -> Init();			// Font laden
			hOFont = (HFONT)SelectObject (hDC, pF -> Handle (API_FONT_HFONT));
			hOTFont = (HFONT)SelectObject (hTargetDC, pF -> Handle (API_FONT_HFONT));
		}
		uiT = SetTextAlign (hDC, TA_BOTTOM|TA_LEFT);
	}

// bei Exponentialdarstellung zusätzliche Skalierung bestimmen, damit vertretbare
// Werte zur Darstellung kommen
// double dMax = 1.0;

//	if (bm == BMExp) dMax = EvalScaleKoeff (pSectors, iSectors);
	
// Balkendiagramme zeichnen
	for (short i = iRotOffset; i < iSectors; i++) {
	RECT rcT;
	long lSector = (long)(GetSector (pSectors[i], bm) * dKoeff) /* *dMax */;
	
		SetRect (&rcT, iLeft, short(iBottom + lSector)+iY, 
			       iLeft + iWidth, iBottom+iY);

		{	// RechtEck ausgeben				
		FVisInfo *pFVI = pVPal -> GetFVisInfo ((i-iRotOffset) % MAXPIECOLORS);
		CFixupDC dcT (hDC, fTempPal ? 0 : m_hPal, pFVI);

			if (!fRot) 
				DrawRectangle (hDC, rcT.left, rcT.top, rcT.right, rcT.bottom);
			else {
			// gedrehtes Rechteck ausgeben
			Point pts[4];
			
				RotateRect (dSin, dCos, pts, ptRot, (Rectangle &)rcT);
				Polygon (hDC, (POINT *)pts, 4);				
			}
			DELETE_OBJ (pFVI);
		} 	iLeft += iWidth + iEsc;		// nächste Säule

	// evtl. Texte anzeigen, wenn diese sinnvoll zu sehen sind
	// Merkmale ausgeben: Position berechnen
		if (pF) {
		SIZE szText;
		int iLen = strlen(ppMWerte[i+1]);
		
			GetTextExtentPoint (hTargetDC, ppMWerte[i+1], iLen, &szText);

		Point pt (0, 0);
		CoOrd iX = rcT.left + iWidth/2 + szText.cy/2;
		CoOrd iY;
		
			if (lSector >= 0)
				iY = rcT.top + szSize.cy/20;
			else
				iY = rcT.top - szSize.cy/20 - szText.cx;
		
			if (fRotFlag) {		// Text 'wenden'
				iX -= szText.cy;
				iY += szText.cx;
			}
			RotatePoint (pt, iX, iY, ptRot, dSin, dCos);
			TextOut (hDC, pt.X(), pt.Y(), ppMWerte[i+1], iLen);
		}
	}

// GrundLinie zeichnen
	if (!fRot) {
		MoveToEx (hDC, iLeft+iWidth-iEsc, iBottom+iY, NULL);
		LineTo (hDC, iLeft - (iSectors-iRotOffset)*(iWidth+iEsc) - iWidth, 
			iBottom+iY);
	} else {
	Point pt (0, 0);
	
		RotatePoint (pt, iLeft+iWidth-iEsc, iBottom+iY, 
			     ptRot, dSin, dCos);
		MoveToEx (hDC, pt.X(), pt.Y(), NULL);
		RotatePoint (pt, iLeft - (iSectors-iRotOffset)*(iWidth+iEsc) - iWidth, 
			     iBottom+iY, ptRot, dSin, dCos);
		LineTo (hDC, pt.X(), pt.Y());
	}
			
// Aufräumen
	if (pF) {
		SelectObject (hDC, hOFont);
		SelectObject (hTargetDC, hOTFont);
		SetTextAlign (hDC, uiT);		// zurücksetzen
	}

	DELETE_OBJ (pF);				// Font freigeben
	
return TRUE;	// ok
}


static double EvalScaleKoeff (long *pSectors, short iSectors)
{
double dMax = -HUGE_VAL;

	for (short i = 0; i < iSectors; i++) {
	double dCurr = GetSector (pSectors[i], BMExp);
	
		dMax = __max (dMax, dCurr);
	}
	if (dMax < 0) return SHRT_MIN/dMax;

return SHRT_MAX/dMax;
}


static double GetSector (long lVal, BALKENMODE bm)
{
	switch (bm) {		// konkreten BalkenMode auswerten
	case BMLog:
		return double(VALUE_SCALING * logl(double(fabs(double(lVal))+1)/VALUE_SCALING));
			
	case BMExp:
		return double(VALUE_SCALING * expl(double(lVal)/VALUE_SCALING));
			
	case BMNormal:		// nur skalieren
	default:
		break;
	}

return double(lVal);
}


