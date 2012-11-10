// Definitionen fÅr Teilprojekterweiterung ------------------------
// File: DEFPROJ.H

#if !defined(_DEFPROJ_H)
#define _DEFPROJ_H

class TPRJTree;

#define MCODESIZE 12
#define TEXTLEN 32

const short MaxExtension = 50;
const short MaxKey = 61;
const short MaxParmLine = 256;

const int START = 7;

//Mod-Funktionen
#define MF_DeleteKey 	1
#define MF_AddKey 	2
#define MF_ModKey 	3
#define MF_ModProject 	4

typedef struct DBPROJECT {
	char * pKey;
	char * pDBName;
	char * pUserName;
	char * pSightName;
	char * pDrive;
	char * pPath;
	char * pExt;
	char * pOwner;
	char * pPrev;
	char * pNext;
//------------------------------
	short iStatus;
	short iLevel;
	short iPrevMenuPoint;
//-----------Container----------
	long lXmin;
	long lXmax;
	long lYmin;
	long lYmax;
	class TPRJTree *pTPRJ;
} DBPROJECT;

typedef struct MODMENU {
	char * pKey;
	char * pDBName;
	char * pReferenz;
	short iMenuNr;
	short iModKZ;
	short iStatus;
} MODMENU;


typedef struct TPPOINT {
	class TPRJTree *pTPRJ;
	long *pObjPos;
	long *pObjNeg;
	long TPMCode;
} TPPOINT;

//	"Lˆschen" der Struktur
void SetZero ( struct DBPROJECT *);

//	"Lˆschen" der Struktur
void SetModZero ( struct MODMENU *);

// 	Doppeln von Strings
char * StrDuplicat ( char *);

// noch unbekannt
void MyStrupr ( char *, short);

// KK010517
Bool WriteIniFile ( ResString Projects, char *pOem, char *pProject, char *pIni );
Bool WriteIniFileEx ( ResString Projects, char *pOem, char *pProject, char *pIni );
Bool WritePrivateIniFile(void);
Bool IniEqualToTemp( char *, char *);

// KK010608
Bool FileExist(const char *);

//Globale Enumerationsfunktionen
extern "C" BOOL PASCAL _XTENSN_EXPORT SucheSichtDQ (long, Bool , void *);
extern "C" Bool PASCAL _XTENSN_EXPORT FillTPMCListBox (long , Bool, void *);
extern "C" Bool PASCAL _XTENSN_EXPORT EnumTPMCode (long , Bool, void *);
extern "C" Bool PASCAL _XTENSN_EXPORT NumTPObjects (long , Bool, void *);
extern "C" BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, bool , void *pData);

#endif // _DEFPROJ_H
