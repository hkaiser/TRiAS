// Hauptprogramm fuer SICAD Import
// File: GDBM.CPP

#include "stdafx.h"

#include "dbversio.h"
#include "gdb.h"

#define BACKSLASH '\\'

#define MAXINPUT 40		// max. Anzahl der Eingabedateien

char *fnin[MAXINPUT];		/* ASCII-Dateinamen */
int cntInput = 0;		// Anzahl der Eingabedateien
int wasInput = 0;

char fnout[80] = "";	/* DB-Name */
char protocol[80] = "";	/* Protokolldatei */

FILE *fpprot = NULL;

int dbd = -1;			/* DB-deskriptor */

int first = 0;			/* erster zu speichernder Satz */
int last = 0;			/* letzter einzugebender Satz */

int MaxPunktStufe = 1;		// maximal auszugebende Stufe
int MaxLinienStufe = 1;
int MaxFlaechenStufe = 3;
int MaxTextStufe = 3;

long cntEl = 1;			/* Zähler der GDBElemente */

// Container der Eingabedaten
extern double XMin, XMax, YMin, YMax;

static char titel[] = "Transformation von GDB-Daten in DIRIS-Austauschformat";

static char *usage[] = {
	"Verwendung: gdbasc [options] gdb_datei [gdb_datei ...]\n",
	"Optionen:\n\t-odatei\t[O]utput, Ausgabedateiname,\n",
	"\t-s\t[s]ilent, keine Bildschirmausgaben,\n",
	"\t-c\t[K]ommentare übernehmen,\n",
	"\t-b\tTexte als [B]egleitobjekte generieren,\n",
	"\t-hdatei\t[H]eaderDateiname,\n",
	"\t-r\tGeometrie aller Objekte speichern,\n",
	"\t-k\t[K]reise als Flächen speichern (def: Linien),\n"
	"\t-pNum\tHierarchiestufe, bis zu der [P]unktObjekte\n",
	"\t\tgeneriert werden (def: 1),\n",
	"\t-lNum\tHierarchiestufe, bis zu der [L]inienObjekte\n",
	"\t\tgeneriert werden (def: 1),\n",
	"\t-fNum\tHierarchiestufe, bis zu der [F]lächenObjekte\n",
	"\t\tgeneriert werden (def: 3),\n",
	"\t-tNum\tHierarchiestufe, bis zu der [T]extObjekte\n",
	"\t\tgeneriert werden (def: 3).\n",
	(char *)NULL,
};

static char *no_open = "Kann %s \'%s\' nicht eröffnen\n";

static char *PbdLine = "D PbdName \"sicad\"\n";

int s_flag = FALSE;	/* keine Ausgaben auf stdout */
int c_flag = 0;		// Kommentare nicht übernehmen
int r_flag = FALSE;	// Geometrie nicht speichern
int h_flag = TRUE;	// keine doppelten Objekte ausgeben
int b_flag = FALSE;	// keine Begleitobjekte
int k_flag = FALSE;	// Kreise als Linien (TRUE: Flächen)

extern FILE *yyin;	/* Eingabedatei (LEX) */
extern FILE *yyout;	/* Ausgabedatei */

// I/O-Puffer
char InBuff[20*1024];
char OutBuff[20*1024];

// Funktionsprototypen --------------------------------------------------------
void command_line (int, char **);
void out_open (void);
void protocol_open (void);
void print_titel (char *);
void make_file (char *, char *, char *);

static void PutDummyLine (FILE *fp) {
register int i;

	for (i = 0; i < 78; i++) 
		fputc (' ', fp);
	fputc ('\n', fp);
}

//double min (double d1, double d2)
//{
//	return (d1 < d2) ? d1 : d2;
//}

