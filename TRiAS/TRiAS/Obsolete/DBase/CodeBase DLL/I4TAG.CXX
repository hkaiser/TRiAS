// i4tag.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <io.h>
#include <string.h>
}

// 't4num ...' routine returns:
//   -1	  -  Data	 <   Search
// r4success -  Data	==   Search
// r4after   -  Data	 >   Search 

extern "C" {			// #JB920618
/* static*/  TAG_CMP_FUNC t4cmp_doub( const void *data_ptr, const void *search_ptr, size_t ) // #JB940923 static deaktiviert
{
   #ifdef PORTABLE
	  double d1, d2 ;
	  memcpy( &d1, data_ptr, sizeof(double) ) ;
	  memcpy( &d2, search_ptr, sizeof(double) ) ;
	  double dif =  d1 - d2 ;
   #else
	  double dif =  *((double *)data_ptr) - *((double *)search_ptr) ;
   #endif

   if ( dif > e4accuracy )  return r4after ;
   if ( dif < -e4accuracy ) return -1 ;
   return r4success ;
}

/* static */ TAG_CMP_FUNC t4desc_cmp_doub( const void *data_ptr, const void *search_ptr, size_t ) // #JB940923 static deaktiviert
{
   return -1 * t4cmp_doub( data_ptr, search_ptr, 0 ) ;
}

/* static */ TAG_CMP_FUNC t4desc_bcd_cmp( const void *data_ptr, const void *search_ptr, size_t ) // #JB940923 static deaktiviert
{
   return -1 * c4bcd_cmp( data_ptr, search_ptr, 0 ) ;
}

/* static*/  TAG_CMP_FUNC t4desc_memcmp( const void *data_ptr, const void *search_ptr, size_t len ) // #JB940923 static deaktiviert
{
   return -1 * memcmp( data_ptr, search_ptr, len ) ;
}
}	   // extern "C"

static void t4str_to_date_mdx( Str& result, Str& input )
{
   Date  dt( input.ptr() ) ;
   if ( result.set_len(sizeof(double)) < 0 )  e4severe( e4result, (char *) 0 ) ;
   double d =  dt.format_mdx() ;
   memcpy( result.ptr(), &d, sizeof(double) ) ;
}

static void t4no_change( Str& result, double d )
{
   if ( result.set_len(sizeof(double)) < 0 )  e4severe( e4result, (char *) 0 ) ;
   memcpy( result.ptr(), &d, sizeof(double) ) ;
}

static void t4no_change( Str& result, Str& input )
{
   if ( result.assign(input) < 0 )  e4severe( e4result, (char *) 0 ) ;
}

__export Tag::Tag( Index *index_ptr ) : expr( index_ptr->data ), filter(index_ptr->data)
{
   index =  index_ptr ;   
   code_base =  index->data->code_base ;
   unique_error =  code_base->default_unique_error ;
		#ifdef __DLL__
		   cmp = /* (T4CMP_ROUTINE*) */ dll_memcmp ;  // #JB920618; #JB940923 --> typecast aufgehoben
		#else
		   #ifdef __ZTC__
			  cmp =  zc_memcmp ;
		   #else
			 cmp =  memcmp ;
		   #endif
		#endif
   root_write = 0 ;
}

__export Tag::~Tag()
{
   #ifdef DEBUG
	  if ( blocks.last() != 0  ||  saved.last() != 0 )  e4severe( e4info, "Tag::~Tag", (char *) 0 ) ;
   #endif
}

void *Tag::operator new( size_t )
{
   return 0 ;
}

void *Tag::operator new( size_t, void *memory )
{
   return memory ;
}

void Tag::operator delete( void* p )
{
   Tag *tag_ptr = (Tag *) p ;
   tag_ptr->index->tags.remove( (Link *) p ) ;
}

