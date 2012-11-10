// c4codeop.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

Data *CodeBase::data( char *alias_name )
{
   if ( error() )  return 0 ;

   LinkIterator next( data_list ) ;
   Str10 alias_str( alias_name ) ;
   alias_str.upper() ;

   Data *data_ptr ;
   Data *result_ptr = 0 ;
   while( data_ptr =  (Data *) next() )
	  if ( alias_str == data_ptr->alias )
	  {
		 #ifdef DEBUG
			if ( result_ptr != 0 )  e4severe( e4info, "CodeBase::data", "Duplicate Alias", (char *) 0 ) ;
			result_ptr =  data_ptr ;
		 #else
			result_ptr =  data_ptr ;
			break ;
		 #endif
	  }
   return result_ptr ;
}

