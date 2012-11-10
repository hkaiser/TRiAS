/* Finden des Slots mit einem Schluessel der groesser als aktueller ist */
/* File: LOCSLT.C                       last update: 18. Juli 1989      */

#include "trias01p.hxx"

/* Die Funktiom liefert:
      0 = Key existiert nicht
      1 = Key existiert
      2 = Key existiert, aber mit anderer DB_ADDR
*/
 
int FUNCTYPE t_locate_slot (void *lockey, void *buffer, short n, short *slot)
{
INT cmp;
register INT *iptr;
register short i, j;
long lVersion = LocGetDBVersion();
 
	for (i = 0, iptr = (INT *)buffer; i < n; ++i, iptr += key_len+1) {
	/* Key vergleichen */
		if (lVersion <= VERSION05000009) {
			for (j = 1; j <= key_len; ++j)
				if (cmp = *(iptr+j) - *((INT *)lockey+j))
					break;
		} else {
			cmp = memcmp (iptr+1, (INT *)lockey+1, key_len*sizeof(INT));
		}

		if (cmp < 0) continue;
		if (cmp > 0) return (*slot = i, 0);
 
	/* Adresse vergleichen */
		cmp = *iptr - *(INT *)lockey;
		if (cmp == 0) return (*slot = i, 1);
		if (unique) return (*slot = i, 2);
		if (cmp < 0) continue;
		if (cmp > 0) return (*slot = i, 0);
	}
 
return (*slot = i, 0);
}
 
