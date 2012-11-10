// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.09.99 11:03:45
//
// @doc
// @module PerfCounters.cpp | Starting and stopping Performance counters

#include "trias01p.hxx"

#if defined(_USE_PERFMON_COUNTERS)

#include <Com/PerfMonContext.h>
#include <Com/PerfMonInstanceMap.h>

#include <WinPerf.h>

#include "obj32/trias321.h"
#include "Strings.h"
#include "PerfCounters.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

using namespace PerfMon;

///////////////////////////////////////////////////////////////////////////////
// Flags, ob PerfCounters überhaupt gebraucht werden
extern "C" HINSTANCE g_hInstance;

///////////////////////////////////////////////////////////////////////////////
// Performance counter rund um diverse COM-Objekte
BEGIN_PERFCOUNTERDATA_MAP(ErrorCounter)
	PERCOUNTERDATA_ENTRY(L"Installs", IDS_INSTALLCOUNT_DESC, IDS_INSTALLCOUNT_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)
	PERCOUNTERDATA_ENTRY(L"Removes", IDS_REMOVEALLOCS_DESC, IDS_REMOVEALLOCS_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)
	PERCOUNTERDATA_ENTRY(L"ActCount", IDS_ACTCOUNT_DESC, IDS_ACTCOUNT_TEXT, PERF_DETAIL_EXPERT, PERF_COUNTER_RAWCOUNT, 0L)
END_PERFCOUNTERDATA_MAP()

BEGIN_PERFOBJECT_MAP()
	PERFOBJECTDATA_ENTRY(L"ErrorCounters", ErrorCounter, IDS_ERRORCOUNTS_DESC, IDS_ERRORCOUNTS_TEXT)
END_PERFOBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// Vorbereitende Maßnamen
#define LOCALE_ENGLISH ((MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)))

static bool s_fCountersInstalled = false;

BOOL StartPerfCounters(HINSTANCE hInst)
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return TRUE;

	COM_TRY {
		if (!g_PerfCtx.IsValid()) {
#if defined(_USE_DYNAMIC_PERFMON_COUNTERS)
		static CDllBind g_PerfMon;
		GETPERFMONCTXPROC pProc = (GETPERFMONCTXPROC)g_PerfMon.GetProcAddress (_T("PerfMon::GetOrCreateContext"));

			if (NULL == pProc)
				return FALSE;
			THROW_FAILED_HRESULT((*pProc)(L"TRiAS01", g_PerfCtx.ppi()));
#else
			THROW_FAILED_HRESULT(PerfMon::GetOrCreateContext (L"TRiAS01", g_PerfCtx.ppi()));
#endif // defined(_USE_DYNAMIC_PERFMON_COUNTERS)
		}

		if (!s_fCountersInstalled && SUCCEEDED(g_PerfCtx -> Start (PerfMon::PERFMONSTARTMODE_Normal)))
		{
			THROW_FAILED_HRESULT(g_PerfCtx -> put_Locale (LOCALE_ENGLISH));
			THROW_FAILED_HRESULT(InstallPerfCounters(hInst));
			s_fCountersInstalled = true;
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

BOOL StopPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return TRUE;

	_ASSERTE(g_PerfCtx.IsValid());

	g_PerfCtx -> Stop();
	g_PerfCtx.Assign(NULL);	
	return TRUE;
}

HRESULT RegisterPerfCounters()
{
	if (!IsWinNT() || !(g_dwFlags & REG_USE_PERFCOUNTERS))
		return S_OK;

	_ASSERTE(g_PerfCtx.IsValid());
	if (!s_fCountersInstalled) {
		RETURN_FAILED_HRESULT(g_PerfCtx -> Start (PerfMon::PERFMONSTARTMODE_Register));
		RETURN_FAILED_HRESULT(g_PerfCtx -> put_Locale (LOCALE_ENGLISH));
		RETURN_FAILED_HRESULT(InstallPerfCounters(g_hInstance));
		s_fCountersInstalled = true;
	}
	RETURN_FAILED_HRESULT(g_PerfCtx -> Register());
	return S_OK;
}

HRESULT UnRegisterPerfCounters()
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

BOOL StartPerfCounters(HINSTANCE hInst)
{
	return TRUE;
}

BOOL StopPerfCounters()
{
	return TRUE;
}

HRESULT RegisterPerfCounters()
{
	return S_OK;
}

HRESULT UnRegisterPerfCounters()
{
	return S_OK;
}

#endif // defined(_USE_PERFMON_COUNTERS)
