/* Routine zum Bilden der Routinennamen-Metadateien             */
/* File: PBDPUTKM.C                                               */

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

static char inline[1001];
static char LangText[501];

main (argc, argv)
int argc;
char *argv[];
{
register int dbnum;
register char *cptr, *ptr;
register FILE *fsrc;
FILE *fopen ();
char KurzText[20];
register int zeile = 0;
long Merkmal, Satz, GetMerkmalsWerte(long, FILE *);
long WF;
short MTyp;
long WVon[2], WBis[2];
long RC;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fsrc = fopen (argv[1], "r")) == NULL) {
                fprintf (stderr, "%s: Kann Eingabedatei %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (3);
        }
// 	SetCopyrightFlag (FALSE);
	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[2], argv[2], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (2);
        }
	printf ("Merkmalssatz:     ");
	fflush (stdout);
	ptr = inline;
        while ((cptr = fgets (ptr, 500, fsrc)) != NULL) {
                char *myatoi (), *strchr (), *myatof ();

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

	// Merkmalskode einlesen
                if ((cptr = myatoi (inline, &Merkmal)) == NULL) {
			ptr = inline;
                        continue;
		}
                while (*cptr && isspace (*cptr)) cptr++;

	// restliche Merkmalsparameter analysieren
		switch (MTyp = *cptr++) {
		case 'I':
		case 'A':	// Objektmerkmal
		case 'B':	// IdentMerkmal
		case 'C':	// Sichtmerkmal
			if ((cptr = myatoi (cptr, &WF)) == NULL) {
				ptr = inline; continue;
			}
			if ((cptr = myatoi (cptr, WVon)) == NULL) {
				ptr = inline; continue;
			}
			WVon[1] = 0L;
			if ((cptr = myatoi (cptr, WBis)) == NULL) {
				ptr = inline; continue;
			}
			WBis[1] = 0L;
			break;

		case 'F':
			if ((cptr = myatoi (cptr, &WF)) == NULL) {
				ptr = inline; continue;
			}
			if ((cptr = myatof (cptr, (double *)&WVon)) == NULL) {
				ptr = inline; continue;
			}
			if ((cptr = myatof (cptr, (double *)&WBis)) == NULL) {
				ptr = inline; continue;
			}
			break;
		}
		while (*cptr && isspace (*cptr)) cptr++;

	// Text extrahieren (MerkmalsCode
		KurzText[0] = '\0';
		if (*cptr == '/' && *(cptr+1) == '*') {
		// Kurztext
		register char *pKurzText = KurzText;

			cptr += 2;
			while (!(*cptr == '*' && *(cptr+1) == '/'))
				*pKurzText++ = *cptr++;
			*pKurzText = '\0';
			cptr += 2;	// '*/' berspringen
		} else {
		// KurzText gleich Langtext
			if (strlen (cptr) <= 16)
				strcpy (KurzText, cptr);
		}
	// LangText kopieren
		memset (LangText, '\0', sizeof(LangText));
		strcpy (LangText, cptr);
	// Merkmalssatz schreiben
		DBASSERT (mputkm (Merkmal, MTyp, WF, WVon, WBis, &Satz));

	// ggf. Merkmalswerte verarbeiten
		if (WBis[0] == -1L) 
			GetMerkmalsWerte (WVon[0], fsrc);  // liefert 1. MW-Satz

	// KurzText schreiben
		if (*KurzText != '\0') 
			DBASSERT (mputkt ('m', Satz, KurzText));

	// LangText schreiben
		DBASSERT (mputtxm (Satz, LangText));

	// Nummer anzeigen
		printf ("\b\b\b\b%4d", ++zeile);
		fflush (stdout);
		ptr = inline;
        }
        z_close (dbnum);

exit (0);
}

long GetMerkmalsWerte (long Anzahl, FILE *fsrc) {
register char *cptr, *ptr;
long Satz = 0, MW = 0;
char *myatoi (), *strchr ();
long Merkmal, MWert;
char MTyp;
int First = TRUE;
long RC;

	ptr = inline;
        while (Anzahl-- > 0) {
		if ((cptr = fgets (ptr, 500, fsrc)) == NULL)
			return MW;

		if (*inline == ';') {
		// Kommentar
			ptr = inline;
			continue;
		}
                if ((cptr = strchr (inline, '\n')) != NULL) *cptr = '\0';
		if (inline[strlen(inline)-1] == '\\') {
		// Fortsetzungszeile
			Anzahl++;
			ptr = &inline[strlen(inline)-1];
			continue;
		}

	// Merkmalskode einlesen
                if ((cptr = myatoi (inline, &Merkmal)) == NULL) {
			ptr = inline; continue;
		}
                while (*cptr && isspace (*cptr)) cptr++;
		MTyp = *cptr++;
		if ((cptr = myatoi (cptr, &MWert)) == NULL) {
			ptr = inline; continue;
		}
		if ((cptr = myatoi (cptr, &MWert)) == NULL) {
			ptr = inline; continue;
		}
	// Merkmalswert abspeichern
		DBASSERT (mputwm (Merkmal, MWert, &Satz));
		if (First) {
		// ersten Satz merken
			First = FALSE;
			MW = Satz;
		}
	// Text einlesen und speichern
		if ((cptr = myatoi (cptr, &MWert)) == NULL) {
			ptr = inline; continue;
		}
		while (*cptr && isspace (*cptr)) cptr++;
		DBASSERT (mputtxw (Satz, cptr));	
	}

return MW;
}

char *myatoi (cptr, iptr)
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

char *myatof (cptr, dptr)
register char *cptr;
register double *dptr;
{
	while (*cptr && isspace (*cptr)) cptr++;

	*dptr = atof (cptr);
	while (*cptr && !isspace (*cptr)) cptr++;
        
return (cptr);
}


