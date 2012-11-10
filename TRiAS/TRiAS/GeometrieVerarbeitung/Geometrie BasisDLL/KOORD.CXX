// Funktionen für Koordinatentransformationen
// File: KOORD.CXX
// W. Mörtl


#include "GeometrP.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


        
///////////////////////////////////////////////////////////////////////////////////////////////
extern HWND __hWndM;
extern UINT __DexxCmd;
extern UINT __DexCmd;
extern "C" char pDLLName [_MAX_PATH];



///////////////////////////////////////////////////////////////////////////////////////////////
// aus dem LPARAM-Wert der WindowsNotification den Bildschirmpunkt ermitteln
Point _GEOMETR_EXPORT BSPoint (LPARAM lParam)
{
HWND hWndV = ::GetDlgItem (__hWndM, VIEWCHILDID);	// VIEWCHILDID: Child-ID vom ViewFenster

	if (0 == hWndV)	// Projekt wird geschlossen oder kein Projekt geöffnet
		return Point();

Window Wnd(hWndV);	// TRiAS-ViewFenster
//Point Pt (LOWORD (lParam), HIWORD (lParam));	// Punkt in Bildschirmkoordinaten (04.08.98)
CoOrd x = LOWORD (lParam);	// beide Werte sind
CoOrd y = HIWORD (lParam);	// vorzeichenbehaftet

	if (x >= 0x8000) x -= 0x10000;	// Vorzeichen
	if (y >= 0x8000) y -= 0x10000;	// berücksichtigen

Point Pt (x, y);	// Punkt in Bildschirmkoordinaten
Rectangle CRc = Wnd.CanvasRect();

//#if _TRiAS_VER < 0x0300
// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
// konform zu gehen !!!!!!!!!!!!
int iBH = CRc.Top() - CRc.Bottom() - 1;		// Höhe des TRiAS-ViewFensters
//#else				// ist das an dieser Stelle auch richtig ?????
//int iBH = CRc.Top() - CRc.Bottom();		// Höhe des TRiAS-ViewFensters
//#endif // _TRiAS_VER < 0x0300

	Pt.Y() = iBH - Pt.Y();	// y-Koordinate drehen
	return Pt;

} // BSPoint


// --------------------------------------------------------------------------------------------
// Koordinaten der Cursorposition in BS- (Pt) und DB-Koordinaten (Pkt) ermitteln
bool _GEOMETR_EXPORT GetCursorCoordinates (Point& Pt, EPunkt& Pkt)
{
HWND hWndV = ::GetDlgItem (__hWndM, VIEWCHILDID);	// VIEWCHILDID: Child-ID vom ViewFenster

	if (0 == hWndV)	// Projekt wird geschlossen oder kein Projekt geöffnet
		return false;

POINT PT;

	if (! GetCursorPos (&PT))	// Funktion hat einen bool-return-Wert
	{
		_ASSERTE (false);
		return false;
	}

Window Wnd(hWndV);	// TRiAS-ViewFenster
Rectangle CRc = Wnd.CanvasRect();

	ScreenToClient (hWndV, &PT);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

	Pt.X() = PT.x;

//#if _TRiAS_VER < 0x0300
	// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
	// konform zu gehen !!!!!!!!!!!!
	Pt.Y() = CRc.Top() - CRc.Bottom() - 1 - PT.y;	// y-Koordinate drehen
//#else				// ist das an dieser Stelle auch richtig ?????
//	Pt.Y() = CRc.Top() - CRc.Bottom() - PT.y;	// y-Koordinate drehen
//#endif // _TRiAS_VER < 0x0300

	// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
	Pkt = DBKoordinaten (Pt);

	return true;

} // GetCursorCoordinates


