/* Setzen der Anzahl zur Verfuegung stehenden Filedeskriptoren  */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZFILES_F.C             last update: 5. Dezember 1989   */

#include "trias01p.hxx"

INT FUNCTYPE
zfiles_ (num)
int num;
{
        if (dbopen) return (dberr (S_DBOPEN));
        if (num < 1) max_open_files = 1;
        else max_open_files = num;
 
return (db_status = S_OKAY);
}
