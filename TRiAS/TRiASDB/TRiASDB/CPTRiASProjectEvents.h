///////////////////////////////////////////////////////////////////////////
// CPTRiASProjectEvents.h

#if !defined(_CPTRIASPROJECTEVENTS_H__96E58005_6415_11D1_9729_00A024D6F582__INCLUDED_)
#define _CPTRIASPROJECTEVENTS_H__96E58005_6415_11D1_9729_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASProjectEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASProjectEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASProjectEvents, CComDynamicUnkArray>
{
public:

// ITRiASProjectEvents : IUnknown
public:
	HRESULT Fire_ProjectToCreate(
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
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectCreated(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectCreated(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OpeningProject(
		BSTR Name, VARIANT_BOOL *pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->OpeningProject(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht öffnen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectToOpen(
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
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectToOpen(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectIsOpening(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectIsOpening(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectOpened(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectOpened(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ClosingProject(
		IDispatch * pIPrj, VARIANT_BOOL *pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ClosingProject(pIPrj, pVal);
				if (*pVal != VARIANT_FALSE) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectToClose(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectToClose(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectClosed(
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
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ProjectClosed(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_Save(
		IDispatch * pIPrj,
		IUnknown * Stg,
		VARIANT_BOOL fSameAsLoad)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->Save(pIPrj, Stg, fSameAsLoad);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_SaveCompleted(
		IDispatch * pIPrj,
		VARIANT Stg)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->SaveCompleted(pIPrj, Stg);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_HandsOffStorage(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->HandsOffStorage(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ErrorOpeningProject(
		IDispatch * pIPrj)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASProjectEvents* pITRiASProjectEvents = reinterpret_cast<ITRiASProjectEvents*>(*pp);
				ret = pITRiASProjectEvents->ErrorOpeningProject(pIPrj);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASPROJECTEVENTS_H__96E58005_6415_11D1_9729_00A024D6F582__INCLUDED_)
