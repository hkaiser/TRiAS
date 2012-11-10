%{
/* ASCII-Format: Analyse, Put etc.                              */
/* File: ASCPARS.Y                                              */

#if defined(sccs)
static char SccsId[] = "ASCPARS: %W%	%E%";
#endif

#include "StdAfx.h"

#include "ascbna.h"
#include "ascerrs.h"

#include "input.h"

// Prototyp von yylex / yyparse
int yylex (void);
int yyparse (void);

// #define yyerrok errfl = 0

/* Informationsfelder */
long on = 0;                    /* Objektnummer */
//long id;                        /* Identifikator */
char cbOKS[64];					// Objektklassenschlüssel
long sta[2] = { E_OBJEKT, 0 };  /* Status */
long mi[MAXMI] = { MAXMI, 0, }; /* Merkmalsinformation */
double gxi[MAXGI];                /* Geometrieinformation */
double gyi[MAXGI];
long lgi = -1;                  /* Anzahl der Koordinatenpaare */
long maxgi = MAXGI;

long *curr_mi = &mi[-1];         /* Merkmalsfeldzeiger */
char *curr_mi_text = (char *)&mi[5]; /* Merkmalsfeldzeiger fuer Text */

int mi_count = 3;               /* Zaehler der I*4 Merkmalsfelder */

/* sonstige Variablen */
int koord_paare;                /* Anzahl der einzulesenden Koordinatenpaare */
int mi_werte = 0;               /* Anzahl der einzulesenden Merkmalswerte */
int mi_length;                  /* Laenge der Merkmalswerte */
int satz_nr = 0;                /* Nummer des Objektes im ASCII-File */
int objekt_nr = 0;              /* Nummer des Satzes im ASCII-File */

/* globale Daten */
long eps = -1;                  /* Testtoleranz */

long lTextObjMCode = TEXTOBJMCODE;	// MerkmalsCode, an dem bei Textobjekten der Text hängt

extern int r_flag;		// Relationen ignorieren
extern int d_flag;

/* lokale Daten */
static char comment[STRINGLEN+1];
static short fFirstIdent = TRUE;

char *UniqueIdentKey = 	"Unique Ident    ";
char *IdentBase =	"IdentBase       ";


%}


%start  AsciiDatei

%union {
	STRING_TOKEN strtok;
	NUMBER_TOKEN numtok;
	FLOAT_TOKEN flttok;
}

%token  <strtok>        T_STRING T_MISTRING

%token  <numtok>        T_INTEGER T_PSATZ T_LSATZ T_FSATZ T_DSATZ
%token  <numtok>        T_GSATZ T_MSATZ T_RSATZ T_TSATZ T_WSATZ
%token  <numtok>        '\n' T_ESATZ T_IDENT T_BSATZ T_ISATZ T_CSATZ
%token	<numtok>		T_VSATZ T_HRELSATZ T_KRELSATZ T_BRELSATZ
%token	<numtok>		T_KOSATZ T_HEXINTEGER

%token  <strtok>        T_KSATZ T_HSATZ T_OFFSET T_SCALE T_ENTRY
%token  <strtok>        T_PBDNAME T_ENTRYROSYS T_ENTRYRO T_ENTRYSYS

%token  <flttok>        T_FLOAT

%type   <numtok>        ElementarObjektTyp ElementSatz IdentifikatorSatz
%type   <numtok>        IntegerMerkmalsSatz FloatMerkmalsSatz StringMerkmalsSatz
%type   <numtok>        RelationsSatz TrennSatz GeometrieSatz KommentarSatz
%type   <numtok>        BeschreibungsSatz HeaderSatz AsciiDateiKoerper
%type   <numtok>        KommentarSaetze ElementSaetze TextObjektSatz
%type	<numtok>		SteuerSatz RelationsTyp

%%

AsciiDatei:     AsciiDateiKoerper EndeSatz
	|       AsciiDateiKoerper
		{
			if (satz_nr > 0) end_previous_object ();
			db_error (ENOEND, ASCPARSER, $1.num_line);
			YYACCEPT;
		}
	;

AsciiDateiKoerper:
		HeaderSatz
	|       HeaderSatz ElementSaetze
	|       KommentarSaetze HeaderSatz
	|       KommentarSaetze HeaderSatz ElementSaetze
	|       ElementSatz 
		{
			db_error (ENOHD, ASCPARSER, $1.num_line);
			YYABORT;
		}
	;

