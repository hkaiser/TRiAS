// f4filecr.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <time.h>
#include <string.h>
}

#ifdef __ZTC__
extern volatile int  errno ;
#include <sys\locking.h>
#define L4LOCKING   
#else
// extern int errno;	#JB911211
#endif

extern "C" {
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>		// #JB911120, Typen für stat.h
#include <sys\stat.h>
#include <errno.h>
#include <stdio.h>
#include <share.h>
}

int File::create()
{
   if ( close() < 0 )  return -1 ;

   #ifdef WINDOWS
	  OFSTRUCT of_struct ;
	  if ( code_base->safety ) 
		 hand = OpenFile( name.ptr(), &of_struct, OF_EXIST ) ;  // check for file existence
	  if ( hand < 0 )  // if file doesn't exist, create
		 hand = OpenFile( name.ptr(), &of_struct, OF_CREATE | OF_READWRITE | OF_SHARE_COMPAT ) ;
   #else
	  int  extra_flag  = 0 ;
	  if ( code_base->safety )  extra_flag =  O_EXCL ;
	  hand =  ::sopen( name.ptr(), O_CREAT | O_TRUNC | extra_flag | O_BINARY | O_RDWR, SH_DENYNO, S_IREAD | S_IWRITE ) ;
   #endif
   if ( hand < 0 )
   {
	  if ( code_base->create_error )
		 return code_base->error( e4create, "File Name:", name.ptr(), (char *) 0 ) ;
	  return r4no_create ;
   }

   return 0 ;
}

int File::write( long pos, Str& str )
{
   if ( code_base->error() )  return -1 ;

   if( pos < 0 ) return 0 ;	// cannot seek a negative amount - Borland C gives no error on lseek with < 0

   #ifdef WINDOWS
	  if ( _llseek( hand, pos, 0 ) != pos )
   #else
	  if ( lseek( hand, pos, 0 )  != pos )
   #endif
		 return code_base->error( e4write, name.ptr(), (char *) 0 ) ;

   unsigned len =  str.len() ;
   #ifdef WINDOWS
	  unsigned urc =  (unsigned) _lwrite( hand, str.ptr(), len ) ;
   #else
	  unsigned urc =  (unsigned) ::write( hand, str.ptr(), len ) ;
   #endif
   if ( urc != len ) return code_base->error( e4write, name.ptr(), (char *) 0 ) ;
   return 0 ;
}

File::rename( FileName& new_name )
{
   if ( close() < 0 )  return -1 ;

   File  new_file( code_base ) ;
   if ( new_file.name.assign( new_name.ptr() ) < 0 )  return -1 ;

   if ( ! code_base->safety )
	  new_file.remove() ;

   if ( ::rename( name.ptr(), new_name.ptr() ) < 0 )
   {
	  if ( code_base->create_error )
		 return code_base->error( e4rename, "From:", name.ptr(), "To:", new_name.ptr(), (char *) 0 ) ;
	  else
		 return r4no_create ;
   }

   name.assign( new_name.ptr() ) ;
   return code_base->error() ;
}

int File::temp( int auto_remove )
{
   if ( code_base->error() )  return -1 ;
   if ( auto_remove )  is_temp =  1 ;

   int	 i ;
   time_t  t ;

   for ( i=0; i < 100; i++, t++ )
   {
	  time( &t ) ;
	  t %= 10000L ;

	  name.assign( "TEMP" ) ;
	  char buf[4] ;  StrLen str(buf,sizeof(buf)) ;
	  str.assign_long( t, 1 ) ;
	  name.add( str ) ;
	  name.extension( "TMP", 1 ) ;

	  int save_flag =  code_base->create_error ;
	  code_base->create_error =  0 ;
	  int rc =  create() ;
	  code_base->create_error =  save_flag ;
	  if ( rc < 0 )  return -1 ;
	  if ( rc == 0 )  return 0 ;
   }

   return code_base->error( e4create, "Temporary Working File", (char *) 0 ) ;
}
