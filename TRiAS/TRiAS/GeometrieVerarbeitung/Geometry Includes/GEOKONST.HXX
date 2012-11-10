// Allgemeine Deklarationen und Konstantendefinitionen für "Geometrie-DLL"
// File: GeoKonst.hxx
// W. Mörtl

#ifndef _GEOKONST_HXX
#define _GEOKONST_HXX




// ********************************************************************************************
// mögliche 1. Markierung bei markierbaren Punkten
enum Mar1
{
	NORMAL,		// normaler Punkt
	INNERHALB,	// Punkt innerhalb eines Überlappungsbereiches
	RANDP,		// Randpunkt eines Überlappungsbereiches
	RAND_INN,	// Randpunkt eines Überlappungsbereiches mit Zuführung aus dem
				// Inneren der Bezugsfläche
	RAND_UMG,	// Randpunkt eines Überlappungsbereiches mit Zuführung aus der
				// Umgebung der Bezugsfläche
	BERUEHR,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel
	BERUE_INN,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
				// beteiligten Strecken aus dem Inneren der Bezugsfläche kommen
	BERUE_UMG,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
				// beteiligten Strecken aus der Umgebung der Bezugsfläche kommen
	BERUE_ER,	// erster Punkt einer offenen Kante mit Randpunkt- bzw. Innenberührung ohne
				// Seitenwechsel, wobei die beteiligten Strecken aus dem Inneren der
				// Bezugsfläche kommen und der Anfangspunkt der Kante im Inneren der
				// Bezugsfläche liegt
	BERUE_LE,	// letzter Punkt einer offenen Kante mit Randpunkt- bzw. Innenberührung ohne
				// Seitenwechsel, wobei die beteiligten Strecken aus dem Inneren der
				// Bezugsfläche kommen und der Endpunkt der Kante im Inneren der Bezugsfläche
				// liegt
	SCHNITT,	// Schnittpunkt
	GEMEINSAM	// Punkt, an dem 2 Linien eine Gemeinsamkeit haben (Schnitt, Berührung,
				// Überlappung) 
};

// mögliche 2. Markierung bei markierbaren Punkten
enum Mar2
{
	UNVERBR,	// "unverbrauchte" Strecke
	VERBR		// "verbrauchte" Strecke
};

// mögliche Ergebnisse bei Test auf Überschneidung der Strecken zweier Kanten
enum SchnittErg
{
	KEINE,		// keine Überschneidung
	ECHT,		// Überschneidung, so daß Schnittpunkt jeweils im "Inneren" der beiden
				// Strecken liegt (echter Schnitt)
	RAND,		// Überschneidung, so daß Schnittpunkt bei beiden Strecken ein Randpunkt
				// ist, Seitenwechsel ist noch nicht geklärt (Randpunktberührung)
	RAND_MIT,	// Überschneidung, so daß Schnittpunkt bei beiden Strecken ein Randpunkt
				// ist und ein sofortiger Seitenwechsel erfolgt (Randpunktberührung)
	RAND_OHNE,	// Berührung in einem Punkt, der bei beiden Strecken ein Randpunkt ist, ein
				// Seitenwechsel erfolgt nicht (Randpunktberührung)
	INNEN,		// Berührung in einem Punkt, der bei einer Strecke ein Randpunkt ist, bei der
				// anderen in deren "Inneren" liegt, Seitenwechsel ist noch nicht geklärt
				// (Innenberührung)
	INNEN_MIT,	// Überschneidung, so daß Schnittpunkt bei einer Strecke ein Randpunkt ist,
				// bei der anderen in deren "Inneren" liegt und ein sofortiger Seitenwechsel
				// erfolgt (Innenberührung)
	INNEN_OHNE,	// Berührung in einem Punkt, der bei einer Strecke ein Randpunkt ist, bei der
				// anderen in deren "Inneren" liegt, ein Seitenwechsel erfolgt nicht
				// (Innenberührung)
	BERUE_OHNE,	// Randpunkt- oder Innenberührung ohne Seitenwechsel
	UEBERLAPP	// Überlappung beider Strecken
};


// Relation eines Objektes zu einem Bezugsobjekt (nach der OGC-Norm)
enum OGCPosit
{
	WITHIN,		// vollständig innerhalb des Bezugsobjektes
	CONTAIN,	// überdeckt das Bezugsobjekt vollständig
	OVERLAP,	// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes (nur für die
				// Kombinationen Linie/Linie und Fläche/Fläche; der Durchschnitt beider Objekte
				// muß die gleiche Dimension wie die Vergleichsobjekte haben)
	ENTER,		// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes (nur für die
				// Kombinationen Linie/Linie, Linie/Fläche und Fläche/Linie; der Durchschnitt
				// beider Objekte muß eine geringere Dimension wie die größere der beiden
				// Dimensionen der Vergleichsobjekte haben)
	TOUCH,		// berührt das Bezugsobjekt von außen
	EQUAL,		// vollständig identisch mit dem Bezugsobjekt
	DISJOINT,	// keinerlei Gemeinsamkeiten mit dem Bezugsobjekt
	INTERSECT,	// mindestens ein Punkt mit dem Bezugsobjekt gemeinsam (NOT DISJOINT)
	UNCLEAR		// vorzeitiges Ende bei falschen Parametern, unzureichendem dynamischen
				// Speicher oder Abbruch durch den Anwender
};


