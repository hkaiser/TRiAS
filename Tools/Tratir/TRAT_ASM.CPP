/* Testdatei fuer ASCPARSER                                     */
/* File: trat_asm.c                                              */

#include "tratasp.h"

#include <CIID.h>

#include "dbversio.h"

// Atl stuff
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
//
char fnin[_MAX_PATH] = { '\0' };		/* ATLAS ASCII-Dateiname */
char ascii[_MAX_PATH] = { '\0' };		/* DIRIS-Austauschdatei-Name */
char MFile[_MAX_PATH] = { '\0' };		/* Datei mit zusätzlichen Merkmalen */
char HFile[_MAX_PATH] = { '\0' };		// Header - Datei
char cbINI[_MAX_PATH] = { '\0' };		// zu verwendende INI-Datei

int first = 0;                  /* erster zu speichernder Satz */
int last = 0;                   /* letzter einzugebender Satz */
int flen = IDLEN;               /* Stellenzahl des Identifikators */
long fmin = 10000000;           /* minimaler Identifikator */
long idst = 10000000;           /* Standardidentifikator */

FILE *fascii;                   /* DIRIS/Win-Austauschdatei */

char InBuff[20*1024];			// Buffer für Ein- und Ausgabedateien
char OutBuff[20*1024];

double g_dKoeff = 1.0;			// zusätzlicher Skalierungskoeffizient

IExtendedDataConversionPtr g_ExtConv;

static char titel[] = "Erstellung des TRiAS-Austauschformates aus Atlas*GIS-Austauschformat";

static char *usage[] = {
	"Verwendung: bna2asc [options] [atlas_ascii_datei] [trias_ascii_datei]\n",
	"Options: -fint_zahl\tZeichenanzahl des Objektklassenschlüssels (default: 8),\n",
	"\t-s\t\tUnterdrückt Bildschirmausgaben,\n",
	"\t-c<filename>\tName der zu verwendenden INI-Datei\n\t\t\t(default: BNA2ASC.INI),\n",
	"\t-h<filename>\tName der Header-Datei,\n",
	"\t-mint_zahl\tMerkmalscode für name2 (default: 51100000),\n",
	"\t-m-\t\tMerkmal aus name2 nicht generieren (sinnvoll mit '-n'),\n",
	"\t-uint_zahl\tMerkmalscode des Unique Ident (default: 51200000),\n",
	"\t-lint_zahl\tMerkmalscode für name4 (default: 50000000),\n",
	"\t-b\t\tVerarbeitung von Begleitobjekten,\n",
	"\t-n<filename>\tDatei enthält zusätzliche Merkmale,\n",
	"\t-iint_zahl\tStandardmäßig zu verwendender Objektklassenschlüssel,\n",
	"\t-x\t\tObjektklassenschlüssel hexadezimal interpretieren\n\t\t\t(default),\n",
	"\t-d\t\tObjektklassenschlüssel dezimal interpretieren,\n",
	"\t-y\t\tObjektklassenschlüssel als Identifikator ausgeben,\n",
	"\t-k\t\tZusätzlicher Skalierungskoeffizient für Koordinaten\n\t\t\t(default: 1.0).\n",
	NULL,
};

char *no_open = "Kann %s \'%s\' nicht eröffnen\n";

int s_flag = FALSE;     /* keine Ausgaben auf stdout */
int m_flag = TRUE;	// Unique Ident Atlas*Gis
int b_flag = FALSE;	// ohne Begleitobjekte
int bo_flag = FALSE;	// BO wurde ausgegeben - Relation herstellen !
int n_flag = FALSE;	// zusätzliche Merkmal zuspielen
int h_flag = FALSE;	// HeaderDatei rankopieren
int d_flag = FALSE;	// Standard: haxadezimaler Ident
int nomk_flag = FALSE;	// Merkmal aus Name2 nicht generieren
int y_flag = FALSE;	// Objektklassenschlüssel als Identifikator ausgeben

