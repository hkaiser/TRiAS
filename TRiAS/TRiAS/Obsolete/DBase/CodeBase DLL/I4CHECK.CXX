// I4CHECK.C -- used to check the index files
// (C)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
}

class E4EXPORT Check
{
public:
   Check( CodeBase *, Tag *, long num_recs ) ;
  ~Check() ;

   void	 set_flag( long ) ;
   unsigned test_set( long ) ;
   int	  check_record() ;

   CodeBase *code_base ;
   Tag	  *tag ;
   unsigned char *rec_flags ;
   long	  num_recs ;

   String	old_key ;
   String	new_key ;
   long	  old_rec ;
   int	   do_compare ;  /* Do not compare the first time */
} ;

Check::Check( CodeBase *cb, Tag *tg, long n_recs ) : old_key( cb ), new_key( cb )
{
   code_base =  cb ;
   tag	   =  tg ;
   num_recs  =  n_recs ;
   do_compare =  0 ;

   rec_flags =  (unsigned char *)  m4alloc( num_recs/8 +2 ) ;
   if ( rec_flags == 0 )  code_base->error( e4memory, (char *) 0 ) ;

   old_key.set_len( tag->valuelen() ) ;
   new_key.set_len( tag->valuelen() ) ;
}

Check::~Check()
{
   if ( rec_flags != 0 )
   {
	  m4free( rec_flags ) ;
	  rec_flags =  0 ;
   }
}

void Check::set_flag( long r_num )
{
   unsigned int  low_val, set_val, high_val  ;

   if ( r_num < 1 || r_num > num_recs )  
	  e4severe( e4parm, "Tag::check(), set_flag", (char *) 0 ) ;

   low_val  =  (unsigned int) (r_num & 0x7) ;
   high_val =  (unsigned int) (r_num >> 3) ;

   set_val  =  1 << low_val ;

   rec_flags[high_val] = (unsigned char)  (set_val | (unsigned int) rec_flags[high_val]) ;
}

unsigned Check::test_set( long r_num )
{
   unsigned int  ret_val, low_val, high_val  ;

   low_val  =  (unsigned int) (r_num & 0x7) ;
   high_val =  (unsigned int) (r_num >> 3) ;

   ret_val =  (1 << low_val) &  (unsigned int) rec_flags[high_val]  ;
   return( ret_val )  ;
}

int  Check::check_record()
{
   KeyData *key_data =  tag->key() ;
   if ( key_data == 0 )  return code_base->error( e4result, (char *) 0 ) ;

   if ( key_data->rec_num < 1 ||   key_data->rec_num > num_recs )
	  return code_base->error( e4info, "Incorrect Record Number in tag:", tag->alias.ptr(), (char *) 0 ) ;

   if ( test_set(key_data->rec_num) )
	  return code_base->error( e4info, "Repeated Record Number in tag:", tag->alias.ptr(), (char *) 0 ) ;
   else
	  set_flag( key_data->rec_num ) ;

   if ( tag->index->data->go( key_data->rec_num ) < 0)  return( -1) ;
   tag->expr.key( new_key ) ;

   if (new_key.len() != (unsigned) tag->valuelen() )   // #JB950623
	  return code_base->error( e4result, "Unexpected key evaluation length:", tag->alias.ptr(), (char *) 0 ) ;

   if ( memcmp( new_key.ptr(), key_data->value, tag->valuelen() ) != 0 )
	  return code_base->error( e4result, "Tag is out of date:", tag->alias.ptr(), (char *) 0 ) ;

   if ( do_compare )
   {
	  int  rc = (*tag->cmp)( old_key.ptr(), new_key.ptr(), tag->valuelen() ) ;
	  if ( rc > 0)
		 code_base->error( e4result, "The tag is out of order:", tag->alias.ptr(), (char *) 0 ) ;
	  if ( rc == 0  &&  key_data->rec_num <= old_rec )
		 code_base->error( e4result, "Record numbers out of order for equal keys:", tag->alias.ptr(), (char *) 0 ) ;

	  if ( tag->unique() )
		 if ( rc == 0 )
			code_base->error( e4result, "Identical keys in unique key tag:", tag->alias.ptr(), (char *) 0 ) ;
   }
   else
	  do_compare =  1 ;

   old_key =  new_key ;
   old_rec =  key_data->rec_num ;
   return  code_base->error() ;
}

