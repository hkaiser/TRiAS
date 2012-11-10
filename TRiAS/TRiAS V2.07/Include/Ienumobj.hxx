// Enumerator von ObjektNummern für IClassProperty ----------------------------
// File: IENUMOBJ.HXX

#if !defined(_IENUMOBJ_HXX)
#define _IENUMOBJ_HXX

#undef INTERFACE
#define INTERFACE IEnumLONG

// 0796380E-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumLONG, 0x0796380EL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IEnumLONG, IUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;
	
// *** IEnumXXX methods
	STDMETHOD (Next) (THIS_ ULONG celt, LONG *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD (Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD (Reset) (THIS) PURE;
	STDMETHOD (Clone) (THIS_ IEnumLONG **ppenm) PURE;

// *** IEnumLONG methods
	STDMETHOD_(ULONG, Count) (THIS) PURE;
};
typedef IEnumLONG *LPENUMLONG;

#undef INTERFACE
#define INTERFACE IQueryEnumLONG

// 0796385B-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IQueryEnumLONG, 0x0796385BL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IQueryEnumLONG, IUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

// *** IQueryEnumLONG methods
	STDMETHOD (QueryEnumLONG) (THIS_ IEnumLONG **ppenm) PURE;
};

#endif // _IENUMOBJ_HXX
