/* Fuellen dreier Child-Nodes aus dem Puffer 'buf'              */
/* File: NODFIL.C               last update: 31. Mai 1989       */

#include "trias01p.hxx"

int FUNCTYPE fill_nodes (PAGE_NO ch1, PAGE_NO ch2, PAGE_NO ch3, 
			 register short m, register short n, short level)
{
register NODE *np;
NODE *np1;
KEY_SLOT temp;
 
/* fuellen von Child1 */
        if (dio_get (ch1, &np1) != S_OKAY) return (db_status);
        np = np1;
	memcpy (np->nd_slots, (char FAR *)buf, slot_len*m + sizeof (PAGE_NO));
        np->nd_filled = m;
        dio_touch (ch1);
 
/* fuellen von Child2 */
        if (dio_get (ch2, &np1) != S_OKAY) return (db_status);
        np = np1;
	memcpy (np->nd_slots, (char FAR *)buf + (m+1)*slot_len, slot_len*m + sizeof (PAGE_NO));
        np->nd_filled = m;
        dio_touch (ch2);
 
/* fuellen von Child3 */
        if (dio_get (ch3, &np1) != S_OKAY) return (db_status);
        np = np1;
	memcpy (np->nd_slots, (char FAR *)buf + (2*m+2)*slot_len, slot_len*n + sizeof (PAGE_NO));
        np->nd_filled = n;
        dio_touch (ch3);
 
/* Einfuegen der internen Node-Pointer in Parent-Node */
        memcpy (&temp, (char *)buf+slot_len*m, slot_len);
        temp.ks_child = ch1;
        *(INT *)((char *)buf+slot_len*(2*m+1)) = ch2;
        NodeExpand (parent[level-1], (char *)buf+slot_len*(2*m+1), level-1);
        NodeExpand (parent[level-1], (char *)&temp, level-1);
 
return (db_status = S_OKAY);
}
 
 
