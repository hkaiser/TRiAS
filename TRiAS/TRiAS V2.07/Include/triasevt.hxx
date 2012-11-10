// Interface, über welches Notifikationen von TRiAS weitergeleitet werden -----
// File: TRIASEVT.HXX

#if !defined(_TRIASEVT_HXX)
#define _TRIASEVT_HXX

#include <triasnfy.h>				// Deklaration der EventTypen 

// Interface, welches alle möglichen Events von TRiAS verarbeitet -------------
// 07963807-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasEvents, 0x07963807L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

#undef INTERFACE
#define INTERFACE ITriasEvents
DECLARE_INTERFACE_(ITriasEvents, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITriasEvents methods
	STDMETHOD_(LRESULT, OnServerEvent) (THIS_ SERVEREVT) PURE;
	STDMETHOD_(LRESULT, OnProjectEvent) (THIS_ PROJECTEVT, BSTR bProj) PURE;
	STDMETHOD_(LRESULT, OnViewEvent) (THIS_ VIEWEVT, BSTR bView) PURE;
	STDMETHOD_(LRESULT, OnGeoClassEvent) (THIS_ GEOCLASSEVT, ULONG ulCls) PURE;
	STDMETHOD_(LRESULT, OnGeoObjectEvent) (THIS_ GEOOBJECTEVT, LONG lONr) PURE;
	STDMETHOD_(LRESULT, OnGeoFeatureEvent) (THIS_ GEOFEATUREEVT, LONG lMCode) PURE;
};
typedef ITriasEvents *LPTRIASEVENTS;


#endif // _TRIASEVT_HXX

