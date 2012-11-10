// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2000 20:31:51 
//
// @doc
// @module Pragmas.h | Declaration of the some common used pragma macros

#if !defined(__MESSAGE_PRAGMAS_H__119B30E0_1DC0_11d3_9973_0060085FC1CE)
#define __MESSAGE_PRAGMAS_H__119B30E0_1DC0_11d3_9973_0060085FC1CE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#if !defined(STR)
#define STR(x)			#x
#endif
#if !defined(STR2)
#define STR2(x)			STR(x)
#endif
#if !defined(MESSAGE)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) ") : " #desc)
#endif
#if !defined(TODO)
#define TODO(desc)		message(__FILE__ "(" STR2(__LINE__) ") : TODO: " #desc)
#else
#pragma MESSAGE("pragmas like MESSAGE, TODO etc. are now in <pragmas.h>")
#endif

///////////////////////////////////////////////////////////////////////////////
// Header-Diagnostics; z.B:
//	...
//	#include <Pragmas.h>
//	#pragma	HDR_ON()
//		....
//	#pragma HDR_OFF()
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#define	HDR_ON()	message(__FILE__ "(" STR2(__LINE__) ") : {{ " __TIME__ )
#define	HDR_OFF()	message(__FILE__ "(" STR2(__LINE__) ") : }} " __TIME__ )
#else
#define	HDR_ON()	
#define	HDR_OFF()
#endif

///////////////////////////////////////////////////////////////////////////////
// Define-Diagnostics; z.B:
//	#if defined(AnyThing)
//	#pragma SHOW_DEFINE(AnyThing)
//	#endif // AnyThing
#if defined(_TRIAS_DBG_DEFINES)
#define	SHOW_DEFINE(d)	message(__FILE__ "(" STR2(__LINE__) ") : <<" #d ">> is defined" )
#else
#define	SHOW_DEFINE(d)
#endif

#endif __MESSAGE_PRAGMAS_H__119B30E0_1DC0_11d3_9973_0060085FC1CE