ElementSaetze:  ElementSatz 
	|       ElementSaetze ElementSatz 
	;

ElementSatz:    BeschreibungsSatz
	|       IdentifikatorSatz
	|       IntegerMerkmalsSatz IntegerWertSaetze
	|       FloatMerkmalsSatz FloatWertSaetze
	|       StringMerkmalsSatz StringWertSaetze
	|       RelationsSatz
	|       GeometrieSatz 
	|       TrennSatz
	|       KommentarSatz
	|	TextObjektSatz
	|	SteuerSatz
	|       error '\n'
		{
			yyerrok;
			db_error (EBADRC, ASCPARSER, $2.num_line);
		}
	;

BeschreibungsSatz:
		T_DSATZ T_SCALE T_FLOAT T_FLOAT T_FLOAT T_FLOAT '\n'
		{
			if (fphead)
				fprintf (fphead, "D Scale %lf %lf %lf %lf\n", 
						$3.fltnum, $4.fltnum,
						$5.fltnum, $6.fltnum);

		}
	|       T_DSATZ T_OFFSET T_FLOAT T_FLOAT '\n'
		{
			if (fphead)
				fprintf (fphead, "D Offset %lf %lf\n", 
							$3.fltnum*dKoeff, 
							$4.fltnum*dKoeff);
		}
	|       T_DSATZ T_ENTRY T_STRING T_STRING '\n'
		{
			if (fphead) {
			char KeyString[17];
			short len;

				memset (KeyString, ' ', 16);
				KeyString[16] = '\0';
				strncpy (KeyString, $3.string, 16);
				if ((len = strlen (KeyString)) < 16)
					KeyString[len] = ' ';
				if (!strcmp (KeyString, UniqueIdentKey)) {
				// Unique Ident gegeben
					fprintf (fphead, "; D Entry \"%16.16s\" \"%s\"\n", KeyString, $4.string);
					if (lUIdent == -1L) {
						lUIdent = atol ($4.string);
						if (lUIdent == 0)
							lUIdent = -1L;
					}
				} if (!strcmp (KeyString, IdentBase)) {
		 		// Zahlenbasis für Identifikator einstellen (Hex hat Vorrang)
					if (d_flag) 
						d_flag = (atoi ($4.string) == 10);
				} else
					fprintf (fphead, "D Entry \"%16.16s\" \"%s\"\n", KeyString, $4.string);
			}
		}
	|    
	   T_DSATZ T_ENTRYRO T_STRING T_STRING '\n'
		{
			if (fphead)
				fprintf(fphead, "D EntryRo \"%16.16s\" \"%s\"\n", $3.string, $4.string);
		}
	|       T_DSATZ T_ENTRYSYS T_STRING T_STRING '\n'
		{
			if (fphead)
				fprintf(fphead, "D EntrySys \"%16.16s\" \"%s\"\n", $3.string, $4.string);
		}
	|       T_DSATZ T_ENTRYROSYS T_STRING T_STRING '\n'
		{
			if (fphead)
				fprintf(fphead, "D EntryRoSys \"%16.16s\" \"%s\"\n", $3.string, $4.string);
		}
	|       T_DSATZ T_PBDNAME T_STRING '\n'
		{
			if (fphead)
				fprintf (fphead, "D PbdName \"%s\"\n", $3.string);
		}
	|       T_DSATZ error '\n'
		{
			yyerrok;
			db_error (EBADRC, ASCPARSER, $3.num_line);
		}                       
	;

IntegerWertSaetze:
		IntegerWertSatz
	|       IntegerWertSaetze IntegerWertSatz
	;

FloatWertSaetze:
		FloatWertSatz
	|       FloatWertSaetze FloatWertSatz
	;

StringWertSaetze:
		StringWertSatz
	|       StringWertSaetze StringWertSatz
	;

GeometrieSatz:  T_GSATZ PunktKoordinaten '\n'
	|       T_GSATZ error '\n'
		{
			yyerrok;
			db_error (EKOORD, ASCPARSER, $3.num_line);
		}
	;

