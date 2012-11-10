// @doc
// @module DebugSupport.cpp | eben DebugSupport

#include "StdAfx.h"
#include "GeodCtf_COM.h"

#if defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)

//#define _USE_BSCKIT
#include <AtlDebug.h>

CIIDsToAnalyse g_IIDsToAnalyse;

BEGIN_DEBUGSUPPORT_MAP()
	DEBUGSUPPORT_ENTRY(IID_ICoordTransform)
	DEBUGSUPPORT_ENTRY(IID_ICoordTransformInit)
END_DEBUGSUPPORT_MAP()

#include <AtlDebug.cpp>

#endif // _ATLX_DEBUG_REFCOUNT_WALKSTACK
