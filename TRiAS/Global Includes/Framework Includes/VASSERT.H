// VerbAssert.H

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net

#ifndef VERB_ASSERT_

#define VERB_ASSERT_


#include <windows.h>


#ifdef __BCPLUSPLUS__
  #define DLLEXPORT _export
#else
  #define DLLEXPORT __declspec( dllexport )
#endif


extern "C" DLLEXPORT void VerboseAssert( const char* file, LONG line ) ;

#ifdef _DEBUG
  #define VASSERT( c )                     \
    if( !(c) )                             \
      VerboseAssert( __FILE__, __LINE__ )
#else
  #define VASSERT( c ) NULL
#endif


#endif // #ifndef VERB_ASSERT_
