// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.10.2000 20:51:18 
//
// @doc
// @module DtoACTF.h | Declaration of the DtoACTF function

#if !defined(_DTOACTF_H__49EF9889_A6E6_44F0_8F39_6CD9390E4AF7__INCLUDED_)
#define _DTOACTF_H__49EF9889_A6E6_44F0_8F39_6CD9390E4AF7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
char *DtoACTF (char *lpszString, const char *lpszFormat, int iPrec, double dblFloat);

#endif // !defined(_DTOACTF_H__49EF9889_A6E6_44F0_8F39_6CD9390E4AF7__INCLUDED_)
