// f4filese.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef F4FILESE

#define  F4FILESE

#ifndef D4DATA
#include "d4data.h"
#endif

// FileSeqRead and FileSeqWrite always do 'lseek' before read/write.
class E4EXPORT FileSeqRead
{
public:
   FileSeqRead() ;
   void init( File&, long start_pos, Str& buffer ) ;
   int  read( Str& ) ;
   int  read( Str&, unsigned *len ) ;

   File *file ;

private:
   long  pos ;          // The next position to read from
   char *buffer ;
   unsigned next_read_len ;
   unsigned total ;     // Total buffer length
   unsigned working ;   // Temporary working buffer length (to help align write)
   unsigned avail ;     // # of bytes currently available
} ;

class E4EXPORT FileSeqWrite
{
public:
   FileSeqWrite() ;
   int  flush() ;
   void init( File&, long start_pos, Str& buffer ) ;
   int  repeat( long, char ) ;  // Writes character repeatedly
   int  write( Str& ) ;

   File *file ;

private:
   long  pos ;          // The next position to read from
   char *buffer ;
   unsigned total ;     // Total buffer length
   unsigned working ;   // Temporary working buffer length (to help align write)
   unsigned avail ;     // # of bytes left in working buffer
} ;

// Miscellaneous File Routines
int D4DLL_EXP  f4name_char( char ) ;


#endif
