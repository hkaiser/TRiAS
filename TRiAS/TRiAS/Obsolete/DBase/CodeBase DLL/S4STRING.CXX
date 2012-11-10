// s4string.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <string.h>
#include <limits.h>
}

static int  num_per_type[16] = { 8, 6, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

static int  calc_type( unsigned l )
{
   long n = 16 ;
   int  i = 0 ;

   while ( (long) l > n )
   {
	  i++ ;
	  n <<= 1 ;
   }
   return i ;
}

static unsigned calc_max( int i_type )
{
   return  1 << (unsigned) (i_type+4) ;
}

__export String::String( CodeBase *cb ) : StrMax(0,0)
{
   code_base =  cb ;
}

__export String::String( String& a ) : StrMax(0,0)
{
   code_base =  a.code_base ;
   if ( set_len( a.cur_len ) < 0 )  return ;
   memcpy( p, a.p, a.cur_len ) ;
}

__export String::~String()
{
   free() ;
}

void *String::operator new( size_t )
{
   return m4alloc( sizeof( String ) ) ;
}

void String::operator delete( void *p )
{
   m4free( p ) ;
}

void String::free()
{
   if ( p != 0 )
   {
	  int i_type = calc_type( max_len ) ;
	  code_base->string_types[i_type]->free( p ) ;
	  p =  0 ;
   }
}

__export String::set_max( unsigned n )
{
   if ( code_base->error() )  return -1 ;
   if ( n >= UINT_MAX )  return code_base->error( e4memory, (char *) 0 ) ;

   if ( n == 0 )
   {
	  free() ;
	  return cur_len =  max_len =  0 ;
   }
   if ( cur_len == 0 )  free() ;

   int i_type =  calc_type( n+1 ) ;
   unsigned new_max =  calc_max(i_type)-1 ;

   #ifdef DEBUG
	  if ( i_type > 16 )
		 e4severe( e4parm, "String::set_max", (char *) 0 ) ;
	  if ( calc_type(new_max) != i_type )
		 e4severe( e4parm, "String::set_max", (char *) 0 ) ;
   #endif

   if ( code_base->string_types[i_type] == 0 )
   {
	  code_base->string_types[i_type] = m4memory_type( num_per_type[i_type], new_max+1, num_per_type[i_type]) ;
	  if ( code_base->string_types[i_type] == 0 )  return code_base->error( e4memory, (char *) 0);
   }

   char *new_p =  (char *) code_base->string_types[i_type]->alloc() ;
   if ( new_p == 0 )  return code_base->error( e4memory, (char *) 0 ) ;

   if ( cur_len > new_max )  cur_len =  new_max ;
   memcpy( new_p, p, cur_len ) ;

   free() ;
   max_len =  new_max ;
   p =  new_p ;
   p[max_len] =  0 ;

   return 0 ;
}

