/* Lesen des aktuellen Schluesselwertes                         */
/* Fortran Schnittstelle (UNIX)                                 */
/* File: ZKREAD_F.C             last update: 24. November 1989  */

#include "trias01p.hxx"

INT FUNCTYPE _export zkread_ (char *keyptr)
{
	return (INT)z_keyread (keyptr);
}
