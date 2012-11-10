/* Generieren einer neuen Backupdatei                           */
/* File: GENBACK.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

#define NOCOPYRIGHT
#include <dbversio.h>

#if defined(MSWIND)
#define close(fh)	_lclose(fh)
#endif

/* Backupdatei neu generieren */
extern "C" int FUNCTYPE EXPORT01 gen_backup (FILE_ENTRY *bf_p, PGZERO *pz_p, 
					     char *copyright, unsigned long time_val)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

register int fh;
register int i;
unsigned short ui;
#ifdef MSWIND
OFSTRUCT of;
#else
unsigned int num;
#endif

	if (bf_p->ft_status == OPEN) 
		file_close (bf_p, true, false);
#ifdef MSWIND
	if ((fh = OpenFile (bf_p->ft_name, &of, OF_CREATE|OF_READWRITE)) == -1)
#else  // MSWIND
	unlink (bf_p->ft_name);
	if ((fh = open (bf_p->ft_name, O_RDWR)) < 0)
#endif // MSWIND
		return (db_error (S_BACKUP, GEN_BACKUP));

	_dos_write (fh, copyright, COPYRIGHT_LEN, &num);

// pgzero wegschreiben und Zeitstempel aufdruecken
	pz_p[backup_flag].bdate = time_val;
	_dos_write (fh, (LPCSTR)&pz_p[backup_flag], sizeof(PGZERO), &num);
	for (i = 0; i < size_ft; ++i) {
		pz_p[i].bdate = time_val;
		_dos_write (fh, (LPCSTR)&pz_p[i], sizeof(PGZERO), &num);
	}
	for (ui = 0; ui < pActivatedDB->db_pagesize-((size_ft+1)*sizeof(PGZERO)+COPYRIGHT_LEN); ++ui)
		_dos_write (fh, "", 1, &num);	// Page mit '\0' ausfüllen
	close (fh);
 
return (db_status = S_OKAY);
}
