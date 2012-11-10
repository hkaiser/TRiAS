// d4xselct.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

void __export DataIndex::select( Tag *new_tag )
{
   if ( new_tag == 0 )
	  indexes.selected =  0 ;
   else
   {
	  #ifdef OTHER_NDX
		 indexes.selected =  new_tag ;
	  #else
		 indexes.selected =  new_tag->index ;
		 new_tag->index->tags.selected =  new_tag ;
	  #endif
   }
}

int  __export DataIndex::select( char *name )
{
   if ( name == 0 )
   {
	  indexes.selected =  0 ;
	  return 0 ;
   }

   Str10  new_name( name ) ;
   new_name.trim() ;
   new_name.upper() ;

   #ifdef OTHER_NDX
	  LinkIterator  next_index( indexes ) ;
	  for ( Index *tag_on; tag_on = (Index *) next_index(); )
   #else
	  TagIterator next(*this) ;
	  for ( Tag *tag_on; tag_on = next.next_tag(); )
   #endif
	  if ( tag_on->alias == new_name )
	  {
		 select( tag_on ) ;
		 return 0 ;
	  }

   if ( code_base->tag_name_error )
	  return code_base->error( e4tag_name, name, (char *) 0 ) ;

   return r4no_tag ;
}
