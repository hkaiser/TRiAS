// Allgemeine Deklarationen für "Editier-Funktionen"
// File: EDIKONST.HXX
// W. Mörtl

#if !defined(_EDIKONST_HXX)
#define _EDIKONST_HXX


// mögliche Editier-Funktionen
enum ObjOp
{
	NEUERFASSEN,		// GeoObjekt neu erfassen
	OBJ_LOESCHEN,		// GeoObjekt löschen
	PKT_VERSCHIEBEN,	// Stützpunkt verschieben
	PKT_GREIFEN,		// Stützpunkt greifen
	OBJ_VERSCHIEBEN,	// GeoObjekt verschieben
	OBJ_DREHEN,			// GeoObjekt drehen
	OBJ_TEILEN,			// GeoObjekt teilen
};

// mögliche Aktivitäten beim Neuerfassen eines Objektes
enum AktNeu
{
	VERWERFEN,	// Neuerfassung verwerfen, Objhekt nicht speichern
	BEENDEN,	// Neuerfassung abschließen, Objekt speichern
	FORTSETZEN,	// Neuerfassung fortsetzen
	ZUZIEHEN,	// Linienobjekt zuziehen
	LOESCHEN,	// letzten Stützpunkt löschen
	INSEL,		// mit dem nächsten Stützpunkt beginnt eine Insel
	KREIS,		// aus den letzten 3 Stützpunkten wird Kreis(bogen) gebildet
};

// mögliche Cursorpositionen
enum CursPosit
{
	IN_PUNKT,	// Cursor im Marker eines Stützpunktes
	AUF_STRECKE,// Cursor in der Nähe einer Strecke
	IN_OBJEKT,	// Cursor innerhalb eines markierten Objektes
	KEIN_BEZUG	// Cursor weder im Marker eines Stützpunktes noch in der Nähe einer Strecke
};

// Cursorformen bei Modifizierung vorhandener bzw. Neuerfassung von Geometrieobjekte
enum Curs
{
	PFEIL,		// Standard-Cursor
	STERN,		// Cursorposition liegt innerhalb einer Stützpunktmarkierung (bei Modifizieren von
				//  Objektgeometrieen)
	TRENNER,	// Cursorposition liegt "in der Nähe" einer Kante bzw. Flächenkontur
	KREUZ,		// Cursorposition liegt innerhalb einer Stützpunktmarkierung und CTRL-Taste
				//  wurde zusätzlich gedrückt
	INOBJEKT,	// Cursorposition liegt innerhalb eines markierten Objektes
	FANGEN		// Cursorposition liegt innerhalb einer Stützpunktmarkierung (bei Neuerfassen von
				//  Objektgeometrieen)
};


// ************************************************************************************************
// Konstantendefinition
const short iUGr = 6;	// Standardwert (untere Grenze) für Pixelanzahl der Markierungsquadrate
const short iOGr = 20;	// Standardwert (obere Grenze) für Pixelanzahl der Markierungsquadrate
const uchar GW = 0;		// Color (Rot=GW, Grün=GW, Blau=GW) für Rand der Markierungsquadrate
const uchar GW1 = 100;	// Color (Rot=GW1, Grün=GW1, Blau=GW1) für Rand des 1. Markierungsquadrates
const int zug = 2;		// Sicherheitszugabe für zu bildendes Rechteck bei Neuzeichnen


// ******************************************************************************************
// Struktur für Datenübergabe der Routine AddToORWindow()
struct MoveONr
{
	long lAltObjNr, lNeuObjNr;	// Objektnummer des Original- und des verschobenen Objektes
};

struct MultiVtx
{
	short iIndSel;	// Anzahl der selektierten Objekte, zu denen der Stützpunkt gehört,
					// auf den der Cursor zeigt
	long* plONrSel;	// Objektnummer der Objekte, die den Stützpunkt besitzen, auf den der
					// Cursor zeigt
	short iAnz;		// Anzahl der m_plONrSel-Objekte, die gleichzeitig ein aktiviertes Objekt sind
	long lAktObj;	// Objektnummer eines dieser aktivierten Objekte
};

#endif  // _EDIKONST_HXX
