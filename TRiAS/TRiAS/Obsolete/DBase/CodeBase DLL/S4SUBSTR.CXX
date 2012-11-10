// s4substr.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

StrLen Str::substr( unsigned pos, unsigned result_len )
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::substr() called, but has a null pointer", (char *) 0 ) ;
   #endif
   unsigned my_len =  len() ;

   if ((unsigned)(long(pos) + result_len) > my_len )		// #JB950623
   {
	  if ( pos > my_len )
		 result_len =  0 ;
	  else
		 result_len =  my_len - pos ;
   }

   return StrLen( ptr()+pos, result_len ) ;
}

