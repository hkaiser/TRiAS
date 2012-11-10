// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 18:29:03 
//
// @doc
// @module ICommandPrepareImpl.h | Declaration of the <c CICommandPrepareImpl> class

#if !defined(_ICOMMANDPREPAREIMPL_H__5ECDC482_ECF4_4215_9AC6_42CFCA7FE568__INCLUDED_)
#define _ICOMMANDPREPAREIMPL_H__5ECDC482_ECF4_4215_9AC6_42CFCA7FE568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// helper for ICommandPrepare (counts open Recordsets)
template <class T>
class ATL_NO_VTABLE IInternalConnectionCommandImpl : 
	public IInternalConnection
{
public:
	STDMETHOD(AddConnection)()
	{
	T* pT = static_cast<T *>(this);

		T::_ThreadModel::Increment(&pT->m_cRowsetsOpen);
		return S_OK;
	}
	STDMETHOD(ReleaseConnection)()
	{
	T* pT = static_cast<T *>(this);

		T::_ThreadModel::Decrement(&pT->m_cRowsetsOpen);
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// implementation of ICommandPrepare
template<typename T>
class ATL_NO_VTABLE ICommandPrepareImpl :
	public ICommandPrepare
{
public:
	ICommandPrepareImpl() : 
		m_fIsPrepared(false) 
#if _ATL_VER < 0x0700
		, m_cRowsetsOpen(0) 
#endif // _ATL_VER < 0x0700
	{
	}

	HRESULT PrepareCommand (ULONG cExpectedRuns)
	{
		return S_OK;
	}
	HRESULT UnprepareCommand ()
	{
		return S_OK;
	}

// ICommandPrepare
	STDMETHODIMP Prepare(ULONG cExpectedRuns)
	{
		ATLTRACE2(atlTraceDBProvider, 2, "ICommandPrepareImpl::Prepare\n");

	T *pT = static_cast<T *>(this);

		T::ObjectLock lock(pT);
		if (pT->m_cRowsetsOpen != 0) {
			ATLTRACE2(atlTraceDBProvider, 0, "Unprepare called with Open Rowsets\n");
			return DB_E_OBJECTOPEN;
		}
		if (m_fIsPrepared)
			return S_OK;

		if (pT->CheckCommandText(pT->GetUnknown()) == DB_E_NOCOMMAND)
			return DB_E_NOCOMMAND;

	HRESULT hr = pT -> PrepareCommand(cExpectedRuns);

		if (SUCCEEDED(hr))
			m_fIsPrepared = true;
		return hr;
	}
	STDMETHODIMP Unprepare()
	{
		ATLTRACE2(atlTraceDBProvider, 2, "ICommandPrepareImpl::Unprepare\n");
	
	T *pT = static_cast<T *>(this);
	
		T::ObjectLock lock(pT);
		if (pT->m_cRowsetsOpen != 0) {
			ATLTRACE2(atlTraceDBProvider, 0, "Unprepare called with Open Rowsets\n");
			return DB_E_OBJECTOPEN;
		}
		if (!m_fIsPrepared)
			return S_OK;

	HRESULT hr = pT->UnprepareCommand();

		if (SUCCEEDED(hr))
			m_fIsPrepared = false;
		return hr;
	}

#if _ATL_VER < 0x0700
	LONG m_cRowsetsOpen;
#endif // _ATL_VER < 0x0700

protected:
	unsigned m_fIsPrepared : 1;
};

#endif // !defined(_ICOMMANDPREPAREIMPL_H__5ECDC482_ECF4_4215_9AC6_42CFCA7FE568__INCLUDED_)