int Tag::add( Str& str, long rec )
{
   if ( code_base->error() )  return -1 ;
   void *key_info =  str.ptr() ;

   int rc =  go( str, rec ) ;   if ( rc < 0 )  return -1 ;
   if ( rc == 0 )
   {
	  code_base->error( e4unique, index->file.name.ptr(), (char *) 0 ) ;
	  return e4unique ;
   }
   if ( unique() && rc == r4found )
   {
	  switch ( code_base->default_unique_error )
	  {
		 case e4unique:
		 {
			return code_base->error( e4unique, index->file.name.ptr(), (char *) 0 ) ;
		 }

		 case r4unique:
		 {
			return r4unique ;
		 }

		 case r4unique_continue:
		 {
			return r4unique_continue ;
		 }
	  }
   }

   index->header.version =  index->version_old+1 ;

   Block *old_block =  block() ;
   long  old_file_block =  0 ;

   for(;;)
   {
	  if ( old_block == 0 )
	  {
		 // Must create a new root block
		 long  extend_block =  index->extend() ;
		 if ( extend_block < 0 )  return (int) extend_block ;

		 Block *root_block =  new(*this, extend_block) Block ;
		 if ( root_block == 0 )  return -1 ;

		 blocks.add( root_block ) ;

		 root_block->insert( key_info, old_file_block ) ;
		 root_block->insert( key_info, rec ) ;
		 root_block->n_keys-- ;
		 header.root =  root_block->fileblock() ;
		 root_write  =  1 ;
		 return 0 ;
	  }

	  if ( old_block->room() )
	  {
		 old_block->insert( key_info, rec ) ;
		 return 0 ;
	  }
   
	  blocks.pop() ;

	  int  is_branch  =  old_block->leaf()  ?  0 : 1 ;

	  // NNNNOOOO  N - New, O - Old
	  // The new block's end key gets added to the block just up
	  Block *new_block=  split( old_block ) ; 
	  if ( new_block == 0 )  return -1 ;

	  saved.add( new_block ) ;

	  new_block->n_keys -=  is_branch ;
	  if ( new_block->keypos() < (new_block->numkeys()+is_branch) )
		 new_block->insert( key_info, rec ) ;
	  else
		 old_block->insert( key_info, rec ) ;

	  // Now add to the block just up
	  new_block->go( new_block->lastpos() ) ;
	  key_info =  new_block->key()->ptr() ;
	  rec	  =  new_block->fileblock() ;

	  old_file_block =  old_block->fileblock() ;
	  if ( old_block->flush() < 0 )  return -1 ;
	  delete old_block ;
	  old_block =  (Block *) blocks.last() ;
   }
}

Tag::add_calc( Str& str, long rec )
{
   if ( filter.source.len() )
   {
	  String result( code_base ) ;
	  result = str ;
	  int filter_type =  filter.vary( result ) ;  if ( filter_type < 0 )  return -1 ;
	  #ifdef DEBUG
		 if ( filter_type != t4log )  e4severe( e4result, "Reindex::supply_keys", (char *) 0 ) ;
	  #endif
	  int *is_true =  (int *) result.ptr() ;
	  if ( ! *is_true )  return 0 ; //r4filtered ;
   }
   expr.key( str ) ;
   return add( str, rec ) ;
}

Block *Tag::block()
{
   #ifdef DEBUG
	  if ( blocks.last() == 0 )  e4severe( e4info, "Tag::block", (char *) 0 ) ;
   #endif
   return (Block *) blocks.last() ;
}

int Tag::bottom()
{
   int rc = lock() ;  if ( rc != 0 )  return rc ;  // Error or lock
   if ( up_to_root() < 0 )  return -1 ;

   block()->go_eof() ;
   do
   {
	  if ( (rc = down()) < 0 )  return -1 ;
	  block()->go_eof() ;
   } while ( rc == 0 ) ;

   Block *block_on =  block() ;
   if ( block_on->key_on > 0 )
	  block_on->key_on =  block_on->n_keys-1 ;
   #ifdef DEBUG
	  if ( block_on->key_on < 0 )  e4severe( e4info, "Tag::bottom", (char *) 0 ) ;
   #endif

   return 0 ;
}

