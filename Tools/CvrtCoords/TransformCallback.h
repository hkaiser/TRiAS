// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 13:48:45 
//
// @doc
// @module TransformCallback.h | Declaration of the <c CTransformCallback> class

#if !defined(_TRANSFORMCALLBACK_H__ED09041C_E305_4567_90EF_B3B53D5FB635__INCLUDED_)
#define _TRANSFORMCALLBACK_H__ED09041C_E305_4567_90EF_B3B53D5FB635__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransformCallback
class CCvrtCoordsApp;		// forward decl only

class ATL_NO_VTABLE CTransformCallback : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTransformCallback, &CLSID_TransformCallback>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITransformLineOfTextCallback, &IID_ITransformLineOfTextCallback, 
		&LIBID_CvrtCoords>
{
public:
	CTransformCallback() :
		m_pParent(NULL)
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTransformCallback)
		COM_INTERFACE_ENTRY(ITransformLineOfTextCallback)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	void SetParent(CCvrtCoordsApp *pParent) 
	{
		m_pParent = pParent;
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITransformLineOfTextCallback
public:
	STDMETHOD(TransformCoords)(/*[in, out]*/ double *pdX, /*[in, out]*/ double *pdY);

private:
	CCvrtCoordsApp *m_pParent;
};

#endif // !defined(_TRANSFORMCALLBACK_H__ED09041C_E305_4567_90EF_B3B53D5FB635__INCLUDED_)
