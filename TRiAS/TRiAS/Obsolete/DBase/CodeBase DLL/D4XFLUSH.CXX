// d4xflush.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int DataIndex::flush_all()
{
   int rc = flush_record() ;  if ( rc != 0 )  return rc ;

   #ifdef OTHER_NDX
	  LinkIterator next( indexes ) ;
	  Index *tag ;
	  while ( tag =  (Index *) next() )
   #else
	  TagIterator tags( *this ) ;
	  Tag *tag ;
	  while ( tag = tags.next_tag() )
   #endif
   {
	  rc = tag->flush() ;
	  if ( rc != 0 )  return rc ;
   }
	  
   return 0 ;
}

int DataIndex::flush_record()
{
   if ( code_base->error() )  return -1 ;

   if ( recno() <= 0 || eof() )
   {
	  for ( int i = 0; i < n_memo_fields; i++ )
		 memo_fields[i]->reset() ;
	  record.is_changed = 0 ;
	  return 0 ;
   }

   if ( record.is_changed )
   {
	  int rc =  write( recno() ) ;
	  if ( rc != 0 )  return rc ;
   }

   for ( int i = 0; i < n_memo_fields; i++ )
	  memo_fields[i]->reset() ;

   return 0 ;
}
