// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 12:32:16 
//
// @doc
// @module IRowsetNotifySourceImpl.h | Declaration of the <c CIRowsetNotifySourceImpl> class

#if !defined(_IROWSETNOTIFYSOURCEIMPL_H__87CCBECD_54B2_478E_9E05_9D92A8794EF9__INCLUDED_)
#define _IROWSETNOTIFYSOURCEIMPL_H__87CCBECD_54B2_478E_9E05_9D92A8794EF9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if _ATL_VER < 0x0700

class CComSharedMutex
{
public:
	CComSharedMutex()
	{
		m_lInterlockedVariable = -1;
	};

	inline bool IncrementMutex() 
	{ 
		long lAvailable = ::InterlockedIncrement(&m_lInterlockedVariable);
		if (lAvailable > 0)
		{
			// Mutex is held, decrement and return false
			DecrementMutex();
			return false;
		}
		else
			return true;
	};
	inline void DecrementMutex() 
	{
		::InterlockedDecrement(&m_lInterlockedVariable);
	};

	long m_lInterlockedVariable;
};

template <class T, class ReentrantEventSync = CComSharedMutex>
class IRowsetNotifyCP : 
	public IConnectionPointImpl<T, &__uuidof(IRowsetNotify), CComDynamicUnkArray>,
	public ReentrantEventSync
{
public:
	HRESULT Fire_OnFieldChange(IRowset * pRowset, HROW hRow, DBORDINAL cColumns, 
				DBORDINAL* rgColumns, DBREASON eReason, DBEVENTPHASE ePhase, 
				BOOL fCantDeny)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetNotifyCP::Fire_OnFieldChange\n"));
		
		IncrementMutex();	// Lock the event handler so other's can't call methods
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IRowsetNotify* pIRowsetNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
			if (pIRowsetNotify != NULL)
				ret = pIRowsetNotify->OnFieldChange(pRowset, hRow, cColumns,
					rgColumns, eReason, ePhase, fCantDeny);
			switch(ePhase)
			{
			case DBEVENTPHASE_OKTODO:
				if (ret == S_FALSE  && fCantDeny == FALSE)
				{
					// if we get an S_FALSE back, a consumer has vetoed the
					// request.  In this case, we should send a FAILEDTODO
					// to ONLY those consumers already notified.
					for (int nFailedIndex = 0; nFailedIndex <= nConnectionIndex; nFailedIndex++)
					{
						pT->Lock();
						CComPtr<IUnknown> sp = m_vec.GetAt(nFailedIndex);
						pT->Unlock();
						IRowsetNotify* pIFailedNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
						if (pIFailedNotify != NULL)
							pIFailedNotify->OnFieldChange(pRowset, hRow, cColumns, rgColumns, 
								eReason, DBEVENTPHASE_FAILEDTODO, FALSE);
					}
					// Terminate the loop as no further consumers should be
					// notified.
					DecrementMutex();
					return ret;
				}
				else
				{
					if (ret != S_OK)
						ret = S_OK;
				}
				break;
			case DBEVENTPHASE_ABOUTTODO:
			case DBEVENTPHASE_SYNCHAFTER:
				if (ret == S_FALSE && fCantDeny == FALSE)
				{
					Fire_OnFieldChange(pRowset, hRow, cColumns, rgColumns,
						eReason, DBEVENTPHASE_FAILEDTODO, FALSE);
					DecrementMutex();
					return ret;
				}
				else
				{
					if (ret != S_OK)
						ret = S_OK;
				}
				break;
			case DBEVENTPHASE_FAILEDTODO:
			case DBEVENTPHASE_DIDEVENT:
				break; // Nothing todo
			default:
				ATLTRACE(atlTraceDBProvider, 0, _T("IRowsetNotifyCP::Fire_OnFieldChange: Unknown Phase requested\n"));
				ATLASSERT(FALSE);
				DecrementMutex();
				return E_FAIL;
			};
		}	
		DecrementMutex();
		if( ret != S_OK && ret != S_FALSE )
			ret = S_OK;
		return ret;
	
	}
	HRESULT Fire_OnRowChange(IRowset * pRowset, DBCOUNTITEM cRows, const HROW rghRows[], 
		DBREASON eReason, DBEVENTPHASE ePhase, BOOL fCantDeny)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetNotifyCP::Fire_OnRowChange\n"));
		IncrementMutex();  // Lock the handler so other's can't call methods
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IRowsetNotify* pIRowsetNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
			if (pIRowsetNotify != NULL)
			{
				ret = pIRowsetNotify->OnRowChange(pRowset, cRows, rghRows, eReason, ePhase, fCantDeny);
			}
			switch(ePhase)
			{
			case DBEVENTPHASE_OKTODO:
				if (ret == S_FALSE && fCantDeny == FALSE)
				{
					// if we get an S_FALSE back, a consumer has vetoed the
					// request.  In this case, we should send a FAILEDTODO
					// to ONLY those consumers already notified.
					for (int nFailedIndex = 0; nFailedIndex <= nConnectionIndex; nFailedIndex++)
					{
						pT->Lock();
						CComPtr<IUnknown> sp = m_vec.GetAt(nFailedIndex);
						pT->Unlock();
						IRowsetNotify* pIFailedNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
						if (pIFailedNotify != NULL)
							pIFailedNotify->OnRowChange(pRowset, cRows, rghRows, eReason,
								DBEVENTPHASE_FAILEDTODO, FALSE);
					}
					// Terminate the loop as no further consumers should be
					// notified.
					DecrementMutex();
					return ret;
				}
				break;
			case DBEVENTPHASE_SYNCHAFTER:
			case DBEVENTPHASE_ABOUTTODO:
				if (ret	== S_FALSE && fCantDeny == FALSE)
				{
					Fire_OnRowChange(pRowset, cRows, rghRows, eReason,
						DBEVENTPHASE_FAILEDTODO, FALSE);
					DecrementMutex();
					return ret;
				}
				break;
			case DBEVENTPHASE_FAILEDTODO:
			case DBEVENTPHASE_DIDEVENT:
				break; // Nothing todo
			default:
				ATLTRACE(atlTraceDBProvider, 0, _T("IRowsetNotifyCP::Fire_OnRowChange: Unknown Phase requested\n"));
				ATLASSERT(FALSE);
				DecrementMutex();
				return E_FAIL;
			};
		}	
		DecrementMutex();
		if( ret != S_OK && ret != S_FALSE )
			ret = S_OK;
		return ret;
	
	}
	HRESULT Fire_OnRowsetChange(IRowset* pRowset, DBREASON eReason, 
		DBEVENTPHASE ePhase, BOOL fCantDeny)
	{
		ATLTRACE(atlTraceDBProvider, 2, _T("IRowsetNotifyCP::Fire_OnRowsetChange\n"));
		IncrementMutex(); // Lock the handler so others can't call methods
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IRowsetNotify* pIRowsetNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
			if (pIRowsetNotify != NULL)
				ret = pIRowsetNotify->OnRowsetChange(pRowset, eReason, ePhase, fCantDeny);
			switch(ePhase)
			{
			case DBEVENTPHASE_OKTODO:
				if (ret == S_FALSE && fCantDeny == FALSE)
				{
					// if we get an S_FALSE back, a consumer has vetoed the
					// request.  In this case, we should send a FAILEDTODO
					// to ONLY those consumers already notified.
					for (int nFailedIndex = 0; nFailedIndex <= nConnectionIndex; nFailedIndex++)
					{
						pT->Lock();
						CComPtr<IUnknown> sp = m_vec.GetAt(nFailedIndex);
						pT->Unlock();
						IRowsetNotify* pIFailedNotify = reinterpret_cast<IRowsetNotify*>(sp.p);
						if (pIFailedNotify != NULL)
							pIFailedNotify->OnRowsetChange(pRowset, eReason, 
								DBEVENTPHASE_FAILEDTODO, FALSE);
					}
					// Terminate the loop as no further consumers should be
					// notified. 
					DecrementMutex();
					return ret;
				}
				break;
			case DBEVENTPHASE_ABOUTTODO:
			case DBEVENTPHASE_SYNCHAFTER:
				if (ret == S_FALSE && fCantDeny == FALSE)
				{
					Fire_OnRowsetChange(pRowset, eReason, DBEVENTPHASE_FAILEDTODO, 
						FALSE);
					DecrementMutex();
					return ret;
				}
				break;
			case DBEVENTPHASE_FAILEDTODO:
			case DBEVENTPHASE_DIDEVENT:
				break; // Nothing todo
			default:
				ATLTRACE(atlTraceDBProvider, 0, _T("IRowsetNotifyCP::Fire_OnRowChange: Unknown Phase requested\n"));
				ATLASSERT(FALSE);
				DecrementMutex();
				return E_FAIL;
			};
		}
		DecrementMutex();
		if( ret != S_OK && ret != S_FALSE )
			ret = S_OK;
		return ret;
	
	}
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_IROWSETNOTIFYSOURCEIMPL_H__87CCBECD_54B2_478E_9E05_9D92A8794EF9__INCLUDED_)
