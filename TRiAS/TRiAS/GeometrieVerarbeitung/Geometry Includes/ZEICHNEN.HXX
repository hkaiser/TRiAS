// Funktionen zum Zeichnen
// File: ZEICHNEN.HXX
// W. Mörtl

#if !defined(_ZEICHNEN_HXX)
#define _ZEICHNEN_HXX




// Linie mit den BS-Punkten APt und EPt auf dem Bildschirm zeichnen
_GEOMETR_ENTRY bool DrawLine (Point APt, Point EPt, pWindow pW);

// Linie mit den DB-Punkten AP und EP auf dem Bildschirm zeichnen
_GEOMETR_ENTRY bool DrawLine (EPunkt& AP, EPunkt& EP, bool bKipp, pWindow pW);

// Polygon mit dem KoOrd-Vektor plXK,plYK der Länge lAnz auf dem Bildschirm zeichnen
_GEOMETR_ENTRY bool DrawPolygon (EPunkt& RefPkt, KoOrd* plXK, KoOrd* plYK, long lAnz,
								 bool bKipp, pWindow pW);

// mehrere Polygone auf dem Bildschirm zeichnen
_GEOMETR_ENTRY bool DrawPolyPolygon (EPunkt& RefPkt, KoOrd* plXK, KoOrd* plYK,
								const int* piPolyCounts, long lAnz, bool bKipp, pWindow pW);

// Kante komplett auf dem Bildschirm neuzeichnen
_GEOMETR_ENTRY void KanteNeuZeichnen (EKante* pK, pWindow pW);

// Polygon plX/plY der Länge lAnz vom Anfangsindex lAnfInd auf dem Bildschirm neuzeichnen
_GEOMETR_ENTRY void KanteNeuZeichnen (KoOrd* plXK, KoOrd* plYK, long lAnfInd, long lAnz,
									  pWindow pW);

// temporäres pIOG-Objekt auf dem Bildschirm neu zeichnen
_GEOMETR_ENTRY bool DrawTemporaryObject (IObjektGeometrie* pIOG, pWindow pW);

// Größe eines Punktsymbols in BS-Pixel ermitteln
_GEOMETR_ENTRY void PointSymbolSize (ulong ulIdent, int& iPixX, int& iPixY);

// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster
_GEOMETR_ENTRY Dimension GetDotsPerMM (HDC hDC);

// Anzahl der Pixel in beiden Koordinatenrichtungen für aktuellen Bildschirm
_GEOMETR_ENTRY Dimension GetDots (HDC hDC);

#endif  // _ZEICHNEN_HXX
