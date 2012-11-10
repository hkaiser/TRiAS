/*
File: TOOLS.HXX
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 8.1.1994
*/

#ifndef _TOOLS_HXX
#define _TOOLS_HXX

//  neuen Identifkator in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateIdent (ulong ID, pchar pIDText, pWindow pParent);

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateMerkmal (ulong MK, pchar pText, short MaxLen, ulong ID = 0);

//  Unique-Ident-Merkmal für Objekt ausgeben
ErrCode OutputUniqueIdent (long ObjNr);

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long ObjNummer, ulong MerkmalsKode, pchar pMerkmalsText);

//  Geometrie eines/r Punktes/Linie ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunktLinie (double *pKoordX, double *pKoordY,
			   		   long ArcInfoObjNr,   // interner ArcInfo-ID (nur für Fehlerausgabe)	
			   		   long Cnt = 1,        // 1 Stützpunkt
		       		   Bool Typ = True);     // Punkt, False --> Linie
		       
		       

//  Geometrie einer Fläche ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputFlaeche (double *pKoordX, double *pKoordY, long Cnt,
		    short KCnt,     // Größe des Konturfeldes
		    long *pCnt,    // Konturfeld
		    long ArcInfoObjNr);  // interner ArcInfo-ID (nur für Fehlerausgabe)

#ifndef NOTEXTOBJECT
//  Text-Objekt an TRIAS ausgeben
class TextObject {
private:
//  Attribute
    pchar _pText;
    double _X, _Y;

public:
//  Konstruktor/Destruktor
    TextObject (void);
    ~ TextObject (void);

//  weitere Member-Funktionen
    void AddKoord (double &X, double&Y) { _X = X; _Y = Y; }
    Bool AddText (pchar pText);             // Text speichern
    Bool Output (void);                     // Object an TRIAS ausgeben
};
#endif  // NOTEXTOBJECT

#endif
