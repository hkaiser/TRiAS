///////////////////////////////////////////////////////////////////////////
// CPTRiASPropertyEvents.h

#if !defined(_CPTRIASPROPERTYEVENTS_H__96E58003_6415_11D1_9729_00A024D6F582__INCLUDED_)
#define _CPTRIASPROPERTYEVENTS_H__96E58003_6415_11D1_9729_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASPropertyEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASPropertyEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASPropertyEvents, CComDynamicUnkArray>
{
public:

// ITRiASPropertyEvents : IUnknown
public:
	HRESULT Fire_CreatingProperty(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->CreatingProperty(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyToCreate(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyCreated(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyCreated(pIProp);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ModifyingProperty(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->ModifyingProperty(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyToModify(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyToModify(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyModified(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyModified(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingProperty(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->DeletingProperty(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyToDelete(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyToDelete(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_PropertyDeleted(
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
				ITRiASPropertyEvents* pITRiASPropertyEvents = reinterpret_cast<ITRiASPropertyEvents*>(*pp);
				ret = pITRiASPropertyEvents->PropertyDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASPROPERTYEVENTS_H__96E58003_6415_11D1_9729_00A024D6F582__INCLUDED_)
