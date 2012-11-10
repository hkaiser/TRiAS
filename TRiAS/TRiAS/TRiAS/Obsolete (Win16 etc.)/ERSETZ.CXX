/* Ersetzen von @V in einer Datei durch argv[1]                 */
/* File: ERSETZ.CXX              last update: 5. Dezember 1989   */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char cbBuffer[_MAX_PATH];
char cbError1Fmt[] = "Usage: %s arg1 arg2 ... infile outfile\n\r"
		     "       im Text wird: @A --> arg1, @B --> arg2 ...";
char cbError2Fmt[] = "Kann Ausgabedatei \'%s\' nicht eröffnen.";
char cbError3Fmt[] = "Kann Eingabedatei \'%s\' nicht eröffnen.";
char cbErrorCaption[] = "ERSETZ: Kommandozeilenfehler";

int main (int argc, char *argv[])
{
register int c, c1;
FILE *fout, *fin;

    if (argc < 2) {
        wsprintf (cbBuffer, cbError1Fmt, argv[0]);
        MessageBox (NULL, cbBuffer, cbErrorCaption, MB_OK);
        return 0;
    }

// argv[argc-1] ist AusgabeDateiName
	fout = fopen (argv[argc-1], "w");
	if (fout == NULL) {
		wsprintf (cbBuffer, cbError2Fmt, argv[argc-1]);
		MessageBox (NULL, cbBuffer, cbErrorCaption, MB_OK);
		return 0;
	}

// letztes oder vorletztes Argument ist Eingabedatei
	fin = fopen (argv[argc-2], "r");
	if (fin == NULL) {
		wsprintf (cbBuffer, cbError3Fmt, __argv[__argc-2]);
		MessageBox (NULL, cbBuffer, cbErrorCaption, MB_OK);
		return 0;
	}

// Eingabedatei verarbeiten
    while ((c = getc (fin)) != EOF) {
        if (c == '@') {
            if ((c1 = getc (fin)) == EOF) 
				break;
            if ((c1 >= 'A') && (c1 <= 'Z') && (c1 - argc - '@' < 0)) 
			{
                if (strcmp (argv[c1-'@'], "-"))
                        fprintf (fout, "%s", argv[c1-'@']);
                continue;
            } else
                ungetc (c1, fin);
        }
        putc (c, fout);
    }
        
return 0;
}
 
