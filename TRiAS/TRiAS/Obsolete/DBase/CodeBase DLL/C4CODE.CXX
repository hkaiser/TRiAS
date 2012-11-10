// c4code.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

#ifdef __TURBOC__
   #ifndef __DLL__
   #ifdef DEBUG
	  extern unsigned _stklen ;
   #endif
   #endif
#endif

extern "C" {
#include <string.h>
}

__export CodeBase::CodeBase()
{
   #ifdef DEBUG
	  // if a DLL, can't check the stack length since this is a seperate executable
	  #ifndef __DLL__
	  #ifdef __TURBOC__
		 if ( _stklen < 6000 ) // 6000 seems to be an appropriate minimum
			e4severe( e4result, "Stack length variable _stklen below minimum.", (char *) 0 ) ;
	  #endif
	  #endif
   #endif

   #ifdef CLIPPER
	  numeric_str_len  = 10 ;	// default length for clipper numeric keys is 10
	  decimals		 =  0 ;
   #else
	  numeric_str_len  = 17 ;
	  decimals		 =  2 ;
   #endif
   block_size	   =  0x400 ;   // 1024

   blocks_start	 = 10 ;
   blocks_expand	=  5 ;

   sort_pool_size   =  0xFFC0 ;
   sort_buffer_size =  0x1000 ;  // 4096
   buffer_size	  =  0x4000 ;  // 16384

   default_unique_error =  r4unique_continue ;
   date_format( "MM/DD/YY" ) ;

   error_code	=  0 ;

   // Flags initialization
   go_error=  open_error=  create_error =  skip_error =  tag_name_error
		   =  auto_open =  field_name_error =  read_lock =  safety =  wait =  1;

   otherndx_memory = index_memory =  field_memory =  dfield_memory =
	  mfield_memory = nfield_memory =  0 ;
   memset( string_types, 0, sizeof(string_types) ) ;

   hWnd =  0 ;
   hInst = 0 ;
//   str_buffer = new String( this ) ;
//   if ( str_buffer == 0 )
//	  e4severe( e4memory, "Memory allocation failure" ) ;
}

__export CodeBase::~CodeBase()
{
   close_all() ;

   m4release( otherndx_memory ) ;
   m4release( index_memory ) ;
   m4release( field_memory ) ;
   m4release( dfield_memory ) ;
   m4release( mfield_memory ) ;
   m4release( nfield_memory ) ;

//   delete str_buffer ;

   for ( int i = 0; i < 16; i++ )
	  m4release( string_types[i] ) ;
}

int  CodeBase::close_all()
{
   LinkIterator next( data_list ) ;

   int rc, rc_return = 0 ;
   for ( Data *data_on; data_on = (Data *) next(); )
	  if ( (rc =  data_on->close()) > 0 )  rc_return =  rc ;
   if ( error() < 0 )  return -1 ;
   return rc_return ;
}

char *CodeBase::date_format( char *new_format )
{
   if ( new_format != 0 )
   {
	  StrMax m( date_format_info, sizeof(date_format_info) ) ;
	  m.assign( new_format ) ;
	  m.null_ensure() ;
   }

   return date_format_info ;
}
