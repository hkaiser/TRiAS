///////////////////////////////////////////////////////////////////////////
// @doc
// @module CSRectGeom.h | Wrapper für _DGMRectangleGeometry

#if !defined(_CSRECTGEOM_H__6AA5EF94_9E55_11D1_BA1C_080036D63803__INCLUDED_)
#define _CSRECTGEOM_H__6AA5EF94_9E55_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable: 4192)	// automatically excluding 'bla' while importing type library 'bla'

#if !defined(_CSRECT_ALREADY_PRESENT_)
///////////////////////////////////////////////////////////////////////////////
// type libraries
#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#import "tlb/tdbgeo.tlb" no_namespace raw_native_types raw_interfaces_only named_guids no_implementation \
	exclude("IPersist", "IPersistMemory")

#if !defined(___DGMPoint_FWD_DEFINED__)
#define ___DGMPoint_FWD_DEFINED__
#define ___DGMPoints_FWD_DEFINED__
#endif // ___DGMPoint_FWD_DEFINED__
#if !defined(___DGMPoint_INTERFACE_DEFINED__)
#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__
#endif // ___DGMPoint_INTERFACE_DEFINED__

DefineSmartInterface2(_DGMRectangleGeometry, IID__DGMRectangleGeometry);	// W_DGMRectangleGeometry

#endif	// _CSRECT_ALREADY_PRESENT_

//#include <ictf.h>
#include <CSPoint.h>		// Geomedia und TRiAS-Definitionen kommen hier mit...

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASCSRectangleGeometry> CRectFactory;
extern CRectFactory MakeRects;
#endif // defined(_USE_CLASSFACTORY_CACHE)

