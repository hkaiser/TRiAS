// m4check.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

class FlagCheck
{
public:
   FlagCheck( CodeBase *, long  max_num_flags ) ;
  ~FlagCheck() ;

   int	  set_range( long, long ) ;
   int	  set_flag( long ) ;

   int	  is_set( long ) ;
   int	  is_all_set( long, long ) ;
   int	  is_any_set( long, long ) ;

   CodeBase *code_base ;
   unsigned char *flags ;
   long	 num_flags ;
} ;

FlagCheck::FlagCheck( CodeBase *cb, long n_flags ) 
{
   code_base =  cb ;
   num_flags =  n_flags ;

   flags =  (unsigned char *)  m4alloc( num_flags/8 +2 ) ;
   if ( flags == 0 )  code_base->error( e4memory, (char *) 0 ) ;
}

FlagCheck::~FlagCheck()
{
   if ( flags != 0 )
   {
	  m4free( flags ) ;
	  flags =  0 ;
   }
}

int  FlagCheck::set_flag( long flag_num )
{
   if ( flag_num < 0 || flag_num > num_flags  ||  flags == 0 )  
	  return code_base->error( e4info, "FlagCheck::set_flag()", (char *) 0 ) ;

   unsigned low_val  =  (unsigned int) (flag_num & 0x7) ;
   unsigned high_val =  (unsigned int) (flag_num >> 3) ;
   unsigned set_val  =  1 << low_val ;

   flags[high_val] = (unsigned char)  (set_val | (unsigned int) flags[high_val]) ;

   return 0 ;
}

int  FlagCheck::set_range( long flag_num, long num_flags )
{
   for ( long i_flag =  0; i_flag < num_flags; i_flag++ )
	  if ( set_flag( flag_num + i_flag ) != 0 )  return e4info ;
   return 0 ;
}

int FlagCheck::is_set( long flag_num )
{
   if ( flag_num > num_flags  ||  flag_num < 0  ||  flags == 0 )
	  return code_base->error( e4info, "FlagCheck::is_set()", (char *) 0 ) ;

   unsigned low_val  =  (unsigned int) (flag_num & 0x7) ;
   unsigned high_val =  (unsigned int) (flag_num >> 3) ;

   unsigned ret_val =  (1 << low_val) &  (unsigned int) flags[high_val]  ;

   return int(ret_val) ;
}

int FlagCheck::is_all_set( long flag_num, long num_flags )
{
   int rc ;
   for ( long i_flag =  flag_num; i_flag <= num_flags; i_flag++ )
   {
	  rc = is_set( i_flag ) ; 
	  if ( rc < 0 )  return e4info ;
	  if ( rc == 0 )  return 0 ;
   }
   return 1 ;
}

int FlagCheck::is_any_set( long flag_num, long num_flags )
{
   int rc ;
   for ( long i_flag =  flag_num; i_flag <= num_flags; i_flag++ )
	  if ( (rc = is_set( i_flag )) )  return rc ;
   return 0 ;
}

MemoFile::check()
{
   DataMemo *data_memo =  (DataMemo *) data ;
   int rc =  data_memo->lock_file() ;
   if ( rc != 0 )  return rc ;

   if ( (rc = data_memo->flush_all()) != 0)  return rc ;

   FlagCheck  check( code_base, file.len()/block_size ) ;
   if ( code_base->error() )  return e4memory ;
   
   // Set flags for the data file entries
   for ( data_memo->top(); ! data_memo->eof(); data_memo->skip() )
   {
	  for ( int i_field =  0;  i_field < data_memo->n_memo_fields; i_field++ )
	  {
		 long num_blocks =  (data_memo->memo_fields[i_field]->len() + block_size - 1)/ block_size ;
		 StrLen  field_data( data_memo->memo_fields[i_field]->Field::ptr(),
							 data_memo->memo_fields[i_field]->Field::len() ) ;
		 long memo_id =  long( field_data ) ;

		 if ( check.is_any_set( memo_id, num_blocks ) )
			return code_base->error( e4info, "MemoFile::check()", "A memo block is used twice.", (char *) 0 ) ;
		 if ( check.set_range( memo_id, num_blocks ) < 0 )
			return e4info ;
	  }
   }

   // Set flags for the free chain
   ChainEntry cur( this ) ;
   cur.skip() ;  // Read in root

   for ( cur.skip(); cur.next != -1; cur.skip() )
   {
	  if ( code_base->error() )  return e4info ;
	  if ( check.is_any_set( cur.block_no, cur.num) )
		 return code_base->error( e4info, "MemoFile::check()", "A memo block is used twice.", (char *) 0 ) ;
	  if ( check.set_range( cur.block_no, cur.num ) < 0 )  return e4info ;
   }

   if ( code_base->error() )  return e4info ;

   if ( ! check.is_all_set( 1, file.len()/block_size-1 ) )
	  return code_base->error( e4result, "MemoFile::check()", "Wasted File Space in Memo File", (char *) 0 ) ;

   return 0 ;
}
