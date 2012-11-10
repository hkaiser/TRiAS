/*
File: IDENTDES.HXX
realiert die Verwaltung einer Identifikator-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein                 Stand vom 13. April 1994
*/

#ifndef _IDENTDES_HXX
#define _IDENTDES_HXX

// Symbol-Nummer-Objekt
class SymbolNummer
{
//  Attribute
    short _Nr;

public:
//  Konstruktor/Desttruktor
    SymbolNummer (short Nr) { _Nr = Nr; }
    ~ SymbolNummer (void) {}

    short & Nummer (void) { return _Nr; }

    friend int CompareNr (void *Obj1, void *Obj2);
    friend void* GetNr (void *Obj);
};

// Symbol-Nummern-Baum
class SymbolNummernBaum : public CTree
{
protected:
    void /*XX EXPORTFLT*/ UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    SymbolNummernBaum (void);
    ~ SymbolNummernBaum (void); // Bauminhalt löschen

    // True, wenn neue Symbol-Nummer im Baum gespeichert, falls noch
    // nicht vorhanden, sonst False.
    Bool AddNummer (short SymbolNr);
};
DeclareLock (SymbolNummernBaum, SymbolNummer);

//  erweiterte Identifikator-Beschreibungsklasse
class ExtIdentDescription : public IdentDescription
{
private:
//  Attribute
    double _Rot;            // Drehwinkel
    double _Skal;           // Skalierungs-Faktor für x und y

//  Konstruktor/Destruktor
public:
    ExtIdentDescription (IdentDescription &IDD, double Rot = 0, double Skal = 0)
    : IdentDescription (IDD) { _Rot = Rot; _Skal = Skal; }
    ~ ExtIdentDescription (void) {}

//  weitere Member
    double &Rotation (void) { return _Rot; }
    double &Skalierung (void) { return _Skal; }
};

// Die Klasse IdentDescriptionTree verwaltet erweiterte Identifikator-Beschrei-
// bungen in einem Baum.
class ExtIdentDescriptionTree : public CTree
{
private:
//  Attribute
    Bool _Result;               // Konstruktor-Flag
    double _SymGroesse;         // durchschnittliche Symbolgroesse

protected:
    void /*XX EXPORTFLT*/ UserDelete (void *pObj);
public:
// Konstruktor/Destruktor
    ExtIdentDescriptionTree (double SymbolGroesse = 0);
    ~ ExtIdentDescriptionTree (void);          // Bäume ggf. löschen

//  sonstige Member
    Bool AddIDD (IdentDescription &IDD);
				// neue ID-Beschr. in Baum
    pchar FindName (long ID); // zu einem ID seinen Kurztext suchen,
	// der über den Zeiger übergebene Speicher ist wieder freizugeben !
    Bool CheckLayerNames (void); // Layer-Namen säubern
    ErrCode OutputLayerTable (int FileHandle, // Layer-Table ausgeben
			      int ColFileHandle);
    ErrCode OutputSymbole (int FileHandle, short StSymbol, MFELD *pMF); // alle Symbole
				    // ausgeben, Standardsymbol übergeben
    short FindTextHoehe (long ID); // zu einem Text-Objekt über seinen ID die
    short FindTextDrehWinkel (long ID); // Höhe und seinen Drehwinkel bestim-
				    // men, die Werte sind im Fehlerfall 0 ist
    short FindSymbolStyle (long ID); // Darstellungstyp eines Symbols über seinen
			       // ID suchen, der im Fehlerfall 0 ist
    short FindWidth (long ID, AcadTyp Typ); // Linienbreite einse Objektes über
			// seinen ID suchen, die im Fehlerfall 0 ist

    short GetColor (GSTRUCT &GS); // AutoCAD-Farbe bilden

    pchar GetLineType (GSTRUCT &GS, pchar pLinTypeText);

    pchar KonvertLineType (short TRIASTyp, pchar LineType); // Linientyp konvertieren

    void Optimiere (void);  // optimiert Baum und FarbBaum
    ErrCode OutputSymAttrs (int FileHandle, long ID); // Symboldreh-Winkel
	// und Skalierung über geg. Identifikator ausgeben

//  Operatoren
    operator Bool (void) { return _Result == True; }
    Bool operator ! (void) { return _Result == False; }

//  Baum-Zugriffsfunktionen
    friend int CompareExtIDs (void *Obj1, void *Obj2);
    friend void* GetExtID (void *Obj);
};
DeclareLock (ExtIdentDescriptionTree, ExtIdentDescription);

#endif // _IDENTDES_HXX
