/* Splitten zweier benachbarter Nodes in drei Nodes             */
/* File: NODSPL.C               last update: 30. Mai 1989       */

#include "trias01p.hxx"
 
int FUNCTYPE split_nodes (PAGE_NO left, PAGE_NO right, void *key, 
			  short slot, short level)
{
PAGE_NO child;
short nkeys;
register short m, n;
register NODE *nd;
NODE *nd1;
 
        asm_buf (left, right, key, &nkeys, slot, level);
 
        if (dio_get (parent[level-1], &nd1) != S_OKAY)
                return (db_status);
        nd = nd1;
        zap_slot (nd->nd_slots, slot, nd->nd_filled);
        --nd->nd_filled;
        dio_touch (parent[level-1]);
 
        if (db_pzalloc (keyfile, &child) != S_OKAY)
                return (db_status);
 
        m = (nkeys-1) / 3;
        n = (nkeys-1) - 2*m - 1;
 
        fill_nodes (left, child, right, m, n, level);
 
return (db_status = S_OKAY);
}
 
 
 
