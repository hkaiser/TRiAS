/////////////////////////////////////////////////////////////
// CoDelegator.cpp - Generic Delegator Component
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
#include "precomp.h"
#include "CoDelegator.h"
#include "Delegator.h"

//---------------------------------------------------------------------------//
CoDelegator::CoDelegator( IUnknown* pUnkOuter, IUnknown* pUnkInner )
  : m_cRefs( 0 ),
	m_pUnkOuter( pUnkOuter ),
	m_pUnkInner( pUnkInner ),
	m_first( 0 ),
	m_last( 0 ),
	m_end( 0 )
{
	InitializeCriticalSection( &m_sect );
	m_pUnkInner->AddRef();
}

//---------------------------------------------------------------------------//
CoDelegator::~CoDelegator()
{
	for ( Delegator** it = m_first; it != m_last; ++it )
		delete *it;
	delete m_first;

	m_pUnkInner->Release();
	DeleteCriticalSection( &m_sect );
}

//---------------------------------------------------------------------------//
void CoDelegator::DeleteDelegator( Delegator* pDelegator )
{
	Lock lock( *this );

	AddRef();		// this can delete me !
	for ( Delegator** it = m_first; m_last != it; ++it )
	{
		if ( *it == pDelegator )
		{
			delete *it;
			while ( ++it != m_last )
				*(it - 1) = *it;
			--m_last;
			break;
		}
	}
	Release();
}

//---------------------------------------------------------------------------//
HRESULT CoDelegator::_growArray()
{
	size_t capacity = 2 * (m_end - m_first);
	if ( 0 == capacity )	
		capacity = INITIAL_CAPACITY;
	
	Delegator** first = new Delegator*[capacity];
	if ( !first )
		return E_OUTOFMEMORY;
	
	Delegator** dest = first;
	for ( Delegator** it = m_first; it != m_last; ++it )
		*dest++ = *it;

	m_last = first + (m_last - m_first);
	m_end = first + capacity;
	delete m_first;
	m_first = first;
	
	return S_OK;
}

//---------------------------------------------------------------------------//
STDMETHODIMP CoDelegator::QueryInterface( REFIID iid, void** ppv )
{
	// we subsume the identity of the inner
	if ( IID_IUnknown == iid )
	{
		((IUnknown*)(*ppv = (IUnknown*)this))->AddRef();
		return S_OK;
	}

	*ppv = 0;

	Lock lock( *this );

	// see if we've already assimilated the requested interface
	for ( Delegator** it = m_first; it != m_last; ++it )
	{
		if ( (*it)->m_iid == iid )
		{
			*ppv = (IUnknown*)*it;
			((IUnknown*)(*ppv))->AddRef();
			return S_OK;
		}
	}

	// go get the requested interface from the inner and assimilate it.
	IUnknown* pUnkInner = 0;
	HRESULT hr = m_pUnkInner->QueryInterface( iid, (void**)&pUnkInner );
	if ( SUCCEEDED( hr ) )
	{
		// grow the array if necessary
		if ( m_last == m_end )
			hr = _growArray();
		
		if ( SUCCEEDED( hr ) )
		{
			Delegator* pDelegator = new Delegator( *this, pUnkInner, iid );
			if ( pDelegator )
			{
				*m_last++ = pDelegator;
				((IUnknown*)(*ppv = pDelegator))->AddRef();
			}
			else hr = E_OUTOFMEMORY;
		}
		pUnkInner->Release();
	}
	return hr;
}

//---------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) CoDelegator::AddRef()
{
	extern void SvcLock();
	if ( 0 == m_cRefs )
		SvcLock();
	return ++m_cRefs;
}

//---------------------------------------------------------------------------//
STDMETHODIMP_(ULONG) CoDelegator::Release()
{
	extern void SvcUnlock();
	if ( 0 != --m_cRefs )
		return m_cRefs;
	delete this;
	SvcUnlock();
	return 0;
}
