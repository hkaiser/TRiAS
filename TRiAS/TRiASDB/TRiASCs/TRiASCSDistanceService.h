// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 22:57:47 
//
// @doc
// @module TRiASCSDistanceService.h | Declaration of the <c CTRiASCSDistanceService> class

#if !defined(_TRiASCSDistanceService_H__E24ED91E_A9F8_4081_9FB9_A39AB6E28B00__INCLUDED_)
#define _TRiASCSDistanceService_H__E24ED91E_A9F8_4081_9FB9_A39AB6E28B00__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "EllipsParams.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSTransform);

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSDistanceService
class ATL_NO_VTABLE CTRiASCSDistanceService : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSDistanceService, &CLSID_TRiASCSDistanceService>,
	public CErrSupport<CTRiASCSDistanceService, &IID_ITRiASCSDistanceService>,
	public IDispatchImpl<ITRiASCSDistanceService, &IID_ITRiASCSDistanceService, &LIBID_TRIASCS>
{
public:
	CTRiASCSDistanceService() :
		m_rgAcc(ACCURACY_Spheric), m_rgUoL(tcsUOL_Metre), m_dConvertUoL(1.0), m_timeLastTime(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCSDistanceService)
	DECLARE_REGISTRY_RESOURCEID(IDR_DISTANCESERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASCSDistanceService)
		COM_INTERFACE_ENTRY(ITRiASCSDistanceService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT FinalConstruct();
	void FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASCSDistanceService
public:
// Methods
	STDMETHODIMP GetDistancePts(/*[in]*/ VARIANT CS1, /*[in]*/ VARIANT Pts1, /*[in]*/ VARIANT CS2, /*[in]*/ VARIANT Pts2, double *pVal);

// Properties
	STDMETHODIMP put_Accuracy(/*[in]*/ DIST_ACCURACY newVal);
	STDMETHODIMP get_Accuracy(/*[out, retval]*/ DIST_ACCURACY *pVal);
	STDMETHODIMP putref_TransformPipe(/*[in]*/ ITRiASCSTransform *newVal);
	STDMETHODIMP get_TransformPipe(/*[out, retval]*/ ITRiASCSTransform **pVal);
	STDMETHODIMP get_LastTime(/*[out, retval]*/ double *pVal);

protected:
	HRESULT RetrieveCSGuid(VARIANT vCSArg, CIID *pGuid);
	HRESULT CalculateDistance (REFGUID rGuid1, CSCOORD *pPt1, REFGUID rGuid2, CSCOORD *pPt2, double *pDist);
	HRESULT CalculateDistancePlanar (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist);
	HRESULT CalculateDistanceSpheric (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist);
	HRESULT CalculateDistanceEllipsoidal1 (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist);
	HRESULT CalculateDistanceEllipsoidal2 (CSCOORD *pPt1, CSCOORD *pPt2, double *pDist);
	HRESULT InitCachedValues();

	double CorrectValueOfLength (double dDist) { return m_dConvertUoL * dDist; }
	double CorrectValueOfAngle (double dCoord) { return m_dConvertUoA * dCoord; }
	double InvCorrectValueOfLength (double dDist) { return dDist / m_dConvertUoL; }
	double InvCorrectValueOfAngle (double dCoord) { return dCoord / m_dConvertUoA; }

private:
	DIST_ACCURACY m_rgAcc;
	WTRiASCSTransform m_CSS;

// gecachte Parameter des Ausgangssystemes
	CEllipsoidParams m_EP;
	TRIASCSUNITOFLENGTH m_rgUoL;	// L‰ngenmaﬂeinheit
	TRIASCSUNITOFANGLE m_rgUoA;		// Winkelmaﬂeinheit

	double m_dConvertUoL;
	double m_dConvertUoA;

	double m_timeLastTime;			// letzte Rechenzeit in [ms]
};

#endif // !defined(_TRiASCSDistanceService_H__E24ED91E_A9F8_4081_9FB9_A39AB6E28B00__INCLUDED_)
