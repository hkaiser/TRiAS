/*****************************************************************************
 *                                                                           *
 * DH_TIME.C                                                                 *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/
/*
 * 	Use ftime to get more accurate
 * 	time information.
 * 	[1997/06/13  03:08:11  tbartley]
 */
#if !defined(lint) && !defined(_NOIDENT)
static const char* rcsid = "@(#)$RCSfile: dh_time.c,v $ $Revision: 1.1.2.2 $ (DOWNHILL) $Date: 1997/06/13 03:09:16 $";
#endif


/* Include stuff *************************************************************/
#include "INCLUDE/DH.H"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/timeb.h>


/* Function stuff ************************************************************/

/* Get the time of day ===================================================== */
#if (_DOWNHILL_POSIX_SOURCE == 0)
int gettimeofday(struct timeval* time_Info,struct timezone* timezone_Info)
{
    struct _timeb t;
    
    /*
     * Get the time - this returns seconds, milliseconds,
     * timezone and daylight savings info.
     */
    _ftime(&t);

    /* Get the time, if they want it */
    if (time_Info != NULL) {
	time_Info->tv_sec  = t.time;
	time_Info->tv_usec = t.millitm * 1000;
    }

    /* Get the timezone, if they want it */
    if (timezone_Info != NULL) {
	timezone_Info->tz_minuteswest = t.timezone;
	timezone_Info->tz_dsttime     = t.dstflag;
    }

    /* And return */
    return 0;
}
#endif
