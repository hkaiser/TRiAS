// d4xpos.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int DataIndex::position( double pos)
{
   if ( pos > 1.0 )  return go_eof() ;
   if ( pos <= 0 )	return top() ;

   #ifdef OTHER_NDX
	  Index *tag_on =  index_selected() ;
   #else
	  Tag *tag_on =  tag_selected() ;
   #endif

   long new_rec ;
   if ( tag_on == 0 )
   {
	  long count =  reccount() ;
	  if ( count <= 0L )  return go_eof() ;

	  new_rec =  (long) (pos * (count - 1) + 1.5);  // #JB950623
	  if ( new_rec > count ) new_rec = count ;
   }
   else
   {
	  int rc ;
	  if ( (rc = tag_on->position(pos)) != 0 )  return rc ;
	  if ( rc == r4eof )  return  go_eof() ;

	  new_rec =  tag_on->recno() ;
   }

   return go(new_rec) ;
}

double DataIndex::position()
{
   if ( eof() ) return 1.1 ;

   #ifdef OTHER_NDX
	  Index *tag_on =  index_selected() ;
   #else
	  Tag *tag_on =  tag_selected() ;
   #endif

   if ( tag_on == 0 || recno() <= 0L )
   {
	  long count =  reccount() ;
	  if ( count < 0 )  return -1.0 ;
	  if ( count == 0  ||  recno() <= 0L )  return 0.0 ;

	  return  (double) ( recno() - 1) / ( count - (count != 1 ) );
   }
   else
   {
	  if ( tag_on->recno() == recno() )
		 return tag_on->position() ;

	  String  result( code_base ) ;
	  if ( tag_on->expr.key(result) < 0 )  return -1.0 ;
	  int rc =  tag_on->seek( result ) ;
	  if ( rc != 0  && rc != r4eof && rc != r4after )  return -1.0 ;

	  return tag_on->position() ;
   }
}
