/* Finden des ersten Schluessels ueber einen BTree              */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZFIRST_F.C             last update: 24. November 1989  */

#include "trias01p.hxx"
 
INT FUNCTYPE _export zfirst_ (DB_ADDR *dba, register INT *keyno)
{
	return (INT)z_keyfirst (dba, (int) *keyno);
}

