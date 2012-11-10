// e4error.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.
// Angepaßt an die Fehlerbehandlung in DIRIS durch JB am 23. März 1992.
// Erweitert durch bedingte ERROR_HANDLING-Compilierung.

#include <d4all.h> 
#ifdef WIN32
#include <bool.h>
#endif
#include <cxxtypes.hxx>

extern "C" {
	#include <io.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <assert.h>
}

#define ERROR_HANDLING

#ifdef WINDOWS
   #ifdef __TURBOC__
	  void FAR PASCAL FatalAppExit(WORD,LPSTR) ;
   #else
	  #ifndef ERROR_HANDLING
		 extern "C" {
			void FAR PASCAL FatalAppExit(UINT,LPCSTR);
		 }
	  #else
		 extern "C" {   
		 	#ifndef WIN32
				#include <storage.h>		// LPSTORAGE 
			#else
				#include <objbase.h>		// LPSTORAGE 
			#endif	
			#include <xtension.h>	   // für DEX_Error ()
			#include <xtensnx.h>
		 }
	  #endif
   #endif
#else
extern "C" {
   #include <conio.h> }
#endif

typedef struct error_data_st
{
   int   error_num ;
   char *error_data ;
}  ERROR_DATA ;

#ifndef ERROR_HANDLING
ERROR_DATA e4error_data[] =
{
   /* General Disk Access Errors */
   { e4close,	 "Closing File" },
   { e4create,	"Creating File" },
   { e4length,	"Determining File Length" },
   { e4length_set,"Setting File Length" },
   { e4lock,	  "Locking File" },
   { e4open,	  "Opening File" },
   { e4read,	  "Reading File" },
   { e4remove,	"Removing File" },
   { e4rename,	"Renaming File" },
   { e4seek,	  "Seeking to File Position" },
   { e4unlock,	"Unlocking File" },
   { e4write,	 "Writing to File" },

   /* Database Specific Errors */
   { e4data,	  "File is not a Data File" },
   { e4field_name,"Unrecognized Field Name" },
   { e4field_type,"Unrecognized Field Type" },
   { e4record_len,"Record Length is too Large" },

   /* Index File Specific Errors */
   { e4entry,	 "Tag Entry Missing" },
   { e4index,	 "Not a Correct Index File" },
   { e4tag_name,  "Tag Name not Found" },
   { e4unique,	"Unique Key Error" },

   /* Expression Evaluation Errors */
   { e4comma_expected, "Comma or Bracket Expected" },
   { e4complete,	   "Expression not Complete" },
   { e4data_name,	  "Data File Name not Located" },
   { e4num_parms,	  "Number of Parameters is Wrong" },
   { e4overflow,	   "Overflow while Evaluating Expression" },
   { e4right_missing,  "Right Bracket Missing" },
   { e4type,		   "Sub-expression Type is Wrong" },
   { e4unrec_function, "Unrecognized Function" },
   { e4unrec_operator, "Unrecognized Operator" },
   { e4unrec_value,	"Unrecognized Value"} ,
   { e4unterminated,   "Unterminated String"} ,

   // Critical Errors 
   { e4info,	  "Unexpected Information"} ,
   { e4memory,	"Out of Memory"} ,
   { e4new,	   "Unexpected New Call"} ,
   { e4parm,	  "Unexpected Parameter"} ,
   { e4result,	"Unexpected Result"} ,
   { 0, 0 }, 
} ;
#endif

__export CodeBase::error_set( int new_err_no )
{
   int old_err_no =  error_code ;
   error_code =  new_err_no ;
   return old_err_no ;
}

void CodeBase::exit_test()
{
   if ( error_code < 0 )  exit() ;
}


#ifdef WINDOWS
   void CodeBase::exit()
   {
	  #ifndef ERROR_HANDLING
		 FatalAppExit( 0, "Exiting Application." ) ;
	  #else
		 // DEX_Error (RC_dBase, e4fatal);		  
		 FatalAppExit( 0, "Fataler Fehler beim Arbeiten mit dBASE !" ) ;
	  #endif	
   }

   CodeBase::error( const int err_no, char *, ... )
   {
   #ifndef ERROR_HANDLING
	  #ifdef DEBUG
		 if ( hWnd == 0 )
		 FatalAppExit( 0, "CodeBase::hWnd was not assigned a window handle" ) ;
	  #endif

	  error_code =  err_no ;
   
	  va_list  arg_marker  ;
	  va_start( arg_marker, msg ) ;
   
	  Str255 error_str ;
	  error_str.set_len(4) ;
	  error_str.assign_long( err_no, 0 ) ;

	  error_str.add( StrChar( '\n' ) ) ;
	  error_str.insert( StrPtr("Error #") ) ;

	  for ( int i = 0; e4error_data[i].error_data != 0; i++ )
		 if ( e4error_data[i].error_num == err_no )
		 {
			error_str.add( StrPtr(e4error_data[i].error_data) ) ;
			error_str.add( StrChar( '\n' ) ) ;
			break ;
		 }

	  char *ptr =  msg ;
	  for (; ptr != (char *) 0; ptr =  va_arg(arg_marker, char *))
	  {
		 error_str.add( StrPtr(ptr) ) ;
		 error_str.add( StrChar('\n') ) ;
	  }

	  WORD wType =  MB_OK | MB_ICONSTOP ;

	  if ( err_no == e4memory )
		 wType |=  MB_SYSTEMMODAL ;

	  if ( MessageBox( hWnd, error_str.ptr(), NULL, wType ) == 0 )
		 e4severe( e4memory, (char *) 0 ) ;
   #else
	  error_code =  err_no ;
	  DEX_Error (RC_dBase, err_no);
   #endif

	  return( err_no ) ;
   }

   void __export e4severe( const int err_no, char *, ... )
   {
   #ifndef ERROR_HANDLING
	  va_list  arg_marker  ;
	  va_start( arg_marker, msg ) ;
   
	  Str255 error_str ;
	  error_str.set_len(4) ;
	  error_str.assign_long( err_no, 0 ) ;

	  error_str.add( StrChar( ',' ) ) ;
	  error_str.add( StrChar( ' ' ) ) ;
	  error_str.insert( StrPtr("Error #") ) ;

	  for ( int i = 0; e4error_data[i].error_data != 0; i++ )
		 if ( e4error_data[i].error_num == err_no )
		 {
			error_str.add( StrPtr(e4error_data[i].error_data) ) ;
			error_str.add( StrChar( ',' ) ) ;
			error_str.add( StrChar( ' ' ) ) ;
			break ;
		 }

	  char *ptr =  msg ;
	  for (; ptr != (char *) 0; ptr =  va_arg(arg_marker, char *))
	  {
		 error_str.add( StrPtr(ptr) ) ;
		 error_str.add( StrChar( ' ' ) ) ;
	  }
	  FatalAppExit( 0, error_str.ptr() ) ;
   #else	
   {
	  DEX_Error (RC_dBase, err_no);
	  // DEX_Error (RC_dBase, e4fatal);
	  assert (FALSE); 
		}	  
   #endif
   }

#else	  // für MSDOS

   void CodeBase::exit()
   {
	  ::exit(error_code) ;
   }
   
   static void  e4error_out( char *ptr )
   {
	  write( 0, ptr, (unsigned int) strlen(ptr) ) ;
   }
   
   static void display( const int err_no )
   {
	  Str10  str ;
	  str.set_len(6) ;
	  str.assign_long( err_no, 0 ) ;
	  e4error_out( str.ptr() ) ;
   
	  for ( int i = 0; e4error_data[i].error_data != 0; i++ )
		 if ( e4error_data[i].error_num == err_no )
		 {
			e4error_out( "\r\n" ) ;
			e4error_out( e4error_data[i].error_data ) ;
			break ;
		 }
   }
   
   CodeBase::error( const int err_no, char *msg, ... )
   {
	  error_code =  err_no ;
   
	  va_list  arg_marker  ;
	  va_start( arg_marker, msg ) ;

	  e4error_out( "\r\n\r\nError Number" ) ;
	  display ( err_no ) ;
   
	  char *ptr =  msg ;
	  for (; ptr != (char *) 0; ptr =  va_arg(arg_marker, char *))
	  {
		 e4error_out( "\r\n" ) ;
		 e4error_out( ptr ) ;
	  }
   
	  e4error_out( "\r\nPress a key ..." ) ;
	  getch() ;

	  return( err_no ) ;
   }
   
   void __export e4severe( const int err_no, char *msg, ... )
   {
	  va_list  arg_marker  ;
	  va_start( arg_marker, msg ) ;
   
	  e4error_out( "\r\n\r\nSevere Error Number" ) ;
	  display( err_no ) ;
   
	  char *ptr =  msg ;
	  for (; ptr != (char *) 0; ptr =  va_arg(arg_marker, char *))
	  {
		 e4error_out( "\r\n" ) ;
		 e4error_out( ptr ) ;
	  }
   
	  e4error_out( "\r\nPress a key ..." ) ;
	  getch() ;
   
	  exit(1) ;
   }

#endif
