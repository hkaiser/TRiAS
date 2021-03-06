// Ausrichten eines beliebigen Textes innerhalb eines gegebenen Rechtecks -----
// File: JUSTIFY.CXX

//JG
//
#include "trias03p.hxx"
// #include "triaspre.hxx"		// pch changed
#include <math.h>

#include <funcs03.h>

#if defined(WIN32)	// neue Funktion in WIN32
#undef GetTextExtentPoint
#define GetTextExtentPoint	GetTextExtentPoint32
#endif // WIN32

// Wenn prc -> bottom nicht gegeben ist (== prc -> top), dann wird die 
// ben�tigte H�he f�r den gegebenen Text berechnet. Ansonsten wird der
// gegebene Rechtecksbereich maximal ausgef�llt. 
// Wenn prc -> right nicht gegeben ist (== prc -> left), dann wird die
// ben�tigte Breite f�r den gegebenen Text berechnet.
// Gezeichnet wird nur dann, wenn keine diesbez�glichen Berechnungen 
// gefordert sind.
// Geliefert wird in jedem Fall die H�he einer Zeile.
// Wenn nur ein Wort auf einer Zeile ist, und dieses zu lang ist, dann
// wird in keinem Fall gezeichnet und immer die rechte Seite berechnet.

const double PI =  3.14159265359;

char *CodeChars (const char *lpText, bool &fTabs);

