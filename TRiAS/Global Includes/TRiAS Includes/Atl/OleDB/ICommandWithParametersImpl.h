// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.05.2001 20:01:25 
//
// @doc
// @module ICommandWithParametersImpl.h | Declaration of the <c ICommandWithParametersImpl> class

#if !defined(_ICOMMANDWITHPARAMETERSIMPL_H__759A3F4C_0014_4ABE_8776_4086FD2E3555__INCLUDED_)
#define _ICOMMANDWITHPARAMETERSIMPL_H__759A3F4C_0014_4ABE_8776_4086FD2E3555__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include <atlcom.h>
#include <atldb.h>

///////////////////////////////////////////////////////////////////////////
// class ICommandWithPamametersImpl

template <class T>
class ATL_NO_VTABLE ICommandWithPamametersImpl : 
	public ICommandWithParameters
{
public:
	STDMETHOD(GetParameterInfo)(ULONG *pcParams, DBPARAMINFO **prgParamInfo, OLECHAR **ppNamesBuffer)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ICommandWithPamameterImpl::GetParametersInfo\n");
		
	HRESULT hr = E_FAIL;

		if (!pcParams || !prgParamInfo || !ppNamesBuffer) {
			ATLTRACE2(atlTraceDBProvider, 0, "ICommandWithPamameterImpl::GetParametersInfo: - Error - a pointer is null\n");
			return E_POINTER;
		}

	// The way that we use the command parameters means that this never gets called...
	T *pT = 0;

		*pcParams = 0;
		return DB_E_PARAMUNAVAILABLE;
	}
	
	STDMETHOD(MapParameterNames)(ULONG cParamNames, const OLECHAR *rgParamnNames[], LONG rgParamOrdinals[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ICommandWithPamametersImpl::MapParameterNames\n");
		if (0 == cParamNames)
			return S_OK;

	// The way that we use the command parameters means that this never gets called...
		return E_FAIL;
	}

	STDMETHOD(SetParameterInfo)(ULONG cParams, const ULONG rgParamOrdinals[], const DBPARAMBINDINFO rgParamBindInfo[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ICommandWithPamametersImpl::SetParameterInfo\n");
		if (0 == cParams)
			return S_OK;

	// We should really check to see that:
	// cParams is 1, 
	// rgParamOrdinals[0] is 1
	// rgParamBindInfo[0]->dwFlags is DBPARAMFLAGS_ISINPUT
	// rgParamBindInfo[0]->pwszDataSourceType is "DBTYPE_IUNKNOWN"
		return S_OK;
	}
};

#endif // !defined(_ICOMMANDWITHPARAMETERSIMPL_H__759A3F4C_0014_4ABE_8776_4086FD2E3555__INCLUDED_)
