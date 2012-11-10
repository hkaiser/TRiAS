// d4datafi.h  (c)Copyright Sequiter Software Inc., 1990-1991.	All rights reserved.

#ifndef D4DATAFI

#define D4DATAFI

#ifndef D4DATA
#include "d4data.h"
#endif

#ifdef __DLL__
#define D4DLLS
#endif

#ifdef DLL
#define D4DLLS
#endif

#ifdef WINDOWS                 // #JB920618
   #ifdef D4DLLS 
      extern "C" {
      typedef int FAR PASCAL CALL_BACK( void * ) ; 
      }
      #define FILTER_FUNCTION int FAR PASCAL FN_EXP
      #include "e4error.h"
   #else
      typedef int CALL_BACK( void * ) ;
      #define FILTER_FUNCTION int
   #endif   // D4DLLS
#else     // WINDOWS
   typedef int CALL_BACK (void* );
   #define FILTER_FUNCTION int
#endif    // WINDOWS


class E4EXPORT DataFilter
{
public:
   DataFilter() ;

   int  bottom() ;
   
   void DataFilter::filter( DataIndex *data_ptr, CALL_BACK *cb_filter, void *filter_data=0 )
   {
      data =  data_ptr ;
      code_base =  data->code_base ;
      #ifndef WINDOWS              // #JB951102
         #ifdef D4DLLS  
            if ( code_base->hInst == (HANDLE) 0 ) 
            e4severe( e4info, "Error: must set CodeBase.hInst if using a DLL", (char *) 0 ) ;
            FARPROC lpfnfilter_routine = MakeProcInstance( (FARPROC) cb_filter,
                                                           code_base->hInst ) ;
            routine = (CALL_BACK *)lpfnfilter_routine ;
         #else       // D4DLLS
            routine   =  cb_filter ;
         #endif
     #else      // WINDOWS
        routine = cb_filter;
     #endif    
      routine_data =  filter_data ;
   }
   int  filter_test() ;  // TRUE - keep record.
   int  find_good(int) ;  // Go to the first legitimate record, current ?
   int  go( long ) ;
   int  seek( double ) ;
   int  seek( Str& ) ;
   int  seek( char *p )        { return seek(StrPtr(p)) ; }
   int  skip( long n = 1L ) ;
   int  top() ;
protected:
   int   filter_go_eof() ;
   int   seek_do( int rc ) ;

   DataIndex  *data ;
   CodeBase   *code_base ;
   CALL_BACK *routine ;
   void  *routine_data ;
} ;

class E4EXPORT ExtDataFilter : public DataFilter
{
public:
   // Konstruktor/Destruktor
   ExtDataFilter (void);
   ~ ExtDataFilter (void);

// sonstige Member
// ff. Funktionen wurden speziell fÅr die Komplex-Recherche geschaffen
   int	seek_on (double d, long SkipVal = 1);
   int	seek_on (Str& s, long SkipVal = 1);
   int	seek_on (char *p, long SkipVal = 1);
};

#endif
