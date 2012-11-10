// c4.h  Conversion Routines  (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef C4HINCL

#define C4HINCL

#ifndef D4DATA
#include "d4data.h"
#endif

#ifndef I4INDEX
#include "i4index.h"
#endif

#ifdef WINDOWS
#define M4MAX_DBL_ACCURACY 15
#else
#define M4MAX_DBL_ACCURACY 16
#endif

typedef unsigned size_t ;
class E4EXPORT  Str ;

typedef struct
{
   unsigned  sig_dig : 8 ;  /* The number of significant digits; 52 is zero */
   #ifndef __ZTC__ 
      // Turbo C++ and __GCXX__ order
      unsigned  one  : 2 ;     /* Always 1 */
      unsigned  len  : 5 ;     /* The number of encoded digits */
      unsigned  sign : 1 ;     /* The sign of the digits */
   #else   
      unsigned  sign : 1 ;     /* The sign of the digits */
      unsigned  len  : 5 ;     /* The number of encoded digits */
      unsigned  one  : 2 ;     /* Always 1 */
   #endif
   unsigned  char  bcd[10] ;
}  BCD ;

double D4DLL_EXP c4atod( char *, int) ;
int    D4DLL_EXP c4atoi( char *, int) ;
long   D4DLL_EXP c4atol( char *, int) ;
void   D4DLL_EXP c4dtoa( double, char *, int, int ) ;
void   D4DLL_EXP c4encode( char *, char *, char *, char *) ;
void   D4DLL_EXP c4ltoa( long, char *, int) ;
extern "C" {
TAG_CMP_FUNC c4bcd_cmp( const void *, const void *, size_t dummy_len ) ;
}
void  D4DLL_EXP c4stob( Str&, Str& ) ;
void  D4DLL_EXP c4dtob( Str&, double ) ;
// double c4btod( void * ) ;

int D4DLL_EXP c4clip( char *, int ) ;

#endif
