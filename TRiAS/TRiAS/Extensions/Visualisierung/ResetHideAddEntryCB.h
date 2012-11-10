// @doc 
// @module ResetHideAddEntryCB.h | Declaration of the CResetHideAddEntryCB

#if !defined(_RESETHIDEADDENTRYCB_H__0CB3A671_E5CE_11D2_9BD9_586A20524153__INCLUDED_)
#define _RESETHIDEADDENTRYCB_H__0CB3A671_E5CE_11D2_9BD9_586A20524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <selidprp.h>

EXTERN_C const CLSID __declspec(selectany) CLSID_ResetHideAddEntryCB = {0x0CB3A667,0xE5CE,0x11D2,{0x9B,0xD9,0x58,0x6A,0x20,0x52,0x41,0x53}};

/////////////////////////////////////////////////////////////////////////////
// CResetHideAddEntryCB
class ATL_NO_VTABLE CResetHideAddEntryCB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CResetHideAddEntryCB, &CLSID_ResetHideAddEntryCB>,
	public IAddEntryCallback
{
public:
	CResetHideAddEntryCB()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_RESETHIDEADDENTRYCB)
	DECLARE_NOT_AGGREGATABLE(CResetHideAddEntryCB)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CResetHideAddEntryCB)
		COM_INTERFACE_ENTRY(IAddEntryCallback)
	END_COM_MAP()

// IAddEntryCallback
public:
	STDMETHOD(AddEntry) (THIS_ INT_PTR lIdent, DWORD dwTypes, DWORD *pdwTypesToAdd);
};

#endif // !defined(_RESETHIDEADDENTRYCB_H__0CB3A671_E5CE_11D2_9BD9_586A20524153__INCLUDED_)
