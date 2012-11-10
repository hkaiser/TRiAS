/* Finden des ersten Schluesseleintrages                        */
/* File: LOCFRST.C              last update: 19. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE locate_first (DB_ADDR *dba)
// DB_ADDR *dba;           /* gesuchte DB-Adresse */
{
NODE *nd1;
register NODE *nd;
register KEY_SLOT *ks_p;
 
/* Anfangsbedingungen */
        parent [0] = ROOT_ADDR;
        lvl = 0;
 
/* Suchschleife */
        while (TRUE) {
                if (dio_get (parent[lvl], &nd1) != S_OKAY) return (db_status);
                nd = nd1;
                slots[lvl] = 0;
		ks_p = ((KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len));
                parent[++lvl] = ks_p->ks_child;
                if (parent[lvl] == NONE) {
                /* Blattknoten erreicht */
                        --lvl;
                        while (slots[lvl] >= nd->nd_filled) {
                        /* wieder hochhangeln */
                                if (lvl == 0) break;
                                if (dio_get (parent[--lvl], &nd1) != S_OKAY)
                                        return (db_status);
                                nd = nd1;
                        }
                        if (lvl == 0 && slots[lvl] >= nd->nd_filled) {
                        /* root-leaf */
                                --slots[lvl];
                                return (db_error (S_NOTFOUND, LOCFRST));
                        }
			ks_p = (KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len);
                        dba->rec_no = ks_p->ks_rec_no;
                        return (db_status = S_OKAY);
                }
        }
}
