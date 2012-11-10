// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/13/1998 08:19:06 PM
//
// @doc
// @module CSLineGeom.h | Wrapper für LinienGeometrie

#if !defined(_CSLINEGEOM_H__80B9A2F3_02B0_11D2_8650_00600875138A__INCLUDED_)
#define _CSLINEGEOM_H__80B9A2F3_02B0_11D2_8650_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// type libraries
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
DefineSmartInterface2(_DGMPoints, IID__DGMPoints);	// W_DGMPoints
DefineSmartInterface2(_DGMPolylineGeometry, IID__DGMPolylineGeometry);	// W_DGMPolylineGeometry

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSPolylineGeometry> CLineFactory;
extern CLineFactory MakeLineGs;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSLineGeometry
{
private:
	W_DGMPolylineGeometry m_line;

public:
	CCSLineGeometry()
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_line (CLSID_TRiASCSPolylineGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeLineGs.CreateInstance (m_line.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_line);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSLineGeometry(long lCnt, double *pdX, double *pdY)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_line (CLSID_TRiASCSPolylineGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeLineGs.CreateInstance (m_line.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_line);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();

	W_DGMPoints pts;

		THROW_FAILED_HRESULT(m_line -> get_Points (pts.ppi()));
		for (long i = 0; i < lCnt; ++i) 
			THROW_FAILED_HRESULT(pts -> Add (CCSPoint(pdX[i], pdY[i]), vtMissing));
	}
	CCSLineGeometry (IDispatch *pRG)
		: m_line (pRG)
	{
	}
	CCSLineGeometry (_DGMPolylineGeometry *pRG)
		: m_line (pRG)
	{
	}
	~CCSLineGeometry () {}

// Zugriffsoperatoren
	_DGMPolylineGeometry *operator ->() const { return m_line; }
	operator _DGMPolylineGeometry *() const { return m_line; }
	_DGMPolylineGeometry *detach() { return m_line.detach(); }

	bool operator! () { return !m_line; }
	bool IsValid() { return m_line.IsValid(); }
};

#endif // !defined(_CSLINEGEOM_H__80B9A2F3_02B0_11D2_8650_00600875138A__INCLUDED_)
