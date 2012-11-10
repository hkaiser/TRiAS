///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Smartif.Debug.h | SmartInterface's mit Debug-Support

#if !defined(_SMARTIF_DEBUG_H__F5802CB3_D772_11D1_85F2_00600875138A__INCLUDED_)
#define _SMARTIF_DEBUG_H__F5802CB3_D772_11D1_85F2_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(__ATLCOM_H__)
	#error smartif.h requires atlcom.h to be included first
#endif 
#if !defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)
	#error Configuration error regarding '_ATLX_DEBUG_REFCOUNT_WALKSTACK' preprocessor constant!
#endif // !_ATLX_DEBUG_REFCOUNT_WALKSTACK

#include <ospace/com/ComErrorMacros.h>
#include <Atl/AtlDebug.h>		// support for _ATLX_DEBUG_REFCOUNT_WALKSTACK

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse für IID_XXX

#if _MSC_VER < 1100
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
#else
#define DefineIIDWrapper(Type)
#define DefineIIDWrapper2(Type,_IID)

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
template<class Interface, class ID = __CIID<&__uuidof(Interface)>, class Base = CComPtrDebug<Interface, __CIID<&__uuidof(Interface)> > >
#endif // _MSC_VER >= 1100
class __Interface : public Base
{
public:
	typedef Base base_t;
	typedef __Interface<Interface, ID, Base> self;
	typedef Interface target_t;

// 'native' copy ctors only addref
	__Interface (Interface *pIF = NULL) throw () : base_t(pIF) {}
	__Interface (const self &rhs) throw () : base_t((Interface *)rhs.p) {}

// 'foreign' copy ctors needs to QueryInterface
	__Interface (IUnknown *pIUnk) 
#if !defined(QI_EXCEPTION)
		: base_t()
	{	
		if (NULL != pIUnk) {
			::SetLastError(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
			if (SUCCEEDED(GetLastHRESULT())) WalkStackOnAddRef();
		}
	}
#else
		throw(_com_error) : base_t()
	{	
		if (NULL != pIUnk) {
			THROW_FAILED_HRESULT(pIUnk -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
			WalkStackOnAddRef();
		}
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
		throw(_com_error) : base_t()
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
		throw() : base_t()
	{ 
		::SetLastError(::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p))); 
		if (SUCCEEDED(GetLastHRESULT())) WalkStackOnAddRef();
	}
#else
		throw(_com_error) : base_t()
	{ 
		THROW_FAILED_HRESULT(::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p)));	
		WalkStackOnAddRef();
	}
#endif // !!QI_EXCEPTION

// destructor auto releases
	~__Interface (void) throw() {}

// 'native' assignment only addrefs after releasing
	__Interface &operator= (const Interface *pIF) throw()
		{ Assign ((Interface *)pIF); return *this; }
	__Interface &operator= (const self &rhs) throw()
		{ return operator= (rhs.p); }

// 'foreign' assignment must QueryInterface after releasing
	__Interface &operator= (const IUnknown *pIUnk)
#if !defined(QI_EXCEPTION)
		throw()
#else
		throw(_com_error)
#endif // QI_EXCEPTION
	{
		if (p != pIUnk) {
			Release();
			p = NULL;
#if !defined(QI_EXCEPTION)
			if (pIUnk) {
				::SetLastError(const_cast<IUnknown *>(pIUnk) -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
				if (SUCCEEDED(GetLastHRESULT())) WalkStackOnAddRef();
			}
#else
			if (pIUnk) {
				THROW_FAILED_HRESULT(const_cast<IUnknown *>(pIUnk) -> QueryInterface (ID::iid(), reinterpret_cast<void **>(&p))); 
				WalkStackOnAddRef();
			}
#endif // !QI_EXCEPTION
		}
		return *this;
	}

#if _ATL_VER >= 0x0200
	IUnknown *Assign (IUnknown *pIUnk) throw() { return AtlComPtrAssignStackWalk(reinterpret_cast<IUnknown **>(&p), pIUnk); }
	Interface **ppi (void) throw() { Release(); WalkStackOnAddRef(true); return base_t::operator&(); }
#else
	#error Debugsupport for old versions of ATL not supported!
#endif // _ATL_VER

#if defined(_DEBUG)
	bool IsCorrectInterface() { return (p == self((IUnknown *)p)) ? true : false; }
#endif // _DEBUG
	bool IsValid() { return !!(*this); }

// smart pointer operators
	Interface *operator-> (void) throw(_com_error)
		{ if (NULL == p) _com_issue_error(E_POINTER); return base_t::operator->(); }
	operator Interface * (void) const throw() { return ((base_t *)this) -> base_t::operator Interface *(); }
	bool operator! (void) const throw() { return NULL == p; }
	void **ppv (void) throw() { return reinterpret_cast<void **>(ppi()); }
	IUnknown **ppu (void) throw() { return reinterpret_cast<IUnknown **>(ppi()); }
	static const IID & GetIID (void) throw() { return ID::iid(); }
	Interface *detach (void) throw() { Interface *pIF = reinterpret_cast<Interface *>(p); p = NULL; WalkStackOnRelease(); return pIF; }
	void Release() { WalkStackOnRelease(); base_t::Release(); }

	self *operator& (void) throw() { return this; }
	const self *operator& (void) const throw() { return this; }

public:
// Dummy operatoren definieren, damit diese Klasse mit der STL verwendet werden kann
	bool operator== (const self &r1) const throw() { return _CompareUnknown(r1) == 0; }
	bool operator< (const self &r1) const throw() { return _CompareUnknown(r1) < 0; }

#if _MSC_VER >= 1100
// Performs the QI for the specified IID and returns it in p.
// As with all QIs, the interface will be AddRef'd.
	template<class __InterfaceType> 
	HRESULT QueryInterface(__InterfaceType& rpout) throw()
	{
		if (p != NULL) {
			if (SUCCEEDED(p->QueryInterface(rpout.GetIID(), rpout.ppv()))) {
				WalkStackOnAddRef();
				return S_OK;
			}
		}
		return E_POINTER;
	}
#endif // _MSC_VER

// explicit instantiation of an object
	HRESULT CreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	HRESULT hr = ::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p));

		if (SUCCEEDED(hr)) {
			WalkStackOnAddRef();
			return S_OK;
		}
		return hr;
	}
