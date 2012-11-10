///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CPTRiASViewItemEvents.h | Declaration of <c CProxyITRiASViewItemEvents> class

#if !defined(_CPTRIASVIEWITEMEVENTS_H__B7AEB936_922C_11D1_BA01_080036D63803__INCLUDED_)
#define _CPTRIASVIEWITEMEVENTS_H__B7AEB936_922C_11D1_BA01_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template <class T>
class ATL_NO_VTABLE CProxyITRiASViewItemEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASViewItemEvents, CComDynamicUnkArray>
{
public:

//ITRiASViewItemEvents : IUnknown
public:
	HRESULT Fire_CreatingViewItem(
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->CreatingViewItem(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemToCreate(
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemCreated(
		IDispatch * pIProp)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemCreated(pIProp);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ModifyingViewItem(
		IDispatch *pIViewItem,
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ModifyingViewItem(pIViewItem, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemToModify(
		IDispatch *pIViewItem)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemToModify(pIViewItem);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemModified(
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemModified(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingViewItem(
		IDispatch *pIViewItem,
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->DeletingViewItem(pIViewItem, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemToDelete(
		IDispatch *pIViewItem)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemToDelete(pIViewItem);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ViewItemDeleted(
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
				ITRiASViewItemEvents* pITRiASViewItemEvents = reinterpret_cast<ITRiASViewItemEvents*>(*pp);
				ret = pITRiASViewItemEvents->ViewItemDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASVIEWITEMEVENTS_H__B7AEB936_922C_11D1_BA01_080036D63803__INCLUDED_)
