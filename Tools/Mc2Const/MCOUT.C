/*++

Copyright (c) 1991-1996 Microsoft Corporation

Module Name:

    mcout.c

Abstract:

    This file contains the output functions of the Win32 Message Compiler (MC)

--*/

#include "mc.h"

PMESSAGE_BLOCK MessageBlocks = NULL;
int NumberOfBlocks = 0;

/*++

Routine Description:

Arguments:


Return Value:


--*/


BOOLEAN
McBlockMessages( void )
{
    PMESSAGE_BLOCK p, *pp;
    PMESSAGE_INFO MessageInfo;

    pp = &MessageBlocks;
    p = NULL;

    MessageInfo = Messages;
    while (MessageInfo) {
        if (p) {
            if (p->HighId+1 == MessageInfo->Id) {
                p->HighId += 1;
                }
            else {
                pp = &p->Next;
                }
            }

        if (!*pp) {
            NumberOfBlocks += 1;
            p = malloc( sizeof( *p ) );
            p->Next = NULL;
            p->LowId = MessageInfo->Id;
            p->HighId = MessageInfo->Id;
            p->LowInfo = MessageInfo;
            *pp = p;
            }

        MessageInfo = MessageInfo->Next;
        }

    return( TRUE );
}

/*++

Routine Description:

Arguments:


Return Value:


--*/


BOOLEAN
McWriteBinaryFiles( void )
{
    return( TRUE );
}
