// Notifikationen weiterleiten ------------------------------------------------
// File: APPNTFY.CXX

#include "precomp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

LRESULT CTriasApp :: OnServerEvent (SERVEREVT se)
{
#if _ATL_VER >= 0x200
	return LRESULT(Fire_ServerEvent(se));
#else
	return LRESULT(m_cp.ServerEvent(se));
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnProjectEvent (PROJECTEVT rgPE, HPROJECT hPr)
{
char cbBuffer[_MAX_PATH];

	if (DEX_GetActiveProject (cbBuffer) == NULL) 
		return LRESULT(false);

#if _ATL_VER >= 0x200
	return Fire_ProjectEvent (rgPE, cbBuffer);
#else
	return m_cp.ProjectEvent (rgPE, cbBuffer);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnProjectClosedEvent (LPCSTR pName)
{
#if _ATL_VER >= 0x200
	return Fire_ProjectEvent (PROJECTEVT_ProjectClosed, pName);
#else
	return m_cp.ProjectEvent (PROJECTEVT_ProjectClosed, pName);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnViewEvent (GEOVIEWEVT ve, LPCTSTR pView)
{
#if _ATL_VER >= 0x200
	return Fire_GeoViewEvent (ve, pView);
#else
	return m_cp.GeoViewEvent (ve, pView);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnClassEvent (GEOCLASSEVT ce, ULONG ulIdent)
{
#if _ATL_VER >= 0x200
	return Fire_GeoClassEvent (ce, ulIdent);
#else
	return m_cp.GeoClassEvent (ce, ulIdent);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnObjectEvent (GEOOBJECTEVT oe, LONG lONr)
{
#if _ATL_VER >= 0x200
	return Fire_GeoObjectEvent (oe, lONr);
#else
	return m_cp.GeoObjectEvent (oe, lONr);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnFeatureEvent (GEOFEATUREEVT fe, ULONG ulMCode)
{
#if _ATL_VER >= 0x200
	return Fire_GeoFeatureEvent (fe, ulMCode);
#else
	return m_cp.GeoFeatureEvent (fe, ulMCode);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnRelationEvent (GEORELATIONEVT re, ULONG ulRCode)
{
#if _ATL_VER >= 0x200
	return Fire_GeoRelationEvent (re, ulRCode);
#else
	return m_cp.GeoRelationEvent (re, ulRCode);
#endif // _ATL_VER
}

LRESULT CTriasApp :: OnObjectWindowEvent (OBJWNDEVT oe, HWND hORWnd)
{
#if _ATL_VER >= 0x200
	return Fire_ObjectWindowEvent (oe, hORWnd);
#else
	return m_cp.ObjectWindowEvent (oe, hORWnd);
#endif // _ATL_VER
}

