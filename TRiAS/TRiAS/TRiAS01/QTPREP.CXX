/* Einfuegen/Loeschen  einer Geometrieinfo in den QTree         */
/* File: QTPREP.C               last update: 11. Oktober 1989   */

#include "trias01p.hxx"

#ifdef vax
#ifdef unix
#define z8000
#endif
#endif

#ifndef z8000
static QUADRANT NEAR root = { 0L, 0L, MAXKOORD };
#endif
 
/* Einfuegen einer Geometrieinformation */
int FUNCTYPE qt_insert (QTPOINT FAR *w_key, DB_ADDR *db_addr) 
{
// Testen, ob Koordinaten innerhalb der gültigen Grenzen liegen
	ASSERTKOORD(w_key->x_min, QTINS);
	ASSERTKOORD(w_key->y_min, QTINS);

// Einspeichern des Schlüssels
	qtaction = qt_ins;
        return (qtprep (w_key, db_addr));
}
 
/* Loeschen einer Geometrieinformation */
int FUNCTYPE qt_delete (QTPOINT FAR *w_key, DB_ADDR *db_addr) 
{
// Testen, ob Koordinaten innerhalb der gültigen Grenzen liegen
	ASSERTKOORD(w_key->x_min, QTDEL);
	ASSERTKOORD(w_key->y_min, QTDEL);

// Löschen des Schlüssels
	qtaction = qt_del;
        return (qtprep (w_key, db_addr));
}

/* Vorbereiten einer HTree-Operation */
int FUNCTYPE qtprep (register QTPOINT *w_key, register DB_ADDR *db_addr)
{
register short key_index;
QUADRANT rootqd;
 
#ifdef z8000
        rootqd.w.qd_x = rootqd.w.qd_y = 0L;
        rootqd.w.qd_len = MAXKOORD;
#else
        rootqd = root;
#endif
	/* Setzen der default-Werte fuer Schluesselzugriff */
        if ((key_index = record_table[db_addr->file_no].rt_keyfile) < 0) {
                return (dberr (S_NOKEY, QTPREP));
        }
        if (key_init (key_table + key_index) != S_OKAY)
                return (db_status);
        if ((treedba.file_no = qtfile) < 0)
                return (dberr (S_NOKEY, QTPREP));
 
	treedba.db_no = 0;		// auf aktives Projekt setzen lassen 

        *(QTPOINT *)(GeoKey.ks_key) = *w_key;
        GeoKey.ks_rec_no = db_addr->rec_no + db_addr->file_no * MAXQTREC;
        /* ab in den Baum */
        if (qtsearch (ROOT_ADDR, &rootqd, 0) != S_OKAY) {
		working_file = NONE;
		return (db_status);
	}
        working_file = NONE;
 
return (db_status = S_OKAY);
}
