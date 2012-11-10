// f4filese.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

extern "C" {
#include <io.h>
#include <string.h>
#include <limits.h>
}

FileSeqRead::FileSeqRead() 
{
   buffer = 0 ;
   file   = 0 ;
}

void  FileSeqRead::init( File& file_parm, long start_offset, Str& str )
{
   total =  str.len() & 0xFC00 ;  // Make it a multiple of 1K
   pos   =  start_offset ;

   buffer=  str.ptr() ;
   avail =  0 ;
   next_read_len =  total - unsigned(start_offset % 0x400) ;
   file  =  &file_parm ;
}

int FileSeqRead::read( Str& str )
{
   unsigned len_read, start_len ;
   len_read =  start_len =  str.len() ;

   if ( read( str, &len_read ) < 0 )  return -1 ;
   if ( len_read != start_len )   return file->read_error() ;

   return 0 ;
}

int FileSeqRead::read( Str& str, unsigned *len_ptr )
{
   if ( file->code_base->error() )  return -1 ;
   #ifdef DEBUG
	  if ( file == 0 ) e4severe( e4info, "FileSeqRead::read", (char *) 0);
   #endif

   str.set_len( *len_ptr ) ;
   if ( str.len() < *len_ptr )  *len_ptr =  str.len() ;

   if ( buffer == 0 )
   {
	  int rc =  file->read( pos, str, len_ptr ) ;
	  str.set_len( *len_ptr ) ;
	  pos +=  *len_ptr ;
	  return rc ;
   }

   char *ptr =  str.ptr() ;

   if ( avail == 0 )
   {
	  if( pos < 0 ) return 0 ;	// cannot seek a negative amount - Borland C gives no error on lseek with < 0

	  #ifdef WINDOWS
		 long lrc =  _llseek( file->hand, pos, 0 ) ;
	  #else
		 long lrc =  lseek( file->hand, pos, 0 ) ;
	  #endif
	  if ( lrc < 0 )  return   file->read_error() ;

	  #ifdef WINDOWS
		 avail =  working =  (unsigned) _lread( file->hand, buffer, next_read_len ) ;
	  #else
		 avail =  working =  (unsigned) ::read( file->hand, buffer, next_read_len ) ;
	  #endif
	  if ( working == UINT_MAX )  return file->read_error() ;
	  #ifdef DEBUG
		 // Make sure reading is aligned correctly for maximum speed
		 if ( (pos+next_read_len) % 0x400  != 0  &&  avail != 0 )
			e4severe( e4result, "FileSeqRead::read()", (char *) 0 ) ;
	  #endif
	  pos +=  working ;
	  next_read_len =  total ;
   }

   if ( avail >= *len_ptr )
   {
	  unsigned  buffer_i =  working-avail ;
	  memcpy( ptr, buffer+ buffer_i, *len_ptr ) ;
	  avail -= *len_ptr ;
	  return 0 ;
   }
   else
   {
	  if ( avail == 0 )
	  {
		 *len_ptr =  0 ;
		 str.set_len(0) ;
		 return 0 ;
	  }

	  unsigned  buffer_i =  working-avail ;
	  memcpy( ptr, buffer+ buffer_i, avail ) ;

	  unsigned  copy_bytes =  avail ;
	  avail =  0 ;

	  *len_ptr -=  copy_bytes ;
	  // if (  read( str.substr(copy_bytes,*len_ptr), len_ptr ) < 0 ) 
	  str.substr (copy_bytes,*len_ptr);
	  if (  read( str, len_ptr ) < 0 ) 		  // #JB950626 siehe Kommentar
	  	return -1 ;

	  *len_ptr +=  copy_bytes ;
	  return  0 ;
   }
}


FileSeqWrite::FileSeqWrite() 
{
   buffer = 0 ;
   file   = 0 ;
}

int FileSeqWrite::flush()
{
   if ( file->code_base->error() )  return -1 ;
   if ( buffer == 0 )  return 0 ;

   if( pos < 0 ) return 0 ;	// cannot seek a negative amount - Borland C gives no error on lseek with < 0

   #ifdef WINDOWS
	  if ( _llseek( file->hand, pos, 0 ) != pos )
   #else
	  if ( lseek( file->hand, pos, 0) != pos )
   #endif
		 file->code_base->error( e4write, file->name.ptr(), (char *) 0 ) ;

   unsigned to_write =  working-avail ;

   #ifdef WINDOWS
	  if ( (unsigned) _lwrite( file->hand, buffer, to_write) != to_write)
   #else
	  if ( (unsigned) ::write( file->hand, buffer, to_write) != to_write)
   #endif
	  return file->code_base->error( e4write, file->name.ptr(), (char *) 0 ) ;

   pos +=  to_write ;

   avail =  working =  total ;
   return 0 ;
}

void  FileSeqWrite::init( File& file_parm, long start_offset, Str& str )
{
   file =  &file_parm ;

   total =  str.len() & 0xFC00 ;  // Make it a multiple of 1K
   pos =  start_offset ;

   buffer =  str.ptr() ;
   avail =  working =  total - unsigned(start_offset % 0x400) ;
}

int  FileSeqWrite::repeat( long n, char ch )
{
   char buf[512] ;
   StrMax str( buf, sizeof(buf) ) ;
   str.set(ch) ;

   while ( n > sizeof(buf) )
   {
	  if ( write(str) < 0 )  return -1 ;
	  n -= sizeof(buf) ;
   }
   str.set_len( (unsigned) n ) ;
   return write(str) ;
}

int  FileSeqWrite::write( Str& str )
{
   if ( file->code_base->error() )  return -1 ;

   void	*ptr =  str.ptr() ;
   unsigned len =  str.len() ;

   if ( buffer == 0 )
   {
	  int rc =  file->write( pos, str ) ;
	  pos +=  str.len() ;
	  return rc ;
   }

   if ( avail == 0 )
	  if ( flush() < 0 )  return -1 ;

   #ifdef DEBUG
	  if ( avail <= 0 )
		 e4severe( e4info, "FileSeqWrite::write", (char *) 0 ) ;
   #endif

   if ( avail >= len )
   {
	  #ifdef DEBUG
		 if ( working < avail ||  working-avail+len > total )
			e4severe( e4result, "FileSeqWrite::write()", (char *) 0 ) ;
	  #endif
	  memcpy( buffer+ (working-avail), ptr, len ) ;
	  avail -= len ;
	  return 0 ;
   }
   else
   {
	  unsigned  first_len =  avail ;

	  #ifdef DEBUG
		 if ( working < avail || working > total )
			e4severe( e4result, "FileSeqWrite::write()", (char *) 0 ) ;
	  #endif
	  memcpy( buffer+ (working-avail), ptr, avail ) ;
	  avail =  0 ;
                                      
	  // return write( str.substr(first_len, len-first_len) ) ;  // Recursive call
	  str.substr(first_len, len-first_len);		// #JB950626 siehe Kommentar
	  return write( str) ; 		  		  	
   }
}
