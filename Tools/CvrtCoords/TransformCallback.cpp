// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 13:48:21 
//
// @doc
// @module TransformCallback.cpp | Definition of the <c CTransformCallback> class

#include "stdafx.h"

#include "CvrtCoords.h"
#include "CvrtCoords_i.h"

#include "TransformCallback.h"
#include "CvrtCoordsApp.h "

/////////////////////////////////////////////////////////////////////////////
// CTransformCallback

STDMETHODIMP CTransformCallback::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransformLineOfTextCallback
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Koordinatenpaar tranmsformieren

STDMETHODIMP CTransformCallback::TransformCoords(double *pdX, double *pdY)
{
	if (NULL == pdX || NULL == pdY)
		return E_POINTER;

	RETURN_FAILED_HRESULT(m_pParent->TransformCoords(pdX, pdY));
	return S_OK;
}
