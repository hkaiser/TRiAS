/* Finden des naechsten Schluesseleintrages                     */
/* File: KEYNEXT.C              last update: 19. Oktober 1989   */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int FUNCTYPE key_next (int keyindex, DB_ADDR *dba)
// int keyindex;           /* Schluesselnummer */
// DB_ADDR *dba;           /* gesuchte DBA */
{
NODE *nd1;
register NODE *nd;
register KEY_SLOT *ks_p;
PAGE_NO child;
 
/* Setzen der default-Werte fuer den Schluesselzugriff */
	TX_ASSERT(TIsValidAddress(key_table, sizeof(KEY_ENTRY)*size_kt, false));

	if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
	if (find_field != keyindex) return (dberr (S_KEYSEQ, KEY_NEXT));
 
/* Finden des nächsten Schlüsseleintrages */
	if (dio_get (parent[lvl], &nd1) != S_OKAY) return (db_status);
	nd = nd1;
	++slots[lvl];
	if (lvl == 0 && slots[lvl] > nd->nd_filled) {
		--slots[lvl];
		return (db_error (S_NOTFOUND, KEY_NEXT));
	}
	ks_p = (KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len);
	child = ks_p->ks_child;
	if (child != NONE) {
		while (child != NONE) {
		/* nach unten durchhangeln */
			if (++lvl >= MAXLEVEL)		// Level muß in Grenzen bleiben
				return db_error(S_SYSERR, KEY_PREV);
			parent[lvl] = child;
			slots[lvl] = 0;
			if (dio_get (child, &nd1) != S_OKAY)
				return (db_status);
			nd = nd1;
			child = ((KEY_SLOT FAR *)(nd->nd_slots))->ks_child;
		}
	/* diese Position zurückliefern */
	}
	else {
		while (slots[lvl] >= nd->nd_filled) {
		/* weiter hochhangeln */
			if (lvl == 0) return (db_error (S_NOTFOUND, KEY_NEXT));
			if (dio_get (parent[--lvl], &nd1) != S_OKAY)
				return (db_status);
			nd = nd1;
		}
	/* diese Position zurückliefern */
	}
	ks_p = (KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len);
	dba->rec_no = ks_p->ks_rec_no;
	return (db_status = S_OKAY);
}
