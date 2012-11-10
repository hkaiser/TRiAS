/* Fortran Schnittstelle (UNIX) - Schreiben eines Datensatzes in die DB */
/* File: ZWRITE_F.C             last update: 22. November 1989          */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)zwrite_f.c  2.7  90/05/09";
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
 
/* Wegschreiben eines Datensatzes, aktualisieren Schluesseldateien */
INT FUNCTYPE
zwrite_ (dba, ptr)
DB_ADDR *dba;
char *ptr;
{
register short keyindex;
register KEY_ENTRY *kt_p;
char *data;
register short offset;
 
/* Test ob DB geoeffnet ist */
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZWRITE_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZWRITE_F));
#endif  
        if (dba->file_no < 0 || dba->file_no >= size_rt)
                return (db_error (S_INVADDR, ZWRITE_F, dba));

// Satz auf Gltigkeit berprfen
	if (db_read (dba, &data) != S_OKAY) return (db_status);                         
	if (*((INT *)(data)+1) == MAXPOSLONG)
		return db_error (S_DELRECORD, ZWRITE, dba);
                
/* Schluesseldateien laufendhalten */
        if ((keyindex = record_table[(short)dba->file_no].rt_keyfile) != NONE) {
        /* Satz enthaelt Schluessel */
                do {
                        kt_p = &key_table[keyindex];
                        offset = kt_p->kt_offset;
			if (!_fmemcmp (data+offset, ptr+offset, kt_p->kt_len))
                        /* wenn alter Schluessel gleich neuem, dann weiter */
                                continue;
                        if (key_init (kt_p) != S_OKAY) return (db_status);
                        if (!nullcmp (data+offset, kt_p->kt_len))
                        /* wenn alter Schluessel nicht gleich Null */
                                db_status = delete_key (dba, data+offset);
                        if (db_status == S_NOTFOUND)  db_status = S_OKAY;
                        else if (db_status != S_OKAY) return (db_status);

                        if (!nullcmp (ptr+offset, kt_p->kt_len)) 
                        /* wenn neuer Schluessel nicht gleich Null */
                                if (insert_key (dba, ptr+offset) != S_OKAY) 
                                        return (db_status);
                        working_file = NONE;
                } while ((keyindex = kt_p->kt_chain) != NONE);
        }
        /* Datensatz selbst wegschreiben */
        if (db_write (dba, ptr) != S_OKAY) return (db_status);
 
return (db_status = S_OKAY);
}
