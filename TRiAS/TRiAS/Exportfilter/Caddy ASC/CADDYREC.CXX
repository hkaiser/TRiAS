/*
File: CADDYREC.CXX
realiert die Verwaltung eines Caddy-Rekord-Baumes.

Das Modul beinhaltet die eigentliche Konvertierung der TRIAS-Elemente
in entsprechende CADdy-Objekte.

erarbeitet : J. Benkenstein                 Stand vom 2. April 1993
								Stand vom 11. Mai 1994
*/

#include "pheader.h"

// möglichen zu erzeugenden Caddy-Objekte
enum CaddyTyp { C_Symbol, C_Linie, C_PolyLinie, C_Flaeche, C_Text };

#include <attribs.hxx>      // VisInfo ...
#include <ristypes.hxx>     // OT_Punkt u.a.    
#include <impexp.hxx>       // IdentDesription u.a.
#include <strdup.hxx>       // StrDup () und StringDup

#include "caddyasc.hr"       // Konstanten       
#include "caddyasc.hxx"     // ExportLine (), ExportPunkt () u.a.
#include "caddyrec.hxx"     // zugeh. Header-File

// globale Variablen, die vom Benutzer eingestellt werden können
short StandEbene = 21;              // Standard-Ebene
double StandLinBrFakt = 0.01;       // Linien-Breiten-Faktor
long StandMKode = 51100000;         // Merkmals-Kode für CADdy-Anbindung
double StandTextAbstFakt = 0.25;        // Zeichenabstand = 0.25 * Zeichenhöhe
double StandTextBreitenFakt = 1.0;  // Breite = Hoehe * 1.0
double StandTextHoehFakt = 1.0;     // Text-Höhe korrigieren
double StandTextRotFakt = -1.0;     // math pos. drehen
long StandTextMKode = 0L;               // Merkmalskode eines Textwertes

// lokale Konstanten
char StandFolge [] = "0";                       // keine Folge
char pTextFormat [] = "%-9.2f";                 // Text-Format
char pWinkelFormat [] = "%-7.2f";               // Drehwinkel-Format
pchar pScalFormat = pWinkelFormat;              // Format für Skalierung
char TextRefPunkt [] = "0";                     // linksbündig
char TextRichtung [] = "0";                     // horizontal
const short CaddyKurzTextLen = 15;				// Länge eines CADdy-Kurztextes
const short LangTextLen = 80;					// Länge eines CADdy-LangTextes
const short MaxSchriftSatz = 8;					// max. und min.
const short MinSchriftSatz = 1;					// Schriftsatz-Nummer
char NoFolgenElem [] = "0";                     // kein Element einer Folge
char FolgenBegin [] = "7";                      // Werte einer CADdy-Folge
char FolgenElem [] = "8";
char FolgenEnde [] = "9";

/* momentan nicht benötigt (in CheckLayerNames)
const short LayerNameLength = 16;
const char StandardLayerName [] = "CADDY_0";
const char LayerBeginn [] = "C_";   // Ersetzen wenn 1. Zeichen
				    // im Layernamen kein Großbuchstabe
*/

#ifndef __NT__
#define HUGE __huge
#else 
#define HUGE
#endif

// Linientypen
enum LinienTypen { Durchgezogen = 0, Gepunktet, KurzGestrichelt, LangGestrichelt,
				   StrichPunkt, StrichPunktPunkt };

// Schriftzusatz-Vereinbarungen
enum SchriftZusatz { OhneZusatz, unterstrichen, ueberstrichen, Rahmen };

extern char pIniFilePath [_MAX_PATH];
extern ResourceFile *pRF;
extern double SymGroesse;       // Standard-Symbolgröße

//  CaddyRekord ------------------------------------------------------------
//  CADdy-Farbe bilden
short CaddyRekord :: CreateCaddyFarbe (Color Farbe)
{
    return ((Farbe.Red () >> 5) & 7) | ((Farbe.Green () >> 2) & 56) |
	    (Farbe.Blue () & 192);
}

