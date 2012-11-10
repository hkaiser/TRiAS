/* Zusammenfassen einer Key-Node                                */
/* File: SHRINK.C               last update: 6. Juni 1989       */

#include "trias01p.hxx"

int FUNCTYPE shrink (PAGE_NO nod, short i, short level)
{
	register NODE FAR *nd;
	NODE FAR *nd1;
        PAGE_NO next, prev;
        short filled;
        short slot;
 
        if (dio_get (nod, &nd1) != S_OKAY) return (db_status);
        nd = nd1;
 
        /* entfernen des slots i aus dem Puffer 'buf' */
        zap_slot (nd->nd_slots, i, nd->nd_filled);
        filled = --nd->nd_filled;
        dio_touch (nod);
 
        if (level == 0) return (db_status = S_OKAY);
 
        /* berechnen der PAGE_NO der Nachbarn und der REC_NO des
           uebergeordneten Slots */
        slot = parent_slot (level, nod, &next, &prev);
 
        if (filled < d/2) {
                /* testen des rechten Nachbarn */
                if (next != NONE) {
                        if (dio_get (next, &nd1) != S_OKAY)
                                return(db_status);
                        if (nd1->nd_filled < d/2)
                                return (combine (nod, next, slot, level));
                        else
                                return (overflow (nod, next, NULL, slot, level));
                }
                /* testen des linken Nachbarn */
                else if (prev != NONE) {
                        if (dio_get (prev, &nd1) != S_OKAY)
                                return (db_status);
                        if (nd1->nd_filled < d/2)
                                return (combine (prev, nod, slot-1, level));
                        else
                                return (overflow (prev, nod, NULL, slot-1, level));
                }
                /* das darf nicht passieren */
                else {
                        return (dberr (S_SYSERR, SHRINK));
                }
        }
 
return (db_status = S_OKAY);
}
 
 
