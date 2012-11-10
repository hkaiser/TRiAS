// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\portability.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined PORTABILITY_INCLUDED
#define PORTABILITY_INCLUDED

/* Comment Shorthand @-codes

   @ni  not-inline because...
      dep - to prevent dependancies.  Putting the implementation in the header would require
         more #include's in that header.  Putting it in a Cpp file means that a forward-declaration
         will do, if it's needed at all.
      size - to optomize for size.  A "simple" function that might be a candidate for inlining
         may involve more parameters or two or more function calls.  The work done is complex
         so it's not worth saving the time of one more function call.
*/

#if defined DOUBLE_BAGGED
# define STARTWRAP  namespace Dlugosz {
# define ENDWRAP  } //end namespace
#else
// Microsoft Visual C++ 5.0 has problems <sigh!>
# define STARTWRAP /* nothing */
# define ENDWRAP  /* nothing */
#endif

#if defined _MSC_VER 
#if _MSC_VER >= 1200  //v6.0 or higher
 # define ccfg_PLACEMENT_DELETE
#endif
#if _MSC_VER >= 1100  //reported by v5.0
   // bool is supported.
   #pragma warning (disable:4800)
   // not related to bool issues, but a handy place to put these.
   #pragma warning (disable:4250)  //dominance during inheritance
   #pragma warning (disable:4355)  //using 'this' in initialization list
   #pragma warning (disable:4244)  //loss of significance in conversion
   #pragma warning (disable:4661)  //hidden template bodies
#elif !defined bool
#if _MSC_VER == 1020  //reported by v4.2
 #include <yvals.h>
#else
 # define bool int
 # define true 1
 # define false 0
#endif
#endif  //_MSC_VER

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#if _MSC_VER < 1100
#define explicit /*not supported*/
#endif

#endif    //Microsoft C


#endif

