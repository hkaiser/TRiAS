// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.99 13:45:52
//
// @module PerfCounters.cpp | Starting and stopping Performance counters

#include "StdAfx.h"

#include "TRiASDBApp.h"

#if defined(_USE_PERFMON_COUNTERS)

#include <WinPerf.h>

#include "resource.h"
#include "Strings.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

using namespace PerfMon;

///////////////////////////////////////////////////////////////////////////////
// Flags, ob PerfCounters überhaupt gebraucht werden
extern DWORD g_dwFlags;	// REG_USE_PROXYSTUB: use ProxyStub, REG_USE_PERFCOUNTERS: use PerfCounters

///////////////////////////////////////////////////////////////////////////////
// Performance counter rund um diverse COM-Objekte
BEGIN_PERFCOUNTERDATA_MAP(ObjectCounter)
	PERCOUNTERDATA_ENTRY(g_cbCount, IDS_OBJECTCOUNT_DESC, IDS_OBJECTCOUNT_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)
	PERCOUNTERDATA_ENTRY(g_cbAllocs, IDS_OBJECTALLOCS_DESC, IDS_OBJECTALLOCS_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)
	PERCOUNTERDATA_ENTRY(g_cbFrees, IDS_OBJECTFREES_DESC, IDS_OBJECTFREES_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)

	PERCOUNTERDATA_ENTRY(L"Dummy", IDS_DUMMY, IDS_DUMMY, PERF_DETAIL_NOVICE, PERF_COUNTER_RAWCOUNT|PERF_DISPLAY_NOSHOW, 0L)
END_PERFCOUNTERDATA_MAP()

BEGIN_PERFOBJECT_MAP()
	PERFOBJECTDATA_ENTRY(g_cbCounts, ObjectCounter, IDS_OBJECTCOUNTS_DESC, IDS_OBJECTCOUNTS_TEXT)
END_PERFOBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// Vorbereitende Maßnamen
#define LOCALE_ENGLISH ((MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)))

BOOL CTriasDBApp::StartPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return TRUE;

	COM_TRY {
		if (!g_PerfCtx.IsValid()) {
#if defined(_USE_DYNAMIC_PERFMON_COUNTERS)
		GETPERFMONCTXPROC pProc = (GETPERFMONCTXPROC)m_PerfMon.GetProcAddress (_T("PerfMon::GetOrCreateContext"));

			if (NULL == pProc)
				return FALSE;
			THROW_FAILED_HRESULT((*pProc)(g_cbPerfCtx, g_PerfCtx.ppi()));
#else
			THROW_FAILED_HRESULT(PerfMon::GetOrCreateContext (g_cbPerfCtx, g_PerfCtx.ppi()));
#endif // defined(_USE_DYNAMIC_PERFMON_COUNTERS)
		}

		if (SUCCEEDED(g_PerfCtx -> Start (PerfMon::PERFMONSTARTMODE_Normal)))
		{
			THROW_FAILED_HRESULT(g_PerfCtx -> put_Locale (LOCALE_ENGLISH));
			THROW_FAILED_HRESULT(InstallPerfCounters(m_hInstance));
			m_fCountersInstalled = true;
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

BOOL CTriasDBApp::StopPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return TRUE;

	_ASSERTE(g_PerfCtx.IsValid());

	g_PerfCtx -> Stop();
	g_PerfCtx.Assign(NULL);	
	return TRUE;
}

HRESULT CTriasDBApp::RegisterPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return S_OK;

	_ASSERTE(g_PerfCtx.IsValid());
	RETURN_FAILED_HRESULT(g_PerfCtx -> Start (PerfMon::PERFMONSTARTMODE_Register));
	RETURN_FAILED_HRESULT(g_PerfCtx -> put_Locale (LOCALE_ENGLISH));
	if (!m_fCountersInstalled) {
		RETURN_FAILED_HRESULT(InstallPerfCounters(m_hInstance));
		m_fCountersInstalled = true;
	}
	RETURN_FAILED_HRESULT(g_PerfCtx -> Register());
	return S_OK;
}

HRESULT CTriasDBApp::UnRegisterPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return S_OK;

	_ASSERTE(g_PerfCtx.IsValid());
	RETURN_FAILED_HRESULT(g_PerfCtx -> Start (PerfMon::PERFMONSTARTMODE_UnRegister));
	RETURN_FAILED_HRESULT(g_PerfCtx -> put_Locale (LOCALE_ENGLISH));
	RETURN_FAILED_HRESULT(g_PerfCtx -> UnRegister());
	return S_OK;
}

#else // defined(_USE_PERFMON_COUNTERS)

BOOL CTriasDBApp::StartPerfCounters()
{
	return TRUE;
}

BOOL CTriasDBApp::StopPerfCounters()
{
	return TRUE;
}

HRESULT CTriasDBApp::RegisterPerfCounters()
{
	return S_OK;
}

HRESULT CTriasDBApp::UnRegisterPerfCounters()
{
	return S_OK;
}

#endif // defined(_USE_PERFMON_COUNTERS)
