// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.12.2000 16:52:17 
//
// @doc
// @module UnitsOfMeasurePP.h | Declaration of the <c CUnitsOfMeasurePP> class

#if !defined(_UNITSOFMEASUREPP_H__E86E5021_7523_44AD_B909_D53E2EC4F138__INCLUDED_)
#define _UNITSOFMEASUREPP_H__E86E5021_7523_44AD_B909_D53E2EC4F138__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "PropPageExt.h"
#include "UnitsOfMeasureDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasurePP
class ATL_NO_VTABLE CUnitsOfMeasurePP : 
	public CPropPageExt<CUnitsOfMeasureDlg>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnitsOfMeasurePP, &CLSID_UnitsOfMeasurePP>
{
public:
	CUnitsOfMeasurePP()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_UNITSOFMEASUREPP)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CUnitsOfMeasurePP)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()
};

#endif // !defined(_UNITSOFMEASUREPP_H__E86E5021_7523_44AD_B909_D53E2EC4F138__INCLUDED_)
