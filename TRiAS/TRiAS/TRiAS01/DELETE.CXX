/* Loeschen der gegebenen Node aus dem B*-Suchbaum              */
/* File: DELETE.C               last update: 6. Juni 1989       */

#include "trias01p.hxx"

int FUNCTYPE kdel (PAGE_NO nod, register void *key, register short level)
{
register NODE *nd;
NODE *nd1;
PAGE_NO ch;
short i;
 
        /* fuehren der Pfadliste */
        parent[level] = nod;
 
        /* Lesen der entsprechenden Page */
        if (dio_get (nod, &nd1) != S_OKAY) return( db_status );
        nd = nd1;
 
	if (locate_slot ((INT FAR *)key, (INT FAR *)nd->nd_slots, nd->nd_filled, &i) == 1) {
        /* `key' ist in diesem Niveau enthalten: ersetzen dieses Keys
           durch den am weitesten links liegenden Key des rechten 
           Subtrees */
		ch = *(PAGE_NO FAR *)(nd->nd_slots+(i+1)*slot_len);
                if (ch != NONE) {
                        do {
                                dio_get (ch, &nd1);
                                parent[++level] = ch;
				ch = *(PAGE_NO FAR *)(nd1->nd_slots);
                        } while (ch != NONE);
			memcpy (buf, &((KEY_SLOT FAR *)(nd1->nd_slots))->ks_rec_no,
                                                slot_len-sizeof(REC_NO));

	// erst diesen Node Shrinken und dann Schlssel oben einkopieren
//			shrink (parent[level], 0, level);

                        if (dio_get (nod, &nd1) != S_OKAY) return (db_status);
			memcpy (&((KEY_SLOT FAR *)(nd1->nd_slots+i*slot_len))->ks_rec_no,
                                                buf, slot_len-sizeof(REC_NO));

			dio_touch (nod);
			return (shrink (parent[level], 0, level));
                }
                else return (shrink (nod, i, level));
        }
        else {
		ch = *(PAGE_NO FAR *)(nd->nd_slots+i*slot_len);
                if (ch != NONE) return (kdel (ch, key, level+1));
                else return (db_error (S_NOTFOUND, DELETE_BT));
        }
}
 
 
 
