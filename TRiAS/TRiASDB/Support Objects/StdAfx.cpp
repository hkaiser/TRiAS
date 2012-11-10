// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information

#include <bool.h>
#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#if _ATL_VER >= 0x0200
#include <atlimpl.cpp>
#else
#include <atlimpl11.h>
#endif // _ATL_VER
