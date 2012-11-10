/* Aufteilen der slots auf zwei Nodes                           */
/* File: OVERFL.C               last update: 30. Mai 1989       */

#include "trias01p.hxx"

int FUNCTYPE overflow (PAGE_NO left, PAGE_NO right, void *key, short slot, short level)
{
register short i, len;
short nkeys, m, n;
register NODE *nd;
NODE *nd1;
 
/* Zusammenkopieren zweier Nodes in 'buffer' */
        asm_buf (left, right, key, &nkeys, slot, level);
 
/* Zurueckkopieren mit gleichzeitiger Aufteilung */
        m = nkeys / 2;
        n = nkeys - 1 - m;
        if (dio_get (right, &nd1) != S_OKAY)
                return (db_status);
        i = nkeys * slot_len + sizeof(INT);
        len = n * slot_len + sizeof(INT);
        i -= len;
	memcpy ((nd = nd1)->nd_slots, (char FAR *)buf+i, len);
        nd->nd_filled = n;
        dio_touch (right);
 
        len = slot_len - sizeof(INT);
        i -= len;
        if (dio_get (parent[level-1], &nd1) != S_OKAY)
                return (db_status);
	memcpy ((nd = nd1)->nd_slots+slot*slot_len+sizeof(INT), (char FAR *)buf+i, len);
        dio_touch (parent[level-1]);
 
        len = m * slot_len + sizeof(INT);
        if (dio_get (left, &nd1) != S_OKAY)
                return (db_status);
	memcpy ((nd = nd1)->nd_slots, (char FAR *)buf, len);
        nd->nd_filled = m;
        dio_touch (left);
 
return (db_status = S_OKAY);
}
 
 
