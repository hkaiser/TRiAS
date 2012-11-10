///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CPTRiASFeatureEvents.h | Events, die sich auf Objekteigenschaften 
// beziehen

#if !defined(_CPTRIASFEATUREEVENTS_H__3A9F5C05_DE8C_11D1_8603_00600875138A__INCLUDED_)
#define _CPTRIASFEATUREEVENTS_H__3A9F5C05_DE8C_11D1_8603_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASFeatureEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASFeatureEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASFeatureEvents, CComDynamicUnkArray>
{
public:

//ITRiASFeatureEvents : IUnknown
public:
	HRESULT Fire_CreatingFeature(
		VARIANT NameOrHandle,
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
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->CreatingFeature(NameOrHandle, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureToCreate(
		VARIANT NameOrHandle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureToCreate(NameOrHandle);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureCreated(
		IDispatch * Item)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureCreated(Item);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ModifyingFeature(
		IDispatch * Item,
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
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->ModifyingFeature(Item, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureToModify(
		IDispatch * Item)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureToModify(Item);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureModified(
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
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureModified(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingFeature(
		IDispatch * Item,
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
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->DeletingFeature(Item, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureToDelete(
		IDispatch * Item)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureToDelete(Item);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FeatureDeleted(
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
				ITRiASFeatureEvents* pITRiASFeatureEvents = reinterpret_cast<ITRiASFeatureEvents*>(*pp);
				ret = pITRiASFeatureEvents->FeatureDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASFEATUREEVENTS_H__3A9F5C05_DE8C_11D1_8603_00600875138A__INCLUDED_)
