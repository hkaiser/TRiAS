// d4field.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int __export Data::jfield( char *field_name )
{
   if ( code_base->error() )  return -1 ;
   if ( field_name == 0 )  return -1 ;

   Str255  name( field_name ) ;
   name.trim() ;
   name.upper() ;

   for ( int i = 0; i< num_fields(); i++ )
	  if ( name == fields[i]->name )
		 return i+1 ;

   return -1 ;
}

Field * __export Data::field( char *field_name )
{
   int j =  jfield(field_name) ;
   if ( j > 0 )  return fields[j-1] ;

   if ( ! code_base->error() && code_base->field_name_error )
	  code_base->error( e4field_name, field_name, (char *) 0 ) ;
   return 0 ;
}

Field * __export Data::field( int j_field )
{
   if ( code_base->error() )  return 0 ;
   #ifdef DEBUG
	  if ( fields == 0 || j_field > num_fields() || j_field <= 0 )
		 e4severe( e4info, "Data::field", (char *) 0 ) ;
   #endif
   return  fields[j_field-1] ;
}

DField *Data::dfield( char *name )
{
   Field *f =  field( name ) ;

   #ifdef DEBUG
	  if ( f == 0 )  return 0 ;
	  if ( f->type() != 'D' )
		 e4severe( e4field_type, name, "Expecting Date field.", (char *) 0 ) ;
   #endif

   return (DField *) f ;
}

NField *Data::nfield( char *name )
{
   Field *f =  field( name ) ;

   #ifdef DEBUG
	  if ( f == 0 )  return 0 ;
	  if ( f->type() != 'N' && f->type() != 'F' )
		 e4severe( e4field_type, "Expecting Numeric field.", (char *) 0 ) ;
   #endif

   return (NField *) f ;
}
