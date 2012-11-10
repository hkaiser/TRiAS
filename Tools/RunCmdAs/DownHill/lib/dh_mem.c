/*****************************************************************************
 *                                                                           *
 * DH_MEM.C                                                                  *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/
#if !defined(lint) && !defined(_NOIDENT)
static const char* rcsid = "@(#)$RCSfile: dh_mem.c,v $ $Revision: 1.1.2.1 $ (DOWNHILL) $Date: 1997/04/17 06:17:16 $";
#endif


/* Include stuff *************************************************************/
#include "INCLUDE/DH.H"
#include <malloc.h>


/* Function stuff ************************************************************/

/* Free a memory block ===================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
void cfree(void* mem_Block)
{
	free(mem_Block);
}
#endif
