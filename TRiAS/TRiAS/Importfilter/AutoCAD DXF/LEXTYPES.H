/*
Datei: lextypes.h

Definition lex-spezifischer Datentypen und Strukturen.

Erarbeitet: J. Benkenstein				begonnen am 2. August 1995
*/

#ifndef LEX_TYPES_H
#define LEX_TYPES_H

const short IGNORE_REC = -1;			// Satz überlesen

// Definition einer Satz-Verarbeitungs-Funktion
typedef short (* HandleValFct)(char *);	

//	Definition der Tabellen
struct TableInfo
{
	short sRecVar;
	HandleValFct pHandleValFct;	
};
typedef TableInfo* pTableInfo;				// zugeh. Zeiger-Def.

//	Definition der Schlüsselwortliste
struct KeyList 
{
	char *pKeyWord;
	short sRetVal;
};
typedef KeyList *pKeyList;					// zugeh. Zeiger-Def.

struct ExtKeyList							// für Entities
{
	char *pKeyWord;
	short sRetVal;
	pTableInfo pTI;		
};
typedef ExtKeyList *pExtKeyList;

#endif 		// LEX_TYPES_H
