/* Routinen zum loeschen und einfuegen eines beliebigen Schluessels     */
/* File: KEYUTIL.C                                                      */

#include "trias01p.hxx"

/* Einfuegen eines Schluessels (fuer alle Schluesseltypen */
extern "C" int FUNCTYPE insert_key (register DB_ADDR *dba, register void *ptr)
{
#ifdef HTREE_FUNCTIONS
	if (htfile != NONE) {
		htfile = NONE;
		return (ht_insert ((CONTAINER FAR *)ptr, dba));
	} else
#endif
#ifdef QTREE_FUNCTIONS
	if (qtfile != NONE) {
		qtfile = NONE;
		return (qt_insert ((QTPOINT FAR *)ptr, dba));
	} else
#endif
#ifdef BTREE_FUNCTIONS
	if (working_file != NONE) {
		key_cat ((INT FAR *)ptr, &dba->rec_no);
		ins (ROOT_ADDR, (char *)&key, 0);
        return (db_status);
	} else
#endif
		return (dberr (S_NOKEY, INSERT_KEY));
}

/* Loeschen eines Schluessels */
extern "C" int FUNCTYPE delete_key (register DB_ADDR *dba, register void *ptr)
{
#ifdef HTREE_FUNCTIONS
	if (htfile != NONE) {
		htfile = NONE;
		return (ht_delete ((CONTAINER FAR *)ptr, dba));
	} else
#endif
#ifdef QTREE_FUNCTIONS
	if (qtfile != NONE) {
		qtfile = NONE;
		return (qt_delete ((QTPOINT FAR *)ptr, dba));
	} else
#endif
#ifdef BTREE_FUNCTIONS
	if (working_file != NONE) {
		key_cat ((INT FAR *)ptr, &dba->rec_no);
		kdel (ROOT_ADDR, (char *)&key, 0);
		return (db_status);
	} else
#endif
		return (dberr (S_NOKEY, DELETE_KEY));
}

