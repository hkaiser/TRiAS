// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 07.02.2003 11:21:00 
//
// @doc
// @module ManageObjectProperties.h | Declaration of the <c CManageObjectProperties> class

// ManageObjectProperties.h : Declaration of the CManageObjectProperties

#if !defined(_MANAGEOBJECTPROPERTIES_H__B43A803B_5B86_4459_B15B_5818A4FED6E5__INCLUDED_)
#define _MANAGEOBJECTPROPERTIES_H__B43A803B_5B86_4459_B15B_5818A4FED6E5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"					// main symbols
#include "TRiASOptionsPropPage.h"
#include "ManageObjectPropertiesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CManageObjectProperties
class ATL_NO_VTABLE CManageObjectProperties : 
	public COptionsPropPage<CManageObjectPropertiesDlg>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CManageObjectProperties, &CLSID_ManageObjectProperties>
{
public:
	CManageObjectProperties()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MANAGEOBJECTPROPERTIES)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CManageObjectProperties)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()
};

#endif // !defined(_MANAGEOBJECTPROPERTIES_H__B43A803B_5B86_4459_B15B_5818A4FED6E5__INCLUDED_)
