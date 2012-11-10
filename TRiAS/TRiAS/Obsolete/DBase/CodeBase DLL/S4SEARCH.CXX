// s4search.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int __export Str::search( Str& search_str )
{
   #ifdef DEBUG
	  if( ptr() == 0 || search_str.ptr() == 0 ) e4severe( e4parm, "Str::search() called with or has a null pointer", (char *) 0 ) ;
   #endif
   unsigned len_search =  search_str.len() ;
   if ( len_search == 0 )  return 0 ;

   unsigned str_len  =  len() ;
   if ( str_len < len_search )  return -1 ;

   unsigned last_try =  str_len - len_search ;
   char *str_ptr =  ptr() ;
   char *search_ptr =  search_str.ptr() ;

   for ( unsigned i = 0; i <= last_try; i++ )
	  if ( str_ptr[i]  == *search_ptr )
	  {
		 for ( unsigned j = 1; j < len_search; j++ )
			if ( str_ptr[i+j] != search_ptr[j] )  break ;
		 if ( j >= len_search )  return int(i) ;
	  }

   return -1 ;
}