CoOrd Justify (HDC hdc, HDC hTargetDC, 
	       const char *lpOutText, POINT *pPtRef, RECT *prc,
	       AlignType nAlign, bool fToDraw, short *piLineCnt, short iEsc)	// JG Parameter iEsc
{
// double Berechnungen durchf�hren
double dCos = 1.0;
double dSin = 0.0;

	if (0 != iEsc) {
		dCos = cos(-iEsc * PI / 1800.0);	// aus irgendwelchen Gr�nden kommt der Drehwinkel mit vertauschtem Vorzeichen
		dSin = sin(-iEsc * PI / 1800.0);
	}

// BaseLineStyle herausfiltern
bool fBaseLine = (nAlign & ATBaseLine) ? true : false;

	nAlign = (AlignType)(nAlign & ~ATBaseLine);

bool fTabbed = false;	// variablen f�r Tabs
int iTabs = 0;
int nTabs = 0;

// Text umkopieren, Sonderzeichen kodieren
const char *lpText = CodeChars (lpOutText, fTabbed);
char *lpFree = (char *)lpText;

	if (lpText == NULL) lpText = lpOutText;		// Speicherfehler
	
SIZE szExtent;
const char *lpBegin, *lpEnd;
CoOrd xDrawStart, yDrawStart, yStart, xEnd, nBreakCount, nWordCount;
CoOrd iLineHeight = 0;
short iLines = 0;
bool fCalcY = (prc -> top == prc -> bottom);
bool fCalcX = (prc -> left == prc -> right);
bool fToLong = false;	// ein Wort l�nger als Zeile

// wenn rechter Rand berechnet werden soll, dann nur linksb�ndige Ausgabe m�glich
	if (fCalcX) nAlign = ATLeft;

// wenn H�he oder Breite berechnet werden sollen, dann nichts zeichnen
	if (fCalcX && fCalcY) fToDraw = false;

double ptZeilenRefY = 0;
double ptZeilenRefX = 0;

	if (NULL != pPtRef) {
		ptZeilenRefY = pPtRef -> y;
		ptZeilenRefX = pPtRef -> x;
	}
	else {
		ptZeilenRefY = prc -> top;
		switch (nAlign) {	// geforderte Ausrichtung
		case ATRight:	// rechtsb�ndig
			ptZeilenRefX = prc -> right;
			break;
			
		case ATCentre:	// zentriert
			ptZeilenRefX = (prc -> right + prc -> left) / 2;
			break;
			
		default:		// Blocksatz, Linksausrichtung etc.
			ptZeilenRefX = prc -> left;
			break;
		}
	}

	yStart = (pPtRef != NULL) ? pPtRef -> y : prc -> top;
	xEnd = prc -> left;
	
// TextAlign global �ber alles setzen	
UINT uiT = SetTextAlign (hdc, fBaseLine ? TA_BASELINE|TA_LEFT : TA_BOTTOM|TA_LEFT);
		
// wenn TargetDC nicht gegeben, dann gleich ZielDC setzen
HFONT hTargetFont = NULL;
UINT uiTargetT = 0;

	if (NULL == hTargetDC) 
		hTargetDC = hdc;
	else if (hTargetDC != hdc) {
	HFONT hFont = (HFONT)SelectObject(hdc, GetStockObject(SYSTEM_FONT));

		SelectObject (hdc, hFont);			// wieder selektieren
		hTargetFont = (HFONT)SelectObject (hTargetDC, hFont);
		uiTargetT = SetTextAlign (hTargetDC, fBaseLine ? TA_BASELINE|TA_LEFT : TA_BOTTOM|TA_LEFT);
	}
	
	if (fTabbed) {	// Tabs aller 2 Zeichen des aktuellen Fonts setzen
	TEXTMETRIC tm;
	
		GetTextMetrics (hTargetDC, &tm);
		iTabs = 1;
		nTabs = 2*tm.tmAveCharWidth;
	}

// f�r jede TextZeile
	do {
		fToLong = false;	// Anfang der Zeile, Flags r�cksetzen

		nBreakCount = 0;
		nWordCount = 0;
		
		while (*lpText == ' ')	// f�hrende Blanks �berspringen
			lpText++;

		if (*lpText == '\0') {
			if (iLines == 0) {
				if (lpFree) delete lpFree;
				SetTextAlign (hdc, uiT);	// TextAlign r�cksetzen
				if (NULL != hTargetFont) {
					SetTextAlign (hTargetDC, uiTargetT);
					SelectObject (hTargetDC, hTargetFont);
				}
				return -1;	// abbrechen: kein Text
			} else
				break; 		// TextEnde mit Leerzeichen
		}
			
		lpBegin = lpText;	// AnfangsInitialisierung
		lpEnd = lpText;

	// Zeile zusammenstellen
		do {
		bool fBreak = false;
		
		// Worte isolieren
			while (*lpText != '\0' && *lpText != ' ') {
				if (*lpText == '\n') {
					*(char *)lpText = ' ';
					fBreak = true;	// Zeilenende
					break;
				}
				if (*lpText == (' ' | 0x80))
					*(char *)lpText = ' ';	// hartes space
				lpText++;
			}
			
		// Worte auf der Zeile Z�hlen
			if (*(lpText -1) != ' ')
				nWordCount++;		// nur bei erstem Blank 
				
		// nach jedem Wort die TextGr��e bestimmen
		short fLineEnd = 0;	// ZeilenEndeZeichen

			if (*lpText != '\0') {
				nBreakCount++;
				lpText++;
				fLineEnd = 1;
			}
			if (lpText > lpBegin + fLineEnd) {
				SetTextJustification (hTargetDC, 0, 0);
				if (fTabbed) {
				DWORD dwExt = GetTabbedTextExtent (hTargetDC, lpBegin,
						lpText - lpBegin - fLineEnd, 
						iTabs, &nTabs);
					szExtent.cx = LOWORD (dwExt);
					szExtent.cy = HIWORD (dwExt);
				} else {
					GetTextExtentPoint (hTargetDC, lpBegin, 
						lpText - lpBegin - fLineEnd, &szExtent);
				}
			} else {
				szExtent.cx = 0;
				szExtent.cy = 0;
			}

		// Abbruchbedingung testen
			if (!fCalcX && szExtent.cx > (prc -> right - prc -> left)) {
				fToLong = true;
				break;		// Zeile zu lang oder Zeilenende
			}

			lpEnd = lpText;		// dieses Wort mitnehmen

			if (fBreak) break;	// gewollter Zeilenwechsel

			if (*lpText == '\0') 
				break;		// TextEnde erreicht
		} while (true);
		 
		nBreakCount--;

		if (nWordCount <= 1) {		// nur 1 Wort
			lpEnd = lpText;		// auf jeden Fall mitnehmen
			if (!fToDraw && fToLong)
				fCalcX = true;	// wenn ein Wort l�nger als 
		}				// gesamte Zeile ist, dann berechnen

	// Abschlie�ende Blanks entfernen
		while (*(lpEnd - 1) == ' ') {	
			lpEnd--;
			nBreakCount--;
		}

		if (lpEnd > lpBegin) {
			SetTextJustification (hdc, 0, 0);
			if (hdc != hTargetDC)
				SetTextJustification (hTargetDC, 0, 0);
			if (fTabbed) {
			DWORD dwExt = GetTabbedTextExtent (hTargetDC, lpBegin,
					lpEnd - lpBegin, iTabs, &nTabs);
				szExtent.cx = LOWORD (dwExt);
				szExtent.cy = HIWORD (dwExt);
			} else {
				GetTextExtentPoint (hTargetDC, lpBegin, 
					lpEnd - lpBegin, &szExtent);
			}
		} else {
			szExtent.cx = 0;
			szExtent.cy = 0;
		}

		if (fCalcX) 	// evtl. rechte Seite berechnen
			xEnd = max (xEnd, prc -> left + szExtent.cx);

		// n�chste Zeile
		if (0 == iLines) 		// nur in der ersten Zeile 
			iLineHeight = szExtent.cy;

		// Bezugspunkt der n�chsten Zeile berechnen
		if (0 != iLines || NULL == pPtRef) {
			ptZeilenRefY -=  dCos * iLineHeight;
			ptZeilenRefX +=  dSin * iLineHeight;
		}

		yDrawStart = CoOrd(ptZeilenRefY + 0.5);	// Zeilenreferenzpunkt 
		xDrawStart = CoOrd(ptZeilenRefX + 0.5);

		switch (nAlign) {	// geforderte Ausrichtung
		case ATLeft:	// linksb�ndig
			if (fTabbed)
				xDrawStart = prc -> left;	// hier evtl. auch noch auf pPtRef beziehen
//			else				
//				xStart = (pPtRef != NULL) ? pPtRef -> x : prc -> left;
			break;

		case ATRight:	// rechtsb�ndig
//			xStart = prc -> right - szExtent.cx;
			{
				xDrawStart -= CoOrd((dCos * szExtent.cx) + 0.5);
				yDrawStart -= CoOrd((dSin * szExtent.cx) + 0.5);
			}
			break;

		case ATCentre:	// zentriert
//			xStart = (prc -> right + prc -> left - szExtent.cx) / 2;
			{
				xDrawStart -= CoOrd((dCos * (szExtent.cx / 2)) + 0.5);
				yDrawStart -= CoOrd((dSin * (szExtent.cx / 2)) + 0.5);
			}
			break;

		case ATJust:	// Blocksatz
			if (*lpText != '\0' && nBreakCount > 0) {
				SetTextJustification (hdc,
					prc -> right - prc -> left - szExtent.cx,
					nBreakCount);
			}
//			xStart = prc -> left;
			break;

		default:
			if (lpFree) delete lpFree;
			SetTextAlign (hdc, uiT);	// TextAlign r�cksetzen
			if (NULL != hTargetFont) {
				SetTextAlign (hTargetDC, uiTargetT);
				SelectObject (hTargetDC, hTargetFont);
			}
			return -1;	// Fehler
		}

		if (iLines || pPtRef == NULL)	// auch f�r die erste Zeile
		{
			yStart	-= iLineHeight;
		}

		if (fToDraw && lpEnd > lpBegin) {
			if (fTabbed) {
				TabbedTextOut (hdc, xDrawStart, yDrawStart, 
					lpBegin, lpEnd - lpBegin, 
					iTabs, &nTabs, (pPtRef != NULL) ? pPtRef -> x : xDrawStart);
			} else {
				TextOut (hdc, xDrawStart, yDrawStart, 
					lpBegin, lpEnd - lpBegin);

			}
		}

		iLines++;
		lpText = lpEnd;			// Anfang der n�chsten Zeile
	} while (*lpText && (fCalcY || yStart > prc -> bottom));

	if (fCalcY) prc -> bottom = yStart;
	if (fCalcX) prc -> right = xEnd;
	
	if (lpFree) delete lpFree;
	
// wenn gew�nscht, Anzahl der Zeilen liefern
	if (piLineCnt) *piLineCnt = iLines;

	SetTextAlign (hdc, uiT);	// TextAlign r�cksetzen
	if (NULL != hTargetFont) {
		SetTextAlign (hTargetDC, uiTargetT);
		SelectObject (hTargetDC, hTargetFont);
	}
	return iLineHeight;
}


