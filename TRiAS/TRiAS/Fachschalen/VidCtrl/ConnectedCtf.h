// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.07.2002 14:04:36 
//
// @doc
// @module ConnectedCtf.h | Connected CTF for maintenance of coordinate system 
// configuration

#if !defined(_CONNECTEDCTF_H__EC208427_F10D_44DA_B238_984D4B2EFAEF__INCLUDED_)
#define _CONNECTEDCTF_H__EC208427_F10D_44DA_B238_984D4B2EFAEF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <triastlb.h>
#include <ctfxmfc.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ConnectionPointContainer);

class CConnectedCtf :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnectedCtf, &CLSID_ConnectedCTF>,
	public ITRiASNotificationSink
{
public:
	CConnectedCtf() { m_pCTF = NULL; }
	~CConnectedCtf() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CConnectedCtf)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CConnectedCtf)
	DECLARE_NO_REGISTRY();

	HRESULT FinalConstruct(void);

public:
// ITRiASNotificationSink specific functions
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

	HRESULT SetXtsnSite (ITriasXtensionSite *pSite);
	HRESULT DisConnectFromServer();

public:
	bool LoadCTF (void);
	void ReleaseCTF (void);
	bool EnsureLoaded(void);

	bool Transform (double *pX, double *pY)
	{ 
		if(!EnsureLoaded()) return false; 
		_ASSERTE(NULL != m_pCTF); 
		return m_pCTF -> Transform(pX, pY); 
	}
	bool InvTransform (double *pX, double *pY)
	{ 
		if(!EnsureLoaded()) return false; 
		_ASSERTE(NULL != m_pCTF); 
		return m_pCTF -> InvTransform(pX, pY); 
	}
	bool Scale (const double &rX, const double &rY, KoOrd *pdX, KoOrd *pdY)
	{ 
		if(!EnsureLoaded()) return false; 
		_ASSERTE(NULL != m_pCTF); 
		return m_pCTF -> Scale (rX, rY, pdX, pdY); 
	}
	bool UnScale (const KoOrd &rX, const KoOrd &rY, double *pdX, double *pdY)
	{ 
		if(!EnsureLoaded()) return false; 
		_ASSERTE(NULL != m_pCTF); 
		return m_pCTF -> UnScale (rX, rY, pdX, pdY); 
	}

	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransToStringEx (dX, dY, isX, pBuffer, iLen); }
	double CoordTransDistance (const DoublePair *pDP1, const DoublePair *pDP2)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransDistance (pDP1, pDP2); }
	char *CoordTransDescription (char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; _ASSERTE(NULL != m_pCTF); return m_pCTF -> CoordTransDescription (pBuffer, iLen); }

	bool CanConfig (void) 
		{ _ASSERTE(NULL != m_pCTF); return m_pCTF -> CanConfig(); }

private:
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	CCoordTransX *m_pCTF;
};

#endif // !defined(_CONNECTEDCTF_H__EC208427_F10D_44DA_B238_984D4B2EFAEF__INCLUDED_)
