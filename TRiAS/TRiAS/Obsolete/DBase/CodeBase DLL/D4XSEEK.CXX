// d4xseek.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int  DataIndex::seek( Str& str )
{
   #ifdef OTHER_NDX
	  Index *tag =  index_default() ;
   #else
	  Tag *tag =  tag_default() ;
   #endif
   if ( code_base->error() )  return -1 ;
   if ( tag == 0 )  return r4no_tag ;

   int rc =  flush_record() ;  if ( rc != 0 )  return rc ;

   char buf[i4max_key_size] ;  StrMax  sbuf( buf, sizeof(buf) ) ;
   tag->stok( sbuf, str ) ;

   rc =  tag->seek( sbuf ) ;
   if ( tag->eof() )  return go_eof() ;

   int rc2 =  go( tag->recno() ) ;
   if ( rc2 != 0 )  return rc2 ;
   return rc ;
}


