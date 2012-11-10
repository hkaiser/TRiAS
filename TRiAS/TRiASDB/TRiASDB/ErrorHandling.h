// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 09/27/1998 11:36:34 AM
//
// @doc
// @module ErrorHandling.h | alle Vorbereitungen für die Fehlerbehandlung treffen

#if !defined(_ERRORHANDLING_H__56D922E4_5531_11D2_9ECE_006008447800__INCLUDED_)
#define _ERRORHANDLING_H__56D922E4_5531_11D2_9ECE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Im wesentlichen auf das existierende aufsetzen
#include <ospace/com/ComErrorMacros.h>
#include <Com/ErrorMacros2.h>

///////////////////////////////////////////////////////////////////////////////
// Und nun die Makros richtig mappen
#if defined(_USE_NEW_ERRORHANDLING)
#undef RETURN_FAILED_HRESULT
#define RETURN_FAILED_HRESULT(x)	ERROR_FAILED_HRESULT(x, 0)
#endif

#include "ReportError.h"

#endif // !defined(_ERRORHANDLING_H__56D922E4_5531_11D2_9ECE_006008447800__INCLUDED_)
