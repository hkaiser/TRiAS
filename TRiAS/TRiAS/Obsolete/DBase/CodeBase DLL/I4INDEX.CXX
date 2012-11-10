// i4index.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

#ifdef IndexInfo
   #error  --  you are using the wrong (NDX) "i4index.h" header file when
   attempting to build an MDX version of the library.  Make sure you copy
   'i4index.h' from the \H directory.
#endif

extern "C" {
#include <string.h>
}

__export Index::Index(DataIndex *data_parm, char *name ) : file(data_parm->code_base)
{
   #ifdef DEBUG
	  if ( data_parm == 0 )   e4severe( e4parm, "Index::Index", (char *) 0 ) ;
   #endif

   memset( &header, 0, sizeof(header) ) ;
   data	   =  data_parm ;
   code_base  =  data_parm->code_base ;
   tag_locked =  0 ;
   file_locked=  0 ;

   block_alloc=  0 ;
   if ( tags.init( 10, sizeof(Tag), 5 ) < 0 )
   {
	  if ( code_base != 0 )   code_base->error( e4memory, (char *) 0 ) ;
	   return ;
   }

   if ( name != 0 )
   {
	  file.name.assign( name ) ;
	  file.name.extension( INDEX_EXTENSION, 0 ) ;		// #JB951108  "MDX" --> "MDC"
	  open() ;
   }
}

__export Index::~Index()
{
   close() ;
}

void *Index::operator new( size_t, CodeBase *cb )
{
   if ( cb->index_memory == 0 )
   {
	  cb->index_memory =  m4memory_type( 5, sizeof(Index), 5) ;
	  if ( cb->index_memory == 0 )  return 0 ;
   }

   return  cb->index_memory->alloc() ;
}

void *Index::operator new( size_t )
{
   #ifdef DEBUG
	  e4severe( e4new, "Should Use:  new(CodeBase *) Index", (char *) 0 ) ;
   #endif
   return 0 ;
}

void Index::operator delete( void *p )
{
   Index *index_ptr =  (Index *) p ;
   index_ptr->code_base->index_memory->free( p ) ;
}

__export Index::close()
{
   int final_rc =  code_base->error_set(0) ;
   int save_wait =  code_base->wait ;
   code_base->wait =  1 ;

   if ( data != 0 )
	  if ( data->flush_all() < 0 )
		 final_rc =  code_base->error_set(0) ;

   if ( unlock() < 0 )
	  final_rc =  code_base->error_set(0) ;

   LinkIterator next( tags ) ;
   for ( Tag *tag_on; tag_on = (Tag *) next(); )
   {
	  if ( tag_on->free() < 0 )
	  {
		 final_rc =  code_base->error_set(0) ;
		 break ;
	  }
	  delete tag_on ;
   }

   m4release( block_alloc ) ;
   block_alloc =  0 ;

   if ( file.open_test() )
   {
	  if ( data != 0 )
		 data->indexes.remove( this ) ;
	  if ( file.close() < 0 )  final_rc = code_base->error_set(0) ;
   }

   // clear the header
   memset( &header, 0, sizeof(header) ) ;

   code_base->wait =  save_wait ;
   code_base->error_set( final_rc ) ;
   return  final_rc ;
}

long Index::extend()
{
   #ifdef DEBUG
	  if ( header.version == version_old )
		 e4severe( e4info, "Index::extend()", (char *) 0 ) ;
   #endif

   long old_eof = header.free_list ;

   if( header.free_list == 0L )  // case where no free list
   {
				old_eof = header.eof ;
	  header.eof = header.eof + block_rw_len()/i4multiply ;
   }
   else
   {
	  unsigned len =  sizeof(header.free_list) ;
	  int rc =  file.read( header.free_list*i4multiply, StrLen((char *)&header.free_list, sizeof(header.free_list)), &len) ;
	  if ( rc < 0 )  return rc ;
	  switch( len )
	  {
		 case 0:
		 {
			#ifdef DEBUG
			   e4severe( e4info, "Index::extend", (char *) 0 ) ;
			#endif

			// else fix up

			header.free_list = 0L ;
			old_eof = header.eof ;
			header.eof = header.eof + block_rw_len()/i4multiply ;
		 }
			break ;

		 case sizeof(header.free_list):
			break ;

		 default:
		 {
			return file.read_error() ;
		 }
	  }
   }

   return old_eof ;
}

