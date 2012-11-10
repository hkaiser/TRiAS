// stdafx.cpp : source file that includes just the standard includes
//  stdafx.pch will be the pre-compiled header
//  stdafx.obj will contain the pre-compiled type information


//#include <bool.h>

#include "stdafx.h"

#ifdef _ATL_TRIAS_REGISTER
#include <TRiASHelper_i.c>
#include <TRiASHelper.h>
#endif

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>
