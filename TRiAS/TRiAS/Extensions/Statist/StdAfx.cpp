// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if _ATL_VER < 0x0700
#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>
#endif // _ATL_VER < 0x0700

#include <triastlb.h>

#include <Com/ErrorMacros2Impl.cpp>
#include <Com/ObjectPropertyBase.cpp>
#include <Com/PropertyActionBase.cpp>
#include <Atl/RunTimeObjectMapMgrImpl.cpp>

