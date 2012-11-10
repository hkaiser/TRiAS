///////////////////////////////////////////////////////////////////////////
// @doc
// @module CPTRiASViewEvents.h | Events, die ViewItem-bezogene Ereignisse
// melden

#if !defined(_CPTRIASVIEWEVENTS_H__3E4A3F25_878C_11D1_9784_00A024D6F582__INCLUDED_)
#define _CPTRIASVIEWEVENTS_H__3E4A3F25_878C_11D1_9784_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASViewEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASViewEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASViewEvents, CComDynamicUnkArray>
{
public:

//ITRiASViewEvents : IUnknown
public:
	HRESULT Fire_CreatingView(
		BSTR Name,
		VARIANT_BOOL * pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->CreatingView(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewToCreate(
		BSTR Name)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewCreated(
		IDispatch * pIView)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewCreated(pIView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ChangingView(
		BSTR OldName,
		BSTR NewName,
		VARIANT_BOOL * pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ChangingView(OldName, NewName, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht wechseln
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewToChange(
		BSTR OldName, BSTR NewView)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewToChange(OldName, NewView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewChanged(
		IDispatch * pIView)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewChanged(pIView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingView(
		IDispatch * pIConn,
		VARIANT_BOOL * pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->DeletingView(pIConn, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewToDelete(
		IDispatch * pIView)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewToDelete(pIView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewDeleted(
		BSTR Name)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewEvents* pITRiASViewEvents = reinterpret_cast<ITRiASViewEvents*>(*pp);
				ret = pITRiASViewEvents->ViewDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASVIEWEVENTS_H__3E4A3F25_878C_11D1_9784_00A024D6F582__INCLUDED_)
