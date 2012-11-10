// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 09.09.2002 19:27:34 
//
// @doc
// @module EnumCoordSystemNames.h | Declaration of the <c CEnumCoordSystemNames> class

#if !defined(_ENUMCOORDSYSTEMNAMES_H__7BCEC6D2_C92A_4545_B134_59C6A9EC2D12__INCLUDED_)
#define _ENUMCOORDSYSTEMNAMES_H__7BCEC6D2_C92A_4545_B134_59C6A9EC2D12__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Atl/CollTempl.h>

// FCD2CD94-AEFB-4E9E-A97E-59C16D4502F7
EXTERN_C const GUID __declspec(selectany) CLSID_EnumCoordSystemNames = 
	{ 0xFCD2CD94, 0xAEFB, 0x4E9E, 0xA9, 0x7E, 0x59, 0xC1, 0x6D, 0x45, 0x02, 0xF7 };

/////////////////////////////////////////////////////////////////////////////
// CEnumCoordSystemNames
class ATL_NO_VTABLE CEnumCoordSystemNames : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEnumCoordSystemNames, &CLSID_EnumCoordSystemNames>,
	public IStaticCollectionImpl<CComBSTR, &LIBID_TRIASCS, 
		TYPELIB_TRIASCS_VERSION_MAJOR, TYPELIB_TRIASCS_VERSION_MINOR, 
		IEnumCoordSystemNames, &IID_IEnumCoordSystemNames>
{
public:
	CEnumCoordSystemNames()
	{
	}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CEnumCoordSystemNames)
	
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CEnumCoordSystemNames)
		COM_INTERFACE_ENTRY(IEnumCoordSystemNames)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

// IEnumCoordSystemnames
public:

protected:
	BOOL __stdcall EnumResNameProc(HMODULE hModule,
		LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam);
};

#endif // !defined(_ENUMCOORDSYSTEMNAMES_H__7BCEC6D2_C92A_4545_B134_59C6A9EC2D12__INCLUDED_)
