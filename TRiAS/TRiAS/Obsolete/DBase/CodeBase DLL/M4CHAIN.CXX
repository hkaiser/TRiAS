// m4chain.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

ChainEntry::ChainEntry( MemoFile *m )
{
   memo =  m ;
   next = 0L ;
   num = 0 ;
   to_disk =  0 ;
   block_no = 0 ;
}

ChainEntry::flush()
{
   if ( to_disk )
   {
	  to_disk =  0 ;
	  return memo->file.write( block_no * memo->block_size, *this ) ;
   }
   return 0 ;
}

ChainEntry::skip()
{
   to_disk  =  0 ;
   block_no =  next ;
   unsigned len_read =  len() ;
   if ( memo->file.read( next*memo->block_size, *this, &len_read ) < 0 )  return -1 ;
   if ( len_read == 0 )
   {
	  num  =  -1 ;
	  next =  -1 ;
	  set_len( 2*sizeof(long) ) ;
	  return 0 ;
   }
   if ( len_read != len() )	return memo->file.read_error() ;
   return 0 ;
}

