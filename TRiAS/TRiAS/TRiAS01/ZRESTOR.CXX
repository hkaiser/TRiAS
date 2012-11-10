/* Wiederherstellen des Standes bei vorhergehendem 'z_touch'    */
/* File: ZRESTOR.C                                              */

#include "trias01p.hxx"

#include <dbversio.h>
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" int FUNCTYPE EXPORT01 z_restore (HPROJECT hPr)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

register int i;
register FILE_ENTRY *bf_p;
INT *nd;
char copyright[COPYRIGHT_LEN+1];
time_t time_val;
#if !defined(MSWIND)
unsigned int num;
#endif
int RC;

#ifndef MULTI_DB
        if (!dbopen) return (db_error (S_DBOPEN, ZTOUCH));
#else
register DBASE *db_p; 
DBASE *old_slot;
short db_slot = (short)hPr -1;

	TX_ASSERT(db_slot >= 0 && db_slot < MAXDB);
//	if (db_slot < 0 || db_slot >= MAXDB) return (db_error (S_DBOPEN, ZRESTORE));
        
	if ((db_p = &db_table[db_slot])->db_name == NULL && db_p -> db_pIStorage == NULL) 
                return S_OKAY;		// temporäre Datenbank

        old_slot = activate (db_p);
#endif
        if (backup_flag < 0) return S_OKAY;

// Einlesen der alten pz_table aus der Backupdatei
        bf_p = &file_table[backup_flag];
        DBASSERT (file_open (bf_p));
#if defined(MSWIND)
        _lread (bf_p->ft_desc, copyright, COPYRIGHT_LEN);
        _llseek (bf_p->ft_desc, (long)sizeof(PGZERO), 1);
	_lread (bf_p->ft_desc, pgzero, size_ft*sizeof(PGZERO));

#else
        _dos_read (bf_p->ft_desc, copyright, COPYRIGHT_LEN, &num);
        lseek (bf_p->ft_desc, (long)sizeof(PGZERO), 1);
	_dos_read (bf_p->ft_desc, pgzero, size_ft*sizeof(PGZERO), &num);
#endif
	DBASSERT (file_close (bf_p));

// Merken der Zeit
        time_val = pgzero[backup_flag].bdate;
 
        nd = (INT *)(backup_page->buff);
 
// Verteilen der Pages aus der Backupdatei auf die DB-Dateien
        for (i = 1; TRUE; ++i) {
	register FILE_ENTRY *ft_p;
	INT page_no;
	INT file_no;
 
		DBASSERT (file_open (bf_p));
#if defined(MSWIND)
		_llseek (bf_p->ft_desc, (long)i*PageSize, 0);
		if (_lread (bf_p->ft_desc, nd, PageSize) < PageSize) {
#else
		lseek (bf_p->ft_desc, (long)i*PageSize, 0);
                if (_dos_read (bf_p->ft_desc, nd, PageSize, &num) != 0) {
#endif
			DBASSERT (file_close (bf_p));
			break;		// Fehler: abbrechen
		}
		DBASSERT (file_close (bf_p));

                file_no = nd[0] / MAXPAGES;     /* Dateinummer */
                page_no = nd[0] % MAXPAGES;     /* Pagenummer */
                nd[0] = (INT)time_val;

                ft_p = &file_table[file_no];
                DBASSERT (file_open (ft_p));
#if defined(MSWIND)
		_llseek (ft_p -> ft_desc, (long)(page_no*PageSize), 0);
                _lwrite (ft_p -> ft_desc, (LPCSTR)nd, PAGESIZE);
#else
                lseek (ft_p -> ft_desc, (long)(page_no*PageSize), 0);
                _dos_write (ft_p -> ft_desc, nd, PageSize, &num);
#endif
		DBASSERT (file_close (ft_p));
        }
 
// zurückschreiben der pgzero Einträge in die Dateien
	for (i = 0; i < size_ft; i++) {
	FILE_ENTRY *ft_p;

                ft_p = &file_table[i];
                DBASSERT (file_open (ft_p));
#if defined(MSWIND)
		_llseek (ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
                _lwrite (ft_p->ft_desc, (LPCSTR)&pgzero[i], sizeof(pgzero));
#else
                lseek (ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
                _dos_write (ft_p->ft_desc, &pgzero[i], sizeof(pgzero), &num);
#endif
		DBASSERT (file_close (ft_p));
	}

// Backupdatei neu generieren
	DBASSERT (gen_backup (bf_p, pgzero, copyright, time_val));

// vorhergehende DB wieder aktivieren
        if (old_slot != db_p) activate (old_slot);

return (db_status = S_OKAY);
}

