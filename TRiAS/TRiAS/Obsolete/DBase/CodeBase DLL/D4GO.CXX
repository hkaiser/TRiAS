// d4go.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"
int Data::go( long rec )
{
   #ifdef DEBUG
	  if ( rec < 1L )  e4severe( e4info, "Data::go", (char *)  0) ;
   #endif

   unsigned len =  record.len() ;
   if ( file.read( recpos(rec), record, &len ) < 0 )  return -1 ;

   if ( len != record.len() )
   {
	  if ( code_base->go_error )
		 return  code_base->error( e4read, file.name.ptr(), (char *) 0 ) ;

	  return r4entry ;
   }
   rec_num =  rec ;
   return 0 ;
}


