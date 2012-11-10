// $Header: /TRiAS/TRiASDB/TDBGeo/TRiASCSVector.cpp 1	 15.06.98 21:26 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/11/1998 11:27:25 PM
//
// @doc
// @module TRiASCSVector.cpp | Description here

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSVector.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
//IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSVector);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSVector, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSRectangle

STDMETHODIMP CTRiASCSVector::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID * arr[] =
	{
		&IID__DGMVector,
	};
	for (int i = 0;i < sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(* arr[i] , riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// properties

STDMETHODIMP CTRiASCSVector::get_I(double * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_dX;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::put_I(double newVal)
{
ObjectLock l(this);

	m_dX = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::get_J(double * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_dY;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::put_J(double newVal)
{
ObjectLock l(this);

	m_dY = newVal;
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::get_K(double * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	*pVal = m_dZ;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::put_K(double newVal)
{
ObjectLock l(this);

	m_dZ = newVal;
	m_fIsDirty = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// methods

STDMETHODIMP CTRiASCSVector::GetVector (double * Coords)
{
	CHECKOUTPOINTER(Coords);

ObjectLock l(this);

	Coords[0] = m_dX;
	Coords[1] = m_dY;
	Coords[2] = m_dZ;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::SetVector (double * Coords)
{
	CHECKINPOINTER(Coords);

ObjectLock l(this);

	m_dX = Coords[0];
	m_dY = Coords[1];
	m_dZ = Coords[2];
	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSVector
STDMETHODIMP CTRiASCSVector::SetVector(double X , double Y , double Z)
{
ObjectLock l(this);

	m_dX = X;
	m_dY = Y;
	m_dZ = Z;
	return S_OK;
}

STDMETHODIMP CTRiASCSVector::GetVector(double * pX , double * pY , double * pZ)
{
	CHECKOUTPOINTER(pX);
	CHECKOUTPOINTER(pY);
	CHECKOUTPOINTER(pZ);

ObjectLock l(this);

	*pX = m_dX;
	*pY = m_dY;
	*pZ = m_dZ;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSVector::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

HRESULT CTRiASCSVector::Load (LPSTREAM pStm)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);

	RETURN_FAILED_HRESULT(LoadItem (pStm , m_dX));
	RETURN_FAILED_HRESULT(LoadItem (pStm , m_dY));
	RETURN_FAILED_HRESULT(LoadItem (pStm , m_dZ));

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSVector::Save (LPSTREAM pStm , BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

ObjectLock l(this);

	RETURN_FAILED_HRESULT(SaveItem (pStm , m_dX));
	RETURN_FAILED_HRESULT(SaveItem (pStm , m_dY));
	RETURN_FAILED_HRESULT(SaveItem (pStm , m_dZ));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSVector::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);
	pcbSize -> QuadPart = 3 * sizeof(double);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSVector::InitNew (void)
{
ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);
	m_dX = 0.0;
	m_dY = 0.0;
	m_dZ = 1.0;
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSVector::Load (void * pvMem , ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

ObjectLock l(this);

	ERROR_EXPR_TRUE(m_fIsInitialized , STREAM_E_OBJECTALREADYINITIALIZED);
	ASSERT(cbSize >= 3 * sizeof(double));
	::LoadAndAdvance (m_dX, pvMem);
	::LoadAndAdvance (m_dY, pvMem);
	::LoadAndAdvance (m_dZ, pvMem);

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSVector::Save (void * pvMem , BOOL fClearDirty , ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

	ASSERT(cbSize >= 3 * sizeof(double));

ObjectLock l(this);

	::SaveAndAdvance (pvMem, m_dX);
	::SaveAndAdvance (pvMem, m_dY);
	::SaveAndAdvance (pvMem, m_dZ);

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

HRESULT CTRiASCSVector::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);

	ERROR_EXPR_TRUE(!m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 3 * sizeof(double);
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSVector::Clone (IDispatch * * ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

ObjectLock l(this);
CComObject<CTRiASCSVector> *pNew = NULL;

	COM_TRY	{
		THROW_FAILED_HRESULT(CComObject < CTRiASCSVector > ::CreateInstance(& pNew));
		pNew -> AddRef();		// pending AddRef

		// alle Werte kopieren
		pNew -> m_dX = m_dX;
		pNew -> m_dY = m_dY;
		pNew -> m_dZ = m_dZ;

		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

		// Resultat liefern
		 * ppIClonedObj = static_cast < _DGMVector * > (pNew);

	} COM_CATCH_OP (
		RELEASE(pNew);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSVector::GetSizeMaxWkb(ULONG *pulSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSVector::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSVector::SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSVector::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSVector::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	return E_NOTIMPL;
}