int Tag::check()
{
   int rc ;
   #ifndef SINGLE
	  rc =  index->data->lock_file() ;
	  if ( rc != 0 )  return rc ;
	  if ( (rc = lock()) != 0 )  return rc ;
   #endif

   if ( (rc = index->data->flush_record()) < 0 )  return -1 ;
   if ( rc != 0 )
	  return code_base->error( e4result, "Tag::check()", "DataIndex::flush_record() did not work.", (char *) 0 ) ;

   #ifdef OTHER_INDEX
	  index->data->select( index ) ;
   #else
	  index->data->select( this ) ;
   #endif

   long base_size =  index->data->reccount() ;
   if ( base_size < 0L )  return -1 ;
   if ( index->data->top() < 0 )  return( -1 ) ;

   if ( base_size == 0L )
   {
	  if ( skip( 1L ) == 0 )
		 return( 0 ) ;
	  else
		 return code_base->error( e4info, "Tag::check()", "Database is empty.", (char *) 0 ) ;
   }

   Check check( code_base, this, base_size ) ;
   if ( code_base->error() )  return -1 ;

   rc = 1 ;
   while ( rc == 1 )
   {
	  if ( (rc = check.check_record()) != 0 )  return -1 ;
	  rc =  (int) skip(1L) ;
	  if ( rc < 0 )  return -1 ;
   }

   String result( code_base ) ;
   int is_record =  1 ;
   #ifndef OTHER_INDEX
	  int do_filter =  0 ;
	  if ( filter.source.len() > 0 )  do_filter =  1 ;
   #endif

   /* Now Test for Duplication */
   for ( long on_rec = 1;  on_rec <= base_size; on_rec++)
   {
	  #ifndef OTHER_INDEX
		 if ( do_filter )
			is_record = filter.ExprTrue( result ) ;
	  #endif


	  if ( check.test_set(on_rec) )
	  {
		 if ( ! is_record )
			return code_base->error( e4info,
				  "Tag::check()", "Key should have been filtered:", alias.ptr(), (char *) 0 ) ;
	  }
	  else
	  {
		 if ( ! is_record )  continue ;

		 if ( unique() )
		 {
			if ( index->data->go(on_rec) < 0 )  break ;
			if ( expr.key( result ) < 0 )  break ;
			if ( seek( result ) == 0 )  continue ;
		 }

		 return  code_base->error( e4info, "Tag::check()", "Record is missing.", "Tag:", alias.ptr(), (char *) 0 ) ;
	  }
   }

   if ( code_base->error() )  return -1 ;


   // Now make sure the block key pointers match the blocks they point to.
   // This needs to be true for d4seek to function perfectly.

   if ( (rc = bottom()) < 0 )  return -1 ;
   if ( rc == 3 )  return 0 ;

   for(;;)
   {
	  int keys_skip = -block()->numkeys() ;
	  rc =  (int) skip( (long) keys_skip ) ;
	  if ( code_base->error() )  return -1 ;
	  if ( rc !=  keys_skip )  return  0 ;  // Top of File 

	  #ifndef CLIPPER
		 LinkIteratorPrev prev( blocks ) ;
		 if ( prev() == 0 )  return code_base->error( e4info, "Tag is corrupted:", alias.ptr(), (char *) 0 ) ;

		 Block *block_on ;
		 while( block_on = (Block *) prev() )
		 {
			if ( block_on->keypos() < block_on->numkeys() )
			{
			   KeyData *key_branch =  block_on->key() ;
			   KeyData *key_leaf   =  block()->key() ;

			   if ( memcmp( key_branch->value, key_leaf->value, valuelen()) != 0)
				  return code_base->error( e4info, "Tag is corrupted:", alias.ptr(), (char *) 0 ) ;
			   break ;
			}
		 }
		 if ( block_on == 0 )  return code_base->error( e4info, "Tag is corrupted:", alias.ptr(), (char *) 0 ) ;
	  #endif
   }
}

void mark_block( char *block_list, long position )
{
   long b_pos = position / 8 ;
   int i_pos = int(position % 8) ;
   block_list[b_pos] |= (0x80 >> i_pos) ;
}