// Hauptprogramm --------------------------------------------------------------
void main (int argc, char **argv) {
register int c;
long ScalePos, OffsetPos;
double ScaleX, ScaleY, Scale;

	command_line (argc, argv);	/* Kommandozeile auswerten */

	if (!s_flag) 
		print_titel (titel); 	/* Programmtitel ausgeben */

	yyin = NULL;			// erste Datei zu eröffnen
	out_open ();			/* AusgabeDatei eröffnen */
	protocol_open ();     	/* Protokolldatei eroeffnen */
	fprintf (yyout, "; %s - %s%s %s\n", Copyright, Version, Release, Date);
					// Copyright ausgeben
// wenn Headerdatei vorhanden ist
	if (fpprot != NULL) {
		while ((c = fgetc (fpprot)) != EOF)
			fputc (c, yyout);	// Header umkopieren
	} else {
	// keine HeaderDatei vorhanden ist
	time_t loctime;

		time (&loctime);
		fprintf (yyout, "H Transformation aus dem GDB-Format, %s", ctime (&loctime));
	}

// Dummy-Headerwerte schreiben
	ScalePos = ftell (yyout);	// Position im File merken
	PutDummyLine (yyout);
	OffsetPos = ftell (yyout);
	PutDummyLine (yyout);
	fputs (PbdLine, yyout);

// erste EingabeDatei eröffnen
	if (ascii_open (0))
		exit (1);     		/* ASCII-Datei eroeffnen */

	fflush (yyout);

	InitYYParse ();			/* ASCII-Datei verarbeiten */
	if (fpprot) 
		fclose (fpprot);	/* Protokolldatei schliessen */

// Endekennung ausgeben und Datei abschlieáen
	fprintf (yyout, "E\n");	// Endekennung

// HeaderInfo schreiben
	fseek (yyout, ScalePos, 0L);
// SCaalierung berechnen
	ScaleX = 10e5/(XMax-XMin);
	ScaleY = 10e5/(YMax-YMin);
	Scale = min (ScaleX, ScaleY);
	fprintf (yyout, "D Scale %12.5lf 0.0 0.0 %12.5lf\n", Scale, Scale);
	fseek (yyout, OffsetPos, 0L);
	fprintf (yyout, "D Offset %12.5lf %12.5lf\n", XMin, YMin);

	fclose (yyout);		/* AusgabeDatei abschlieáen */
	if (!s_flag) {
		printf ("\nGesamtcontainer: LiU(%f, %f), ReO(%f, %f)\n", XMin, YMin, XMax, YMax);
		printf ("\n");
		fflush (stdout);
	}

exit (0);
}

void print_usage (void) {
register char **cptr;

	print_titel (titel);
	fprintf (stderr, "\n");
	for (cptr = usage; *cptr != NULL; ++cptr)
		fputs (*cptr, stderr);
}

/* Neue Extension anhaengen */
void make_file (char *neu, char *old, char *ext) {
register char *cptr;

	strcpy (neu, old);
	for (cptr = &neu[strlen(neu) -1]; cptr >= neu; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == neu) {
			strcat (neu, ext);
			break;
		}
	}
}


void command_line (int argc, char **argv) {
register int i;
register char *p;

// EingabeDateifeld nullsetzen
	for (i = 0; i < MAXINPUT; i++)
		fnin[i] = NULL;
/* Kommandozeile auswerten */
	if (argc < 2) {
		print_usage ();
		exit (1);
	}
        for (i = 1; i < argc; ++i) {
                p = argv[i];
                if (*p == '-') {
                        ++p; switch (*p++) {
			case 'p':	// Stufe einstellen
			case 'P':
				MaxPunktStufe = atoi (p);
				if (MaxPunktStufe < 1 || MaxPunktStufe > 3)
					MaxPunktStufe = 3;
				break;

			case 'l':	// Stufe einstellen
			case 'L':
				MaxLinienStufe = atoi (p);
				if (MaxLinienStufe < 1 || MaxLinienStufe > 3)
					MaxLinienStufe = 1;
				break;

			case 'f':	// Stufe einstellen
			case 'F':
				MaxFlaechenStufe = atoi (p);
				if (MaxFlaechenStufe < 1 || MaxFlaechenStufe > 3)
					MaxFlaechenStufe = 3;
				break;

			case 't':	// Stufe einstellen
			case 'T':
				MaxTextStufe = atoi (p);
				if (MaxTextStufe < 1 || MaxTextStufe > 3)
					MaxFlaechenStufe = 3;
				break;

			case 'h':	/* Headerdatei */
			case 'H':
				strncpy (protocol, p, 75);
				protocol[75] = '\0';
				break;

			case 's':	/* silent */
			case 'S':
				s_flag = TRUE;
				break;

			case 'c':	// Kommentare übernehmen
			case 'C':
				c_flag++;
				break;

			case 'a':
			case 'A':
				h_flag = FALSE;	// doppelte Objekte ausgeben
				break;

			case 'b':
			case 'B':
				b_flag = TRUE;	// Begleitobjekte generieren
				break;

			case 'r':
			case 'R':	// Geometrie immer speichern
				r_flag = TRUE;
				break;

			case 'k':
			case 'K':
				k_flag = TRUE;
				break;

			case 'o':
			case 'O':	// Ausgabedateiname
				if (*fnout == '\0')
					strcpy (fnout, p);
				else {
					print_usage ();
					exit (1);
				}
				break;

			case '\0':	/* Eingabe von stdin */
				if (cntInput == 0) {
					fnin[0] = (char *)calloc (1, 20);
					if (fnin[0] == NULL) {
						yyerror ("Kein Speicherplatz.");
						exit (1);
					}
					strcpy (fnin[0], "-");
					break;
				} else {
					print_usage ();
					exit (1);	
				}
				break;

			default:
				print_usage ();
				exit(1);
                        }
		} else if (cntInput +1 < MAXINPUT) {
			fnin[cntInput] = (char *)calloc (1, strlen (p)+1);
			if (fnin[cntInput] == NULL) {
				yyerror ("Kein Speicherplatz.");
				exit (1);
			}
			strcpy (fnin[cntInput], p);
			cntInput++;
		} else if (cntInput >= MAXINPUT) {
		char ErrorText[80];

			sprintf (ErrorText, "Kann maximal %d Eingabedateien eröffnen.", MAXINPUT);
			yyerror (ErrorText);
			exit (1);
		} else {
		/* ungueltiger Parameter */
			print_usage ();
			exit(1);
                }
        }
}

