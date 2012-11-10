// m4comprs.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

DataMemo::compress()
{
   if ( code_base->error() )  return -1 ;
   if ( n_memo_fields == 0 )  return 0 ;

   MemoFile new_file( code_base, this ) ;
   if ( new_file.create(memo_file.file.name.ptr(),1) < 0 )  return -1 ;

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

   long cur_count =  reccount() ;
   String  result( code_base ) ;

   for (long i_rec= 1L; i_rec <= cur_count; i_rec++ )
   {
	  if ( rd.read( record ) < 0 )  break ;

	  for ( int i = 0; i < n_memo_fields; i++ )
	  {
		 MField *memo_ptr =  (MField *)(memo_fields[i]) ;
		 memo_file.read( memo_ptr->id(), result ) ;
		 long new_id =  0L ;
		 new_file.write( &new_id, result ) ;
		 memo_ptr->id( new_id ) ;
	  }

	  wr.write( record) ;
   }

   if ( wr.flush() < 0 )  return -1 ;

   if ( rd_buf != 0 )  m4free( rd_buf ) ;
   if ( wr_buf != 0 )  m4free( wr_buf ) ;
   if ( code_base->error() < 0 )  return -1 ;

   memo_file.file.remove() ;
   new_file.file.rename( memo_file.file.name ) ;
   return memo_file.file.open() ;
}
