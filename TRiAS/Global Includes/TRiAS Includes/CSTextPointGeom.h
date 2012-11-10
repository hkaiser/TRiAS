// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/13/1998 02:50:16 PM
//
// @doc
// @module CSTextPointGeom.h | Wrapper für TextPointGeometry

#if !defined(_CSTEXTPOINTGEOM_H__554A4D14_1A1E_11D2_9E91_006008447800__INCLUDED_)
#define _CSTEXTPOINTGEOM_H__554A4D14_1A1E_11D2_9E91_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#if !defined(___DGMPoint_FWD_DEFINED__)
#define ___DGMPoint_FWD_DEFINED__
#define ___DGMPoints_FWD_DEFINED__
#endif // ___DGMPoint_FWD_DEFINED__
#if !defined(___DGMPoint_INTERFACE_DEFINED__)
#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__
#endif // ___DGMPoint_INTERFACE_DEFINED__
#include <ictf.h>
#include <CSPoint.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(_DGMTextPointGeometry, IID__DGMTextPointGeometry);	// W_DGMTextPointGeometry

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSTextPointGeometry> CTextFactory;
extern CTextFactory MakeTexts;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSTextPointGeometry
{
private:
	W_DGMTextPointGeometry m_text;

public:
	CCSTextPointGeometry()
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_text (CLSID_TRiASCSTextPointGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeTexts.CreateInstance (m_text.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_text);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSTextPointGeometry (double dX, double dY, LPCSTR pcText = NULL)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_text (CLSID_TRiASCSTextPointGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeTexts.CreateInstance (m_text.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_text);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();

	W_DGMPoint pt;

		if (SUCCEEDED(m_text -> get_Origin (pt.ppi()))) {
			pt -> put_X (dX);
			pt -> put_Y (dY);
		}
		if (NULL != pcText) 
			m_text -> put_text (CComBSTR(pcText));
	}
	CCSTextPointGeometry (IDispatch *pPG)
		: m_text (pPG)
	{
	}
	CCSTextPointGeometry (_DGMTextPointGeometry *pPG)
		: m_text (pPG)
	{
	}
	~CCSTextPointGeometry () {}

// Helperfunktionen für Zugriff auf Origin
	HRESULT get_X (double *pdX) const
	{
	W_DGMPoint pt;

		if (SUCCEEDED(const_cast<W_DGMTextPointGeometry &>(m_text) -> get_Origin (pt.ppi())))
			return pt -> get_X (pdX);
		return E_UNEXPECTED;
	}
	HRESULT put_X (double dX) 
	{
	W_DGMPoint pt;

		if (SUCCEEDED(m_text -> get_Origin (pt.ppi())))
			return pt -> put_X (dX);
		return E_UNEXPECTED;
	}

	HRESULT get_Y (double *pdY) const
	{
	W_DGMPoint pt;

		if (SUCCEEDED(const_cast<W_DGMTextPointGeometry &>(m_text) -> get_Origin (pt.ppi())))
			return pt -> get_Y (pdY);
		return E_UNEXPECTED;
	}
	HRESULT put_Y (double dY) 
	{
	W_DGMPoint pt;

		if (SUCCEEDED(m_text -> get_Origin (pt.ppi())))
			return pt -> put_Y (dY);
		return E_UNEXPECTED;
	}

	HRESULT get_Text (BSTR *pbstrText)
	{
		return m_text -> get_text (pbstrText);
	}
	HRESULT put_Text (BSTR bstrText)
	{
		return m_text -> put_text (bstrText);
	}

// Zugriffsoperatoren
	_DGMTextPointGeometry *operator ->() const { return m_text; }
	operator _DGMPointGeometry *() const { return (_DGMTextPointGeometry *)m_text; }
	operator _DGMTextPointGeometry *() const { return m_text; }
	_DGMTextPointGeometry *detach() { return m_text.detach(); }

	bool operator! () { return !m_text; }
	bool IsValid() { return m_text.IsValid(); }
};

#endif // !defined(_CSTEXTPOINTGEOM_H__554A4D14_1A1E_11D2_9E91_006008447800__INCLUDED_)
