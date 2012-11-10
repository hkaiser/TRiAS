/* Root-Node in drei Pages aufsplitten                          */
/* File: ROOTSP.C               last update: 31. Mai 1989       */

#include "trias01p.hxx"

int FUNCTYPE split_root (register NODE *nd, KEY_SLOT *key, short level)
{
	register short j, m;
	short n, i;
	PAGE_NO ch1, ch2, ch3;
	
	/* alle Slots in 'buf' kopieren, dabei den neuen Key richtig einordnen */
	for (i = 0; i < d; ++i) {               /* for (1) */
		register KEY_SLOT FAR *ks_p = (KEY_SLOT FAR *)(nd->nd_slots+i*slot_len);
		INT cmp;
		
		if (key_type == FT_CHAR_ARRAY) {
			cmp = strncmp ((char *)key -> ks_key, 
				(char *)ks_p -> ks_key, 
				key_len * sizeof(INT)
				);
		} else {
		long lVersion = LocGetDBVersion();
			
			if ((VERSION0500000F <= lVersion && FT_STRUCT == key_type) || lVersion <= VERSION05000009) 
			{
				for (j = 0; j < key_len; ++j) {  /* for (2) */
					if (cmp = key -> ks_key[j] - ks_p -> ks_key[j])
						break;  /* raus aus for (2) */
				}
			} else {	// neue GeoDB
				cmp = memcmp ((char *)key -> ks_key, 
					(char *)ks_p -> ks_key, 
					key_len * sizeof(INT)
					);
			}
		}
		if (cmp < 0) break;     /* raus aus for (1) */
		if (cmp > 0) continue;
		if ((cmp = key -> ks_rec_no - ks_p -> ks_rec_no) < 0)
			break;
	}
	memcpy ((char *)buf, nd->nd_slots, i*slot_len);
	memcpy ((char *)buf+i*slot_len, key, slot_len);
	memcpy ((char *)buf+(i+1)*slot_len, nd->nd_slots+i*slot_len, (d-i)*slot_len);
	*(PAGE_NO *)((char *)buf+(d+1)*slot_len) = *(PAGE_NO *)(nd->nd_slots+d*slot_len);
	
	/* Root ist leer */
	nd->nd_filled = 0;
	
	/* Anfordern der drei neuen Records */
	if (db_pzalloc (keyfile, &ch1) != S_OKAY) return (db_status);
	if (db_pzalloc (keyfile, &ch2) != S_OKAY) return (db_status);
	if (db_pzalloc (keyfile, &ch3) != S_OKAY) return (db_status);
	
	/* der letzte Pointer muss auf ch3 zeigen */
	*(PAGE_NO *)nd->nd_slots = ch3;
	
	/* alle Slots neu verteilen */
	m = d / 3;
	n = d - 2*m - 1;
	fill_nodes (ch1, ch2, ch3, m, n, level+1);
	
	return (db_status = S_OKAY);
}


