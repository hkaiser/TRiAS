// f4file.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

#ifndef L4NO_LOCK
#define L4NO_LOCK			// #JB951103 --> "locking ()" arbeitet nicht mit HFILE (OpenFile ())
#endif

extern "C" {
	#include <time.h>
	#include <string.h>
#ifdef _DEBUG
	#include <stdlib.h>		// _MAX_PATH
#endif 			
}

#ifdef __ZTC__
extern volatile int  errno ;
extern "C" {
#include <sys\locking.h>
}
#else
#ifndef L4NO_LOCK
  #define L4LOCKING	  // #JB911211
  extern "C" {
  #include <sys\locking.h> 
  }
#endif

// extern int errno ;  // #JB911211
#endif

extern "C" {
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>  // Typen für stat.h, #JB911120
#include <sys\stat.h>
#include <errno.h>
#include <stdio.h>
#include <share.h>
}

File::File(CodeBase *cb) : name( cb )
{
   code_base =  cb ;
   hand =  -1 ;
   is_temp =  0 ;
}

int File::close()
{
   if ( hand < 0 )  return 0 ;
   #ifdef WINDOWS
	  int rc = _lclose(hand) ;
   #else
	  int rc =  ::close(hand) ;
   #endif
   hand = -1 ;
   if ( rc < 0 )  return code_base->error( e4close, name.ptr(), (char *) 0 ) ;
   if ( is_temp )
   {
	  is_temp =  0 ;
	  if ( remove() < 0 )  return -1 ;
   }
   return 0 ;
}


long File::len()
{
   if ( code_base->error() )  return -1 ;
   // long lrc =  filelength( hand ) ;			// #JB951103 --> läuft nicht mit OpenFile
   long lOldPos = _llseek (hand, 0L, SEEK_CUR);	// alte Position speichern
   long lrc = _llseek (hand, 0L, SEEK_END);		// ans akt. Ende und Länge lesen
	_llseek (hand, lOldPos, SEEK_SET);			// auf alte Position
   if ( lrc < 0L )  code_base->error( e4length, name.ptr(), (char *) 0 ) ;
   return  lrc ;
}

int File::lock( long o_set, long num_bytes )
{
   if ( code_base->error() )  return -1 ;

   #ifdef DEBUG
	  if( o_set < 0 )   e4severe( e4parm,"invalid lock position",(char *) 0 ) ;
   #endif

   #ifdef L4NO_LOCK
	  return 0 ;
   #else
	  int	   rc ;
	  errno =  0 ;
	  #ifdef L4LOCKING
		 #ifdef WINDOWS
			_llseek( hand, o_set, 0 ) ;
		 #else
			lseek( hand, o_set, 0 ) ;
		 #endif
		 rc =  ::locking( hand, LK_NBLCK, num_bytes ) ;
	  #else
		 rc =  ::lock( hand, o_set, num_bytes ) ;
	  #endif
	  if (rc == 0 ||  errno == EINVAL)
	  {
		 #ifdef L4LOCK_CHECK
			l4lock_save( hand, o_set, num_bytes ) ;
		 #endif
		 return( 0) ;  /* Single User or Success */
	  }
   
	  int dummy = errno ;	// for debugging, since in DLL can't see errno

	  if (errno != EACCES)
		 return code_base->error( e4lock, name.ptr(), (char *) 0 ) ;
   
	  if ( ! code_base->wait )  return( r4locked ) ;
   
	  for(;;)
	  {
		 time_t  old_time ;
   
		 time( &old_time) ;   /* wait a second & try lock again */
		 while (  time( (time_t *) 0 ) <=  old_time)	;
   
		 #ifdef L4LOCKING
			#ifdef WINDOWS
			   _llseek( hand, o_set, 0 ) ;
			#else
			   lseek( hand, o_set, 0 ) ;
			#endif
			rc =  ::locking( hand, LK_NBLCK, num_bytes ) ;
		 #else
			rc =  ::lock( hand, o_set, num_bytes ) ;
		 #endif
		 if ( rc == 0 )
		 {
			#ifdef L4LOCK_CHECK
			   l4lock_save( hand, o_set, num_bytes ) ;
			#endif
			return( 0) ;
		 }
	  }
   #endif
}

int File::open()
{
   if ( code_base->error() )  return -1 ;
   is_temp =  0 ;
   #ifdef DEBUG
	  if ( hand >= 0 )
		 e4severe( e4info, "File::open", "File already open", (char *) 0 ) ;
   #endif

   #ifdef WINDOWS        
   #ifdef _DEBUG         				// #JB960626
	  char FullName [_MAX_PATH] = "";    
	  wsprintf (FullName, "FullName: %s\n", name.ptr ());
   	  OutputDebugString (FullName);	
   #endif  	// _DEBUG	   	  
	  OFSTRUCT of_struct ;
	  hand = OpenFile( name.ptr(), &of_struct, OF_READWRITE | OF_SHARE_COMPAT ) ;
   #else
	  hand =  ::sopen( name.ptr(), O_BINARY | O_RDWR , SH_DENYNO, S_IREAD | S_IWRITE ) ;
   #endif
   if ( hand < 0 )
   {
	  if ( code_base->open_error )
		 return  code_base->error( e4open, "File Name:", name.ptr(), (char *) 0 ) ;
	  else
		 return  r4no_open ;
   }

   return 0 ;
}

