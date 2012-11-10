/* Zusammenfassen zweier Nodes zu einer Page                    */
/* File: COMBIN.C               last update: 6. Juni 1989       */

#include "trias01p.hxx"
 
int FUNCTYPE combine (PAGE_NO left, PAGE_NO right, 
		      register short slot, register short level)
{
register NODE *nd;
NODE *nd1;
short nkeys;
 
	asm_buf (left, right, NULL, &nkeys, slot, level);
	if (nkeys > d)
		return (dberr (S_SYSERR, COMBIN));
 
/* Wurzel bearbeiten ? */
	if (level == 1) {
		if (dio_get (ROOT_ADDR, &nd1) != S_OKAY)
			return (db_status);
		if ((nd = nd1)->nd_filled == 1) {
			memcpy (nd->nd_slots, buf, nkeys*slot_len+sizeof(PAGE_NO));
			nd->nd_filled = nkeys;
			dio_touch (ROOT_ADDR);
 
			if (db_pzfree (keyfile, left) != S_OKAY) return (db_status);
			if (db_pzfree (keyfile, right) != S_OKAY) return (db_status);
 
			return (db_status = S_OKAY);
		}
	}
 
	if (dio_get (right, &nd1) != S_OKAY) return (db_status);
	nd = nd1;
	memcpy (nd->nd_slots, buf, nkeys*slot_len+sizeof(PAGE_NO));
	nd->nd_filled = nkeys;
	dio_touch (right);
 
/* freigeben der linken Node */
	if (db_pzfree (keyfile, left) != S_OKAY) return (db_status);
 
/* Entfernen des slot aus der uebergeordneten Node */
	return (shrink (parent[level-1], slot, level-1));
}
 
