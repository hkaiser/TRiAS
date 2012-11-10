///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CPTRiASConnectionEvents.h | Events, die Connection-bezogene 
// Ereignisse melden

#if !defined(_CPTRIASCONNECTIONEVENTS_H__96E58004_6415_11D1_9729_00A024D6F582__INCLUDED_)
#define _CPTRIASCONNECTIONEVENTS_H__96E58004_6415_11D1_9729_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASConnectionEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASConnectionEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASConnectionEvents, CComDynamicUnkArray>
{
public:

//ITRiASConnectionEvents : IUnknown
public:
	HRESULT Fire_CreatingConnection(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->CreatingConnection(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionToCreate(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionCreated(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionCreated(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OpeningConnection(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->OpeningConnection(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht öffnen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionToOpen(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionToOpen(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionOpened(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionOpened(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ClosingConnection(
		IDispatch * pIPrj,
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ClosingConnection(pIPrj, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht schließen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionToClose(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionToClose(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionClosed(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionClosed(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingConnection(
		IDispatch * pIPrj,
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->DeletingConnection(pIPrj, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionToDelete(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionToDelete(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionDeleted(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_RenamingConnection(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->RenamingConnection(OldName, NewName, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht umbenennen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionToRename(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionToRename(OldName, NewView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectionRenamed(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectionRenamed(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ChangingConnectedDatasource(
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
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ChangingConnectedDatasource(pIConn, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht bearbeiten
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectedDatasourceToChange(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectedDatasourceToChange(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ConnectedDatasourceChanged(
		IDispatch * pIConn)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASConnectionEvents* pITRiASConnectionEvents = reinterpret_cast<ITRiASConnectionEvents*>(*pp);
				ret = pITRiASConnectionEvents->ConnectedDatasourceChanged(pIConn);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASCONNECTIONEVENTS_H__96E58004_6415_11D1_9729_00A024D6F582__INCLUDED_)
