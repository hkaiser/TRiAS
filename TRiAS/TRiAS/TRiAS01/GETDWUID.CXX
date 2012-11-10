/* Liefert DB-Passwortfileeintrag fuer Nutzer mit dbuid         */
/* File: GETDWUID.C                                             */

#include "trias01p.hxx"

#include <dwd.h>
 
struct dbpasswd * FUNCTYPE getdwuid (int dbuid, char FAR *dbname) {
register struct dbpasswd *p;
 
	if (dbname == NULL) return NULL;

        setdwent (dbname);
        while ((p = getdwent ()) && dbuid != p->dw_uid)
                ;
        enddwent ();
 
return (p);
}
