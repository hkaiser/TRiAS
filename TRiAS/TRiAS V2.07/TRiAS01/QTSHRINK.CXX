/* Zusammenfassen aller Eintraege einer Node des QTree          */
/* File: QTSHRINK.C             last update: 11. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE qt_shrink (register QTSLOT *data, short level)
{
NODE *nd;
PAGE_NO node;
QTSLOT *dat, noddat;
unsigned short cnt = 0;
 
/* alle Eintraege des QTree-Nodes umkopieren, und slots freigeben */
	for (short i = 0; i < QDIM; ++i) {
		node = -data->records[i];
		if (node) {
		short k;
                
			dio_get (node, &nd);
			for (unsigned short j = 0; j < data->filled[i]; ++j) {
				t_locate_slot ((INT *)(nd->nd_slots+j*slot_len),
							   (INT *)buf, (short)(cnt+j), (short *)&k);
				t_put_inline ((char *)(nd->nd_slots+j*slot_len),
							  (char *)buf, (short)(cnt+j), (short)k);
			}
			cnt += data->filled[i];
			db_pzfree (keyfile, node, treedba.db_no);
		}
		data->records[i] = 0;
		data->filled[i] = 0;
		tdb_write (&treedba, (char *)data);
	}
	db_pzfree (qtfile, cubparent[level], treedba.db_no);
 
/* neuen Keyfile-Node anfordern */
	if (db_pzalloc (keyfile, &node) != S_OKAY) return (db_status);
	if (dio_get (node, (NODE FAR **)&nd) != S_OKAY) return (db_status);
	memcpy (nd->nd_slots, buf, cnt*slot_len);
	dio_touch (node);
 
/* neuen Node in HTree eintragen */
	treedba.rec_no = cubparent[level-1];
	tdb_read (&treedba, (void **)&dat);
	(data = dat)->records[cubslots[level-1]] = -node;
	data->filled[cubslots[level-1]] = (unsigned char)cnt;
	noddat = *data;
	tdb_write (&treedba, NULL);
 
/* Überpruefen, ob weitere Komprimierung notwendig ist */
	if (level > 1) {
		data = &noddat;
		for (i = 0, cnt = 0; i < QDIM; ++i) {
			if (data->records[i] > 0) break;
			if ((cnt += data->filled[i]) > QTSLOTS) break;
		}
		if (i == QDIM) return (qt_shrink (data, level-1));
	}
 
return (db_status = S_OKAY);
}
 