HeaderSatz:     T_HSATZ '\n'
		{
			fFirstIdent = TRUE;
		}
	;

IdentifikatorSatz:
		ElementarObjektTyp T_INTEGER T_INTEGER T_INTEGER '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

	l_Ident:
			if (fFirstIdent) fFirstIdent = FALSE;

		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) 
				end_previous_object ();

		/* Plausibilitaetskontrolle */
			if (($1.intnum == O_PUNKT && $4.intnum != 1) ||
				($1.intnum == O_LINIE && $4.intnum < 2)) 
			{
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}
		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
//			id = $3.intnum;         /* Identifikator */
			ultoa ($3.intnum, cbOKS, d_flag ? 10 : 16);
			sta[1] = $1.intnum;     /* Objekttyp */
			koord_paare = $4.intnum; /* Stuetzpunktanzahl */
		}
	|	ElementarObjektTyp T_INTEGER T_HEXINTEGER T_INTEGER '\n'
		{
			if (d_flag && !fFirstIdent) {
				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
				YYABORT;
			}
			if (d_flag && fFirstIdent) 
				d_flag = TRUE;
			goto l_Ident;
		}
		ElementarObjektTyp T_INTEGER T_INTEGER T_INTEGER T_STRING '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

	l_Ident_typ2:
			if (fFirstIdent) fFirstIdent = FALSE;

		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) 
				end_previous_object ();

		/* Plausibilitaetskontrolle */
			if (($1.intnum == O_PUNKT && $4.intnum != 1) ||
				($1.intnum == O_LINIE && $4.intnum < 2)) 
			{
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}
		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
//			id = $3.intnum;         /* Identifikator */
			ultoa ($3.intnum, cbOKS, d_flag ? 10 : 16);
			sta[1] = $1.intnum;     /* Objekttyp */
			koord_paare = $4.intnum; /* Stuetzpunktanzahl */
		}
	|	ElementarObjektTyp T_INTEGER T_HEXINTEGER T_INTEGER T_STRING '\n'
		{
			if (d_flag && !fFirstIdent) {
				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
				YYABORT;
			}
			if (d_flag && fFirstIdent) 
				d_flag = TRUE;
			goto l_Ident_typ2;
		}
	|	ElementarObjektTyp T_INTEGER T_STRING T_INTEGER '\n'
		{
		// Ident ist Hexadezimal
			if (fFirstIdent) fFirstIdent = FALSE;

		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) 
				end_previous_object ();

		/* Plausibilitaetskontrolle */
			if (($1.intnum == O_PUNKT && $4.intnum != 1) ||
				($1.intnum == O_LINIE && $4.intnum < 2)) 
			{
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}

		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
//			id = lIdent;					/* Identifikator */
			strcpy (cbOKS, $3.string);
			sta[1] = $1.intnum;				/* Objekttyp */
			koord_paare = $4.intnum;		/* Stuetzpunktanzahl */
		}
	|	ElementarObjektTyp T_INTEGER T_STRING T_INTEGER T_STRING '\n'
		{
			if (fFirstIdent) fFirstIdent = FALSE;

		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) 
				end_previous_object ();

		/* Plausibilitaetskontrolle */
			if (($1.intnum == O_PUNKT && $4.intnum != 1) ||
				($1.intnum == O_LINIE && $4.intnum < 2)) 
			{
			/* Punkt-EO und nicht ein Koordinatenpaar oder
			   Linien-EO und weniger als zwei Koordinatenpaare */
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}

		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;            /* lfde Nummer in ASCII-Datei */
