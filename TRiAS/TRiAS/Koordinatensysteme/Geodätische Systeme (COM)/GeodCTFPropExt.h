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

/////////////////////////////////////////////////////////////////////////////
// CGeodCTFPropExt
class CCTFParams;

template<class T>
class ATL_NO_VTABLE CGeodCTFPropExt : 
	public CCTFPropSheetExt<CGeodCTFPropExt<T>, CCTFParams>,
	public CComTearOffObjectBase<T, CComObjectThreadModel>
{
public:
	CGeodCTFPropExt()
	{
	}

	BEGIN_COM_MAP(CGeodCTFPropExt)
		COM_INTERFACE_ENTRY_EX(ITriasPropSheetExt)
	END_COM_MAP()
};

#endif // !defined(_GEODCTFPROPEXT_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_)
