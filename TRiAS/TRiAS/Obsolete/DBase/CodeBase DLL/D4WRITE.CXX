// d4write.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int Data::update_header( int do_time_stamp, int do_count )
{
   long pos = 0L ;
   unsigned len = sizeof(header) ;
   if ( do_time_stamp )
	  u4yymmdd( &header.yy ) ;
   else
   {
	  pos += 4 ;
	  len -= 4 ;
   }

   if ( do_count )
	   reccount() ;
   else
	   len -= (sizeof(header.num_recs) +sizeof(header.header_len)) ;
   if ( file.write( pos, StrLen( ((char *)(&header)) + pos,len)) < 0 )
	  return -1 ;
   file_changed =  0 ;
   return 0 ;
}

int Data::write( long rec )
{
   #ifdef DEBUG
	  if ( code_base->error() )  return -1 ;
	  if ( rec <= 0L )  e4severe( e4parm, "Data::write()", (char *) 0 ) ;
   #endif
   int rc =  lock( rec ) ;  if ( rc != 0 )  return rc ;
   record.is_changed =  0 ;
   file_changed =  1 ;
   return file.write( recpos(rec), record ) ;
}
