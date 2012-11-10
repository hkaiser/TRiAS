///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Smartif.Nodebug.h | SmartInterface's ohne Debugsupport

#if !defined(_SMARTIF_NODEBUG_H__F5802CB4_D772_11D1_85F2_00600875138A__INCLUDED_)
#define _SMARTIF_NODEBUG_H__F5802CB4_D772_11D1_85F2_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(__ATLCOM_H__)
	#error smartif.h requires atlcom.h to be included first
#endif 

///////////////////////////////////////////////////////////////////////////////
// mask throw() declarations
#if !defined(_USE_THROW_DECLS)
#define MASKED_THROW(x)
#define MASKED_NOTHROW()
#else
#define MASKED_THROW(x)		throw(x)
#define MASKED_NOTHROW()	throw()
#endif // !defined(_USE_THROW_DECLS)

///////////////////////////////////////////////////////////////////////////////
// 
#include <ospace/com/ComErrorMacros.h>

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse für IID_XXX

#if !defined(DefineIIDWrapper)
#define DefineIIDWrapper(Type)								\
	EXTERN_C const IID IID_I##Type;							\
	class CIID_##Type {										\
	public:													\
	static const IID & iid (void) { return IID_I##Type ; }	\
	static const IID *piid (void) { return &IID_I##Type ; }	\
	}
#define DefineIIDWrapper2(Type,_IID)						\
	EXTERN_C const IID _IID;								\
	class CIID_##Type {										\
	public:													\
	static const IID & iid (void) { return _IID; }			\
	static const IID *piid (void) { return &_IID; }			\
	}
#endif // DefineIIDWrapper

#if _MSC_VER >= 1100

///////////////////////////////////////////////////////////////////////////////
// die identische Wrapperklasse, aber mit einem template IID-Pointer
// (vielleicht versteht der compiler irgend wann mal Referenzen als 
// Templateparameter)
template <const IID *_IID>
class __CIID {
public:
	static const IID & iid (void) { return *_IID; }
	static const IID *piid (void) { return _IID; }
};
#endif // _MSC_VER < 1100

#pragma warning (disable: 4290)		// ignored C++ Exception specification

///////////////////////////////////////////////////////////////////////////////
// allgemeines Template 
#if _MSC_VER < 1100
template<class Interface, class ID, class Base>
#else
template<class Interface, class ID = __CIID<&__uuidof(Interface)>, class Base = CComPtr<Interface> >
#endif // _MSC_VER >= 1100
class __Interface : public Base
{
public:
	typedef Base base_t;
	typedef __Interface<Interface, ID, Base> self;
	typedef Interface target_t;

// 'native' copy ctors only addref
	__Interface (Interface *pIF = NULL) MASKED_NOTHROW() : base_t(pIF) {}
	__Interface (const self &rhs) MASKED_NOTHROW() : base_t((Interface *)rhs.p) {}

// 'foreign' copy ctors needs to QueryInterface
	__Interface (IUnknown *pIUnk) 
#if !defined(QI_EXCEPTION)
		: base_t()
	{	
		if (NULL != pIUnk) ::SetLastError(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
	}
#else
		MASKED_THROW(_com_error) : base_t()
	{	
		if (NULL != pIUnk) 
			THROW_FAILED_HRESULT(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
	}
#endif // !QI_EXCEPTION

// 'foreign' copy ctors needs to QueryInterface, optional no AddRef (needed in some circumstances)
	__Interface (IUnknown *pIUnk, bool fAddRef) 
#if !defined(QI_EXCEPTION)
		: base_t()
	{
		if (NULL != pIUnk) {
			::SetLastError(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p)));
			if (!fAddRef && NULL != p) p -> Release();	// überflüssiges AddRef wieder rückgängig machen
		}
	}
#else
		MASKED_THROW(_com_error) : base_t()
	{
		if (NULL != pIUnk) {
			THROW_FAILED_HRESULT(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
			if (!fAddRef) p -> Release();				// überflüssiges AddRef wieder rückgängig machen
		}
	}
#endif // !QI_EXCEPTION

// create new object
	__Interface (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL) 
#if !defined(QI_EXCEPTION)
		MASKED_NOTHROW() : base_t()
	{ 
		::SetLastError(::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p))); 
	}
#else
		MASKED_THROW(_com_error) : base_t()
	{ 
		THROW_FAILED_HRESULT(::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p)));	
	}
