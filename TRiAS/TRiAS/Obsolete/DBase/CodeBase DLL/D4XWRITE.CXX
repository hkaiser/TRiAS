// d4xwrite.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int DataIndex::write( long rec )
{
   int rc =  write_keys( rec ) ;
   if ( rc != 0 )  return rc ;

   return Data::write(rec) ;
}

int DataIndex::write_keys( long rec )
{
   if ( code_base->error() )   return -1 ;
   bof_flag = eof_flag = 0 ;
   record.is_changed = 0 ;

   int rc =  lock(rec) ;  if ( rc != 0 )  return rc ;

   if ( indexes.nlinks() > 0 )
   {
	  if ( read_old( recno() ) < 0 )  return -1 ;
	  if ( record_old == record )  return 0 ;
   }

   String old_key( code_base), new_key( code_base) ;

   LinkIterator  next_index( indexes ) ;
   for ( Index *index_on; index_on = (Index *) next_index(); )
   {
	 rc =  index_on->lock_file() ;
	 if ( rc != 0 )  return rc ;
   }

   #ifdef OTHER_NDX
	  LinkIterator next_index_ag( indexes ) ;
	  for (Index *tag_on ;tag_on = (Index *) next_index_ag(); )
   #else
	  TagIterator tags( *this ) ;
	  for ( Tag *tag_on; tag_on = tags.next_tag(); )
   #endif
   {
	  int old_key_added = 1, add_new_key = 1 ;

	  tag_on->expr.key( new_key ) ;
	  char *old_buffer =  record.p ;  record.p =  record_old.p ;
	  rc = tag_on->expr.key( old_key ) ;
	  if ( rc < 0 )  return rc ;


	  #ifndef OTHER_NDX
		 String result( code_base ) ;
		 if ( tag_on->filter.source.len() )
		 {
			result = old_key ;
			int filter_type =  tag_on->filter.vary( result ) ;  if ( filter_type < 0 )  return -1 ;
			#ifdef DEBUG
			   if ( filter_type != t4log )  e4severe( e4result, "Reindex::supply_keys", (char *) 0 ) ;
			#endif
			old_key_added = *( int *)result.ptr() ;
		 }
	  #endif

	  record.p =  old_buffer ;

	  #ifndef OTHER_NDX
		 if ( tag_on->filter.source.len() )
		 {
			result = new_key ;
			int filter_type =  tag_on->filter.vary( result ) ;  if ( filter_type < 0 )  return -1 ;
			#ifdef DEBUG
			   if ( filter_type != t4log )  e4severe( e4result, "Reindex::supply_keys", (char *) 0 ) ;
			#endif
			add_new_key = *(int *)result.ptr() ;
		 }
	  #endif

	  if ( old_key_added == add_new_key )
		 if ( new_key == old_key )
			 continue ;

	  rc = 0 ;   // reset the return code
	  if ( old_key_added )
		 rc =  tag_on->remove(old_key,rec) ;

	  if ( rc == 0 )
	  {
		  if ( add_new_key )
			 rc =  tag_on->add(new_key,rec) ;
		  if ( rc < 0 || rc == r4unique )
		  {
			 int save_error =  code_base->error_set(0) ;
			 if ( tag_on->add(old_key,rec) < 0 )  return -1 ;
			 code_base->error_set(save_error) ;
		 }
	  }

	  #ifdef DEBUG
		 if ( rc == r4locked )  e4severe( e4result, "DataIndex::write()", (char *) 0 ) ;
	  #endif

	  if ( rc < 0  ||  rc == r4unique )
	  {
		 #ifndef OTHER_NDX
			tag_on  = tags.prev_tag() ;
		 #endif

		 int save_error =  code_base->error_set(0) ;

		 // Remove the keys which were just added

		 #ifdef OTHER_NDX
			LinkIteratorPrev  prev_index( indexes ) ;
			Index *tag_on2 = (Index *) prev_index() ;
			while( tag_on2 != tag_on) tag_on2 = (Index *) prev_index() ; // start at current index 
			while ( tag_on2 = (Index *) prev_index() )
		 #else
			while ( tag_on = tags.prev_tag() )
		 #endif
		 {
			char *old_buffer =  record.p ;  record.p =  record_old.ptr() ;
			#ifdef OTHER_NDX
			   int rc2 = tag_on2->remove_calc(new_key,rec) ;
			#else
			   int rc2 = tag_on->remove_calc(new_key,rec) ;
			#endif
			record.p =  old_buffer ;
			if ( rc2 < 0 )  return -1 ;

			#ifdef OTHER_NDX
			   if ( tag_on2->add_calc(new_key,rec) < 0 )  return -1 ;
			#else
			   if ( tag_on->add_calc(new_key,rec) < 0 )  return -1 ;
			#endif
		 }
		 code_base->error_set(save_error) ;
		 return rc ;
	  }
   }
   return 0 ;
}
