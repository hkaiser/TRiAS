// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/31/1998 02:54:39 PM
//
// @doc
// @module PerfMonContext.h | Defintionen für PerfMon-Adapterobjekte

#if !defined(_PERFMONCONTEXT_H__30414255_A036_11D2_9F09_006008447800__INCLUDED_)
#define _PERFMONCONTEXT_H__30414255_A036_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if !defined(__PERFMONDLL__)
#define _PERFMON_EXPORT	__declspec(dllimport)
#else
#define _PERFMON_EXPORT __declspec(dllexport)
#endif	// __PERFMONDLL__

#include <comdef.h>
#import "tlb/PerfMon.tlb" raw_interfaces_only raw_dispinterfaces named_guids \
	exclude("INT_PTR") 

///////////////////////////////////////////////////////////////////////////////
// PerfContext immer nur mit einer der folgenden API-Funktionen erzeugen
inline 
HRESULT PerfMonGetOrCreateContext (LPCOLESTR pcoleContext, PerfMon::IPerfContext **ppICtx) throw(_com_error)
{
_bstr_t bstrMk("clsid:8FE61067-9A8D-11D2-9F08-006008447800:!");

	bstrMk += pcoleContext;
	return CoGetObject (bstrMk, NULL, __uuidof(PerfMon::IPerfContext), (LPVOID *)ppICtx);
}

// die folgende Variante ist aus der PerfMon.dll exportiert
namespace PerfMon {
	_PERFMON_EXPORT HRESULT GetOrCreateContext (LPCOLESTR pcoleContext, PerfMon::IPerfContext **ppICtx);
}

#endif // !defined(_PERFMONCONTEXT_H__30414255_A036_11D2_9F09_006008447800__INCLUDED_)
