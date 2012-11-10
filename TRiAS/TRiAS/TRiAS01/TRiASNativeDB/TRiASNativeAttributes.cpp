// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.05.2001 11:16:56 
//
// @doc
// @module TRiASNativeAttributes.cpp | Definition of the <c CTRiASNativeAttributes> class

#include "stdafx.h"

#include <Com/Thunk.h>
#include <NativeMerkmal.h>

#include "TRiASNativeDB.h"
#include "TRiASNativeAttributes.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

using namespace trias_nativemerkmal;

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeAttributes

STDMETHODIMP CTRiASNativeAttributes::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASEnumNativeAttributes ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeAttributes::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeAttributes::FinalRelease()
{
}

// Enumerator mit allen Objektklassen einer Datenquelle füllen
namespace {
	typedef HRESULT (CALLBACK *ENUMATTRIBUTECALLBACK)(INT_PTR, DWORD, UINT_PTR);

	class CEnumAttributeThunk : 
		public CStdThunk<CTRiASNativeAttributes>
	{
	public:
		CEnumAttributeThunk(CTRiASNativeAttributes *pThis)
		{
			InitThunk(reinterpret_cast<TMFP>(CTRiASNativeAttributes::FInitItem), pThis);
		}
		ENUMATTRIBUTECALLBACK GetCallback() 
		{
			return reinterpret_cast<ENUMATTRIBUTECALLBACK>(CStdThunk<CTRiASNativeAttributes>::GetThunk());
		}
	};
}

HRESULT CTRiASNativeAttributes::FInitItem (INT_PTR lMCode, DWORD dwType, UINT_PTR dwData)
{
	m_coll.push_back(lMCode);
	return S_OK;
}

HRESULT CTRiASNativeAttributes::FInit(HPROJECT hPr, INT_PTR lIdent)
{
HRESULT hr = E_FAIL;

	COM_TRY {
	// derzeit haben alle Objektklassen einer Datenbank einen identischen Staz von 
	// Objekteigenschaften
	CEnumAttributeThunk Thunk(this);

		THROW_FAILED_HRESULT(hr = CNativeMerkmal::EnumMerkmale(hPr, Thunk.GetCallback(), NULL));

	} COM_CATCH;
	return hr;
}

