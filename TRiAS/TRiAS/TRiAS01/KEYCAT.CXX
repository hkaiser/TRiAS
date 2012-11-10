/* Bilden des vollstaendigen Schluesseleintrages                */
/* File: KEYCAT.C               last update: 31. Mai 1989       */

#include "trias01p.hxx"

void FUNCTYPE key_cat (register void *key_val, REC_NO *db_ad)
{
	register short i;
	register long *keyp;
	long *pKey = (long *)key_val;
	
	/* Schluessel */
	for (i = 0, keyp = &key.ks_key[0]; i < key_len; ++i) 
		*keyp++ = *pKey++;
	
	/* Recordnummer */
	key.ks_rec_no = *db_ad;
	key.ks_child = NONE;
}


