// @doc
// @module DebugSupport.cpp | eben DebugSupport

#include "StdAfx.h"

#if defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)

//#define _USE_BSCKIT
#include <Atl/AtlDebug.h>

CIIDsToAnalyse g_IIDsToAnalyse;

BEGIN_DEBUGSUPPORT_MAP()
	DEBUGSUPPORT_ENTRY(IID_ITRiASProperty)
	DEBUGSUPPORT_ENTRY(IID_ITRiASProperties)
	DEBUGSUPPORT_ENTRY(IID_ITRiASPropertyBase)
	DEBUGSUPPORT_ENTRY(IID_ITRiASPropertyCallback)
END_DEBUGSUPPORT_MAP()

#include <Atl/AtlDebug.cpp>

#endif // _ATLX_DEBUG_REFCOUNT_WALKSTACK
