/* Suchen des Slots fuer gegebenen Schluessel                   */
/* File: KEYCMP.C               last update: 19. Oktober 1989   */

#include "trias01p.hxx"

extern "C" int FUNCTYPE key_cmp (void *keyval, void *buffer, short filled, short *sln)
// char *keyval;           /* Suchschluessel */
// char *buffer;		 /* Suchbereich */
// short filled;           /* Anzahl der Slots */
// short *sln;		 /* Slotnummer */
{
	INT cmp;
	register INT *keyptr, *bufptr;
	register int i;
	
	for (*sln = 0; *sln < filled; ++(*sln)) {
        /* fuer alle Slots */
		if (key_type == FT_CHAR_ARRAY) {
			cmp = strncmp ((char *)keyval,
				(char *)((KEY_SLOT *)((char *)buffer+(*sln)*slot_len))->ks_key, 
				key_len*sizeof(INT));
		} else {
		long lVersion = LocGetDBVersion();

			if ((VERSION0500000F <= lVersion && FT_STRUCT == key_type) || lVersion <= VERSION05000009) 
			{
			// wenn alte GeoDB oder (ganz neue und StructKey)
				bufptr = (INT *)(((KEY_SLOT FAR *)((char *)buffer+(*sln)*slot_len))->ks_key);
				keyptr = (INT *)(keyval);
				for (i = 0; i < key_len; ++i) {
					if (0 != (cmp = (*keyptr++ - *bufptr++))) 
						break;
				}
			} else {	// neuere GeoDB (> VERSION05000009 || < VERSION0500000F)
				cmp = memcmp (keyval,
					((KEY_SLOT*)((char *)buffer+(*sln)*slot_len))->ks_key,
					key_len*sizeof(INT));
			}
		}
		
		if (cmp == 0) {
			if (unique) 
				return TRUE;
			return FALSE;
		} else if (cmp < 0)
			return FALSE;
	}
	
	return FALSE;
}


