// d4xgo.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int  __export DataIndex::go( long rec )
{
   int rc =  flush_record() ;  if ( rc != 0 ) return rc ;
   if ( code_base->read_lock )
   {
	  rc =  lock(rec) ;
	  if ( rc != 0 )  return rc ;
   }
   rc =  Data::go(rec) ;	   if ( rc != 0 )  return rc ;
   bof_flag = eof_flag = 0 ;
   if ( lock_test(rec)  )
   {
	  record_old =  record ;
	  rec_num_old =  rec_num ;
   }
   return rc ;
}


