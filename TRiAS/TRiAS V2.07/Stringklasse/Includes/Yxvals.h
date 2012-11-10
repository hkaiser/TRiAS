// yxvals.h - compiler specifics
#ifndef _YXVALS_
#define _YXVALS_

// translator/library features
#define _CATCH_IO_EXCEPTIONS	1	// try blocks in iostreams
// #define _HAS_ARRAY_NEW		// operator new[] implemented
// #define _HAS_PJP_CLIB		// running atop PJP C library
#define _HAS_SIGNED_CHAR	1	// char/signed char distinct
// #define _HAS_TYPEINFO		// typeid implemented

// bitmask macros -- enum overloading implemented
/* #define _BITMASK(E,T)						\
E& operator&= (E& _X, E _Y) { _X = (E)(_X & _Y); return (_X); }	\
E& operator|= (E& _X, E _Y) { _X = (E)(_X | _Y); return (_X); }	\
E& operator^= (E& _X, E _Y) { _X = (E)(_X ^ _Y); return (_X); }	\
E& operator& (E _X, E _Y) { return ((E)(_X & _Y)); }		\
E& operator| (E _X, E _Y) { return ((E)(_X | _Y)); }		\
E& operator^ (E _X, E _Y) { return ((E)(_X ^ _Y)); }		\
E& operator~ (E _X) { return ((E)~_X); }			\
typedef E T
*/
// exception macros -- exceptions not implemented
#define _TRY_BEGIN	try {
#define _CATCH_ALL	} catch (...) {
#define _CATCH_END	}
#define _RAISE(x)	throw (x)
#define _RERAISE	throw

// numeric representation macros
#define _BITS_BYTE	8
#define _MAX_EXP_DIG	8
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	36

// type definitions
#if _MSC_VER < 1100
typedef int _Bool;
#endif // _MSC_VER < 1100

struct _Filet;
struct _FPost;

// #define _PTRDIFFT		// ptrdiff_t already defined
typedef int _Ptrdifft;
// #define _SIZE_T		// size_t already defined
typedef unsigned int _Sizet;
typedef int _Typedecs;
// #define _WCHART		// wchar_t already defined
typedef unsigned short _Wchart;
// #define _WINTT		// wint_t already defined
typedef unsigned short _Wintt;

#endif // _YXVALS_

