// u4util.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.  

#ifndef U4UTIL

#define U4UTIL

#ifndef D4DATA
#include "d4data.h"
#endif

int u4memcmp (char *s1, char *s2, size_t len ); //#JB931208

#if defined (__ZTC__) && defined (MEDIUM)
   int   u4ptr_equal( void far *p1, void far *p2 ) ;
#else
   int   D4DLL_EXP u4ptr_equal( void *p1, void *p2 ) ;
#endif
void  D4DLL_EXP u4ncpy( char *, char *, int ) ;
void  D4DLL_EXP u4yymmdd( char *yymmdd ) ;  // Fills in 'YYMMDD' into char[3] array.

int   D4DLL_EXP l4lock_check() ;
void  D4DLL_EXP l4lock_remove( int,long,long) ;
void  D4DLL_EXP l4lock_save( int,long,long) ;


#endif

