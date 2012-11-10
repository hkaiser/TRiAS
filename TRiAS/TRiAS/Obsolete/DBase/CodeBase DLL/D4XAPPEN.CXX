// d4xappen.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int DataIndex::append()
{
   #ifdef DEBUG
	  if ( recno() != 0 )
		 e4severe( e4result, "DataIndex:append()", "append_start() was not completed.", (char *) 0 ) ;
   #endif

   int rc = lock_append() ;  if ( rc != 0 )  return rc ;

   String  str(code_base) ;

   bof_flag = eof_flag = 0 ;
   record.is_changed = 0 ;

   LinkIterator  next_index( indexes ) ;
   for ( Index *index_on; index_on = (Index *) next_index(); )
   {
	 int rc =  index_on->lock_file() ;
	 if ( rc != 0 )  return rc ;
   }

   rec_num =  reccount() + 1 ;

   #ifdef OTHER_NDX
	  LinkIterator  nxt_index( indexes ) ;
	  for ( Index *tag_on; tag_on = (Index *) nxt_index(); )
   #else
	  TagIterator tags( *this ) ;
	  Tag *tag_on ;
	  while ( tag_on = tags.next_tag() )
   #endif
   {
	  int rc = tag_on->add_calc(str, rec_num) ;
	  if ( rc < 0 || rc ==  r4locked || rc == r4unique )
	  {
		 int save_error =  code_base->error_set(0) ;

		 // Remove the keys which were just added
		 #ifdef OTHER_NDX
			LinkIteratorPrev  prev_index( indexes ) ;
			Index *index_on2 = (Index *) prev_index() ;   
			while( index_on2 != index_on) index_on2 = (Index *) prev_index() ; // start at current index 
			while ( index_on2 = (Index *) prev_index() )
			   if ( (rc = index_on2->remove_calc(str,rec_num)) < 0 )  return rc ;
		 #else
			int rc2 ;
			while ( tag_on = tags.prev_tag() )
			   if ( (rc2 = tag_on->remove_calc(str,rec_num)) < 0 )  return rc2 ;
		 #endif

		 code_base->error_set(save_error) ;
		 rec_num =  0 ;
		 return rc ;
	  }
   }

   return Data::append() ;
}

int  __export DataIndex::append_start()
{
   int rc =  flush_record() ;
   if ( rc != 0 )  return rc ;

   rec_num =  0 ;
   return 0 ;
}


