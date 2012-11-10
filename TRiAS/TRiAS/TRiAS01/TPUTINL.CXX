/* Einfuegen eines Key-Eintrages an die richtige Stelle im 'buf'        */
/* File: PUTINL.C               last update: 31. Mai 1989               */

#include "trias01p.hxx"

extern "C" void FUNCTYPE t_put_inline (void *key, register void *buffer, 
			    register short n, short u_gr)
{
        for (register short i = n - u_gr; i > 0; --i)
		memcpy ((char *)buffer+(u_gr+i)*slot_len, (char *)buffer+(u_gr+i-1)*slot_len, slot_len);
	memcpy ((char *)buffer+u_gr*slot_len, key, slot_len);
}
 
 
