/* Ersetzen von @V in einer Datei durch argv[1]                 */
/* File: ERSETZ.C              last update: 5. Dezember 1989   */

#include <stdio.h>
#include <io.h>
 
main (argc, argv)
int argc;
char *argv[];
{
register int c, c1;
FILE *fout, *fin;

        if (argc < 2) {
                fprintf (stderr, "Usage: %s arg1 arg2 ... [ < infile][ > outfile]\n", argv[0]);
                fprintf (stderr, "       im Text wird: @A --> arg1, @B --> arg2 ...\n");
                exit (1);
        }

// berprfen, ob stdin bzw. stdout umgeleitet wurden
	if (isatty (fileno (stdout))) {
	// Ausgabe nicht umgeleitet: argv[argc-1] ist AusgabeDateiName

		fout = fopen (argv[argc-1], "w");
		if (fout == NULL) {
			fprintf (stderr, "Kann Ausgabedatei \'%s\' nicht er”ffnen.\n", argv[argc-1]);
			exit (1);
		}
	} else
		fout = stdout;

	if (isatty (fileno (stdin))) {
	// Eingabe nicht umgeleitet: letztes oder vorletztes Argument ist Eingabedatei
	int InFile = fout == stdout ? argc - 1 : argc - 2;

		fin = fopen (argv[InFile], "r");
		if (fin == NULL) 
			fin = stdin;
	} else
		fin = stdin;

// Eingabedatei verarbeiten
        while ((c = getc (fin)) != EOF) {
                if (c == '@') {
                        if ((c1 = getc (fin)) == EOF) break;
                        if ((c1 >= 'A') && (c1 <= 'Z') 
                         && (c1 - argc - '@' < 0)) {
                                if (strcmp (argv[c1-'@'], "-"))
                                        fprintf (fout, "%s", argv[c1-'@']);
                                continue;
                        } else
                                ungetc (c1, fin);
                }
                putc (c, fout);
        }
 
exit (0);
}
 
