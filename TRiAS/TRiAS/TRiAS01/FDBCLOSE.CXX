/* Datenbank I/O Funktionen -- Abschliessen eines Datenbankfiles		*/
/* File: FDBCLOSE.C 			last update: 26. September 1989 		*/

#include "trias01p.hxx"

#ifdef STATISTICS
extern int close_cnt;
extern int statistics;
#endif
 
/* Abschliesen des Datenbankfiles mit der Nummer `fno' */
int FUNCTYPE file_close (register FILE_ENTRY FAR *ft_p, BOOL fForceClosing, BOOL fCommit)
{
	if (ft_p->ft_access == O_NOACC) 
			return (dberr (S_ACCESS, FILE_CLOSE));

#if defined(MSWIND)
	if (ft_p->ft_pIStream != NULL) {
	// CompoundDocument
		if (fCommit) {
		HRESULT hr = ft_p -> ft_pIStream -> Commit (STGC_DEFAULT);

			if (FAILED(hr))
				return db_error (S_STG_FLUSHERROR, FILE_CLOSE, hr);
		}
			
		if (fForceClosing) {
			ft_p -> ft_pIStream -> Release();
			ft_p -> ft_pIStream = NULL;
		}
		return (db_status = S_OKAY);
	}
#endif // MSWIND

	if (ft_p->ft_status == OPEN) {
#if defined(MSWIND)
		_lclose (ft_p -> ft_desc);
#else
		close (ft_p->ft_desc);
#endif // MSWIND
#ifdef STATISTICS
		if (statistics) ++close_cnt;
#endif // STATISTICS
		ft_p->ft_status = CLOSED;
		ft_p->ft_desc = -1;
		--cnt_open_files;
	}
 	return (db_status = S_OKAY);
}
 
