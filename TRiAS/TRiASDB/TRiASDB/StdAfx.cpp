// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#if _ATL_VER < 0x0700
#include <atlimpl.cpp>
#include <atlctl.cpp>
#include <atlwin.cpp>
#endif // _ATL_VER < 0x0700

#include <Com/ErrorMacros2Impl.cpp>

#if defined(_USE_PERFMON_COUNTERS)
#include <Com/PerfMonInstanceMapImpl.cpp>
#endif // defined(_USE_PERFMON_COUNTERS)

#include <Atl/RunTimeObjectMapMgrImpl.cpp>
