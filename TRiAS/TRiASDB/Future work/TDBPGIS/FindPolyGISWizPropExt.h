// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.02.2002 08:03:56 
//
// @doc
// @module FindPolyGISWizPropExt.h | Declaration of the <c CFindPolyGISWizPropExt> class

#if !defined(_FINDPOLYGISWIZPROPEXT_H__64C7FC8E_72F8_4854_A1E1_16A026507835__INCLUDED_)
#define _FINDPOLYGISWIZPROPEXT_H__64C7FC8E_72F8_4854_A1E1_16A026507835__INCLUDED_

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
#include "FindPolyGISWiz.h"

/////////////////////////////////////////////////////////////////////////////
// CFindPolyGISWizPropExt
class ATL_NO_VTABLE CFindPolyGISWizPropExt : 
	public CTRiASPropSheetExt<CFindPolyGISWiz>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CFindPolyGISWizPropExt, &CLSID_FindPolyGISWizPropExt>
{
public:
	CFindPolyGISWizPropExt()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_FINDPOLYGISPROPEXT)
	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CFindPolyGISWizPropExt>)

	BEGIN_COM_MAP(CFindPolyGISWizPropExt)
		COM_INTERFACE_ENTRY2(IUnknown, ITRiASOpenWizardPropExt)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASPropSheetExt<CFindPolyGISWiz>)
	END_COM_MAP()

	void FinalRelease()
	{
		CComSingletonFactory<CFindPolyGISWizPropExt>::ResetInstance();
	}

public:
};

#endif // !defined(_FINDPOLYGISWIZPROPEXT_H__64C7FC8E_72F8_4854_A1E1_16A026507835__INCLUDED_)
