/* Loeschen eines Key's, wenn er existiert                      */
/* File: KEYDEL.C               last update: 6. Juni 1989       */

#include "trias01p.hxx"

int FUNCTYPE key_del (register int keyindex, void *key_val, register DB_ADDR *db_ad)
{
	/* Setzen der default-Werte aus der File-Tabelle und Key-Tabelle */
	if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
	
	/* Bilden des vollstaendigen Schluesseleintrages */
	key_cat (key_val, &db_ad->rec_no);
	
	kdel (ROOT_ADDR, (char *)&key, 0);
	find_field = NONE;
	working_file = NONE;
	
	return (db_status);
}
