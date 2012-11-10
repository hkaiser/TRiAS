// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/27/1998 11:43:04 PM
//
// @doc
// @module PerfCounterDefinitions.cpp | Implementation of the <c CPerfCounterDefinitions> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfCounterDefinitions.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinitions

STDMETHODIMP CPerfCounterDefinitions::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfCounterDefinitions,
		&IID_IDynamicCollection,
		&IID_IStaticCollection,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

