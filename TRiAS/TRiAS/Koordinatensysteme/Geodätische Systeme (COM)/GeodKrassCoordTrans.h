///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GeodKrassCoordTrans.h | Description goes here

#if !defined(_GEODKRASSCOORDTRANS_H__4AEFCF44_A869_11D1_A060_0060975566B4__INCLUDED_)
#define _GEODKRASSCOORDTRANS_H__4AEFCF44_A869_11D1_A060_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CoordTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CGeodKrassCoordTrans
class ATL_NO_VTABLE CGeodKrassCoordTrans : 
	public CComCoClass<CGeodKrassCoordTrans, &CLSID_GeodKrassCoordTrans>,
	public CCoordTrans
{
public:
	typedef CComCoClass<CGeodKrassCoordTrans, &CLSID_GeodKrassCoordTrans> base_t;

	CGeodKrassCoordTrans()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GEODKRASSCOORDTRANS)

	BEGIN_COM_MAP(CGeodKrassCoordTrans)
		COM_INTERFACE_ENTRY(ICoordTransform)
		COM_INTERFACE_ENTRY_TEAR_OFF(__uuidof(ITriasPropSheetExt), CGeodCTFPropExt<CGeodKrassCoordTrans>)
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
		CTFELLIPSE_Krassovsky = 0,
		CTFELLIPSE_Etrs89 = 1,
		CTFELLIPSE_Bessel = 2,
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
};

#endif // !defined(_GEODKRASSCOORDTRANS_H__4AEFCF44_A869_11D1_A060_0060975566B4__INCLUDED_)