// Returns  1 - Cannot move down; 0 - Success; -1 Error
int Tag::down()
{
   if ( code_base->error() )  return -1 ;

   long block_down ;

   Block *block_on =  (Block *) blocks.last() ;

   if ( block_on == 0 )	// Read the root block
   {
	  if ( header.root <= 0L )
		 if ( index->file.read( header_offset,
			   StrLen(&header.root,sizeof(header.root))) < 0 ) return -1 ;
	  block_down =  header.root ;
   }
   else
   {
	  if ( block_on->leaf() )  return 1 ;
	  block_down =  block_on->blockdown() ;
	  #ifdef DEBUG
		 if ( block_down <= 0L )  e4severe( e4info, "Tag::down", "Illegal file block reference", (char *) 0 ) ;
	  #endif
   }

   // Get memory for the new block
   Block *pop_block =  (Block *) saved.pop() ;
   Block *new_block =  pop_block ;
   if ( new_block == 0 )	new_block =  new(*this,block_down) Block() ;
   if ( new_block == 0 )	return -1 ;
   blocks.add( new_block ) ;

   if ( pop_block == 0  ||  new_block->fileblock() != block_down )
   {
	  if ( new_block->flush() < 0 )  return -1 ;
	  if ( index->file.read( i4multiply*block_down,
			StrLen(&new_block->n_keys,new_block->len())) < 0 ) return -1 ;

	  new_block->file_block =  block_down ;
	  Block *on_block ;
	  while ( on_block = (Block *) saved.pop())
	  {
		 if ( on_block->flush() < 0 )  return -1 ;
		 delete( on_block ) ;
	  }
   }

   new_block->key_on =  0 ;
   return 0 ;
}

Tag::eof()
{
   return block()->eof() ;
}

int Tag::flush()
{
   if ( code_base->error() )  return -1 ;
   LinkIterator next_saved(saved) ;

   Block *block_on ;
   while ( block_on = (Block *) next_saved() )
	  if ( block_on->flush() < 0 )  return -1 ;

   LinkIterator next_block(blocks) ;

   while ( block_on = (Block *) next_block() )
	  if ( block_on->flush() < 0 )  return -1 ;

   if ( root_write )
   {
	  if ( index->file.write( header_offset, 
			   StrLen(&header.root,sizeof(header.root)) ) < 0 )  return -1 ;
	  root_write =  0 ;
   }

   return 0 ;
}

int Tag::free()
{
   while ( up() == 0 ) ;
   return free_saved() ;
}

int Tag::free_saved()
{
   if ( flush() < 0 )  return -1 ;
   Block *block_on ;
   while ( block_on = (Block *) saved.pop() )
   {
	  if ( block_on->flush() < 0 )  return -1 ;
	  delete block_on ;
   }
   return 0 ;
}

int Tag::go( Str& str, long rec_num )
{
   if ( code_base->error() )  return -1 ;

   int  len_compare =  valuelen() ;
   #ifdef DEBUG
	  if ((unsigned)  len_compare != str.len() )  e4severe( e4parm, "Tag::go", (char *) 0 ) ; // #JB950623
   #endif

   int rc = seek( str ) ;
   if ( rc != 0 )  return rc ;

   for(;;)
   {
	  if ( recno() == rec_num )  return 0 ;
	  if ( recno() > rec_num )  return r4found ;

	  rc =  (int) skip(1L) ;
	  if ( rc == -1 )  return -1 ;
	  if ( rc == 0 )
	  {
		 block()->go_eof() ;
		 return r4found ;
	  }

	  if ( (*cmp)( key()->ptr(), str.ptr(), len_compare ) != 0 )  return r4found ;
   }
}

Tag::init( Index& index_parm, TAG_INFO& tag_info, long lock_position )
{
   if ( code_base->error() )  return -1 ;

   lock_pos =  lock_position ;
   index = &index_parm ;
   header_offset =  tag_info.header_pos * 512 ;

   FileSeqRead seqread ;
   char  buffer[1024] ;  StrLen buffer_str( buffer, sizeof(buffer) ) ;
   seqread.init( index->file, header_offset, buffer_str ) ;
   if ( seqread.read( StrLen(&header,sizeof(header))) < 0 )  return -1 ;
   header.root =  -1 ;

   alias =  StrLen( tag_info.tag, sizeof(tag_info.tag) ) ;
   alias.trim() ;
   alias.upper() ;

   if ( index->data )
   {
	  expr.source.set_len( 220 ) ;
	  seqread.read( expr.source ) ;
	  expr.source.trim() ;
	  expr.source.set_max( expr.source.len() ) ;
	  expr.data =  index->data ;

	  String result( code_base ) ;
	  int key_type =  expr.key( result ) ;
	  if ( key_type < 0 )  return -1 ;

	  if ( header.type	  !=  key_type ||
		   (unsigned) header.value_len   !=  result.len() )  // #JB950623
		 return  code_base->error( e4index, index->file.name.ptr(), (char *) 0 ) ;

	  init_seek_conv(key_type) ;

	  char garbage_buffer[GARBAGE_LEN] ;
	  seqread.read( StrLen(garbage_buffer,sizeof(garbage_buffer)) ) ;
	  filter.source.set_len( 220 ) ;
	  if ( seqread.read( filter.source ) < 0 )  return -1 ;
	  filter.source.trim() ;
	  filter.source.set_max( filter.source.len() ) ;

	  if ( filter.source.len() > 0 )
	  {
		 key_type =  filter.key( result ) ;  if ( key_type < 0 )  return key_type ;
		 if ( key_type != 'L' )
			return code_base->error( e4index, index->file.name.ptr(), (char *) 0 ) ;
	  }
   }
   return 0 ;
}

