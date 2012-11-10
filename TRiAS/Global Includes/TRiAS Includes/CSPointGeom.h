// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/11/1998 10:12:36 PM
//
// @doc
// @module CSPointGeom.h | Wrapperklasse für _DGMPointGeometry

#if !defined(_CSPOINTGEOM_H__BC145184_013F_11D2_864C_00600875138A__INCLUDED_)
#define _CSPOINTGEOM_H__BC145184_013F_11D2_864C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // !defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#if !defined(___DGMPoint_FWD_DEFINED__)
#define ___DGMPoint_FWD_DEFINED__
#define ___DGMPoints_FWD_DEFINED__
#endif // ___DGMPoint_FWD_DEFINED__
#if !defined(___DGMPoint_INTERFACE_DEFINED__)
#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__
#endif // ___DGMPoint_INTERFACE_DEFINED__
#include <ictf.h>
//#include <TDBGeo.h>
#include <CSPoint.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(_DGMPointGeometry, IID__DGMPointGeometry);	// W_DGMPointGeometry

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSPointGeometry> CPointGeomFactory;
extern CPointGeomFactory MakePtGs;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSPointGeometry
{
private:
	W_DGMPointGeometry m_pt;

public:
	CCSPointGeometry()
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_pt (CLSID_TRiASCSPointGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakePtGs.CreateInstance (m_pt.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_pt);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSPointGeometry (double dX, double dY, double dZ = 0.0)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_pt (CLSID_TRiASCSPointGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakePtGs.CreateInstance (m_pt.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_pt);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();

	W_DGMPoint pt;

		if (SUCCEEDED(m_pt -> get_Origin (pt.ppi()))) {
			pt -> put_X (dX);
			pt -> put_Y (dY);
			pt -> put_Z (dZ);
		}
	}
	CCSPointGeometry (IDispatch *pPG)
		: m_pt (pPG)
	{
	}
	CCSPointGeometry (_DGMPointGeometry *pPG)
		: m_pt (pPG)
	{
	}
	~CCSPointGeometry () {}

// Helperfunktionen für Zugriff auf Origin
	HRESULT get_X (double *pdX) const
	{
	W_DGMPoint pt;

		if (SUCCEEDED(const_cast<W_DGMPointGeometry &>(m_pt) -> get_Origin (pt.ppi())))
			return pt -> get_X (pdX);
		return E_UNEXPECTED;
	}
	HRESULT put_X (double dX) 
	{
	W_DGMPoint pt;

		if (SUCCEEDED(m_pt -> get_Origin (pt.ppi())))
			return pt -> put_X (dX);
		return E_UNEXPECTED;
	}

	HRESULT get_Y (double *pdY) const
	{
	W_DGMPoint pt;

		if (SUCCEEDED(const_cast<W_DGMPointGeometry &>(m_pt) -> get_Origin (pt.ppi())))
			return pt -> get_Y (pdY);
		return E_UNEXPECTED;
	}
	HRESULT put_Y (double dY) 
	{
	W_DGMPoint pt;

		if (SUCCEEDED(m_pt -> get_Origin (pt.ppi())))
			return pt -> put_Y (dY);
		return E_UNEXPECTED;
	}
	HRESULT get_Z (double *pdZ) const
	{
	W_DGMPoint pt;

		if (SUCCEEDED(const_cast<W_DGMPointGeometry &>(m_pt) -> get_Origin (pt.ppi())))
			return pt -> get_Z (pdZ);
		return E_UNEXPECTED;
	}
	HRESULT put_Z (double dZ) 
	{
	W_DGMPoint pt;

		if (SUCCEEDED(m_pt -> get_Origin (pt.ppi())))
			return pt -> put_Z (dZ);
		return E_UNEXPECTED;
	}

// Zugriffsoperatoren
	_DGMPointGeometry *operator ->() const { return m_pt; }
	operator _DGMPointGeometry *() const { return m_pt; }
	_DGMPointGeometry *detach() { return m_pt.detach(); }
	void Assign (IDispatch *pINew) { m_pt = pINew; }

	bool operator! () { return !m_pt; }
	bool IsValid() { return m_pt.IsValid(); }
};

#endif // !defined(_CSPOINTGEOM_H__BC145184_013F_11D2_864C_00600875138A__INCLUDED_)
