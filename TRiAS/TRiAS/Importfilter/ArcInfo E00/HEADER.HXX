/*
Datei: HEADER.HXX

Das Modul beinhaltet eine Klasse zum Lesen/Schreiben des Headers
einer TRIAS-Datenbank.

erarbeitet : J. Benkenstein                 Stand vom 7. Januar 1994
*/

#ifndef _HEADER_HXX
#define _HEADER_HXX

//  Konvertiere "double" nach ASCII (scientific format)
// Prototypen
char *DtoA (double Wert, char *String, char *Format = NULL); 
// pchar DtoA (pchar pOutBuffer, double Value);

#ifndef NOHEADER
// Ausgabe des ASCII-Headers
class Header {
protected:
	// allg. Funktion zum Lesen eines Merkmalskodes
    Bool _GetMerkmalsKode (ulong &MK,             // voreingestellter Kode
			   			   char *pHeaderText);

	double Check (double dVal, BOOL bDirect);

public:
//  Konstruktor
    Header (void) {}
    ~ Header (void) {}

//  Memberfunktionen
    Bool OutScaleAndOffset (double *pKoord);

//  unique Ident lesen
    Bool GetUniqueIdent (ulong &,ulong ID = 0);				// voreingestellter Kode

//  Merkmalskode für Textwert lesen
    Bool GetTextObjMKode (ulong &, ulong ID = 0);				// voreingestellter Kode
};	
#endif  // NOHEADER

#endif //_HEADER_HXX
