/***************************************************************************
//	Header file for Computer Associates FreeStore release 2.0
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
 ***************************************************************************/

#ifndef _CXXTYPES_HXX
#define _CXXTYPES_HXX

#if _MSC_VER >= 700
	#define MSWIND 1
	#define MSCC7 1
	#define MSC_C7 1
#elif _MSC_VER >= 800
	#define MSWIND 1
	#define MSCC8
#elif defined(__BCPLUSPLUS__)
	#define MSWIND 1
#elif defined(__ZTC__)
	#define MSWIND 1
#elif defined(__WATCOMC__)
	#define MSWIND 1
#elif defined(__TURBOC__)
	#if !defined(MSWIND) && defined(_Windows)
		#define MSWIND
	#endif
#else
	#if !defined( MSWIND ) && !defined( PM ) && defined( __GWXX__ )
		#ifndef __PROT__
			#define MSWIND
		#else
			#define PM
		#endif
	#endif
#endif

#if	defined(__ZTC__)
	#define size_t unsigned
#else
	#ifndef _SIZE_T_DEFINED
		typedef unsigned int size_t;
		#define _SIZE_T_DEFINED
	#endif
#endif

#if !defined(_TF_ENTRY32)

#if defined(WIN32)
#undef _DLLENTRY
#define _DLLENTRY

#if defined(__TFDLL__)
#define _TF_ENTRY32 __declspec(dllexport)
#else

#if !defined(__TFLIB__)
#define _TF_ENTRY32 __declspec(dllimport)
#else
#define _TF_ENTRY32
#endif // __TFLIB__

#endif // __TFDLL__

#else
#define _TF_ENTRY32
#define _DLLENTRY __export
#endif // WIN32

#endif // _TF_ENTRY32

#define True	1
#define TRUE	1
#define False	0
#define FALSE	0	
#undef	NULL
#define NULL	0

typedef int		Bool;
typedef char *		pchar;
typedef unsigned long	ulong;
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef	void *		FSHandle;

#include <bool.h>

#endif // _CXXTYPES_HXX
	
