// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.07.2002 14:40:20 
//
// @doc
// @module HotSpot.cpp | Definition of the <c CHotSpot> class

#include "stdafx.h"
#include "VidCtrl.h"

#include <Com/SafeArray.h>

#include "HotSpot.h"

///////////////////////////////////////////////////////////////////////////////
// 
#define ID_TRIAS_VIEW	0xE900		// AFX_PANE_FIRST

///////////////////////////////////////////////////////////////////////////////
// SmartIF's, SAFEARRAY-Zugriff
DeclareSafeLock(long);	
DefineSmartInterface(TriasXtensionSite);

/////////////////////////////////////////////////////////////////////////////
// CHotSpot

// Constructor
CHotSpot::CHotSpot() :
	m_dwCookie(0), m_dwCookieSys(0), m_pCTF(NULL)
{
}

// Destructor
CHotSpot::~CHotSpot()
{
	_ASSERTE(0 == m_dwCookie);
	_ASSERTE(0 == m_dwCookieSys);
	_ASSERTE(NULL == m_pCTF);
}

/////////////////////////////////////////////////////////////////////////////
// IHotSpot

STDMETHODIMP CHotSpot::SetExtensionSite(IUnknown *pSite)
{
	if (NULL != pSite) {
	// Koordinatensystemverwaltung
	CComObject<CConnectedCtf> *pCTF = NULL;

		_ASSERTE(NULL == m_pCTF);
		RETURN_FAILED_HRESULT(CComObject<CConnectedCtf>::CreateInstance(&pCTF));

	WUnknown Unk (pCTF);		// pending AddRef
	WTriasXtensionSite Site;

		RETURN_FAILED_HRESULT(pSite -> QueryInterface(Site.ppi()));
		RETURN_FAILED_HRESULT(m_pCTF->SetXtsnSite(Site));

	// bei TRiAS anmelden
		_ASSERTE(0 == m_dwCookie);
		RETURN_FAILED_HRESULT(pSite -> QueryInterface(m_Cont.ppi()));
		RETURN_FAILED_HRESULT(AtlAdvise (m_Cont, GetUnknown(), 
			__uuidof(ITRiASNotificationSink), &m_dwCookie));
			
	// Alle WindowsMessages auch hier vorbeischicken	
		_ASSERTE(0 == m_dwCookieSys);
		RETURN_FAILED_HRESULT(AtlAdvise (m_Cont, GetUnknown(), 
			__uuidof(ITRiASSysNotificationSink), &m_dwCookieSys));

		(m_pCTF = pCTF) -> AddRef();
	} 
	else {
		RETURN_FAILED_HRESULT(DisconnectFromServer());
	}
	return S_OK;
}

STDMETHODIMP CHotSpot::DisconnectFromServer()
{
	if (m_Cont.IsValid()) {
	// normale Notifikationen abmelden
		_ASSERTE(0 != m_dwCookie);
		RETURN_FAILED_HRESULT(AtlUnadvise (m_Cont, __uuidof(ITRiASNotificationSink), 
			m_dwCookie));
		m_dwCookie = 0L;

	// WindowsMessages abmelden
		_ASSERTE(0 != m_dwCookieSys);
		RETURN_FAILED_HRESULT(AtlUnadvise (m_Cont, __uuidof(ITRiASSysNotificationSink), 
			m_dwCookieSys));
		m_dwCookieSys = 0L;

	// Koordinatensystemverwaltung ausknipsen
		_ASSERTE(NULL != m_pCTF);

		RETURN_FAILED_HRESULT(m_pCTF->SetXtsnSite(NULL));
		m_pCTF -> Release();
		m_pCTF = NULL;

		m_Cont.Assign(NULL);	// Release()
	}

	_ASSERTE(0 == m_dwCookie);
	_ASSERTE(0 == m_dwCookieSys);
	_ASSERTE(NULL == m_pCTF);

	return S_OK;
}

STDMETHODIMP CHotSpot::RePaint()
{
CPoint ptPos;

	RETURN_FAILED_HRESULT(GetActScreenPosition(m_ptHotSpot, ptPos));
	RETURN_FAILED_HRESULT(PaintTurtle(NULL, ptPos));
	return S_OK;
}

STDMETHODIMP CHotSpot::SetPosition(double dX, double dY)
{
	_ASSERTE(m_ptHotSpot.IsValid());
	RETURN_FAILED_HRESULT(m_ptHotSpot.put_X(dX));
	RETURN_FAILED_HRESULT(m_ptHotSpot.put_Y(dY));
	return S_OK;
}

