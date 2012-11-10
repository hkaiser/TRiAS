// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.11.1999 23:12:43 
//
// @doc
// @module TemplateWizPropExt.h | Declaration of the <c CTemplateWizPropExt> class

#if !defined(_TEMPLATEWIZPROPEXT_H__6960A6A2_1B68_443A_AB35_6F1254823AEE__INCLUDED_)
#define _TEMPLATEWIZPROPEXT_H__6960A6A2_1B68_443A_AB35_6F1254823AEE__INCLUDED_

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
#include "CreateNewTemplateWiz.h"

/////////////////////////////////////////////////////////////////////////////
// CTemplateWizPropExt
class ATL_NO_VTABLE CTemplateWizPropExt : 
	public CTRiASPropSheetExt<CCreateNewTemplateWiz>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTemplateWizPropExt, &CLSID_TemplateWizPropExt>
{
public:
	CTemplateWizPropExt()
	{
	}

	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CTemplateWizPropExt>)

	BEGIN_COM_MAP(CTemplateWizPropExt)
		COM_INTERFACE_ENTRY2(IUnknown, ITRiASOpenWizardPropExt)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASPropSheetExt<CCreateNewParamWiz>)
	END_COM_MAP()

	void FinalRelease()
	{
		CComSingletonFactory<CTemplateWizPropExt>::ResetInstance();
	}

public:
};

#endif // !defined(_TEMPLATEWIZPROPEXT_H__6960A6A2_1B68_443A_AB35_6F1254823AEE__INCLUDED_)
