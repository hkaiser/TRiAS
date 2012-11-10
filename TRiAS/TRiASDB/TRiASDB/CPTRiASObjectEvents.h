// $Header: /TRiAS/TRiASDB/TRiASDB/CPTRiASObjectEvents.h 1     15.06.98 21:30 Hartmut Kaiser $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 05/30/1998 07:54:39 PM
//
// @doc
// @module CPTRiASObjectEvents.h | Events, die sich auf Objekte beziehen

#if !defined(_CPTRIASOBJECTEVENTS_H__25FE9635_F798_11D1_8637_00600875138A__INCLUDED_)
#define _CPTRIASOBJECTEVENTS_H__25FE9635_F798_11D1_8637_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASObjectEvents
template <class T>
class ATL_NO_VTABLE CProxyITRiASObjectEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASObjectEvents, CComDynamicUnkArray>
{
public:

//ITRiASObjectEvents : IUnknown
public:
	HRESULT Fire_CreatingObject(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->CreatingObject(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectToCreate(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectToCreate(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectCreated(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectCreated(Item);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ModifyingObject(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ModifyingObject(Item, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectToModify(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectToModify(Item);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectModified(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectModified(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_DeletingObject(
		IDispatch * Object,
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->DeletingObject(Object, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht löschen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectToDelete(
		IDispatch * Object)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectToDelete(Object);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectDeleted(
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
				ITRiASObjectEvents* pITRiASObjectEvents = reinterpret_cast<ITRiASObjectEvents*>(*pp);
				ret = pITRiASObjectEvents->ObjectDeleted(Name);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPTRIASOBJECTEVENTS_H__25FE9635_F798_11D1_8637_00600875138A__INCLUDED_)
