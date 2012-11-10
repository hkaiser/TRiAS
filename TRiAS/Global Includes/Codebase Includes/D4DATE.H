// d4date.h   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#ifndef D4DATE

#define D4DATE

#ifndef D4DATA
#include "d4data.h"
#endif

class E4EXPORT  DateOperations
{
public:
   virtual   char *ptr() = 0 ;

   StrPtr cdow() ;
   StrPtr cmonth() ;
   int    day() ;        // Day of month  (1-31)
   int    dow() ;        // Day of week   (1-7)
   int    format( Str& result, char *picture ) ;
   double format_mdx() ;			      
   long   julian_day() ;
   int    month() ;      // Month of year (1-12)
   int    year() ;

   DateOperations&  init( char *, char *picture ) ;
   DateOperations&  init_today() ;

protected:
   void  init( long ) ;
} ;

class E4EXPORT  Date : public DateOperations, public Str
{
public:
   Date() ;
   Date( long ) ;
   Date( char * ) ;

   operator long() { return julian_day() ; }
   Date& operator=( Str& s ) { assign(s) ; return *this ; }

   unsigned  len()  { return 8 ; }
   char *ptr() { return dt ; }

private:
   char dt[9] ;
} ;

class E4EXPORT DField : public Field, public DateOperations
{
public:
   DField( Data *, FieldDataImage *, unsigned *last_offset_ptr ) ;
   void *operator new( size_t ) ;
   void *operator new( size_t, CodeBase * ) ;
   void operator delete( void * ) ;
   void do_delete( void * ) ;

   operator long() ;
   DField&   operator=( DField& ) ;
   DField&   operator=( Str& ) ;
   DField&   operator=( char * ) ;
   DField&   operator=( long ) ;

   void      assign( double ) ;
   unsigned  len()  { return 8 ; }
   char     *ptr()  { return Field::ptr() ; }
} ;

class E4EXPORT Time : public Str
{
public:
   Time()         { set(' ') ; time_data[8] = 0 ; }
   Time( char * ) ;

   char *ptr()    { return time_data ; }
   unsigned len() { return 8 ; }

   Time&  init_now() ;

private:
   char time_data[9] ;
} ;            



#endif
