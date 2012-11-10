// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 11:42:48 PM
//
// @doc
// @module CSBoundaryGeom.h | Wrapper für eine Flächengeometrie

#if !defined(_CSBOUNDARYGEOM_H__CBC5D025_03AF_11D2_8651_00600875138A__INCLUDED_)
#define _CSBOUNDARYGEOM_H__CBC5D025_03AF_11D2_8651_00600875138A__INCLUDED_

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
DefineSmartInterface2(_DGMGeometry, IID__DGMGeometry);	// W_DGMGeometry
DefineSmartInterface2(_DGMPolylineGeometry, IID__DGMPolylineGeometry);	// W_DGMPolylineGeometry
DefineSmartInterface2(_DGMPolygonGeometry, IID__DGMPolygonGeometry);	// W_DGMPolygonGeometry
DefineSmartInterface2(_DGMBoundaryGeometry, IID__DGMBoundaryGeometry);	// W_DGMBoundaryGeometry

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSBoundaryGeometry> CBoundaryFactory;
typedef CClassFactoryCache<&CLSID_TRiASCSPolygonGeometry> CPolygonFactory;
extern CBoundaryFactory MakeBound;
extern CPolygonFactory MakePolygon;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSBoundaryGeometry
{
private:
	bool m_fIsBoundary;
	W_DGMGeometry m_area;

public:
	CCSBoundaryGeometry(bool fIsBoundary = false)
		: m_fIsBoundary(fIsBoundary)
#if !defined(_USE_CLASSFACTORY_CACHE)
		, m_area (fIsBoundary ? CLSID_TRiASCSBoundaryGeometry : CLSID_TRiASCSPolygonGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
	if (fIsBoundary) {
			THROW_FAILED_HRESULT(MakeBound.CreateInstance (m_area.ppi()));
		} else {
			THROW_FAILED_HRESULT(MakePolygon.CreateInstance (m_area.ppi()));
		}
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_area);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSBoundaryGeometry(long lCnt, KoOrd *pdX, KoOrd *pdY, bool fIsBoundary = false)
		: m_fIsBoundary(fIsBoundary)
#if !defined(_USE_CLASSFACTORY_CACHE)
		, m_area (fIsBoundary ? CLSID_TRiASCSBoundaryGeometry : CLSID_TRiASCSPolygonGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		if (fIsBoundary) {
			THROW_FAILED_HRESULT(MakeBound.CreateInstance (m_area.ppi()));
		} else {
			THROW_FAILED_HRESULT(MakePolygon.CreateInstance (m_area.ppi()));
		}
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_area);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();

	W_DGMPoints pts;

		if (!fIsBoundary) {
			THROW_FAILED_HRESULT(W_DGMPolylineGeometry(m_area) -> get_Points (pts.ppi()));
		} else {
		__Interface<IDispatch> ext;

			THROW_FAILED_HRESULT(W_DGMBoundaryGeometry(m_area) -> get_Exterior(ext.ppi()));
			THROW_FAILED_HRESULT(W_DGMPolylineGeometry(ext) -> get_Points (pts.ppi()));
		}
		for (long i = 0; i < lCnt; ++i) 
			THROW_FAILED_HRESULT(pts -> Add (CCSPoint(pdX[i], pdY[i]), vtMissing /*CComVariant(i+1)*/));
	}
	CCSBoundaryGeometry (IDispatch *pRG, bool fIsBoundary = false)
		: m_area (pRG), m_fIsBoundary(fIsBoundary)
	{
	}
	CCSBoundaryGeometry (_DGMGeometry *pRG, bool fIsBoundary = false)
		: m_area (pRG), m_fIsBoundary(fIsBoundary)
	{
	}
	~CCSBoundaryGeometry () {}

// Zugriffsoperatoren
	_DGMGeometry *operator ->() const { return m_area; }
	operator _DGMGeometry *() const { return m_area; }
	_DGMGeometry *detach() { return m_area.detach(); }

	CCSBoundaryGeometry &operator= (const CCSBoundaryGeometry &rhs)
	{
		if (&rhs != this) {
			m_fIsBoundary = rhs.m_fIsBoundary;
			m_area = rhs.m_area;
		}
		return *this;
	}

	bool operator! () { return !m_area; }
	bool IsValid() { return m_area.IsValid(); }
	bool IsBoundary() { return m_fIsBoundary; }
};

#endif // !defined(_CSBOUNDARYGEOM_H__CBC5D025_03AF_11D2_8651_00600875138A__INCLUDED_)
