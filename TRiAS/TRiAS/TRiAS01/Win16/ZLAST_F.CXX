/* Finden des letzten Schluessels ueber einen BTree             */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZLAST_F.C              last update: 24. November 1989  */

#include "trias01p.hxx"

INT FUNCTYPE _export zlast_ (dba, keyno)
DB_ADDR *dba;
register INT *keyno;
{
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZLAST_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZLAST_F));
#endif  
        if (*keyno < 0 || *keyno >= size_kt) return (dberr (S_NOKEY, ZLAST_F));
/* Finden des gesuchten Datensatzes */
        return (key_last ((short)*keyno, dba));
}
