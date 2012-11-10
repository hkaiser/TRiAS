// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/28/1998 11:57:45 PM
//
// @doc
// @module PerfCounters.cpp | Implementation of the <c CPerfCounters> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfCounters.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfCounters

STDMETHODIMP CPerfCounters::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfCounters,
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
