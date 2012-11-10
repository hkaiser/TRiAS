//	Definitionen für Attributverarbeitung
//	File:DEFINE.H


#if !defined(_DEFINE_H)
#define _DEFINE_H
//Nur fuer Sorge
#define TPZEILEN	50

//Allgemeine define-Anweisungen

#define TEXTLEN 	32
#define MAXFCTNAME	32
#define MAXKEY	512

// Arten von MerkmalRecherchen
#define MISicht			0	//Sicht
#define MISegment		1	//Segment der Sicht
#define MIFenster		2	//Objekte OR
#define MI2Fenster		3	//Objekte in 2 OR

// Modi von MerkmalRecherchen
#define MIExistiert		0	//Merkmal vorhanden.
#define MIExistiertNicht	1	//Merkmal nicht vorhanden.
#define MIExakt			2	//Merkmal vollst.
#define MITeilMenge		3	//Teilmenge
#define MINichtVorhanden	4	//inverse Recherche
#define MIWertAnfang		5	//Zeichen am Anfang
#define MIWertEnde		6	//Zeichen am Ende
#define MIWertLaenge		7	//Maximale Laenge der Zeichenkette


//ObjektStruktur
typedef struct OBJECTTYP {
//-----------Klasse------------
	long lIdent;
	long lMCode;
	short iGITyp;
} OBJECTTYP;


typedef struct OBJPOINT {
	class OBJTree *pOBJ;
	class IDMTree *pIdent;
} OBJPOINT;


typedef struct MCVERGLEICH {
	long lObj;
	long lMCode;
	short iTyp;
	char *pVText;
} MCVERGLEICH;

//Doppeln von Strings
char *StrDuplicat ( char *);

// DtoA-Modifikation
char * PASCAL ST_DtoA (char _far *, char _far *, double);

//Merkmalskode einer GeoDB in ListBox
extern "C" Bool PASCAL _XTENSN_EXPORT FillMKListBox (long , Bool, void *);
//Identifikator nach GITyp einer GeoDB-Sicht in ListBox
extern "C" Bool PASCAL _XTENSN_EXPORT GetIdentWithTyp (long , DWORD , void *);
//Identifikator nach GITyp einer GeoDB-Sicht in ListBox
extern "C" Bool PASCAL _XTENSN_EXPORT GetIdentWithPoint (long , DWORD , void *);
//Identifikator nach GITyp einer GeoDB-Sicht in ListBox und Baum
extern "C" Bool PASCAL _XTENSN_EXPORT StoreIdentWithTyp (long , DWORD , void *);
//Identifikator nach GITyp einer GeoDB-Sicht in ListBox
extern "C" Bool PASCAL _XTENSN_EXPORT GetIdents (long , Bool , void *);
//Identifikator nach GITyp einer Sicht
extern "C" Bool PASCAL _XTENSN_EXPORT SearchObjects (long , DWORD , void *);
//Identifikator nach GITyp eines Sichtausschnittes
extern "C" Bool PASCAL _XTENSN_EXPORT SearchIdentObjects (long , Bool , void *);
//Identifikator nach GITyp eines Sichtausschnittes
extern "C" Bool PASCAL _XTENSN_EXPORT EnumObjectsWithStatus (long , Bool , void *);
//Partner suchen
extern "C" Bool PASCAL _XTENSN_EXPORT FindePartner (long , Bool , void *);
//MK-Partner suchen
extern "C" Bool PASCAL _XTENSN_EXPORT SucheMKPartner (long , Bool , void *);
//Idents suchen
extern "C" Bool PASCAL _XTENSN_EXPORT AufbauIDListe (long , DWORD , void *);

#endif
