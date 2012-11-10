// d4reccnt.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

long __export Data::reccount()
{
   if ( code_base->error() )  return -1L ;
   if ( header.num_recs >= 0L )  return header.num_recs ;

   long count =  file.len() ;
   if ( count < 0L )  return -1L ;
   count =  (count-header.header_len)/ record.len() ;
   if ( lock_test_append() )
	  header.num_recs =  count ;

   return count ;
}