//  Visualisierungs-Information in VisInfo-Datei ausgeben
ErrCode CaddyRekord :: OutputVisInfo (int cfh, Color& Farbe, short CaddyFarbe,
		       short Eb, short Prio, pchar pKurzText)
{
    char Buffer [80] = "";

    wsprintf (Buffer, "%-5d%-34.34s%5u%5u%5u%5d%5d", Eb, pKurzText,
	      Farbe.Red (), Farbe.Green (), Farbe.Blue (), 
	      CaddyFarbe, Prio);

    return ExportLine (cfh, Buffer);
}

// Die Klasse dient zur Verwaltung der Basis-Attribute eines Caddy-Objektes.
CaddyRekord :: CaddyRekord (IdentDescription &ID, pchar pKennung, int cfh)
{
    _Result = False;                // noch nichts getan
    char Buffer [80] = "";          // Arbeits-Puffer
    char Ident [30] = "";

    short Eb = StandEbene;          // Ebene auf Standardwert setzen

//  Identifikator
    _ID = ID.ID ();                 // Identifikator

//  Ebenen-Nr. aus INI-File lesen
    ResString RS (ResID (IDS_EBENENSECT, pRF), 80);
	ClassFromIdentX (_ID, Ident, sizeof(Ident));
    if (GetPrivateProfileString (RS.Addr (), Ident, "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) // wenn Eintrag OK
	Eb = atoi (Buffer);
    if (!Eb)
	Eb = StandEbene;
    if (!_Ebene.Replace (itoa (Eb, Buffer, 10)))  // wenn kein Speicher mehr
		return;

//  Farbe
    Color Farbe;
    VisInfo &VI = ID.VisInfoObj ();    // Visualisierungs-Info
    if (VI.isA () == VT_Flaeche)
		Farbe = ((FVisInfo &) VI).SecColor ();     // Füllfarbe
    else
		Farbe = VI.PrimColor ();                   // Randfarbe

    short sFarbe = CreateCaddyFarbe (Farbe);
    if (!_Farbe.Replace (itoa (sFarbe, Buffer, 10)))
		return;

//  Kennbuchstabe
    if (! _Kennung.Replace (pKennung))
		return;

//  Ebenen-Info, Farbe und Priorität in VisInfo-Tabelle
    if (OutputVisInfo (cfh, Farbe, sFarbe, Eb, VI.Priority (), 
	ID.KurzText ()) != EC_OKAY)
		return;

    _Result = True;     // alles OK
}

// vollständigen Record-Header in Datei ausgeben
ErrCode CaddyRekord :: ExportRecordHeader (int fh, pchar pMerkmal,
					   pchar pFolge, pchar pEbene)
{
    register ErrCode EC;

//  Kennbuchtstabe ausgeben
    if ((EC = ExportLine (fh, _Kennung)) < 0)
		return EC;

//  Ebenen-Namen ausgeben: ggf. übergebene Ebene nutzen
    pchar pEb = pEbene && *pEbene ? pEbene : _Ebene.Ptr ();
    if ((EC = ExportLine (fh, pEb)) < 0)
		return EC;

//  Farbe oder Merkmal ausgeben ?
    if (pMerkmal) {
		if ((EC = ExportLine (fh, pMerkmal)) < 0)
		return EC;
    } else {
		if ((EC = ExportLine (fh, _Farbe)) < 0)
			return EC;
    }

//  Folge-Kenner ausgeben
    if ((EC = ExportLine (fh, pFolge)) < 0)
		return EC;

    return EC_OKAY;
}

// CaddySymbol init.
CaddySymbol :: CaddySymbol (IdentDescription &ID, int cfh)
		 : CaddyRekord (ID, "A", cfh)
{
    _Result = False;                    // noch nichts getan
    char Buffer [15] = "";              // Arbeits-Puffer
    char Ident [30] = "";
    double Wi = 0.0;                    // Drehwinkel

//  identifikatorbezogenen Drehwinkel aus INI-Datei lesen
    ResString RS (ResID (IDS_SYMDREHWINKSECT, pRF), 80);
	ClassFromIdentX (ID.ID (), Ident, sizeof(Ident));
    if (GetPrivateProfileString (RS.Addr (), Ident, "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) // wenn Eintrag OK
		Wi = atof (Buffer);
    if (!_DrehWinkel.Replace (DtoA (Buffer, pWinkelFormat, Wi)))
		return;

 // Symbolskalierung bilden
    PVisInfo *pPVI = (PVisInfo *) (&ID.VisInfoObj ());
    double Skal = pPVI -> Size ().Width ();
    if (Skal)
		Skal /= SymGroesse;     // für x und y nur einen Wert bilden
    else
		Skal = 1.0;

    if (!_SkalierungX.Replace (DtoA (Buffer, pScalFormat, Skal)))
		return;

    if (!_SkalierungY.Replace (Buffer))
		return;

    if (!_Name.Replace (itoa (ID.VisInfoObj().Style(), Buffer, 10)))
		return;

    _Result = True;
}

// vollständiges CaddySymbol in Datei ausgeben
ErrCode CaddySymbol :: Output (OutputParams &OP, pchar pMerkmal, pchar, pchar)
{
    register ErrCode EC;    // Return-Kode
    _Result = False;        // noch nichts getan

//  Rekord-Header ausgeben
    if ((EC = ExportRecordHeader (OP._FH, pMerkmal, NoFolgenElem)) < 0)
		return EC;

//  Symbol-Namen ausgeben
    if ((EC = ExportLine (OP._FH, _Name)) < 0)
		return EC;

//  Punkt-Koordinaten ausgeben
    if ((EC = ExportPunkt (OP._FH, OP._pGS->x[0], OP._pGS->y[0])) < 0)
		return EC;

//  Drehwinkel ausgeben
    if ((EC = ExportLine (OP._FH, _DrehWinkel)) < 0)
		return EC;

//  Skalierung in X-Richtung ausgeben
    if ((EC = ExportLine (OP._FH, _SkalierungX)) < 0)
		return EC;

//  Skalierung in Y-Richtung ausgeben
    if ((EC = ExportLine (OP._FH, _SkalierungY)) < 0)
		return EC;

    _Result = True;
	return EC;
}

// CaddyLinie init.
CaddyLinie :: CaddyLinie (IdentDescription &ID, int cfh)
			: CaddyRekord (ID, "L", cfh)
{
    _Result = False;            // noch nichts getan
    char Buffer [40];           // Arbeits-Puffer
    short LinBreite = 0,
	  LinTyp = 0;

//  Linienbreite
    if (ID.VisInfoObj ().isA () == VT_Linie) {
		_TTyp = OT_KANTE;
		LinBreite = ((LVisInfo &) ID.VisInfoObj ()).Width ();

    //  Linientyp
		switch (ID.VisInfoObj().Style ()) {
		case Dashed:
				LinTyp = KurzGestrichelt;
		break;
		case Dotted:
				LinTyp = Gepunktet;
		break;
		case Dash_Dot:
				LinTyp = StrichPunkt;
		break;
		case Dash_Dot_Dot:
				LinTyp = StrichPunktPunkt;
		break;
		case SolidLine:
				LinTyp = Durchgezogen;
		break;
		default:
				LinTyp = Durchgezogen;
		}
    } else {
		_TTyp = OT_FLAECHE;
		LinBreite = ((FVisInfo &) ID.VisInfoObj ()).Width ();
    }

//  Attribute speichern
    if (!_Typ.Replace (itoa (LinTyp, Buffer, 10)))
		return;
    LinBreite = (short) ((LinBreite * StandLinBrFakt) + 0.5);
    if (!_Breite.Replace (itoa (LinBreite, Buffer, 10)))
	    return;

//  evtl. Ebene der Innenflächen lesen
    short Eb = StandEbene;          // Ebene auf Standardwert setzen
    if (ID.VisInfoObj ().isA () == VT_Flaeche) {
		char Ident [30] = "";

    //  Ebenen-Nr. aus INI-File lesen
		ResString RS (ResID (IDS_IDFLEXT, pRF), 3);
		ClassFromIdentX (ID.ID (), Ident, sizeof(Ident));
		lstrcat (Ident, RS.Addr ());       // ID-Extension anhängen
		RS = ResString (ResID (IDS_EBENENSECT, pRF), 40);
	if (GetPrivateProfileString (RS.Addr (), Ident, "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) // wenn Eintrag OK
	    Eb = atoi (Buffer);
	if (!Eb)                // wenn kein Fehler beim Lesen
	    Eb = StandEbene;

    //  Caddy-Farbe erzeugen
	Color &Farbe = ((FVisInfo &) ID.VisInfoObj ()).SecColor ();
	short sFarbe = CreateCaddyFarbe (Farbe);

    //  Ebenen-Info, Farbe und Priorität in VisInfo-Tabelle
	wsprintf (Buffer, "%-32.32s_i", ID.KurzText ());
	if (OutputVisInfo (cfh, Farbe, sFarbe, Eb, ID.VisInfoObj ().Priority (),
	    Buffer) != EC_OKAY)
	    return;
    }

    if (!_iEbene.Replace (itoa (Eb, Buffer, 10)))       // wenn kein Speicher mehr
		return;

    _Result = True;
}

// vollständige CaddyLinie in Datei ausgeben
ErrCode CaddyLinie :: Output (OutputParams &OP, pchar pMerkmal, pchar pFolge,
						 	  pchar pEbene)
{
    register ErrCode EC;    // Return-Kode
    _Result = False;        // noch nichts getan

//  Rekord-Header ausgeben
    if ((EC = ExportRecordHeader (OP._FH, pMerkmal, pFolge, pEbene)) < 0)
		return EC;

//  Anfangs-Punkt ausgeben
    if ((EC = ExportPunkt (OP._FH, ((double HUGE *)OP._pGS->x)[OP._Ind],
    							   ((double HUGE *)OP._pGS->y)[OP._Ind])) < 0)
		return EC;

//  End-Punkt ausgeben
    if ((EC = ExportPunkt (OP._FH, ((double HUGE *)OP._pGS->x)[OP._Ind+1],
    							   ((double HUGE *)OP._pGS->y)[OP._Ind+1])) < 0)
		return EC;

//  Linienbreite ausgeben
    if ((EC = ExportLine (OP._FH, _Breite)) < 0)
		return EC;

//  Linientyp ausgeben
    if ((EC = ExportLine (OP._FH, _Typ)) < 0)
		return EC;

    _Result = True;
    return EC;
}

// komplette PolyLinien, Flächen (einschl. Innenflächen) als Folge ausgeben
ErrCode CaddyLinie :: OutputFolge (OutputParams &OP, pchar pMerkmal)
{
    register ErrCode EC;    // Return-Kode
    _Result = False;        // noch nichts getan

//  weitere Variablen init.
    long *pCount = OP._pGS -> cnt;  // Vektor für Anzahl der
									// Stützpunkte in Flächen
    long RelInd = 0;                // aktueller Punkt in aktuelle Fläche

//  für alle Flächen (einschl. Innenflächen)
	pchar pEb = NULL;
    for (OP._Ind = 0; *pCount; pCount++, OP._Ind += 2) 
    {
		pEb = OP._Ind ? _iEbene.Ptr () : NULL;
		if ((EC = Output (OP, pMerkmal, FolgenBegin, pEb)) < 0) // Anfangs-Punkt ausgeben
			return EC;

	//  für die einzelne Fläche
		for (OP._Ind++, RelInd = 3; RelInd < *pCount; RelInd++, OP._Ind++) 
		{
			if ((EC = Output (OP, pMerkmal, FolgenElem, pEb)) < 0) // Zwischen-Punkt ausgeben
				return EC;
		}
			if ((EC = Output (OP, pMerkmal, FolgenEnde, pEb)) < 0) // End-Punkt ausgeben
			return EC;
    }

    _Result = True;
    return EC;
}

// CaddyText init.
CaddyText :: CaddyText (IdentDescription &ID, int cfh)
		   : CaddyRekord (ID, "d", cfh)
{
    _Result = False;                // noch nichts getan
    char Buffer [10];               // Arbeits-Puffer
    TVisInfo &VI = (TVisInfo &) ID.VisInfoObj (); // Visualisierungs-Info

//  Text-Drehwinkel
    if (!_DrehWinkel.Replace (DtoA (Buffer, pWinkelFormat,
				    (double) VI.Rotation ()*StandTextRotFakt)))
		return;

//  Text-Hoehe, Breite und Abstand
    double Hoehe = StandTextHoehFakt * (double) abs (VI.Size ().Height ());
    if (!_Hoehe.Replace (DtoA (Buffer, pTextFormat, Hoehe)))
		return;
    if (!_Abstand.Replace (DtoA (Buffer, pTextFormat, Hoehe * StandTextAbstFakt)))
		return;
    double Breite = (double) abs (VI.Size ().Width ());
    if (Breite == 0.0)      // Breite ggf. korrigieren
		Breite = Hoehe * StandTextBreitenFakt;

    if (!_Breite.Replace (DtoA (Buffer, pTextFormat, Breite)))
		return;

//  Proportionaler Schriftsatz ?
    if (!_Proportional.Replace (itoa (!VI.isFixedPitch (), Buffer, 10)))
		return;

//  Schriftsatz (Windows 0..5, CADdy 1..8)
    short SchriftSatz =  VI.Style () + 1;
    if (SchriftSatz > MaxSchriftSatz || SchriftSatz < MinSchriftSatz)
		SchriftSatz = MinSchriftSatz;

    if (!_SchriftSatz.Replace (itoa (SchriftSatz, Buffer, 10)))
		return;

//  Zusatz ermitteln und speichern
    short Zusatz = OhneZusatz;
    if (VI.isUnderlined ())
		Zusatz = unterstrichen;
    else
		if (VI.FrameMode ())
		Zusatz = Rahmen;
		else
		if (VI.isStrikedthru ())
				Zusatz = ueberstrichen;
    if (!_Zusatz.Replace (itoa (Zusatz, Buffer, 10)))
		return;

//  Text-Richtung und Referenzpunkt, bisher keine Infos von TRIAS
    if (!_RefPunkt.Replace (TextRefPunkt))
		return;
    if (!_Richtung.Replace (TextRichtung))
		return;

//  kursiver Text ?
    if (!_Kursiv.Replace (itoa (VI.isItalic(), Buffer, 10)))
		return;

    _Result = True;
}

// vollständigen CaddyText in Datei ausgeben
ErrCode CaddyText :: Output (OutputParams &OP, pchar pText, pchar, pchar)
{
    register ErrCode EC;                // Return-Kode
    _Result = False;                    // noch nichts getan

    if (!pText || !*pText)
		return EC_OKAY;

//  Kurz- oder Langtext ?
    short TextLen = lstrlen (pText);
    if (TextLen > CaddyKurzTextLen) {
		if (TextLen > LangTextLen) {
			*(pText + LangTextLen) = '\0';          // Text abschneiden
                DEX_Error (RC_CADDYASC, WC_TEXTTRUNCATED);
		}
		_Kennung.Upper ();
    }
    else
		_Kennung.Lower ();

//  Rekord-Header ausgeben
    if ((EC = ExportRecordHeader (OP._FH, NULL, NoFolgenElem)) < 0)
		return EC;

//  Text ausgeben
    // :: AnsiToOem (pText, pText);            // DOS-Text erzeugen
//	Steuerzeichen filtern
	short sLen = strlen (pText) + 1;
	char *pEndText = new char [sLen];		
	if (!pEndText)
		return EC_NOMEMORY;

	memset (pEndText, 0, sLen);
	char *pActPos = pEndText;				// absolute Zeichenposition
	for (char *pR = pText; pR && *pR; pR++)
	{
		if ('\\' != *pR)
		{
			*pActPos++ = *pR;			// normales Zeichen
			continue;
		}
		
	//	Steuerzeichen
		if (!*++pR)						// prüfe nächste Zeichen
			break;

		*pActPos++ = ' ';				// durch Leerzeichen ersetzen

	/*
	//	was für ein Steuerzeichen folgt ?
		switch (*pR)
		{
			case 'n':
				*pActPos++ = '\n';		// durch einfachen Backslash ersetzen
			break;
			case 't':					// Tabs auflösen
				*pActPos++ = '\t';
			break;				
			case ' ':
				*pActPos++ = ' ';		// durch einfaches Leerzeichen ersetzen
			break;
			default:					// unbekanntes Steuerzeichen überlesen
			break;				
		}
	*/
	}

    if ((EC = ExportLine (OP._FH, pEndText)) < 0)
	{
		DELETE_VEC (pEndText);
		return EC;
	}
	DELETE_VEC (pEndText);

//  Drehwinkel ausgeben
    if ((EC = ExportLine (OP._FH, _DrehWinkel)) < 0)
		return EC;

//  Referenz-Punkt ausgeben
    if ((EC = ExportPunkt (OP._FH, OP._pGS->x[0], OP._pGS->y[0])) < 0)
		return EC;

//  Höhe, Abstand und Breite ausgeben
    if ((EC = ExportLine (OP._FH, _Hoehe)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Abstand)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Breite)) < 0)
		return EC;

//  restlichen Parameter ausgeben
    if ((EC = ExportLine (OP._FH, _SchriftSatz)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Proportional)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Kursiv)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Zusatz)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _Richtung)) < 0)
		return EC;
    if ((EC = ExportLine (OP._FH, _RefPunkt)) < 0)
		return EC;

    _Result = True;
    return EC;
}

