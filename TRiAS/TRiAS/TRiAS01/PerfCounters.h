// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.09.99 11:13:20 
//
// @doc
// @module PerfCounters.h | Declaration of the PerfCounter helper functions

#if !defined(_PERFCOUNTERS_H__7DA67BB1_BE25_464E_9973_0F86FD563EC5__INCLUDED_)
#define _PERFCOUNTERS_H__7DA67BB1_BE25_464E_9973_0F86FD563EC5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// (keep in sync with TRiASDBApp.h)
const DWORD REG_USE_PROXYSTUB = 0x01;		// use ProxyStub
const DWORD REG_USE_PERFCOUNTERS = 0x02;	// use PerfCounters
const DWORD REG_USE_NOVELLTESTCODE = 0x04;	// use NovellTestCode
const DWORD REG_USE_THREADSAFE_DBACCESS = 0x08;		// use thread safe db access

///////////////////////////////////////////////////////////////////////////////
// Name der PerfMon.dll
#if defined(_USE_PERFMON_COUNTERS)
#if defined(_USE_DYNAMIC_PERFMON_COUNTERS)
// counter dll dynamisch binden
#if defined(_DEBUG)
const TCHAR g_cbPerfMonDll[] = _T("PERFMOND.DLL");
#else
const TCHAR g_cbPerfMonDll[] = _T("PERFMON.DLL");
#endif // _DEBUG

#else
// counter dll statisch binden
#if defined(_DEBUG)
#pragma comment(lib, "perfmond.lib")
#else
#pragma comment(lib, "perfmon.lib")
#endif // _DEBUG

#endif // defined(_USE_DYNAMIC_PERFMON_COUNTERS)
#endif // defined(_USE_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Prototypen für PerfCounterFunktionen
BOOL StartPerfCounters(HINSTANCE hInst);
BOOL StopPerfCounters();
HRESULT RegisterPerfCounters();
HRESULT UnRegisterPerfCounters();

#if defined(_USE_PERFMON_COUNTERS) && defined(_USE_DYNAMIC_PERFMON_COUNTERS)
///////////////////////////////////////////////////////////////////////////////
// dynamisches binden einer DLL
typedef HRESULT (* GETPERFMONCTXPROC)(LPCOLESTR pcoleContext, PerfMon::IPerfContext **ppICtx);

class CDllBind {
private:
	HMODULE m_hLib;		// Handle der gebundenen DLL

public:
// Konstruktor
	CDllBind (const char *pcDLLName)
	{
	// WindowsFehlerMeldung unterdrücken
	unsigned int oldErrMode = SetErrorMode (SEM_NOOPENFILEERRORBOX);

	// #HK990620 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	int cbShortName = GetShortPathName (pcDLLName, szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (_MAX_PATH != cbShortName) {
			pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? pcDLLName : szModuleShort;
			m_hLib = LoadLibrary (pcModule);
		}

	// vorherigen Zustand wieder einstellen
		SetErrorMode (oldErrMode);
	}

// Memberfunktion
	HMODULE hLib (void) const { return m_hLib; }
	FARPROC GetProcAddress (const char *pcFcnName)
	{
		if (NULL != m_hLib)
			return ::GetProcAddress (m_hLib, pcFcnName);
		return NULL;
	}
	
// Destruktor
	~CDllBind (void)
	{
		if (NULL != m_hLib) {
			FreeLibrary(m_hLib); 
			m_hLib = NULL;
		}
	}
};

#endif // defined(_USE_PERFMON_COUNTERS) && defined(_USE_DYNAMIC_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Flags, ob PerfCounters überhaupt gebraucht werden
extern DWORD g_dwFlags;	// REG_USE_PROXYSTUB: use ProxyStub, REG_USE_PERFCOUNTERS: use PerfCounters

#endif // !defined(_PERFCOUNTERS_H__7DA67BB1_BE25_464E_9973_0F86FD563EC5__INCLUDED_)
