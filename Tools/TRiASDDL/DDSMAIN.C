/* Hauptprogramm fuer DDSP - Datenbasisstruktur Definitions-Sprachprozessor */
/* File: DDSMAIN.C              last update: 14. Juli 1989                  */

#if defined(sccs)
static char SccsId[] = "%W%	%E%";
#endif

#include "StdAfx.h"

#include "dbversio.h"
#include "ddspprot.h"		// Prototypen

FILE *schema;           /* Eingabefile */
int r_flag = 0;         /* Komandozeilenflag */
int s_flag = 0;         /* Silent */
int f_flag = 0;         /* F77 Headerdatei generieren */
int h_flag = 1;         /* C-Header generieren */
int c_flag = 0;         /* nur 'C' und 'F77' Header Dateien generieren */

char fnin[_MAX_PATH];	/* Schemafilename */
char fnout[_MAX_PATH];	/* AusgabeDateiname */

extern int tot_errs;    /* Fehleranzahl */

extern long DBVersion;	/* VersionsNummer */
extern long PageSize;	/* PageGröße */

static char titel[] = "Prozessor für die Definition einer Datenbasisstruktur                 ";
#define T_LEN sizeof(titel)

static char *usage = "Verwendung: %s [-vsfh] [-o outfile] dds_spec\n";

void main (argc,argv)
int argc;
char *argv[];
{
	register int i;
	register char *p;
	
	*fnin = '\0';
	for (i = 1; i < argc; ++i) {
		p = argv[i];
		if (*p == '-') {
			++p;
			switch (*p++) {
            case 's':       /* Silent */
            case 'S':
				++s_flag;
				break;
				
            case 'f':       /* F77-Includefile generieren */
            case 'F':
				++f_flag;
				break;
				
            case 'h':		// C-Header
            case 'H':
				if (*p == '-')
					h_flag = 0;
				else
					h_flag = 1;
				break;
				
            case 'v':       /* Verbose: Report generieren */
            case 'V':
				++r_flag;
				break;
				
            case 'c':		// Syntaxtest
            case 'C':
				++c_flag;
				break;
				
			case 'o':		// Ausgabedateiname
			case 'O':
				{
					if ('\0' == *p) {
					// Dateiname im nächsten Argument
						if (i < argc)
							p = argv[++i];
						else {
							fprintf (stderr, usage, argv[0]);
							exit(1);
						}
					} 
					strcpy (fnout, p);
				}
				break;

            default:
				fprintf (stderr, usage, argv[0]);
				exit(1);
			}
		} else if (*fnin == '\0') {
			strcpy (fnin, p);
		} else {
			fprintf (stderr, usage, argv[0]);
			exit(1);
		}
	}
	if (*fnin == '\0') {
		schema = stdin;
		++s_flag;
		strcpy(fnin, "stdin");
	} else {
		if ((schema = fopen (fnin, "r")) == NULL) {
			fprintf (stderr, "Kann Datei \'%s\' nicht eröffnen\n", fnin);
			exit(1);
		}
	}
	if (!s_flag) {
		fprintf (stderr, "\n%s\n", titel);
		fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
		fflush (stderr);
	}
	if (!s_flag) printf ("Quelldateiname:   %s\n", schema == stdin ? "stdin" : fnin);
	
	PageSize = PAGESIZE;
	
	yyparse();
	fclose(schema);
	finish_up();
	fflush (stdout);
	
	if (tot_errs) {
		if (!s_flag) fprintf (stderr, "%d Fehler im Quelltext\n", tot_errs);
	} else {
		write_tables();
		if (!s_flag && DBVersion != 0) {
			printf ("Versionsnummer:   %02d.%02d.%02d.%03d\n\n",
				(short)(DBVersion >> 24),
				(short)((DBVersion >> 16) & 0xff),
				(short)((DBVersion >> 8) & 0xff),
				(short)(DBVersion & 0xff)
				);
			printf ("Pagegröße: %ld\n", PageSize);
			fflush (stdout);
		}
		if (!s_flag) fprintf (stderr, "Quelltext fehlerfrei.\n");
	}
	exit (0);
}
