/* Einfuegen eines Punktes in den QTree                         */
/* File: QTINS.C                last update: 11. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE qt_ins (REC_NO node, QUADRANT *qd, register QTSLOT *data, short level)
{
NODE *nd;
register short slot = cubslots[level];
register short filled = data->filled[slot];
short int i;
 
    if (node == 0) {
		if (db_pzalloc (keyfile, &node) != S_OKAY) return (db_status);
		data->records[slot] = -node;
		tdb_write (&treedba, NULL);
    }
	if (dio_get (node, (NODE FAR **)&nd) != S_OKAY) return (db_status);
	switch (t_locate_slot ((INT *)&GeoKey, (INT *)nd->nd_slots, filled, &i)) {
        case 1:
                return (db_status = S_OKAY);
        case 2:
                if (unique) return (db_error (S_DUPLICATE, QTINS));
        case 0:
                break;
	}
	if (filled < d) {       /* Platz reicht aus */
		t_put_inline ((char *)&GeoKey, (char *)nd->nd_slots, filled, i);
		data->filled[slot] = (unsigned char)(filled +1);
		dio_touch (node);
		return (db_status = S_OKAY);
	} else {
		memcpy (buf, nd->nd_slots, slot_len*d);
		t_put_inline ((char *)&GeoKey, (char *)buf, (short)d, i);
		if (db_pzfree (keyfile, node) != S_OKAY) return (db_status);
		data->filled[slot] = 0;
		if (qt_split (qd, level) != S_OKAY) return (db_status);
		return (S_DUMMY);
	}
}