int Index::lock_file()
{
   if ( code_base->error() )  return -1 ;
   if ( file_locked )  return 0 ;	// Already locked
   if ( unlock() < 0 )  return -1 ;  // Unlock any locked tag

   int rc =  file.lock( l4lock_pos, l4lock_pos ) ;
   if ( rc != 0 )  return rc ;

   if ( version_check() < 0 )
   {
	  file.unlock( l4lock_pos, l4lock_pos ) ;
	  return -1 ;
   }
   file_locked =  1 ;
   return 0 ;
}

int __export Index::open( char *file_name )
{
   int rc =  close() ;  if ( rc != 0 )  return rc ;
   if ( file_name != 0 )
   {
	  file.name =  file_name ;
	  file.name.extension(INDEX_EXTENSION) ;		// #JB951108  "MDX" --> "MDC"
   }
   else
	  if ( file.name.len() == 0 )
	  {
		 file.name.assign( data->file.name.ptr() ) ;
		 file.name.extension(INDEX_EXTENSION, 1 ) ;		// #JB951108  "MDX" --> "MDC"	
	  }

   rc =  file.open() ;  if ( rc != 0 )  return rc ;
   if ( data != 0 )
	  data->indexes.add( this ) ;

   if ( file.read( 0L, StrLen((char *)&header, sizeof(header))) < 0 )  return -1 ;

   /* Perform some checks */
   if ( header.block_rw != header.block_chunks*512  ||
		header.block_chunks <= 0 ||
		header.block_chunks > 32 ||
		header.num_tags < 0  || header.num_tags > 47 ||
		header.eof <= 0L )
	  return code_base->error( e4index, file.name.ptr(), (char *) 0 ) ;

   TAG_INFO  tag_info[47] ;
   if ( file.read( 544L, StrLen((char *)&tag_info, sizeof(tag_info))) < 0 )  return -1;

   for ( int i_tag = 0; i_tag < header.num_tags; i_tag++ )
   {
	  Tag *new_tag =  new( tags.add() )  Tag( this ) ;
	  if ( new_tag == 0 )  return  code_base->error( e4memory, (char *) 0 ) ;
	  if ( new_tag->init( *this, tag_info[i_tag], l4lock_pos+i_tag) < 0 )
	  {
		 close() ;
		 return -1 ;
	  }
   }

   block_alloc = m4memory_type( code_base->blocks_start,
		   sizeof(Block) + header.block_rw -
		   sizeof(KeyData) - sizeof(short) - sizeof(char[6]),
		   code_base->blocks_expand, 0 ) ;
   if ( block_alloc == 0 )
   {
	  close() ;
	  return e4memory ;
   }

   return 0 ;
}

int Index::shrink( long block_no )
{
   if ( file.write( block_no*i4multiply,
			  StrLen((char *)&header.free_list, sizeof(header.free_list))) < 0) return -1 ;
   header.free_list =  block_no ;
   return 0 ;
}

int __export Index::unlock()
{
   if ( file_locked )
   {
	  if ( update_header() < 0 )  return -1 ;

	  LinkIterator next_flush( tags ) ;
	  for ( Tag *tag_on; tag_on = (Tag *) next_flush(); )
	  {
		 if ( tag_on->flush() < 0 )  return -1 ;
		 tag_on->header.root =  -1 ;
	  }

	  if ( file.unlock( l4lock_pos, l4lock_pos ) < 0 )  return -1 ;
	  file_locked =  0 ;
	  return 0 ;
   }

   if ( tag_locked != 0 )
   {
	  // Must lock entire index to update, consequently, it was not changed
	  tag_locked->header.root =  -1 ;
	  if ( file.unlock( tag_locked->lock_pos, 1L) < 0 )  return -1 ;
	  tag_locked =  0 ;
   }
   return 0 ;
}

// Updates the header if the version has changed
int Index::update_header()
{
   if ( code_base->error() )  return -1 ;
   if ( version_old != header.version )
   {
	  if ( file.write( 0L, StrLen((char *)&header, sizeof(header))) < 0) return -1 ;
	  version_old =  header.version ;
   }
   return 0 ;
}

// Reads the header, checks the version to see if the blocks need to be freed.
int Index::version_check()
{
   StrLen header_str( &header, sizeof(header) ) ;
   if ( file.read( 0L, header_str ) < 0 ) return -1 ;
   if ( header.version == version_old )
	  return 0 ;

   version_old =  header.version ;

   LinkIterator next( tags ) ;
   for ( Tag *tag_on; tag_on = (Tag *) next(); )
	  if ( tag_on->free() < 0 )  // Should be a memory operation only
		 e4severe( e4result, "Index::version_check()", (char *) 0 ) ;

   return 0 ;
}
