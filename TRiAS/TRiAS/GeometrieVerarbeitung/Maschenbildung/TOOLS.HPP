/*
File: TOOLS.HPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 26.9.1996
*/

#ifndef _TOOLS_HPP
#define _TOOLS_HPP

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateMerkmal (LONG lIdent, ULONG MK, char *pText, short MaxLen,
					   BOOL bSystemMerkmal = FALSE, BOOL bReadOnly = FALSE);

//  UniqueIdent-Merkmal für Objekt ausgeben
ErrCode OutputUniqueIdent (long lObjNr, ULONG ulMCode);

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (ULONG lObjNummer, ULONG MerkmalsKode, const char *pMerkmalsText);

//	Merkmal für ein bestimmtes Objekt lesen
char *GetTextMerkmal (long lObjNr, ULONG ulMK, char *pText, short sMaxLen);

//  Geometrie einer Fläche ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  UniqueIdent-Merkmal ausgeben
// long OutputFlaeche (long *pX, long *pY, long lCnt, ULONG ulMCode);

//  Geometrie einer Linie ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  UniqueIdent-Merkmal ausgeben
//	hier etvl. Mörtl'sche Funktion rufen
// long OutputLine (long *pX, long *pY, long lCnt, ULONG ulMCode); 

//	hat Objekt Geometrie-Fehler ?
//	hier nur als Notvarinate implementiert
BOOL HasGeoError (long lObjNr);

//	Repräsentiert das übergebene Objekt eine Fläche ?
BOOL IsFlaeche (long *plX, long *plY, long lCnt);
BOOL IsFlaeche (double *pdX, double *pY, long lCnt);

//	berechne vorzeichenbehafteten Inhalt einer Fläche:
//	+/- --> math. positiver/negativer Umlaufsinn
double FlaechenInhalt (long *plX, long *plY, long lCnt);
double FlaechenInhalt (double *pdX, double *pdY, long lCnt);

LONG GetMerkmalsKode (LONG lONr, UINT uiHdrEntry, UINT uiPbdEntry, BOOL fSystem = FALSE,
					  BOOL fRO = FALSE);

BOOL GetKurzText (ULONG ulCode, short iType, CString& strKText);
double QuasiWinkel (double &dXa, double &dYa, double &dXe, double &dYe);
BOOL Intersection (long lX11, long lY11, long lX21, long lY21, long lX12, long lY12, long lX22,
				   long lY22);
int TurnDirection (long lX1, long lY1, long lX2, long lY2, long lX3, long lY3);

#endif

