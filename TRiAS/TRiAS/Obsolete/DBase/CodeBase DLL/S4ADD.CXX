// s4add.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <ctype.h>
#include <limits.h>
}

int __export Str::add( Str& str_from )
{
   return insert( str_from, len() ) ;
}


int __export Str::insert( Str& str_from, unsigned pos )
{
   #ifdef DEBUG
	  s4asser_no_overlap( *this, str_from ) ;
   #endif

   changed() ;

   unsigned  start_to_len =  len() ;
   #ifdef DEBUG
	  if ( pos > start_to_len )  e4severe( e4info, "Str::insert()", (char *) 0 ) ;
   #endif
   unsigned  move_len =  start_to_len-pos ;

   unsigned  from_len =  str_from.len() ;
   long	  want_to_len =  long(start_to_len) +from_len ;
   int rc ;
   if ( want_to_len > UINT_MAX )
	  rc =  -1 ;
   else
	  rc =  set_len( unsigned(want_to_len) ) ;

   unsigned to_len = len() ;

   if ( rc != 0 )
   {
	  #ifdef DEBUG
		 if ( to_len < start_to_len )  e4severe( e4info, "Str::insert", (char *) 0 ) ;
	  #endif
	  move_len  -=  unsigned( want_to_len - to_len ) ;

	  unsigned space_avail =  to_len-pos ;
	  if ( space_avail < from_len ) from_len =  space_avail ;
   }

   char *to_ptr =  ptr() ;
   char *to_pos =  to_ptr+pos ;
   memmove( to_pos+from_len, to_pos, move_len ) ;
   memcpy( to_pos, str_from.ptr(), from_len ) ;

   if ( to_len < maximum() )
	  to_ptr[to_len] =  0 ;
   return rc ;
}