// GetKey-Funktion für ID-Baum
void* GetID (void *pObj)
{
    return & (((CaddyRekord *) pObj) -> ID ());
}

// KeyCompare-Funktion für ID-Baum
int CompareIDs (void *pObj1, void *pObj2)
{
    long ID1 = *((long *) pObj1);
    long ID2 = *((long *) pObj2);

    if (ID1 == ID2)
		return 0;
    else
		if (ID1 > ID2)
		return 1;
		else
		return -1;
}

// CaddyRekordBaum anlegen
CaddyRekordBaum :: CaddyRekordBaum (void)
				 : CTree (GetID, CompareIDs)
{
    // nothing to do
}

void __export CaddyRekordBaum :: UserDelete (void *pObj)
{
    ((CaddyRekord *) pObj) -> ~ CaddyRekord ();
}

CaddyRekordBaum :: ~ CaddyRekordBaum (void)
{
    EveryDelete ();
}

// neuen Rekord erzeugen und in Baum einfügen, VisInfo-Datei ergänzen
ErrCode CaddyRekordBaum :: AddCaddyRekord (IdentDescription &ID, int cfh)
{
//  Typ konvertieren
    short STyp = 0;                     // zu suchender Typ
    switch (ID.VisInfoObj ().isA ()) {
		case VT_Linie:
		STyp = OT_KANTE;
		break;
		case VT_Flaeche:
		STyp = OT_FLAECHE;
		break;
		case VT_Punkt:
		STyp = OT_PUNKT;
		break;
		case VT_Text:
		STyp = OT_TEXT;
		break;
		default:
		case VT_Default:
		return WC_UNKOBJECTTYP;
    }

//  zugeh. Rekord im Baum suchen
    CTable Tb (*this);
    for (Tb.FindFirst (&ID.ID ()); Tb.Valid (); Tb.FindNext (&ID.ID ())) {
		CaddyRekordLock pCR (Tb);
		if (!pCR)
		return EC_LOCKERROR;
		if (pCR -> isA () == STyp)
		return EC_OKAY;
    }

//  sonst neuen Eintrag erzeugen
    CaddyRekordCreator ID_Cr (*this);
    CaddyRekord *pCR = NULL;
    switch (ID.VisInfoObj ().isA ()) {
		case VT_Punkt: // konvertiere: Punkt --> Symbol
		pCR = Create (ID_Cr, CaddySymbol) (ID, cfh);
		break;
		case VT_Linie:
		case VT_Flaeche:
		pCR = Create (ID_Cr, CaddyLinie) (ID, cfh);
		break;
		case VT_Text:
		pCR = Create (ID_Cr, CaddyText) (ID, cfh);
		break;
		case VT_Default:
		default:
		return WC_UNKOBJECTTYP;
    }
    return (!pCR || !*pCR ? EC_NOMEMORY : EC_OKAY); // wenn kein Rekord erzeugt
					// oder Fehler beim Erzeugen
}

