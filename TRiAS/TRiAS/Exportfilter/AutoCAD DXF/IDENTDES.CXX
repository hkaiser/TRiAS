/*
File: IDENTDES.CXX
realiert die Verwaltung eines Identifikator-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein                 Stand vom 13. April 1994
*/

#include "stdafx.h"
#include "AcadDXFImpl.h"

#include <attribs.hxx>          // VisInfo ...
#include <impexp.hxx>           // IdentDescription
#include <ristypes.hxx>         // OT_PUNKT, OT_KANTE, OT_FLAECHE, OT_TEXT
#include <strdup.hxx>           // StringDup ()

//XX#include "acaddxf.hr"           // Resource-IDs
#include "acaddxf.hxx"          // ExportRecord, ExportLine ...
#include "merkmdes.hxx"         // ExtMerkmalDescription
#include "identdes.hxx"         // zugeh. Header-File

// Konstanten            
char StandardLayerName [MinLayerSize] = "0";      // Standard-Layer-Name
const char StandardLayerFlag [] = "     0";             //
const char StandardLayerFarbe [] = "     7";            // weiß
const char StandardLayerLinTyp [] = "CONTINUOUS";       // geschlossen
const short StandardFarbe = 7;  // weiß

// Prototypen
//XX	extern "C" {
extern UINT GetAutoCADFarbe (COLORREF); // WINDOWS-Farbe in AutoCAD-Farbe umwandeln
//XX	}

extern ExtMerkmalDescriptionTree *pMDT; // erweiterter Merkmal-Beschreibungs-Baum
extern Bool ValidMKodes;                // gültige MerkmalsKodes
extern ResourceFile *pRF;
extern char pIniFilePath [_MAX_PATH];   // Pfad für INI-Datei

// lokale Funktionen -------------------------------------------------------
// GetKey-Funktion für erw. ID-Baum
void* GetExtID (void *pObj)
{
    return & (((ExtIdentDescription *) pObj) -> ID ());
}

// KeyCompare-Funktion für ID-Baum
int CompareExtIDs (void *pObj1, void *pObj2)
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

// GetKey-Funktion für Symbol-Nummern-Baum
void* GetNr (void *pObj)
{
    return & (((SymbolNummer *) pObj) -> Nummer ());
}

// KeyCompare-Funktion für SymbolNummern-Baum
int CompareNr (void *pObj1, void *pObj2)
{
    short Nr1 = *((short *) pObj1);
    short Nr2 = *((short *) pObj2);

    if (Nr1 == Nr2)
		return 0;
    else {
		if (Nr1 > Nr2)
	    	return 1;
		else
	    	return -1;
    }
}

// Symbol-Nummern-Baum -----------------------------------------------------
//  neuen Baum anlegen
SymbolNummernBaum :: SymbolNummernBaum (void)
				   : CTree (GetNr, CompareNr)
{
    //  nothing to do
}

// Symbol-Nummern-Baum freigeben
SymbolNummernBaum :: ~ SymbolNummernBaum (void)
{
    EveryDelete ();
}

void /*XX EXPORTFLT*/ SymbolNummernBaum :: UserDelete (void *pObj)
{
    ((SymbolNummer *) pObj) -> ~ SymbolNummer ();
}

// True, wenn neue Symbol-Nummer im Baum gespeichert, falls noch
// nicht vorhanden, sonst False.
Bool SymbolNummernBaum :: AddNummer (short Nr)
{
    CTable Tb (*this);
    if (Tb.Find (&Nr))      // wenn Nummer bereits existiert
		return True;

//  sonst neuen Eintrag erzeugen
    SymbolNummerCreator SN_Cr (*this);
//XX	    return (Create (SN_Cr, SymbolNummer) (Nr) != NULL);
/*XX*/	    return (ContCreate (SN_Cr, SymbolNummer) (Nr) != NULL);
}

// IdentDescriptionTree -----------------------------------------------------
// ID-Beschreibungs-Baum anlegen
ExtIdentDescriptionTree :: ExtIdentDescriptionTree (double SymGroesse)
						 : CTree (GetExtID, CompareExtIDs)
{
    _SymGroesse = SymGroesse;
    _Result = True;
}

void /*XX EXPORTFLT*/ ExtIdentDescriptionTree :: UserDelete (void *pObj)
{
    ((ExtIdentDescription *) pObj) -> ~ ExtIdentDescription ();
}

ExtIdentDescriptionTree :: ~ ExtIdentDescriptionTree (void)
{
    EveryDelete ();
}

