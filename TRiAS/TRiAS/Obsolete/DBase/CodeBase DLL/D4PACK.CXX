// d4pack.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"
int Data::pack()
{
   if ( code_base->error() < 0 )  return -1 ;
   file_changed =  1 ;

   char *rd_buf, *wr_buf ;
   FileSeqRead   rd ;
   FileSeqWrite  wr ;

   rd_buf = wr_buf =  0 ;
   unsigned  buf_size =  code_base->buffer_size ;

   for (; buf_size > record.len(); buf_size -= 0x800 )
   {
	  if ( rd_buf != 0 )  m4free( rd_buf ) ;
	  if ( wr_buf != 0 )  m4free( wr_buf ) ;

	  rd_buf =  (char *) m4alloc( buf_size ) ;
	  if ( rd_buf == 0 )  continue ;

	  wr_buf =  (char *) m4alloc( buf_size ) ;
	  if ( wr_buf != 0 )  break ;
   }

   rd.init( file, recpos(1L), StrLen(rd_buf, (rd_buf == 0) ? 0 : buf_size) ) ;
   wr.init( file, recpos(1L), StrLen(wr_buf, (wr_buf == 0) ? 0 : buf_size) ) ;

   long new_count = 0L ;
   long cur_count =  reccount() ;
   for (long i_rec= 1L; i_rec <= cur_count; i_rec++ )
   {
	  rd.read( record) ;
	  if ( ! deleted() )
	  {
		 wr.write( record) ;
		 new_count++ ;
	  }
   }

   wr.write( StrChar(0x1A) ) ;
   int rc =  wr.flush() ;
   if ( rd_buf != 0 )  m4free( rd_buf ) ;
   if ( wr_buf != 0 )  m4free( wr_buf ) ;
   if ( rc < 0 )  return -1 ;

   header.num_recs =  new_count ;
   rec_num =  -1 ;
   rec_num_old =  -1 ;
   record.set( ' ' ) ;
   return  file.set_len(header.header_len + new_count*record.len()+ 1) ;
}


