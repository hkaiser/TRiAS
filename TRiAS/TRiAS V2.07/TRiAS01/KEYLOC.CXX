/* Lokalisieren eines Keys im BTree, sofern er existiert        */
/* File: KEYLOC.C               last update: 19. Oktober 1989   */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifdef unix
typedef unsigned size_t;
#endif

int FUNCTYPE key_loc (void *keyval, register int keyindex, DB_ADDR *dba)
// char *keyval;           /* Suchsch¸ssel */
// register int keyindex;  /* Schl¸sselnummer */
// DB_ADDR *dba;           /* gefundene DB-Adresse */
{
	/* Setzen der default-Werte aus File- und Keytabelle */
	TX_ASSERT(TIsValidAddress(key_table, sizeof(KEY_ENTRY)*size_kt, false));
	
	if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
	find_field = keyindex;
	
	if (keyval != NULL) {	/* Schl¸ssel lokalisieren */
		/* Initialisieren des Suchschl¸ssels */
		memset (key.ks_key, '\0', key_len * sizeof(INT));
		
		TX_ASSERT(TIsValidAddress(keyval, key_len * sizeof(INT), false));
		
		if (key_type == FT_CHAR_ARRAY) 
			strcpy ((char *)key.ks_key, (char *)keyval);
		else memcpy (key.ks_key, keyval, (size_t)(key_len * sizeof(INT)));
		
		return (locate (key.ks_key, dba));
	}
	else {
        /* Kein Schl¸sselwert gegeben >> vor erstem Schl¸ssel positionieren */
        DB_ADDR db_dummy(dba->db_no);
		
		if (locate_first (&db_dummy) != S_OKAY)
			return (db_status);
		--slots[lvl];   /* n‰chster Slot muﬂ erster sein */
		return (db_error (S_NOTFOUND, KEYLOC));
	}
}
