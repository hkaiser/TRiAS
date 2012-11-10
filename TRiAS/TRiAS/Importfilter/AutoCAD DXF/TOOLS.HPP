/*
File: TOOLS.HPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 8.1.1994
*/

#ifndef _TOOLS_HPP
#define _TOOLS_HPP

//	Wert auf 2 Stellen nach dem Komma abschneiden
void SetTwoDec (char *pText);

//  neuen Identifkator in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateIdent (ulong ID, char *pIDText);

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
//ErrCode CreateMerkmal (ulong MK, char *pText, short MaxLen);
ErrCode CreateMerkmal (ulong MK, char *pText, short MaxLen, ulong ID = 0L);

//  Unique-Ident-Merkmal für Objekt ausgeben
ErrCode OutputUniqueIdent (long ObjNr, ulong ulID);

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long ObjNummer, ulong MerkmalsKode, pchar pMerkmalsText);

//  Geometrie eines/r Punktes/Linie ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunktLinie (double *pKoordX, double *pKoordY, ulong ID,
			   		   long Cnt = 1,         // 1 Stützpunkt
		       		   Bool Typ = True);     // Punkt, False --> Linie
		       
		       
//  Geometrie einer Fläche ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputFlaeche (double *pKoordX, double *pKoordY, long Cnt, ulong ID);

//	Textobjekt an TRiAS ausgeben
long OutputText (char *pText, double dKoordX, double dKoordY, ulong ulID);

#endif	// TOOLS_HPP
