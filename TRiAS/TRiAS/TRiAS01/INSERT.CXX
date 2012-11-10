/* Einfuegen eines Schluesseleintrages in den B*-Suchbaum       */
/* File: INSERT.C               last update: 6. Juni 1989       */

#include "trias01p.hxx"

int FUNCTYPE ins (PAGE_NO nod, register void *key, register short level)
{
	register NODE *nd;
	NODE *nd1;
	short i; 
	
// auf zu tiefe Verschachtelung achten
	if (level >= MAXLEVEL)
		return db_error (S_SYSERR, INSERT_BT);

	/* fuehren der Pfadliste */
	parent[level] = nod;
	
	/* Lesen der entsprechenden Page */
	if (dio_get (nod, (NODE FAR **)&nd1) != S_OKAY) return (db_status);
	
	/* wenn der Child-Pointer `NONE' ist, dann ist das ein Blattnode
	und der Node muss erweitert werden, um den gegebenen Key
	aufnehmen zu koennen */
	if (*(REC_NO *)((nd = nd1)->nd_slots) == NONE) {
        /* Blattnode  (leaf) */
		return (NodeExpand (nod, key, level));
	} else {        
        /* interner Node --> ins child-node einfuegen */
		switch (locate_slot ((INT *)key, (INT *)nd->nd_slots, nd->nd_filled, &i)) {
		case 2:
			if (unique) 
				return (db_error (S_DUPLICATE, INSERT_BT));
			/* hier soll man durchfallen */
		case 0:
			return (ins (*(PAGE_NO *)(nd->nd_slots+i*slot_len), key, level+1));
			
		case 1:
			return (db_status = S_OKAY);
		}
	}
	return db_status = S_OKAY;
}

