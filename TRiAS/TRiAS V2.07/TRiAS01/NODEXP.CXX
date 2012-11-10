/* Child node expandieren                                       */
/* File: NODEXP.C               last update: 6. Juni  1989      */

#include "trias01p.hxx"

int FUNCTYPE NodeExpand (PAGE_NO nod, void *key, register short level)
{
	short i, slot;
	register NODE FAR *nd;
	NODE *nd1, *nxt, *prv;
	PAGE_NO next, prev;
	
	if (dio_get (nod, &nd1) != S_OKAY)
		return (db_status);
	nd = nd1;
	switch (locate_slot ((INT FAR *)key, (INT FAR *)nd->nd_slots, nd->nd_filled, &i)) {
	case 1:
		return (db_status = S_OKAY);
	case 2:
		if (unique) return (db_error (S_DUPLICATE, EXPAND));
	case 0:
		break;
	}
	
	/* wenn aktueller Node voll ist, dann entweder ausgleichen
	zu benachbarten Nodes oder splitten */
	if (nd->nd_filled < d) {
        /* es ist noch Platz im Node */
		put_inline (key, nd->nd_slots, nd->nd_filled, i);
		nd->nd_filled++;
		dio_touch (nod);
	} else {
        /* Node ist voll */
		/* Berechnen der REC_NO im Parent-slot und der PAGE_NO der 
		benachbarten Child-Slots */
		if (level == 0) {
			/* Root-Node: splitten */
			dio_touch (nod);
			split_root (nd, (KEY_SLOT *)key, level);
		} else {
			/* wenn nicht root-Node */
			slot = parent_slot (level, nod, &next, &prev);
			if (next != NONE) {
				/* ist rechter Nachbar auch voll ? */
				if (dio_get (next, &nxt) != S_OKAY)
					return (db_status);
				if (nxt->nd_filled >= d-2)
					split_nodes (nod, next, key, slot, level);
				else overflow (nod, next, key, slot, level);
			} else if (prev != NONE) {
				/* wenn linker Nachbar existiert: ist er voll ? */
				if (dio_get (prev, &prv) != S_OKAY)
					return (db_status);
				if (prv->nd_filled >= d-2)
					split_nodes (prev, nod, key, slot-1, level);
				else overflow (prev, nod, key, slot-1, level);
			} else { /* hier stimmt was nicht */
				return (dberr (S_SYSERR, EXPAND));
			}
		}
	}
	
	return (db_status = S_OKAY);
}