// neue ID-Beschr. in Baum
Bool ExtIdentDescriptionTree :: AddIDD (IdentDescription &IDD) {
    _Result = True;

    CTable Tb (*this);
	VisInfo *pViNew = &IDD.VisInfoObj ();
	VisInfo *pViOld = NULL;
    for (Tb.FindFirst (&IDD.ID ()); Tb.Valid (); Tb.FindNext (&IDD.ID ())) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return False;
		}

	//	Spezialfall 1: beide VisInfos nicht vorhanden		
		pViOld = &pIDD -> VisInfoObj ();
		if (NULL == pViNew && NULL == pViOld)
			return TRUE;

	//	beide VisInfos sinid vorhanden	
		if (pViNew && pViOld && (pViNew -> isA() == pViOld -> isA()))
			return TRUE;
	}

    double Wi = 0.0;
    double Skal = 1.0;
    
//  ggf. Symbol-Attribute speichern
    if (pViNew && (pViNew -> isA () ==  VT_Punkt)) {
		ResString RS (ResID (IDS_IDENTKENNUNG, pRF), 5);
		char IdBuffer [15] = "";
		lstrcpy (IdBuffer, RS.Addr ());         // Id-Kennung speichern
		char Buffer [15] = "";
		ltoa (IDD.ID (), Buffer, DEX_GetIdBase ()); // Wert anhängen
		lstrcat (IdBuffer, Buffer);             // Suchstring komplettieren
		Buffer [0] = '\0';                      // Ergebnisstring rücksetzen
		RS = ResString (ResID (IDS_SYMDREHWINKSEC, pRF), 40);
		if (GetPrivateProfileString (RS.Addr (), IdBuffer, "",
	    	Buffer, sizeof (Buffer) - 1 , pIniFilePath))
	    	Wi = atof (Buffer);                 // Winkel konvertieren

    //  Symbolskalierung bilden
		PVisInfo *pPVI = (PVisInfo *) (&IDD.VisInfoObj ());
		Skal = pPVI -> Size ().Width ();
		if (Skal)
	    	Skal /= _SymGroesse;    // für x und y nur einen Wert bilden
		else
	    	Skal = 1.0;
    }

    if (_Result == False)
		return False;

    ExtIdentDescriptionCreator IDD_Cr (*this);
//XX	    return (Create (IDD_Cr, ExtIdentDescription) (IDD, Wi, Skal) != NULL);
/*XX*/	    return (ContCreate (IDD_Cr, ExtIdentDescription) (IDD, Wi, Skal) != NULL);
}

// zu einem ID seinen Kurztext suchen
pchar ExtIdentDescriptionTree :: FindName (long ID) {
    CTable Tb (*this);
    if (! Tb.Find (& ID))
		return NULL;            // ID nicht gefunden
    else {
		ExtIdentDescriptionLock pIDD (Tb);
		if (pIDD)
	    	return StrDup (pIDD -> KurzText (), RC_ACADDXF);
		else 
	    	return NULL;
    }
}

// Drehwinkel und Skalierung eines Symbols ausgeben
ErrCode ExtIdentDescriptionTree :: OutputSymAttrs (int fh, long Id)
{
    ErrCode EC = EC_OKAY;
    const char Format [] = "%-7.2f";    // Real-Format;
    char Buff [10] = "";

    CTable Tb (*this);
	VisInfo *pVi = NULL;
    for (Tb.FindFirst (&Id); Tb.Valid (); Tb.FindNext (&Id)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return EC_LOCKERROR;
		}
		pVi = &pIDD -> VisInfoObj ();
		if (!pVi || (pIDD -> VisInfoObj ().isA () !=  VT_Punkt))
	    	continue;

    //  ggf. Skalierung ausgeben
		if (pIDD -> Skalierung () != 1.0) {      // wenn von 1.0 verschieden
	    	if ((EC = ExportRecord (fh, 41, DtoA (Buff, Format,
				      pIDD -> Skalierung ()))) != EC_OKAY)
				return EC;
	    	if ((EC = ExportRecord (fh, 42, Buff)) != EC_OKAY)
				return EC;      // Y-Skalierung hat gleichen Wert
		}

    //  ggf. Drehwinkel ausgeben
		if (pIDD -> Rotation ())         // wenn von 0 verschieden
	    	return ExportRecord (fh, 50, DtoA (Buff, Format, pIDD -> Rotation ()));
		return EC_OKAY;
    }
    return WC_NOVALFOUND;
}

