// d4xtop.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int __export DataIndex::top()
{
   if ( code_base->error() )  return -1 ;
   #ifdef OTHER_NDX
	  Index *tag =  (Index *) index_selected() ;
   #else
	  Tag *tag =  tag_selected() ;
   #endif

   int rc ;
   if ( tag == 0 )
   {
	  int save_flag =  code_base->go_error ;
	  code_base->go_error =  0 ;
	  rc = go(1L) ;
	  code_base->go_error =  save_flag ;
	  if ( rc <= 0 )  return rc ;

	  if ( reccount() != 0L )
		 return go(1L) ;
   }
   else
   {
	  if ( (rc = tag->top()) < 0 )  return -1 ;
	  if ( ! tag->eof() )
		 return go( tag->recno()) ;
   }

   bof_flag =  1 ;
   return go_eof() ;
}


