// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:25:38
//
// @doc 
// @module LineToolsUtil.h | Nützliche Makros etc...

#if !defined(_LINETOOLSUTIL_H__272A592E_6409_4686_8EEB_80F6BF2AF907__INCLUDED_)
#define _LINETOOLSUTIL_H__272A592E_6409_4686_8EEB_80F6BF2AF907__INCLUDED_

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

#endif // !defined(_LINETOOLSUTIL_H__272A592E_6409_4686_8EEB_80F6BF2AF907__INCLUDED_)
