/* Berechnen der Nummern der uebergeordneten und benachbarten Nodes     */
/* File: PARENT.C               last update: 30. Mai 1989               */

#include "trias01p.hxx"
 
int FUNCTYPE parent_slot (short level, PAGE_NO nod, 
			  register PAGE_NO *next, PAGE_NO *prev)
{
register short slot;
register NODE *nd;
NODE *nd1;
 
        if (level == 0) {
                *next = NONE;
                *prev = NONE;
                return (-1);
        }
 
        slot = 0;
        if (dio_get (parent[level-1], &nd1) != S_OKAY)
                return (db_status);
        nd = nd1;
 
	while (*(PAGE_NO FAR *)(nd->nd_slots+slot*slot_len) != nod)
	{
                ++slot;
	}
 
        if (slot > nd->nd_filled) 
        /* hier stimmt was nicht */
                return (dberr (S_SYSERR, PARENT));
 
        if (slot > 0)
		*prev = *(PAGE_NO FAR *)(nd->nd_slots+(slot-1)*slot_len);
        else *prev = NONE;
 
        if (slot < nd->nd_filled)
		*next = *(PAGE_NO FAR *)(nd->nd_slots+(slot+1)*slot_len);
        else *next = NONE;
 
return (slot);
}
 
