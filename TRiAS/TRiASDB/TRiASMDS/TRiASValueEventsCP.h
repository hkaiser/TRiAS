// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.06.2000 20:28:04 
//
// @doc
// @module TRiASValueEventsCP.h | Declaration of the <c CProxyITRiASValueEvents> class

#if !defined(_TRIASVALUEEVENTSCP_H__E4364E9C_1E8E_4C9E_A895_2A66016C6EEF__INCLUDED_)
#define _TRIASVALUEEVENTSCP_H__E4364E9C_1E8E_4C9E_A895_2A66016C6EEF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

template <class T>
class ATL_NO_VTABLE CProxyITRiASValueEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASValueEvents, CComDynamicUnkArray>
{
public:
	HRESULT Fire_ModifyingValue(BSTR Name, VARIANT_BOOL * pVal)
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
			ITRiASValueEvents* pITRiASValueEvents = reinterpret_cast<ITRiASValueEvents*>(sp.p);
			if (pITRiASValueEvents != NULL) {
				ret = pITRiASValueEvents->ModifyingValue(Name, pVal);
				if (*pVal != VARIANT_FALSE) break;		// nicht modifizieren
			}
		}
		return ret;
	
	}
	HRESULT Fire_ValueToModify(BSTR Name)
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
			ITRiASValueEvents* pITRiASValueEvents = reinterpret_cast<ITRiASValueEvents*>(sp.p);
			if (pITRiASValueEvents != NULL)
				ret = pITRiASValueEvents->ValueToModify(Name);
		}
		return ret;
	}
	HRESULT Fire_ValueModified(BSTR Name)
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
			ITRiASValueEvents* pITRiASValueEvents = reinterpret_cast<ITRiASValueEvents*>(sp.p);
			if (pITRiASValueEvents != NULL)
				ret = pITRiASValueEvents->ValueModified(Name);
		}
		return ret;
	}
};

#endif // !defined(_TRIASVALUEEVENTSCP_H__E4364E9C_1E8E_4C9E_A895_2A66016C6EEF__INCLUDED_)
