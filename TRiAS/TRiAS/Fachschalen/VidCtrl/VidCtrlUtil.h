// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.06.2002 16:35:25
//
// @doc 
// @module VidCtrlUtil.h | Nützliche Makros etc...

#if !defined(_VIDCTRLUTIL_H__29005DC0_6B0C_4CE7_A6E5_0AFC45288B4B__INCLUDED_)
#define _VIDCTRLUTIL_H__29005DC0_6B0C_4CE7_A6E5_0AFC45288B4B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)			#x
#define STR2(x)			STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) ") : " #desc)
#define TODO(desc)		message(__FILE__ "(" STR2(__LINE__) ") : TODO: " #desc)

///////////////////////////////////////////////////////////////////////////////
// sonstige nützliche Makros
#define _countof(array) (sizeof(array)/sizeof(array[0]))

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

#if _MSC_VER < 1100			// der neue midl generiert sowas
#define DECLSPEC_UUID(x)
#define DECLSPEC_SELECTANY
#else
#define DECLSPEC_SELECTANY __declspec(selectany)
#endif // _MSC_VER < 1100

#endif // !defined(_VIDCTRLUTIL_H__29005DC0_6B0C_4CE7_A6E5_0AFC45288B4B__INCLUDED_)
