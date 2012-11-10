/*
Datei: HEADER.HPP

Das Modul beinhaltet eine Klasse zum Lesen/Schreiben des Headers
einer TRIAS-Datenbank.

erarbeitet : J. Benkenstein                 Stand vom 21. August 1994
*/

#ifndef _HEADER_HPP
#define _HEADER_HPP

#ifndef NOHEADER
// Ausgabe des ASCII-Headers
class Header 
{
protected:
	// allg. Funktion zum Lesen eines Merkmalskodes
    Bool _GetMerkmalsKode (ulong &MK,             // voreingestellter Kode
			   			   char *pHeaderText);

	//	Koordinaten-Container runden
	double Check (double dVal, BOOL bDirect);

public:
//  Konstruktor
    Header (void) {}
    ~ Header (void) {}

//  Memberfunktionen
    Bool OutScaleAndOffset (void);
// KK990927
    Bool GetScaleAndOffset (void);

// KK990927
//	Bool GetUniqueIdent (ulong &);		//  unique Ident Merkmalskode lesen
//	Bool GetTextObjMKode (ulong &);		//  Merkmalskode für Textwert lesen
//	Bool GetTextObjWinkel (ulong &);	//	Merkmalskode für Textdrehwinkel lesen		
//  Bool GetTextObjHoehe (ulong &);		//	Merkmalskode für Texthöhe lesen
//	Bool GetSymObjWinkel (ulong &);		//	Merkmalskode für Symboldrehwinkel lesen		
//	Bool GetComment (ulong &);			//	Merkmalskode für Kommentar lesen

	Bool GetUniqueIdent (ulong &,ulong ID = 0L);		//  unique Ident Merkmalskode lesen
	Bool GetTextObjMKode (ulong &,ulong ID = 0L);		//  Merkmalskode für Textwert lesen
	Bool GetTextObjWinkel (ulong &,ulong ID = 0L);	//	Merkmalskode für Textdrehwinkel lesen		
    Bool GetTextObjHoehe (ulong &,ulong ID = 0L);		//	Merkmalskode für Texthöhe lesen
	Bool GetSymObjWinkel (ulong &,ulong ID = 0L);		//	Merkmalskode für Symboldrehwinkel lesen		
	Bool GetComment (ulong &,ulong ID = 0L);			//	Merkmalskode für Kommentar lesen

	Bool SetTextFlag (void);

//	wird eine Matrix benötigt ?
	Bool MatrixExists (void);
};	
#endif  // NOHEADER

#endif //_HEADER_HPP
