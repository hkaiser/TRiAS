// f4filenm.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"
extern "C" {
#include <string.h>
}

int FileName::assign( char *file_name_ptr )
{
   if ( Str::assign( file_name_ptr) < 0 )  return -1 ;
   return null_ensure() ;
}

int FileName::extension( char *new_ext, int do_replace )
{
   unsigned file_name_len =  len() ;
   unsigned ext_pos =  file_name_len ;
   char *start_ptr  =  ptr() ;

   for( unsigned on_pos = ext_pos-1;; on_pos-- )
   {
	  if ( start_ptr[on_pos] == '.' )  ext_pos =  on_pos ;
	  if ( on_pos == 0 )  break ;
   }

   if ( file_name_len != ext_pos &&  !do_replace )
   {
	  upper() ;
	  return 0 ;
   }
   set_len( ext_pos ) ;
   if ( add( StrChar('.') ) < 0 )  return -1 ;
   if ( *new_ext == '.' ) new_ext++ ;
   if ( add( StrPtr(new_ext) ) < 0 )  return -1 ;
   upper() ;
   return null_ensure() ;
}

int  FileName::path( char *extra_path )
{
   int num_slash = 0 ;
   unsigned len = strlen(extra_path) ;
   if ( len == 0 )  return 0 ;

   if ( *ptr() == '\\' )  num_slash++ ;
   if ( extra_path[len-1] == '\\' ) num_slash++ ;

   if ( num_slash == 0 )
	  if ( insert( StrChar('\\') ) < 0 )  return -1 ;
   if ( num_slash == 2 )  len-- ;

   int rc =  insert( StrLen(extra_path,len) ) ;
   upper() ;
   if ( null_ensure() < 0 )  return -1 ;
   return rc ;
}

int FileName::piece( Str& result, int give_path, int give_ext )
{
   int file_name_len =  len() ;
   if ( file_name_len == 0 )
   {
	  result.set_len( 0 ) ;
	  return 0 ;
   }

   char *start_ptr =  ptr() ;

   unsigned name_pos = 0 ;
   unsigned ext_pos =  file_name_len ;

   for( unsigned on_pos = file_name_len-1;; on_pos-- )
   {
	  switch ( start_ptr[on_pos] )
	  {
		 case '\\':
		 case ':':
		 {
			if (name_pos == 0)  name_pos =  on_pos + 1 ;
		 }
			break ;

		 case '.':
		 {
			ext_pos =  on_pos ;
		 }
			break ;
	  }

	  if ( on_pos == 0 )  break ;
   }

   unsigned pos = 0 ;
   unsigned new_len =  file_name_len ;
   if ( ! give_path )
   {
	  pos =  name_pos ;
	  new_len -=  name_pos ;
   }

   if ( ! give_ext )
	  new_len -=  file_name_len - ext_pos ;
                             
   // int rc =  result.assign( substr( pos,new_len ) ) ;             
   StrLen SL (substr( pos,new_len ));	                       // #JB950626 siehe Kommentar      
   int rc =  result.assign (SL);
   result.trim() ;
   return rc ;
}

void FileName::remove_extension()
{
   upper() ;
   char *p = ptr() ;
   for ( int i = len()-1; i >= 0; i-- )
   {
	  if ( p[i] == '.' )
	  {
		 p[i] =  0 ;
		 set_len(i) ;
		 return ;
	  }
	  if ( p[i] == '\\' )  return ;
   }
}

// f4name_char.c  Returns TRUE iff it is a valid dBase field or function name character

int f4name_char( char ch)
{
   return ( ch>='a' && ch<='z'  ||
			ch>='A' && ch<='Z'  ||
			ch>='0' && ch<='9'  ||
			ch=='\\'  ||  ch=='.'  || ch=='_'  ||  ch==':' ) ;
}
