// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 14:02:02 
//
// @doc
// @module LPictImpl.h | Declaration of the <c CLPictImpl> class

#if !defined(_LPICTIMPL_H__2F87901B_1289_4C1E_BAEA_E06A179D809B__INCLUDED_)
#define _LPICTIMPL_H__2F87901B_1289_4C1E_BAEA_E06A179D809B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(TRILAY)
	#include "../TRILay/resource.h"
	#include "lpict/pictdef.h"		// allgemeine Definitionen
#else
	#include "resource.h"
	#include "lpict/pictver_.h"		// Versionskontrolle
	#include "lpict/pictdef.h"		// allgemeine Definitionen

	#ifndef _AFXEXT
		#if _MFC_VER < 0x0400 
			extern "C" void WINAPI InitLPictDLL();
		#else
			#pragma comment( lib, IMPORT_PICT_DLL )
		#endif
	#endif

	#ifdef _AFXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#endif
#endif

#include "LibTopoMap/LibTopoMapStructs.h"
#include "lpict/picture.h"
#include "lpict/PolyGISPicture.h"
#include "lpict/LeadToolsPicture.h"
#include "lpict/PictFlt.h"
#include "lpict/PictCod.h"
#include "PictPriv.h"

#endif // !defined(_LPICTIMPL_H__2F87901B_1289_4C1E_BAEA_E06A179D809B__INCLUDED_)