void Tag::init_seek_conv(int key_type)
{
   int is_desc =  header.type_code & 8 ;

   switch( key_type )
   {
	  case t4num_bcd:
	  { 
		 if ( is_desc )
			cmp =  /* (T4CMP_ROUTINE*) */ t4desc_bcd_cmp ; // #JB920618 #JB940923 --> typecast aufgehoben
		 else
			cmp =  /* (T4CMP_ROUTINE*) */ c4bcd_cmp ;	  // #JB920618 #JB940923 --> typecast aufgehoben
		 stok=  c4stob ;
		 dtok=  c4dtob ;
	  }
		 break ;

	  case t4date_doub:
	  {
		 if ( is_desc )
			cmp = /* (T4CMP_ROUTINE*) */ t4desc_cmp_doub ; // #JB920618 #JB940923 --> typecast aufgehoben
		 else
			cmp = /* (T4CMP_ROUTINE*) */ t4cmp_doub ;	  // #JB920618 #JB940923 --> typecast aufgehoben
		 stok=  t4str_to_date_mdx ;
		 dtok=  t4no_change ;
	  }
		 break ;

	  case t4str:
	  {
		 if ( is_desc )
			cmp = /* (T4CMP_ROUTINE*) */ t4desc_memcmp ;   // #JB920618 #JB940923 --> typecast aufgehoben
		 else
			#ifdef __DLL__
			   cmp = /* (T4CMP_ROUTINE*) */ dll_memcmp ;   // #JB920618 #JB940923 --> typecast aufgehoben
			#else
				#ifdef __ZTC__
				   cmp =  zc_memcmp ;
				#else
				  cmp =  memcmp ;
				#endif
			#endif
		 stok=  t4no_change ;
		 dtok=  0 ;
	  }
		 break ;

	  default:
	  { 
		 e4severe( e4info, "Invalid key type in index file", (char *) 0 ) ;
	  }
   }
}

KeyData *Tag::key()
{
   return block()->key() ;
}

int Tag::lock()
{
   if ( code_base->error() )  return -1 ;
   if ( index->file_locked )  return 0 ;
   if ( index->tag_locked == this )  return 0 ;

   if ( index->tag_locked != 0 )
	  if ( index->unlock() < 0 )  return -1 ;

   int rc = index->file.lock( lock_pos, 1L ) ;
   if ( rc != 0 )  return rc ; // Error or locked

   index->tag_locked =  this ;
   if ( index->version_check() < 0 )  return -1 ;
   return 0 ;
}

int Tag::position( double pos ) // 'pos' is an percentage, positioning is approximate.
{
   int rc =  lock() ;   if ( rc != 0 )  return rc ; // Error or locked

   if ( up_to_root() < 0 )  return -1 ;

   for(;;)
   {
	  #ifdef DEBUG
		 if ( pos < 0.0 || pos > 1.0 )  // Could be caused by rounding error ?
			e4severe( e4parm, "Tag::position", "Illegal position", (char *) 0 ) ;
	  #endif

	  Block *block_on =  block() ;
	  int n =  block_on->numkeys() + 1 ;

	  if ( block_on->leaf() ) n-- ;

	  int final_pos =  int(n * pos) ;
	  if ( final_pos == n )  final_pos-- ;
   
	  block_on->go( final_pos ) ;
	  pos =  pos*n - final_pos ;

	  if ( (rc = down()) < 0 )  return -1 ;
	  if ( rc == 1 )  return 0 ;
   }
}

double Tag::position()
{
   LinkIteratorPrev prev( blocks ) ;

   double pos = .5 ;
   for ( Block *block_on; block_on = (Block *) prev(); )
   {
	  int n =  block_on->numkeys()+1 ;
	  if ( block_on->leaf() )  n-- ;

	  pos =  (block_on->keypos()+pos)/n ;
   }
   return pos ;
}