// --------------------------------------------------------------------------------------------
// Umrechnung der Koordinaten des Bildschirmpunktes BSPkt in Datenbank-Koordinaten, die als
// Punkt über "return" zurückgegeben werden; mit bKipp kann unterschieden werden, ob die
// y-Koordinate an der Bildschirmhöhe gekippt werden soll (true) oder nicht (false)
EPunkt _GEOMETR_EXPORT DBKoordinaten (Point& BSPkt, bool bKipp)
{
COORDCONVERT CC;
// Datenbasis-Koordinaten (nicht als Punkt sondern als 2 KoOrd-Werte deklariert, da "mein
// Punkt" durch EObjekt eine virtuelle Tabelle enthält, "Hartmut's Punkt" hingegen nicht !!!)
KoOrd DBKoord [2];

	CC.lpPt = (POINT*) &BSPkt;
	CC.lpPkt = DBKoord;
	if (bKipp)
		DEX_DCtoOC (CC);	// kippt die y-Koordinate
	else
		DEX_DCtoOCEx (CC);	// kippt die y-Koordinate nicht
	return EPunkt (DBKoord[0], DBKoord[1]);
} // DBKoordinaten


// --------------------------------------------------------------------------------------------
// Umrechnung von Datenbank-Koordinaten in Bildschirm-Koordinaten für das TRiAS-ViewFenster,
// die als Point über "return" zurückgegeben werden; mit bKipp kann unterschieden werden, ob
// die y-Koordinate an der Bildschirmhöhe gekippt werden soll (true) oder nicht (false)
Point _GEOMETR_EXPORT BSKoordinaten (KoOrd XD, KoOrd YD, bool bKipp)
{
COORDCONVERT CC;
Point BSPkt;
// Datenbasis-Koordinaten (nicht als Punkt sondern als 2 KoOrd-Werte deklariert, da bei Hartmut
// der Punkt etwas anderes bedeutet als bei mir !!!)
KoOrd DBKoord [2];

	DBKoord [0] = XD; DBKoord [1] = YD;
	CC.lpPt = (POINT*) &BSPkt;
	CC.lpPkt = DBKoord;
	if (bKipp)
		DEX_OCtoDC (CC);	// kippt die y-Koordinate
	else
		DEX_OCtoDCEx (CC);	// kippt die y-Koordinate nicht

//#if _TRiAS_VER < 0x0300
	BSPkt.X()--;	// wegen Fehler bei Hartmut notwendig	22.04.98
	BSPkt.Y()--;
//#endif // _TRiAS_VER < 0x0300

	return BSPkt;

} // BSKoordinaten


// --------------------------------------------------------------------------------------------
// Umrechnung der Koordinaten des Bildschirmpunktes BSPkt für CoordTransDistance() in
// ASC-Format (jedoch NICHT noch den Schritt der Umwandlung in Real-Koordinaten (ist für
// CoordTransDistance() Gift !!!)
DoublePair _GEOMETR_EXPORT BSInASCKoord (Point& BSPkt, CoordTransX* pCT, bool bKipp)
{
	_ASSERTE (pCT != 0);

	if (! pCT)
		return DoublePair();

// 1. Schritt: Koordinaten in DB-Koordinaten konvertieren
COORDCONVERT CC;
// Datenbasis-Koordinaten (nicht als Punkt sondern als 2 KoOrd-Werte deklariert, da bei Hartmut
// der Punkt etwas anderes bedeutet als bei mir !!!)
KoOrd DBKoord [2];

	CC.lpPt = (POINT*) &BSPkt;
	CC.lpPkt = DBKoord;
	if (bKipp)
		DEX_OCtoDC (CC);	// kippt die y-Koordinate
	else
		DEX_DCtoOCEx (CC);	// kippt die y-Koordinate nicht

// 2. Schritt: DB-Koordinaten in ASC-Format transformieren (incl. rausrechnen der internen
//             Skalierung)
double XOut, YOut;

	pCT->UnScale (DBKoord[0], DBKoord[1], &XOut, &YOut);

	return DoublePair (XOut, YOut);

} // BSInASCKoord


