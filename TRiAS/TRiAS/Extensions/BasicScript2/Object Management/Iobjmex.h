#ifndef _IOBJMEX_H
#define _IOBJMEX_H

#if _MSC_VER < 1100 && !defined(DECSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECSPEC_UUID)

#undef INTERFACE
#define INTERFACE IObjectHolder

// 079638A4-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectHolder, 0x079638A4L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638A4-3123-101C-BB62-00AA0018497C")
IObjectHolder : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjectHolder methods
	STDMETHOD(GetDelayedDel)(bool & fDelayedDel)	PURE;
	STDMETHOD(SetDelayedDel)(void)					PURE;
	STDMETHOD(SetNew)		(bool fNew)				PURE;
	STDMETHOD(GetNew)		(bool *pfNew)			PURE;
	STDMETHOD(GetStream)	(LPSTREAM*	lplpStream) PURE;
	STDMETHOD(SetStream)	(LPSTREAM	lpStream)	PURE;
	STDMETHOD(GetMoniker)	(LPMONIKER*)			PURE;
	STDMETHOD(SetMoniker)	(LPMONIKER)				PURE;
	STDMETHOD(GetName)		(BSTR *)				PURE;
	STDMETHOD(SetName)		(BSTR bstrName)			PURE;
	STDMETHOD(SetTemporaer)	(bool		fTemp)		PURE;
	STDMETHOD(GetTemporaer)	(bool	&	fTemp)		PURE;
	STDMETHOD(GetObject)	(LPUNKNOWN*	lplpUnk)	PURE;
	STDMETHOD(SetObject)	(LPUNKNOWN	lpUnk)		PURE;
	STDMETHOD(Rename)		(BSTR)					PURE;
	STDMETHOD(ReleaseObject)(VARIANT_BOOL fFullRelease)	PURE;
};

#undef INTERFACE
#define INTERFACE IObjectHolder

// 079638A5-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumUnknownExtended, 0x079638A4L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638A5-3123-101C-BB62-00AA0018497C")
IEnumUnknownExtended  : public IEnumUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IEnumUnknown methods
	STDMETHOD(Next)(ULONG celt, IUnknown ** rgelt, ULONG * pceltFetched) PURE;
	STDMETHOD(Skip)(ULONG celt)	PURE;
	STDMETHOD(Reset)(void) PURE;
	STDMETHOD(Clone)(IEnumUnknown ** ppenum) PURE;

// *** IEnumUnknownExtended methods
	STDMETHOD(Delete)(BSTR bstr)	PURE;
	STDMETHOD(Add)(IUnknown *) PURE;
	STDMETHOD(Find)(BSTR bstr, IUnknown ** pp) PURE;
	STDMETHOD_(UINT, Count) (THIS) PURE;
};

#endif // _IOBJMEX_H
