// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 07.02.2002 23:25:41 
//
// @doc
// @module TRiASCSTransformService.cpp | Definition of the <c CTRiASCSTransformService> class

#include "stdafx.h"
#include "TRiASCs.h"
#include "TRiASCsImpl.h"

#include <Atl/Ciid.h>

#include "EnumCoordSystemNames.h"
#include "TRiASCSTransformService.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSTransformService

// Constructor
CTRiASCSTransformService::CTRiASCSTransformService()
{
}

// Destructor
CTRiASCSTransformService::~CTRiASCSTransformService()
{
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

// InterfaceSupportsErrorInfo implementation
STDMETHODIMP CTRiASCSTransformService::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASCSTransformService ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransformService

// Implementation of Transform
STDMETHODIMP CTRiASCSTransformService::Transform(IDispatch *Geometry, 
	BSTR CoordSysGuid, ITRiASCSTransform *CTF)
{
	CHECKINPOINTER(Geometry);
	CHECKINPOINTER(CTF);

	COM_TRY {
	CIID Guid (CoordSysGuid);

		THROW_FAILED_HRESULT(WTRiASTransformGeometry(Geometry)->Transform(*(CSID *)&Guid, CTF));
	} COM_CATCH;
	return S_OK;
}

// Implementation of TransformInverse
STDMETHODIMP CTRiASCSTransformService::TransformInverse(IDispatch *Geometry, 
	BSTR CoordSysGuid, ITRiASCSTransform *CTF)
{
	CHECKINPOINTER(Geometry);
	CHECKINPOINTER(CTF);

	COM_TRY {
	CIID Guid (CoordSysGuid);

		THROW_FAILED_HRESULT(WTRiASTransformGeometry(Geometry)->TransformInverse(*(CSID *)&Guid, CTF));
	} COM_CATCH;
	return S_OK;
}


// Implementation of TransformPts
STDMETHODIMP CTRiASCSTransformService::TransformPts(BSTR CoordSysGuid, 
	ITRiASCSTransform *CTF, VARIANT InPoints, VARIANT *pOutPoints)
{
	CHECKINPOINTER(pOutPoints);
	RETURN_FAILED_HRESULT(CTF->Transform(CoordSysGuid, InPoints, pOutPoints));
	return S_OK;
}

// Implementation of TransformInversePts
STDMETHODIMP CTRiASCSTransformService::TransformInversePts(BSTR CoordSysGuid, 
	ITRiASCSTransform *CTF, VARIANT InPoints, VARIANT *pOutPoints)
{
	CHECKINPOINTER(pOutPoints);
	RETURN_FAILED_HRESULT(CTF->TransformInverse(CoordSysGuid, InPoints, pOutPoints));
	return S_OK;
}

// Implementation of EnumCoordSystemNames
STDMETHODIMP CTRiASCSTransformService::EnumCoordSystemNames(IEnumCoordSystemNames **ppIEnum)
{
	ATLTRACE(_T("CTRiASCSTransformService::EnumCoordSystemNames\n"));

	// Check for NULL pointer parameters
	if (!ppIEnum) return E_POINTER;
	*ppIEnum = NULL;

CComObject<CEnumCoordSystemNames> *pEnum = NULL;

	RETURN_FAILED_HRESULT(CComObject<CEnumCoordSystemNames>::CreateInstance(&pEnum));
	return (*ppIEnum = pEnum) -> AddRef(), S_OK;
}

