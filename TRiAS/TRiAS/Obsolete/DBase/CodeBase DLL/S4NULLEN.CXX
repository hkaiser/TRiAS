// s4nullen.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <ctype.h>
#include <limits.h>
}

int __export Str::null_ensure()
{
   if ( null_ended() )  return 0 ;

   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::null_ensure() called, but has a null pointer", (char *) 0 ) ;
   #endif

   changed() ;

   int rc =  0 ;
   unsigned l =  len() ;
   if ( l >= maximum() ) 
   {
	  if ( l == UINT_MAX )
		 l-- ;
	  else
	  {
		 set_max(l+1) ;
		 if ( l >= maximum() )
		 {
			rc =  -1 ;
			if ( l == 0 )  e4severe( e4result, "Str::null_ensure()", (char *) 0 ) ;
			l-- ;
		 }
	  }
   }
   ptr()[l] =  0 ;
   return rc ;
}


