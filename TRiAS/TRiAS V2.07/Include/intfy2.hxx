// NotificationSink, welches über ConnectionPoint-Mechanismus an OLEAUTO
// angebunden werden kann
// File: INTFY2.HXX

#if !defined(_INTFY2_HXX)
#define _INTFY2_HXX

// #include <triasnfy.h>		// Definition der enums

#undef INTERFACE
#define INTERFACE INotificationSink2

// 89C5F583-4E2B-101B-AAE1-E7E7E7E7E7E7	
// DEFINE_GUID(IID_NotificationSink2, 0x89C5F583L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
DECLARE_INTERFACE_(INotificationSink2, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** INotificationSink2 members
	STDMETHOD_(ULONG, ServerEvent)(THIS_ SERVEREVT se) PURE;
	STDMETHOD_(ULONG, ProjectEvent)(THIS_ PROJECTEVT pe, LPCTSTR pProj) PURE;
	STDMETHOD_(ULONG, GeoViewEvent)(THIS_ GEOVIEWEVT ve, LPCTSTR pView) PURE;
	STDMETHOD_(ULONG, GeoClassEvent)(THIS_ GEOCLASSEVT ce, ULONG ulIdent) PURE;
	STDMETHOD_(ULONG, GeoObjectEvent)(THIS_ GEOOBJECTEVT oe, LONG lONr) PURE;
	STDMETHOD_(ULONG, GeoFeatureEvent)(THIS_ GEOFEATUREEVT fe, ULONG ulMCode) PURE;
	STDMETHOD_(ULONG, GeoRelationEvent)(THIS_ GEORELATIONEVT re, ULONG ulRCode) PURE;
	STDMETHOD_(ULONG, ObjectWindowEvent)(THIS_ OBJWNDEVT oe, HWND hORWnd) PURE;

	STDMETHOD_(ULONG, MenuInitEvent)(THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd) PURE;
	STDMETHOD_(ULONG, MenuSelectEvent)(THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd) PURE;
	STDMETHOD_(ULONG, MenuCommandEvent)(THIS_ WPARAM wParam, HWND hWnd) PURE;
};
typedef INotificationSink2 * LPNOTIFICATIONSINK2;

#endif // _INTFY2_HXX