extern FILE *yyin;      /* Eingabedatei (LEX) */

// FunktionsPrototypen --------------------------------------------------------
void main (int, char *[]);
void print_usage (void);
int yyparse (void);
void make_file (char *pnew, char *old, char *ext);
void command_line (int argc, char *argv[]);
void atlasgis_open (void);
void ascii_open (void);
void print_titel (char *titel);
HRESULT CreateExtDataConvObject (void);
HRESULT FreeExtDataConvObject ();

void main (int argc, char *argv[])
{
	CoInitialize(NULL);
	_Module.Init(ObjectMap, GetModuleHandle(NULL));

	command_line (argc, argv);      /* Kommandozeile auswerten */
	ascii_open ();                  /* ZIPEDB-ASCII-Datei eroeffnen */
	atlasgis_open ();               /* ATLASGIS-Austauschdatei eroeffnen */
	fprintf (fascii, "; %s - %s%s %s\n", Copyright, Version, Release, Date);
	if (!s_flag) 
		print_titel (titel);		/* Programmtitel ausgeben */
	if (n_flag) 
		MIOpen (MFile);				/* Datei mit Merkmalen einlesen */

	if (SUCCEEDED(CreateExtDataConvObject())) 
		yyparse ();					/* ASCII-Datei verarbeiten */
	else
		fprintf (stderr, "Der in der Datei '%s' angegebene Zusatzmodul kann nicht instantiiert werden!\n", cbINI);

	fclose (fascii);                /* ATLASGIS-Austauschdatei schliessen */
	if (fascii != stdout)
		fprintf (stderr, "\n");
	if (n_flag)
		ReleaseMTree ();	/* Merkmale wieder freigeben */

	FreeExtDataConvObject();
	CoUninitialize();
	exit (0);
}

void print_usage (void) 
{
register char **cptr;

	print_titel (titel);	/* Programmtitel ausgeben */
	for (cptr = usage; *cptr != NULL; ++cptr)
		fputs (*cptr, stderr);
}

/* Neue Extension anhaengen */
void make_file (char *pnew, char *old, char *ext)
{
register char *cptr;

	strcpy (pnew, old);
	for (cptr = &pnew[strlen(pnew) -1]; cptr >= pnew; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == pnew) {
			strcat (pnew, ext);
			break;
		}
	}
}


