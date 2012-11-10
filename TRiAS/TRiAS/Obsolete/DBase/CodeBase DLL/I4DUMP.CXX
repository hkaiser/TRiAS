// I4DUMP.C
// (C)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

// Displays the contents of a tag.
// Currently uses printf

#include <d4all.h>

extern "C" {
#include <stdio.h>
#include <io.h>
#include <string.h>
}

static void output( int h, char * s )
{
  write( h, s, strlen(s) ) ;
}

int Tag::dump( int out_handle, int display_all )
{
   int rc ;
   #ifndef SINGLE
	  if ( (rc = lock()) != 0 )  return rc ;
   #endif
   if ( free() < 0 )  return -1 ;
   output( out_handle, "\r\n\r\n" ) ;
   return dump_do( out_handle, 0, display_all ) ;
}

int  Tag::dump_do( int out_handle, int level, int display_all )
{
   char  out_buf[200] ;
   int rc =  down() ;  if ( rc != 0 )  return rc ;

   Block *block_on =   block() ;

   if ( block_on->leaf() && ! display_all )
   {
	  up() ;
	  return 0 ;
   }

   if ( block_on->leaf() )
   {
	  sprintf( out_buf, "\r\n\r\nLeaf Block #: %ld   Level %d\r\n\r\n", block_on->fileblock(), level ) ;
	  output( out_handle, out_buf ) ;
	  output( out_handle, "Record Number   Key\r\n" ) ;
   }
   else
   {
	  sprintf( out_buf, "\r\n\r\nBranch Block #: %ld   Level %d\r\n\r\n", block_on->fileblock(), level ) ;
	  output( out_handle, out_buf ) ;
	  #ifdef CLIPPER
		 output( out_handle, "File Block	  Record Number   Key\r\n" ) ;
	  #else
		 output( out_handle, "File Block	  Key\r\n" ) ;
	  #endif
   }

   for ( int i_key = 0; i_key < block_on->numkeys(); i_key++ )
   {
	  #ifdef OTHER_INDEX
		 #ifdef NDX
			if ( block_on->leaf() )
			   sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->recno() ) ;
			else  sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->fileblock() ) ;
		 #elif defined CLIPPER
			if ( !block_on->leaf() )
				sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->fileblock()/512 ) ;
			sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->recno() ) ;
		 #endif
	  #else
		 sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->recno() ) ;
	  #endif
	  output( out_handle, out_buf ) ;
	  if ( type() == t4str )
	  {
		 char buf[i4max_key_size] ;
		 int len =  50 ;
		 if ( len > valuelen() )  len =  valuelen() ;

		 memcpy( buf, block_on->key(i_key)->ptr(), len ) ;
		 buf[len] =  0 ;
		 output( out_handle, buf ) ;
	  }
   }

   if ( block_on->leaf() )
   {
	  up() ;
	  return 0 ;
   }

   #ifdef OTHER_INDEX
	  #ifdef NDX
		 sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->fileblock() ) ;
	  #elif defined CLIPPER
		 sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->fileblock()/512 ) ;
	  #endif
   #else
	  sprintf( out_buf, "\r\n%10ld	  ", block_on->key(i_key)->recno() ) ;
   #endif
   output( out_handle, out_buf ) ;

   block_on->go(0);
   do
   {
	  rc = dump_do( out_handle, level+1, display_all ) ;
	  if ( rc > 0 )  e4severe( e4result, "Tag::dump_do()", (char *) 0 ) ;
	  if ( rc < 0 )  return -1 ;
   } while ( block_on->skip(1) == 1 ) ;

   up() ;
   return 0 ;
}
