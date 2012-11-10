/* Deklarationen fuer ATLPARSER                                 */
/* File: ATLPARS.H                                              */

/* ATLPARSER: %W%       %E%
 */

#if !defined(_ATLPARS_H)
#define _ATLPARS_H

#define STRINGLEN       256

#define NAMELEN         32
#define IDLEN			33
#define BACKSLASH       '\\'

#define DEFAULTUNIQUEIDENT 	51200000L
#define DEFAULTNAME4		50000000L

/* Groesse der Informationsfelder */
#define MAXGI   100000
#define MAXMI   5000
#define MAXLOCH	5000

/* Yacc-Stacktypen */
typedef struct tagSTRINGTOKEN {        /* String-Token */
	int str_line;
	char string[STRINGLEN+1];
} STRINGTOKEN;

typedef struct tagNUMBERTOKEN {        /* Integer-Token */
	int num_line;
	long intnum;
} NUMBERTOKEN;

typedef struct tagFLOATTOKEN {        /* Float-Token */
	int flt_line;
	double fltnum;
} FLOATTOKEN;

// String --> HexZahl
#define xtol(cptr)	strtoul(cptr,NULL,16)

/* Datendeklarationen */
extern long on;                 /* Objektnummer */
extern long id;                 /* Identifikator */
extern char ID[IDLEN];			/* Identifikator-char */
extern char IdInBuffer[IDLEN];			/* Identifikator-char */
extern double *gxi;             /* Geometrieinformation */
extern double *gyi;
extern long lgi;                /* Anzahl der Koordinatenpaare */
extern long maxgi;              /* Feldgr”áe Geometrie */

/* sonstige Variablen */
extern int koord_paare;         /* Anzahl der Stuetzpunkt eines EO's */
extern long mi_code;            /* Merkmalscode von name2 */
extern long u_code;		/* Merkmalscode Unique ident */
extern int mi_werte;            /* Anzahl der Merkmalswerte */
extern int mi_length;           /* Laenge der Merkmalswerte */
extern char mi_typ;             /* Merkmalstyp */
extern int satz_nr;             /* Satznummer in ASCII-Datei */
extern char name1[STRINGLEN+1]; /* name1 aus ATLAS-Austauschdatei */ 
extern char txt[STRINGLEN+1];   /* name2 aus ATLAS-Datei, Objektname */
extern char uident[STRINGLEN+1]; /* Unique Ident der Atlas*Gis - Datei */
extern char name4[];		/* Name4 */
extern long name4_code;		// MCode für Name4
extern int d_flag;

extern char HFile[];		// HeaderDateiName

extern int flen;                /* Identifikatorstellenzahl */
extern long fmin;               /* minimaler Identifikator */
extern long idst;               /* Standardidentifikator */

extern int yylineno;		/* Zeilennummer */

extern long Znr;		/* Nr des BO */

extern double g_dKoeff;		// zusätzlicher Skalierungskoeffizient

/* Funktionsprototypen */ 
void print_hdr (long UCode);	/* Dateikopf ausgeben */
void print_trailer (void);	// EndeSatz schreiben
void save_object (void); 	/* Objekt ausgeben */
void save_point (void); 	/* Punkt ausgeben */
void save_line (void);		/* Linie ausgeben */
void save_area (void);		/* Flaeche ausgeben */
void init_new_object (void);    /* Naechstes Objekt initialisieren */
char *read_string (char *);             /* Rest der Zeile einlesen */
void yyerror (char *);
int yylex (void);

double ginhed (double *, double *, long *, long *);
long iglaged (double *, double *, double *, double *, double *, double *);
long igppted (double *, double *, double *, double *, long *, long *);
void igumoed (double *, double *, long *, long *);

// C++ -Routinen --------------------------------------------------------------
void MIOpen (char *lpFileName);
short ExtractMI (char *pKey, long *pMCode, short *pMTyp, char *pMText, short maxLen);
short NextMI (long *pMCode, short *pMTyp, char *pMText, short maxLen);
void ReleaseMTree (void);

#endif // _ATLPARS_H
