// s4strset.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <ctype.h>
#include <limits.h>
}

void __export Str::set( int chr_value )
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::null_ensure() called, but has a null pointer", (char *) 0 ) ;
   #endif
   changed() ;

   unsigned l =  len() ;
   char *p =  ptr() ;
   memset( p, chr_value, l ) ;
   if ( l < maximum() )  p[l] =  0 ;
}


