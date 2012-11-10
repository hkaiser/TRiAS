// m4memo.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <limits.h>
#include <string.h>
}

// call DataIndex with name = 0, so we call OUR open statement!
#pragma warning (disable: 4355)		// #JB950622
__export DataMemo::DataMemo( CodeBase *cb, char *name ) : DataIndex( cb, 0 ), memo_file( cb, this )
{
   if ( name != 0 )
	  open( name ) ;
}

__export DataMemo::~DataMemo()
{
   close() ;
}

__export DataMemo::close()
{
   int final_rc =  0 ;
   if ( DataIndex::close() < 0) final_rc =  -1 ;
   if ( memo_file.close() < 0)  final_rc =  -1 ;
   if ( memo_fields != 0 )
   {
	  m4free( memo_fields ) ;
	  n_memo_fields =  0 ;
	  memo_fields =  0 ;
   }

   return final_rc ;
}                              
#pragma warning (default: 4355)

MField * __export DataMemo::mfield( char *name )
{
   Field *f =  field( name ) ;

   #ifdef DEBUG
	  if ( f == 0 )  return 0 ;
	  if ( f->type() != 'M' )
		 e4severe( e4field_type, "Expecting Memo field.", (char *) 0 ) ;
   #endif

   return (MField *) f ;
}

__export DataMemo::open( char *name )
{
   int rc = DataIndex::open( name ) ;  if ( rc != 0 )  return rc ;
   if ( init() < 0 )  return -1 ;
   if ( header.version & 0x80 )
	  return  memo_file.open( 0 ) ;
   return 0 ;
}

DataMemo::init()
{
   n_memo_fields =  0 ;
   for ( int i=0; i< num_fields(); i++ )
	  if ( fields[i]->type() == (int) 'M' )
		 n_memo_fields++ ;

   if ( n_memo_fields == 0 )  return 0 ;

   if ( memo_file.file.name.assign( file.name.ptr() ) < 0 )  return -1 ;
   if ( memo_file.file.name.extension( "DBT", 1 ) < 0 )  return -1 ;

   memo_fields =  (Field **) m4alloc( sizeof(Field *) * n_memo_fields ) ;
   if ( memo_fields == 0 )
	  return code_base->error( e4memory, (char *) 0 ) ;

   int j = 0 ;
   for ( i=0; i< num_fields(); i++ )
	  if ( fields[i]->type() == (int) 'M' )
		 memo_fields[j++] =  fields[i] ;
   return 0 ;
}

MemoFile::MemoFile( CodeBase *cb, Data *d ) : file( cb )
{ code_base = cb; data = d ; }

int  MemoFile::dump( long memo_id, Str& str )
{
   MemoBlock  memo_block ;
   memo_block.init( str.len() ) ;

   long  pos =  memo_id*block_size ;
   file.write( pos, memo_block ) ;
   pos +=  memo_block.start_pos ;
   return  file.write( pos, str ) ; 
}

int  MemoFile::open( char *name )
{
   if ( name != 0 )
   {
	  file.name.assign( name ) ;
	  file.name.extension( "DBT", 0 ) ;
   }
   if ( file.open() < 0 )  return -1 ;
   MemoHeader  header ;
   int rc =  file.read( 0L, StrLen(&header,sizeof(header)) ) ;
   block_size =  header.block_size ;
   return rc ;
}

int  MemoFile::read( long memo_id, Str& str )
{
   if ( memo_id <= 0L )
   {
	  str.set_len(0) ;
	  return 0 ;
   }
	
   long pos =  memo_id * block_size ;
   MemoBlock memo_block ;
   if ( file.read( pos, memo_block) < 0) return -1 ;

   if ( memo_block.num_chars >= UINT_MAX )
	  return code_base->error( e4info, "MemoFile::read", (char *) 0 ) ;

   unsigned final_len =  (unsigned) memo_block.num_chars - 2*sizeof(short)-sizeof(long) ;
   str.set_len( final_len ) ;
   if ( str.len() != final_len )
	  return code_base->error( e4read, file.name.ptr(), "String parameter length could not be set.", (char *) 0 ) ;

   return file.read( pos+ memo_block.start_pos, str ) ;
}
   


void MemoBlock::init( unsigned n_chars )
{
   minus_one =  -1 ;
   start_pos =  sizeof(long) + 2*sizeof(short) ;
   num_chars =  n_chars + start_pos ;
}
