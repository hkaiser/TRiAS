/* Finden eines Schluessels ueber einen BTree                   */
/* Fortran-Schnittstelle (UNIX)                                 */
/* File: ZFIND_F.C              last update: 24. November 1989  */

#include "trias01p.hxx"
 
INT FUNCTYPE
zfind_ (dba, keyno, keyptr)
DB_ADDR *dba;
register INT *keyno;
char *keyptr;
{
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZFIND_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZFIND_F));
#endif  
        if (*keyno < 0 || *keyno >= size_kt) return (dberr (S_NOKEY, ZFIND_F));
/* Finden des gesuchten Datensatzes */
        return (key_loc (keyptr, (short)*keyno, dba));
}
