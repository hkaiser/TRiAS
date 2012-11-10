// Allgemeine Deklarationen für die Erweiterung "Geometrie-Editierung"
// File: EditKonst.h
// W. Mörtl

#ifndef _EDITKONST_H
#define _EDITKONST_H


///////////////////////////////////////////////////////////////////////////////////////////////
// mögliche Aktivitäten beim Erfassen eines Objektes
enum AktNeu
{
	OK,			// OK-Button gedrückt
	BEENDEN,	// Editierung abschließen, Objekt speichern
	ABBRECHEN,	// Editierung abbrechen, Objekt nicht speichern
	LOESCHEN	// Stützpunkt löschen
};

// Einteilung der Winkel von Flächen
enum StrWinkel
{
	RECHTER,	// ("nahe") 90° bzw. 270°
	GESTRECKT,	// ("nahe") 180°
	ENTARTET,	// 0° bzw. 360°
	ALLGEMEIN,	// alle anderen (NORMAL ist wegen Redefinition nicht möglich!)
	UNBEKANNT	// noch nicht berechnet
};

// mögliche Zustände beim Rechtwinkligmachen
enum RectMode
{
	RECHTW,	// es gibt Winkel, die rechtwinklig zu machen sind
	KEINRW,	// es gibt keinen Winkel, der rechtwinklig zu machen ist und es gibt auch keinen,
			// der schon exakt rechtwinklig ist (NICHTS ist wegen Redefinition nicht möglich!)
	EXAKT	// es gibt keinen Winkel, der rechtwinklig zu machen ist, aber es gibt mindestens
			// einen, der schon exakt rechtwinklig ist
};


///////////////////////////////////////////////////////////////////////////////////////////////
// Konstantendefinition
const int iUGr = 8;				// untere Grenze für Markierungsquadrate (in Pixel)
const int iOGr = 8;				// obere Grenze für Markierungsquadrate (in Pixel)
const ulong ulGW0 = 0x00;		// Füllfarbe eines Markierungsquadrates
const ulong ulGW1 = 0x408040;	// Randfarbe des 1. Markierungsquadrates einer Kante bzw.
								// Flächenkontur (Blau=0x40, Grün=0x80, Rot=0x40)
const ulong ulGW2 = 0x4040A0;	// Randfarbe des letzten Markierungsquadrat einer Kante
								// (Blau=0x40, Grün=0x40, Rot=0xA0)
const int iThick = 1;			// Randstärke eines Markierungsquadrates
const int iZug = 2;				// Sicherheitszugabe für zu bildendes Rechteck bei Neuzeichnen
const int iAway = 2;			// Dialoge und Menüs werden iAway Pixel noch verschoben, damit sie
								// nicht so unmittelbar an einer Stützpunktmarkierung kleben
const double dRWnkEps = 10.;	// Epsilon für rechten Winkel                  { für das
const double dGWnkEps = 7.;		// Epsilon für gestreckten Winkel              { Recht-
const double dAngrEps = 0.;		// Epsilon Gleichheit der angrenzenden Objekte { winkligmachen
const int iComCnt = 3;			// max. Anzahl möglicher GrabPunkte für CommonBorder

const long lMaxAnz = 500;		// max. Eckenzahl des n-Ecks für Kreisfläche
const long lMinAnz1 = 60;		// min. Eckenzahl des n-Ecks für Kreisfläche (darf nicht 0 sein !!!)
const long lMinAnz2 = 5;		// min. Eckenzahl des n-Ecks für Kreisbogen (darf nicht 0 sein !!!)
const double dKantenL = 100.;	// max. Kantenlänge des zu erzeugenden n-Ecks

const int iDPSize = 18;			// Ausdehnung für kreuzförmigen RestrictCursor (in Pixel)

#define BMPSIZE_EDIT	6		// Anzahl der Button in der EditToolbar-Bitmap
#define BMPSIZE_DESIGN	2		// Anzahl der Button in der DesignToolbarBitmap

#define DESIGNKEY	1101949		// Schlüssel für Registrier-DB, damit der DesignMode aktiviert wird


///////////////////////////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// TRiAS2
const char RegistryExtPathEdit[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.Editierung.2\\Config");
const char g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");

#if _TRiAS_VER < 0x0300
const char g_cbApplication[] = TEXT("TRiAS.Application.2");
#elif _TRiAS_VER < 0x0400
const char g_cbApplication[] = TEXT("TRiAS.Application.3");
#else
const char g_cbApplication[] = TEXT("TRiAS.Application.4");
#endif // _TRiAS_VER < 0x0400

const char g_cbGeoEdit[] = TEXT("TRiAS.Editierung.2");
const char g_cbGeoEditNewPoint[] = TEXT("PropertySheetHandlers\\NewPoint");
const char g_cbGeoEditNewLine[] = TEXT("PropertySheetHandlers\\NewLine");
const char g_cbGeoEditNewArea[] = TEXT("PropertySheetHandlers\\NewArea");
const char g_cbGeoEditLineElongat[] = TEXT("PropertySheetHandlers\\LineElongation");
const char g_cbGeoEditIslandAdd[] = TEXT("PropertySheetHandlers\\IslandAdd");
// je nach Bedarf andere Keys dazudefinieren


///////////////////////////////////////////////////////////////////////////////////////////////
// eigene Windows-Messages
const UINT WM_WM_SETMYFOCUS = WM_USER + 1000;
const UINT WM_WM_OBJMODIFYEND = WM_USER + 1001;
const UINT WM_WM_DESIGNBUILDEND = WM_USER + 1002;


///////////////////////////////////////////////////////////////////////////////////////////////
// Struktur für Datenübergabe der Routine AddToORWindow()
struct MoveONr
{
	INT_PTR lAltObjNr, lNeuObjNr;	// Objektnummer des Original- und des verschobenen Objektes
};

#endif  // _EDITKONST_H
