// d4xgoeof.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int  DataIndex::go_eof()
{
   int rc ;
   if ( (rc = flush_record()) != 0 )  return rc ;
   long count =  reccount() ;  if ( count < 0 )  return -1 ;
   rec_num =  count+1L ;
   eof_flag =  1 ;
   if ( rec_num == 1 )  bof_flag =  1 ;
   record.set( ' ' ) ;
   return r4eof ;
}


