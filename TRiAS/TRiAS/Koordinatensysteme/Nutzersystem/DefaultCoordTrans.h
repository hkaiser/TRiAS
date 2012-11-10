///////////////////////////////////////////////////////////////////////////
// @doc
// @module DefaultCoordTrans.h | Declaration of the CDefaultCoordTrans

#if !defined(_DEFAULTCOORDTRANS_H__0BDC3C1A_503F_11d1_96F0_00A024D6F582__INCLUDED_)
#define _DEFAULTCOORDTRANS_H__0BDC3C1A_503F_11d1_96F0_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "default.h"       // main symbols

#include <ospace/std/map>

// type libraries
//#include <GMObjects/PBasic.tlh>

#import "tlb/TRiASCS.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASRawCoordTransform);
DefineSmartInterface(TRiASCSTransform);

/////////////////////////////////////////////////////////////////////////////
// CDefaultCoordTrans
class ATL_NO_VTABLE CDefaultCoordTrans : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDefaultCoordTrans, &CLSID_DefaultCoordTrans>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDefaultCoordTrans>,
	public ICoordTransformInit,
	public IDispatchImpl<ICoordTransform, &IID_ICoordTransform, &LIBID_CoordTransLib>
{
public:
	CDefaultCoordTrans() :
		m_dKoeff(1.0), m_iPrecision(0), 
		m_dFalseX(4500000.0), m_dFalseY(0.0), m_dLongOrig(12*3600), m_dLatOrig(0.0),
		m_dScaleAtOrig(1.0)
	{
	}

	HRESULT FinalConstruct()
	{
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}

	void FinalRelease()
	{
		TermCoordTransform();
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_DEFAULTCOORDTRANS)
	BEGIN_COM_MAP(CDefaultCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ICoordTransformInit)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CDefaultCoordTrans)
	END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICoordTransform
public:
	STDMETHOD(get_CanConfig)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_IsMetric)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_AspectRatio)(/*[in]*/ _DGMPoint *pPt1, /*[in]*/ _DGMPoint *pPt2, /*[out, retval]*/ double *pVal);

	STDMETHOD(Transform)(_DGMPoint *pPt, TRANSDIRECTION Dir);
	STDMETHOD(TransformColl)(/*[in]*/ _DGMPoints *Points, TRANSDIRECTION Dir);
	STDMETHOD(TransformEx)(_DGMPoint *pPt, TRANSDIRECTION Dir, IDispatch *pIParam);
	STDMETHOD(TransformCollEx)(/*[in]*/ _DGMPoints *Points, TRANSDIRECTION Dir, IDispatch *pIParam);
	STDMETHOD(TransformEx2)(_DGMPoint *pPt, TRANSDIRECTION Dir, IUnknown *pICS);
	STDMETHOD(TransformCollEx2)(/*[in]*/ _DGMPoints *Points, TRANSDIRECTION Dir, IUnknown *pICS);

	STDMETHOD(Native)(/*[in]*/ _DGMPoint *Point, TRANSDIRECTION Dir);
	STDMETHOD(NativeColl)(/*[in]*/ _DGMPoints *Points, TRANSDIRECTION Dir);
	STDMETHOD(NativeEx)(/*[in]*/ _DGMPoint *Point, TRANSDIRECTION Dir, IDispatch *pIParam);
	STDMETHOD(NativeCollEx)(/*[in]*/ _DGMPoints *Points, TRANSDIRECTION Dir, IDispatch *pIParam);

	STDMETHOD(Distance)(/*[in]*/ _DGMPoint *Point1, /*[in]*/ _DGMPoint *Point2, /*[out, retval]*/ _DGMPoint ** pDist);
	STDMETHOD(DistanceEx)(/*[in]*/ _DGMPoint *Point1, /*[in]*/ _DGMPoint *Point2, /*[out]*/ _DGMPoint ** pDist, /*[out, retval]*/ double *pdDist);
	STDMETHOD(DistancePoint)(/*[in]*/ _DGMPoint *Point, /*[in]*/ _DGMPoint *Delta, /*[out, retval]*/ _DGMPoint * *pVal);

	STDMETHOD(TransformParameter)(/*[in]*/ _DGMPoint *Point, /*[in]*/ TRANSDIRECTION Dir, /*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(FreeTransformParameter)(/*[in]*/ TRANSDIRECTION Dir, /*[in]*/ IDispatch *pDisp);
	STDMETHOD(NativeParameter)(/*[in]*/ _DGMPoint *Point, /*[in]*/ TRANSDIRECTION Dir, /*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(FreeNativeParameter)(/*[in]*/ TRANSDIRECTION Dir, /*[in]*/ IDispatch *pIDisp);

	STDMETHOD(ToPoint)(/*[in]*/ BSTR XStr, /*[in]*/ BSTR YStr, /*[in]*/ BSTR ZStr, /*[out, retval]*/ _DGMPoint **Point);
	STDMETHOD(ToStrings)(/*[in]*/ _DGMPoint *Point, /*[out]*/ BSTR *XStr, /*[out]*/ BSTR *YStr, /*[out]*/ BSTR *ZStr);

	STDMETHOD(get_Envelope)(/*[out, retval]*/ IDispatch **ppIDisp);
	STDMETHOD(get_CoordTransformPipe)(/*[out, retval]*/ IDispatch **ppIPipe);

// ICoordTransformInit
	STDMETHOD(InitCoordTransform)(IUnknown *pIUnk);
	STDMETHOD(ReInitCoordTransform)(IUnknown *Props);
	STDMETHOD(TermCoordTransform)();

private:
	WTRiASPropertyBase m_PropBase;		// TRiASPropertyBase vom Projekt

	double m_dKoeff;	// zusätzliche Skalierung
	int m_iPrecision;	// DarstellungsGenauigkeit

	double m_dFalseX;
	double m_dFalseY;
	double m_dLongOrig;
	double m_dLatOrig;
	double m_dScaleAtOrig;

// #HK020301
//	typedef map<ULONG, CSID, less<ULONG> > CCSMap;
//	CCSMap m_CSMap;
	WTRiASRawCoordTransform m_CTF;

	HRESULT AddOutputAndInputCS();
};

#endif // !defined(_DEFAULTCOORDTRANS_H__0BDC3C1A_503F_11d1_96F0_00A024D6F582__INCLUDED_)
