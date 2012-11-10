// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.07.2002 14:38:46 
//
// @doc
// @module HotSpot.h | Declaration of the <c CHotSpot> class

#if !defined(_HOTSPOT_H__6563FF58_4C41_4864_A384_C7C9A335FDF3__INCLUDED_)
#define _HOTSPOT_H__6563FF58_4C41_4864_A384_C7C9A335FDF3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

#include <triastlb.h>
#include <CSPointGeom.h>

#include "ConnectedCTF.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ConnectionPointContainer);

/////////////////////////////////////////////////////////////////////////////
// CHotSpot

class ATL_NO_VTABLE CHotSpot : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHotSpot, &CLSID_HotSpot>,
	public ITRiASNotificationSink,
	public ITRiASSysNotificationSink,
	public IHotSpot
{
public:
// Construction
	CHotSpot();
	~CHotSpot();

// Initialisation

// Operations

	DECLARE_REGISTRY_RESOURCEID(IDR_HOTSPOT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CHotSpot)
		COM_INTERFACE_ENTRY(IHotSpot)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
	END_COM_MAP()

// ITRiASNotificationSink specific functions
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

// ITRiASSysNotificationSink specific functions
	STDMETHOD(WindowsMessage) (THIS_ long hWnd, long uiMsg, long wParam, long lParam);

// Implementation
protected:
// Attributes

// Operations
	HRESULT OnViewPainted(VARIANT vData);

	HRESULT PaintTurtle(HDC hDC, CPoint const &ptPos);
	HRESULT GetActScreenPosition(CCSPointGeometry const &ptSpot, CPoint &ptPos);

// Interfaces
// IHotSpot
public:
	STDMETHOD(GetPosition)(/*[out]*/ double *pdX, /*[out]*/ double *pdY);
	STDMETHOD(SetPosition)(/*[in]*/ double dX, /*[in]*/ double dY);
	STDMETHOD(RePaint)();
	STDMETHOD(DisconnectFromServer)();
	STDMETHOD(SetExtensionSite)(IUnknown *pIXtsn);

private:
	DWORD m_dwCookie;
	DWORD m_dwCookieSys;
	WConnectionPointContainer m_Cont;

	CCSPointGeometry m_ptHotSpot;
	CComObject<CConnectedCtf> *m_pCTF;
};

#endif // !defined(_HOTSPOT_H__6563FF58_4C41_4864_A384_C7C9A335FDF3__INCLUDED_)
