// Zusätzliche Interface für IEnumLONG, über welches GeoObjects-Collection des
// Automation-Interfaces verfügbar wird
// File: IGEOOBJS.H

#if !defined(_IGEOOBJS_H)
#define _IGEOOBJS_H

#undef INTERFACE
#define INTERFACE IQueryGeoObjects

// 079638C7-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IQueryGeoObjects, 0x079638C7L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IQueryGeoObjects, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IQueryGeoObjects specific functions ***
	STDMETHOD(GetGeoObjects) (THIS_ _DGeoObjects **ppIGeoObjs) PURE;
};

#endif // _IGEOOBJS_H
