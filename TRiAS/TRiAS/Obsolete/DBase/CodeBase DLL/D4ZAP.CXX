// d4zap.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

int Data::zap( long start_rec, long end_rec )
{
   if ( code_base->error() )  return -1 ;
   file_changed =  1 ;

   long cur_count =  reccount() ;
   if ( start_rec > cur_count )  return 0 ;
   if ( end_rec < start_rec )  return 0 ;
   if ( end_rec > cur_count )  end_rec =  cur_count ;

   char *rd_buf, *wr_buf ;
   FileSeqRead   rd ;
   FileSeqWrite  wr ;
   if ( code_base->error() )  return -1 ;

   rd_buf = wr_buf =  0 ;
   unsigned  buf_size =  code_base->buffer_size ;

   for (; buf_size > record.len(); buf_size -= 0x800 )
   {
	  if ( rd_buf != 0 ) m4free( rd_buf ) ;
	  if ( wr_buf != 0 ) m4free( wr_buf ) ;

	  rd_buf =  (char *) m4alloc( buf_size ) ;
	  wr_buf =  (char *) m4alloc( buf_size ) ;
	  if ( rd_buf != 0  &&  wr_buf != 0 )  break ;
   }

   rd.init( file, recpos(end_rec+1), StrLen(rd_buf, buf_size) ) ;
   wr.init( file, recpos(start_rec), StrLen(wr_buf, buf_size) ) ;

   for (long i_rec= end_rec+1L; i_rec <= cur_count; i_rec++ )
   {
	  rd.read( record) ;
	  wr.write( record ) ;
   }

   wr.write( StrChar(0x1A)) ;
   wr.flush() ;
   if ( rd_buf != 0 )  m4free(rd_buf) ;
   if ( wr_buf != 0 )  m4free(wr_buf) ;
   if ( code_base->error() )  return -1 ;

   header.num_recs =  cur_count- (end_rec-start_rec+1) ;
   rec_num =  -1 ;
   rec_num_old =  -1 ;
   record.set( ' ' ) ;
   return  file.set_len(header.header_len + header.num_recs*record.len()+ 1) ;
}
