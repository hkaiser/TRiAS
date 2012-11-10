/* Routine zum Bilden der Routinennamen-Metadateien             */
/* File: PBDPUTKS.C                                               */

static char SccsId[] = "ZIPEDB: %W%  %E%";

#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include "dbtypes.h"
#include "errdef.h"
#include "errdb.h"
#include "pbd.h"

static char *usage = "Verwendung: %s srctext dbname.\n";
static DB_ADDR dba;

main (argc, argv)
int argc;
char *argv[];
{
register int dbnum;
register char *cptr, *ptr;
register FILE *fsrc;
FILE *fopen ();
char inline[4001];
char KurzText[20];
register int zeile = 0;
long Id, Satz;
long Symbol;

        if (argc != 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fsrc = fopen (argv[1], "r")) == NULL) {
                fprintf (stderr, "%s: Kann Eingabedatei %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (3);
        }
        if ((dbnum = z_open (argv[2], argv[2], "")) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (2);
        }
	printf ("Symbolsatz:     ");
	ptr = inline;
        while ((cptr = fgets (ptr, 500, fsrc)) != NULL) {
                char *myatoi (), *strchr ();

		if (*inline == ';') {
		// Kommentar
			ptr = inline;
			continue;
		}
                if ((cptr = strchr (inline, '\n')) != NULL) *cptr = '\0';
		if (inline[strlen(inline)-1] == '\\') {
		// Fortsetzungszeile
			ptr = &inline[strlen(inline)-1];
			continue;
		}
	// Symbolnummer extrahieren
		if ((cptr = myatoi (inline, &Symbol)) == NULL) {
			ptr = inline; continue;
		}

	// Identifikatoren extrahieren
		dba.file_no = IPS;
		do {
		struct ips ips;

			memset (&ips, '\0', sizeof(struct ips));
			if ((cptr = myatoi (cptr, &ips.pis)) == NULL) {
				break;
			}
			ips.skodnr = Symbol;
			z_fillnew (&dba, &ips);
		} while (*cptr == ',');
		while (*cptr && isspace (*cptr)) cptr++;

	// Text extrahieren
		KurzText[0] = '\0';
		if (*cptr == '/' && *(cptr+1) == '*') {
		// Kurztext
		register char *pKurzText = KurzText;

			cptr += 2;
			while (!(*cptr == '*' && *(cptr+1) == '/')) 
				*pKurzText++ = *cptr++;
			*pKurzText = '\0';
			cptr += 2;	// '*/' Åberspringen
		// KurzText schreiben
			mputkt ("s", &Satz, KurzText);
		} else {
		// KurzText gleich Langtext
			if (strlen (cptr) < 16)
				mputkt ("s", &Satz, cptr);
		}
	// LangText schreiben
		mputtx ("s", &Satz, cptr);

	// Symbol selbst extrahieren
	        while ((cptr = fgets (ptr, 500, fsrc)) != NULL) {
		struct mrc mrc;
		long Code;
		register int i;
		long oldRec;


			if (*inline == ';') {
			// Kommentar
				ptr = inline;
				continue;
			}
        	        if ((cptr = strchr (inline, '\n')) != NULL) *cptr = '\0';
			if (inline[strlen(inline)-1] == '\\') {
			// Fortsetzungszeile
				ptr = &inline[strlen(inline)-1];
				continue;
			}
			cptr = inline;
			i = 0;
			memset (&mrc, '\0', sizeof(struct mrc));
			dba.file_no = MRC;
			oldRec = 0;
			while ((cptr = myatoi (cptr, &Code)) != NULL) {
				mrc.rlcode[i++] = (signed char)Code;
				if (i == 120) {
				// neuen Satz anfangen
				long Rec;

					z_fillnew (&dba, &mrc);
					Rec = dba.rec_no;
					if (oldRec != 0) {
						dba.rec_no = oldRec;
						z_readrec (&dba, &mrc);
						mrc.zncode = Rec;
						z_writerec (&dba, &mrc);
					}
					oldRec = Rec;
					i = 0;
					memset (&mrc, '\0', sizeof(struct mrc));
				}
			}
			if (i != 0) {
			// letzten Satz wegschreiben
			long Rec;

				z_fillnew (&dba, &mrc);
				Rec = dba.rec_no;
				if (oldRec != 0) {
					dba.rec_no = oldRec;
					z_readrec (&dba, &mrc);
					mrc.zncode = Rec;
					z_writerec (&dba, &mrc);
				}
			}
		}
	// Nummer ausgeben
		printf ("\b\b\b\b%4d", ++zeile);
		ptr = inline;
        }
        z_close (dbnum);

exit (0);
}

char *
myatoi (cptr, iptr)
register char *cptr;
register long int *iptr;
{
register int sign;

        while (*cptr && isspace (*cptr)) cptr++;
        *iptr = 0;
        sign = 0;
        if (*cptr == '-') {
                sign = 1;
                cptr++;
        }
        while (*cptr && isdigit (*cptr)) *iptr = *iptr * 10 + *cptr++ - '0';
        if (*cptr == '\0') return (NULL);
        if (sign) *iptr = -(*iptr);
        
return (cptr);
}


