/* Lokalisieren des ersten Schluesseleintrages                  */
/* File: KEYFRST.C              last update: 19. Oktober 1989   */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int FUNCTYPE key_first (register short keyindex, DB_ADDR *dba)
// register short keyindex; /* Schluesselnummer */
// DB_ADDR *dba;           /* gesuchte DB-Adresse */
{
	/* Setzen der default-Werte fuer den Schluesselzugriff */
	TX_ASSERT(TIsValidAddress(key_table, sizeof(KEY_ENTRY)*size_kt, false));
	
	if (key_init (key_table + keyindex) != S_OKAY) return (db_status);
	find_field = keyindex;
	
	return (locate_first (dba));
}
