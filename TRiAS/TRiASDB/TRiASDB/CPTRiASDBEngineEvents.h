// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.02.2001 17:40:59 
//
// @doc
// @module CPTRiASDBEngineEvents.h | Implementation of the <c CProxyITRiASDBEngineEvents> class

#if !defined(_CPTRIASDBENGINEEVENTS_H__EBE1E33D_D86B_4617_8426_091E78115875__INCLUDED_)
#define _CPTRIASDBENGINEEVENTS_H__EBE1E33D_D86B_4617_8426_091E78115875__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

template <class T>
class CProxyITRiASDBEngineEvents : 
	public IConnectionPointImpl<T, &IID_ITRiASDBEngineEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_AskToContinue(CONTINUEMODE * Mode)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ITRiASDBEngineEvents* pITRiASDBEngineEvents = reinterpret_cast<ITRiASDBEngineEvents*>(sp.p);
			if (pITRiASDBEngineEvents != NULL) {
				ret = pITRiASDBEngineEvents->AskToContinue(Mode);
				if (FAILED(ret) || CONTINUEMODE_Continue != *Mode)
					break;
			}
		}	
		return ret;
	
	}
};

#endif // !defined(_CPTRIASDBENGINEEVENTS_H__EBE1E33D_D86B_4617_8426_091E78115875__INCLUDED_)