// Schnittverhalten von geometrischen Objekten auf dem Bildschirm
enum SectScreen
{
	INSECT,		// es gibt Schnittpunkte, die alle im Bildschirmbereich liegen
	OUTSECT,	// es gibt Schnittpunkte, die aber alle außerhalb des Bildschirms liegen
	INOUTSECT,	// es gibt Schnittpunkte, die teilweise im und teilweise außerhalb des
				// Bildschirmbereiches liegen
	INFISECT,	// es gibt keine eindeutigen Schnittpunkte (die beiden Objekte liegen teilweise
				// oder ganz übereinander)
	NOSECT,		// es gibt keine Schnittpunkte
	ERRSECT		// irgend eine unklare Situation

};


// ********************************************************************************************
// Stringkonstanten
const char RegistryExtPathRein[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.Bereinigung.1\\Config");

const char RegDoppelPunkt[] = TEXT("DoppelPunkt");
const char RegSpitzenWinkel[] = TEXT("SpitzenWinkel");
const char RegSchleife[] = TEXT("Schleife");


// ********************************************************************************************
// Definitionen
#define VIEWCHILDID		0xE900		// Child-ID vom ViewFenster

#if _TRiAS_VER >= 0x0300	// neuer Compiler
#define MAXVIEWNAMESIZE	_MAX_PATH	// maximale Länge eines Sichtnamens
#else						// alter Compiler
#define MAXVIEWNAMESIZE	40			// maximale Länge eines Sichtnamens
#endif // _TRiAS_VER >= 0x0300

const short iKurzTextLen = 64;		// max. Länge des Kurztextes für Objektklasse/Merkmal
const short iLangTextLen = 1024;	// max. Länge des Langtextes für Objektklasse/Merkmal
#define TEXTL	80					// Länge des Konvertierungspuffers für Koordinaten, Objektname bzw. Caption
const short iCharSize = 50;			// Länge einer Fensterüberschrift


// ********************************************************************************************
// Konstantendefinitionen
const double Pi = 3.141592653589793238462643383279502884197169399;

// dGlEps ist die zulässige Abweichung bei EpsGleich() bzw. EpsUngleich().
// Eigentlich müßte sqrt(2)/2 = 0.7071 (die halbe Diagonale eines Quadrates mit der
// Kantenlänge 1) ausreichen.
// In mindestens einem Fall reicht dies aber nicht aus: So wurde eine Fläche mit Inseln
// geschnitten. Zwischen dem Schnitt der Außenkontur und den Innenkonturen wurden jeweils die
// double-Koordinaten auf KoOrd-Koordinaten gerundet, da die Ergebnisfläche ein
// GeoFlaeche-Objekt ist. Dadurch ragte die Ergebnisfläche mehr als sqrt(2)/2 über die
// schneidende Fläche hinaus. Ein erneuter Schnitt (nun aber mit dem Schnittergebnis des ersten
// Schnittes) hätte noch einmal echte neue Teilflächen ergeben.
// Die bisher bekannte größte Abweichung beträgt 0.74275 (08.10.98)
// Die bisher bekannte größte Abweichung beträgt 1.51555 (13.10.98)
const double dGlEps = 1.52;		// zulässige Abweichung bei Test auf Gleichheit (in DB-Koordinaten)
const double dREps = 1E-6;		// zulässiges Rauschen bei double-Koordinaten
const short iKoEps = 6;			// zulässige Abweichung bei eps-Kollinearität dreier Punkte
const short iCoEps = 6;			// zulässige Abweichung bei Container-Durchschnitt
const short iBuEps = 6;			// zulässige Abweichung bei Bildung der Pufferelemente

const short iRWZug = 5;			// Zugabe (in Pixel) bei der Positionierung von Recherchefenstern
const short iZeiZug = 5;		// Zugabe beim Zeichnen eines Rechteckbereiches in Millimeter
const int iSicher = 2;			// Sicherheitszugabe für zu bildendes Rechteck bei Neuzeichnen

const string sMTrenn = "/";		// Trennzeichen für Merkmale aus mehreren Objekten 

const double dDopEps = 0.;		// zulässige Abweichung bei Bereinigung von DoppelPunkt'en (in Meter)
const double dSpiEps = 0.5;		// Grenzwinkel für Spitze (in Gradmaß)
const int iLoopLen = 5;			// min. Anzahl von Stützpunkten bei Schleifen an Kantenenden


#endif  // _GEOKONST_HXX
