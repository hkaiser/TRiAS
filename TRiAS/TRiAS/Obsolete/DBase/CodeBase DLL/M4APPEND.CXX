// m4append.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

DataMemo::append()
{
   // 0. Lock record count bytes
   // 1. Update Memo File
   // 2. Update Index File and Data File

   int rc =  lock_append() ;  if ( rc != 0 )  return rc ;

   for ( int i = 0; i < n_memo_fields; i++ )
   {
	  MField *mfield =  (MField *) memo_fields[i] ;
	  mfield->is_changed =  0 ;
	  if ( mfield->contents.len() > 0 )
	  {
		 long new_id =  0L ;
		 rc =  memo_file.write( &new_id, mfield->contents ) ;
		 if ( rc != 0 )  return rc ;
		 mfield->id( new_id ) ;
	  }
   }

   return DataIndex::append() ;
}

int  DataMemo::append_start( int use_memo_entries )
{
   int rc =  flush_record() ;
   if ( rc != 0 )  return rc ;

   if ( recno() <= 0 )  use_memo_entries =  0 ;

   if ( use_memo_entries )
   {
	  // Read in the current memo entries of the current record
	  if ( (rc = lock(recno())) != 0 )  return rc ;

	  char *save_ptr =  record.p ;
	  record.p =  record_old.p ;

	  if ( Data::go( recno() ) < 0 )
	  {
		 record.p =  save_ptr ;
		 return -1 ;
	  }

	  for ( int i = 0; i < n_memo_fields; i++ )
	  {
		 MField *mfield =  (MField *) memo_fields[i] ;
		 if ( memo_file.read( mfield->id(), mfield->contents ) < 0 )
		 {
			record.p =  save_ptr ;
			return -1 ;
		 }
	  }
	  record.p =  save_ptr ;
   }

   for ( int i = 0; i < n_memo_fields; i++ )
	  ((MField *) memo_fields[i])->id(0) ;

   rec_num =  0 ;
   return 0 ;
}

