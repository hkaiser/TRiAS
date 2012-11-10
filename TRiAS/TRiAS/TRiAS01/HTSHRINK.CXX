/* Zusammenfassen aller Eintraege einer Node                    */
/* File: HTSHRINK.C             last update: 28. Juli 1989      */

#include "trias01p.hxx"
 
int FUNCTYPE ht_shrink (register HTSLOT *data, short level)
{
NODE FAR *nd;
PAGE_NO node;
HTSLOT *dat, noddat;
register unsigned short cnt;
register short i;
 
/* alle Eintraege des HTree-Nodes umkopieren, und slots freigeben */
	for (i = 0, cnt = 0; i < HDIM; ++i) {
		node = -data->records[i];
		if (node) {
		register unsigned short j;
		short k;
                
			dio_get (node, &nd);
			for (j = 0; j < data->filled[i]; ++j) {
				t_locate_slot ((INT FAR *)(nd->nd_slots+j*slot_len),
					       (INT FAR *)buf, (short)(cnt+j), (short *)&k);
				t_put_inline ((char FAR *)(nd->nd_slots+j*slot_len),
					      (char FAR *)buf, (short)(cnt+j), (short)k);
			}
			cnt += data->filled[i];
			db_pzfree (keyfile, node);
		}
		data->records[i] = 0;
		data->filled[i] = 0;
		tdb_write (&treedba, (char FAR *)data);
	}
	db_pzfree (htfile, cubparent[level]);
 
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
 
/* ueberpruefen, ob weitere Komprimierung notwendig ist */
	if (level > 1) {
		data = &noddat;
		for (i = 0, cnt = 0; i < HDIM; ++i) {
			if (data->records[i] > 0) break;
			if ((cnt += data->filled[i]) > HTSLOTS) break;
		}
		if (i == HDIM) return (ht_shrink (data, level-1));
	}
 
return (db_status = S_OKAY);
}
 
