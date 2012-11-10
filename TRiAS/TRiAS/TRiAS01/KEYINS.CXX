/* Key in Suchbaum einfuegen                                    */
/* File: KEYINS.C               last update: 29. Mai 1989       */

#include "trias01p.hxx"

/* Einfuegen eines Schluesseleintrages in eine B*-Suchbaum */
int FUNCTYPE key_ins (register int keyindex, void *key_val, register DB_ADDR *db_ad)
{
	/* Setzen der default-Werte aus der File-Tabelle und Key-Tabelle */
	if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
	
	/* Bilden des vollstaendigen Schluesseleintrages */
	key_cat (key_val, &db_ad->rec_no);
	
	/* Einfuegen des Key's in den Suchbaum */
	ins (ROOT_ADDR, (char *)&key, 0);
	find_field = NONE;
	working_file = NONE;
	
	return (db_status);
}


