/* Liefert DB-Passwortfileeintrag fuer Nutzer `name'            */
/* File: GETDWNAM.C             last update: 22. September 1989 */

#include "trias01p.hxx"

#include <dwd.h>
 
struct dbpasswd * FUNCTYPE getdwnam (char *name, char *dbname) 
{
register struct dbpasswd *p;
 
	if (name == NULL || dbname == NULL)
		return NULL;

	setdwent (dbname);
	while ((p = getdwent ()) && stricmp (name, p->dw_name))
                ;
	enddwent ();
	return (p);
}