// zu einem Text-Objekt über seinen ID die Höhe bestimmen
short ExtIdentDescriptionTree :: FindTextHoehe (long ID) {
    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return -1;
		}

		pVI = &pIDD -> VisInfoObj ();
		if (pVI && (pIDD -> VisInfoObj ().isA () ==  VT_Text))
	    	return abs (((TVisInfo &) (pIDD -> VisInfoObj ())).Size ().Height());
    }

    return -1;		//	wird vom Programm auf Standard gesetzt gesetzt
}

// zu einem Text-Objekt über seinen ID den Drehwinkel bestimmen
short ExtIdentDescriptionTree :: FindTextDrehWinkel (long ID) {
    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return -1;
		}

		pVI = &pIDD -> VisInfoObj ();
		if (pVI && (pIDD -> VisInfoObj ().isA () ==  VT_Text)) // ID gefunden
	    	return ((TVisInfo &) (pIDD -> VisInfoObj ())).Rotation ();
    }
    return -1;
}

// Layer-Namen säubern          
Bool ExtIdentDescriptionTree :: CheckLayerNames (void)
{
    pchar pText = NULL;
    char NewLayer [2*LayerNameLength];  // Platz für Umlaute
    pchar pNewLayer, pNewText;

    CTable Tb (*this);
    for (Tb.First (); Tb.Valid (); Tb.Next ()) { // alle Namen suchen
		ExtIdentDescriptionLock pID (Tb);
		if (pID) {
	     	pText = pID -> KurzText ();

		//  Namen prüfen: zuerst Sonderbehandlung !
	    	if (!pText || !*pText) {
				pNewText = new char [2];
				if (!pNewText)
		    		return False;

				lstrcpy (pNewText, StandardLayerName);  // Standard-Layer-Name

	    	//  alten Namen löschen
				if (pText)
		    		delete pID -> KurzText ();

	    	//  neuen Zeiger setzen
				pID -> KurzText () = pNewText;
				continue;
	    	}

		//  Namen säubern
	    	pNewLayer = NewLayer;   // Zeiger auf Puffer für neuen Namen
	    	for (short Index = 0; Index < LayerNameLength; Index++) {
				if (!*pText)
		    		break;
				if (*pText >= 'a' && *pText <= 'z') {
                                        *pNewLayer++ = toupper (*pText);
					pText++;        
					continue;
				}
				if ((*pText >= 'A' && *pText <= 'Z') ||
		    		(*pText >= '0' && *pText <= '9') ||
		    		(*pText == '-') || (*pText == '_')) {
					*pNewLayer++ = *pText++;
					continue;
				}
				
			// evtl. Umlaute ersetzen
				switch (*pText) {
		    		case 'á':
						*pNewLayer++ = 'S';
						*pNewLayer = 'S';
					break;
		    		case '„':
		    		case 'Ž':
						*pNewLayer++ = 'A';
						*pNewLayer = 'E';
					break;
		    		case '':
		    		case 'š':
						*pNewLayer++ = 'U';
						*pNewLayer = 'E';
					break;
		    		case '”':
		    		case '™':
						*pNewLayer++ = 'O';
						*pNewLayer = 'E';
					break;
		    		default:
						*pNewLayer = '_';
				}
				pNewLayer++;
				pText++;
	    	}   // end_for
	    	
	    	*pNewLayer = '\0';

		//  max. Anzahl Zeichen OK ?
	    	if (lstrlen (NewLayer) > (LayerNameLength - 1))
				NewLayer [LayerNameLength - 1] = '\0'; // abschneiden !

		//  Speicher für neuen Text anfordern
	    	pNewText = new char [lstrlen (NewLayer) + 1];
	    	if (!pNewText)
				return False;

		//  neuen Layer-Namen kopieren
	    	lstrcpy (pNewText, NewLayer);

		//  alten Layer-Namen löschen
	    	delete pID -> KurzText ();

		//  neuen Zeiger auf Layer-Namen setzen
	    	pID -> KurzText () = pNewText;
		}
    }
    return True;
}


