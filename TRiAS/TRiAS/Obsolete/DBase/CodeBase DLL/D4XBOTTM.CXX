// d4xbottm.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int DataIndex::bottom()
{
   if ( code_base->error() )  return -1 ;

   #ifdef OTHER_NDX
	  Index *tag =  index_selected() ;
   #else
	  Tag *tag =  tag_selected() ;
   #endif

   if ( tag == 0 )
   {
	  long rec =  reccount() ;
	  if ( rec > 0L )
		 return go(rec) ;
   }
   else
   {
	  int rc ;
	  if ( (rc = tag->bottom()) != 0 )  return rc ;
	  if ( ! tag->eof() )
		 return go( tag->recno() ) ;
   }

   bof_flag =  1 ;
   return go_eof() ;
}
