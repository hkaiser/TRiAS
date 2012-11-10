// d4append.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int Data::append()
{
   long count =  reccount() ;  if ( count < 0L )  return -1 ;
   file_changed =  1 ;
   long pos =  recpos( count+1L ) ;
   record.ptr()[record.cur_len++] = 0x1A ;
   int rc =  file.write( pos, record ) ;
   if ( rc >= 0 )
   {
	  rec_num =  count + 1L ;
	  record.is_changed =  0 ;
	  if ( lock_test_append() )
		 header.num_recs++ ;
   }

   record.ptr()[--record.cur_len] = 0 ;

   return rc ;
}
