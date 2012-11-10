///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CoordTransBase.h | Description goes here

#if !defined(_COORDTRANSBASE_H__95F58F34_DF2C_11D1_8606_00600875138A__INCLUDED_)
#define _COORDTRANSBASE_H__95F58F34_DF2C_11D1_8606_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/map>

#include "resource.h"       // main symbols
#include "CoordPara.h"
#include "GeodCTFPropExt.h"
#include "CPCTFTransformEvents.h"

#import "tlb/TRiASCS.tlb" raw_interfaces_only, raw_native_types, no_namespace, \
	named_guids 

DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASRawCoordTransform);
DefineSmartInterface(TRiASCSTransform);

/////////////////////////////////////////////////////////////////////////////
// CCoordTrans
class ATL_NO_VTABLE CCoordTrans : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public ICoordTransformInit,
	public CProxyICoordTransformEvents<CCoordTrans>,
	public IConnectionPointContainerImpl<CCoordTrans>,
	public IDispatchImpl<ICoordTransform, &IID_ICoordTransform, &LIBID_GEODCTFLib>
{
public:
	CCoordTrans()
	{
//		HA = 0.0;
//		HB = 0.0;
//		KS = 1.0;

		m_CTFType = CTF_Native;				// Geod-Koordinaten anzeigen
		m_CTFMode = CTFMODE_AutoMeridian;	// wenn GK, dann Meridian automatisch auswählen
		m_iMeridian = 12;					// Meridian für GK
		m_iStrBreite = 3;					// Streifenbreite für GK
		m_iPrec = 0;						// Darstellungsgenauigkeit
		m_dUnitScale = 1.0;					// Default: seconds
		m_rgUOA = tcsUOA_Second;

		m_fInitialized = false;				// CTF wurde ordnungsgemäß geladen
		m_fAllowChangeEllipse = false;				// EllipsoidWechsel erlauben

		m_rgChangeEllipse = CTFELLIPSE_Unknown;		// Ellipsoid der externen Koordinaten
		m_rgEllipseNative = CTFELLIPSE_Unknown;		// Ellipsoid der internen Koordinaten
	}

	HRESULT FinalConstruct()
	{
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}

	void FinalRelease()
	{
		TermCoordTransform();
	}

	BEGIN_COM_MAP(CCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ICoordTransformInit)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CCoordTrans)
		CONNECTION_POINT_ENTRY(IID_ICoordTransformEvents)
	END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ErrorHandling
	STDMETHOD(Error)(LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ICoordTransform) = 0;

// ICoordTransform
public:
	STDMETHOD(get_CanConfig)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_IsMetric)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_AspectRatio)(/*[in]*/ _DGMPoint *pPt1, /*[in]*/ _DGMPoint *pPt2, /*[out, retval]*/ double *pVal);

	STDMETHOD(get_Envelope)(/*[out, retval]*/ IDispatch **pIParam);

//	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);	// JG990127

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

	STDMETHOD(Distance)(/*[in]*/ _DGMPoint *Point1, /*[in]*/ _DGMPoint *Point2, /*[out, retval]*/ _DGMPoint **pVal);
	STDMETHOD(DistanceEx)(/*[in]*/ _DGMPoint *Point1, /*[in]*/ _DGMPoint *Point2, /*[out]*/ _DGMPoint **pVal, /*[out, retval]*/ double *pdDist);
	STDMETHOD(DistancePoint)(/*[in]*/ _DGMPoint *Point, /*[in]*/ _DGMPoint *Delta, /*[out, retval]*/ _DGMPoint * *pVal);

	STDMETHOD(TransformParameter)(/*[in]*/ _DGMPoint *Point, /*[in]*/ TRANSDIRECTION Dir, /*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(FreeTransformParameter)(/*[in]*/ TRANSDIRECTION Dir, /*[in]*/ IDispatch *pDisp);
	STDMETHOD(NativeParameter)(/*[in]*/ _DGMPoint *Point, /*[in]*/ TRANSDIRECTION Dir, /*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(FreeNativeParameter)(/*[in]*/ TRANSDIRECTION Dir, /*[in]*/ IDispatch *pIDisp);

	STDMETHOD(ToPoint)(/*[in]*/ BSTR XStr, /*[in]*/ BSTR YStr, /*[in]*/ BSTR ZStr, /*[out, retval]*/ _DGMPoint **Point);
	STDMETHOD(ToStrings)(/*[in]*/ _DGMPoint *Point, /*[out]*/ BSTR *XStr, /*[out]*/ BSTR *YStr, /*[out]*/ BSTR *ZStr);

	STDMETHOD(get_CoordTransformPipe)(/*[out, retval]*/ IDispatch **ppIPipe);