// Layer-Table in Datei ausgeben, die zuvor in entsprechendem Modus
// geöffnet worden sein muß.
ErrCode ExtIdentDescriptionTree :: OutputLayerTable (int fh, int cfh) {
//  prüfe interne Parameter
    short Cnt = (short) Count ();
    if (! Cnt)      // keine Enträge vorh.
		return EC_OKAY;

    register ErrCode EC;
    short Count = 1;       // Anz. Tab.-Einträge, Standard-Layer immer ausgeb.
    short Ind = 0;
    const short BufferSize = 7;
    char Buffer [BufferSize];

    memset (Buffer, ' ', BufferSize - 1);
    Buffer [BufferSize-1] = '\0';

//  Layer-Table-Kopf
    if ((EC = ExportRecord (fh, 0, "TABLE")) < 0)
	    return EC;
    if ((EC = ExportRecord (fh, 2, "LAYER")) < 0)
	    return EC;

    long CountPos = _llseek (fh, 0L, SEEK_CUR);                 // Anz.-Pos. merken

    if ((EC = ExportRecord (fh, 70, Buffer)) < 0)       // Dummy-Zeile raus
	    return EC;


//  Vergleichsliste aufbauen
    CTable Tb (*this);

    long *pIdList = new long [Cnt + 1];
    if (! pIdList) {
		DEX_Error (RC_ACADDXF, EC_NOMEMORY);
		return EC_NOMEMORY;
    }
    for (Ind = 0; Ind < Cnt; Ind++)
		pIdList [Ind] = 0L;

//  alle IDs sammeln
    for (Ind = 0, Tb.First (); Tb.Valid (); Tb.Next (), Ind++) {
		ExtIdentDescriptionLock pId (Tb);
		if (!pId) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	continue;
		}
		pIdList [Ind] = pId -> ID ();
    }

//  Tabellen ausgeben/ für jeden ID nur eine Tabelle
    for (Tb.First (); Tb.Valid (); Tb.Next ()) { // alle Namen suchen
		ExtIdentDescriptionLock pID (Tb);
		if (!pID) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	continue;
		}

    //  Standard-Layer wurde schon ausgegeben
		if (!lstrcmp (pID -> KurzText (), StandardLayerName))
	    	continue;

    //  wurde Layer schon ausgegeben ?
		long ActID = pID -> ID ();
		Bool Output = True;
		for (Ind = 0; Ind < Cnt; Ind++) {
	    	if (pIdList [Ind] == ActID) {
				Output = False;
				break;
	    	}
		}
		if (Output)
	    	continue;

		Count++;            // Anzahl Layer erhöhen
		if ((EC = ExportRecord (fh, 0, "LAYER")) < 0) // Tabellen-Kopf
	    	break;
		if ((EC = ExportRecord (fh, 2, pID -> KurzText ())) < 0)// Name
	    	break;
		if ((EC = ExportRecord (fh, 70, StandardLayerFlag)) < 0) // Flag
	    	break;

     // Farbe auswerten
		VisInfo *pVI = &pID -> VisInfoObj ();
		Color Farbe (0,0,0);
		if (pVI)
		{
			if ((pVI -> isA () ==  VT_Flaeche) && (pVI -> Style () != 0))
	    		Farbe = ((FVisInfo *) pVI) -> SecColor ();      // Füllfarbe
			else
				Farbe = pVI -> PrimColor ();					// Randfarbe
		}
		ushort AcadFarbe = (ushort) GetAutoCADFarbe (*(COLORREF*) &Farbe);
		wsprintf (Buffer, "%6u", AcadFarbe);
		if ((EC = ExportRecord (fh, 62, Buffer)) < 0) // Farbe
	    	break;

     // Typ bestimmen
		char Typ;
		if (pVI)
		{
			switch (pVI -> isA ()) {
	    		case  VT_Flaeche:
					Typ = 'F';
	    		break;
	    		case  VT_Punkt:
					Typ = 'P';
	    		break;
	    		case  VT_Linie:
					Typ = 'L';
	    		break;
	    		case  VT_Text:
					Typ = 'T';
	    		break;
	    		case  VT_Default:
	    		default:
					Typ = 'U';
	    		break;
			}
		}			
		else
			Typ = 'U';

     // alle Werte in VisInfo-Tabelle ausgeben
		char ColBuffer [80];
		wsprintf (ColBuffer, "%-32.32s%5d%5d%5d%5d%5d%2c", pID -> KurzText (),
		     	(ushort) Farbe.Red (), (ushort) Farbe.Green (),
				(ushort) Farbe.Blue (), (ushort) AcadFarbe, pVI ? pVI -> Priority () : 0, Typ);
		if ((EC = ExportLine (cfh, ColBuffer)) < 0)
	    	break;

    //  Linientyp auswerten
		char LineType [LineTypeSize] = "";
		if (pVI && pVI -> isA () ==  VT_Linie) 
	    	KonvertLineType (pVI -> Style (), LineType);
		else
	    	lstrcpy (LineType, StandardLayerLinTyp);
		if ((EC = ExportRecord (fh, 6,  LineType)) < 0) // Linientyp
	    	break;
		
    //  akt. ID aus Liste löschen --> ist ausgegeben
		for (Ind = 0; Ind < Cnt; Ind++) {
	    	if (pIdList [Ind] == ActID)
				pIdList [Ind] = 0L;
		}
    }   // für alle Ebenen

    DELETE_OBJ (pIdList);   // Vergleichsliste löschen

