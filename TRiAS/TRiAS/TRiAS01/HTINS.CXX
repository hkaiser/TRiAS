/* Einfuegen eines Containers in den HTree                      */
/* File: HTINS.C                last update: 24. Juli 1989      */

#include "trias01p.hxx"

int FUNCTYPE ht_ins (REC_NO node, HYPERCUBE *hc, register HTSLOT *data, short level)
{
NODE *nd;
register short slot = cubslots[level];
register short filled = data->filled[slot];
short i;
	
	if (node == 0) {
		if (db_pzalloc (keyfile, &node) != S_OKAY) 
			return (db_status);
		data->records[slot] = -node;
		tdb_write (&treedba, NULL);
	}
	if (dio_get (node, (struct node **)&nd) != S_OKAY) 
		return (db_status);
	
	switch (t_locate_slot (&GeoKey, nd->nd_slots, filled, &i)) {
	case 1:
		return (db_status = S_OKAY);
	case 2:
		if (unique) return (db_error (S_DUPLICATE, HTINS));
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
		t_put_inline ((char *)&GeoKey, (char *)buf, d, i);
		if (db_pzfree (keyfile, node) != S_OKAY) 
			return (db_status);
		data->filled[slot] = 0;
		if (ht_split (hc, level) != S_OKAY) 
			return (db_status);
		return (S_DUMMY);
	}
}
