/* Suchen eines Schluessels                                     */
/* File: LOCATE.C               last update: 19. Oktober 1989   */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int FUNCTYPE locate (void *keyval, DB_ADDR *dba)
// char *keyval;           /* Schluesselwert */
// DB_ADDR *dba;           /* gesuchte DBA */
{
	TX_ASSERT_POINTER(dba, DB_ADDR);
	TX_ASSERT(TIsValidAddress (keyval, key_len*sizeof(INT), false));
	
	NODE *nd1;
	register NODE *nd;
	register KEY_SLOT *ks_p;
	
	/* Anfangsbedingungen */
	parent[0] = ROOT_ADDR;
	lvl = 0;
	
	/* Suchschleife */
	while (TRUE) {
		if (dio_get (parent[lvl], &nd1) != S_OKAY) return (db_status);
		nd = nd1;
		if (key_cmp (keyval, nd->nd_slots, nd->nd_filled, &slots[lvl])) {
			/* Unique Schlüssel gefunden */
			dba->rec_no = ((KEY_SLOT *)(nd->nd_slots+slots[lvl]*slot_len))->ks_rec_no;
			return (db_status = S_OKAY);
		}
		else {
			/* Schlüssel noch nicht gefunden */
			ks_p = (KEY_SLOT *)(nd->nd_slots+slots[lvl]*slot_len);
			parent[++lvl] = ks_p->ks_child;
			if (parent[lvl] == NONE) {
				--lvl;
				if (unique) {
					--slots[lvl];
					return (db_error (S_NOTFOUND, LOCATE));
				}
				else {
					while (slots[lvl] >= nd->nd_filled) {
						if (lvl == 0) break;
						if (dio_get (parent[--lvl], &nd1) != S_OKAY)
							return (db_status);
						nd = nd1;
					}
					if (lvl == 0 && slots[lvl] >= nd->nd_filled) {
						--slots[lvl];
						return (db_error (S_NOTFOUND, LOCATE));
					}
					ks_p = (KEY_SLOT *)(nd->nd_slots+slots[lvl]*slot_len);
					if (key_type == FT_CHAR_ARRAY) {
						if (!strncmp ((char *)keyval, (char *)ks_p->ks_key, key_len*sizeof(INT))) {
							dba->rec_no = ks_p->ks_rec_no;
							return (db_status = S_OKAY);
						}
					} else {
						if (!memcmp (keyval, ks_p->ks_key, key_len*sizeof(INT))) {
							dba->rec_no = ks_p->ks_rec_no;
							return (db_status = S_OKAY);
						}
					}
				}
				--slots[lvl];
				return (db_error (S_NOTFOUND, LOCATE));
			}
		}
	}
}

