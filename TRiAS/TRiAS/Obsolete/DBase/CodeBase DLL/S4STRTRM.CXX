// s4strtrm.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

void Str::trim()
{
   #ifdef DEBUG
	  if( ptr() == 0 ) e4severe( e4parm, "Str::trim() called, but has a null pointer", (char *) 0 ) ;
   #endif
   changed() ;

   char *p =  ptr() ;
   for ( unsigned i = len();; )
   {
	  if ( i == 0 )  break ;
	  i-- ;

	  if ( p[i] == ' ' || p[i] == 0 )
		 p[i] =  0 ;
	  else
	  {
		 set_len(i+1) ;
		 return ;
	  }
   }
   set_len(0) ;
}


