/* Finden des Slots mit einem Schluessel der groesser als aktueller ist */
/* File: LOCSLT.C                       last update: 18. Juli 1989      */

#include "trias01p.hxx"
 
/* Die Funktiom liefert:
      0 = Key existiert nicht
      1 = Key existiert
      2 = Key existiert, aber mit anderer DB_ADDR
*/
extern "C" int FUNCTYPE locate_slot (void *key, void *buffer, short n, short *slot)
{
INT cmp;
register INT *iptr;
register short i, j;

	for (i = 0, iptr = (INT *)buffer; i < n; ++i, iptr += key_len +2) {
	/* Key vergleichen */
		if (key_type == FT_CHAR_ARRAY) {
			cmp = strncmp ((char *)(iptr + 2), (char *)((INT *)key + 2), key_len*sizeof(INT));
		} 
		else {
		long lVersion = LocGetDBVersion();

			if ((VERSION0500000F <= lVersion && FT_STRUCT == key_type) || lVersion <= VERSION05000009) 
			{
				for (j = 2; j <= key_len+1; ++j) {
					if (cmp = *(iptr+j) - *((INT *)key+j))
						break;
				}
			} else 	// neuere GeoDB
				cmp = memcmp ((iptr + 2), ((INT *)key + 2), key_len*sizeof(INT));
		}

		if (cmp < 0) continue;
		if (cmp > 0) return (*slot = i, 0);
 
	/* Adresse vergleichen */
		cmp = *(iptr+1) - *((INT *)key+1);

		if (cmp == 0) return (*slot = i, 1);
		if (unique) return (*slot = i, 2);
		if (cmp < 0) continue;
		if (cmp > 0) return (*slot = i, 0);
	}
	return (*slot = i, 0);
}
 
