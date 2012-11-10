// b4block.c  (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C"{
#include <string.h>
}

void *Block::operator new( size_t )
{
   return 0 ;
}

void *Block::operator new( size_t , Tag&t, long fb )
{
   MemoryType *mt =  t.index->block_alloc ;
   Block *block_on = (Block *) mt->alloc() ;
   if ( block_on == 0 )
   {
	  t.code_base->error( e4memory, (char *) 0 ) ;
	  return 0 ;
   }

   block_on->tag =  &t ;
   block_on->file_block =  fb ;
   block_on->key_on =  0 ;
   block_on->changed=  0 ;
   memset( &block_on->n_keys, 0, t.index->block_rw_len() ) ;
   return block_on ;
}

void Block::operator delete( void *p )
{
   Block *block_on =  (Block *) p ;
   #ifdef DEBUG
	  if ( block_on->changed )  e4severe( e4info, "Block::operator delete", (char *) 0 ) ;
   #endif
   MemoryType *mt =  block_on->tag->index->block_alloc ;
   mt->free(p) ;
}

int Block::flush()
{
   if ( changed )
   {
	  int rc =  tag->index->file.write((long)file_block*i4multiply, StrLen(&n_keys,len()));
	  if ( rc < 0 )  return rc ;
	  changed =  0 ;
   }
   return 0 ;
}

void  Block::insert( void *k, long r )
{
   #ifdef DEBUG
	  if ( k == 0 || r <= 0L )  
		 e4severe( e4parm, "Block::insert", (char *) 0 ) ;
   #endif

   KeyData *data_ptr  =  key() ;
   KeyData *next_ptr=  key( keypos()+1 ) ;

   int left_len =  tag->index->block_rw_len() -  (keypos()+1) * tag->grouplen() -
				   sizeof(short) - sizeof(char[6]) ;

   #ifdef DEBUG
	  if ( keypos() < 0  ||  keypos() > numkeys()  ||  left_len < 0 )
		 e4severe( e4info, "Block::insert", (char *) 0 ) ;
   #endif

   memmove( next_ptr, data_ptr, left_len ) ;
   n_keys++ ;
   memcpy( data_ptr->value, k, tag->valuelen() ) ;
   memcpy( &data_ptr->rec_num, &r, sizeof(r) ) ;
   changed =  1 ;
}

KeyData * __export Block::key( int i_key )
{
   return  (KeyData *) ((char *) &data + tag->grouplen()*i_key) ;
}

char *Block::key_data( int i_key )
{
   return  key(i_key)->value ;
}

int Block::lastpos()
{
   if ( leaf() )
	  return n_keys - 1 ;
   else
	  return n_keys ;
}

int Block::leaf()
{
   KeyData *key_ptr =  key( numkeys() ) ;
   return( key_ptr->rec_num == 0L ) ;
}

unsigned  Block::len()
{
   return tag->index->block_rw_len() ;
}

long  Block::recno()
{
   return key()->rec_num ;
}

void  Block::remove()
{
   KeyData *key_on  =  key() ;
   KeyData *key_next=  key( keypos()+1 ) ;

   int left_len =  len() - sizeof(n_keys) - sizeof(dummy) 
						 - (keypos()+1) * tag->grouplen() ;

   #ifdef DEBUG
	  if ( keypos() < 0  ||  keypos() > lastpos() )
		 e4severe( e4info, "Block::remove", (char *) 0 ) ;
   #endif

   if ( left_len > 0 )
	  memmove( key_on, key_next, left_len ) ;
   n_keys-- ;
   changed =  1 ;
}

int  Block::room()
{
   return( n_keys < tag->keysmax() ) ;
}

int  Block::seek( Str& str )
{
   void *search_value =  str.ptr() ;
   unsigned len =  str.len() ;
   #ifdef DEBUG
	  if ( len > (unsigned) tag->valuelen() )		// #JB950623
		 e4severe( e4parm, "Block::seek", (char *) 0 ) ;
   #endif

   // key_on must be between  key_lower and  key_upper
   int key_lower = -1 ;
   int key_upper = numkeys() ;

   T4CMP_ROUTINE *cmp =  tag->cmp ;

   if ( key_upper == 0 )
   {
	  go(0) ;
	  return r4after ;
   }

   int  save_rc =  1 ;

   for(;;)  // Repeat until the key is found
   {
	  int  key_on  =  (key_upper + key_lower) / 2  ;
	  int  rc =  (*cmp)( key_data(key_on), search_value, len ) ;

	  if ( rc >= 0 )
	  {
		 key_upper =  key_on ;
		 save_rc =  rc ;
	  }
	  else
		 key_lower =  key_on ;

	  if ( key_lower >= (key_upper-1) )  // then there is no exact match
	  {
		 go( key_upper ) ;
		 if ( save_rc )  return r4after ;
		 return 0 ;
	  }
   }
}

int Block::skip( long n )
{
   int num_left ;

   if ( n > 0 )
   {
	  num_left = numkeys() - keypos() ;
	  if ( leaf() )
		 if ( num_left != 0 )
			num_left -- ;
   }
   else
	  num_left =  -keypos() ;

   if ( ( n <= 0 ) ?  (num_left <= n)  :  (num_left >= n)  )
   {
	  go( keypos()+ (int) n ) ;
	  return (int) n ;
   }
   else
   {
	  go( keypos()+num_left ) ;
	  return num_left ;
   }
}
