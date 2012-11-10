//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992

#ifndef _CVDEBUG_HXX
#define _CVDEBUG_HXX

enum DebugTypes { CVD_DebugOff, CVD_DebugOn, CVD_Debug, CVD_Always };

#if !defined(WIN32)
extern "C" void _cdecl CVDebug (DebugTypes, char *, ...);
#else
extern "C" _TF_ENTRY32 void CVDebug (DebugTypes, char *, ...);
#endif

#endif
