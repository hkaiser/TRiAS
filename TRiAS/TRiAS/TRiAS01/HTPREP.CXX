/* Einfuegen/Loeschen  einer Geometrieinfo in den HTree         */
/* File: HTPREP.C               last update: 21. September 1989 */

#include "trias01p.hxx"

#ifdef vax 
#ifdef unix
#define z8000
#endif 
#endif

#ifndef z8000
static HYPERCUBE NEAR root = { 0L, 0L, 0L, 0L, MAXKOORD };
#endif
 
/* Einfuegen einer Geometrieinformation */
int FUNCTYPE ht_insert (CONTAINER FAR *w_key, DB_ADDR *db_addr) 
{
// Testen, ob Koordinaten innerhalb der gültigen Grenzen liegen
	ASSERTKOORD(w_key->x_min, HTINS);
	ASSERTKOORD(w_key->x_max, HTINS);
	ASSERTKOORD(w_key->y_min, HTINS);
	ASSERTKOORD(w_key->y_max, HTINS);	

// Schlüssel einspeichern
	htaction = (HTACTIONPROC)ht_ins;
	return (htprep (w_key, db_addr));
}
 
/* Loeschen einer Geometrieinformation */
int FUNCTYPE ht_delete (CONTAINER FAR *w_key, DB_ADDR *db_addr) 
{
// Testen, ob Koordinaten innerhalb der gültigen Grenzen liegen
	ASSERTKOORD(w_key->x_min, HTDEL);
	ASSERTKOORD(w_key->x_max, HTDEL);
	ASSERTKOORD(w_key->y_min, HTDEL);
	ASSERTKOORD(w_key->y_max, HTDEL);	

// Schlüssel herauslöschen
	htaction = (HTACTIONPROC)ht_del;
	return (htprep (w_key, db_addr));
}


int FUNCTYPE htprep (register CONTAINER *w_key, register DB_ADDR *db_addr)
{
register short key_index;
HYPERCUBE roothc;
 
#ifdef z8000
	roothc.w.hc_w = roothc.w.hc_x = roothc.w.hc_y = roothc.w.hc_z = 0L;
	roothc.w.hc_len = MAXKOORD;
#else
	roothc = root;
#endif
/* Setzen der default-Werte fuer Schluesselzugriff */
    if ((key_index = record_table[db_addr->file_no].rt_keyfile) < 0) 
		return (dberr (S_NOKEY, HTPREP));
	if (key_init (key_table + key_index) != S_OKAY)
		return (db_status);
    if ((treedba.file_no = htfile) < 0)
		return (dberr (S_NOKEY, HTPREP));
	
	treedba.db_no = 0;		// auf aktives Projekt setzen lassen 
	
    *(CONTAINER *)(GeoKey.ks_key) = *w_key;
    GeoKey.ks_rec_no = db_addr->rec_no + db_addr->file_no * MAXHTREC;

/* ab in den Baum */
    if (htsearch (ROOT_ADDR, &roothc, 0) != S_OKAY) {
		working_file = NONE;
		return (db_status);
	}
    working_file = NONE;
 	return (db_status = S_OKAY);
}
