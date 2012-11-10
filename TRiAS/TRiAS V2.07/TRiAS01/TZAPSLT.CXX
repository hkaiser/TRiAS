/* Slot aus dem Buffer eliminieren                              */
/* File: TZAPSLT.C              last update: 31. Mai 1898       */

#include "trias01p.hxx"
 
extern "C" int FUNCTYPE t_zap_slot (register void *buffer, register short slot, register short n)
{
        if (slot < n) {
		memcpy ((char *)buffer+slot*slot_len, (char *)buffer+(slot+1)*slot_len,
                                        (n-slot-1)*slot_len+sizeof(PAGE_NO));
                return (db_status = S_OKAY);
        } else
                return (dberr (S_SYSERR, TZAPSLT));
}
 
 