// über Identifikator selektierten Rekord in Datei ausgegeben
ErrCode CaddyRekordBaum :: OuputCaddyRekord (OutputParams &OP, MFELD *pMF)
{
//  Eintrag bereits vorhanden ?
    long Id = OP._pGS -> Id;
    CTable Tb (*this);
    for (Tb.FindFirst (&Id); Tb.Valid (); Tb.FindNext (&Id)) {
		CaddyRekordLock pCR (Tb);
		if (!pCR)
		return EC_LOCKERROR;
		if (pCR -> isA () == OP._pGS -> Typ) {  // wenn Objekt gefunden
		//  spezifischen Merkmals-Wert konvertieren
		pchar pMerkmal = NULL;
		if (OP._pGS -> Typ == OT_TEXT) {                // Merkmalskodes des Texte
				pMerkmal = pMF -> MText;                // auf 1. Wert setzen
				while (pMF -> MCode) {
				if (pMF -> MCode == StandTextMKode) { // wenn Kode gef.
						pMerkmal = pMF -> MText;        // dessen Wert ist Textwert
						break;
				}
				pMF++;
				}
		} else {        // alle anderen Geometrietypen untersuchen
				while (pMF -> MCode) {                  // für alle Kodes
				if (pMF -> MCode == StandMKode) {       // vereinbarte MK ?
						if (atoi (pMF -> MText)) {      // und vom Typ Integer
						pMerkmal = pMF -> MText;        // Merkmal als Farbe ben.
						break;                  // gefunden
						}
				}
				pMF++;  // nächstes Merkmal
				}
		}
		switch (OP._pGS -> Typ) {
				case OT_PUNKT:
				case OT_TEXT:
				return pCR -> Output (OP, pMerkmal);
				case OT_FLAECHE:
				return pCR -> OutputFolge (OP, pMerkmal);
				case OT_KANTE:
				return OP._pGS -> GSize > 2 ? pCR -> OutputFolge (OP, pMerkmal) :
						   pCR -> Output (OP, pMerkmal, NoFolgenElem);
				case OT_UNKNOWN:
				default:
				return WC_UNKOBJECTTYP;
		}
		}
    }                   // "for" alle CaddyRecords

    return EC_NOON;     // CaddyRecord entsprechenden Typs nicht gefunden
}

