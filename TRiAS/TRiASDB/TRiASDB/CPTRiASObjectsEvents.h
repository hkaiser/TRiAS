// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.07.99 21:59:44 
//
// @doc
// @module CPTRiASObjectsEvents.h | Declaration of the <c CCPTRiASObjectsEvents> class

#if !defined(_CPTRIASOBJECTSEVENTS_H__D0DC9300_3AEF_11D3_94FB_0080C786297B__INCLUDED_)
#define _CPTRIASOBJECTSEVENTS_H__D0DC9300_3AEF_11D3_94FB_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

template <class T>
class CProxyITRiASObjectsEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASObjectsEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_CreatingObjects(BSTR Name, VARIANT_BOOL * pVal)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL) {
				ret = pITRiASObjectsEvents->CreatingObjects(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
		}
		return ret;
	}
	HRESULT Fire_ObjectsToCreate(BSTR Name)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsToCreate(Name);
		}
		return ret;
	}
	HRESULT Fire_ObjectsCreated(IDispatch * Item)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsCreated(Item);
		}
		return ret;
	}
	HRESULT Fire_ModifyingObjects(CHANGEDOBJECTS rgMode, IDispatch * Item, VARIANT_BOOL * pVal)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL) {
				ret = pITRiASObjectsEvents->ModifyingObjects(rgMode, Item, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
		}
		return ret;
	}
	HRESULT Fire_ObjectsToModify(CHANGEDOBJECTS rgMode, IDispatch * Item)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsToModify(rgMode, Item);
		}
		return ret;
	}
	HRESULT Fire_ObjectsModified(CHANGEDOBJECTS rgMode, BSTR Name)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsModified(rgMode, Name);
		}
		return ret;
	}
	HRESULT Fire_DeletingObjects(IDispatch * Object, VARIANT_BOOL * pVal)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL) {
				ret = pITRiASObjectsEvents->DeletingObjects(Object, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
		}
		return ret;
	}
	HRESULT Fire_ObjectsToDelete(IDispatch * Object)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsToDelete(Object);
		}
		return ret;
	}
	HRESULT Fire_ObjectsDeleted(BSTR Name)
	{
		HRESULT ret = S_OK;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASObjectsEvents* pITRiASObjectsEvents = reinterpret_cast<ITRiASObjectsEvents*>(sp.p);
			if (pITRiASObjectsEvents != NULL)
				ret = pITRiASObjectsEvents->ObjectsDeleted(Name);
		}
		return ret;
	}
};

#endif // !defined(_CPTRIASOBJECTSEVENTS_H__D0DC9300_3AEF_11D3_94FB_0080C786297B__INCLUDED_)
