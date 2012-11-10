// gist_compat.h						-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_compat.h,v 1.10 2000/03/10 01:39:02 mashah Exp $

#ifndef GIST_COMPAT_H
#define GIST_COMPAT_H

///////////////////////////////////////////////////////////////////////////////
// port-specific specializations
///////////////////////////////////////////////////////////////////////////////

#ifdef UNIX

#define HAVE_STRDUP
#define HAVE_VALUES_H
#define HAVE_UNISTD_H
#define	HAVE_RAND48
#define	HAVE_RAND48_PROTOS
#define	HAVE_COPYSIGN_PROTOS
#undef  HAVE_MALLOC_H
#undef  HAVE_O_BINARY

// there are some interface changes between STLv2 and STLv3.
#if (__GNUG__==2 && __GNUC_MINOR__>=8)
#define	HAVE_STL_V3
#endif // gcc 2.8.x

#ifdef ultrix
#undef	HAVE_STRDUP
#undef	HAVE_RAND48_PROTOS
#undef	HAVE_COPYSIGN_PROTOS
#endif // ultrix

#endif // UNIX

#ifdef WIN32

#define HAVE_STRDUP
#undef  HAVE_VALUES_H
#undef  HAVE_UNISTD_H
#define HAVE_MALLOC_H
#define HAVE_O_BINARY
#define	HAVE_STL_V3


#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// feature handling
///////////////////////////////////////////////////////////////////////////////

// XXX it's aesthetically displeasing to have this stuff here.  think
// of it as an incentive to get gnu configure working.

#ifndef HAVE_STRDUP
#define strdup(s) strcpy(new char[strlen(s)+1], s)
#endif // HAVE_STRDUP

#ifdef HAVE_VALUES_H
#include <values.h>
#else // HAVE_VALUES_H
// a quick hack, taken from <values.h> on a Solaris system - assumes
// 64-bit IEEE-754 doubles, 2s-complement integer arithmetic and 8-bit
// bytes.
#define MAXDOUBLE 1.79769313486231570e+308
#define MINDOUBLE 4.94065645841246544e-324
#define HIBITI (1U << (8 * (int) sizeof(int)) - 1)
#define MAXINT ((int) ~(HIBITI))
#endif // HAVE_VALUES_H

// Linux has MININT in values.h
#ifndef MININT
#define MININT ((int) (HIBITI))
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else // HAVE_UNISTD_H
#include <io.h>
#endif // HAVE_UNISTD_H

#ifdef HAVE_RAND48
#ifndef HAVE_RAND48_PROTOS
extern "C"
{
    extern double drand48(void);
    extern double erand48(unsigned short *);
    extern long jrand48(unsigned short *);
    extern void lcong48(unsigned short *);
    extern long lrand48(void);
    extern long mrand48(void);
    extern long nrand48(unsigned short *);
    extern unsigned short *seed48(unsigned short *);
    extern void srand48(long);
};
#endif // HAVE_RAND48_PROTOS
#else // HAVE_RAND48

// VCPORT_B
#ifdef WIN32

#define drand48() (((double) rand())/((double) MAXINT))
#define srand48(S) srand(S)

#else

#define	drand48() (((double) random())/((double) MAXINT))
#define srand48(S) srandom(S)

#endif
// VCPORT_E

#endif // HAVE_RAND48

#ifndef HAVE_COPYSIGN_PROTOS
extern "C"
{
    extern double copysign(double x, double y);
    extern double drem(double x, double y);
    extern int finite(double x);
    extern double logb(double x);
    extern double scalb(double x, int n);
};
#endif // HAVE_COPYSIGN_PROTOS

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif // HAVE_MALLOC_H

#ifndef HAVE_O_BINARY
#define O_BINARY 0
#endif // HAVE_O_BINARY

#endif // GIST_COMPAT_H