int  File::read( long pos, Str& str )
{
   if ( code_base->error() )  return -1 ;

   if( pos < 0 ) return 0 ;	// cannot seek a negative amount - Borland C gives no error on lseek with < 0

   #ifdef WINDOWS
	  long rc = _llseek( hand, pos, 0 ) ;
   #else
	  long  rc =  lseek( hand, pos, 0 ) ;
   #endif
   if ( rc != pos )
	  return code_base->error( e4read, name.ptr(), (char *) 0 ) ;

   unsigned len_read =  str.len() ;
   #ifdef WINDOWS
	  unsigned urc =  (unsigned) _lread( hand, str.ptr(), len_read ) ;
   #else
	  unsigned urc =  (unsigned) ::read( hand, str.ptr(), len_read ) ;
   #endif
   if ( urc != len_read )
	  return code_base->error( e4read, name.ptr(), (char *) 0 ) ;

   return 0 ;
}

int  File::read( long pos, Str& str, unsigned *count )
{
   if ( code_base->error() )  return -1 ;

   if( pos < 0 ) return 0 ;	// cannot seek a negative amount - Borland C gives no error on lseek with < 0

   #ifdef WINDOWS
	  long rc = _llseek( hand, pos, 0 ) ;
   #else
	  long  rc =  lseek( hand, pos, 0 ) ;
   #endif
   if ( rc != pos )
	  return code_base->error( e4read, name.ptr(), (char *) 0 ) ;

   str.set_len( *count ) ;
   unsigned str_len =  str.len() ;
   if ( code_base->error() )  return -1 ;

   if ( str_len < *count )  *count =  str_len ;

   #ifdef WINDOWS
	  unsigned urc =  (unsigned) _lread( hand, str.ptr(), *count ) ;
   #else
	  unsigned urc =  (unsigned) ::read( hand, str.ptr(), *count ) ;
   #endif
   if ( urc != *count )
   {
	  if ( urc > *count )
		 return code_base->error( e4read, name.ptr(), (char *) 0 ) ;

	  *count =  urc ;
	  str.set_len( *count ) ;
	  if ( (str_len = str.len()) > *count )
		 str.ptr()[*count] =  0 ;
   }
   return 0 ;
}

File::read_error()
{
   return code_base->error( e4read, "File Name:", name.ptr(), (char *) 0 ) ;
}

File::remove()
{
   if ( close() < 0 )  return -1 ;
   if ( ::remove( name.ptr() ) != 0 )  return 1 ;
   return 0 ;
}


File::set_len( long new_size )
{
   	if ( code_base->error() )  return -1 ;

   	// int rc =  chsize( hand, new_size ) ;			// #JB951103 --> läuft nicht mit HFILE (OpenFile ())
	int rc = r4success;
   	_lclose (hand);									// alte Datei schließen				
   	if((hand = _open(name.ptr(), _O_WRONLY))  != -1 )	// neu öffnen
   	{
       	rc = _chsize (hand, new_size);				// Länge neu setzen
	   	_close (hand);								// wieder schließen
	   	if (rc == 0)
	   	{
			hand = -1;								// wird ungültig
	   		rc = open ();							// und neu öffnen
	   	}
	}
	else
		rc == -1;									// Fehler beim Öffnen

   	if ( rc < 0 )
	  	return code_base->error( e4length_set, "File Name:", name.ptr(), (char *) 0 ) ;
   	return 0 ;
}

int File::unlock( long pos, long num_bytes )
{
   if ( code_base->error() )  return -1 ;

   #ifndef L4NO_LOCK
	  int	   rc ;
   
	  #ifdef L4LOCK_CHECK
		 l4lock_remove( hand, pos, num_bytes ) ;
	  #endif
   
	  errno =  0 ;
	  #ifdef L4LOCKING
		 #ifdef WINDOWS
			_llseek( hand, pos, 0 ) ;
		 #else
			lseek( hand, pos, 0 ) ;
		 #endif
		 rc =  ::locking( hand, LK_UNLCK, num_bytes ) ;
	  #else
		 rc =  ::unlock( hand, pos, num_bytes ) ;
	  #endif
	  if (rc < 0  && errno != EINVAL )
		 return code_base->error( e4unlock, name.ptr(), (char *) 0 ) ;
   #endif

   return 0 ;
}

