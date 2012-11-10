/* Aktivieren einer Datenbasis                                  */
/* File: ACTIVATE.C             last update: 28. Februar 1990   */

#include "trias01p.hxx"

#if defined(MULTI_DB)

extern "C" DBASE * FUNCTYPE activate (DBASE *new_db) 
{
DBASE *old_db = pActivatedDB;

	if (old_db != NULL) {
	// Parameter auf jeden Fall rückschreiben
		old_db->db_work = working_file;
		old_db->db_field = find_field;
		old_db->db_lvl = lvl;
		old_db->db_parent = parent;
		old_db->db_slots = slots;
	}

	if (pActivatedDB == new_db)	/* alte DB ist gleich neuer */
		return pActivatedDB;

	if (new_db == NULL) {
		pActivatedDB = NULL;          /* Keine DB aktiv */

		file_table = NULL;
		key_table = NULL;
		record_table = NULL;
		pgzero = NULL;
		slots = NULL;
		parent = NULL;
	} else {
	/* Aktivieren der neuen DB */   
		if (new_db->db_name == NULL && new_db->db_pIStorage == NULL) {
		/* neuer DB-slot ist leer */
			dberr (S_ACTIV, ACTIVATE);
			return (NULL);
		}
	/* neue aktive DB */
		pActivatedDB = new_db;

	// Speicheradressen der neuen DB
		file_table = new_db->db_ftab;
		key_table = new_db->db_ktab;
		record_table = new_db->db_rtab;
		pgzero = new_db->db_pztab;
		slots = new_db->db_slots;
		parent = new_db->db_parent;
		size_ft = new_db->db_sft;
		size_kt = new_db->db_skt;
		size_rt = new_db->db_srt;
		working_file = new_db->db_work;
		find_field = new_db->db_field;
		lvl = new_db->db_lvl;
		PageSize = new_db->db_pagesize;
#ifdef BACKUP
		backup_flag = new_db->db_bflag;
#endif
	}

return (old_db);
}

#endif // MULTI_DB