class CCSRectangleGeometry
{
private:
	__Interface<ITRiASSimpleRectangle> m_rect;

public:
	CCSRectangleGeometry()
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_rect (CLSID_TRiASCSRectangleGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeRects.CreateInstance (m_rect.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_rect);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
	}
	CCSRectangleGeometry (double dX, double dY, double dWidth, double dHeight)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_rect (CLSID_TRiASCSRectangleGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeRects.CreateInstance (m_rect.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_rect);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
		m_rect -> SetRect (dX, dY, dX + dWidth, dY + dHeight);
	}
	CCSRectangleGeometry (double dXMin, double dYMin, double dXMax, double dYMax, int iDummy)
#if !defined(_USE_CLASSFACTORY_CACHE)
		: m_rect (CLSID_TRiASCSRectangleGeometry)
#endif // !defined(_USE_CLASSFACTORY_CACHE)
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		THROW_FAILED_HRESULT(MakeRects.CreateInstance (m_rect.ppi()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> p (m_rect);
	
		_ASSERTE(NULL != (IPersistStreamInit *)p);
		p -> InitNew();
		m_rect -> SetRect (dXMin, dYMin, dXMax, dYMax);
	}
	CCSRectangleGeometry (ITRiASSimpleRectangle *pRG)
		: m_rect (pRG)
	{
	}
	CCSRectangleGeometry (IDispatch *pRG)
		: m_rect (pRG)
	{
	}
	CCSRectangleGeometry (IUnknown *pRG)
		: m_rect (pRG)
	{
	}
	~CCSRectangleGeometry () {}

// Helperfunktionen für Zugriff auf Origin
	HRESULT get_X (double *pdX) { return m_rect -> get_XMin (pdX); }
	HRESULT put_X (double dX) { return m_rect -> put_XMin (dX); }
	HRESULT get_Y (double *pdY) { return m_rect -> get_YMin (pdY); }
	HRESULT put_Y (double dY) { return m_rect -> put_YMin (dY); }

// Helperfunktionen links unten/rechts oben
	HRESULT get_XMin (double *pdX) { return m_rect -> get_XMin (pdX); }
	HRESULT put_XMin (double dX) { return m_rect -> put_XMin (dX); }
	HRESULT get_XMax (double *pdX) { return m_rect -> get_XMax (pdX); }
	HRESULT put_XMax (double dX) { return m_rect -> put_XMax (dX); }

	HRESULT get_YMin (double *pdY) { return m_rect -> get_YMin (pdY); }
	HRESULT put_YMin (double dY) { return m_rect -> put_YMin (dY); }
	HRESULT get_YMax (double *pdY) { return m_rect -> get_YMax (pdY); }
	HRESULT put_YMax (double dY) { return m_rect -> put_YMax (dY); }

	HRESULT GetRect (double *pdXMin, double *pdYMin, double *pdXMax, double *pdYMax)
	{
		return m_rect -> GetRect (pdXMin, pdYMin, pdXMax, pdYMax);
	}
	HRESULT SetRect (double dXMin, double dYMin, double dXMax, double dYMax)
	{
		return m_rect -> SetRect (dXMin, dYMin, dXMax, dYMax);
	}

// Zugriffsoperatoren
	ITRiASSimpleRectangle *operator ->() const { return m_rect; }
	operator ITRiASSimpleRectangle *() const { return m_rect; }
	ITRiASSimpleRectangle *detach() { return m_rect.detach(); }
	void Assign (IDispatch *pINew) { m_rect = pINew; }

// explizites QI, da der default-IDispatch nicht der von ITRiASSimpleRectangle ist
	operator IDispatch *() const 
	{
	__Interface<IDispatch> disp;

		if (SUCCEEDED(const_cast<CCSRectangleGeometry &>(*this).m_rect -> QueryInterface(disp.ppi()))) {
			disp -> Release();		// access with no AddRef !
			return disp.detach();
		}
		return NULL;
	}

	bool operator! () { return !m_rect; }
	bool IsValid() { return m_rect.IsValid(); }

// Zuweisungsoperator
	CCSRectangleGeometry &operator= (const CCSRectangleGeometry &rhs)
		{ if (&rhs != this) m_rect = const_cast<CCSRectangleGeometry &>(rhs).m_rect; return *this; }
	CCSRectangleGeometry &operator= (ITRiASSimpleRectangle *rhs) { m_rect = rhs; return *this; }
	CCSRectangleGeometry &operator= (IUnknown *rhs) { m_rect = rhs; return *this; }

///////////////////////////////////////////////////////////////////////////////
// RechtecksOperatoren
// Verschnitt der beiden Rechtecke
	bool operator^ (const CCSRectangleGeometry &p)
	{
	double dMin1, dMin2, dMax1, dMax2;
	CCSRectangleGeometry &rhs = const_cast<CCSRectangleGeometry &>(p);

		THROW_FAILED_HRESULT(get_XMin(&dMin1));
		THROW_FAILED_HRESULT(rhs.get_XMax(&dMax2));
		if (dMin1 > dMax2) return false;	// ObjContainer überschneiden sich nicht

		THROW_FAILED_HRESULT(get_XMax(&dMax1));
		THROW_FAILED_HRESULT(rhs.get_XMin(&dMin2));
		if (dMax1 < dMin2) return false;	// ObjContainer überschneiden sich nicht

		THROW_FAILED_HRESULT(get_YMin(&dMin1));
		THROW_FAILED_HRESULT(rhs.get_YMax(&dMax2));
		if (dMin1 > dMax2) return false;	// ObjContainer überschneiden sich nicht

		THROW_FAILED_HRESULT(get_YMax(&dMax1));
		THROW_FAILED_HRESULT(rhs.get_YMin(&dMin2));
		if (dMax1 < dMin2) return false;	// ObjContainer überschneiden sich nicht

		return true;
	}

// Gemeinsamen Container berechnen
	CCSRectangleGeometry& operator+ (const CCSRectangleGeometry &p)
	{
	double dXMin1, dXMin2;
	double dXMax1, dXMax2;
	double dYMin1, dYMin2;
	double dYMax1, dYMax2;
	CCSRectangleGeometry &rhs = const_cast<CCSRectangleGeometry &>(p);

		THROW_FAILED_HRESULT(get_XMin(&dXMin1));
		THROW_FAILED_HRESULT(rhs.get_XMin(&dXMin2));

		THROW_FAILED_HRESULT(get_YMin(&dYMin1));
		THROW_FAILED_HRESULT(rhs.get_YMin(&dYMin2));

		THROW_FAILED_HRESULT(get_XMax(&dXMax1));
		THROW_FAILED_HRESULT(rhs.get_XMax(&dXMax2));

		THROW_FAILED_HRESULT(get_YMax(&dYMax1));
		THROW_FAILED_HRESULT(rhs.get_YMax(&dYMax2));

		if (dXMax1 < dXMax2) { THROW_FAILED_HRESULT(put_XMax(dXMax2)); }
		if (dXMin1 > dXMin2) { THROW_FAILED_HRESULT(put_XMin(dXMin2)); }
		if (dYMax1 < dYMax2) { THROW_FAILED_HRESULT(put_YMax(dYMax2)); }
		if (dYMin1 > dYMin2) { THROW_FAILED_HRESULT(put_YMin(dYMin2)); }

		return *this;
	}

// Verschneiden und gemeinsame Fläche liefern
	CCSRectangleGeometry& operator& (const CCSRectangleGeometry &p)
	{
	double dXMin1, dXMin2;
	double dXMax1, dXMax2;
	double dYMin1, dYMin2;
	double dYMax1, dYMax2;
	CCSRectangleGeometry &rhs = const_cast<CCSRectangleGeometry &>(p);

		THROW_FAILED_HRESULT(get_XMin(&dXMin1));
		THROW_FAILED_HRESULT(rhs.get_XMin(&dXMin2));

		THROW_FAILED_HRESULT(get_YMin(&dYMin1));
		THROW_FAILED_HRESULT(rhs.get_YMin(&dYMin2));

		THROW_FAILED_HRESULT(get_XMax(&dXMax1));
		THROW_FAILED_HRESULT(rhs.get_XMax(&dXMax2));

		THROW_FAILED_HRESULT(get_YMax(&dYMax1));
		THROW_FAILED_HRESULT(rhs.get_YMax(&dYMax2));

		if (dXMax1 > dXMax2) { THROW_FAILED_HRESULT(put_XMax(dXMax2)); }
		if (dXMin1 < dXMin2) { THROW_FAILED_HRESULT(put_XMin(dXMin2)); }
		if (dYMax1 > dYMax2) { THROW_FAILED_HRESULT(put_YMax(dYMax2)); }
		if (dYMin1 < dYMin2) { THROW_FAILED_HRESULT(put_YMin(dYMin2)); }

		return *this;
	}
};

#endif // !defined(_CSRECTGEOM_H__6AA5EF94_9E55_11D1_BA1C_080036D63803__INCLUDED_)
