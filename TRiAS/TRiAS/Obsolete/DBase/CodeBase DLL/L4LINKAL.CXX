// l4linkal.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

LinkAlloc::LinkAlloc()
{
   type_ptr =  0 ;
}

LinkAlloc::LinkAlloc( int units_start, unsigned unit_size, int unit_expand, int is_temp)
{
   type_ptr =  m4memory_type(units_start, unit_size, unit_expand, is_temp) ;
}

LinkAlloc::~LinkAlloc()
{
   reset() ;
}

void LinkAlloc::reset()
{
   while ( last() )  remove( last() ) ;
   if ( type_ptr != 0 )
	  m4release( (MemoryType *) type_ptr ) ;
   type_ptr =  0 ;
}

LinkAlloc::init( int units_start, unsigned unit_size, int unit_expand, int is_temp)
{
   #ifdef DEBUG
	  if ( type_ptr != 0 )
		 e4severe( e4info, "LinkAlloc::init", "Already initialized", (char *) 0 ) ;
   #endif
   type_ptr =  m4memory_type( units_start, unit_size, unit_expand, is_temp ) ;
   if ( type_ptr == 0 )  return e4memory ;
   return 0 ;
}

Link *LinkAlloc::add()
{
   MemoryType *t =  (MemoryType *) type_ptr ;
   if ( t == 0 )  return 0 ;

   Link *l =  (Link *) t->alloc() ;
   if ( l == 0 )  return 0 ;
   LinkSelect::add( l ) ;

   return  (Link *) l ;
}

void LinkAlloc::remove( Link *l_ptr )
{
   if ( l_ptr == 0 )  return ;
   LinkSelect::remove( l_ptr ) ;
   MemoryType *t =  (MemoryType *) type_ptr ;
   t->free( l_ptr ) ;
}