//			id = lIdent;					/* Identifikator */
			strcpy (cbOKS, $3.string);
			sta[1] = $1.intnum;				/* Objekttyp */
			koord_paare = $4.intnum;		/* Stuetzpunktanzahl */
		}
	|       ElementarObjektTyp error '\n'
		{
		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) 
				end_previous_object ();

		/* Fehler behandeln */
			yyerrok;
			switch ((int)$1.intnum) {
			case O_PUNKT:
				error_skip_lines ("PLFB", EPKTID); break;
			case O_LINIE:
				error_skip_lines ("PLFB", ELINID); break;
			case O_FLAECHE:
				error_skip_lines ("PLFB", EFLID); break;
			}
		}
	|	T_KOSATZ T_INTEGER T_INTEGER '\n'
		{
			if (!d_flag) 	// Ident ist Hexadezimal
				$3.intnum = MakeHex ($3.intnum);

	l_KOIdent:
			if (fFirstIdent) fFirstIdent = FALSE;

		// KomplexObjekt
		/* Vorhergehendes Objekt bearbeiten */
			if (satz_nr > 0) end_previous_object ();
			++objekt_nr;

		/* Naechstes Objekt beginnen */
			init_new_object ();

		/* Objektparameter setzen */
			satz_nr = $2.intnum;	/* lfde Nummer in ASCII-Datei */
//			id = $3.intnum;		/* Identifikator */
			ultoa ($3.intnum, cbOKS, d_flag ? 10 : 16);
			sta[0] = K_OBJEKT;	
			sta[1] = 0;		/* Objekttyp */
			koord_paare = 0;	/* Stuetzpunktanzahl */
		}
	|	T_KOSATZ T_INTEGER T_HEXINTEGER '\n'
		{
			if (d_flag && !fFirstIdent) {
				fprintf (stderr, "\nInkonsistente Identifikator-Zahlenbasis ('-x' verwenden).\n");
				YYABORT;
			}
			if (d_flag && fFirstIdent) 
				d_flag = TRUE;
			goto l_KOIdent;
		}
	|	T_KOSATZ error '\n'
		{
		/* Vorhergehendes EO bearbeiten */
			if (satz_nr > 0) end_previous_object ();
			yyerrok;
			error_skip_lines ("PLFB", EFKID);
		}
	;

ElementarObjektTyp:
		T_PSATZ         /* Punkt */
		{       $$.intnum = O_PUNKT;    }
	|       T_LSATZ         /* Linie */
		{       $$.intnum = O_LINIE;    }
	|       T_FSATZ         /* Flaeche */
		{       $$.intnum = O_FLAECHE;  }
	|	T_BSATZ		/* TextObjekt */
		{	$$.intnum = O_TEXTOBJEKT;	}
	;

TextObjektSatz:	T_ISATZ T_STRING '\n'
		{
		short Len = strlen ($2.string);
		long wf = 0;

			curr_mi = &curr_mi[mi_count];
			mi_count = 3;
			curr_mi_text = (char *)&curr_mi[3];

			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
			curr_mi[1] = M_TEXT;

		// wie normalen Merkmalswert behandeln
			strncpy (curr_mi_text, $2.string, 78);
			curr_mi_text[min(78, Len)] = '\0';

			curr_mi_text += Len;
			wf = (Len + (sizeof(long)-1))/sizeof(long);

			mi[1] += wf + 3;
			curr_mi[2] = wf;		// Wiederholungsfaktor
			mi_count += wf;
		}
	|	T_ISATZ T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];

			curr_mi[0] = lTextObjMCode;	// MerkmalsCode
			curr_mi[1] = M_TEXT;
			curr_mi[2] = -1;		// WF
			curr_mi[3] = $2.intnum;		// MCode

			mi[1]++;
			mi_count += 4;

		// Status korrigieren
			sta[1] = O_TEXTOBJIND;
		}
	;

SteuerSatz:	T_CSATZ T_VSATZ '\n'
	;

IntegerMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'I' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_INTEGER;         /* Integermerkmale */
			mi_werte = $3.intnum;   /* Anzahl der I*4 - Werte */
		merkmal: ;
			curr_mi[0] = $2.intnum; /* Merkmalskode */
			curr_mi[2] = 0;         /* Wiederholungsfaktor loeschen */
			mi[1] += 3;
			mi_count = 3;
			mi_length = $5.intnum;  /* Laenge der Werte */
		}
	;

FloatMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'F' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_DOUBLE;          /* Floatpointmerkmale */
			mi_werte = $3.intnum; //*(sizeof(double)/sizeof(long));
			goto merkmal;   /* weiter wie fuer M_INTEGER */
		}
	;

StringMerkmalsSatz:
		T_MSATZ T_INTEGER T_INTEGER 'A' T_INTEGER '\n'
		{
			curr_mi = &curr_mi[mi_count];
			curr_mi[1] = M_TEXT;            /* Textmerkmale */
			curr_mi_text = (char *)&curr_mi[3];
			mi_werte = ($5.intnum + (sizeof(long)-1))/sizeof(long);
			goto merkmal;   /* weiter wie fuer M_INTEGER */
		}
	;

