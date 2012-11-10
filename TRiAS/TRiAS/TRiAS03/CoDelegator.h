/////////////////////////////////////////////////////////////
// CoDelegator.h - Generic Delegator Component
//
// Copyright 1997, Keith Brown
//
// The CoDelegator class implements a standard non-delegating
// unknown and caches interface pointers lazily as they
// are asked for by the outer object.
// Each new interface pointer is wrapped by a Delegator
// object and refcounted individually, until the refcount
// on the interface drops to zero, at which time it is
// released and removed from the collection.
/////////////////////////////////////////////////////////////

#ifndef _CODELEGATOR_H
#define _CODELEGATOR_H

//#include "delegator.h"

//---------------------------------------------------------------------------//
// CoDelegator is an aggregatable component that assimilates a child object
// and exposes all the child's interfaces via a thunking wrapper.
// The effect is that a non-aggregatable object (perhaps even an out-of-proc
// object) can be aggregated by using CoDelegator as a shim. Another use might
// be to dynamically aggregate an existing object (direct aggregation requires
// you to *construct* the object passing the outer unknown).
//
// The motivation for creating CoDelegator was to automate handler marshaling
// by allowing a custom handler to aggregate on the standard proxy.
//
// The space complexity for this object is as follows:
//		 48 bytes for a non-delegating IUnknown
//	plus 24 bytes per custom interface in use.
//	  
// The time complexity for this object is as follows:
//		Non-Delegating Unknown:
//			Zero overhead for QI on cached interfaces
//			O(N) overhead for QI on non-cached interfaces
//			Zero overhead for AddRef/Release,
//				except for final release, which is O(N)
//		Delegating Unknown
//			Zero overhead
//		Assimilated interface methods
//			O(1) overhead per method call (about 14 assembly instructions on x86)
//
class CoDelegator : public IUnknown
{
	friend struct Delegator;
public:
	CoDelegator( IUnknown* pUnkOuter, IUnknown* pUnkInner );
	~CoDelegator();

	void DeleteDelegator( Delegator* pDelegator );
	IUnknown* GetOuter() { return m_pUnkOuter; }

	STDMETHODIMP QueryInterface( REFIID iid, void** ppv );
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

private:
	HRESULT _growArray();

	class Lock
	{
	public:
		Lock( CoDelegator& obj )
		  : m_obj( obj )
		{ EnterCriticalSection( &m_obj.m_sect ); }
		~Lock() { LeaveCriticalSection( &m_obj.m_sect ); }
	private:
		CoDelegator& m_obj;
	};
	friend class Lock;

	enum { INITIAL_CAPACITY = 3 };

	long				m_cRefs;
	IUnknown*			m_pUnkOuter;
	IUnknown*			m_pUnkInner;
	Delegator**			m_first;
	Delegator**			m_last;
	Delegator**			m_end;
	CRITICAL_SECTION	m_sect;				// 24 bytes
};

///////////////////////////////////////////////////////////////////////////////
// Erzeugen/Registrieren einer neuen DelegatorFactory
HRESULT CreateDelegatorFactory (REFIID riid, LPVOID *ppv);
STDAPI DelegatorRegisterServer();
STDAPI DelegatorUnregisterServer();

#endif // _CODELEGATOR_H
