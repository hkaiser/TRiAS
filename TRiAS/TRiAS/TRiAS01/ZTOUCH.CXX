/* Bestaetigen der letzten DB-Aenderungen                       */
/* File: ZTOUCH.C                                               */

#include "trias01p.hxx"

#include "syncdb.hxx"

#define NOCOPYRIGHT
#include <dbversio.h>
 
PGZERO *old_pztable;

extern "C" int FUNCTYPE EXPORT01 z_touch (HPROJECT hPr) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

register int i;
register FILE_ENTRY *bf_p;
time_t time_val;
char copyright[COPYRIGHT_LEN+1];
#if !defined(MSWIND) 
unsigned int num;
#endif

#ifndef MULTI_DB
	if (backup_flag < 0) return S_OKAY;
        if (!dbopen) return (db_error (S_DBOPEN, ZTOUCH));
#else
register DBASE *db_p; 
short db_slot = (short)hPr -1;
DBASE *old_slot;

	if (backup_flag < 0) return S_OKAY;
        if (db_slot < 0 || db_slot >= MAXDB) return (db_error (S_DBOPEN, ZTOUCH));
        if ((db_p = &db_table[db_slot])->db_name == NULL && db_p -> db_pIStorage == NULL) 
                return (db_status);

        old_slot = activate (db_p);
#endif

/* alte Pagezero-Tabelle einlesen */
	old_pztable = (PGZERO *)new PGZERO [size_ft];
        if (old_pztable == NULL) return (db_error (S_NOMEMORY, ZTOUCH));

        bf_p = &file_table[backup_flag];
        if (file_open (bf_p) != S_OKAY) {
		delete [] old_pztable;
		return (db_status);
	}
#if defined(MSWIND)
	_lread (bf_p -> ft_desc, copyright, COPYRIGHT_LEN);
	_llseek (bf_p -> ft_desc, sizeof(PGZERO), 1);
        _lread (bf_p -> ft_desc, &old_pztable[0], size_ft*sizeof(PGZERO));
#else
	_dos_read (bf_p -> ft_desc, copyright, COPYRIGHT_LEN, &num);
        lseek (bf_p -> ft_desc, sizeof(PGZERO), 1);
        _dos_read (bf_p -> ft_desc, &old_pztable[0], size_ft*sizeof(PGZERO), &num);
#endif

        if (file_close (bf_p) != S_OKAY) {
		delete [] old_pztable;
		return (db_status);
	}
 
// DB-Dateien aktualisieren
        time (&time_val);               /* backup time */
        for (i = 0; i < size_ft; ++i) {
	INT old_page, new_page, j;
	register FILE_ENTRY *ft_p;
 
                pgzero[i].bdate = time_val;     /* Zeit setzen */
                if (i == backup_flag) continue;

	// alle Pages anfassen, die neu sind (new_pages)
                if (file_table[i].ft_type == KEYFILE) {
                        old_page = old_pztable[i].pz_next;
                        new_page = pgzero[i].pz_next;
                } else {
                        old_page = (old_pztable[i].pz_next-1)/file_table[i].ft_slots;
                        new_page = (pgzero[i].pz_next-1)/file_table[i].ft_slots;
                }

                if (old_page >= new_page) continue;

                ft_p = &file_table[i];
                if (file_open (ft_p) != S_OKAY) {
			delete [] old_pztable;
			return (db_status);
		}
                
	// neue Pages dazugekommen
                for (j = old_page+1; j <= new_page; ++j) {
#if defined(MSWIND)
			_llseek (ft_p->ft_desc, (long)((j+1)*PageSize), 0);
			_lwrite (ft_p -> ft_desc, (LPCSTR)&time_val, sizeof(INT));
#else
			lseek (ft_p->ft_desc, (long)((j+1)*PageSize), 0);
                        write (ft_p->ft_desc, &time_val, sizeof(INT));
#endif
                }
        	if (file_close (ft_p) != S_OKAY) {
			delete [] old_pztable;
			return (db_status);
		}
        }

// Speicher freigeben
	delete [] old_pztable;

// Backupdatei neu generieren
	if (gen_backup (bf_p, pgzero, copyright, time_val))
		return db_status;

// vorhergehemde DB wieder aktivieren
        if (old_slot != db_p) activate (old_slot);

return (db_status = S_OKAY);
}
