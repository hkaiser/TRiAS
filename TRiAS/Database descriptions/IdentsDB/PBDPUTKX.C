/* Routine zum Bilden der Routinennamen-Metadateien             */
/* File: PBDPUTKI.C                                               */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "dbtypes.h"
#include "errdef.h"
#include "errdb.h"

#include <idtdb.h>
#include <mprotos.h>
#include <zprotos.h>

static char *usage = "Verwendung: %s srctext dbname.\n";

char *myatoi (char *, long *);
char *myatox (char *, long *);

main (argc, argv)
int argc;
char *argv[];
{
register int dbnum;
register char *cptr, *ptr;
register FILE *fsrc;
FILE *fopen ();
char inline[1001];
char KurzText[40];
register int zeile = 0;
long Ident, Satz;
long RC;
short ktLen;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fsrc = fopen (argv[1], "r")) == NULL) {
                fprintf (stderr, "%s: Kann Eingabedatei %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (3);
        }
//	SetCopyrightFlag (FALSE);
	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[2], argv[2], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (2);
        }

	ktLen = (GetDBVersion() <= PBD030000001) ? 16 : 32;

	printf ("Identifikatorsatz:     ");
	fflush (stdout);
	ptr = inline;
        while ((cptr = fgets (ptr, 500, fsrc)) != NULL) {
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
                if ((cptr = myatox (inline, &Ident)) == NULL) {
			ptr = inline;
                        continue;
		}
                while (*cptr && isspace (*cptr)) cptr++;
	// Identsatz schreiben
		DBASSERT (mputki (Ident, &Satz));
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
			DBASSERT (mputkt ('i', Satz, KurzText));
		} else {
		// KurzText gleich Langtext
			if (strlen (cptr) <= ktLen) {
				DBASSERT (mputkt ('i', Satz, cptr));
			} else {
			// nur die ersten 16 Zeichen als KurzText nehmen
			char tmp[33];

				strncpy (tmp, cptr, ktLen);
				tmp[ktLen] = '\0';
				DBASSERT (mputkt ('i', Satz, tmp));
			}
		}
	// LangText schreiben
		DBASSERT (mputtxi (Satz, cptr));
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


char *myatox (char *cptr, long *iptr)
{
char *pEnd = NULL;

	*iptr = strtoul (cptr, &pEnd, 16);

return pEnd;
}
