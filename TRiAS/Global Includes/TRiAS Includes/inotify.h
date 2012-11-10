// Connectionpoint, der von TRiAS direkt unterstützt wird ---------------------
// File: INOTIFY.H

#if !defined(_INOTIFY_H)
#define _INOTIFY_H

#include <triasnfy.h>		// Definition der enums

#undef INTERFACE
#define INTERFACE ITRiASNotificationSink

// 0796385A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASNotificationSink, 0x0796385AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASNotificationSink, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se) PURE;
	STDMETHOD(ProjectEvent) (THIS_ PROJECTEVT pe, LPCTSTR pProj) PURE;
	STDMETHOD(GeoViewEvent) (THIS_ GEOVIEWEVT ve, void *pView) PURE;
	STDMETHOD(GeoClassEvent) (THIS_ GEOCLASSEVT ce, ULONG ulIdent) PURE;
	STDMETHOD(GeoObjectEvent) (THIS_ GEOOBJECTEVT oe, LONG lONr) PURE;
	STDMETHOD(GeoFeatureEvent) (THIS_ GEOFEATUREEVT fe, ULONG ulMCode) PURE;
	STDMETHOD(GeoRelationEvent) (THIS_ GEORELATIONEVT re, ULONG ulRCode) PURE;
};

#undef INTERFACE
#define INTERFACE ITRiASSysNotificationSink

// 0796386E-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASSysNotificationSink, 0x0796386EL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASSysNotificationSink, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASSysNotificationSink specific functions ***
	STDMETHOD(WindowsMessage) (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) PURE;
};

#endif // _INOTIFY_H
