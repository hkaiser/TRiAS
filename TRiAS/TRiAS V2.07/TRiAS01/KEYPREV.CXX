/* Finden des vorhergehenden Schluesseleintrages                */
/* File: KEYPREV.C              last update: 19. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE key_prev (int keyindex, DB_ADDR *dba)
// int keyindex;           /* Schlüsselnummer */
// DB_ADDR *dba;           /* gesuchte DBA */
{
NODE *nd1;
register NODE *nd;
register KEY_SLOT *ks_p;
PAGE_NO child;
 
/* Setzen der default-Werte fuer den Schluesselzugriff */
        if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
        if (find_field != keyindex) return (dberr (S_KEYSEQ, KEY_PREV));
 
/* Finden des vorhergehenden Schluesseleintrages */
        if (slots[lvl] < 0) return (db_error (S_NOTFOUND, KEY_PREV));
        if (dio_get (parent[lvl], &nd1) != S_OKAY) return (db_status);
        nd = nd1;
	ks_p = (KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len);
        child = ks_p->ks_child;
        if (child != NONE) {
                while (child != NONE) {
                /* nach unten durchhangeln */
                        parent[++lvl] = child;
                        if (dio_get (child, &nd1) != S_OKAY)
                                return (db_status);
                        nd = nd1;
			child = ((KEY_SLOT FAR *)(nd->nd_slots))->ks_child;
                        slots[lvl] = nd->nd_filled;
                }
                /* diese Position zurueckliefern */
                --slots[lvl];
        }
        else {
                while (slots[lvl] <= 0) {
                /* weiter hochhangeln */
                        if (lvl == 0) return (db_error (S_NOTFOUND, KEY_PREV));
                        if (dio_get (parent[--lvl], &nd1) != S_OKAY)
                                return (db_status);
                        nd = nd1;
                }
                /* diese Position zurueckliefern */
                --slots[lvl];
        }
	ks_p = (KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len);
        dba->rec_no = ks_p->ks_rec_no;
 
return (db_status = S_OKAY);
}
