/* Herausloesen eines Containers aus dem HTree                  */
/* File: HTDEL.C                last update: 28. Juli 1989      */

#include "trias01p.hxx"

int FUNCTYPE ht_del (REC_NO node, HYPERCUBE *hc, register HTSLOT *data, short level)
{
NODE FAR *nd;
unsigned short cnt;
short i;
register short slot = cubslots[level];
register short filled = data->filled[slot];
 
	if (node == 0) return (db_error (S_NOTFOUND, HTDEL));
 
/* Page aus Keyfile einlesen */
	if (dio_get (node, &nd) != S_OKAY) return (db_status);
 
/* Schluesseleintrag suchen */
	switch (t_locate_slot (&GeoKey, nd->nd_slots, filled, &i)) {
	case 0: /* nicht gefunden */
		return (db_error (S_NOTFOUND, HTDEL));
	
	case 2:
		if (unique) return (db_error (S_DUPLICATE, HTDEL));
		return (db_error (S_NOTFOUND, HTDEL));
	
	case 1: /* gefunden */
		break;
	}

/* Schlüssel löschen */
	t_zap_slot (nd->nd_slots, i, filled);
	dio_touch (node);
	if ((data->filled[slot] = (unsigned char)--filled) == 0) {
	/* Page jetzt leer, entfernen aus HTree */
		data->records[slot] = 0;
		tdb_write(&treedba, (char FAR *)data);
		db_pzfree (keyfile, node, treedba.db_no);
	} else
		tdb_write(&treedba, (char FAR *)data);
 
	if (level > 0) {
		for (i = 0, cnt = 0; i < HDIM; ++i) {
		/* zählen der Eintraege in der Node */
			if (data->records[i] > 0) break;
			if ((cnt += data->filled[i]) > HTSLOTS) break;
		}
		if (i == HDIM) {
		/* Node komprimieren */
			if (ht_shrink (data, level) != S_OKAY)
				return (db_status);
			else return (S_DUMMY);
		}
	}
 
return (db_status = S_OKAY);
}
 
 
 
 
