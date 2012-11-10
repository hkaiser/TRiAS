/* Einfuegen eines Key-Eintrages an die richtige Stelle im 'buf'        */
/* File: PUTINL.C               last update: 23. Oktober 1989           */

#include "trias01p.hxx"
 
void FUNCTYPE put_inline (void *key, register void *buffer, 
			  short n, register short u_gr)
{
	memcpy ((char *)buffer+(n+1)*slot_len, (char *)buffer+n*slot_len, sizeof(REC_NO));
        for (register short i = n - u_gr; i > 0; --i)
		memcpy ((char *)buffer+(u_gr+i)*slot_len, (char *)buffer+(u_gr+i-1)*slot_len, slot_len);
	memcpy ((char *)buffer+u_gr*slot_len, key, slot_len);
}
 
 
