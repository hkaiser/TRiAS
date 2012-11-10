/* Deklarationen fuer ASCPARSER					*/
/* File: ASCPARS.H						*/

/* ASCPARSER: %W%	%E%
 */

/* Objekttypen */
#define E_OBJEKT	1
#define K_OBJEKT	2
#define O_PUNKT		1
#define O_LINIE		2
#define O_FLAECHE	3
#define O_TEXTOBJEKT	4
#define O_TEXTOBJIND	5

/* Merkmalstypen */
#define	M_INTEGER	1
#define M_DOUBLE	3
#define M_TEXT		0

#define STRINGLEN 	_MAX_PATH
#define NAMELEN		32
#define BACKSLASH	'\\'

#define TEXTOBJMCODE	1000000000L	// MCode für TextObjekte

/* Yacc-Stacktypen */
typedef struct {	/* String-Token */
	int str_line;
	char string[STRINGLEN+1];
} STRING_TOKEN;

typedef struct {	/* Integer-Token */
	int num_line;
	long intnum;
} NUMBER_TOKEN;

typedef struct {	/* Float-Token */
	int flt_line;
	double fltnum;
} FLOAT_TOKEN;

/* Datendeklarationen */
extern long eps;		/* Testtoleranz */
extern long on;			/* Objektnummer */
//extern long id;			/* Identifikator */
extern char cbOKS[64];	// Objektklassenschlüssel
extern long sta[];		/* Status */
extern long mi[];		/* Merkmalsinformation */
extern double gxi[];		/* Geometrieinformation */
extern double gyi[];
extern long lgi;		/* Anzahl der Koordinatenpaare */
extern long maxgi;		/* Feldgroesse Geometrie */

extern int mi_count;		/* Zaehler der Merkmalswerte */

/* sonstige Variablen */
extern int koord_paare;		/* Anzahl der Stuetzpunkt eines EO's */
extern int mi_werte;		/* Anzahl der Merkmalswerte */
extern int satz_nr;		/* Satznummer in ASCII-Datei */

extern long *curr_mi;		/* aktuelle Merkmalswerte */
extern char *curr_mi_text;

extern char UIdent[];		// VorString zu Unique Ident

extern long lUIdent;
extern long lMCode;
extern long Name4Code;

extern FILE *fpout;		/* Protokolldatei */
extern FILE *fpmkl;
extern FILE *fphead;

extern int yylineno;		/* Zeilennummer */

extern long lTextObjMCode;	// MerkmalsCode der Texte an Textobjekten

/* Funktionsprototypen */
int end_previous_object (void);	/* Objekt bearbeiten */
void init_new_object (void);	/* Naechstes Objekt initialisieren */
int error_skip_lines (char *, int);	/* Objekt ueberspringen, Fehler melden */
void skip_lines (char *);		/* Objekt ueberspricngen */
char *read_string (char *);		/* Rest der Zeile einlesen */
int next_line (void);
unsigned long MakeHex (unsigned long);

// DB-Header schreiben
int PutHdFlt (double, char *);
int PutHdString (char *, char *);
int EvalKoeffs (double *, double *, double *, double *);	// inverse Matrix berechnen

// Schnittstelle zum Parser/Scanner
int yyparse (void);
int yylex (void);

// Kommandozeilenparameter
extern int s_flag;		// SilentFlag
extern int a_flag;		// alle Merkmale in MKL
extern int b_flag;		// abhängige Begleitobjekte generieren
extern int t_flag;		// keine Textobjekte
extern int i_flag;		// Identifikator als Name4 ausgeben

extern double dKoeff;

//void putbna (long id, long *sta, long *mi, long lgi, double *gxi, double *gyi);
void putbna (char *cbOKS, long *sta, long *mi, long lgi, double *gxi, double *gyi);
void bna_open (void);
void mkl_open (void);
void head_open (void);

///////////////////////////////////////////////////////////////////////////////
// Makros für RelationsTypen
#define UREL	0x01					// Relation von Unten
#define OREL	0x02					// Relation von Oben (ist KomplexObjekt)
#define OUREL	(OREL|UREL)				// beides

#define GREL	0x04					// gleichrangige Relation existiert

#define BRELA	0x08					// hat BegleitObjekt
#define BRELP	0x10					// ist BegleitObjekt
#define BRELAP	(BRELA|BRELP)			// beides

#define HREL(x)		((x)&GREL)			// Zugriffsfunktionen
#define VREL(x)		((x)&OUREL)
#define VRELO(x)	((x)&OREL)
#define VRELU(x)	((x)&UREL)
#define KREL(x)		((x)&(OUREL|GREL))	// Komplexrelationen
#define BREL(x)		((x)&BRELAP)		// Begleitrelationen