// ICoordTransformInit
	STDMETHOD(TermCoordTransform)(void);
	STDMETHOD(InitCoordTransform)(IUnknown *pIUnk);
	STDMETHOD(ReInitCoordTransform)(IUnknown *pIUnk);

	virtual void InitVars (ITRiASProperties *pIProps) = 0;

	typedef enum tagCOORDTRANSELLIPSE {
		CTFELLIPSE_Unknown = 0x8000,
	} COORDTRANSELLIPSE;

// ZugriffsRoutinen für ParameterDialog
	int GetMeridian() { return m_iMeridian; }
	int GetStrBreite() { return m_iStrBreite; }
	int GetPrecision() { return m_iPrec; }	
	bool GetAllowChangeEllipse() { return m_fAllowChangeEllipse; }
	COORDTRANSFORMTYPE GetCTFType() { return m_CTFType; }
	COORDTRANSFORMMODE GetCTFMode() { return m_CTFMode; }
	COORDTRANSELLIPSE GetChangedEllipse() { return m_rgChangeEllipse; }
	COORDTRANSELLIPSE GetNativeEllipse() { return m_rgEllipseNative; }

	void SetMeridian (int iMeridian) { m_iMeridian = iMeridian; }
	void SetStrBreite (int iStrBreite) { m_iStrBreite = iStrBreite; }
	void SetPrecision (int iPrec) { m_iPrec = iPrec; }
	void SetCTFType (COORDTRANSFORMTYPE rgCTFType) { m_CTFType = rgCTFType; }
	void SetCTFMode (COORDTRANSFORMMODE rgCTFMode) { m_CTFMode = rgCTFMode; }
	void SetChangedEllipse (COORDTRANSELLIPSE rgEllipse) { m_rgChangeEllipse = rgEllipse; }
	void SetNativeEllipse (COORDTRANSELLIPSE rgEllipse) { m_rgEllipseNative = rgEllipse; }

	HRESULT UpdateNewSettings(bool fNative, bool fAutoMeridian);				// neu eingestellte Werte zurückschreiben
	virtual CString GetEllipseStrings() = 0;
	virtual CString GetCoordTypeString(int iEllipse, COORDTRANSFORMTYPE rgType = CTF_Native) = 0;

	virtual TRIASCSGEODETICDATUM GetGeodDatum(int iEllipse, bool fNativeEllipse = false) = 0;
	virtual double GetScaleFactor(int iEllipse) = 0;

protected:
// Hilfsroutinen
//	virtual void ConvertEllipse ( int iStrBreite, int iMeridian, long double dYGeod,
//		long double dXGeod, long double *pdYOut, long double *pdXOut) = 0;
//	virtual void InvConvertEllipse ( int iStrBreite, int iMeridian, long double dY,
//		long double dX, long double *pdYOut, long double *pdXOut) = 0;

	BOOL GetMeridianGK (double, int &);
	BOOL GetMeridianGeod (double, int &);

protected:
// TRiASPropertyBase
	WTRiASPropertyBase m_PropBase;

// Ellipsoid-Halbachsen des internen Koordinatensystemes
//	double HA, HB;
//	double KS;

	int m_iMeridian;
	int m_iStrBreite;
	int m_iPrec;
	double m_dUnitScale;
	TRIASCSUNITOFANGLE m_rgUOA;

	bool m_fInitialized;
	bool m_fAllowChangeEllipse;

	COORDTRANSFORMTYPE m_CTFType;
	COORDTRANSFORMMODE m_CTFMode;			// Meridianbestimmung	

	COORDTRANSELLIPSE m_rgChangeEllipse;	// GUIEllipse
	COORDTRANSELLIPSE m_rgEllipseNative;	// DBEllipse

// #HK020301
	typedef map<ULONG, CSID, less<ULONG> > CCSMap;
	CCSMap m_CSMap;
	WTRiASRawCoordTransform m_CTF;

	HRESULT AddOutputCS();
	HRESULT EnsureGeodCS (COORDTRANSELLIPSE rgEllipse, CSID *pCsId);
	HRESULT EnsureGKCS (COORDTRANSELLIPSE rgEllipse, int iZoneWidth, int iMeridian, CSID *pCsId);
};

#endif // !defined(_COORDTRANSBASE_H__95F58F34_DF2C_11D1_8606_00600875138A__INCLUDED_)
