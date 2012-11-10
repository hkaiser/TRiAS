//-< STDTP.H >-------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Standart type and macro definitions
//-------------------------------------------------------------------*--------*

#ifndef __STDTP_H__
#define __STDTP_H__

#ifdef _WIN32
#include <windows.h>
#pragma warning(disable:4800 4355 4146)
#else
#ifndef NO_PTHREADS
#ifndef _REENTRANT
#define _REENTRANT 
#endif
#endif
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

// Align value 'x' to boundary 'b' which should be power of 2
#define DOALIGN(x,b)   (((x) + (b) - 1) & ~((b) - 1))

typedef signed char    int1;
typedef unsigned char  nat1;

typedef signed short   int2;
typedef unsigned short nat2;

typedef signed int     int4;
typedef unsigned int   nat4;

typedef unsigned char  byte;

#if defined(_WIN32)
typedef unsigned __int64 nat8;
typedef __int64          int8;
#define INT8_FORMAT "%I64d"
#define CONST64(c)  c
#else
#if defined(__osf__ )
typedef unsigned long nat8;
typedef signed   long int8;
#define INT8_FORMAT "%ld"
#define CONST64(c)  c##L
#else
#if defined(__GNUC__) || defined(__SUNPRO_CC)
typedef unsigned long long nat8;
typedef signed   long long int8;
#define INT8_FORMAT "%lld"
#define CONST64(c)  c##LL
#else
#error "integer 8 byte type is not defined" 
#endif
#endif
#endif

#if !defined(bool) && (defined(__SUNPRO_CC) || defined(__IBMCPP__))
#define bool  char
#define true  (1)
#define false (0)
#endif

#define nat8_low_part(x)  ((nat4)(x))
#define nat8_high_part(x) ((nat4)((nat8)(x)>>32))
#define int8_low_part(x)  ((int4)(x))
#define int8_high_part(x) ((int4)((int8)(x)>>32))
#define cons_nat8(hi, lo) ((((nat8)(hi)) << 32) | (nat4)(lo))
#define cons_int8(hi, lo) ((((int8)(hi)) << 32) | (nat4)(lo))
 
#define MAX_NAT8  nat8(-1)

typedef float  real4;
typedef double real8; 

#ifndef BIG_ENDIAN
#define BIG_ENDIAN      4321    /* most-significant byte first (IBM, net) */
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN   1234
#endif

#ifndef BYTE_ORDER
#if defined(__sparc__) || defined(__m68k__)
#define BYTE_ORDER      BIG_ENDIAN 
#else
#define BYTE_ORDER      LITTLE_ENDIAN
#endif
#endif

#ifdef _WIN32
typedef HANDLE descriptor_t; 
#else
typedef int descriptor_t; 
#endif

#ifndef _WIN32
#define _fastcall
#endif

#if defined(_WIN32) || !defined(NO_PTHREADS)
#define THREADS_SUPPORTED 1
#else
#define THREADS_SUPPORTED 0
#endif

#define items(array) (sizeof(array)/sizeof*(array))

#endif




