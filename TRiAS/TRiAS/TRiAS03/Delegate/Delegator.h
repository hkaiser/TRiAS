/////////////////////////////////////////////////////////////
// Delegator.h - Generic Delegator Component
//
// Copyright 1997, Keith Brown
//
// The Delegator class holds a single interface pointer and
// implements the delegating unknown, as well as the auto-
// forwarding of method calls to the inner object.
// Delegator objects notify their CoDelegator parent when
// their individual refcount drops to zero so the parent
// can destroy them and remove them from the collection.
/////////////////////////////////////////////////////////////
#ifndef _DELEGATOR_H
#define _DELEGATOR_H

class CoDelegator;

//---------------------------------------------------------------------------//
// We hand out a Delegator struct for each wrapped interface pointer.
// Note the size of this object is significant (20 bytes).
// This is the main reason that we refcount each interface ptr,
// to avoid CoDelegator from getting too corpulent :)
struct Delegator
{
	Delegator( CoDelegator& parent, IUnknown* pUnkInner, const IID& iid )
	  : m_vptr( s_vptr ),
		m_pUnkInner( pUnkInner ),
		m_parent( parent ),
		m_iid( iid ),
		m_cRefs( 0 )
	{
		m_pUnkInner->AddRef();
		m_parent.AddRef();		// #HK981028
	}
	~Delegator()
	{
		m_parent.Release();		// #HK981028
		m_pUnkInner->Release();
	}

	const void*	const	m_vptr;			// ORDER_DEPENDENCY (this + 0 bytes)
	IUnknown*			m_pUnkInner;	// ORDER_DEPENDENCY (this + 4 bytes)
	CoDelegator&		m_parent;
	const IID			m_iid;
	long				m_cRefs;		// refcount for this interface

	static const void* const s_vptr;
};

#endif // _DELEGATOR_H
