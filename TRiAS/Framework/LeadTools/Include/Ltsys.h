/*
   LTSYS.H - operating system definition
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTSYS_H_
#define _LTSYS_H_

#ifdef _UNICODE
/* NOTE: if you use the non-UNICODE version of LEADTOOLS in a UNICODE app,
         then you must undefine this ! */
   #define FOR_UNICODE
   #ifndef UNICODE
      #error UNICODE and _UNICODE must be defined!!!
   #endif
#endif

#ifdef LINUX_DEFS

   #define FOR_LINUX

#elif defined(WIN64)

   #ifndef FOR_WIN64
      #define FOR_WIN64
   #endif

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined (_ALPHA_) || defined(FOR_WINCE)

   #ifndef FOR_WIN32
      #define FOR_WIN32
   #endif                          /* FOR_WIN32 */

#endif

#endif   // _LTSYS_H_
