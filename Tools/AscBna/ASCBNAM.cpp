/* Testdatei fuer ASCPARSER					*/
/* File: ASCPUTM.C						*/

#if defined(sccs)
static char SccsId[] = "INPUT: %W%	%E%";
#endif

#include "StdAfx.h"

#include "dbtypes.h"
#include "dbversio.h"
#include "ascbna.h"
#include "ascerrs.h"

#include "CoordSystems.h"

char fnin[_MAX_PATH] = { '\0' };	/* ASCII-Dateiname */
char db_name[_MAX_PATH] = { '\0' };	/* DB-Name */
char mkl_name[_MAX_PATH] = { '\0' };	
char head_name[_MAX_PATH] = { '\0' };

char cbTcfIn[_MAX_PATH];
char cbTcfOut[_MAX_PATH];

int s_flag = FALSE;
int a_flag = FALSE;
int b_flag = FALSE;
int t_flag = TRUE;
int d_flag = FALSE;		// Standard ist jetzt Hex
int i_flag = FALSE;

FILE *fpout = NULL;			/* Protokolldatei */
FILE *fpmkl = NULL;
FILE *fphead = NULL;

long lUIdent = -1;
long lMCode = -1;
long Name4Code = -1;

double dKoeff = 1.0;

static char titel[] = "Konvertierung von DIRIS-Austauschformat ins Atlas*GIS BNA-Format";

static char *usage[] = {
	"Verwendung: ascbna [Optionen] ASC_Datei BNA_Datei\n",
	"\t-nMKL_Datei\tMerkmalsdatei (Ausgabe),\n",
	"\t-a\t\tAlle Merkmale in MKL_Datei ausgeben,\n",
	"\t-hHEAD_Datei\tHeaderdatei (Ausgabe),\n",
	"\t-mInteger\tName2 liegt auf diesem MCode,\n",
	"\t-uInteger\tUniqueident liegt auf diesem MCode,\n",
	"\t-lInteger\tName4 in liegt auf diesem MCode,\n",
	"\t-i\t\tIdentifikator als Name4 in BNA_Datei ausgeben,\n",
	"\t-kFloat\t\tZusätzlicher Koeffizient für X- und Y-Koordinate,\n",
	"\t-b\t\tAbhängige Begleitobjekte generieren,\n",
	"\t-t\t\tTextobjekte nicht transformieren,\n"
	"\t-x\t\tIdentifikatoren he[X]adezimal interpretieren (Default),\n",
	"\t-d\t\tIdentifikatoren [D]ezimal interpretieren,\n",
	"\t-ciASC_Coords\tKoordinatensystem der ASC-Datei,\n"
	"\t-coBNA_Coords\tKoordinatensystem der BNA-Datei,\n"
	"\t-?\t\tAnzeige dieses Textes.\n",
	NULL,
};

static char *no_open = "Kann %s \'%s\' nicht eröffnen\n";

extern FILE *yyin;	/* Eingabedatei (LEX) */

// Fehlerbehandlung -----------------------------------------------------------

// I/O-Puffer
char InBuff[20*1024];
char OutBuff[20*1024];

char UIdent[20];

///////////////////////////////////////////////////////////////////////////////
// prototypen
void command_line (int argc, char **argv);
void ascii_open (void);
void bna_open (void);
void mkl_open (void);
void head_open (void);
void print_titel (char *titel);

///////////////////////////////////////////////////////////////////////////////
// Com initialisieren
class CInitCom
{
public:
	CInitCom() { CoInitialize(NULL); }
	~CInitCom() { CoUninitialize(); }
};
CInitCom g_InitCom;

CCoordSystems g_CoordSys;

///////////////////////////////////////////////////////////////////////////////
// Hauptprogramm 
void main (int argc, char **argv) 
{
	lUIdent = lMCode = Name4Code = -1L;

	command_line (argc, argv);	/* Kommandozeile auswerten */
	ascii_open ();     			/* ASCII-Datei eroeffnen */
	bna_open ();
	mkl_open ();
	head_open ();
	if (!s_flag) 
		print_titel (titel); 	/* Programmtitel ausgeben */

// EingabeDatei bearbeiten
	yyparse ();          		/* ASCII-Datei verarbeiten */

	if (!s_flag) {
		printf ("\n");
		fflush (stdout);
	}
	if (fpout != stdout) fclose (fpout);
	if (fpmkl) fclose (fpmkl);
	if (fphead) fclose (fphead);

	exit (0);
}

void print_usage (void) 
{
register char **cptr;

	print_titel (titel);
	for (cptr = usage; *cptr != NULL; ++cptr)
		fputs (*cptr, stderr);
}

/* Neue Extension anhaengen */
void make_file (register char *pNew, register char *old, register char *ext) 
{
register char *cptr;

	strcpy (pNew, old);
	for (cptr = &pNew[strlen(pNew) -1]; cptr >= pNew; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == pNew) {
			strcat (pNew, ext);
			break;
		}
	}
}


