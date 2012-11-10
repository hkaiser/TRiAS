///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GeodBesselCoordTrans.h | Description goes here

#if !defined(_GEODBESSELCOORDTRANS_H__4AEFCF43_A869_11D1_A060_0060975566B4__INCLUDED_)
#define _GEODBESSELCOORDTRANS_H__4AEFCF43_A869_11D1_A060_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CoordTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CGeodBesselCoordTrans
class ATL_NO_VTABLE CGeodBesselCoordTrans : 
	public CComCoClass<CGeodBesselCoordTrans, &CLSID_GeodBesselCoordTrans>,
	public CCoordTrans
{
public:
	typedef CComCoClass<CGeodBesselCoordTrans, &CLSID_GeodBesselCoordTrans> base_t;

	CGeodBesselCoordTrans() :
		m_rgNativeDatum(tcsGD_DeutscheHauptdreiecksnetzRd83DHDN)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GEODBESSELCOORDTRANS)

	BEGIN_COM_MAP(CGeodBesselCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY_TEAR_OFF(__uuidof(ITriasPropSheetExt), CGeodCTFPropExt<CGeodBesselCoordTrans>)
		COM_INTERFACE_ENTRY_CHAIN(CCoordTrans)
	END_COM_MAP()

// ErrorHandling
	STDMETHOD(Error)(LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ICoordTransform)
		{ return base_t::Error (pcText, riid, hr); }

// ICoordTransform
public:
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

// ICoordTransformInit
	virtual void InitVars (ITRiASProperties *pIProps);

	typedef enum tagCOORDTRANSELLIPSE {
		CTFELLIPSE_Unknown = 0x8000,
		CTFELLIPSE_Bessel = 0,
		CTFELLIPSE_Krassovsky = 1,
		CTFELLIPSE_Etrs89 = 2,
	} COORDTRANSELLIPSE;

protected:
// Hilfsroutinen
//	void ConvertEllipse ( int iStrBreite, int iMeridian, long double dYGeod,
//		long double dXGeod, long double *pdYOut, long double *pdXOut);
//	void InvConvertEllipse ( int iStrBreite, int iMeridian, long double dY,
//		long double dX, long double *pdYOut, long double *pdXOut);

	CString GetEllipseStrings();
	CString GetCoordTypeString(int iEllipse, COORDTRANSFORMTYPE rgType = CTF_Native);

	TRIASCSGEODETICDATUM GetGeodDatum(int rgEllipse, bool fNativeEllipse = false);
	double GetScaleFactor(int rgEllipse);

private:
	TRIASCSGEODETICDATUM m_rgNativeDatum;
};

#endif // !defined(_GEODBESSELCOORDTRANS_H__4AEFCF43_A869_11D1_A060_0060975566B4__INCLUDED_)
