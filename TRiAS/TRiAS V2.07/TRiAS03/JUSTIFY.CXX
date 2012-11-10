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
// benötigte Höhe für den gegebenen Text berechnet. Ansonsten wird der
// gegebene Rechtecksbereich maximal ausgefüllt. 
// Wenn prc -> right nicht gegeben ist (== prc -> left), dann wird die
// benötigte Breite für den gegebenen Text berechnet.
// Gezeichnet wird nur dann, wenn keine diesbezüglichen Berechnungen 
// gefordert sind.
// Geliefert wird in jedem Fall die Höhe einer Zeile.
// Wenn nur ein Wort auf einer Zeile ist, und dieses zu lang ist, dann
// wird in keinem Fall gezeichnet und immer die rechte Seite berechnet.

const double PI =  3.14159265359;

char *CodeChars (const char *lpText, bool &fTabs);

CoOrd Justify (HDC hdc, HDC hTargetDC, 
	       const char *lpOutText, POINT *pPtRef, RECT *prc,
	       AlignType nAlign, bool fToDraw, short *piLineCnt, short iEsc)	// JG Parameter iEsc
{
// double Berechnungen durchführen
double dCos = 1;
double dSin = 0;

	if (0 != iEsc)
	{
		dCos = cos(-iEsc * PI / 1800.0);	// aus irgendwelchen Gründen kommt der Drehwinkel mit vertauschtem Vorzeichen
		dSin = sin(-iEsc * PI / 1800.0);
	}

// BaseLineStyle herausfiltern
bool fBaseLine = (nAlign & ATBaseLine) ? true : false;

	nAlign = (AlignType)(nAlign & ~ATBaseLine);

bool fTabbed = false;	// variablen für Tabs
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
bool fToLong = false;	// ein Wort länger als Zeile

// wenn rechter Rand berechnet werden soll, dann nur linksbündige Ausgabe möglich
	if (fCalcX) nAlign = ATLeft;

// wenn Höhe oder Breite berechnet werden sollen, dann nichts zeichnen
	if (fCalcX && fCalcY) fToDraw = false;

	double ptZeilenRefY = 0;
	double ptZeilenRefX = 0;

	if (NULL != pPtRef)
	{
		ptZeilenRefY = pPtRef -> y;
		ptZeilenRefX = pPtRef -> x;
	}
	else
	{
		ptZeilenRefY = prc -> top;

		switch (nAlign) {	// geforderte Ausrichtung
		case ATRight:	// rechtsbündig
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
	
// wenn TargetDC nicht gegeben, dann gleich ZielDC setzen
	if (hTargetDC == 0) hTargetDC = hdc;
	
	if (fTabbed) {	// Tabs aller 2 Zeichen des aktuellen Fonts setzen
	TEXTMETRIC tm;
	
		GetTextMetrics (hTargetDC, &tm);
		iTabs = 1;
		nTabs = 2*tm.tmAveCharWidth;
	}

// TextAlign global über alles setzen	
UINT uiT = SetTextAlign (hdc, fBaseLine ? TA_BASELINE|TA_LEFT : TA_BOTTOM|TA_LEFT);
		
// für jede TextZeile
	do {
		fToLong = false;	// Anfang der Zeile, Flags rücksetzen

		nBreakCount = 0;
		nWordCount = 0;
		
		while (*lpText == ' ')	// führende Blanks überspringen
			lpText++;

		if (*lpText == '\0') {
			if (iLines == 0) {
				if (lpFree) delete lpFree;
				SetTextAlign (hdc, uiT);	// TextAlign rücksetzen
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
			
		// Worte auf der Zeile Zählen
			if (*(lpText -1) != ' ')
				nWordCount++;		// nur bei erstem Blank 
				
		// nach jedem Wort die TextGröße bestimmen
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
				fCalcX = true;	// wenn ein Wort länger als 
		}				// gesamte Zeile ist, dann berechnen

	// Abschließende Blanks entfernen
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

		// nächste Zeile
		if (iLines == 0) 		// nur in der ersten Zeile 
		{
			iLineHeight = szExtent.cy;
		}	

		// Bezugspunkt der nächsten Zeile berechnen
		if (iLines || NULL == pPtRef)
		{
			ptZeilenRefY -=  dCos * iLineHeight;
			ptZeilenRefX +=  dSin * iLineHeight;
		}

		yDrawStart = CoOrd(ptZeilenRefY + 0.5);	// Zeilenreferenzpunkt 
		xDrawStart = CoOrd(ptZeilenRefX + 0.5);

		switch (nAlign) {	// geforderte Ausrichtung
		case ATLeft:	// linksbündig
			if (fTabbed)
				xDrawStart = prc -> left;	// hier evtl. auch noch auf pPtRef beziehen
//			else				
//				xStart = (pPtRef != NULL) ? pPtRef -> x : prc -> left;
			break;

		case ATRight:	// rechtsbündig
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
			SetTextAlign (hdc, uiT);	// TextAlign rücksetzen
			return -1;	// Fehler
		}

		if (iLines || pPtRef == NULL)	// auch für die erste Zeile
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
		lpText = lpEnd;			// Anfang der nächsten Zeile
	} while (*lpText && (fCalcY || yStart > prc -> bottom));

	if (fCalcY) prc -> bottom = yStart;
	if (fCalcX) prc -> right = xEnd;
	
	if (lpFree) delete lpFree;
	
// wenn gewünscht, Anzahl der Zeilen liefern
	if (piLineCnt) *piLineCnt = iLines;

	SetTextAlign (hdc, uiT);	// TextAlign rücksetzen
	
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
