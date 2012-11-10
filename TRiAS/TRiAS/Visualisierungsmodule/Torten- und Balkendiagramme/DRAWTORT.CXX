// Zeichnen eines Tortendiagrammes --------------------------------------------
// File DRAWTORT.CXX

#include "tortenp.hxx"

#include <resstrg.h>

#include <icustom.hxx>

#include "impcustm.hxx"
#include "paltree.hxx"
#include "fixupdc.hxx"

#include "torten.h"

extern "C" LPSTR FAR PASCAL DtoAVMD (LPSTR String, LPSTR Format, double Wert);

inline bool operator ^ (RECT &rc1, RECT &rc2)
{
	return !((rc1.left > rc2.right) || (rc1.right < rc2.left) ||
			 (rc1.bottom > rc2.top) || (rc1.top < rc2.bottom));
}

BOOL CTortenVisModule::DrawTorte (
	VisInfo *pVI, HDC hDC, HDC hTargetDC, POINT ptPoint, SIZE szSize, 
	int iSectors, long *pSectors, char **ppMWerte)
{
int iType = pVI -> Style();		// DiagrammTyp
int fTempPal = false;
CVisPalette *pVPal = DefinitelyGetPalette (pVI, fTempPal);

	if (NULL == pVPal) 
		return false;

// ZwischenSummen berechnen
long lTmp = pSectors[0];

	pSectors[0] = 0;
	for (int i = 1; i <= iSectors; i++) {
	long lSwap = pSectors[i];
	
		pSectors[i] = pSectors[i-1] + lTmp;
		lTmp = lSwap;
	}

// Sinnfälligkeit prüfen
	if (pSectors[iSectors] == 0 || szSize.cx == 0 || szSize.cy == 0) 
	    	return false;	// keine Daten gegeben, oder Größe ist Null
		
// sonstige HilfsVariablen initialisieren
CoOrd iLeft = ptPoint.x - szSize.cx;	// äußere Abmessungen des Diagrammes
CoOrd iRight = ptPoint.x + szSize.cx;
CoOrd iTop = ptPoint.y - szSize.cy;
CoOrd iBottom = ptPoint.y + szSize.cy;
double dISum = PI / double (pSectors[iSectors]);
double dPi = PI;
double dArcOffset = 0.0;
CoOrd dY = 0;

// typspezifische Korrekturen
	switch (iType & TORTEN_TYPEMASK) {
	case TORTEN_FULLCIRCLE:
		dISum *= 2.0;		// 2*PI
		dPi *= 2.0;
		break;
		
	case TORTEN_UPPERHALF:	// obere KreisHälfte
		if (iType & TORTEN_OFFSET) {
			dY = szSize.cy / 10;	// ein Stück nach oben verschieben
			iTop += dY;
			iBottom += dY;
		}
		break;
		
	case TORTEN_LOWERHALF:
		dArcOffset = PI;	// untere KreisHälfte
		if (iType & TORTEN_OFFSET) {
			dY = -szSize.cy / 10;	// einStück nach unten verschieben   
			iTop += dY;
			iBottom += dY;
		}
		break;
	}
		
// wenn Texte angezeigt werden sollen, dann Font generieren
pFont pF = NULL;
HFONT hOFont = 0;
UINT uiT = 0;	// bisheriges TextAlign

	if ((iType & (TORTEN_TEXTSREL|TORTEN_TEXTSABS)) && szSize.cy > 10) {
	int iFSize = (iType & TORTEN_BIGFONT) ? szSize.cy/3 : szSize.cy/5;
	ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		pF = new CVFont (Swiss, Dimension (0, -iFSize), rsArial);
#else
		pF = new Font (Swiss, Dimension (0, -iFSize), rsArial);
#endif //!defined(_TRIAS_OLDIMPLEMENTATION2)
		if (NULL == pF) 
			iType &= ~(TORTEN_TEXTSREL|TORTEN_TEXTSABS);
		else {
			pF -> Init();		// Font laden
			hOFont = (HFONT)SelectObject (hDC, pF -> Handle (API_FONT_HFONT));
			uiT = SetTextAlign (hDC, TA_BOTTOM|TA_LEFT);
		}
	}

// KreisSektoren/Texte ausgeben 
CoOrd x1 = ptPoint.x - (CoOrd)(8000 * cos (dArcOffset));
CoOrd y1 = ptPoint.y + (CoOrd)(8000 * sin (dArcOffset));
CoOrd x2, y2;
SIZE szExt;		// TextGröße des aktuellen Textes
RECT rcExt;		// TextGröße des vorherigen Textes
HBRUSH hBr, hOldBr;
char cbFormat[10];

	if (pVPal -> GetNumDigits() >= 0)
		wsprintf (cbFormat, "%%%d.%df", pVPal -> GetNumDigits() +4, pVPal -> GetNumDigits());
	else
		strcpy (cbFormat, "%5.1f");

	SetRect (&rcExt, 0, 0, 0, 0);		// initialisieren
	for (i = 1; i <= iSectors; i++) {
		x2 = ptPoint.x - (CoOrd)(8000 * cos (pSectors[i] * dISum + dArcOffset));
		y2 = ptPoint.y + (CoOrd)(8000 * sin (pSectors[i] * dISum + dArcOffset));
		
	// TortenStück malen
			// ein Segment belegt optisch 100% 								oder sowieso bloß ein Segment
		if ((((x1 == x2) && (y1 == y2) && ((pSectors[i] - pSectors[i-1]) * dISum > PI * 3 / 2)) || (iSectors == 1)) 
				&& ((iType & TORTEN_TYPEMASK) == TORTEN_FULLCIRCLE))	// Vollkreis??
		{	
		// nur einen Kreis malen
			if (iSectors == 1) {
				hBr = CreateSolidBrush ((COLORREF &)(pVI -> PrimColor()));
				hOldBr = (HBRUSH)SelectObject (hDC, hBr);

				Ellipse (hDC, iLeft, iTop, iRight, iBottom);

				SelectObject (hDC, hOldBr);
				DeleteObject (hBr);
			} 
			else {
			FVisInfo *pFVI = pVPal -> GetFVisInfo ((i-1) % MAXPIECOLORS);
			
				if (pFVI == NULL) return false;

			CFixupDC dcT (hDC, fTempPal ? NULL : m_hPal, pFVI);

				Ellipse (hDC, iLeft, iTop, iRight, iBottom);

				DELETE_OBJ (pFVI);
			}
		} 
		else if (x1 != x2 || y1 != y2) {
			if (iSectors == 1) {
				hBr = CreateSolidBrush ((COLORREF &)(pVI -> PrimColor()));
				hOldBr = (HBRUSH)SelectObject (hDC, hBr);
				Pie (hDC, 
				     iLeft, iTop, iRight, iBottom, 
				     x2, y2+dY, x1, y1+dY);		// Segment zeichnen
				SelectObject (hDC, hOldBr);		// hDC zurücksetzen
				DeleteObject (hBr);
			} 
			else {
			FVisInfo *pFVI = pVPal -> GetFVisInfo ((i-1) % MAXPIECOLORS);
			
				if (pFVI == NULL) return false;

			CFixupDC dcT (hDC, fTempPal ? NULL : m_hPal, pFVI);

				Pie (hDC, 
				     iLeft, iTop, iRight, iBottom, 
				     x2, y2+dY, x1, y1+dY);		// Segment zeichnen

				DELETE_OBJ (pFVI);
			}
		}

	// evtl. Texte anzeigen, wenn diese sinnvoll zu sehen sind
		if (pF) {
		double dArc = long((pSectors[i]+pSectors[i-1])/2) * dISum + dArcOffset;
		int iLen = 0;
		RECT rcT;
		double dSourceArc = dArc;	// JG990615 zum feststellen ob bereits um mehr als 360 Grad gedreht wurde speichern wir uns den Ursprungswinkel

			if (iType & TORTEN_TEXTSABS) {
			// Merkmale ausgeben: Position berechnen
				GetTextExtentPoint (hTargetDC, ppMWerte[i], iLen = strlen(ppMWerte[i]), &szExt);
				do {
				CoOrd xT = ptPoint.x - (CoOrd)(szSize.cx * 1.05 * cos (dArc));
				CoOrd yT = ptPoint.y + (CoOrd)(szSize.cy * 1.05 * sin (dArc));
				
					CalcTextPosition (i, &rcT, xT, yT, dArc, szExt);	// Positionierung
					if (rcT ^ rcExt) {
						dArc += PI/180;
						if (dArc - dSourceArc > 2 * PI)	// JG990615 bereits mehr als eine Drehung?
							dArc = dSourceArc;			// dann eben den ersten Winkel nehmen
						else					
							continue;					// weiterdrehen
					} 

				// Text überlappt sich jetzt (hoffentlich) nicht mehr mit anderen
					TextOut (hDC, xT, yT+dY, ppMWerte[i], iLen);
					rcExt = rcT;		// vorheriges Rechteck
					break;				// ok weiter
				} while (true);
			} 
			else if (iType & TORTEN_TEXTSREL && *ppMWerte[i]) {
			// Prozente ausgeben
			char cbPercent[20];
			double dPercent = double(pSectors[i]-pSectors[i-1])/(pSectors[iSectors])*100;

				DtoAVMD (cbPercent, cbFormat, dPercent);
				strcat (cbPercent, "%");
				GetTextExtentPoint (hTargetDC, cbPercent, iLen = strlen(cbPercent), &szExt);

			// Text positionieren
				do {
				CoOrd xT = ptPoint.x - (CoOrd)(szSize.cx * 1.05 * cos (dArc));
				CoOrd yT = ptPoint.y + (CoOrd)(szSize.cy * 1.05 * sin (dArc));
				
					CalcTextPosition (i, &rcT, xT, yT, dArc, szExt);	// Positionierung
					if (rcT ^ rcExt) {					// wenn das aktuelle Rechteck das vorherige überlappt
						dArc += PI/180;
						if (dArc - dSourceArc > 2 * PI)	// JG990615 bereits mehr als eine Drehung?
							dArc = dSourceArc;			// dann eben den ersten Winkel nehmen
						else					
							continue;					// weiterdrehen
					} 	

				// Text überlappt sich jetzt (hoffentlich) nicht mehr mit anderen
					TextOut (hDC, xT, yT+dY, cbPercent, iLen);
					rcExt = rcT;		// vorheriges Rechteck
					break;				// ok weiter
				} while (true);
			}
		}
		x1 = x2;
		y1 = y2;
	}

	if (NULL != pF) {
		SelectObject (hDC, hOFont);
		SetTextAlign (hDC, uiT);	// zurücksetzen
	}
	DELETE_OBJ (pF);				// Font freigeben
	return true;	// ok
}   