IntegerWertSatz:
		T_WSATZ IntegerWerte '\n'
	;

IntegerWerte:   IntegerWert
	|       IntegerWerte IntegerWert
	;

IntegerWert:    T_INTEGER
		{
		/* Plausibilitaetskontrolle */
			if (mi_count -3 >= mi_werte) {
			/* Merkmal ueberspringen */
				error_skip_lines ("PLFMRG", EMCNT);
				break;
			}
			curr_mi[mi_count++] = $1.intnum;
			mi[1]++;
			curr_mi[2]++;
		}
	;

FloatWertSatz:  T_WSATZ FloatWerte '\n'
	;

FloatWerte:     FloatWert
	|       FloatWerte FloatWert
	;

FloatWert:      T_FLOAT
		{
		register int item_size = sizeof(double)/sizeof(long);

		/* Plausibilitaetskontrolle */
			if ((mi_count -3)/(sizeof(double)/sizeof(long)) >= (size_t)mi_werte) {
			/* Merkmal ueberspringen */
				error_skip_lines ("PLFMRG", EMCNT);
				break;
			}
			*((double *)(&curr_mi[mi_count])) = $1.fltnum;
			mi[1] += item_size;
			curr_mi[2]++;           // += item_size;
			mi_count += item_size;
		}
	;

StringWertSatz: T_WSATZ T_STRING '\n'
		{
		register int length = 0;

			/* Plausibilitaetskontrolle */
			if (mi_length <= 0) {
			/* Zu viele Merkmalssaetze */
				error_skip_lines ("PLFRMG", EMCNT);
				break;
			}

			strncpy (curr_mi_text, $2.string, 78);
			curr_mi_text[min(78, mi_length)] = '\0';
			length += strlen (curr_mi_text);
			mi_length -= length;
			curr_mi_text += length;
			if (mi_length <= 0) {
			/* Merkmalswerte vollstaendig gelesen */
			register int wf = 0;    /* Laenge des Textes in I*4 */

				length = curr_mi_text - (char *)&curr_mi[3];
				wf = (length + sizeof(long)-1)/sizeof(long);
				mi[1] += wf;
				curr_mi[2] += wf;
				mi_count += wf;
			}
		}
	;

RelationsSatz:  T_RSATZ RelationsTyp T_INTEGER T_INTEGER '\n'
	|	T_RSATZ T_BRELSATZ T_INTEGER '\n'
	|       T_RSATZ error '\n'
		{
			yyerrok;
			db_error (EBREL, ASCPARSER, $3.num_line);
		}
	;

RelationsTyp:	T_HRELSATZ
		{	$$.intnum = GREL;	}
	|	T_KRELSATZ
		{	$$.intnum = OREL;	}
	;

TrennSatz:      T_TSATZ '\n'
	;

KommentarSaetze:
		KommentarSatz 
	|       KommentarSaetze KommentarSatz
	;

KommentarSatz:  T_KSATZ '\n'
		{       strcpy (comment, $1.string);    }
	;

PunktKoordinaten:
		PunktKoordinate
	|       PunktKoordinaten PunktKoordinate
	;

PunktKoordinate:
		T_FLOAT T_FLOAT
		{
		/* Plausibilitaetskontrolle */
			if (lgi +1 >= koord_paare) {
				error_skip_lines ("PLFB", EGCNT);        /* naechsten Id-Satz suchen */
				break;
			}
		/* Koordinatenpaar abspeichern, Zaehler weitersetzen */
			{
				gxi[++lgi] = $1.fltnum * dKoeff;
				gyi[lgi] = $2.fltnum * dKoeff;
			}
		}
	;

EndeSatz:       T_ESATZ '\n'
		{       if (satz_nr > 0) end_previous_object ();        }
	;

%%

#define YYACCEPT        return(0)
#define YYABORT         return(1)

void yyerror (char *string) 
{
	fprintf (stderr, "Zeile %d: %s\n", yylineno, string);
}

int cdecl db_error (int ec, int rc, ...)
{
	fprintf (stderr, "Zeile %d: Fehler %d in Routine %d\n", yylineno, ec, rc);

return ec;
}
