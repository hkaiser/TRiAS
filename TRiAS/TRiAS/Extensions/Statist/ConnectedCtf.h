// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 23:08:07 
//
// @doc
// @module ConnectedCtf.h | Declaration of the <c CConnectedCtf> class

#if !defined(_CONNECTEDCTF_H__7FB5A56A_2FFD_421E_942E_03536C5C1EAC__INCLUDED_)
#define _CONNECTEDCTF_H__7FB5A56A_2FFD_421E_942E_03536C5C1EAC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ctfxmfc.h>

class CConnectedCtf :
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
		CConnectedCtf() { m_pCTF = NULL; }
		~CConnectedCtf() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CConnectedCtf)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CConnectedCtf)

	HRESULT FinalConstruct(void);

public:
// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

	HRESULT SetXtsnSite (ITriasXtensionSite *pSite);
	HRESULT DisConnectFromServer (void);

public:
	bool LoadCTF (void);
	void ReleaseCTF (void);
	bool EnsureLoaded(void);

	bool Transform (double *pX, double *pY)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> Transform(pX, pY); }
	bool InvTransform (double *pX, double *pY)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> InvTransform(pX, pY); }
	bool TransformEx (double *pX, double *pY, void *pData)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> TransformEx(pX, pY, pData); }
	bool InvTransformEx (double *pX, double *pY, void *pData)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> InvTransformEx(pX, pY, pData); }

	bool MetricEx (double dX, double dY, double *pX, double *pY, void *pData)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> MetricEx(dX, dY, pX, pY, pData); }
	bool NativeEx (double dX, double dY, double *pX, double *pY, void *pData)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> NativeEx(dX, dY, pX, pY, pData); }

	bool Scale (const double &rX, const double &rY, KoOrd *pdX, KoOrd *pdY)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> Scale (rX, rY, pdX, pdY); }
	bool UnScale (const KoOrd &rX, const KoOrd &rY, double *pdX, double *pdY)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> UnScale (rX, rY, pdX, pdY); }

	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransToStringEx (dX, dY, isX, pBuffer, iLen); }
	double CoordTransDistance (const DoublePair *pDP1, const DoublePair *pDP2)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransDistance (pDP1, pDP2); }
	char *CoordTransDescription (char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransDescription (pBuffer, iLen); }

	bool GetTransformParam(double dX, double dY, void **ppData) 
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> GetTransformParam(dX, dY, ppData); }
	bool GetInvTransformParam(double dX, double dY, void **ppData) 
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> GetInvTransformParam(dX, dY, ppData); }
	bool GetMetricParam(double dX, double dY, void **ppData) 
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> GetMetricParam(dX, dY, ppData); }
	bool GetNativeParam(double dX, double dY, void **ppData) 
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> GetNativeParam(dX, dY, ppData); }

	void FreeTransformParam(void *pData) 
		{ if(!EnsureLoaded()) return; _ASSERTE(NULL != m_pCTF); m_pCTF -> FreeTransformParam(pData); }
	void FreeInvTransformParam(void *pData) 
		{ if(!EnsureLoaded()) return; _ASSERTE(NULL != m_pCTF); m_pCTF -> FreeInvTransformParam(pData); }
	void FreeMetricParam(void *pData) 
		{ if(!EnsureLoaded()) return; _ASSERTE(NULL != m_pCTF); m_pCTF -> FreeMetricParam(pData); }
	void FreeNativeParam(void *pData) 
		{ if(!EnsureLoaded()) return; _ASSERTE(NULL != m_pCTF); m_pCTF -> FreeNativeParam(pData); }

	bool CanConfig (void) 
		{ _ASSERTE(NULL != m_pCTF); return m_pCTF -> CanConfig(); }

private:
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	CCoordTransX *m_pCTF;
};

#endif // !defined(_CONNECTEDCTF_H__7FB5A56A_2FFD_421E_942E_03536C5C1EAC__INCLUDED_)