void command_line (int argc, char **argv) 
{
register int i;
register char *p;

	t_flag = TRUE;

/* Kommandozeile auswerten */
        for (i = 1; i < argc; ++i) {
                p = argv[i];
                if (*p == '-') {
                        ++p; switch (*p++) {
			case 's':	/* silent */
			case 'S':
				s_flag = TRUE;
				break;

			case 'h':
			case 'H':
				if (*p) strcpy (head_name, p);
				break;

			case 'u':
			case 'U':
				lUIdent = atol (p);
				if (lUIdent == 0) lUIdent = -1L;
				break;

			case 'm':
			case 'M':
				lMCode = atol (p);
				if (lMCode == 0) lMCode = -1L;
				break;

			case 'l':
			case 'L':
				Name4Code = atol(p);
				if (Name4Code == 0) Name4Code = -1L;
				i_flag = FALSE;
				break;

			case 'n':
			case 'N':
				if (*p)
					strcpy (mkl_name, p);
				break;

			case 'c':
			case 'C':
				{
					if ('i' == tolower(*p))
						strcpy (cbTcfIn, p+1);
					else if ('o' == *p)
						strcpy (cbTcfOut, p+1);
					else {
						print_usage();
						exit(1);
					}
				}
				break;

			case 'a':
			case 'A':
				a_flag = TRUE;
				break;

			case 'b':
			case 'B':
				b_flag = TRUE;
				break;

			case 'i':
			case 'I':
				i_flag = TRUE;
				Name4Code = -1L;
				break;

			case 'k':
			case 'K':
				dKoeff = atof (p);
				break;

			case 't':
			case 'T':
				t_flag = FALSE;
				break;

			case 'x':
			case 'X':
				d_flag = FALSE;
				break;

			case 'd':
			case 'D':
				d_flag = TRUE;
				break;

			case '\0':	/* Eingabe von stdin */
				if (*fnin == '\0') {
					strcpy (fnin, "-");
					break;
				}
				/* ggf. hier durchfallen */
			default:
				print_usage ();
				exit(1);
			}
		} else if (*fnin == '\0') {
		/* ASCII-Dateiname */
			strncpy (fnin, p, 75);
		} else if (*db_name == '\0') {
		/* DB-Name */
			strncpy (db_name, p, 75);
		} else {
		/* ungueltiger Parameter */
			print_usage ();
			exit(1);
		}
	}
	if (*mkl_name == '\0')	// keine MKL_Datei gegeben
		a_flag = FALSE;

// Koordinatensysteme initialisieren
	if ('\0' != cbTcfIn[0] && '\0' != cbTcfOut[0]) {
		if (FAILED(g_CoordSys.LoadCSIn(cbTcfIn))) {
			fprintf (stderr, "Kann (Eingabe-)Koordinatensystem '%s' nicht laden.", cbTcfIn);
			exit(2);
		}
		if (FAILED(g_CoordSys.LoadCSOut(cbTcfOut))) {
			fprintf (stderr, "Kann (Ausgabe-)Koordinatensystem '%s' nicht laden.", cbTcfIn);
			exit(2);
		}
	}
}

void ascii_open (void) 
{
/* ASCII-Datei eroeffnen */

	if (*fnin == '\0' || !strcmp (fnin, "-")) {
		s_flag = TRUE;		/* Eingabe von stdin */
		yyin = stdin;
		strcpy (fnin, "stdin");
		strcpy (UIdent, "STDIN");
	} else {
		if ((yyin = fopen (fnin, "r")) == NULL) {
			fprintf (stderr, no_open, "Datei", fnin);
			exit(1);
		}
		_splitpath (fnin, NULL, NULL, UIdent, NULL);		
		strupr (UIdent);
	}
	setvbuf (yyin, InBuff, _IOFBF, 20*1024);	// EingabePuffer setzen
}

void bna_open (void) 
{
/* Ausgabedateidatei eroeffnen */
	if (*db_name == '\0') {
		fpout = stdout;
		return;
	}
	if ((fpout = fopen (db_name, "w")) == NULL) {
		fprintf (stderr, no_open, "Datei", db_name);
		exit (1);
	}
	setvbuf (fpout, OutBuff, _IOFBF, 20*1024);
}

void mkl_open (void) 
{
/* Ausgabedateidatei eroeffnen */
	if (*mkl_name == '\0') {
		fpmkl = NULL;
		return;
	}
	if ((fpmkl = fopen (mkl_name, "w")) == NULL) {
		fprintf (stderr, no_open, "Datei", mkl_name);
		exit (1);
	}
}

void head_open (void) 
{
/* Ausgabedateidatei eroeffnen */
	if (*head_name == '\0') {
		fphead = NULL;
		return;
	}
	if ((fphead = fopen (head_name, "w")) == NULL) {
		fprintf (stderr, no_open, "Datei", head_name);
		exit (1);
	}
}

void print_titel (char *titel) 
{
	fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
	fflush (stderr);
}