//  Standard-Layer ausgeben
    if ((EC = ExportRecord (fh, 0, "LAYER")) < 0)           // Tabellen-Kopf
		return EC;
    if ((EC = ExportRecord (fh, 2, StandardLayerName)) < 0)  // Name
		return EC;
    if ((EC = ExportRecord (fh, 70, StandardLayerFlag)) < 0) // Flag
		return EC;
    if ((EC = ExportRecord (fh, 62, StandardLayerFarbe)) < 0) // schwarz
		return EC;
    if ((EC = ExportRecord (fh, 6, StandardLayerLinTyp)) < 0) // Linientyp
		return EC;

//  Ende der Layer-Table
    if ((EC = ExportRecord (fh, 0, "ENDTAB")) < 0)      // Table-Ende
		return EC;

//  Anzahl Tabellen-Einträge schreiben
    _llseek (fh, CountPos, SEEK_SET);
    wsprintf (Buffer, "%6d", Count);
    if ((EC = ExportRecord (fh, 70, Buffer)) < 0)
	    return EC;

    _llseek (fh, 0L, SEEK_END);     // File-Ende

    return EC;
}

// zu einem Objekt den Darstellungsstil über seinen ID suchen
short ExtIdentDescriptionTree :: FindSymbolStyle (long Id) {
    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.FindFirst (&Id); Tb.Valid (); Tb.FindNext (&Id)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return 0;
		}
		pVI = &pIDD -> VisInfoObj ();
		if (pVI && (pIDD -> VisInfoObj ().isA () ==  VT_Punkt))
	    	return ((VisInfo &) (pIDD -> VisInfoObj ())).Style ();
    }
    return 0;   // nicht gefunden
}

// Symbole in Datei ausgeben, die zuvor in entsprechendem Modus
// geöffnet worden sein muß.
ErrCode ExtIdentDescriptionTree :: OutputSymbole (int fh, short StandardSymbol, 
												  MFELD *pMF) {

    register ErrCode EC = EC_OKAY;
    char Buff [10] = "";

//  Standard-Symbol speichern
    SymbolNummernBaum SNB;
    if (! SNB.AddNummer (StandardSymbol))
		return EC_NOMEMORY;

    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.First (); Tb.Valid (); Tb.Next ()) { // alle Einträge beh.
		ExtIdentDescriptionLock pID (Tb);
		if (pID) {
	    	pVI = &pID -> VisInfoObj (); // Visualisierungs-Info
	    	if (!pVI || (pVI -> isA () !=  VT_Punkt))
				continue;

	    	CTable STb (SNB);
	    	if (STb.Find (&pVI -> Style ())) // wenn Nummer bereits existiert
				continue;

		//  neue Symbol-Numer speichern
	    	if (! SNB.AddNummer (pVI -> Style ()))
		    	return EC_NOMEMORY;

	    	if ((EC = ExportRecord (fh, 0, "BLOCK")) < 0)
				return EC;
	    	if ((EC = ExportRecord (fh, 8, "0")) < 0)
				return EC;

		//  Blockname
	    	if ((EC = ExportRecord (fh, 2, itoa (pVI -> Style (), Buff, 10))) < 0)
				return EC;

		//  Attribute-Folgen-Flag setzen
	    	if ((EC = ExportRecord (fh, 70, (ValidMKodes) ? "    66" : "    64")) < 0)
				return EC;

		//  Symbol-Körper ausgeben
	    	if (!OutputResourceTemplate (pVI -> Style (), fh))
				return EC_NOSYMBOL;

		//  bei Anforderung die Attribut-Definitionen ausgeben
	    	if (ValidMKodes && pMDT)
				if ((EC = pMDT -> OutputAttrDef (fh, pMF)) < 0)
		    		return EC;

	    	if ((EC = ExportRecord (fh, 0, "ENDBLK")) < 0)
				return EC;
	    	if ((EC = ExportRecord (fh, 8, "0")) < 0)
				return EC;
		}
    }

    return EC;
}

