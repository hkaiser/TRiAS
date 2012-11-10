// d4xlock.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int DataIndex::lock_index()
{
   LinkIterator next( indexes ) ;

   for ( Index *index_on; index_on =  (Index *) next(); )
   {
	  int rc =  index_on->lock_file() ;
	  if ( rc != 0 )  return rc ;
   }
   return  code_base->error() ;
}

int __export DataIndex::unlock_all()
{
   int rc = flush_record() ;  if ( rc != 0 )  return rc ;
   Data::unlock_all() ;
   return  unlock_index() ;
}

int DataIndex::unlock_index()
{
   if ( code_base->error() )  return -1 ;
   LinkIterator next(indexes) ;

   for ( Index *index_on; index_on = (Index *) next(); )
	  if ( index_on->unlock() < 0 )  return -1 ;

   return 0 ;
}


