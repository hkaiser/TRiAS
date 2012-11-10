// d4xappbl.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int DataIndex::append_blank()
{
   int rc =  flush_record() ;  if ( rc != 0 )  return rc ;
   rc = append_start() ;	   if ( rc != 0 )  return rc ;

   record.set( ' ' ) ;
   return append() ;
}