#endif // !!QI_EXCEPTION

// destructor auto releases
	~__Interface (void) MASKED_NOTHROW() {}

// 'native' assignment only addrefs after releasing
	__Interface &operator= (const Interface *pIF) MASKED_NOTHROW()
		{ Assign ((Interface *)pIF); return *this; }
	__Interface &operator= (const self &rhs) MASKED_NOTHROW()
		{ return operator= (rhs.p); }

// 'foreign' assignment must QueryInterface after releasing
	__Interface &operator= (const IUnknown *pIUnk)
#if !defined(QI_EXCEPTION)
		MASKED_NOTHROW()
#else
		MASKED_THROW(_com_error)
#endif // QI_EXCEPTION
	{
		if (p != pIUnk) {
			Release();
			p = NULL;
#if !defined(QI_EXCEPTION)
			if (pIUnk) 
				::SetLastError(const_cast<IUnknown *>(pIUnk) -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
#else
			if (pIUnk) 
				THROW_FAILED_HRESULT(const_cast<IUnknown *>(pIUnk) -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
#endif // !QI_EXCEPTION
		}
		return *this;
	}

#if _ATL_VER >= 0x0200
	IUnknown *Assign (IUnknown *pIUnk) MASKED_NOTHROW() { return AtlComPtrAssign(reinterpret_cast<IUnknown **>(&p), pIUnk); }	//lint --e(534)
	Interface **ppi (void) MASKED_NOTHROW() { Release(); return base_t::operator&(); }
#elif _ATL_VER >= 0x0110
	IUnknown *Assign (IUnknown *pIUnk) { return _AtlComPtrAssign(reinterpret_cast<IUnknown **>(&p), pIUnk); }
	Interface **ppi (void) { Release(); return base_t::operator&(); }
#else
	Interface **ppi (void) { return base_t::operator&(); }
#endif // _ATL_VER

#if defined(_DEBUG)
	bool IsCorrectInterface() { return (p == self((IUnknown *)p)) ? true : false; }
#endif // _DEBUG
	bool IsValid() { return !!(*this); }

// smart pointer operators
	Interface *operator-> (void) MASKED_THROW(_com_error)
		{ if (NULL == p) _com_issue_error(E_POINTER); return base_t::operator->(); }
	operator Interface * (void) const MASKED_NOTHROW() { return *((base_t *)this)/* -> base_t::operator Interface *()*/; }
	bool operator! (void) const MASKED_NOTHROW() { return NULL == p; }
	void **ppv (void) MASKED_NOTHROW() { return reinterpret_cast<void **>(ppi()); }
	IUnknown **ppu (void) MASKED_NOTHROW() { return reinterpret_cast<IUnknown **>(ppi()); }
	static const IID & GetIID (void) MASKED_NOTHROW() { return ID::iid(); }
	Interface *detach (void) MASKED_NOTHROW() { Interface *pIF = reinterpret_cast<Interface *>(p); p = NULL; return pIF; }

	self *operator& (void) MASKED_NOTHROW() { return this; }
	const self *operator& (void) const MASKED_NOTHROW() { return this; }

public:
// Dummy operatoren definieren, damit diese Klasse mit der STL verwendet werden kann
	bool operator== (const self &r1) const MASKED_NOTHROW() { return _CompareUnknown(r1) == 0; }
	bool operator< (const self &r1) const MASKED_NOTHROW() { return _CompareUnknown(r1) < 0; }

#if _MSC_VER >= 1100
// Performs the QI for the specified IID and returns it in p.
// As with all QIs, the interface will be AddRef'd.
	template<class __InterfaceType> 
	HRESULT QueryInterface(__InterfaceType& rpout) MASKED_NOTHROW()
	{
		if (p != NULL) 
			return p->QueryInterface(rpout.GetIID(), rpout.ppv());
		return E_POINTER;
	}
#endif // _MSC_VER

// explicit instantiation of an object
	HRESULT CreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();
		return ::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p));
	}
#if _ATL_VER >= 0x0200
	HRESULT LocalCreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	// erst versuchen, lokal zu erzeugen
		if (CLSCTX_INPROC_SERVER == dwCtx) {
		__Interface<IClassFactory> CF;
		HRESULT hr = _Module.GetClassObject (rClsId, IID_IClassFactory, CF.ppv());

			if (SUCCEEDED(hr)) 
				return CF -> CreateInstance (punkOuter, ID::iid(), reinterpret_cast<void **>(&p));
		}
	// dann der globale Versuch
		return ::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p));
	}