// --------------------------------------------------------------------------------------------
// Konvertierung von Datenbank-Koordinaten in Real-Koordinaten
void _GEOMETR_EXPORT DBKoordInReal (EPunkt& Pt, double& XOut, double& YOut, 
	CoordTransX* pCT, IUnknown *pICS)
{
	_ASSERTE (pCT != 0);

	if (! pCT) return;

// 1. Schritt: DB-Koordinaten in ASC-Format transformieren (incl. rausrechnen der internen
//             Skalierung)
	pCT->UnScale (Pt.X(), Pt.Y(), &XOut, &YOut);

// 2. Schritt: Umwandlung in Real-Koordinaten
	pCT->TransformEx (&XOut, &YOut, NULL, pICS);

} // DBKoordInReal


// --------------------------------------------------------------------------------------------
// Konvertierung von Datenbank-Koordinaten in Real-Koordinaten
void _GEOMETR_EXPORT DBKoordInReal (KoOrd XIn, KoOrd YIn, double& XOut, double& YOut,
									CoordTransX* pCT, IUnknown *pICS)
{
	_ASSERTE (pCT != 0);

	if (! pCT) return;

// 1. Schritt: DB-Koordinaten in ASC-Format transformieren (incl. rausrechnen der internen
//             Skalierung)
	pCT->UnScale (XIn, YIn, &XOut, &YOut);

// 2. Schritt: Umwandlung in Real-Koordinaten
	pCT->TransformEx (&XOut, &YOut, NULL, pICS);

} // DBKoordInReal


//---------------------------------------------------------------------------------------------
// Konvertierung der Real-Koordinaten dX und dY in Datenbank-Koordinaten
void _GEOMETR_EXPORT RealInDBKoord (double dX, double dY, KoOrd& PX, KoOrd& PY,
									CoordTransX* pCT, IUnknown *pICS)
{
	_ASSERTE (pCT != 0);

	if (! pCT) return;

// 1. Schritt: Umwandlung der Real-Koordinaten dX und dY in ASC-Format
	pCT->InvTransformEx (&dX, &dY, NULL, pICS);

// 2. Schritt: Umwandlung des ASC-Format in DB-Koordinaten (unter Einbeziehung der Skalierung)
	pCT->Scale (dX, dY, &PX, &PY);

} // RealInDBKoord

/*
//---------------------------------------------------------------------------------------------
// Transformationsfaktor dFakt berechnen, mit dessen Hilfe ein in Metern vorgegebener Wert
// multipliziert werden muß, um auf Datenbank-Verhältnisse zu kommen; die Berechnung wird für
// den Bereich durchgeführt, der in dem durch P1(x1,y1) und P2(x2,y2) aufgespannten Container
// liegt
HRESULT _GEOMETR_EXPORT UmrechnungsFaktor1 (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
											CoordTransX* pCT, double& dFakt)
{
	_ASSERTE (pCT != 0);

	if (! pCT) return E_POINTER;

	if (x1 == x2 && y1 == y2) return E_INVALIDARG;

double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten

	pCT->UnScale (x1, y1, &XOut1, &YOut1);	// DB-Koordinaten in ASC-Format transformieren
	pCT->UnScale (x2, y2, &XOut2, &YOut2);	//  (incl. rausrechnen der internen Skalierung)

DoublePair P1 (XOut1, YOut1);
DoublePair P2 (XOut2, YOut2);
double dAbst = pCT->CoordTransDistance (&P1, &P2);

	if (0 == dAbst) return E_INVALIDARG;

	dFakt = AbstandPktPktE (x1, y1, x2, y2) / dAbst;

	// auf 8 Kommastellen runden
	dFakt = floor (100000000. * (dFakt + 0.000000005)) / 100000000.;

	return S_OK;

} // UmrechnungsFaktor1
*/

