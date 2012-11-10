/*****************************************************************************
 *                                                                           *
 * netinet/in.h                                                              *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 * Copyright 1994 The Downhill Project                                       *
 *                                                                           *
 *****************************************************************************/

#if !defined(_DOWNHILL_NETINET_IN_H)
#define _DOWNHILL_NETINET_IN_H   

/* Include stuff *************************************************************/
#include <sys/types.h>
#include <sys/socket.h>

#define _getshort(buf)				\
    (((u_short)(((u_char *)buf)[0]) << 8) |	\
     ((u_short)(((u_char *)buf)[1]) << 0))
#define _getlong(buf)				\
    (((u_long)(((u_char *)buf)[0]) << 24) |	\
     ((u_long)(((u_char *)buf)[1]) << 16) |	\
     ((u_long)(((u_char *)buf)[2]) << 8)  |	\
     ((u_long)(((u_char *)buf)[3]) << 0))
#define putshort(n, buf)					\
    (((u_char *)buf)[0] = (((u_short)n) & 0xFF00) >> 8,	\
     ((u_char *)buf)[1] = (((u_short)n) & 0x00FF) >> 0)
#define putlong(n, buf)						\
    (((u_char *)buf)[0] = (((u_long)n) & 0xFF000000) >> 24,	\
     ((u_char *)buf)[1] = (((u_long)n) & 0x00FF0000) >> 16,	\
     ((u_char *)buf)[2] = (((u_long)n) & 0x0000FF00) >> 8,	\
     ((u_char *)buf)[3] = (((u_long)n) & 0x000000FF) >> 0)

#endif /* _DOWNHILL_NETINET_IN_H */