// Textpositionierung bestimmen -----------------------------------------------
void CalcTextPosition (int i, RECT *pRc, CoOrd &xT, CoOrd &yT, double dArc, SIZE szText)
{
// vertikale Positionierung festlegen
// wenn es der erste Text ist, dann an der UnterKante orientieren
	if (i != 1) {		// unten aufhängen
		if (dArc > 9*PI/8 && dArc < 15*PI/8)
			yT -= szText.cy;	// oben aufhängen
		else if (!(dArc > PI/8 && dArc < 7*PI/8))
			yT -= szText.cy/2;	// halbe Höhe
	}
	if (i == 1 && dArc > PI)	// unterer Halbkreis
		yT -= szText.cy;		// oben aufhängen
		
// horizontale Positionierung festlegen
	if ((dArc > 13*PI/8 && dArc < 2*PI) || (dArc >= 0.0 && dArc < 3*PI/8))
		xT -= szText.cx;	// rechts aufhängen
	else if (!(dArc > 5*PI/8 && dArc < 11*PI/8))
		xT -= szText.cx/2;	// halbe Breite
	
// umschließendes Rechteck berechnen
	SetRect (pRc, xT, yT+szText.cy, xT+szText.cx, yT);
}


// Palette aus dem Baum holen, evl. StandardPalette wählen --------------------
CVisPalette *CTortenVisModule::DefinitelyGetPalette (VisInfo *pVI, BOOL &fTemp)
{
	if (m_pPalT == NULL) return NULL;	// Fehler

const char *pVName = pVI -> VisName();
ResString resDefPal (ResID (IDS_DEFAULTPALETTE, m_pRF), 40);

	return m_pPalT -> DefinitelyGetPalette (pVName, resDefPal, fTemp);
}
