/* Zusammenkopieren zweier Nodes in den buffer 'buf'            */
/* File: ASMBUF.C               last update: 30. Mai 1989       */

#include "trias01p.hxx"

int FUNCTYPE asm_buf (PAGE_NO left, PAGE_NO right, void *key, 
		      register short *nkeys, short slot, short level)
{
register short i;
short j, len;
register NODE *nd;
NODE *nd1;
 
        if (dio_get (left, &nd1) != S_OKAY)
                return (db_status);
 
        len = slot_len * (nd = nd1)->nd_filled + sizeof(INT);
        *nkeys = nd->nd_filled;
	memcpy ((char *)buf, nd->nd_slots, len);
 
        i = len;
        len = slot_len - sizeof(INT);
        if (dio_get (parent[level-1], &nd1) != S_OKAY)
                return (db_status);
	memcpy ((char *)buf+i, nd1->nd_slots+slot*slot_len+sizeof(INT), len);
        *nkeys += 1;
 
        if (dio_get (right, &nd1) != S_OKAY)
                return (db_status);
        i += len;
        len = slot_len * (nd = nd1)->nd_filled + sizeof(INT);
        *nkeys += nd->nd_filled;
	memcpy ((char *)buf+i, nd->nd_slots, len);
 
        if (key != NULL) {
		locate_slot (key, buf, *nkeys, &j);
                put_inline (key, buf, *nkeys, j);
                *nkeys += 1;
        }
 
return (db_status = S_OKAY);
}
 
