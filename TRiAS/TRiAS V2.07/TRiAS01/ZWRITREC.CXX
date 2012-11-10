/* Schreiben eines Datensatzes in die DB                        */
/* File: ZWRITREC.C             last update: 22. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"
 
#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/* Wegschreiben eines Datensatzes, aktualisieren Schluesseldateien */
extern "C" 
int FUNCTYPE EXPORT01 z_writerec (DB_ADDR *dba, void *ptr)
{
	SYNC_DBACCESS (g_pDbMutex, (0 != dba->db_no) ? dba->db_no : GetHandleFromPtr(pActivatedDB));

register short keyindex;
register KEY_ENTRY *kt_p;
char *data;
register short offset;
 
/* Test ob DB geoeffnet ist */
#ifndef MULTI_DB
	if (!dbopen) return (dberr (S_DBOPEN, ZWRITE));
#else
//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
	TX_ASSERT_POINTER(act_db, DBASE);
//	if (act_db == NULL) return (dberr (S_DBOPEN, FILLNEW));
#endif  
	TX_ASSERT_POINTER(dba, DB_ADDR);
	TX_ASSERT(TIsValidAddress (record_table, sizeof(REC_ENTRY)*size_rt, false));
	TX_ASSERT(TIsValidAddress (key_table, sizeof(KEY_ENTRY)*size_kt, false));

		if (dba->file_no < 0 || dba->file_no >= size_rt)
			return (db_error (S_INVADDR, ZWRITE, dba));

// Satz einlesen
	if (db_read (dba, (void **)&data) != S_OKAY) return (db_status);

// prüfen, ob Satz gelöscht ist
	if (*(INT *)data == MAXPOSLONG)
		return db_error (S_DELRECORD, ZWRITE, dba);

/* Schlüsseldateien laufendhalten */
	if ((keyindex = record_table[(short)dba->file_no].rt_keyfile) != NONE) 
	{	/* Satz enthaelt Schlüssel */
		do {
			TX_ASSERT(keyindex >= 0 && keyindex < size_kt);

			kt_p = &key_table[keyindex];
			offset = kt_p->kt_offset;

			if (!memcmp (data+offset, (char *)ptr+offset, kt_p->kt_len))
			/* wenn alter Schlüssel gleich neuem, dann weiter */
				continue;

			if (key_init (kt_p) != S_OKAY) return (db_status);

			TX_ASSERT(TIsValidAddress(data+offset, kt_p->kt_len, false));

			if (!nullcmp (data+offset, kt_p->kt_len))
			/* wenn alter Schlüssel nicht gleich Null */
				db_status = delete_key (dba, data+offset);
			
			if (db_status == S_NOTFOUND) {
				db_status = S_OKAY;
			} else if (db_status != S_OKAY) 
				return (db_status);

			TX_ASSERT(TIsValidAddress((char *)ptr+offset, kt_p->kt_len, false));

			if (!nullcmp ((char *)ptr+offset, kt_p->kt_len)) {
			/* wenn neuer Schlüssel nicht gleich Null */
				if (insert_key (dba, (char *)ptr+offset) != S_OKAY) 
					return (db_status);
			}
                        
			working_file = NONE;
		} while ((keyindex = kt_p->kt_chain) != NONE);
	}

/* Datensatz selbst wegschreiben */
	db_status = db_write (dba, ptr);

return (db_status);
}

/*
extern "C" long FUNCTYPE EXPORT01 zwrite_ (long *dba, void *ptr)
{
	return (long) z_writerec ((DB_ADDR *)dba, ptr);
}
*/
