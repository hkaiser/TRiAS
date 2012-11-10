// Funktionen für Koordinatentransformationen
// File: KOORD.HXX
// W. Mörtl

#if !defined(_KOORD_HXX)
#define _KOORD_HXX


// aus dem LPARAM-Wert der WindowsNotification den Bildschirmpunkt ermitteln
_GEOMETR_ENTRY Point BSPoint (LPARAM lParam);

// Koordinaten der Cursorposition BS- (Pt) und DB-Koordinaten (Pkt) ermitteln
_GEOMETR_ENTRY bool GetCursorCoordinates (Point& Pt, EPunkt& Pkt);

// Umrechnung der Koordinaten des Bildschirmpunktes BSPkt in Datenbank-Koordinaten
_GEOMETR_ENTRY EPunkt DBKoordinaten (Point& BSPkt, bool bKipp = false);

// Umrechnung von Datenbank-Koordinaten in Bildschirm-Koordinaten
_GEOMETR_ENTRY Point BSKoordinaten (KoOrd XD, KoOrd YD, bool bKipp = false);

// Umrechnung der Koordinaten des Bildschirmpunktes BSPkt in ASC-Format
_GEOMETR_ENTRY DoublePair BSInASCKoord (Point& BSPkt, CoordTransX* pCT, bool bKipp = false);

// Konvertierung von Datenbank-Koordinaten in Real-Koordinaten
_GEOMETR_ENTRY void DBKoordInReal (EPunkt& Pt, double& XOut, double& YOut, 
	CoordTransX* pCT, IUnknown *pICS = NULL);
_GEOMETR_ENTRY void DBKoordInReal (KoOrd XIn, KoOrd YIn, double& XOut, double& YOut,
	CoordTransX* pCT, IUnknown *pICS = NULL);

// Konvertierung der Real-Koordinaten dX und dY in Datenbank-Koordinaten
_GEOMETR_ENTRY void RealInDBKoord (double dX, double dY, KoOrd& PX, KoOrd& PY,
	CoordTransX* pCT, IUnknown *pICS = NULL);

// Transformationsfaktor berechnen, mit dessen Hilfe ein in Metern vorgegebener Eingabewert in
// Datenbank-Verhältnisse umgerechnet werden kann
_GEOMETR_ENTRY DoublePair UmrechnungsFaktor (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
											 CoordTransX* pCT);

// Konvertierung NumEdit-Text -> DB-Koordinaten
_GEOMETR_ENTRY bool NumEditToDBCoord (DoubleNumEditX* pXWert, DoubleNumEditX* pYWert, KoOrd& x,
									  KoOrd& y, CoordTransX* pCT);

// Konvertierung DB-Koordinaten -> NumEdit-Text
_GEOMETR_ENTRY void DBCoordToNumEdit (KoOrd x, KoOrd y, DoubleNumEditX* pXWert,
									  DoubleNumEditX* pYWert, CoordTransX* pCT);

// Anzahl der Vorkomma-Stellen von pXWert und pYWert bestimmen
_GEOMETR_ENTRY bool DigitNumerator (int& iXL, int& iYL, DoubleNumEditX* pXWert,
									DoubleNumEditX* pYWert, CoordTransX* pCT);

// Einlesen eines Wertes aus einem DoubleNumEditX-Feld und Konvertierung in einen double-Wert
_GEOMETR_ENTRY bool NumEditToDouble (DoubleNumEditX* pEingWert, double& dEingWert);

// Einlesen eines Wertes aus einem DoubleNumEditX-Feld und Konvertierung in einen string	-Wert
_GEOMETR_ENTRY bool NumEditToString (DoubleNumEditX* pEingWert, string& sParam);


#endif  // _KOORD_HXX
