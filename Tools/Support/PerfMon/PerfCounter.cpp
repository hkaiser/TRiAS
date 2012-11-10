// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 02:05:25 PM
//
// @doc
// @module PerfCounter.cpp | Implementation of the <c CPerfCounter> class

#include "stdafx.h"

#include <classics/atomic_counter.h>
#include <Com/PerfMonContext.h>

#include "Wrapper.h"
#include "LockMutex.h"

#include "PerfCounter.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfCounter

STDMETHODIMP CPerfCounter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfCounter,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
STDMETHODIMP CPerfCounter::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPerfCounter::Load (void *pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}


STDMETHODIMP CPerfCounter::InitNew()
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
IMPLEMENT_PROPERTY_ACCESS(CPerfCounter, Type, COUNTERTYPE);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounter, Name, BSTR);
IMPLEMENT_PROPERTY_GET(CPerfCounter, ContextName, BSTR);

///////////////////////////////////////////////////////////////////////////////
// PerfCounterInt32
// Properties
STDMETHODIMP CPerfCounterInt32::get_Value(VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

CComVariant vValue(m_Value);

	return vValue.Detach(pVal);
}

STDMETHODIMP CPerfCounterInt32::put_Value(VARIANT newVal)
{
	_ASSERTE(m_Value.isvalid());

CComVariant vValue;

	RETURN_FAILED_HRESULT(vValue.ChangeType (VT_I4, &newVal));

	m_Value.exchange (V_I4(&vValue));
	return S_OK;
}

STDMETHODIMP CPerfCounter::put_ContextName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_ContextName = newVal;
	return GetPerfContext (newVal, IID_IPerfContextHelper, m_Ctx.ppv());
}

///////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CPerfCounterInt32::Increment(LONG lDelta)
{
	_ASSERTE(m_Value.isvalid());

	m_Value += lDelta;
	return S_OK;
}

STDMETHODIMP CPerfCounterInt32::Step()
{
	_ASSERTE(m_Value.isvalid());

	++m_Value;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPerfCounterInt32::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistMemory
STDMETHODIMP CPerfCounterInt32::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
	if (sizeof(LONG) > cbSize)
		return E_UNEXPECTED;		// zu wenig Platz

	_ASSERTE(NULL != pvMem);

	m_Value = (LONG *)pvMem;

	_ASSERTE(sizeof(LONG) == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfCounterInt32::GetSizeMax (ULONG *pcbSize)
{
	*pcbSize = sizeof(LONG);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// PerfCounterInt64

// Properties
STDMETHODIMP CPerfCounterInt64::get_Value(VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

CComVariant vValue;

	V_VT(&vValue) = VT_CY;
	V_CY(&vValue).int64 = m_Value;
	return vValue.Detach(pVal);
}

STDMETHODIMP CPerfCounterInt64::put_Value(VARIANT newVal)
{
	_ASSERTE(NULL != m_pValue);

CComVariant vValue;

	RETURN_FAILED_HRESULT(vValue.ChangeType (VT_CY, &newVal));

CLockMemMutex LockMtx (m_Ctx);

	if (LockMtx)
		*m_pValue = m_Value = V_CY(&vValue).int64;
	else
		m_Value = V_CY(&vValue).int64;
	return LockMtx.Status();
}

///////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CPerfCounterInt64::Increment(LONG lDelta)
{
	_ASSERTE(NULL != m_pValue);
	m_Value += lDelta;

CLockMemMutex LockMtx (m_Ctx);

	if (LockMtx)
		*m_pValue = m_Value;
	return LockMtx.Status();
}

STDMETHODIMP CPerfCounterInt64::Step()
{
	_ASSERTE(NULL != m_pValue);

CLockMemMutex LockMtx (m_Ctx);

	if (LockMtx)
		*m_pValue = ++m_Value;
	else
		++m_Value;
	return LockMtx.Status();
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPerfCounterInt64::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistMemory
STDMETHODIMP CPerfCounterInt64::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
	if (sizeof(LONGLONG) > cbSize)
		return E_UNEXPECTED;		// zu wenig Platz

	_ASSERTE(NULL != pvMem);

	m_pValue = (LONGLONG *)pvMem;
	*m_pValue = m_Value;			// ohne Mtx, da bereits gelockt

	_ASSERTE(sizeof(LONGLONG) == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfCounterInt64::GetSizeMax (ULONG *pcbSize)
{
	*pcbSize = sizeof(LONGLONG);
	return S_OK;
}

