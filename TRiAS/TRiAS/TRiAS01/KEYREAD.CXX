/* Lesen des aktuellen Schluesselfeldes                         */
/* File: KEYREAD.C              last update: 19. Oktober 1989   */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int FUNCTYPE key_read (register void *keyval)
{
register NODE *nd;
NODE *nd1;
register KEY_SLOT *ks_p;
 
        if (find_field == NONE) return (dberr (S_KEYSEQ, KEY_READ_ROUT));

/* Setzen der default-Werte fuer den Schluesselzugriff */
	TX_ASSERT(TIsValidAddress(key_table, sizeof(KEY_ENTRY)*size_kt, false));
	TX_ASSERT(find_field >= 0 && find_field < size_kt);

        if (key_init (key_table + find_field) != S_OKAY) return (db_status);
 
/* Page einlesen */
        if (dio_get (parent[lvl], &nd1) != S_OKAY) return (db_status);
        nd = nd1;
 
/* Schluesselwert kopieren */
	ks_p = ((KEY_SLOT FAR *)(nd->nd_slots+slots[lvl]*slot_len));

	TX_ASSERT(TIsValidAddress(keyval, key_len*sizeof(INT)));
	if (key_type == FT_CHAR_ARRAY) 
		strcpy ((char *)keyval, (char *)ks_p->ks_key);
	else memcpy (keyval, ks_p->ks_key, key_len*sizeof(INT));
 
return (db_status = S_OKAY);
}
