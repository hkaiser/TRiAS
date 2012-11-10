// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 05.07.2001 17:22:33 
//
// @doc
// @module DateTime.h | Declaration of the <c CDateTime> class

#if !defined(_DATETIME_H__8C5471C5_7316_491A_A5E8_CFDA3FD38ABB__INCLUDED_)
#define _DATETIME_H__8C5471C5_7316_491A_A5E8_CFDA3FD38ABB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <trias01m.hxx>

///////////////////////////////////////////////////////////////////////////////
// Liefert aktuelle Systemzeit als DBTYPE_DATE
_TRIAS01_ENTRY double FUNCTYPE GetCurrentTimeAsDATE();

#endif // !defined(_DATETIME_H__8C5471C5_7316_491A_A5E8_CFDA3FD38ABB__INCLUDED_)
