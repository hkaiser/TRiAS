// s4replac.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <limits.h>
}

int  __export Str::replace( Str& str, unsigned pos )
{
   #ifdef DEBUG
	  s4asser_no_overlap( *this, str ) ;
   #endif

   changed() ;

   unsigned cur_len =  len() ;
   #ifdef DEBUG
	  if ( pos > cur_len )  e4severe( e4parm, "Str::replace()", (char *) 0 ) ;
   #endif
   unsigned copy_len =  str.len() ;
   long to_final_len =  long(copy_len) + pos ;
   int rc = 0 ;
   if ( to_final_len > UINT_MAX )
	  rc =  -1 ;
   else
   {
	  if ((unsigned) to_final_len > cur_len )			// #JB950623
	  {
		 rc =  set_len( unsigned(to_final_len) ) ;
		 cur_len =  len() ;
	  }
   }
   if ( rc < 0 )
	  copy_len =  cur_len - pos ;

   char *p = ptr() ;
   memcpy( p+pos, str.ptr(), copy_len ) ;
   if ( cur_len < maximum() )  p[cur_len] =  0 ;
   return rc ;
}


