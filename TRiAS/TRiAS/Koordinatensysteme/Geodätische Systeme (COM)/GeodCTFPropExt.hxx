///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GeodCTFPropExt.h | Deklaration of the <c CGeodCTFPropExt> class

#if !defined(_GEODCTFPROPEXT_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_)
#define _GEODCTFPROPEXT_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"		   // main symbols

#include "Strings.h"
#include "CTFPropSheetExt.h"
#include "CTFParams.h"			// PropertyPage
#include "AtlSingletonCF.h"		// SingletonClassFactory

/////////////////////////////////////////////////////////////////////////////
// COpenWizPropExt
class ATL_NO_VTABLE CGeodCTFPropExt : 
	public CTRiASPropSheetExt<CCTFParams>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGeodCTFPropExt, &CLSID_GeodCTFPropExt>
{
public:
	CGeodCTFPropExt()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_OPENWIZPROPEXT)
	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CGeodCTFPropExt>)

	BEGIN_COM_MAP(CGeodCTFPropExt)
		COM_INTERFACE_ENTRY2(IUnknown, ITriasPropSheetExt)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASPropSheetExt<CCTFParams>)
	END_COM_MAP()

	void FinalRelease()
	{
		CComSingletonFactory<CGeodCTFPropExt>::ResetInstance();
	}

public:
};

#endif // !defined(_GEODCTFPROPEXT_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_)