STDMETHODIMP CHotSpot::GetPosition(double *pdX, double *pdY)
{
	if (NULL == pdX || NULL == pdY)
		return E_POINTER;

	_ASSERTE(m_ptHotSpot.IsValid());
	RETURN_FAILED_HRESULT(m_ptHotSpot.get_X(pdX));
	RETURN_FAILED_HRESULT(m_ptHotSpot.get_Y(pdY));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASNotificationSink specific functions
STDMETHODIMP CHotSpot::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisconnectFromServer();
		break;
	}
	return S_OK;
}

STDMETHODIMP CHotSpot::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	return S_OK;
}

STDMETHODIMP CHotSpot::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	switch (ve) {
	case GEOVIEWEVT_ViewPainted:	// PAINTTOPLAYER
		return OnViewPainted(vData);
	}
	return S_OK;
}

STDMETHODIMP CHotSpot::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return S_OK;
}

STDMETHODIMP CHotSpot::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return S_OK;
}

STDMETHODIMP CHotSpot::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return S_OK;
}

STDMETHODIMP CHotSpot::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return S_OK;
}

STDMETHODIMP CHotSpot::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASSysNotificationSink specific functions

STDMETHODIMP CHotSpot::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// NotifikationsRoutinen
HRESULT CHotSpot::OnViewPainted(VARIANT vData)
{
	_ASSERTE(V_VT(&vData) == (VT_ARRAY|VT_I4));
	_ASSERTE(NULL != V_ARRAY(&vData));

CSafeArray sa (VT_I4, V_ARRAY(&vData), true);		// autodetach!
CLocklong l(sa);

HDC hDC = reinterpret_cast<HDC>(*l);
HDC hDCTarget = reinterpret_cast<HDC>(*(l+1));

	if (hDC != hDCTarget || DT_RASPRINTER == GetDeviceCaps(hDC, TECHNOLOGY))
		return S_OK;

	_ASSERTE(NULL != hDC);

CPoint ptPos;

	RETURN_FAILED_HRESULT(GetActScreenPosition(m_ptHotSpot, ptPos));
	RETURN_FAILED_HRESULT(PaintTurtle(hDC, ptPos));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Routinen, die das Zeichnen erledigen
namespace {
// Hilfsklasse für den Fall, daß kein hDC gegeben ist
	class CManagedDC :
		public CDCHandle
	{
	public:
		CManagedDC(HDC hDC, HWND hWnd) : 
			CDCHandle(hDC), m_hWnd(hWnd), m_fAutoDetach(NULL != hDC)
		{
			if (!m_fAutoDetach) 
				this->m_hDC = GetDC(hWnd);
		}
		~CManagedDC()
		{
			if (!m_fAutoDetach)
				ReleaseDC(m_hWnd, Detach());
		}

	private:
		HWND m_hWnd;
		bool m_fAutoDetach;
	};
}

HRESULT CHotSpot::PaintTurtle(HDC hDC, CPoint const &ptPos)
{
CManagedDC hDCDst(hDC, GetDlgItem(__hWndM, ID_TRIAS_VIEW));

	_ASSERTE(NULL != hDCDst.m_hDC);

CPen redPen;
CPenHandle hOldPen = redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));

	hDCDst.SelectPen(redPen);
	
	hDCDst.MoveTo(ptPos.x-25, ptPos.y);
	hDCDst.LineTo(ptPos.x-5, ptPos.y);

	hDCDst.MoveTo(ptPos.x+5, ptPos.y);
	hDCDst.LineTo(ptPos.x+25, ptPos.y);

	hDCDst.MoveTo(ptPos.x, ptPos.y+25);
	hDCDst.LineTo(ptPos.x, ptPos.y+5);

	hDCDst.MoveTo(ptPos.x, ptPos.y-5);
	hDCDst.LineTo(ptPos.x, ptPos.y-25);

	hDCDst.SetPixel(ptPos, RGB(255, 0, 0));

	hDCDst.SelectPen(hOldPen);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Aktuelle Position des Positionskreuzes berechnen
inline 
HRESULT OCtoDC (KoOrd lX, KoOrd lY, CPoint &rPt)
{
COORDCONVERT CT;
long Koords[2] = { lX, lY };

	CT.lpPt = &rPt;
	CT.lpPkt = Koords;
	return DEX_OCtoDC(CT) ? S_OK : E_UNEXPECTED;
}

HRESULT CHotSpot::GetActScreenPosition(CCSPointGeometry const &ptSpot, CPoint &ptPos)
{
	_ASSERTE(NULL != m_pCTF);

double dX, dY;
KoOrd lX, lY;

	RETURN_FAILED_HRESULT(ptSpot.get_X(&dX));
	RETURN_FAILED_HRESULT(ptSpot.get_Y(&dY));
	RETURN_FAILED_HRESULT(m_pCTF -> InvTransform(&dX, &dY));
	RETURN_FAILED_HRESULT(m_pCTF -> Scale(dX, dY, &lX, &lY));
	RETURN_FAILED_HRESULT(OCtoDC(lX, lY, ptPos));
	return S_OK;
}

