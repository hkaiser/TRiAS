///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GKEtrsCoordTrans.h | Description goes here

#if !defined(_GKEtrsCoordTrans_H__858FEED3_A8FF_11D1_A061_0060975566B4__INCLUDED_)
#define _GKEtrsCoordTrans_H__858FEED3_A8FF_11D1_A061_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CoordTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CGKEtrsCoordTrans
class ATL_NO_VTABLE CGKEtrsCoordTrans : 
	public CComCoClass<CGKEtrsCoordTrans, &CLSID_GKEtrsCoordTrans>,
	public CCoordTrans
{
public:
	typedef CComCoClass<CGKEtrsCoordTrans, &CLSID_GKEtrsCoordTrans> base_t;

	CGKEtrsCoordTrans()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GKETRSCOORDTRANS)

	BEGIN_COM_MAP(CGKEtrsCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY_TEAR_OFF(__uuidof(ITriasPropSheetExt), CGKPropExt<CGKEtrsCoordTrans>)
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

protected:
	typedef enum tagCOORDTRANSELLIPSE {
		CTFELLIPSE_Unknown = 0x8000,
		CTFELLIPSE_Etrs89 = 0,
		CTFELLIPSE_Bessel = 1,
		CTFELLIPSE_Krassovsky = 2,
	} COORDTRANSELLIPSE;

	// Hilfsroutinen
//	void ConvertEllipse ( int iStrBreite, int iMeridian, long double dYGeod,
//		long double dXGeod, long double *pdYOut, long double *pdXOut);
//	void InvConvertEllipse ( int iStrBreite, int iMeridian, long double dY,
//		long double dX, long double *pdYOut, long double *pdXOut);

public:	
	virtual CString GetEllipseStrings();
	virtual CString GetCoordTypeString(int iEllipse, COORDTRANSFORMTYPE rgType = CTF_Native);
	virtual CString GetInternalCoordTypeString();

	virtual TRIASCSGEODETICDATUM GetGeodDatum(int rgEllipse, bool fNativeEllipe = false);
	virtual double GetScaleFactor(int rgEllipse);
};

#endif // !defined(_GKEtrsCoordTrans_H__858FEED3_A8FF_11D1_A061_0060975566B4__INCLUDED_)
