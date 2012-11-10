%{
/* ATLAS*GIS-ASCII-Format: Analyse                              */
/* File: ATLPARS.Y                                              */

#if defined(sccs)
static char SccsId[] = "ATLPARS: %W%    %E%";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atlpars.h"
#include "atlerrs.h"

/* Informationsfelder */
long on = 0;                    /* Objektnummer */
long Znr = 0;			/* Z„hlnummer BO */
long id = 0;                    /* Identifikator */
char ID[IDLEN];
char IdInBuffer[IDLEN];
long lgi = -1;                  /* Anzahl der Koordinatenpaare */
double *gxi;              	/* Geometrieinformation */
double *gyi;

/* sonstige Variablen */
int koord_paare;                /* Anzahl der einzulesenden Koordinatenpaare */
long mi_code = 51100000;        /* Merkmalscode von name2 */
long u_code = DEFAULTUNIQUEIDENT; /* Merkmalscode fr Unique Ident */
int mi_werte = 1;               /* Anzahl der Merkmalswerte */
int mi_length;                  /* Laenge der Merkmalswerte */
char mi_typ = 'A';              /* Merkmalstyp */
int satz_nr = 0;                /* Nummer des Objektes im ASCII-File */
int objekt_nr = 0;              /* Nummer des Satzes im ASCII-File */
char name1[STRINGLEN+1];        /* name1 aus ATLAS-Austauschdatei */
char txt[STRINGLEN+1];          /* name2 aus ATLAS-Datei, Objektname */
char uident[STRINGLEN+1];	/* Unique Ident aus Atlas-Datei */
char name4[STRINGLEN+1];	/* Name4 (#HK930510) */
long name4_code = DEFAULTNAME4;	// MCode fr Name4

/* globale Daten */
long eps = 0;                   /* Testtoleranz */

// #define min(x,y) (((x)>(y))?(y):(x))

/* lokale Daten */
int hcpkt = 0;

extern int 	y_flag;

#if defined(_MSC_VER)
#pragma warning (disable: 4101 4102)
#endif // _MSC_VER

%}


%start  BNADatei

%union {
	struct tagSTRINGTOKEN strtok;
	struct tagNUMBERTOKEN numtok;
	struct tagFLOATTOKEN flttok;
}

%token  <strtok>        T_STRING T_STERN T_LBDA T_PHI
%token  <numtok>        T_INT '\n'
%token  <flttok>        T_FLOAT 
%type	<flttok>	Int_oder_Float

%%

BNADatei:	{			
			print_hdr (u_code);	// KopfSatz schreiben
		}
		BNADateiKoerper
		{
			print_trailer ();	// EndeSatz schreiben
		}
	;

BNADateiKoerper:	Elemente
	;

Elemente:	Element
	|       Elemente Element
	;
	
Element:        Elementkopf Koordinaten
		{
			save_object();
		}
	;

Elementkopf:    T_STRING "," T_STRING "," T_STRING "," T_INT "\n"
		{       
			on++;
			if (y_flag) {
				if (d_flag)	id = atol ($1.string);
				else		id = xtol ($1.string);
			} else {
				strcpy (IdInBuffer, $1.string);
			}
			strncpy (txt, $3.string, STRINGLEN);
			strncpy (name1, $1.string, STRINGLEN);
			koord_paare = $7.intnum;
// neu: 15.3.92(KK): UNIQUE ident ist unter '$5.string' verfügbar
			strncpy (uident, $5.string, STRINGLEN);
			name4[0] = '\0';
			init_new_object();
		}
	|	T_STRING "," T_STRING "," T_STRING "," T_STRING "," T_INT "\n"
		{       
			on++;
			if (y_flag) {
				if (d_flag)	id = atol ($1.string);
				else		id = xtol ($1.string);
			} else {
				strcpy (IdInBuffer, $1.string);
			}
			strncpy (txt, $3.string, STRINGLEN);
			strncpy (name1, $1.string, STRINGLEN);
			koord_paare = $9.intnum;
			strncpy (uident, $5.string, STRINGLEN);
			strncpy (name4, $7.string, STRINGLEN);
			init_new_object();
		}
	|       T_STRING "," T_STRING "," T_INT "\n"
		{       
			on++;
			if (y_flag) {
				if (d_flag)	id = atol ($1.string);
				else		id = xtol ($1.string);
			} else {
				strcpy (IdInBuffer, $1.string);
			}
			strncpy (txt,$3.string,STRINGLEN);
			strncpy (name1,$1.string,STRINGLEN);
			koord_paare = $5.intnum;
			name4[0] = '\0';
			init_new_object();
		}
	|       T_STRING "," T_INT "\n"
		{       
			on++;
			if (y_flag) {
				if (d_flag)	id = atol ($1.string);
				else		id = xtol ($1.string);
			} else {
				strcpy (IdInBuffer, $1.string);
			}
			strncpy (name1,$1.string,STRINGLEN);
			txt[0]='\0';
			koord_paare = $3.intnum;
			name4[0] = '\0';
			init_new_object();
		}
	|       T_STERN "," T_STRING "," T_STRING "," T_INT "\n"
		{                            
			on++;
			strncpy (txt,$3.string,STRINGLEN);
// neu: 15.3.92(KK): UNIQUE ident ist unter '$5.string' verfügbar
			strncpy (uident, $5.string,STRINGLEN);
			koord_paare = $7.intnum;
			name4[0] = '\0';
			init_new_object();
		}
	|       T_STERN "," T_STRING "," T_INT "\n"
		{       
			on++;
			strncpy (txt,$3.string,STRINGLEN);
			koord_paare = $5.intnum;
			name4[0] = '\0';
			init_new_object();
		}
	|       T_STERN "," T_INT "\n"
		{       
			on++;
			txt[0]='\0';
			koord_paare = $3.intnum;
			name4[0] = '\0';
			init_new_object();
		}       
	;

Koordinaten:    Koordinate
	|       Koordinaten Koordinate
	;
	
Koordinate:     Int_oder_Float "," Int_oder_Float "\n"
		{
			lgi += 1;
			gyi[lgi] = $3.fltnum;
			gxi[lgi] = $1.fltnum;
		}
	;

Int_oder_Float:	T_INT
		{
			$$.fltnum = (double)$1.intnum;
		}
	|	T_FLOAT
		{
			$$.fltnum = $1.fltnum;
		}
	;

