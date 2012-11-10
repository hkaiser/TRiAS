// @doc
// @module CSPoint.h | Wrapper für _DGMPoint

#if !defined(_CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_)
#define _CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable: 4192)	// automatically excluding 'bla' while importing type library 'bla'

#if !defined(_CSPOINT_ALREADY_PRESENT_)
///////////////////////////////////////////////////////////////////////////////
// Import benötigter Definitionen
#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/GMObjects.h>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#import "tlb/TDBGeo.tlb"	\
	named_guids				\
	raw_interfaces_only		\
	raw_dispinterfaces		\
	no_namespace			\
	exclude("IPersist", "IPersistMemory")
DefineSmartInterface2(_DGMPoint, IID__DGMPoint);	// W_DGMPoint
#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__
#endif

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSPoint> CPointFactory;
extern CPointFactory MakePts;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSPoint 
{
private:
	W_DGMPoint m_pt;

public:
	CCSPoint ()
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_pt(CLSID_TRiASCSPoint)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakePts.CreateInstance (m_pt.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_pt);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSPoint (double dX, double dY, double dZ = 0.0)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_pt (CLSID_TRiASCSPoint)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakePts.CreateInstance (m_pt.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_pt);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();

	double Coords[3] = { dX, dY, dZ };

		m_pt -> SetPoint(Coords);
	}
	CCSPoint (IDispatch *pPt)
		: m_pt(pPt)
	{
	}
	CCSPoint (_DGMPoint *pPt)
		: m_pt(pPt)
	{
	}
	~CCSPoint () {}

// Zugriffsoperatoren
	_DGMPoint *operator &() const { return m_pt; }
	_DGMPoint *operator ->() const { return m_pt; }
	operator _DGMPoint *() const { return m_pt; }
	_DGMPoint *detach() { return m_pt.detach(); }
};

#endif // !defined(_CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_)
