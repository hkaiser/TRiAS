// s4endptr.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

char *Str::end_ptr()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::end_ptr() called, but has a null pointer", (char *) 0 ) ;
   #endif
   unsigned pos =  len() ;
   if ( pos == 0 ) return 0 ;
   pos-- ;
   return ptr()+pos ;
}


