// d4xseekdb.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int  DataIndex::seek( double dkey )
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
   #ifdef CLIPPER
	  if ( tag->dtok == 0 )
	  {
		 int len = tag->valuelen() ;
		 sbuf.set_len( len ) ;
		  c4dtoa( dkey, sbuf.ptr(), len, tag->decimals() ) ;
		  if ( char(sbuf.ptr()) == '*' )  return -1 ;  // unknown overflow result!
		  c4clip( sbuf.ptr(), len ) ;
	  }
	  else
   #else
	  #ifdef DEBUG
		 if ( tag->dtok == 0 )
		   e4severe( e4info, "DataIndex::seek(double)", "Wrong Tag Type", (char *) 0 ) ;
	  #endif
   #endif
   tag->dtok( sbuf, dkey ) ;

   rc =  tag->seek( sbuf ) ;
   if ( rc == r4locked )  return r4locked ;
   if ( tag->eof() )  return go_eof() ;
   int rc2 =  go( tag->recno() ) ;
   if ( rc2 != 0 )  return rc2 ;
   return rc ;
}

