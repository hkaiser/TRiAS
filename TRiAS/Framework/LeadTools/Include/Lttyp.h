/*
   LTTYP.H - basic data types
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTTYP_H_
#define _LTTYP_H_

#ifdef FOR_LINUX
#include "windows.h"
#endif

#include "ltsys.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

#pragma warning (error:4020)
#pragma warning (error:4021)

#ifdef FOR_UNICODE
   typedef TCHAR L_TCHAR;
#else
   typedef char  L_TCHAR;
#endif

typedef WCHAR L_WCHAR;          /* 16-bit UNICODE character */
typedef char L_CHAR;            /* signed 8-bit integer */
typedef unsigned char L_UCHAR;  /* unsigned 8-bit integer */
typedef short L_INT16;          /* signed 16-bit integer */
typedef unsigned short L_UINT16;/* unsigned 16-bit integer */
typedef long L_INT32;           /* signed 32-bit integer */
typedef unsigned long L_UINT32; /* unsigned 32-bit integer */
#ifndef FOR_WIN
typedef LONGLONG L_INT64;       /* signed 64-bit integer */
typedef DWORDLONG L_UINT64;     /* unsigned 64-bit integer */
#endif
typedef int L_INT;              /* signed integer 16-bits or larger */
typedef unsigned L_UINT;        /* unsigned integer 16-bits or larger */
typedef void L_VOID;            /* void */
typedef L_UINT L_BOOL;          /* boolean */
typedef L_UINT L_BITFIELD;      /* bit field */
typedef float  L_FLOAT;         /* floating point number */
typedef double L_DOUBLE;        /* double precision floating point number */
typedef RGBQUAD L_RGBQUAD;      /* RGBQUAD structure */

#ifdef FOR_WIN
   #define L_FAR           _far    /* segmented memory attribute < 64K */
   #define L_HUGE          _huge   /* segmented memory attribute > 64K */
   #define L_EXPORT        _export /* export attribute */
   #define L_PASCAL        _pascal /* pascal calling convention */
#elif defined(FOR_WIN32) || defined(FOR_LINUX) || defined(FOR_WIN64)
   #define L_FAR                   /* segmented memory attribute < 64K */
   #define L_HUGE                  /* segmented memory attribute > 64K */
//   #define L_EXPORT                /* export attribute */
   #define L_EXPORT        __stdcall /* export attribute */
   #define L_PASCAL                /* pascal calling convention */
#endif

#ifdef FOR_JUSTLIB
   #define DLL_EXPORT __declspec(dllexport)
#else
   #define DLL_EXPORT 
#endif

#if defined(FOR_WIN) || defined(FOR_WIN32) || defined(FOR_WIN64)
   #define EXT_FUNCTION    WINAPI
   #define pEXT_FUNCTION   EXT_FUNCTION L_FAR *

   #ifndef FOR_LINUX
      #define EXT_CALLBACK    __stdcall L_FAR
   #else
      #define EXT_CALLBACK
   #endif

   #define pEXT_CALLBACK   EXT_CALLBACK L_FAR *
#endif                          /* defined(FOR_WIN) || defined(FOR_WIN32) */

#ifdef FOR_WIN64
#define L_MAXPATH       264 // 64-bit needs this to be multiple of 8
                            // in v14 L_MAXPATH should be set to 264
#else
#define L_MAXPATH       260 // make this bigger so data stays 8-byte aligned
#endif

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTTYP_H_ */
