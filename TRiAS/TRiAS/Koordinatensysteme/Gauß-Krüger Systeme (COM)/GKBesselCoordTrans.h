///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GKBesselCoordTrans.h | Description goes here

#if !defined(_GKBESSELCOORDTRANS_H__727979D4_ABAD_11D1_A066_0060975566B4__INCLUDED_)
#define _GKBESSELCOORDTRANS_H__727979D4_ABAD_11D1_A066_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "CoordTransBase.h"	// JG990125 CCoordTrans now defined in extra file

/////////////////////////////////////////////////////////////////////////////
// CGKBesselCoordTrans
class ATL_NO_VTABLE CGKBesselCoordTrans : 
	public CComCoClass<CGKBesselCoordTrans, &CLSID_GKBesselCoordTrans>,
	public CCoordTrans
{
public:
	typedef CComCoClass<CGKBesselCoordTrans, &CLSID_GKBesselCoordTrans> base_t;

	CGKBesselCoordTrans() : 
		m_rgNativeDatum(tcsGD_DeutscheHauptdreiecksnetzRd83DHDN)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GKBESSELCOORDTRANS)

	BEGIN_COM_MAP(CGKBesselCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY_TEAR_OFF(__uuidof(ITriasPropSheetExt), CGKPropExt<CGKBesselCoordTrans>)
		COM_INTERFACE_ENTRY_CHAIN(CCoordTrans)			/* JG 990119 */
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return CCoordTrans::FinalConstruct();
	}

	void FinalRelease()
	{
	}

// ErrorHandling
	STDMETHOD(Error)(LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ICoordTransform)
		{ return base_t::Error (pcText, riid, hr); }

// ICoordTransform
public:
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

// ICoordTransformInit
	virtual void InitVars(ITRiASProperties *pIProps);	
//	STDMETHOD(InitCoordTransform)(IUnknown *pIUnk);

	virtual CString GetEllipseStrings();
	virtual CString GetCoordTypeString(int iEllipse, COORDTRANSFORMTYPE rgType = CTF_Native);
	virtual CString GetInternalCoordTypeString();

	virtual TRIASCSGEODETICDATUM GetGeodDatum(int rgEllipse, bool fNativeEllipe = false);
	virtual double GetScaleFactor(int rgEllipse);

protected:
	// Hilfsroutinen
//	void ConvertEllipse ( int iStrBreite, int iMeridian, long double dYGeod,
//		long double dXGeod, long double *pdYOut, long double *pdXOut);
//	void InvConvertEllipse ( int iStrBreite, int iMeridian, long double dY,
//		long double dX, long double *pdYOut, long double *pdXOut);

	typedef enum tagCOORDTRANSELLIPSE {
		CTFELLIPSE_Unknown = 0x8000,
		CTFELLIPSE_Bessel = 0,
		CTFELLIPSE_Krassovsky = 1,
		CTFELLIPSE_Etrs89 = 2,
	} COORDTRANSELLIPSE;

	BOOL GetMeridianGK( double, int& );
	BOOL GetMeridianGeod( double, int& );

private:
	TRIASCSGEODETICDATUM m_rgNativeDatum;
};

#endif // !defined(_GKBESSELCOORDTRANS_H__727979D4_ABAD_11D1_A066_0060975566B4__INCLUDED_)