// Kodiert diverse spezielle Zeichen um und merkt sich, ob ein Tabs in der
// ZeichenKette war
char *CodeChars (const char *lpText, bool &fTabs)
{
char *lpRes = new char [strlen (lpText) +1];
char *lpResult = lpRes;

	if (lpResult) {
		while (*lpText) {
			if (*lpText == '\\') {
				switch (*++lpText) {
				case ' ':	// Leerzeichen aber kein Wortende
					*lpResult++ = char(*lpText++ | 0x80);
					break;
					
				case 'n':	// Zeilenumbruch
					*lpResult++ = '\n';
					lpText++;
					break;
					
				case 'r':	// Zeilenumbruch
					*lpResult++ = '\r';
					lpText++;
					break;
					
				case 't':
					*lpResult++ = '\t';
					lpText++;
					fTabs = true;
					break;
					
				case '\0':	// Satzende
					*lpResult = '\0';
					return lpRes;
					
				default:	// keine Sonderbedeutung
					*lpResult++ = *lpText++;
					break;
				}
			} else if ((*lpResult++ = *lpText++) == '\t')
				fTabs = true;
//			else if ((*lpResult++ = *lpText++) == '\r' && *lpText != '\n')
//				*(lpResult-1) = '\n';	// einzelnes '\r' austauschen
		}
	}
	*lpResult = '\0';

return lpRes;
}
