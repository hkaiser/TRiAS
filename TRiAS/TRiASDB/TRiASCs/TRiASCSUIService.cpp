// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.10.2000 19:31:35 
//
// @doc
// @module TRiASCSUIService.cpp | Definition of the <c CTRiASCSUIService> class

#include "stdafx.h"

#include <Atl/Ciid.h>

#include "TRiASCs.h"
#include "TRiASCSUIService.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSUIHelper);

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSUIService
STDMETHODIMP CTRiASCSUIService::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASCSUIService
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// Implementation of get_InputMask
STDMETHODIMP CTRiASCSUIService::get_InputMask(ITRiASCS *pCoordSys, COORDELEMENT rgElement, BSTR *pbstrUIMask)
{
	ATLTRACE(_T("CTRiASCSUIService::get_InputMask\n"));
	CHECKINPOINTER(pCoordSys);
	CHECKOUTPOINTER(pbstrUIMask);

WTRiASCSUIHelper UIHelper;

	if (SUCCEEDED(pCoordSys -> QueryInterface(UIHelper.ppi()))) 
		return UIHelper -> get_InputMask (rgElement, pbstrUIMask);
	return E_NOINTERFACE;
}

// Implementation of get_InputMaskControl
STDMETHODIMP CTRiASCSUIService::get_InputMaskControl(BSTR *pbstrUIGuid)
{
	ATLTRACE(_T("CTRiASCSUIService::get_InputMaskControl\n"));

CIID Guid ("MSMask.MaskEdBox", CIID::INITCIID_InitFromProgId);
CComBSTR bstrGuid (Guid);

	*pbstrUIGuid = bstrGuid.Detach();
	return S_OK;
}

// Implementation of get_Precision
STDMETHODIMP CTRiASCSUIService::get_Precision(ITRiASCS *pCoordSys, long *plPrec)
{
	ATLTRACE(_T("CTRiASCSUIService::get_Precision\n"));
	CHECKINPOINTER(pCoordSys);
	CHECKOUTPOINTER(plPrec);
	
WTRiASCSUIHelper UIHelper;

	if (SUCCEEDED(pCoordSys -> QueryInterface(UIHelper.ppi()))) 
		return UIHelper -> get_Precision (plPrec);
	return E_NOINTERFACE;
}

// Implementation of put_Precision
STDMETHODIMP CTRiASCSUIService::put_Precision(ITRiASCS *pCoordSys, long lPrec)
{
	ATLTRACE(_T("CTRiASCSUIService::put_Precision\n"));
	CHECKINPOINTER(pCoordSys);

WTRiASCSUIHelper UIHelper;

	if (SUCCEEDED(pCoordSys -> QueryInterface(UIHelper.ppi()))) 
		return UIHelper -> put_Precision (lPrec);
	return E_NOINTERFACE;
}

// Implementation of Format
STDMETHODIMP CTRiASCSUIService::Format(
	ITRiASCS *pCoordSys, COORDELEMENT rgElement, double dValue, BSTR *bstrFormattedElement)
{
	ATLTRACE(_T("CTRiASCSUIService::Format\n"));
	CHECKINPOINTER(pCoordSys);
	CHECKOUTPOINTER(bstrFormattedElement);

WTRiASCSUIHelper UIHelper;

	if (SUCCEEDED(pCoordSys -> QueryInterface(UIHelper.ppi()))) 
		return UIHelper -> Format (rgElement, dValue, bstrFormattedElement);
	return E_NOINTERFACE;
}

// Implementation of Convert
STDMETHODIMP CTRiASCSUIService::Convert(
	ITRiASCS *pCoordSys, COORDELEMENT rgElement, BSTR bstrFormatted, double *pdValue)
{
	ATLTRACE(_T("CTRiASCSUIService::Convert\n"));
	CHECKINPOINTER(pCoordSys);
	CHECKINPOINTER(bstrFormatted);
	CHECKOUTPOINTER(pdValue);
	
WTRiASCSUIHelper UIHelper;

	if (SUCCEEDED(pCoordSys -> QueryInterface(UIHelper.ppi()))) 
		return UIHelper -> Convert (rgElement, bstrFormatted, pdValue);
	return E_NOINTERFACE;
}

