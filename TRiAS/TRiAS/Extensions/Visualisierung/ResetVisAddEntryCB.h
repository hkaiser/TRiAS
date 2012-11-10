// @doc 
// @module ResetVisAddEntryCB.h | Declaration of the CResetVisAddEntryCB

#if !defined(_RESETVISADDENTRYCB_H__A4FAE32C_E5A3_11D2_9BD9_586A20524153__INCLUDED_)
#define _RESETVISADDENTRYCB_H__A4FAE32C_E5A3_11D2_9BD9_586A20524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <selidprp.h>

EXTERN_C const CLSID __declspec(selectany) CLSID_ResetVisAddEntryCB = {0xA4FAE30B,0xE5A3,0x11D2,{0x9B,0xD9,0x58,0x6A,0x20,0x52,0x41,0x53}};

/////////////////////////////////////////////////////////////////////////////
// CResetVisAddEntryCB
class ATL_NO_VTABLE CResetVisAddEntryCB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CResetVisAddEntryCB, &CLSID_ResetVisAddEntryCB>,
	public IAddEntryCallback
{
public:
	CResetVisAddEntryCB()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_RESETVISADDENTRYCB)
	DECLARE_NOT_AGGREGATABLE(CResetVisAddEntryCB)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CResetVisAddEntryCB)
		COM_INTERFACE_ENTRY(IAddEntryCallback)
	END_COM_MAP()

// IAddEntryCallback
public:
	STDMETHOD(AddEntry) (THIS_ INT_PTR lIdent, DWORD dwTypes, DWORD *pdwTypesToAdd);
};

#endif // !defined(_RESETVISADDENTRYCB_H__A4FAE32C_E5A3_11D2_9BD9_586A20524153__INCLUDED_)