//---------------------------------------------------------------------------------------------
// Transformationsfaktor (return-Wert) berechnen, mit dessen Hilfe ein in Metern vorgegebener
// Eingabewert in x- bzw. y-Richtung multipliziert werden muß, um auf Datenbank-Verhältnisse zu
// kommen; die Berechnung wird für den Bereich durchgeführt, der in dem durch P1(x1,y1) und
// P2(x2,y2) aufgespannten Container liegt
DoublePair _GEOMETR_EXPORT UmrechnungsFaktor (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
											  CoordTransX* pCT)
{
	_ASSERTE (pCT != 0);

	if (! pCT) return DoublePair();

KoOrd XMin = min (x1, x2);
KoOrd XMax = max (x1, x2);
KoOrd YMin = min (y1, y2);
KoOrd YMax = max (y1, y2);

	if (XMax == XMin) XMax++;	// damit Strecke nicht haarscharf senkrecht bzw.
	if (YMax == YMin) YMax++;	//  haarscharf waagerecht ist

double dXMin, dYMin, dXMax, dYMax;	// Real-Koordinaten

	pCT->UnScale (XMin, YMin, &dXMin, &dYMin);	// DB-Koordinaten in ASC-Format transformieren
	pCT->UnScale (XMax, YMax, &dXMax, &dYMax);	//  (incl. rausrechnen der internen Skalierung)

DoublePair DP1 (dXMin, dYMax);	// linker oberer Punkt des durch P1 und P2 aufgespannten Containers
DoublePair DP2 (dXMax, dYMax);	// rechter oberer Punkt
DoublePair DP3 (dXMin, dYMin);	// linker unterer Punkt
DoublePair dUF;					// Umrechnungsfaktor in x- bzw. y-Richtung

double dBreite = pCT->CoordTransDistance (&DP1, &DP2);	// Containerbreite in Meter
double dHoehe = pCT->CoordTransDistance (&DP1, &DP3);	// Containerhöhe in Meter

	// auf 6 Kommastellen runden
	dBreite = floor (1000000. * (dBreite + 0.0000005)) / 1000000.;
	dHoehe  = floor (1000000. * (dHoehe  + 0.0000005)) / 1000000.;

	dUF.X() = ((double)XMax - XMin) / dBreite;
	dUF.Y() = ((double)YMax - YMin) / dHoehe;

	return dUF;

} // UmrechnungsFaktor


// --------------------------------------------------------------------------------------------
// Konvertierung NumEdit-Text->DB-Koordinaten
bool _GEOMETR_EXPORT NumEditToDBCoord (DoubleNumEditX* pXWert, DoubleNumEditX* pYWert,
									   KoOrd& x, KoOrd& y, CoordTransX* pCT)
{
// TEXTL ist in geokonst.hxx definiert
char pcInBuffX[TEXTL] = { '\0' };		// Konvertierungspuffer für x-
char pcInBuffY[TEXTL] = { '\0' };		//  bzw. y-Koordinate

    if (pCT)
    {
    double dRW, dHW;

    	pXWert->GetText (pcInBuffX, sizeof (pcInBuffX));
    	pYWert->GetText (pcInBuffY, sizeof (pcInBuffY));
    	if (!pCT->CoordTransToValueEx (pcInBuffX, pcInBuffY, dRW, dHW))
    		return false;

    	// Umwandlung der Real- in DB-Koordinaten (unter Berücksichtigung der internen
    	// Skalierung)
    	RealInDBKoord (dRW, dHW, x, y, pCT);
    }
    else
    {
    	pXWert->GetText (pcInBuffX, sizeof (pcInBuffX));
    	x = atol (pcInBuffX);
    	pYWert->GetText (pcInBuffY, sizeof (pcInBuffY));
    	y = atol (pcInBuffY);
    }

    return true;

} // NumEditToDBCoord


