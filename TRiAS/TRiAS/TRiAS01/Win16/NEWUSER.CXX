// Einrichten eines neuen User-Eintrages in der PWD-Datei
// Datei: NEWUSER.C

#include <stdio.h>
#include <signal.h>
#include <io.h>
#include <string.h>
#include <time.h>

#include "dwd.h"
#include "dbversio.h"

char	temp1[20]	= ".\\nXXXXXX";

struct  dbpasswd *dwd;

char    fulltmp[80];
char    db_pw_file[80];
char	syscmd[128];
 
static char titel[] = "Einrichten eines neuen Nutzereintrages";
 
void main(int argc, char *argv[]) {
char *uname;
short i = 0;		// Nutzereintr„ge z„hlen
time_t timeVal;
FILE *tf;

        fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
 
        if (argc != 3) {
                printf ("Verwendung: newuser DBname Nutzername\n");
                goto bex;
        }
        uname = argv[2];        /* Nutzername */
        printf ("Ein Eintrag fr Nutzer '%s' in DB '%s' wird eingerichtet.\n\n", uname, argv[1]);
        fflush (stdout);
 
        strncpy (db_pw_file, argv[1], 75);
        strcat (db_pw_file, ".pwd");

// uniq Name generieren
	mktemp(temp1);
	strcpy (fulltmp, temp1);
	strcat (fulltmp, ".pwd");

// Passwd - Datei entpacken
	sprintf (syscmd, "expand %s %s > nul", db_pw_file, fulltmp);
	system (syscmd);
	setdwent (fulltmp);

        while (((dwd = getdwent ()) != NULL) && strcmp (dwd->dw_name, uname))
        /* Suchen des Nutzereintrages im Passwordfile */
		i++;
        if (dwd != NULL) {
        /* Eintrag fr Nutzer bereits vorhanden */
                printf ("Nutzereintrag fr Nutzer %s ist bereits vorhanden.\n", uname);
                goto bex;
        }
        enddwent ();

        if ((tf = fopen (fulltmp, "r+")) == NULL) {
                printf ("Kann temp-Datei %s nicht er”ffnen.\n", temp1);
                goto bex;
        }
	fseek (tf, 0L, SEEK_END);	// ans Ende positionieren
	time (&timeVal);
	fprintf (tf, "%s::%u:0x%lx:0x%lx: Nutzereintrag generiert %s",
		uname, i,
		0x7fffffffL,
		0x7fffffffL,
		ctime (&timeVal));
	fclose (tf);

	sprintf (syscmd, "compress %s %s > nul", fulltmp, db_pw_file); 
	system (syscmd);

        unlink (fulltmp);

        exit(0);
bex:
 
        exit(1);
}


