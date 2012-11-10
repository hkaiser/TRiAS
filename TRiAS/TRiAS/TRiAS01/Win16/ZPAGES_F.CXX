/* Setzen der Anzahl der virtuell verwalteten Speicherpages     */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZSETPAGE.C             last update: 5. Dezember 1989   */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)zpages_f.c  2.5  90/05/09";
#endif

#include "dbtypes.h"
#include "dioexter.h"
#include "errdef.h"

INT FUNCTYPE
zpages_ (num)
int num;
{
        if (dbopen) return (dberr (S_DBOPEN));
        if (num < MINDYNPAGES) no_of_pages = DEFPAGES;
        else no_of_pages = num;
 
return (db_status = S_OKAY);
}