// --------------------------------------------------------------------------------------------
// Konvertierung DB-Koordinaten->NumEdit-Text
void _GEOMETR_EXPORT DBCoordToNumEdit (KoOrd x, KoOrd y, DoubleNumEditX* pXWert,
									   DoubleNumEditX* pYWert, CoordTransX* pCT)
{
char pcOutBuff[TEXTL] = { '\0' };	// Konvertierungspuffer

    if (pCT)
    {
    double XOut, YOut;

    	DBKoordInReal (x, y, XOut, YOut, pCT);

    	// Umwandlung in Text für Anzeige im DoubleNumEdit-Fenster
    	// Rechtswert
    	pCT->CoordTransToStringEx (XOut, YOut, true, pcOutBuff, sizeof(pcOutBuff));
    	pXWert->SetText (pcOutBuff);
    	// Hochwert
    	pCT->CoordTransToStringEx (XOut, YOut, false, pcOutBuff, sizeof(pcOutBuff));
    	pYWert->SetText (pcOutBuff);
    }
    else
    {
    	pXWert->SetText (ltoa (x, pcOutBuff, 10));
    	pYWert->SetText (ltoa (y, pcOutBuff, 10));
    }

} // DBCoordToNumEdit


// --------------------------------------------------------------------------------------------
// Anzahl der Vorkomma-Stellen von pXWert und pYWert bestimmen, wenn Koordinatensystem metrisch
// ist (Rückgabe von true), sonst keine Ermittlung und Rückgabe von false
bool _GEOMETR_EXPORT DigitNumerator (int& iXL, int& iYL, DoubleNumEditX* pXWert,
									 DoubleNumEditX* pYWert, CoordTransX* pCT)
{
    if (! pCT) return false;

    if (!pCT->isMetric())
    {
    	iXL = 0;
    	iYL = 0;
    	return false;	// geodätische Koordinaten (z. B. in der Form 12°34'56")
    }

char pcBuffer[TEXTL] = { '\0' };	// Konvertierungspuffer

    pXWert->GetText (pcBuffer, TEXTL);

char* pT = strchr (pcBuffer, '.');	
    
    
    if (pT) iXL = pT - pcBuffer;
	else iXL = strlen (pcBuffer);	// Koordinate enthält keinen Dezimalpunkt

	iXL -= strspn (pcBuffer, " ");	// vorangestellte Leerzeichen nicht mitzählen

    pYWert->GetText (pcBuffer, TEXTL);
    pT = strchr (pcBuffer, '.');
    iYL = strlen (pcBuffer);
    if (pT) iYL = pT - pcBuffer;

	iYL -= strspn (pcBuffer, " ");

    return true;

} // DigitNumerator


// --------------------------------------------------------------------------------------------
// Einlesen eines Wertes aus einem DoubleNumEditX-Feld und Konvertierung in einen double-Wert;
// ist das DoubleNumEditX-Feld leer, wird "false" zurückgegeben
bool _GEOMETR_EXPORT NumEditToDouble (DoubleNumEditX* pEingWert, double& dEingWert)
{
	_ASSERTE (pEingWert != 0);

	if (pEingWert->GetTextLen() > 0)
	{
	char pcInBuff[20];

		pEingWert->GetText (pcInBuff, sizeof(pcInBuff));
		dEingWert = atof (pcInBuff);
		return true;
	}

	dEingWert = 0.;
	return false;

} // NumEditToDouble


// --------------------------------------------------------------------------------------------
// Auslesen des Eintrags aus dem DoubleNumEdit-Feld pEingWert und Rückgabe in sParam
bool _GEOMETR_EXPORT NumEditToString (DoubleNumEditX* pEingWert, string& sParam)
{
	_ASSERTE (pEingWert != NULL);

	sParam = "";

	if (pEingWert->GetTextLen() > 0)
	{
	char pcInBuff [20];

		pEingWert->GetText (pcInBuff, sizeof(pcInBuff));

		if (0.0 == atof(pcInBuff) && NPOS == ((string)pcInBuff).find_first_of ("0"))
			return false;	// Editier-Feld ist leer

		sParam = pcInBuff;
		return true;
	}

	return false;

} // GetStringParameter