void command_line (int argc, char *argv[])
{
register int i,j;
register char *p;

/* Kommandozeile auswerten */
	for (i = 1; i < argc; ++i) {
		p = argv[i];
		if (*p == '/') {
			++p; switch (*p++) {
			case '?':
			case 'H':
			case 'h':
			default:
				print_usage ();
				CoUninitialize();
				exit(1);
			}
		} else if (*p == '-') {
			++p; switch (*p++) {
			case 'f':       /* Identifikatorlaenge */
			case 'F':
				flen = atoi (p);
				fmin = 10;
				for (j = 2; j < flen; j++)
					fmin *= 10;
				break;

			case 'm':       /* Merkmalscode */
			case 'M':
				if (*p == '-')
					nomk_flag = TRUE;
				else {
					mi_code = atol (p);
					nomk_flag = FALSE;
				}
				break;

			case 'l':	// MerkmalsCode fr Name4
			case 'L':
				if (p) name4_code = atol (p);
				else   name4_code = DEFAULTNAME4;
				if (name4_code == 0) name4_code = DEFAULTNAME4;
				break;

			case 't':       /* Merkmalstyp */
			case 'T':
				mi_typ = *p;
				break;

			case 'i':       /* Standardidentifikator */
			case 'I':
				idst = atol (p);
				break;

			case 'b':
			case 'B':
				b_flag = TRUE;	// BO sollen gebildet werden
				break;

			case 's':
			case 'S':
				s_flag = TRUE;
				break;

			case 'u':	// Unique Ident
			case 'U':
				m_flag = TRUE;
				if (p) u_code = atol (p);
				else   u_code = DEFAULTUNIQUEIDENT;
				break;

			case 'n':	/* zusätzliche Merkmale gegeben */
			case 'N':
				strncpy (MFile, p, sizeof(MFile)-1);
				if (strlen (MFile) > 0) 
					n_flag = TRUE;
				break;

			case 'c':	// INI-Dateiname gegeben
			case 'C':
				strcpy (cbINI, p);
				break;

			case 'h':
			case 'H':
				strncpy (HFile, p, sizeof(HFile)-1);
				if (strlen (HFile) > 0)
					h_flag = TRUE;
				break;

			case 'd':
			case 'D':
				d_flag = TRUE;
				break;

			case 'x':
			case 'X':
				d_flag = FALSE;
				break;

			case 'y':
			case 'Y':
				y_flag = TRUE;
				break;

			case 'k':
			case 'K':
				g_dKoeff = atof (p);
				if (0.0 == g_dKoeff) {
					print_usage ();
					CoUninitialize();
					exit(1);
				}
				break;

			case '\0':      /* Eingabe von stdin */
				if (*fnin == '\0') {
					strcpy (fnin, "-");
					break;
				}
				/* ggf. hier durchfallen */

			case '?':
			default:
				print_usage ();
				CoUninitialize();
				exit(1);
			}
		} else if (*fnin == '\0') {
		/* ATLAS-Austauschdatei-Name */
			strncpy (fnin, p, 75);
		} else if (*ascii == '\0') {
		/* Austauschdatei-Name */
			strncpy (ascii, p, 75);
		} else {
		/* ungltiger Parameter */
			print_usage ();
			CoUninitialize();
			exit(1);
		}
	}
}

void atlasgis_open (void) 
{
/* ATLASGIS-ASCII-Datei eröffnen */
	if (*fnin == '\0' || !strcmp (fnin, "-")) {
		s_flag = TRUE;          /* Eingabe von stdin */
		yyin = stdin;
		strcpy (fnin, "stdin");
	} else {
		if ((yyin = fopen (fnin, "r")) == NULL) {
			fprintf (stderr, no_open, "Datei", fnin);
			CoUninitialize();
			exit(1);
		}
	}
	setvbuf (yyin, InBuff, _IOFBF, 20*1024);
}

void ascii_open (void) 
{
/* Ausgabedatei eröffnen */

	if (*ascii == '\0') {
		fascii = stdout;
	} else if ((fascii = fopen (ascii, "w")) == NULL) {
		fprintf (stderr, no_open, "Datei", ascii);
		CoUninitialize();
		exit (1);
	}
	if (fascii != stdout)
		setvbuf (fascii, OutBuff, _IOFBF, 20*1024);
}


void print_titel (char *titel) {

	fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
	fflush (stderr);
}

HRESULT CreateExtDataConvObject (void)
{
// nach evtl. INI suchen, zuerst im aktuellen Verzeichnis, dann im Suchpfad
char cbBuffer[_MAX_PATH];
DWORD dwLen = ::SearchPath (NULL, cbINI, NULL, sizeof(cbBuffer), cbBuffer, NULL);

	if (0 == dwLen)
		return S_FALSE;		// nichts gefunden, aber ok

char cbFound[_MAX_PATH];

	if (0 == ::GetPrivateProfileString ("Zusatzmodule", "ExtDataConv", "", cbFound, sizeof(cbFound), cbBuffer))
		return S_FALSE;

CIID Guid (cbFound, CIID::INITCIID_InitFromProgId);
HRESULT hr = g_ExtConv.CreateInstance (Guid);

	if (SUCCEEDED(hr))
		g_ExtConv -> put_ConfigFile (CComBSTR(cbINI));
	return hr;
}

HRESULT FreeExtDataConvObject ()
{
	g_ExtConv = NULL;
	return S_OK;
}
