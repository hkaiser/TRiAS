///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GKPropExt.h | Deklaration of the <c CGKPropExt> class

#if !defined(_GKPropExt_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_)
#define _GKPropExt_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"		   // main symbols

#include "Strings.h"
#include "CTFPropSheetExt.h"
#include "CTFParams.h"			// PropertyPage

/////////////////////////////////////////////////////////////////////////////
// CGKPropExt
class CCTFParams;

template<class T>
class ATL_NO_VTABLE CGKPropExt : 
	public CCTFPropSheetExt<CGKPropExt<T>, CCTFParams>,
	public CComTearOffObjectBase<T, CComObjectThreadModel>
{
public:
	CGKPropExt()
	{
	}

	BEGIN_COM_MAP(CGKPropExt)
		COM_INTERFACE_ENTRY_EX(ITriasPropSheetExt)
	END_COM_MAP()
};

#endif // !defined(_GKPropExt_H__D5FB8134_DF7F_11D1_8607_00600875138A__INCLUDED_)
