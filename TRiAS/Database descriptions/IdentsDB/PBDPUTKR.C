/* Routine zum Bilden der Routinennamen-Metadateien             */
/* File: PBDPUTKR.C                                               */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dbtypes.h"
#include "errdef.h"
#include "errdb.h"

#include <mprotos.h>
#include <zprotos.h>

static char *usage = "Verwendung: %s srctext dbname.\n";

main (argc, argv)
int argc;
char *argv[];
{
register int dbnum;
register char *cptr, *ptr;
register FILE *fsrc;
FILE *fopen ();
char inline[1001];
char KurzText[20];
register int zeile = 0;
long Rel, Satz;
short RTyp;
long RC;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fsrc = fopen (argv[1], "r")) == NULL) {
                fprintf (stderr, "%s: Kann Eingabedatei %s nicht er”ffnen.\n", argv[0], argv[1]);
                exit (3);
        }
	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[2], argv[2], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht er”ffnen.\n", argv[0], argv[2]);
                exit (2);
        }
	printf ("Relationssatz:     ");
	fflush (stdout);
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
                if ((cptr = myatoi (inline, &Rel)) == NULL) {
			ptr = inline;
                        continue;
		}
                while (*cptr && isspace (*cptr)) cptr++;

		RTyp = *cptr++;		// RelationsTyp
		if (tolower (RTyp) != 'h' && tolower (RTyp) != 'k') {
			fprintf (stderr, "Falscher Relationstyp.\n");
			exit (1);
		}

		while (*cptr && isspace (*cptr)) cptr++;

	// Relationssatz schreiben
		DBASSERT (mputkr (Rel, tolower (RTyp), &Satz));

	// Text extrahieren
		KurzText[0] = '\0';
		if (*cptr == '/' && *(cptr+1) == '*') {
		// Kurztext
		register char *pKurzText = KurzText;

			cptr += 2;
			while (!(*cptr == '*' && *(cptr+1) == '/'))
				*pKurzText++ = *cptr++;
			*pKurzText = '\0';
			cptr += 2;	// '*/' berspringen
		// KurzText schreiben
			DBASSERT (mputkt ('r', Satz, KurzText));
		} else {
		// KurzText gleich Langtext
			if (strlen (cptr) <= 16)
				DBASSERT (mputkt ('r', Satz, cptr));
		}
	// LangText schreiben
		DBASSERT (mputtxr (Satz, cptr));
		printf ("\b\b\b\b%4d", ++zeile);
		fflush (stdout);
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

