// m4field.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
}

MField::MField( DataMemo *d, FieldDataImage *image, unsigned *u_ptr ) : 
		Field(d,image,u_ptr), contents( d->code_base )
{
   status =  1 ;
   is_changed = 0 ;
}

void *MField::operator new( size_t )
{
   #ifdef DEBUG
	  e4severe( e4new, "Should Use:  new(CodeBase *) MField", (char *) 0 ) ;
   #endif
   return 0 ;
}

void *MField::operator new( size_t z, CodeBase * code_base )
{
   if ( code_base->mfield_memory == 0 )
   {
	  code_base->mfield_memory =  m4memory_type( 3, z, 3, 0 ) ;
	  if ( code_base->mfield_memory == 0 )  return 0 ;
   }
   return code_base->mfield_memory->alloc() ;
}

void MField::operator delete( void *p )
{
   MField *mfield_ptr = (MField *) p ;
   mfield_ptr->data->code_base->mfield_memory->free( p ) ;
}

void MField::do_delete( void *p )
{
   delete (MField *) p ;
}

MField& MField::operator=( Str& s )
{
   assign(s) ;
   return *this ;
}

MField& MField::operator=( MField& s )
{
   assign(s) ;
   return *this ;
}

MField& MField::operator=( char * p )
{
   assign( StrPtr(p) ) ;
   return *this ;
}

void MField::changed()
{
   status = 0 ;
   is_changed =  1 ;
   data->record.is_changed =  1 ;
}

int  MField::flush()
{
   if ( is_changed )
   {
	  int rc =  write() ;  if ( rc != 0 )  return rc ;
   }
   return 0 ;
}

long  __export MField::id()
{
   StrLen str( Field::ptr(), Field::len()) ;
   return long(str) ;
}

void  MField::id( long new_id )
{
   StrLen str( Field::ptr(), Field::len()) ;
   if ( new_id == 0 )
	  str.set( ' ' ) ;
   else
	  str.assign_long( new_id, 0 ) ;
   data->changed() ;
}

unsigned  __export MField::len()
{
   if ( status == 1 )
   {
	  if ( read() != 0 )  return 0 ;
	  status =  0 ;
   }
   return contents.len() ;
}

char * __export MField::ptr()
{
   if ( status == 1 )  len() ;
   return contents.ptr() ;
}

/*
char *MField::str()
{
   #ifdef DEBUG
	  if ( data->code_base->str_buffer == 0 )
		 e4severe( e4info, "Unallocated memory buffer encountered", (char *) 0 ) ;
   #endif
   if ( status == 1 )  len() ;
   if ( data->code_base->str_buffer->set_len( contents.len() ) < 0 ) return 0 ;
   memcpy( data->code_base->str_buffer->ptr(), contents.ptr(), contents.len() ) ;
   if ( data->code_base->str_buffer->null_ensure() < 0 ) return 0 ;
   return data->code_base->str_buffer->ptr() ;
}
*/

int MField::read( Str *result )
{
   if ( result == 0 )
   {
	  result =  &contents ;
	  is_changed =  0 ;
   }

   if ( data->recno() < 0 )
	  return (int) result->set_len(0) ;

   int rc =  ((DataMemo *)(data))->validate_memo_ids() ;  if ( rc != 0 )  return rc ;

   long memo_id =   id() ;
   if ( memo_id == 0 )
   {
	  result->set_len(0) ;
	  return 0 ;
   }

   return ((DataMemo *)data)->memo_file.read( memo_id, *result ) ;
}

void MField::reset()   // Called indirectly from Data::flush()
{
   contents.set_len(0) ;
   status =  1 ;
}

int MField::set_len( unsigned new_len )
{
   len() ;
   if ( data->code_base->error() )  return -1 ;
   if ( contents.set_len(new_len) < 0 )  return -1 ;
   return 0 ;
}

int MField::write()
{
   int rc = ((DataMemo *)(data))->validate_memo_ids() ;  if ( rc != 0 )  return rc ;
   long memo_id =  id() ;
   long new_id  =  memo_id ;

   rc =  ((DataMemo *)data)->memo_file.write( &new_id, contents ) ;
   if ( rc != 0 )  return rc ;

   if ( new_id != memo_id )
	  id( new_id ) ;

   is_changed =  0 ;
   return  0 ;
}
