// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 16.11.2002 12:35:12 
//
// @doc
// @module ManageGlobalMemory.h | Declaration of the <c CManageGlobalMemory> class

#if !defined(_MANAGEGLOBALMEMORY_H__79112A16_B5AF_4CA6_A5FE_788F69B316C7__INCLUDED_)
#define _MANAGEGLOBALMEMORY_H__79112A16_B5AF_4CA6_A5FE_788F69B316C7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif

#include <Com/MemoryHelper.h>

/////////////////////////////////////////////////////////////////////////////
// A2D23006-DA01-4A59-9182-7548237502C3
EXTERN_C const GUID __declspec(selectany) IID_IManageGlobalMemory = 
	{ 0xA2D23006, 0xDA01, 0x4A59, 0x91, 0x82, 0x75, 0x48, 0x23, 0x75, 0x02, 0xC3 };

/////////////////////////////////////////////////////////////////////////////
// CManageGlobalMemory
class ATL_NO_VTABLE CManageGlobalMemory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IUnknown
{
public:
	CManageGlobalMemory()
	{
	}
	~CManageGlobalMemory()
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CManageGlobalMemory)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CManageGlobalMemory)
		COM_INTERFACE_ENTRY_IID(IID_IManageGlobalMemory, IUnknown)
	END_COM_MAP()

// IManageGlobalMemory
public:
	HRESULT InitGlobalMem(HGLOBAL hGbl, IUnknown *pIUnkForRelease = NULL)
	{
		m_UnkForRelease = pIUnkForRelease;
		m_Mem.Attach(hGbl);
		return S_OK;
	}
	HRESULT InitGlobalMem(DWORD dwSize, IUnknown *pIUnkForRelease = NULL, UINT uiFlags = GHND)
	{
		COM_TRY {
		CGlobalMem Mem(dwSize, uiFlags);

			m_Mem.Attach(Mem.Detach());
			m_UnkForRelease = pIUnkForRelease;

		} COM_CATCH;
		return S_OK;
	}

private:
	CGlobalMem m_Mem;
	WUnknown m_UnkForRelease;
};

#endif // !defined(_MANAGEGLOBALMEMORY_H__79112A16_B5AF_4CA6_A5FE_788F69B316C7__INCLUDED_)