long __export Tag::recno()
{
   Block *block_on =  (Block *) blocks.last() ;
   if ( block_on == 0 )  return -2L ;
   if ( ! block_on->leaf())  return -2L ;

   return block_on->recno() ;
}

Tag::remove() // Remove the current key
{
   if ( code_base->error() )  return -1 ;
   index->header.version =  index->version_old+1 ;

   void *new_key_info =  0 ;

   LinkIteratorPrev  prev( blocks ) ;
   for ( Block *block_on; block_on = (Block *) prev(); )
   {
//	#ifdef DEBUG
//	   if ( block_on->numkeys() <= 0 )  e4severe( e4info, "Tag::remove", "Unexpected block data", (char *) 0 ) ;
//	#endif

	  if ( new_key_info == 0 )  // then delete entry
	  {
		 if ( block_on->lastpos() == 0 )
		 {
			if ( block_on == blocks.first() )
			{
			   // Root Block, do not delete
			   block_on->key_on =  0 ;
			   memset( &block_on->n_keys, 0, index->block_rw_len() ) ;
			}
			else
			{
			   // This block is to be deleted
			   blocks.remove( block_on ) ;
			   if ( index->shrink(block_on->fileblock()) < 0 )  return -1 ;
			   delete block_on ;
			}
		 }
		 else
		 {
			int  less_than_last =  0 ;
			if ( block_on->keypos() < block_on->lastpos() )  
			   less_than_last =  1 ;
			block_on->remove() ;
			if ( less_than_last )  return 0 ;

			// On last entry
			block_on->go( block_on->lastpos() ) ;
			new_key_info =  block_on->key()->ptr() ;
		 }
	  }
	  else  // Adjust entry
	  {
		 if ( block_on->keypos() < block_on->lastpos() )
		 {
			// Just change the entry
			block_on->changed = 1 ;
			memcpy( block_on->key()->ptr(), new_key_info, valuelen() ) ;
			return 0 ;
		 }
	  }
   }
   return 0 ;
}

Tag::remove( Str& str, long rec )
{
   int rc =  Tag::go( str, rec ) ;  if ( rc < 0 )  return rc ;
   if ( rc != 0 )  return r4entry ;

   return remove() ;
}

Tag::remove_calc( Str& str, long rec )
{
   expr.key( str ) ;
   return remove( str, rec ) ;
}

Tag::seek( Str& str )
{
   int rc ;
   if ( (rc = lock()) != 0 )  return rc ;  // Not locked or error

   #ifdef DEBUG
	  if ( str.len() > (unsigned) valuelen()  ||  
	       str.len() != (unsigned) valuelen() && 
	       type() != t4str ) // #JB950623
		 e4severe( e4parm, "Tag::seek", (char *) 0 ) ;
   #endif

   /* Do initial search, moving up only as far as necessary */
   if ( up_to_root() < 0 )  return -1 ;

   for(;;) // Repeat until found
   {
	  Block *block_on =  (Block *) blocks.last() ;
	  #ifdef DEBUG
		 if ( block_on == 0 )  e4severe( e4info, "Tag::seek", (char *) 0 ) ;
	  #endif

	  int rc = block_on->seek( str ) ;
	  if ( block_on->leaf() )  return rc ;

	  if ( down()  < 0 )  return -1 ;
   }
}