// Linienbreite eines Objektes über seinen ID suchen,
// die im Fehlerfall 0 ist
short ExtIdentDescriptionTree :: FindWidth (long ID, AcadTyp ATyp) {
    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return 0;
		}

		pVI = &pIDD -> VisInfoObj ();
		if (!pVI)
			continue;

		short TTyp = pVI -> isA ();
		if (ATyp == A_PLinieClosed && TTyp ==  VT_Flaeche)
	    	return (((FVisInfo &) (pIDD -> VisInfoObj ())).Width ());

		if (ATyp == A_PLinie && TTyp ==  VT_Linie)
	    	return (((LVisInfo &) (pIDD -> VisInfoObj ())).Width ());
    }
    return 0;       // Objekt nicht gefunden oder anderer Fehler
}

// optimiert Baum und FarbBaum
void ExtIdentDescriptionTree :: Optimiere (void)
{
    Optimize ();     // diesen Baum optimieren
}

//  AutoCAD-Farbe bilden
short ExtIdentDescriptionTree :: GetColor (GSTRUCT &GS) {
    Bool Found = False;
    VisInfo *pVI = NULL;
	CTable Tb (*this);
    for (Tb.FindFirst (&GS.Id); Tb.Valid (); Tb.FindNext (&GS.Id)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	return StandardFarbe;
		}

		pVI = &pIDD -> VisInfoObj ();
		if (pVI)
		{
			short Typ = pVI -> isA ();
			switch (GS.Typ) {
	    		case OT_KANTE:
					if (Typ ==  VT_Linie)
		    			Found = True;
	    		break;
	    		case OT_PUNKT:
					if (Typ ==  VT_Punkt)
		    			Found = True;
	    		break;
	    		case OT_FLAECHE:
					if (Typ ==  VT_Flaeche)
		    			Found = True;
	    		break;
	    		case OT_TEXT:
					if (Typ ==  VT_Text)
		    			Found = True;
	    		break;
	    		default:
	    		break;
			}
		}

    //  wenn ID gefunden
		if (Found) {
			Color Farbe (0,0,0);
			VisInfo *pVI = &pIDD -> VisInfoObj (); // Visualisierungs-Info
			if (pVI)
			{
	    		if ((pVI -> isA () ==  VT_Flaeche) && (pVI -> Style () != 0))
					Farbe = ((FVisInfo *) pVI) -> SecColor ();  // Füllfarbe
	    		else
					Farbe = pVI -> PrimColor ();                // Randfarbe
			}
	    	return (short) GetAutoCADFarbe (*(COLORREF*) &Farbe);
		}
    }

    return StandardFarbe;
}

pchar ExtIdentDescriptionTree :: GetLineType (GSTRUCT &GS, pchar pTyp) {
    lstrcpy (pTyp, StandardLayerLinTyp);

//  prüfe Parameter
    if (GS.Typ != OT_KANTE && GS.Typ != OT_FLAECHE) {
		DEX_Error (RC_ACADDXF, EC_SYSERROR);
		return pTyp;
    }

//  bei Flächen bis dato kein Typ in TRIAS
    if (GS.Typ == OT_FLAECHE)
		return pTyp;

//  richtigen ID suchen
    CTable Tb (*this);
	VisInfo *pVI = NULL;
    for (Tb.FindFirst (&GS.Id); Tb.Valid (); Tb.FindNext (&GS.Id)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD) {
	    	DEX_Error (RC_ACADDXF, EC_LOCKERROR);
	    	continue;       // nä. Versuch
		}

		pVI = &pIDD -> VisInfoObj ();
		if (pVI && pVI -> isA () == VT_Linie)
	    	return KonvertLineType (pVI -> Style (), pTyp);
    }

	return KonvertLineType (SolidLine, pTyp);
}

//  Linientyp konvertieren
pchar ExtIdentDescriptionTree :: KonvertLineType (short TRIASTyp, pchar LineType) {
    switch (TRIASTyp) {
		case Dashed:
	    	lstrcpy (LineType, "DASHED");
		break;
		case Dotted:
	    	lstrcpy (LineType, "DOT");
		break;
		case Dash_Dot:
	    	lstrcpy (LineType, "DASHDOT");
		break;
		case Dash_Dot_Dot:
	    	lstrcpy (LineType, "DIVIDE");
		break;
		case SolidLine:
		default:
	    	lstrcpy (LineType, StandardLayerLinTyp);
		break;
     }

    return LineType;
}