#if _ATL_VER >= 0x0200
	HRESULT LocalCreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	// erst versuchen, lokal zu erzeugen
	HRESULT hr = E_FAIL;

		if (CLSCTX_INPROC_SERVER == dwCtx) {
		__Interface<IClassFactory> CF;
		
			hr = _Module.GetClassObject (rClsId, IID_IClassFactory, CF.ppv());
			if (SUCCEEDED(hr)) {
				hr = CF -> CreateInstance (punkOuter, ID::iid(), reinterpret_cast<void **>(&p));
				if (SUCCEEDED(hr)) {
					WalkStackOnAddRef();
					return S_OK;
				}
			}
		}

	// dann der globale Versuch
		hr = ::CoCreateInstance(rClsId, punkOuter, dwCtx, ID::iid(), reinterpret_cast<void **>(&p));
		if (SUCCEEDED(hr)) {
			WalkStackOnAddRef();
			return S_OK;
		}
		return hr;
	}
#endif // _ATL_VER >= 0x0200
	HRESULT QueryInterface(const IID& iid, void **ppout) throw()
	{
		if (p != NULL) {
			if (SUCCEEDED(p->QueryInterface(iid, ppout))) {
				WalkStackOnAddRef();
				return S_OK;
			}
		}
		return E_POINTER;
	}

#if defined(__OSPACESTL_USED__) && !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream& stream, const self &);
	friend void os_read (os_bstream& stream, self &);
#endif // OS_POLY_FUNCTION

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
template<class Interface, class ID>
void os_write (os_bstream &, const __Interface<Interface, ID> &);

template<class Interface, class ID>
void os_read (os_bstream &, __Interface<Interface, ID> &);

OS_CLASS_T2(__Interface);
OS_STREAM_OPERATORS_T2(__Interface);
#endif // OS_POLY_FUNCTION

///////////////////////////////////////////////////////////////////////////////
// für IUnknown eigene Implementation  anbieten -------------------------------
class WUnknown : 
	public CComPtrDebug<IUnknown, __CIID<&IID_IUnknown> > 
{
public:
	typedef CComPtrDebug<IUnknown, __CIID<&IID_IUnknown> > base_t;

// 'native' copy ctors only addref
	WUnknown (struct IUnknown *pIF = NULL) throw() : base_t(pIF) {}
	WUnknown (const WUnknown &rhs) throw() : base_t(rhs.p) {}

// create new object
	WUnknown (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL) 
#if !defined(QI_EXCEPTION)
		throw() : base_t()
	{ 
		::SetLastError(::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p))); 
		if (SUCCEEDED(GetLastHRESULT())) WalkStackOnAddRef();
	}
#else
		throw(HRESULT) : base_t()
	{ 
		THROW_FAILED_HRESULT(::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p))); 
		WalkStackOnAddRef();
	}
#endif // !!QI_EXCEPTION

// destructor auto releases
	~WUnknown (void) throw() {}

#if _ATL_VER >= 0x0200
	IUnknown *Assign (IUnknown *pIUnk) throw() { return AtlComPtrAssignStackWalk(&p, pIUnk); }
	IUnknown  **ppi (void) throw() { Release(); WalkStackOnAddRef(true); return base_t::operator&(); }
