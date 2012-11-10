// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 13:56:26 
//
// @doc
// @module TRiASNativeIdents.cpp | Definition of the <c CTRiASNativeIdents> class

#include "stdafx.h"
#include "TRiASNativeDB.h"

#include <Com/Thunk.h>
#include <NativeIdent.h>

#include "TRiASNativeIdents.h"

using namespace trias_nativeident;

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CTRiASNativeIdents::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASEnumNativeIdents ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeIdents::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeIdents::FinalRelease()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeIdents

// Enumerator mit allen Objektklassen einer Datenquelle füllen
namespace {
	typedef HRESULT (CALLBACK *ENUMIDENTCALLBACK)(INT_PTR, DWORD, UINT_PTR);

	class CEnumIdentThunk : 
		public CStdThunk<CTRiASNativeIdents>
	{
	public:
		CEnumIdentThunk(CTRiASNativeIdents *pThis)
		{
			InitThunk(reinterpret_cast<TMFP>(CTRiASNativeIdents::FInitItem), pThis);
		}
		ENUMIDENTCALLBACK GetCallback() 
		{
			return reinterpret_cast<ENUMIDENTCALLBACK>(CStdThunk<CTRiASNativeIdents>::GetThunk());
		}
	};
}

HRESULT CTRiASNativeIdents::FInitItem (INT_PTR lIdent, DWORD dwObjTypes, UINT_PTR dwData)
{
	m_coll.push_back(lIdent);
	return S_OK;
}

HRESULT CTRiASNativeIdents::FInit(HPROJECT hPr)
{
HRESULT hr = E_FAIL;

	COM_TRY {
	CEnumIdentThunk Thunk(this);

		THROW_FAILED_HRESULT(hr = CNativeIdent::EnumIdents(hPr, Thunk.GetCallback(), NULL));

	} COM_CATCH;
	return hr;
}

