/*
File: TOOLS.HPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 4.12.1994
*/

#ifndef _TOOLS_HPP
#define _TOOLS_HPP

//  neuen Identifkator in der PBD erzeugen
//  (falls noch nicht vorhanden)
// ErrCode CreateIdent (ulong ID, const char *pIDText);

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
// ErrCode CreateMerkmal (ulong MK, const char *pText, short MaxLen);

//  Unique-Ident-Merkmal für Objekt ausgeben
ErrCode OutputUniqueIdent (long ObjNr);

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long ObjNummer, ulong MerkmalsKode, const char *pMerkmalsText);

//  Geometrie eines Punktes ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunkt (double KoordX, double KoordY, ulong ID);

//	Punkt-Geometrie modif.
BOOL ModPunktGeometrie (long lObjNr, double dX, double dY);
		       
#endif	// TOOLS_HPP
