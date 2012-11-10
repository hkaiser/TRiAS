// Vorgeben eines Nutzerpasswortes fuer DIRIS
// File: DBPASSWD.C

#include <stdio.h>
#include <signal.h>
#include <io.h>
#include <string.h>

#include "dwd.h"
#include "dbversio.h"
 
char    temp[20]        = ".\\dXXXXXX";
char	temp1[20]	= ".\\wXXXXXX";

struct  dbpasswd *dwd;

char    *crypt (char _far *, char *);
char    *getpass (char *);

char    *dw;
char    dwbuf[10];
char    buf[512];
char    db_pw_file[80];
#if defined(COMPRESS_PWD)
char	syscmd[128];
#endif
 
static char titel[] = "Festlegen eines Nutzer-Passwortes";
static char format[30];
#define T_LEN sizeof(titel)
 
main(argc, argv)
char *argv[];
{
        char *p;
        int i;
        char saltc[2];
        long salt;
        int u,g,fi,fo;
        int insist;
        int ok, flags;
        int c;
        int dwlen;
        FILE *tf;
        char *uname;
        int rest;
 
        fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
 
        insist = 0;
        if (argc != 3) {
                printf ("Verwendung: dbpasswd db_name user\n");
                goto bex;
        }
        uname = argv[2];        /* Nutzername */
        printf ("Neues Passwort in DB `%s' fr Nutzer `%s'.\n\n", argv[1], uname);
        fflush (stdout);
 
        strncpy (db_pw_file, argv[1], 75);
        strcat (db_pw_file, ".pwd");

// uniq Name generieren
	mktemp(temp1);

#if defined(COMPRESS_PWD)
// Passwd - Datei entpacken
	sprintf (syscmd, "expand %s.pwd %s.pwd > nul", argv[1], temp1);
	system (syscmd);
	setdwent (temp1);
#else
        setdwent (argv[1]);
#endif

        while (((dwd = getdwent ()) != NULL) && strcmp (dwd->dw_name, uname))
        /* Suchen des Nutzereintrages im Passwordfile */
                ;
        if (dwd == NULL) {
        /* Kein Eintrag fuer Nutzer vorhanden */
                printf ("Kein Nutzereintrag fr Nutzer %s vorhanden.\n", uname);
                goto bex;
        }
        enddwent ();

        if (dwd->dw_passwd[0]) {
        /* altes Passwort erfragen */
                strcpy (dwbuf, getpass ("Eingabe des alten Passwortes: "));
                dw = crypt (dwbuf, dwd->dw_passwd);
                if (strcmp (dw, dwd->dw_passwd) != 0) {
                        printf ("Sorry.\n");
                        goto bex;
                }
        }
tryagn:
        strcpy (dwbuf, getpass ("Eingabe des neuen Passwortes: "));
        dwlen = strlen (dwbuf);
        if (dwlen == 0) {
		dw = "\0";	// kein neues Passwort
                printf ("Altes Passwort wird gel”scht.\n");
                goto outNewPWD;
        }
        ok = 0;
        flags = 0;
        p = dwbuf;

/* Passwort auf Verwendbarkeit pruefen */
        while (c = *p++) {
                if(c >= 'a' && c <= 'z') flags |= 2;
                else if(c >= 'A' && c <= 'Z') flags |= 4;
                else if(c >= '0' && c <= '9') flags |= 1;
                else flags |= 8;
        }
        if (flags >= 7 && dwlen >= 4) ok = 1;
        if (((flags == 2) || (flags == 4)) && dwlen >= 6) ok = 1;
        if (((flags == 3) || (flags == 5) || (flags == 6)) && dwlen >= 5)
                ok = 1;
 
        if ((ok == 0) && (insist < 2)) {
                if (flags == 1)
                        printf ("Bitte verwenden Sie mindestens einen Buchstaben !\n");
                else
                        printf ("Bitte verwenden Sie ein l„ngeres Passwort.\n");
                fflush(stdout);
                insist++;
                goto tryagn;
        }
/* Neues Passwort wiederholt abfragen */
        if (strcmp (dwbuf, getpass ("Wiederholung des neuen Passwortes: ")) != 0) {
                printf ("Fehler - Passwort bleibt unver„ndert.\n");
                goto bex;
        }
/* Neues Passwort verschluesseln */
        time (&salt);

#ifdef unix
        salt += getpid();
#endif
 
        saltc[0] = salt & 077;
        saltc[1] = (salt>>6) & 077;
        for (i = 0; i < 2; i++){
                c = saltc[i] + '.';
                if(c > '9') c += 7;
                if(c > 'Z') c += 6;
                saltc[i] = c;
        }
        dw = crypt (dwbuf, saltc);
 
/* Neues Passwortfile Bilden */
#ifdef unix
        signal (SIGHUP, SIG_IGN);
        signal (SIGQUIT, SIG_IGN);
#endif
        signal (SIGINT, SIG_IGN);
/*      if (dwlock ("r")) {
                printf ("Temporary file busy -- try again\n");
                goto bex;
        }
*/

// Ausgabe des neuen Passwortes
outNewPWD:

	mktemp (temp);
        close (creat (temp, 0600));
        if ((tf = fopen (temp, "w")) == NULL) {
                printf ("Kann temp-Datei %s nicht er”ffnen.\n", temp);
                goto bex;
        }

#if !defined(COMPRESS_PWD)
	setdwent (argv[1]);
#else
	setdwent (temp1);
#endif

/* Umkopieren des neuen Passwortes ins temp-File */
        while ((dwd = getdwent ()) != NULL) {
                if (!strcmp (dwd->dw_name, uname)) 
                /* Passwort austauschen */
                        dwd->dw_passwd = dw;
                fprintf (tf, "%s:%s:%u:0x%lx:0x%lx:%s\n",
                        dwd->dw_name,
                        dwd->dw_passwd,
                        dwd->dw_uid,
                        dwd->dw_access,
                        dwd->dw_rw,
                        dwd->dw_comment);
        }
        enddwent ();
        fclose (tf);
 
/* Zurueckkopieren ins DB-Passwortfile */
#if !defined(COMPRESS_PWD)
        if ((fi = open (temp, 0)) < 0) {
                printf ("Die temp-Datei ist verschwunden!\n");
                goto out;
        }
        if ((fo = creat (db_pw_file, 0644)) < 0) {
                printf ("Kann Passwortdatei %s nicht neu erzeugen.\n", db_pw_file);
                goto out;
        }
        while ((u = read (fi, buf, sizeof(buf))) > 0) write (fo, buf, u);
#else
	sprintf (syscmd, "compress %s %s > nul", temp, db_pw_file); 
	system (syscmd);
#endif

out:
        unlink (temp);

#if defined(COMPRESS_PWD)
	unlink (strcat (temp1, ".pwd"));
#endif

/*      dwunlock();*/
        exit(0);
bex:
 
        exit(1);
}

#define MAXPASSWD 20

char inPasswd[MAXPASSWD+1];

char *getpass (char *outString) {
short inCnt = 0;
int c;

	printf (outString);
	while ((c = getch()) != '\r' && inCnt < MAXPASSWD)
		inPasswd[inCnt++] = c;
	inPasswd[inCnt] = '\0';
	printf ("\n");

return inPasswd;
}