long __export Tag::skip( long num_skip )
{
   int rc =  lock() ;   if ( rc != 0 )  return rc ; // Error or locked

   long num_left =  num_skip ;
   int sign ;
   if ( num_skip < 0)
	  sign = -1 ;
   else
	  sign = 1 ;

   rc = 0 ;

   Block *block_on =  block() ;
   if ( block_on == 0 )
	  if ( (rc =  top()) < 0 )  return -num_skip ;

   #ifdef DEBUG
	  if ( ! block_on->leaf() )  e4severe( e4info, "Tag::skip", (char *) 0 ) ;
   #endif

   for(;;)
   {
	  while ( (rc = down()) == 0 )
		 if ( sign < 0 )
		 {
			Block *block_on =  block() ;
			block_on->go_eof() ;
			if ( block()->leaf() )
			{
			   block_on->key_on-- ;
			   #ifdef DEBUG
				  if ( block_on->key_on < 0 )
					 e4severe( e4info, "Tag::skip()", (char *) 0 ) ;
			   #endif
			}
		 }

	  if (rc < 0 )  return( -num_skip ) ;  // Error

	  num_left -=  block()->skip( num_left ) ;
	  if ( num_left == 0)  return( num_skip ) ;  // Success

	  do  // Skip 1 to the next leaf block 
	  {
		 #ifdef DEBUG
			if ( blocks.last() == 0 )
			   e4severe( e4result, "Tag::skip()", (char *) 0 ) ;
		 #endif
		 if ( blocks.last()->prev() == blocks.last() )
		 {
			if ( num_skip > 0 )
			{
			   if ( bottom() < 0 )  return -num_skip ;
			}
			else
			   if ( top() < 0 ) return -num_skip ;

			return( num_skip - num_left ) ;
		 }
		 else
			up() ;
	  }  while ( block()->skip( (long) sign) != (long) sign) ;

	  num_left -= sign ;
   }
}

Block *Tag::split( Block *old_block )
{
   if ( code_base->error() )  return 0 ;
   long  new_file_block =  index->extend() ;

   Block *new_block =  new(*this,new_file_block) Block ;
   if ( new_block == 0 )  return 0 ;

   new_block->changed =  1 ;
   old_block->changed =  1 ;

   // NNNNOOOO  N - New, O - Old
   new_block->n_keys=  (old_block->n_keys+1)/2 ;
   old_block->n_keys -=  new_block->n_keys ;
   new_block->key_on  =  old_block->key_on ;

   int tot_len =  index->block_rw_len() - sizeof(old_block->n_keys) - sizeof(old_block->dummy) ;
   int new_len =  new_block->n_keys * grouplen() ;

   memcpy(  new_block->key(0), old_block->key(0), new_len ) ;
   memmove( old_block->key(0), old_block->key(new_block->numkeys()), tot_len - new_len ) ;
   old_block->go( old_block->keypos() - new_block->numkeys() ) ;

   return new_block ;
}

int __export Tag::top()
{
   int  rc =  lock() ;   if ( rc != 0 )  return rc ;  // Error or locked
   if ( up_to_root() < 0 )  return -1 ;

   block()->go(0) ;
   do
   {
	  if ( (rc = down()) < 0 )  return -1 ;
	  block()->go(0) ;
   } while ( rc == 0 ) ;

   return 0 ;
}

int __export Tag::type()
{
   return header.type ;
}

int  Tag::up()
{
   if ( blocks.last() == 0 )  return 1 ;
   saved.add( blocks.pop() ) ;
   return 0 ;
}

int  Tag::up_to_root()
{
   Link *link_on ;
   while( link_on = blocks.pop() )
	  saved.add( link_on ) ;

   return down() ;
}

TagIterator::TagIterator( DataIndex& data_ref )
{
   cur_tag=  0 ;
   data =  &data_ref ;
}

Tag *TagIterator::next_tag()
{
   if ( cur_tag == 0 )
   {
	  cur_index =  (Index *) data->indexes.first() ;
	  if ( cur_index == 0 )  return 0 ;

	  cur_tag =  (Tag *) cur_index->tags.first() ;
	  return cur_tag ;
   }

   if ( cur_tag == (Tag *) cur_index->tags.last() )
   {
	  if ( cur_index == (Index *) data->indexes.last() )
		 cur_tag =  0 ;
	  else
	  {
		 cur_index =  (Index *) cur_index->next() ;
		 cur_tag =  (Tag *) cur_index->tags.first() ;
	  }
   }
   else
	  cur_tag =  (Tag *) cur_tag->next() ;

   return cur_tag ;
}

Tag *TagIterator::prev_tag()
{
   if ( cur_tag == 0 )  return 0 ;

   Tag *ret_tag =  cur_tag ;

   cur_tag =  (Tag *) cur_tag->prev() ;
   if ( cur_tag ==  (Tag *) cur_index->tags.last() )
   {
	  cur_index =  (Index *) cur_index->prev() ;
	  if ( cur_index == (Index *) data->indexes.last() )
	  {
		 cur_index =  0 ;
		 cur_tag =  0 ;
		 return ret_tag ;
	  }
	  cur_tag =  (Tag *) cur_index->tags.last() ;
   }

   return ret_tag ;
}