int check_block( char *block_list, long position )
{
   long b_pos = position / 8 ;
   int i_pos = int(position % 8) ;
   return (block_list[b_pos] & (0x80 >> i_pos) ) ;
}

// checks that all blocks in the file are on free list or are being used
int  Index::check_blocks()
{
   #ifdef NDX
	  return 0 ;   // NDX version doesn't use free list
   #else
	  long num_blocks = file.len() / block_rw_len() ;
	  #ifdef CLIPPER
		 int block_inc = block_rw_len() ;
	  #else
		 int block_inc = block_rw_len() / i4multiply ;
	  #endif

	  char *block_check = (char *)m4alloc( num_blocks/8 + 1 ) ;
	  if ( block_check == 0 )
		 e4severe( e4memory, "Not enough memory to check index file", (char *) 0 ) ;

	  #ifdef CLIPPER
		 Index *tag_on = this ;
		  {   // this brace only so that it matches the one below!
	  #else
		 LinkIterator tag_it( tags ) ;
		 for( Tag *tag_on; tag_on = (Tag *) tag_it(); )
		 {
	  #endif
		 tag_on->flush() ;
		 tag_on->bottom() ;
		 long last_rec = tag_on->recno() ;

		 tag_on->top() ;

		 for(;;)
		 {
			LinkIteratorPrev prev( tag_on->blocks ) ;

			Block *block_on ;
			while( block_on = (Block *) prev() )
				mark_block( block_check, block_on->fileblock() / block_inc ) ;
			if( tag_on->recno() == last_rec ) break ;
			tag_on->skip( 1L ) ;
		 }
	  }

	  // add all free blocks to the list
	  #ifdef CLIPPER
		 long cur_block = header.eof ;
		  int i4mult2 = 1 ;
		  long start_block = 1 ;
	  #else
		 long cur_block = header.free_list ;
		  int i4mult2 = i4multiply ;
		  long start_block = 2 + header.num_tags ;
	  #endif

	  long next_bl ;
	  unsigned len =  sizeof(cur_block) ;
	  int rc =  file.read( cur_block*i4mult2, StrLen((char *)&next_bl, sizeof(next_bl)), &len) ;
	  if ( rc < 0 )
		 cur_block = 0 ;	// skip add checking

	  while( cur_block != 0 && len == sizeof( cur_block ) )  // while blocks still left
	  {
		 cur_block = next_bl ;
		 mark_block( block_check, cur_block / block_inc ) ;
		 len =  sizeof(next_bl) ;
		 rc =  file.read( cur_block*i4mult2, StrLen((char *)&next_bl, sizeof(cur_block)), &len) ;
		 if ( rc < 0 )  len = 0 ;
	  }

	  for ( long i = start_block; i < num_blocks; i++ )
		  if ( !check_block( block_check, i ) ) rc = -1 ;

	  m4free( block_check ) ;
	  return rc ;
   #endif
}

int  DataIndex::check()
{
   int rc ;

   #ifdef OTHER_INDEX
	  LinkIterator next( indexes ) ;
	  Index *prev_selected =  index_selected() ;
	  for( Index *index_on; index_on = (Index *) next(); )
	  {
		 if ( (rc = index_on->check()) != 0 )
		 {
			select( prev_selected ) ;
			return  rc ;
		 }
	  }
	  select( prev_selected ) ;
   #else
	  // check the tags
	  TagIterator next( *this ) ;
	  Tag *prev_selected =  tag_selected() ;

	  for( Tag *tag_on; tag_on = next.next_tag(); )
		 if ( (rc = tag_on->check()) != 0 )
		 {
			select( prev_selected ) ;
			return  rc ;
		 }

	  // check the indexes
	  LinkIterator next_i( indexes ) ;
	  for( Index *index_on; index_on = (Index *) next_i(); )
		 if ( (rc = index_on->check_blocks()) < 0 )
		 {
			code_base->error( e4index, "i4check: Blocks unaccounted for were found in index file", (char *) 0 ) ;
			select( prev_selected ) ;
			return rc ;
		 }

   select( prev_selected ) ;
   #endif

   return 0 ;
}
