// m4write.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
}

int __export DataMemo::validate_memo_ids()  // Make the memo file entries current
{
   int rc ;
   if ( recno() > 0 )
   {
	  rc =  lock(recno()) ;
	  if ( rc != 0 )  return rc ;
   }
   if ( read_old(recno()) < 0 )  return -1 ;

   for ( int i = 0; i < n_memo_fields; i++ )
   {
	  #ifdef DEBUG
		 if ( memo_fields[i]->Field::len() != 10 )
			e4severe( e4result, "DataMemo::validate_memo_ids()", (char *) 0);
	  #endif
	  char *to_ptr  =  memo_fields[i]->Field::ptr() ;

	  char *save_ptr =  record.p ;
	  record.p =  record_old.p ;
	  char *from_ptr=   memo_fields[i]->Field::ptr() ;
	  record.p =  save_ptr ;

	  memcpy( to_ptr, from_ptr, 10 ) ;
   }
   return 0 ;
}

int DataMemo::write( long rec )
{
   // 0. Validate memo id's
   // 1. Update Keys
   // 2. Update Memo Information
   // 3. Update Data File

   int rc =  validate_memo_ids() ;  if ( rc != 0 )  return rc ;
   rc =  write_keys(rec) ;  if ( rc != 0 )  return rc ;

   int final_rc =  0 ;
   // First cycle through the fields to be flushed
   for ( int i = 0; i < n_memo_fields; i++ )
   {
	  if ( (rc = memo_fields[i]->flush()) < 0 )  return -1 ;
	  if ( rc > 0 )  final_rc =  rc ;
   }

   if ( Data::write( rec ) < 0 )  return -1 ;
   return final_rc ;
}

int  MemoFile::write( long *memo_id_ptr, Str& str )
{
   #ifdef DEBUG
	  if ( memo_id_ptr == 0 )
		 e4severe( e4parm, "MemoFile::write()", (char *) 0 ) ;
   #endif

   ChainEntry new_entry(this) ;
   new_entry.block_no =  *memo_id_ptr ;

   int  str_written =  0 ;
   if ( str.len() == 0 )  str_written =  1 ;

   // Initialize information about the old memo entry
   MemoBlock old_memo_block ;
   if ( new_entry.block_no <= 0L )
   {
	  if ( str_written )
	  {
		 *memo_id_ptr =  0L ;
		 return 0 ;
	  }
	  new_entry.num =  0 ;
   }
   else
   {
	  long old_memo_pos =  new_entry.block_no * block_size ;
	  file.read( old_memo_pos, old_memo_block) ;
	  new_entry.num  = ((unsigned)old_memo_block.num_chars + block_size-1)/ block_size ;
   }

   int  str_num_blocks =  (str.len()+2*sizeof(short)+sizeof(long)+
						  block_size-1)  / block_size ;

   if ( new_entry.num != str_num_blocks  &&  data != 0 )
   {
	  int  rc =  data->lock_append() ;
	  if ( rc != 0  ) return rc ;
   }

   if ( new_entry.num >= str_num_blocks  &&  ! str_written )
   {
	  *memo_id_ptr =  new_entry.block_no + new_entry.num - str_num_blocks ;
	  if ( dump( *memo_id_ptr, str ) < 0 )  return -1 ;
	  str_written =  1 ;
	  if ( new_entry.num == str_num_blocks )  return 0 ;
	  new_entry.num -=  str_num_blocks ;
   }

   // Initialize 'chain'
   ChainEntry cur(this) ;
   ChainEntry prev(this) ;

   for(;;)
   {
	  if ( code_base->error() )  return -1 ;

	  prev.flush() ;
	  memcpy( &prev, &cur, sizeof(prev) ) ;

	  if ( new_entry.block_no > 0  &&  prev.next > new_entry.block_no )
	  {
		 // See if the new entry fits in here
		 memcpy( &cur, &new_entry, sizeof(cur) ) ;
		 new_entry.block_no =  0 ;
		 cur.next  =  prev.next ;
		 prev.next =  cur.block_no ;
		 cur.to_disk =  prev.to_disk =  1 ;
	  }
	  else
		 cur.skip() ;

	  // See if the entries can be combined !
	  if ( prev.block_no + prev.num == cur.block_no  &&  prev.num != 0 )
	  {
		 // 'cur' becomes the combined groups.
		 prev.to_disk =  0 ;
		 cur.to_disk  =  1 ;

		 cur.block_no =  prev.block_no ;
		 if ( cur.num >= 0 )
			cur.num  +=  prev.num ;
		 prev.num  =  0 ;
	  }

	  if ( str_written )
	  {
		 if ( new_entry.block_no == 0 )
		 {
			prev.flush() ;
			cur.flush() ;
			return 0 ;
		 }
	  }
	  else  // 'str' is not yet written, try the current entry
	  {
		 if ( cur.next == -1 )  // End of file
			cur.num =  str_num_blocks ;

		 if ( cur.num >= str_num_blocks )
		 { 
			cur.num -=  str_num_blocks ;
			dump( *memo_id_ptr =  cur.block_no, str ) ;
			if ( cur.next == -1 ) // if end of file
			{
			   // For dBASE IV compatibility
			   long  file_len  =  file.len() ;
			   long  extra_len =  block_size -  file_len % block_size ;
			   if ( extra_len != block_size )
				  file.set_len( file_len+extra_len ) ;
			}

			cur.block_no += cur.num ;
			str_written =  1 ;

			if ( cur.num == 0 )
			{
			   if ( cur.next == -1 ) // End of file
				  prev.next =  cur.block_no + str_num_blocks ;
			   else
				  prev.next =  cur.next ;
			   prev.to_disk =  1 ;
			   cur.to_disk =  0 ;
			}
			else
			   cur.to_disk =  1 ;
		 }
	  }
   }
}