#endif // _ATL_VER >= 0x0200
	HRESULT QueryInterface(const IID& iid, void **ppout) MASKED_NOTHROW()
	{
		if (p != NULL) 
			return p->QueryInterface(iid, ppout);
		return E_POINTER;
	}

#if defined(__OSPACESTL_USED__) && !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream& stream, const self &);
	friend void os_read (os_bstream& stream, self &);
#endif // OS_POLY_FUNCTION

protected:
#if _MSC_VER >= 1100
	template<class __InterfaceType> int _CompareUnknown(const __InterfaceType &rhs) const
	{
	IUnknown *pu1, *pu2;

		if (p != NULL) {
		HRESULT hr = const_cast<Interface *>(p)->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&pu1));
		
			if (FAILED(hr)) _com_issue_error(hr); 
			pu1->Release();
		}
		else 
			pu1 = NULL;

		if (rhs) {
		HRESULT hr = const_cast<__InterfaceType &>(rhs)->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&pu2));

			if (FAILED(hr)) _com_issue_error(hr);
			pu2->Release();
		}
		else 
			pu2 = NULL;

		return pu1 - pu2;
	}
#else
	int _CompareUnknown (IUnknown *rhs) const { return p - rhs; }
#endif // _MSC_VER
};

#if defined(__OSPACESTL_USED__) && !defined(OS_NO_STREAM_SUPPORT)
///////////////////////////////////////////////////////////////////////////////
// bstream-Funktionen lediglich deklarieren, selbige müssen für jede Instanz 
// separat instanziiert werden
#if _MSC_VER < 1100

template<class Interface, class ID>
void os_write (os_bstream &, const __Interface<Interface, ID, CComPtr<Interface> > &);
template<class Interface, class ID>
void os_read (os_bstream &, __Interface<Interface, ID, CComPtr<Interface> > &);

#else // _MSC_VER < 1100

template<class Interface, class ID>
void os_write (os_bstream &, const __Interface<Interface, ID> &);
template<class Interface, class ID>
void os_read (os_bstream &, __Interface<Interface, ID> &);

#endif // _MSC_VER < 1100

OS_CLASS_T3(__Interface);
OS_STREAM_OPERATORS_T3(__Interface);
#endif // OS_POLY_FUNCTION

///////////////////////////////////////////////////////////////////////////////
// für IUnknown eigene Implementation  anbieten -------------------------------
class WUnknown : 
	public CComPtr<IUnknown> 
{
public:
	typedef CComPtr<IUnknown> base_t;

// 'native' copy ctors only addref
	WUnknown (struct IUnknown *pIF = NULL) MASKED_NOTHROW() : base_t(pIF) {}
	WUnknown (const WUnknown &rhs) MASKED_NOTHROW() : base_t(rhs.p) {}

// create new object
	WUnknown (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL) 
#if !defined(QI_EXCEPTION)
		MASKED_NOTHROW() : base_t()
	{ 
		::SetLastError(::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p))); 
	}
#else
		MASKED_THROW(HRESULT) : base_t()
	{ 
		THROW_FAILED_HRESULT(::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p))); 
	}
#endif // !!QI_EXCEPTION

// destructor auto releases
	~WUnknown (void) MASKED_NOTHROW() {}

#if _ATL_VER >= 0x0200
	IUnknown *Assign (IUnknown *pIUnk) MASKED_NOTHROW() { return AtlComPtrAssign(&p, pIUnk); }	//lint --e(534)
	IUnknown  **ppi (void) MASKED_NOTHROW() { Release(); return base_t::operator&(); }
#elif _ATL_VER == 0x0110
	IUnknown *Assign (IUnknown *pIUnk) { return _AtlComPtrAssign(&p, pIUnk); }
	IUnknown **ppi (void) { Release(); return base_t::operator&(); }
#else
	IUnknown **ppi (void) { return base_t::operator&(); }
#endif // _ATL_VER

	bool IsValid() { return !!(*this); }

// 'native' assignment only addrefs after releasing
	WUnknown &operator= (const IUnknown *pIF) MASKED_NOTHROW() { Assign((IUnknown *)pIF); return *this; }
	WUnknown &operator= (const WUnknown &rhs) MASKED_NOTHROW() { return operator= (rhs.p); }

