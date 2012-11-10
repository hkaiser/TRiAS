

#ifndef _defs_h_
#define _defs_h_





/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */



// Check that a platform is defined:
#if !defined(__UNIX__) && !defined(WINDOWS) && !defined(__MS_WINDOWS__)
#if !defined(MSDOS) && !defined(__DOS__) && !defined(__WINDOWS__)
#if !defined(__OS2__) && !defined(WIN32) && !defined(__MS_WIN32__)
#error (defs.h) Unsupported platform: define __UNIX__, WINDOWS, MSDOS, WIN32 or OS2
#endif
#endif
#endif

#ifdef __GNUC__
#pragma interface
#endif

#ifdef __BORLANDC__
#pragma warn -inl // No warnings about inline functions
#endif


#if defined(__BORLANDC__)
#   include "base/bordll.h"
#elif defined(_MSC_VER)
#   include "base/msvcdll.h"
#elif defined(__WATCOMC__)
#   include "base/watcmdll.h"
#endif




#ifndef YACL_BASE
#    define YACL_BASE
#    define YACL_BASEFUNC
#endif


#define CL_EXPORTFUNC YACL_BASE   // For backward compatibility. YACL code
#define CL_EXPORT     YACL_BASE   // does not use these definitions any more.




// -------------------- Essential typedefs -----------------------

typedef unsigned short ushort;
typedef unsigned long  ulong;
typedef unsigned char  uchar;
typedef void*          CL_VoidPtr;
#if defined(__BORLANDC__)
#if (__BCPLUSPLUS__ <= 0x330)
typedef uchar          bool;
#endif
#else
#if !defined(__GNUC__) || __GNUC_MINOR__ <= 6
//typedef uchar          bool;
#endif
#endif



// ---------------------- #define'd symbols -----------------------


// Use CL_CASTDOWN for safe downcasting. It uses RTTI if available.
#ifndef RTTI
#define CL_CAST_REF(type, obj) ((type) (obj))
#define CL_CAST_PTR(type, obj) ((type) (obj))
#else
#define CL_CAST_REF(type, obj) (dynamic_cast<type> (obj))
#define CL_CAST_PTR(type, obj) (dynamic_cast<type> (obj))
#endif


#include <stddef.h>

#ifndef TRUE
#    if defined(__MS_WINDOWS__)
#        define TRUE  1
#        define FALSE 0
#    else
#        define TRUE  ((bool) 1)
#        define FALSE ((bool) 0)
#    endif
#endif


#if defined (__MSDOS__) || defined (__MS_WINDOWS__)
#define __FAR  __far
#define __HUGE __huge
#else
#define __FAR
#define __HUGE
#endif

#ifndef NO_DEBUG
#include "base/error.h"
#define assert(cond,params) if (!(cond)) CL_Error::Fatal params
#else
#define assert(cond, params)
#endif


#ifndef NULL
#define NULL  0L
#endif





// ------------------------- Inline functions -------------------------

#ifdef __GNUC__
#pragma implementation // Force code generation for minl and maxl
#endif

inline long minl (long x, long y)
{
    return (x < y) ? x : y;
}


inline long maxl (long x, long y)
{
    return (x > y) ? x : y;
}

#include "base/version.h"


#endif


