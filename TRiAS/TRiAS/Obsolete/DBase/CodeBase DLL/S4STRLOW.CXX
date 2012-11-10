// s4strlow.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <ctype.h>
}

void Str::lower()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::lower() called, but has a null pointer", (char *) 0 ) ;
   #endif
   changed() ;

   unsigned str_len = len() ;
   char	*str_ptr =  ptr() ;
   for ( unsigned i = 0; i < str_len; i++ )
	  str_ptr[i] =  tolower( str_ptr[i] ) ;
}

