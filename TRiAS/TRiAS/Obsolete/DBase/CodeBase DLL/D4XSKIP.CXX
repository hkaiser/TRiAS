// d4xskip.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include <d4all.h>

int __export DataIndex::skip( long n )
{
   #ifdef OTHER_NDX
	  Index *tag =  index_selected() ;
   #else
	  Tag *tag =  tag_selected() ;
   #endif
   if ( code_base->error() )  return -1 ;

   int rc ;
   if ( tag == 0 )
   {
	  bof_flag =  0 ;
	  long start_rec =  recno() ;
	  long new_rec =  start_rec+n ;
	  if ( new_rec > 0L )
	  {
		 int save_flag =  code_base->go_error ;
		 code_base->go_error =  0 ;
		 rc = go(new_rec) ;
		 code_base->go_error =  save_flag ;
		 if ( rc >= 0 && rc != r4entry )  return rc ;
	  }

	  long count =  reccount() ;
	  if ( count <= 0L || new_rec > count )
	  {
		 if ( count <= 0L )
		 {
			if ( count < 0 )  return -1 ;
			if ( (rc = go_eof()) != r4eof )  return rc ;
			bof_flag =  1 ;
		 }
		 if ( n < 0 )
		 {
			bof_flag =  1 ;
			return r4bof ;
		 }
		 else
			return go_eof() ;
	  }

	  if ( new_rec < 1L )
	  {
		 int old_eof_flag =  eof_flag ;
		 int rc =  go(1L) ;  if ( rc != 0 )  return rc ;
		 bof_flag =  1 ;
		 eof_flag =  old_eof_flag ;
		 return r4bof ;
	  }

	  return go(new_rec) ;
   }
   else
   {
	  if ( eof() )
	  {
		 if ( n >= 0 ) return go_eof() ;

		 int  rc =  bottom() ;  if ( rc !=  0 && rc != r4eof )  return rc ;
		 if ( rc == r4eof )
		 {
			if ( (rc = go_eof()) != r4eof )  return rc ;
			return r4bof ;
		 }
		 n++ ;
		 rec_num =  tag->recno() ;
	  }
	  if ( n == 0 )  return 0 ;
	  bof_flag =  0 ;

	  if ( tag->recno() == recno() )
	  {
		 int rc =  tag->lock() ;
		 if ( rc != 0 )  return rc ;
	  }

	  if ( tag->recno() != recno() )
	  {
		 if ( flush_record() < 0 )  return -1 ;
		 int rc =  lock( recno() ) ;  if ( rc != 0 )  return rc ;
		 go( recno() ) ;

		 String  key_value( code_base ) ;
		 tag->expr.key(key_value) ;
		 rc = tag->go(key_value,recno()) ;  if ( rc < 0 )  return -1 ;
		 if ( rc == r4locked )  return r4locked ;
		 if ( rc > 0 )
		 {
			if ( code_base->skip_error )
			   return code_base->error( e4entry, file.name.ptr(), (char *) 0 ) ;
			else
			   return r4entry ;
		 }
	  }
	  long n_skipped =  tag->skip(n) ;
	  if ( n > 0  &&  n_skipped != n )
		 return go_eof() ;

	  int rc ;
	  if ( (rc = go(tag->recno())) != 0 )  return rc ;
	  if ( n == n_skipped )  return 0 ;
	  if ( n < 0 )
	  {
		 bof_flag =  1 ;
		 return r4bof ;
	  }
   }
   return 0 ;
}
