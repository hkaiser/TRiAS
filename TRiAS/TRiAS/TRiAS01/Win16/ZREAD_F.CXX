/* Fortran-Schnittstelle (UNIX) - Lesen eines Datensatzes       */
/* File: ZREAD_F.C              last update: 22. November 1989  */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)zread_f.c   2.6  90/05/09";
#endif

#ifdef MSWIND
#include <windows.h>
#endif 
#include <stdio.h>
#include <string.h>
#include "dbtypes.h"
#include "errdef.h"
#include "dioexter.h"
#include "keyexter.h"
 
/* Lesen eines gesuchten Datensatzes */

INT FUNCTYPE
zread_ (dba, ptr)
register DB_ADDR *dba;
char *ptr;
{
char *data;
 
/* Test, ob DB geoeffnet ist */
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZREAD_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZREAD_F));
#endif  
        if (dba->file_no < 0 || dba->file_no >= size_rt)
                return (db_error (S_INVADDR, ZREAD_F, dba));

/* Datensatz lesen */
        if (db_read (dba, &data) != S_OKAY) return (db_status);
	if (*((INT *)(data)+1) == MAXPOSLONG)
		return db_error (S_DELRECORD, ZREAD, dba);
                
	memcpy (ptr, data, record_table[(short)dba->file_no].rt_len);

return (db_status = S_OKAY);
}
 
