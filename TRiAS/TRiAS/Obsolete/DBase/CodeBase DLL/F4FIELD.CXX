// f4field.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

extern "C" {
#include <string.h>
#include <limits.h>
}

Field::Field( Data *data_parm, FieldDataImage *image, unsigned *last_offset_ptr )
{
   #ifdef DEBUG
	  if ( data_parm == 0 )  e4severe( e4parm, "Field::Field()", (char *) 0 ) ;
   #endif

   data  =  data_parm ;
   image->name[10] = 0 ;
   name.assign( image->name ) ;
   name.upper() ;

   type_field =  image->type ;

   len_field =  image->len ;
   dec =  image->decimals ;

   if ( type_field == (int) 'C' )
   {
	  len_field +=  dec<<8 ;
	  dec =  0 ;
   }

   offset =  *last_offset_ptr ;
   long  new_offset =  ((long) *last_offset_ptr) + len_field ;
   if (unsigned(new_offset) >   // #JB911213 new_offset --> unsigned()
	   (USHRT_MAX-3))				
   {
	  data->code_base->error( e4record_len, data->file.name.ptr(), (char *) 0 ) ;
	  return ;
   }

   *last_offset_ptr =  (unsigned) new_offset   ;
}

void * __export Field::operator new( size_t )
{
   #ifdef DEBUG
	  e4severe( e4new, "Should Use:  new(CodeBase *) Field", (char *) 0 ) ;
   #endif
   return 0 ;
}

void * __export Field::operator new( size_t z, CodeBase *code_base )
{
   if ( code_base->field_memory == 0 )
   {
	  code_base->field_memory =  m4memory_type( 40, z, 40, 0 ) ;
	  if ( code_base->field_memory == 0 )  return 0 ;
   }
   return code_base->field_memory->alloc() ;
}

void Field::operator delete( void *p )
{                    
/*
   switch (((Field *) p) -> type ()) {		  // #JB930808
		case 'N':
		case 'F':
			((NField *) p) -> NField :: do_delete( p ) ;
		break;
		case 'D':
			((DField *) p) -> DField :: do_delete( p ) ;
		break;
		default:
			((Field *) p) -> Field :: do_delete( p ) ;  // Orginal-Zeile
		break;
   }
*/   
// ((Field *) p) -> do_delete( p ) ;  // Orginal-Zeile
	((Field *) p) -> do_delete ( p ) ;
}

void Field::do_delete( void *p )
{
   data->code_base->field_memory->free( p ) ;
}

char *Field::ptr()
{
   return data->record.ptr() + offset ;
}

DField::DField( Data *data_parm, FieldDataImage *image, unsigned *last_offset_ptr )
   : Field( data_parm, image, last_offset_ptr )
{}

void *DField::operator new( size_t )
{
   #ifdef DEBUG
	  e4severe( e4new, "Should Use:  new(CodeBase *) DField", (char *) 0 ) ;
   #endif
   return 0 ;
}

void *DField::operator new( size_t z, CodeBase *code_base )
{
   if ( code_base->dfield_memory == 0 )
   {
	  code_base->dfield_memory =  m4memory_type( 40, z, 40, 0 ) ;
	  if ( code_base->dfield_memory == 0 )  return 0 ;
   }
   return code_base->dfield_memory->alloc() ;
}

void DField::operator delete( void *p )
{
   ((DField *) p)->do_delete( p ) ;
}

void DField::do_delete( void *p )
{
   data->code_base->dfield_memory->free( p ) ;
}

NField::NField( Data *data_parm, FieldDataImage *image, unsigned *last_offset_ptr )
   : Field( data_parm, image, last_offset_ptr )
{}

void *NField::operator new( size_t )
{
   #ifdef DEBUG
	  e4severe( e4new, "Should Use:  new(CodeBase *) NField", (char *) 0 ) ;
   #endif
   return 0 ;
}

void *NField::operator new( size_t z, CodeBase *code_base )
{
   if ( code_base->nfield_memory == 0 )
   {
	  code_base->nfield_memory =  m4memory_type( 40, z, 40, 0 ) ;
	  if ( code_base->nfield_memory == 0 )  return 0 ;
   }
   return code_base->nfield_memory->alloc() ;
}

void NField::operator delete( void *p )
{
   ((NField *)p)->do_delete( p ) ;
}

void NField::do_delete( void *p )
{
   data->code_base->nfield_memory->free( p ) ;
}

Field::assign( Str& s )
{
   return  Str::assign(s) ;
}

void __export Field::assign( double d )
{
   assign_double( d, decimals() ) ;
}

void Field::changed()
{
   data->record.changed() ;
}

Field&  __export Field::operator=( char *p )
{
   assign( StrPtr(p) ) ;
   return *this ;
}

/*
char *Field::str()
{
   #ifdef DEBUG
	  if ( data->code_base->str_buffer == 0 )
		 e4severe( e4info, "Unallocated memory buffer encountered", (char *) 0 ) ;
   #endif
   if ( data->code_base->str_buffer->set_len( len_field ) < 0 ) return 0 ;
   memcpy( data->code_base->str_buffer->ptr(), (char *) (data->record.ptr() + offset), len_field ) ;
   if ( data->code_base->str_buffer->null_ensure() < 0 ) return 0 ;
   return data->code_base->str_buffer->ptr() ;
}
*/

NField& NField::operator=( NField& s )
{
   assign( s ) ;
   return *this ;
}

NField& NField::operator=( Str& s )
{
   assign_double( double(s) ) ;
   return *this ;
}

NField& NField::operator=( double d )
{
   assign_double( d ) ;
   return *this ;
}

int NField::assign( Str& s )
{
   assign_double( double(s), decimals() ) ;
   return 0 ;
}

DField::operator long()
{
   return julian_day() ;
}

DField& DField::operator=( DField& s )
{
   assign( s ) ;
   return *this ;
}

DField& DField::operator=( Str& s )
{
   Field::assign( s ) ;
   return *this ;
}

DField& DField::operator=( char *p )
{
   Field::assign( StrPtr(p) ) ;
   return *this ;
}

DField& DField::operator=( long l )
{
   DateOperations::init( l ) ;
   return *this ;
}

void  DField::assign( double d )
{
   DateOperations::init( long(d) ) ;
}
