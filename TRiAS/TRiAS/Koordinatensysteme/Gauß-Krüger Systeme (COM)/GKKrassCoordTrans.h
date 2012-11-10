///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GKKrassCoordTrans.h | Description goes here

#if !defined(_GKKRASSCOORDTRANS_H__727979D5_ABAD_11D1_A066_0060975566B4__INCLUDED_)
#define _GKKRASSCOORDTRANS_H__727979D5_ABAD_11D1_A066_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "CoordPara.h"
#include "CoordTransBase.h"


/////////////////////////////////////////////////////////////////////////////
// CGKKrassCoordTrans
class ATL_NO_VTABLE CGKKrassCoordTrans : 
	public CComCoClass<CGKKrassCoordTrans, &CLSID_GKKrassCoordTrans>,
	public IConnectionPointContainerImpl<CGKKrassCoordTrans>,
	public CCoordTrans
{
public:
	typedef CComCoClass<CGKKrassCoordTrans, &CLSID_GKKrassCoordTrans> base_t;

	CGKKrassCoordTrans()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GKKRASSCOORDTRANS)

	BEGIN_COM_MAP(CGKKrassCoordTrans)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_TEAR_OFF(__uuidof(ITriasPropSheetExt), CGKPropExt<CGKKrassCoordTrans>)
		COM_INTERFACE_ENTRY_CHAIN(CCoordTrans)			/* JG 990119*/
	END_COM_MAP()

// ErrorHandling
	STDMETHOD(Error)(LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ICoordTransform)
		{ return base_t::Error (pcText, riid, hr); }

// ICoordTransform
public:
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

// ICoordTransformInit
	virtual void InitVars(ITRiASProperties *pIProps);

protected:
	// Hilfsroutinen
//	void ConvertEllipse ( int iStrBreite, int iMeridian, long double dYGeod,
//		long double dXGeod, long double *pdYOut, long double *pdXOut);
//	void InvConvertEllipse ( int iStrBreite, int iMeridian, long double dY,
//		long double dX, long double *pdYOut, long double *pdXOut);

	typedef enum tagCOORDTRANSELLIPSE {
		CTFELLIPSE_Unknown = 0x8000,
		CTFELLIPSE_Krassovsky = 0,
		CTFELLIPSE_Etrs89 = 1,
		CTFELLIPSE_Bessel = 2,
	} COORDTRANSELLIPSE;

	BOOL GetMeridianGK( double, int& );
	BOOL GetMeridianGeod( double, int& );

public:
	virtual CString GetEllipseStrings();
	virtual CString GetCoordTypeString(int iEllipse, COORDTRANSFORMTYPE rgType = CTF_Native);
	virtual CString GetInternalCoordTypeString();

	virtual TRIASCSGEODETICDATUM GetGeodDatum(int rgEllipse, bool fNativeEllipe = false);
	virtual double GetScaleFactor(int rgEllipse);
};

#endif // !defined(_GKKRASSCOORDTRANS_H__727979D5_ABAD_11D1_A066_0060975566B4__INCLUDED_)
