/* Slot aus dem Buffer eliminieren                              */
/* File: ZAPSLT.C               last update: 23. Oktober 1898   */

#include "trias01p.hxx"

extern "C" int FUNCTYPE zap_slot (register void *buffer, register short slot, 
		       register short n)
{
	if (slot < n) {
		memcpy ((char *)buffer+slot*slot_len, (char *)buffer+(slot+1)*slot_len,
				(n-slot-1)*slot_len+sizeof(PAGE_NO));
		return (db_status = S_OKAY);
	} else
		return (dberr (S_SYSERR, ZAPSLT));
}
