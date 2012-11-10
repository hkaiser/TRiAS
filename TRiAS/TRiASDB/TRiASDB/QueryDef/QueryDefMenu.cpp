// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 11:42:11
//
// @doc
// @module QueryDefMenu.cpp | Implementation of the <c CQueryDefMenu> class

#include "StdAfx.h"

#include "Strings.h"
#include "QueryDef.h"
#include "QueryDefExt.h"

#include <Com/PersistPropertyAction.cpp>
#include <selobwnd.h>
#include <AddAsClsPrp.h>
#include <DelFromClsPrp.h>
#include <DstObWnd.h>
#include <triashelper.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertySequenceService);
DefineSmartInterface(ProgressIndicator);
DefineSmartInterface(ProgressIndicator2);

///////////////////////////////////////////////////////////////////////////////
// MenuPunkte behandeln
HRESULT CQueryDefExtension::MakeObjectClass (HWND hWnd)
{
	COM_TRY {
	WPropertySequenceService Service (CLSID_PropertySequenceService);
	CComBSTR bstrRsc("AddObjectsToClassORWnd.xml");
	CComBSTR bstrCap;
	
		bstrCap.LoadString(IDS_MAKEOBJCLASS_CAPTION);
		_ASSERTE(bstrCap.Length() > 0);

	WProgressIndicator ProgInd (CLSID_ProgressIndicator);

		ProgInd -> InitNew (hWnd, PIFLAGS_RESULT);
		THROW_FAILED_HRESULT(Service -> RunActionSequence (INT_PTR(hWnd), bstrRsc, bstrCap, bstrCap, WProgressIndicator2(ProgInd), NULL, VARIANT_FALSE, NULL));

	} COM_CATCH;
	return S_OK;
}

HRESULT CQueryDefExtension::DeleteFromClass (HWND hWnd)
{
	COM_TRY {
	WPropertySequenceService Service (CLSID_PropertySequenceService);
	CComBSTR bstrRsc("DeleteObjectsFromClassORWnd.xml");
	CComBSTR bstrCap;
	
		bstrCap.LoadString(IDS_DELETEOBJCLASS_CAPTION);
		_ASSERTE(bstrCap.Length() > 0);

	WProgressIndicator ProgInd (CLSID_ProgressIndicator);

		ProgInd -> InitNew (hWnd, PIFLAGS_RESULT);
		THROW_FAILED_HRESULT(Service -> RunActionSequence (INT_PTR(hWnd), bstrRsc, bstrCap, bstrCap, WProgressIndicator2(ProgInd), NULL, VARIANT_FALSE, NULL));

	} COM_CATCH;
	return S_OK;
}

