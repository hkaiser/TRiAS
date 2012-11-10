/* Vorgeben eines Nutzerpasswortes fuer DB/AKS                  */
/* File: DBPASSWD.CXX           last update: 28. September 1989 */

#include <commonvu.hxx>
#include <containr.hxx>
#include <drawobj.hxx>
#include <cvext.hxx>

#include "draw_obj.hxx"

extern "C" {
	#include "protos.h"
	#include "dwd.h"
}
 
struct  dbpasswd *dwd;
char    *mktemp ();
char    *dw;
char    dwbuf[10];
char    buf[512];
char    db_pw_file[80];
 
ErrCode dbpasswd (DBTemplate &DB) {
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
int rest;
 
        insist = 0;

// im Passwordfile nachsehen, ob Nutzereintrag existiert
	dwd = getdwnam (DB.GetUserName(), DB.GetDBName());
        if (dwd == NULL) {
	// Kein Eintrag fuer Nutzer vorhanden 
		return (ErrCode)db_error (EC_
        }

        if (dwd->dw_passwd[0]) {
        /* altes Passwort erfragen */
                strcpy (dwbuf, getpass ("Eingabe des alten Passwortes: "));
                dw = crypt (dwbuf, dwd->dw_passwd);
                if (strcmp (dw, dwd->dw_passwd) != 0) {
                        printf("Sorry.\n");
                        goto bex;
                }
        }
tryagn:
        strcpy (dwbuf, getpass ("Eingabe des neuen Passwortes: "));
        dwlen = strlen (dwbuf);
        if (dwlen == 0) {
                printf("Passwort bleibt unveraendert.\n");
                goto bex;
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
                        printf ("Bitte verwenden Sie mindestens einen Buchstaben!\n");
                else
                        printf ("Bitte verwenden Sie ein laengeres Passwort.\n");
                fflush(stdout);
                insist++;
                goto tryagn;
        }
/* Neues Passwort wiederholt abfragen */
        if (strcmp (dwbuf, getpass ("Wiederholung des neuen Passwortes: ")) != 0) {
                printf ("Fehler - Passwort bleibt unveraendert.\n");
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
*/      mktemp(temp);
        close (creat (temp, 0600));
        if ((tf = fopen (temp, "w")) == NULL) {
                printf ("Kann temp-Datei %s nicht eroeffnen.\n", temp);
                goto bex;
        }
/* Umkopieren des neuen Passwortes ins temp-File */
        setdwent (argv[1]);
        while ((dwd = getdwent ()) != NULL) {
                if (strcmp (dwd->dw_name, uname) == NULL) 
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
        if ((fi = open (temp, 0)) < 0) {
                printf("Die temp-Datei ist verschwunden!\n");
                goto out;
        }
        if ((fo = creat (db_pw_file, 0644)) < 0) {
                printf ("Kann Passwortdatei %s nicht neu erzeugen.\n", db_pw_file);
                goto out;
        }
        while ((u = read (fi, buf, sizeof(buf))) > 0) write (fo, buf, u);
 
out:
        unlink (temp);
/*      dwunlock();*/
        exit(0);
}
