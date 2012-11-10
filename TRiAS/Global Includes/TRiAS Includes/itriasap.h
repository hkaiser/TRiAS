// Zusatzinterface für OleAutoExtension ---------------------------------------
// File: ITRIASAP.H

#if !defined(_ITRIASAP_H)
#define _ITRIASAP_H

#undef INTERFACE
#define INTERFACE IGetTRiASApplication

// 89C5F584-4E2B-101B-AAE1-E7E7E7E7E7E7	
// DEFINE_GUID(IID_IGetTRiASApplication, 0x89C5F584L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

interface DECLSPEC_UUID("89C5F584-4E2B-101B-AAE1-E7E7E7E7E7E7")
IGetTRiASApplication : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IGetTRiASApplication methods
	STDMETHOD(GetApplication) (THIS_ REFIID riid, LPVOID *pIApp) PURE;
};

#endif // _ITRIASAP_H
