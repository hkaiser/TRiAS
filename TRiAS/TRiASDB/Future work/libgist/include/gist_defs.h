// gist_defs.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_defs.h,v 1.16 2000/03/10 01:39:03 mashah Exp $


#ifndef GIST_DEFS_H
#define GIST_DEFS_H

#include <sys/types.h>	// for size_t
#include <assert.h>		// for assert()
#include <vector> // for Vector

// VCPORT_B
#ifdef WIN32
#include <io.h>

#define isatty(X) _isatty(X)
#endif
// VCPORT_E

#define GISTBUFS 17

enum latch_mode_t { LATCH_NL = 0, LATCH_SH = 1, LATCH_EX = 2 };

typedef short   int2;
typedef long    int4;
typedef unsigned char	uint1;
typedef unsigned short	uint2;
typedef unsigned long	uint4;
typedef uint4 smsize_t;

#ifdef NO_BOOL
typedef char            bool;
const char false = '\0';
const char true = '\1';
#endif

typedef unsigned int shpid_t;
typedef int rc_t;
#define RCOK 0
#define SM_PAGESIZE 8192
#define ROOTPAGE 1

// error constants
#define eERROR 0x80015 // generic error
#define eEOF 0x80014
#define eOUTOFSPACE 0x80005
#define eBADSLOTNUMBER 0x8001d
#define eRECWONTFIT 0x80023
#define eNOTOPEN 0x80024
#define eFILEERROR 0x80025
#define eNOBUFFERS 0x80026
#define eOUTOFBOUNDS 0x80027
#define eCLUSTERERROR 0x80028
#define ePARSEERROR 0x80029
#define eCANTPARSEPRED 0x8002e
#define ePAGEBREAK 0x80030
#ifdef AMDB
#define eNOPROFILE 0x8002a
#define eNOOPTCLUSTERING 0x8002b
#define eNOOPTTREE 0x8002c
#define eHASSPLITSTATS 0x8002d
#define eHASPENALTYSTATS 0x8002d
#define eHASWKLDSTATS 0x8002d
#define eARRAYSIZE 0x8002f
#endif

#define ALIGNON 0x8
#define ALIGNON1 (ALIGNON-1)
#define align(sz) ((uint4)((sz + ALIGNON1) & ~ALIGNON1))

#pragma warning (disable: 4800)
#define W_DO(x) 	\
{			\
    rc_t _e = (x);	\
    if ((_e)) return (_e);	\
}

// VCPORT_B
#ifdef WIN32
//using namespace std;
#endif
// VCPORT_E

// Vector used in gist_predcursor_t and various amdb classes
typedef std::vector<void *> Vector;

#endif // GIST_DEFS_H
