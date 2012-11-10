/* Bereitstellen und beschreiben eines neuen Datensatzes        */
/* Fortran-Schnittstelle (UNIX)                                 */
/* File: ZNEW_F.C               last update: 22. November 1989  */

#include "trias01p.hxx"
 
INT FUNCTYPE
znew_ (dba, ptr)
DB_ADDR *dba;
char *ptr;
{
register short keyindex;
register KEY_ENTRY *kt_p;
register short offset;
 
/* Test, ob DB geoeffnet ist */
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZNEW_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZNEW_F));
#endif  
        if (dba->file_no < 0 || dba->file_no >= size_rt)
                return (db_error (S_INVADDR, ZNEW_F, dba));
                
/* Anfordern des neuen Datensatzes */
        if (db_pzalloc (record_table[(short)dba->file_no].rt_file, 
                                        &dba->rec_no) != S_OKAY) 
                return (db_status);
/* Schluesseldateien laufendhalten */
        if ((keyindex = record_table[(short)dba->file_no].rt_keyfile) != NONE) {
        /* Satz enthaelt Schluessel */
                do {
                /* fuer alle Schluessel */
                        kt_p = &key_table[keyindex];
                        offset = kt_p->kt_offset;
                        if (key_init (kt_p) != S_OKAY) return (db_status);

                        if (!nullcmp (ptr+offset, kt_p->kt_len)) 
                        /* wenn neuer Schluessel nicht gleich Null */
                                if (insert_key (dba, ptr+offset) != S_OKAY) 
                                        return (db_status);

                        working_file = NONE;
                } while ((keyindex = kt_p->kt_chain) != NONE);
        }
/* Satz selbst wegschreiben */
        if (db_write (dba, ptr) != S_OKAY) return (db_status);
 
return (db_status = S_OKAY);
}
