// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 01:52:23 PM
//
// @doc
// @module Wrapper.h | InterfaceWrapper für PerMon

#if !defined(_WRAPPER_H__4674526A_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _WRAPPER_H__4674526A_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

using namespace PerfMon;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(PersistMemory);

DefineSmartInterface(PerfContext);
DefineSmartInterface(PerfContextHelper);
DefineSmartInterface(PerfObject);
DefineSmartInterface(PerfObjects);
DefineSmartInterface(PerfCounter);
DefineSmartInterface(PerfCounters);
DefineSmartInterface(PerfCounterDefinition);
DefineSmartInterface(PerfCounterDefinitions);
DefineSmartInterface(PerfInstanceDefinition);
DefineSmartInterface(PerfInstanceDefinitions);

///////////////////////////////////////////////////////////////////////////////
// besorgt einen PerfContext über seinen Namen
inline HRESULT GetPerfContext (BSTR bstrName, REFIID riid, void **ppICtx)
{
	return NamedObjectGetReference (bstrName, riid, (LPVOID *)ppICtx);
}

#endif // !defined(_WRAPPER_H__4674526A_9CBA_11D2_9F09_006008447800__INCLUDED_)
