/* Findendes naechsten Schluessels ueber einen BTree            */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZNEXT_F.C              last update: 24. November 1989  */

#include "trias01p.hxx"
 
INT FUNCTYPE
znext_ (dba, keyno)
DB_ADDR *dba;
register INT *keyno;
{
#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZNEXT_F));
#else
        if (act_db == NULL) return (dberr (S_DBOPEN, ZNEXT_F));
#endif  
        if (*keyno < 0 || *keyno >= size_kt) return (dberr (S_NOKEY, ZNEXT_F));
/* Finden des gesuchten Datensatzes */
        return (key_next ((short)*keyno, dba));
}
