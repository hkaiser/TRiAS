// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/30/1998 01:54:30 PM
//
// @doc
// @module Basetsd.h | Vorbereitung auf 64Bit
// $Log: $

#if !defined(_BASETSD_H)
#define _BASETSD_H

#if defined(__midl)
// MIDL datatype definitions
cpp_quote("#if !defined(_BASETSD_H)")
cpp_quote("#define _BASETSD_H")
typedef long LONG32;
typedef long INT32;
typedef __int64 LONG64;
typedef __int64 INT64;
typedef unsigned long ULONG32;
typedef unsigned long UINT32;
typedef unsigned __int64 ULONG64; 
typedef unsigned __int64 UINT64;
typedef long INT_PTR;
typedef unsigned long UINT_PTR;
typedef unsigned long SIZE_T;
typedef long SSIZE_T;
cpp_quote("#endif // !defined(_BASETSD_H)")
#else

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(WIN32)
// 'normal' compiler datatype definitions
typedef long LONG32;
typedef __int32 INT32;
typedef __int64 LONG64;
typedef __int64 INT64;
typedef unsigned long ULONG32;
typedef unsigned __int32 UINT32;
typedef unsigned __int64 ULONG64; 
typedef unsigned __int64 UINT64;
typedef long INT_PTR;
typedef unsigned long UINT_PTR;
typedef unsigned __int32 SIZE_T;
typedef __int32 SSIZE_T;
#else
#error ("Define integer base datatypes for the required platform!")
#endif // //WIN32

#endif // __midl 

#endif // !defined(_BASETSD_H)
