// $Header: $
// Copyrightę 1998-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.04.2001 16:50:09
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.115 (#HK010427)
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
// PURPOSE.
//
// @doc
// @module CPTRiASDBEngineEvents.h | Implementation of the <c CProxyITRiASDBEngineEvents> class

#if !defined(_CPTRIASDBENGINEEVENTS_H__9B013953_75F2_4762_B780_55495E681F04__INCLUDED_)
#define _CPTRIASDBENGINEEVENTS_H__9B013953_75F2_4762_B780_55495E681F04__INCLUDED_

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
	HRESULT Fire_AskToContinue(CONTINUEMODE *prgMode)
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
			ITRiASDBEngineEvents* pITRiASDBEngineEvents = reinterpret_cast<ITRiASDBEngineEvents *>(sp.p);
			if (pITRiASDBEngineEvents != NULL) {
				ret = pITRiASDBEngineEvents->AskToContinue(prgMode);
				if (FAILED(ret) || CONTINUEMODE_Continue != *prgMode)
					break;
			}
		}	
		return ret;
	
	}
};

#endif // !defined(_CPTRIASDBENGINEEVENTS_H__9B013953_75F2_4762_B780_55495E681F04__INCLUDED_)
