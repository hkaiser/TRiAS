// Zusätzliche Interface für IEnumLONG, über welches geprüft werden kann, ob
// ein LONG enthalten ist oder nicht
// File: IFNDLONG.H

#if !defined(_IFNDLONG_H)
#define _IFNDLONG_H

#undef INTERFACE
#define INTERFACE IFindLONG

// 07963885-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IFindLONG, 0x07963885L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
MIDL_INTERFACE("07963885-3123-101C-BB62-00AA0018497C")
IFindLONG : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IFindLONG specific functions ***
	STDMETHOD(HasLONG) (THIS_ LONG lFind) PURE;
};

#endif // _IFNDLONG_H
