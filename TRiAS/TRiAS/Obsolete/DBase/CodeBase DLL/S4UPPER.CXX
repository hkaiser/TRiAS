// s4upper.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <ctype.h>
#include <limits.h>
}

void Str::upper()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::upper() called, but has a null pointer", (char *) 0 ) ;
   #endif
   changed() ;

   char *start_ptr =  ptr() ;
   unsigned end_pos =  len() ;
   for ( unsigned pos = 0; pos < end_pos; pos++ )
	  start_ptr[pos] = toupper( start_ptr[pos] ) ;
}


