/* Fortran Schnittstelle (UNIX) - Loeschen einer Datenbasis             */
/* File: ZDESTR_F.C             last update: 5. Dezember 1989           */

#include "trias01p.hxx"

#ifndef MODEL
#define MODEL ' '
#endif

#ifdef vms
#include "vmstypes.h"
#endif

#ifdef unix
INT
zdestr_ (s_dbname, p_flag, l_dbname)
char *s_dbname;
long l_dbname;
int *p_flag;    /* Passworddatei loeschen */
#endif

#ifdef msdos
INT
zdestr_ (dbname, p_flag)
char *dbname;
int *p_flag;    /* Passworddatei loeschen */
#endif

#ifdef vms
zdestr (s_dbname, p_flag)
struct str_par *s_db;
int *p_flag;    /* Passworddatei loeschen */
#endif
{
char command[80];
register int i;
#ifdef unix
char dbname[81];
register char *cptr;
char *strrlchr ();

        memset (dbname, '\0', 81);
        strncpy (dbname, s_dbname, (int)l_dbname > 80 ? 80 : (int)l_dbname);
        if ((cptr = strrlchr (dbname, ' ')) != NULL) *cptr = '\0';
#endif
#ifdef vms
char dbname[81];
register char *cptr;
char *strrlchr ();

        memset (dbname, '\0', 81);
        strncpy (dbname, s_db->str, (int)s_db->len > 80 ? 80 : (int)s_db->len);
        if ((cptr = strrlchr (dbname, ' ')) != NULL) *cptr = '\0';
#endif

        for (i = 0; i < MAXDB; ++i) {
                if (db_table[i].db_name == NULL) continue;
                if (!strcmp (dbname, db_table[i].db_name)) break;
        }
        
        if (i != MAXDB) z_close (i);
                
        sprintf (command, "dbdel%c -s %s %s\n", MODEL, 
                        *p_flag ? "-p" : "", dbname);
        if (system (command) < 0) return (dberr (S_SPAWN, ZDESTR_F));
 
return (db_status = S_OKAY);
}

