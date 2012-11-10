/* Findendes vorhergehenden Schluessels ueber einen BTree       */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZPREV_F.C              last update: 24. November 1989  */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)zprev_f.c   2.6  90/05/09";
#endif

#ifdef MSWIND
#include <windows.h>
#endif 
#include <stdio.h>
#include <fcntl.h>
#include "dbtypes.h"
#include "errdef.h"
#include "dioexter.h"
#include "keyexter.h"
 
INT FUNCTYPE
zprev_ (dba, keyno)
DB_ADDR *dba;
register INT *keyno;
{
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZPREV_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZPREV_F));
#endif  
        if (*keyno < 0 || *keyno >= size_kt) return (dberr (S_NOKEY, ZPREV_F));
/* Finden des gesuchten Datensatzes */
        return (key_prev ((short)*keyno, dba));
}
