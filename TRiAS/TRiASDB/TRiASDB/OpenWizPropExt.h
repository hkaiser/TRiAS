// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.02.2002 08:00:28 
//
// @doc
// @module OpenWizPropExt.h | Declaration of the <c COpenWizPropExt> class

#if !defined(_OPENWIZPROPEXT_H__C9782AA8_01E3_41A5_B162_5D531B562B45__INCLUDED_)
#define _OPENWIZPROPEXT_H__C9782AA8_01E3_41A5_B162_5D531B562B45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/AtlSingletonCF.h>		// SingletonClassFactory

#include "resource.h"				// main symbols

#include "Strings.h"
#include "PropSheetExt.h"
#include "CreateNewParamWiz.h"

/////////////////////////////////////////////////////////////////////////////
// COpenWizPropExt
class ATL_NO_VTABLE COpenWizPropExt : 
	public CTRiASPropSheetExt<CCreateNewParamWiz>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<COpenWizPropExt, &CLSID_OpenWizPropExt>
{
public:
	COpenWizPropExt()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_OPENWIZPROPEXT)
	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<COpenWizPropExt>)

	BEGIN_COM_MAP(COpenWizPropExt)
		COM_INTERFACE_ENTRY2(IUnknown, ITRiASOpenWizardPropExt)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASPropSheetExt<CCreateNewParamWiz>)
	END_COM_MAP()

	void FinalRelease()
	{
		CComSingletonFactory<COpenWizPropExt>::ResetInstance();
	}

public:
};

#endif // !defined(_OPENWIZPROPEXT_H__C9782AA8_01E3_41A5_B162_5D531B562B45__INCLUDED_)
