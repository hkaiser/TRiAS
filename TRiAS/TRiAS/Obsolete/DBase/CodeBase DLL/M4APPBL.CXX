// m4appbl.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int DataMemo::append_blank()
{
   int rc =  flush_record() ;  if ( rc != 0 )  return rc ;
   rc = append_start(0) ;	  if ( rc != 0 )  return rc ;

   record.set( ' ' ) ;
   return append() ;
}