// smart pointer operators
	IUnknown *operator-> (void) MASKED_THROW(HRESULT) 
		{ if (NULL == p) _com_issue_error(E_POINTER); return base_t::operator->(); }
	operator IUnknown * (void) const MASKED_NOTHROW() { return ((base_t *)this) -> base_t::operator IUnknown *(); }
	bool operator! (void) const MASKED_NOTHROW() { return NULL == p; }
	void **ppv (void) MASKED_NOTHROW() { return reinterpret_cast<void **>(ppi()); }
	IUnknown **ppu (void) MASKED_NOTHROW() { return ppi(); }
	REFIID GetIID (void) const MASKED_NOTHROW() { return IID_IUnknown; }
	IUnknown *detach (void) MASKED_NOTHROW() { IUnknown *pIF = p; p = NULL; return pIF; }

	WUnknown *operator& (void) MASKED_NOTHROW() { return this; }
	const WUnknown *operator& (void) const MASKED_NOTHROW() { return this; }

// Dummy operatoren definieren, damit diese Klasse mit der STL verwendet werden kann
	bool operator== (const WUnknown &r1) const MASKED_NOTHROW() { return p == r1.p; }
	bool operator< (const WUnknown &r1) const MASKED_NOTHROW() { return false; }

#if _MSC_VER >= 1100
// Performs the QI for the IID of the argument and returns it in p.
// As with all QIs, the interface will be AddRef'd.
	template<class __InterfaceType> 
	HRESULT QueryInterface(__InterfaceType*& rpout) MASKED_NOTHROW()
	{
		if (p != NULL) 
			return p->QueryInterface(rpout.GetIID(), reinterpret_cast<void**>(&rpout));
	}
#endif // _MSC_VER

// explicit instantiation of an object
	HRESULT CreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();
		return ::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p));
	}
#if _ATL_VER >= 0x0200
	HRESULT LocalCreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	// erst versuchen, lokal zu erzeugen
		if (CLSCTX_INPROC_SERVER == dwCtx) {
		__Interface<IClassFactory> CF;
		HRESULT hr = _Module.GetClassObject (rClsId, IID_IClassFactory, CF.ppv());

			if (SUCCEEDED(hr)) 
				return CF -> CreateInstance (punkOuter, IID_IUnknown, reinterpret_cast<void **>(&p));
		}
	// dann der globale Versuch
		return ::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p));
	}
#endif // _ATL_VER >= 0x0200
	HRESULT QueryInterface(const IID& iid, void **ppout) MASKED_NOTHROW()
	{
		if (p != NULL) 
			return p->QueryInterface(iid, ppout);
		return E_NOINTERFACE;
	}
};

///////////////////////////////////////////////////////////////////////////////
// define macro for QueryInterface-style arguments 
#define IID_PPV(rIF)		(rIF).GetIID(),(rIF).ppv()

///////////////////////////////////////////////////////////////////////////////
// InterfaceWrapper für ein beliebiges Interface (nicht IUnknown)
//
#if _MSC_VER < 1100

#define DefineSmartInterface(IF)							\
	DefineIIDWrapper(IF);									\
	typedef __Interface<I##IF,CIID_##IF,CComPtr<I##IF> > W##IF;
#define DefineSmartInterface2(IF,IID)						\
	DefineIIDWrapper2(IF,IID);								\
	typedef __Interface<IF,CIID_##IF,CComPtr<IF> > W##IF;

#else // _MSC_VER < 1100

#define DefineSmartInterface(IF)							\
	typedef __Interface<I##IF,__CIID<&__uuidof(I##IF)>,CComPtr<I##IF> > W##IF;
#define DefineSmartInterface2(IF,IID)						\
	typedef __Interface<IF,__CIID<&__uuidof(IF)>,CComPtr<IF> > W##IF;

#define DefineSmartInterfaceEx(IF)							\
	DefineIIDWrapper(IF);									\
	typedef __Interface<I##IF,CIID_##IF,CComPtr<I##IF> > W##IF;
#define DefineSmartInterfaceEx2(IF,IID)						\
	DefineIIDWrapper2(IF,IID);								\
	typedef __Interface<IF,CIID_##IF,CComPtr<IF> > W##IF;

#endif // _MSC_VER < 1100

#endif // !defined(_SMARTIF_NODEBUG_H__F5802CB4_D772_11D1_85F2_00600875138A__INCLUDED_)