int ascii_open (int i) 
{
/* ASCII-Datei eröffnen */
char locTrennSatz[100];
extern char *TrennSatz;

	if (i < 0 || i >= cntInput) {
		yyerror ("Ungültiger Eingabedateiindex.");
		return 1;
	}
	if (i == 0 && (fnin[0] == NULL || !strcmp (fnin[0], "-"))) {
		s_flag = TRUE;		/* Eingabe von stdin */
		yyin = stdin;
		strcpy (fnin[i], "stdin");
	} else {
		if (yyin != NULL) {
			fclose (yyin);
			yyin = NULL;
		}
		if ((yyin = fopen (fnin[i], "rb")) == NULL) {
			fprintf (stderr, no_open, "Datei", fnin[i]);
			return 1;
		}
		wasInput++;
	}
	if (!s_flag) {
		fprintf (stderr, "\n%s:\n", fnin[i]);
		fflush (stderr);
	}

// Eingabe-DateiNamen ausgeben
	strcpy (locTrennSatz, TrennSatz);
	memcpy (&locTrennSatz[6], fnin[i], strlen(fnin[i]));
	fprintf (yyout, locTrennSatz);

// EingabeBuffer setzen
	setvbuf (yyin, InBuff, _IOFBF, 20*1024);	// EingabePuffer setzen

return 0;
}

void out_open (void) {
/* ASCII-AusgabeDatei eroeffnen */

	if (*fnout == '\0') {
		s_flag = TRUE;		/* Eingabe von stdin */
		yyout = stdout;
		strcpy (fnout, "stdout");
	} else {
		if ((yyout = fopen (fnout, "w+")) == NULL) {
			fprintf (stderr, no_open, "Datei", fnout);
                        exit(1);
                }
	}
	setvbuf (yyout, OutBuff, _IOFBF, 20*1024);	// EingabePuffer setzen
}

void protocol_open (void) {

/* Headerdatei eroeffnen */
	if (*protocol == '\0') 
		strcpy (protocol, ".\\gdbasc.hdr");
	fpprot = fopen (protocol, "r");
}


void print_titel (char *titel) {

	fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n", Copyright, Version, Release, Date);
	fflush (stderr);
}

/*
int esyntx (int errcode, int routine, ...) {
va_list pList;
ERROR_PARAMETER *ErrPar;

	va_start (pList, routine);
	ErrPar = va_arg (pList, ERROR_PARAMETER *);
	va_end (pList);
	fprintf (stderr, "\n%s:%d:%s\n", fnin, ErrPar->line_number, ErrPar->string);

return errcode;
}
*/
