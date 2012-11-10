/* Datenbank - I/O Funktionen unterste Ebene                            */
/* Eroffnen eines Files                                                 */
/* File: FDBOPEN.C              last update: 1. Maerz 1990              */

#include "trias01p.hxx"
 
#ifdef STATISTICS
extern int open_cnt;
extern int statistics;
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif
 
/* Eroeffnen eines Datenbankfiles mit der logischen Nummer `fno' */
int FUNCTYPE file_open (register FILE_ENTRY *ft_p)
{
	if (ft_p->ft_access == O_NOACC)
		return (dberr (S_ACCESS, FILE_OPEN));

#if defined(SINGLEFILE) && defined(MSWIND)
// Unter Windows ist die dynamischer Zuteilung von Dateideskriptoren
// nicht notwendig, da jeweils nur eine Datei geöffnet ist. Zwischen
// den Messages sind alle Dateien geschlossen.
	if (ft_p->ft_status == TO_INIT) {
	// erstes öffnen
	    if ((ft_p->ft_desc = OpenFile (ft_p->ft_name,
				       &ft_p->of,
				       ft_p->ft_access)) < 0)
		return (db_error (S_NOFILE, FILE_OPEN));
	} else if (ft_p->ft_status == CLOSED) {
	    if ((ft_p->ft_desc = OpenFile (ft_p->ft_name,
					 &ft_p->of,
					 ft_p->ft_access | OF_REOPEN)) < 0)
		return (db_error (S_NOFILE, FILE_OPEN));
	}
	ft_p->ft_used = TRUE;
#ifdef STATISTICS
	if (statistics) ++open_cnt;
#endif
	ft_p->ft_status = OPEN;

#else  // SINGLEFILE && MSWIND
// Im normalen Betrieb ist die maximal	mögliche Anzahl von eröffneten
// Dateien vorgegeben. Es muß also gegebenenfalls eine andere Datei
// geschlossen werden, bevor die gewünschte Datei eröffnet werden kann.

        if (ft_p->ft_status == CLOSED || ft_p -> ft_status == TO_INIT) {
	/* File ist 'closed' */
	register FILE_ENTRY FAR *dft_p;
	register int i;

		if (cnt_open_files == max_open_files) {
                register DBASE *db_p;
                register int size;
                /* Kein Filetabelleneintrag mehr frei 
                   --> finden und abschliessen des am laengsten 
                       nicht genutzten Files */
#ifndef MULTI_DB
                        size = size_ft;
#else
                int j;
                
                        for (j = last_db;; j = (j + 1) % MAXDB) {
                        /* fuer alle DB */
                        	if ((db_p = &db_table[j])->db_sft == 0) 
                        	/* anderes Leerkriterium als in dbopen !! */
                                	continue;
                        	size = db_p->db_sft;
#endif                  
				i = db_p->last_file;
                        	do {
#ifdef MULTI_DB
					dft_p = &db_p->db_ftab[i];
#else  // MULTI_DB
                                	dft_p = &file_table[i];
#endif // MULTI_DB
                                	i = (i + 1) % size;     /* naechste Datei */
                                	if (dft_p->ft_access == O_NOACC ||
                                	    dft_p->ft_used || 
					    dft_p->ft_status == TO_INIT ||
                               		    dft_p->ft_status == CLOSED) {
                                    		dft_p->ft_used = FALSE;
                                        	continue;
                                	} else {
                                        	db_p->last_file = i;
#ifdef MULTI_DB
	                                        if (i) last_db = j;
	                                        else last_db = (j + 1) % MAXDB;
#endif                                  
	                                        file_close (dft_p);
	                                        goto found_slot; /* raus aus for(j) */
        	                        }
                        	} while (i != db_p->last_file); /* max. 1 Runde */
#ifdef MULTI_DB
			}	/* for (j) */
#endif
found_slot:             ;
                }

#if defined(MSWIND)
		if (ft_p->ft_status == TO_INIT) {
		// erstes öffnen
	    		if ((ft_p->ft_desc = OpenFile (ft_p->ft_name,
						       &ft_p->of,
						       ft_p->ft_access)) < 0)
			{
				return (db_error (S_NOFILE, FILE_OPEN));
			}
		} else if (ft_p->ft_status == CLOSED) {
			if ((ft_p->ft_desc = OpenFile (ft_p->ft_name,
						       &ft_p->of,
						       ft_p->ft_access | OF_REOPEN)) < 0)
			{
				return (db_error (S_NOFILE, FILE_OPEN));
			}
		}
#else // MSWIND
                if((ft_p->ft_desc = open (ft_p->ft_name, ft_p->ft_access+O_BINARY)) < 0)
                        return (dberr (S_NOFILE, FILE_OPEN));
#endif // MSWIND

                ft_p->ft_used = TRUE;

#ifdef STATISTICS
                if (statistics) ++open_cnt;
#endif
                ft_p->ft_status = OPEN;
                ++cnt_open_files;
	}

#endif // SINGLEFILE
        
return (db_status = S_OKAY);
}