/*---------------------------------------------------------------------------
// wird momentan nicht gebraucht
// Layer-Namen säubern
Bool CaddyRekordTree :: CheckLayerNames (void)
{
    pchar & pText = NULL;
    char NewLayer [LayerNameLength + 3];

    Table Tb (*this);
    for (Tb.First (); Tb.Valid (); Tb.Next ()) { // alle Namen suchen
		CaddyRekordLock pID (Tb);
		if (pID) {
		pText = pID -> KurzText ();

		//  Namen prüfen: zuerst Sonderbehandlung !
		if (!pText || !*pText) {
				DELETE (pID -> KurzText ());
				if ((pID -> KurzText () = StrDup (StandardLayerName, RC_CADDYASC)) == NULL)
				return False;
				continue;       // nächsten Namen               
		}

		//  DOS-String erzeugen
		AnsiToOem (pText, pText);

		//  alles in Großbustaben konvertieren
		pText = strupr (pText);

		//  1. Zeichen muß Großbuchstabe sein
		if (*pText < 'A' || *pText > 'Z') {
				pchar pNewLayer =
			new char [lstrlen (pText) + lstrlen (LayerBeginn) + 1];
				if (!pNewLayer) {
                                DEX_Error (RC_CADDYASC, EC_NOMEMORY);
				return False;
				}
				lstrcpy (pNewLayer, LayerBeginn);
				lstrcat (pNewLayer, pText);
				DELETE (pID -> KurzText ());
				pText = pID -> KurzText () = pNewLayer;
		}

		//  Jokerzeichen ersetzen
		for (; *pText; pText++) {
				if (*pText == '*' || *pText == '?')
				*pText = '_';
		}
		pText =  pID -> KurzText (); // Zeiger wieder richtig setzen

		//  max. Anzahl Zeichen OK ?
		if (lstrlen (pText) > LayerNameLength)
				*(pText + LayerNameLength) = '\0'; // abschneiden !
		}
    }
    return True;
}
*/
