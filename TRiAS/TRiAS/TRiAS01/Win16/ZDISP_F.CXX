/* Freigeben  eines Datensatzes                                 */
/* Fortran-Schnittstelle (UNIX)                                 */
/* File: ZDISP_F.C              last update: 22. November 1989  */

#include "trias01p.hxx"
 
INT FUNCTYPE _export zdisp_ (DB_ADDR *dba)
{
	return (INT)z_dispose (dba);
}

