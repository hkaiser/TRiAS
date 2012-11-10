// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.10.2002 21:02:27 
//
// @doc
// @module CreateOpenWizPropExt.h | Declaration of the <c CCreateOpenWizPropExt> class

#if !defined(_CREATEOPENWIZPROPEXT_H__1976A121_6685_4188_8AC8_F94E780637EF__INCLUDED_)
#define _CREATEOPENWIZPROPEXT_H__1976A121_6685_4188_8AC8_F94E780637EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Obwohl die Datei so heißt, als ob sie für alles möglichen zuständig wäre,
// werden hier lediglich die zusätzliche Dialoge für den SQL-Server definiert.
// Als mir das klar wurde, war es schon zu spät um noch was daran zu ändern :-)

#include <Atl/AtlSingletonCF.h>		// SingletonClassFactory

#include "resource.h"				// main symbols

#include "Strings.h"
#include "PropSheetExt2.h"
#include "PpgSQLServer.h"
#include "PpgSQLServerOpenNew.h"

/////////////////////////////////////////////////////////////////////////////
// COpenWizPropExt
class ATL_NO_VTABLE CCreateOpenWizPropExt : 
	public CTRiASPropSheetExt2<CPpgSQLServer, CPpgSQLServerOpenNew>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CCreateOpenWizPropExt, &CLSID_CreateOpenWizPropExt>
{
public:
	CCreateOpenWizPropExt()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CREATEOPENWIZPROPEXT)
	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CCreateOpenWizPropExt>)

	typedef CTRiASPropSheetExt2<CPpgSQLServer, CPpgSQLServerOpenNew> base_t;
	BEGIN_COM_MAP(CCreateOpenWizPropExt)
		COM_INTERFACE_ENTRY2(IUnknown, ITRiASOpenWizardPropExt)
		COM_INTERFACE_ENTRY_CHAIN(base_t)
	END_COM_MAP()

	void FinalRelease()
	{
		CComSingletonFactory<CCreateOpenWizPropExt>::ResetInstance();
	}

public:
};

#endif // !defined(_CREATEOPENWIZPROPEXT_H__1976A121_6685_4188_8AC8_F94E780637EF__INCLUDED_)