#else
	#error Debugsupport for old versions of ATL not supported!
#endif // _ATL_VER

	bool IsValid() { return !!(*this); }

// 'native' assignment only addrefs after releasing
	WUnknown &operator= (const IUnknown *pIF) throw() { Assign((IUnknown *)pIF); return *this; }
	WUnknown &operator= (const WUnknown &rhs) throw() { return operator= (rhs.p); }

// smart pointer operators
	IUnknown *operator-> (void) throw(HRESULT) 
		{ if (NULL == p) _com_issue_error(E_POINTER); return base_t::operator->(); }
	operator IUnknown * (void) const throw() { return ((base_t *)this) -> base_t::operator IUnknown *(); }
	bool operator! (void) const throw() { return NULL == p; }
	void **ppv (void) throw() { return reinterpret_cast<void **>(ppi()); }
	IUnknown **ppu (void) throw() { return ppi(); }
	REFIID GetIID (void) const throw() { return IID_IUnknown; }
	IUnknown *detach (void) throw() { IUnknown *pIF = p; p = NULL; WalkStackOnRelease(); return pIF; }
	void Release() { WalkStackOnRelease(); base_t::Release(); }

	WUnknown *operator& (void) throw() { return this; }
	const WUnknown *operator& (void) const throw() { return this; }

// Dummy operatoren definieren, damit diese Klasse mit der STL verwendet werden kann
	bool operator== (const WUnknown &r1) const throw() { return p == r1.p; }
	bool operator< (const WUnknown &r1) const throw() { return p < r1.p; }

#if _MSC_VER >= 1100
// Performs the QI for the specified IID and returns it in p.
// As with all QIs, the interface will be AddRef'd.
	template<class __InterfaceType> 
	HRESULT QueryInterface(const IID& iid, __InterfaceType*& rpout) throw()
	{
		if (p != NULL) {
			if (SUCCEEDED(p->QueryInterface(iid, reinterpret_cast<void**>(&rpout)))) {
				WalkStackOnAddRef();
				return S_OK;
			}
		}
		return E_POINTER;
	}

// Performs the QI for the specified IID and returns it in p.
// As with all QIs, the interface will be AddRef'd.
	template<class __InterfaceType> 
	HRESULT QueryInterface(const IID& iid, __InterfaceType** p) throw()
	{
		return QueryInterface(iid, *p);
	}
#endif // _MSC_VER

// explicit instantiation of an object
	HRESULT CreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	HRESULT hr = ::CoCreateInstance(rClsId, punkOuter, dwCtx, IID_IUnknown, reinterpret_cast<void **>(&p));

		if (SUCCEEDED(hr)) {
			WalkStackOnAddRef();
			return S_OK;
		}
		return hr;
	}
#if _ATL_VER >= 0x0200
	HRESULT LocalCreateInstance (REFCLSID rClsId, DWORD dwCtx = CLSCTX_INPROC_SERVER, IUnknown *punkOuter = NULL)
	{
		Release();

	// erst versuchen, lokal zu erzeugen
	HRESULT hr = E_FAIL;

		if (CLSCTX_INPROC_SERVER == dwCtx) {
		__Interface<IClassFactory> CF;
		
			hr = _Module.GetClassObject (rClsId, IID_IClassFactory, CF.ppv());
			if (SUCCEEDED(hr)) {
				hr = CF -> CreateInstance (punkOuter, __uuidof(IUnknown), reinterpret_cast<void **>(&p));
				if (SUCCEEDED(hr)) {
					WalkStackOnAddRef();
					return S_OK;
				}
			}
		}

	// dann der globale Versuch
		hr = ::CoCreateInstance(rClsId, punkOuter, dwCtx, __uuidof(IUnknown), reinterpret_cast<void **>(&p));
		if (SUCCEEDED(hr)) {
			WalkStackOnAddRef();
			return S_OK;
		}
		return hr;
	}
#endif // _ATL_VER >= 0x0200
	HRESULT QueryInterface(const IID& iid, void **ppout) throw()
	{
		if (p != NULL) {
			if (SUCCEEDED(p->QueryInterface(iid, ppout))) {
				WalkStackOnAddRef();
				return S_OK;
			}
		}
		return E_POINTER;
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
	typedef __Interface<I##IF,__CIID<&__uuidof(I##IF)>,CComPtrDebug<I##IF,__CIID<&__uuidof(I##IF)> > > W##IF;
#define DefineSmartInterface2(IF,IID)						\
	typedef __Interface<IF,__CIID<&__uuidof(IF)>,CComPtrDebug<IF,__CIID<&(IID)> > > W##IF;

#endif // _MSC_VER < 1100

#endif // !defined(_SMARTIF_DEBUG_H__F5802CB3_D772_11D1_85F2_00600875138A__INCLUDED_)
