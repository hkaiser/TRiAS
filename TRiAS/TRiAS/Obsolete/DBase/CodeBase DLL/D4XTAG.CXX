// d4xtag.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

#ifdef OTHER_NDX
   Index *DataIndex::index_default()
   {
	  Index *index =  index_selected() ;
	  if ( index != 0 )  return index ;

	  index =  (Index *) indexes.first() ;
	  if ( index != 0 ) return index;
 
	  return 0 ;
   }

   Index * __export DataIndex::index_selected()
   {
	  Index *index =  (Index *) indexes.selected ;
	  if ( index != 0 )  return index ;

	  return 0 ;
   }
   Tag * __export DataIndex::tag( char *tag_name, Index *index_ptr )
   {
	  if ( index_ptr != 0 ) return index_ptr ;

	  Str10 tag_lookup( tag_name ) ;
	  tag_lookup.upper() ;

	  LinkIterator next_tag( indexes ) ;
	  for ( Tag *tag_on; tag_on = (Index *) next_tag(); )
	  {
		 if ( tag_on->alias == tag_lookup )
			return tag_on ;
	  }

	  if ( code_base->tag_name_error )
		 code_base->error( e4tag_name, tag_name, (char *) 0 ) ;
	  return 0 ;
   }

   Tag *DataIndex::tag_default()
   {
	  return index_default() ;
   }

   Tag * __export DataIndex::tag_selected()
   {
	  return index_selected() ;
   }
#else
   // hier nur implentiert, um eine einheitliche LIB erzeuegen zu können #JB930401
   Index *DataIndex::index_selected()   // #JB930401
   {
	  return 0 ;
   }

   Tag * __export DataIndex::tag( char *tag_name, Index *index_ptr )
   {
	  Str10 tag_lookup( tag_name ) ;
	  tag_lookup.upper() ;

	  TagIterator next_tag( *this ) ;
	  for ( Tag *tag_on; tag_on =  next_tag.next_tag(); )
	  {
		 if ( index_ptr != 0 )
			if ( tag_on->index != index_ptr )  continue ;

		 if ( tag_on->alias == tag_lookup )
			return tag_on ;
	  }

	  if ( code_base->tag_name_error )
		 code_base->error( e4tag_name, tag_name, (char *) 0 ) ;
	  return 0 ;
   }

   Tag *DataIndex::tag_default()
   {
	  Tag *tag =  tag_selected() ;
	  if ( tag != 0 )  return tag ;

	  Index *index =  (Index *) indexes.first() ;
	  if ( index != 0 )
	  {
		 tag =  (Tag *) index->tags.first() ;
		 if ( tag != 0 )  return tag ;
	 }
 
	  return 0 ;
   }

   Tag *DataIndex::tag_selected()
   {
	  Index *index =  (Index *) indexes.selected ;
	  if ( index != 0 )
	  {
		 Tag *tag =  (Tag *) index->tags.selected ;
		 if ( tag != 0 )  return tag ;
	  }

	  return 0 ;
   }
#endif

