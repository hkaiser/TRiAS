/* Herausloesen eines Punktes aus dem QTree                     */
/* File: QTDEL.C                last update: 11. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE qt_del (REC_NO node, QUADRANT *qd, register QTSLOT *data, short level)
{
	NODE *nd;
	unsigned short cnt;
	short i;
	register short slot = cubslots[level];
	register short filled = data->filled[slot];
	
	if (node == 0) return (db_error (S_NOTFOUND, QTDEL));
	
	/* Page aus Keyfile einlesen */
	if (dio_get (node, (NODE FAR **)&nd) != S_OKAY) return (db_status);
	
	/* Schluesseleintrag suchen */
	switch (t_locate_slot ((INT *)&GeoKey, (INT *)nd->nd_slots, filled, &i)) {
	case 0: /* nicht gefunden */
		return (db_error (S_NOTFOUND, QTDEL));
	case 2:
		if (unique) return (db_error (S_DUPLICATE, QTDEL));
		return (db_error (S_NOTFOUND, QTDEL));
	case 1: /* gefunden */
		break;
	}
	/* Schluessel loeschen */
	zap_slot (nd->nd_slots, i, filled);
	dio_touch (node);
	if ((data->filled[slot] = (unsigned char)--filled) == 0) {
        /* Page jetzt leer, entfernen aus QTree */
		data->records[slot] = 0;
		tdb_write(&treedba, (char *)data);
		db_pzfree (keyfile, node, treedba.db_no);
	} else
		tdb_write(&treedba, (char *)data);
	
	if (level > 0) {
		for (i = 0, cnt = 0; i < QDIM; ++i) {
			/* zaehlen der Eintraege in der Node */
			if (data->records[i] > 0) break;
			if ((cnt += data->filled[i]) > QTSLOTS) break;
		}
		if (i == QDIM) {
			/* Node komprimieren */
			if (qt_shrink (data, level) != S_OKAY)
				return (db_status);
			else return (S_DUMMY);
		}
	}
	
	return (db_status = S_OKAY);
}




