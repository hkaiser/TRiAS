// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 20.04.2002 19:53:53 
//
// @doc
// @module ExecuteCmdAs.cpp | Definition of the <c CExecuteCmdAs> class

#include "stdafx.h"
#include "RunCmdAs.h"
#include "ExecuteCmdAs.h"

extern "C" {
	#include "DownHill.H"
}

/////////////////////////////////////////////////////////////////////////////
// CExecuteCmdAs

STDMETHODIMP CExecuteCmdAs::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExecuteCmdAs
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CExecuteCmdAs::ExecuteCmd(BSTR bstrCmd, BSTR bstrCommandLine, int *piRetVal)
{
	if (NULL == piRetVal)
		return E_POINTER;
	*piRetVal = 0;

	USES_CONVERSION;

CComBSTR bstrCommand (bstrCmd);

	bstrCommand.Append(L" ");
	bstrCommand.AppendBSTR(bstrCommandLine);

int iRet = 0;
char *pTempFile = Downhill_Process_System2(OLE2A(bstrCommand), &iRet, TRUE);

	if (NULL != pTempFile)
		unlink (pTempFile);
	*piRetVal = iRet;
	return S_OK;
}
