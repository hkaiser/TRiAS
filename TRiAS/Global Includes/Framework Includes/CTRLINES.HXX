//	Header file for Glockenspiel Container release 2.0,
//
//	Glockenspiel's Framework for managing objects
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  ctrlines.hxx - Inline functions for Container 2.0
//-------------------------------------------------------------------------

#if !defined(NOINLINES)
// normale Variante
#define INLINE inline
#undef _DLLENTRY
#define _DLLENTRY
#else
// DEBUGVariante
#define INLINE 
#endif

#ifndef NONODE

INLINE FSHandle _DLLENTRY CNode :: GetHandle (void) const
{
	return m_fsHandle;
}

INLINE void _DLLENTRY CNode :: SetHandle (FSHandle h)
{
	m_fsHandle = h;
}

INLINE void _DLLENTRY CNode :: Lock (void)
{
	m_iLocks++;
}

INLINE void _DLLENTRY CNode :: Unlock (void)
{
	m_iLocks--;
}

INLINE BOOL _DLLENTRY CNode :: Locked (void) const
{
	return m_iLocks;
}

#ifndef NOSEQNODE
#ifndef NOLISTNODE

INLINE void _DLLENTRY CListNode :: SetNext (CListNode *n)
{
	m_pNext = n;
}

INLINE void _DLLENTRY CListNode :: SetPrev (CListNode *p)
{
	m_pPrev = p;
}

INLINE void _DLLENTRY CListNode :: Append (CListNode *n)
{
	n -> m_pNext = m_pNext;
	n -> m_pPrev = this;
	m_pNext = n;
}

INLINE void _DLLENTRY CListNode :: Remove (void)
{
	if (m_pPrev) m_pPrev -> m_pNext = m_pNext;
	if (m_pNext) m_pNext -> m_pPrev = m_pPrev;
}

#endif // NOLISTNODE
#endif // NOSEQNODE
#ifndef NOKEYNODE

INLINE CKeyContainer & _DLLENTRY CKeyNode :: GetContainer (void) const
{
// 	ASSERT_VALID (this);
	
	return *m_pCont;
}

INLINE void _DLLENTRY CKeyNode :: SetContainer (CKeyContainer *pCont)
{
	m_pCont = pCont;
}


#ifndef HASHNODE

INLINE void _DLLENTRY CHashNode :: SetNode (uint i, CHListNode *pn)
{
// 	ASSERT_VALID (this);
	
	m_ppBuckets[i] = pn;
}

INLINE CHListNode * _DLLENTRY CHashNode :: GetNode (uint i) const
{
//	ASSERT_VALID (this);
	
	return m_ppBuckets[i];
}

INLINE uint _DLLENTRY CHashNode :: Size (void) const
{
//	ASSERT_VALID (this);
	
	return m_uiSize;
}

#endif // NOHASHNODE
#ifndef NOHLISTNODE

INLINE CHListNode * _DLLENTRY CHListNode :: GetNext (void) const
{
	return m_pNext;
}

INLINE CHListNode * _DLLENTRY CHListNode :: GetPrev (void) const
{
	return m_pPrev;
}

INLINE void _DLLENTRY CHListNode :: SetNext (CHListNode *n)
{
	m_pNext = n;
}

INLINE void _DLLENTRY CHListNode :: SetPrev (CHListNode *p)
{
	m_pPrev = p;
}

INLINE void _DLLENTRY CHListNode :: Append (CHListNode *n)
{
	n -> m_pNext = m_pNext;
	n -> m_pPrev = this;
	m_pNext = n;
}

INLINE void _DLLENTRY CHListNode :: Insert (CHListNode *p)
{
	p -> m_pPrev = m_pPrev;
	p -> m_pNext = this;
	m_pPrev = p;
}

INLINE void _DLLENTRY CHListNode :: Remove (void)
{
	if (m_pPrev) m_pPrev -> m_pNext = m_pNext;
	if (m_pNext) m_pNext -> m_pPrev = m_pPrev;
}

#endif // NOHLISTNODE
#ifndef NOBINNODE

INLINE CBinaryNode * _DLLENTRY CBinaryNode :: Left (void) const
{
	return m_pLeft;
}

INLINE CBinaryNode * _DLLENTRY CBinaryNode :: Right (void) const
{
	return m_pRight;
}

INLINE CBinaryNode * _DLLENTRY CBinaryNode :: Parent (void) const
{
	return m_pParent;
}

INLINE void _DLLENTRY CBinaryNode :: SetLeft (CBinaryNode *bn)
{
	m_pLeft = bn;
}

INLINE void _DLLENTRY CBinaryNode :: SetRight (CBinaryNode *bn)
{
	m_pRight = bn;
}

INLINE void _DLLENTRY CBinaryNode :: SetParent (CBinaryNode *bn)
{
	m_pParent = bn;
}

#endif // NOBINNODE
#endif // NOKEYNODE
#endif // NONODE

#ifndef NOLOCK

#if !defined(WIN32)
INLINE CFreeStore * _DLLENTRY CLock :: GetFreeStore (void) const
{
	return m_pFS;
}
#endif
INLINE FSHandle & _DLLENTRY CLock :: GetHandle (void) 
{
	return m_fsHandle;
}

#if !defined(NATIVEINLINES)
INLINE void * _DLLENTRY CLock :: P (void)
{
	return m_pObj;
}
#endif

INLINE BOOL _DLLENTRY CLock :: Valid (void)
{
	return m_pObj != 0;
}

#ifndef NONAKEDLOCK

INLINE void * _DLLENTRY CNakedLock :: P (void)
{
	return CLock :: P ();
}

#endif // NONAKEDLOCK
#endif // NOLOCK

INLINE void _DLLENTRY CCreator :: Revoke (void)		// #HK940317
{
CContainer :: CSyncThread Sync (&m_rCont);

	GetHandle() = 0;
}

#if !defined(NOINLINES)
#undef _DLLENTRY
#if !defined(WIN32)
#define _DLLENTRY 	__export	// normale Variante
#define _CTR_ENTRY32
#else

#if defined(__CTRDLL__)
#define _CTR_ENTRY32 __declspec(dllexport)
#else
#define _CTR_ENTRY32 __declspec(dllimport)
#endif

#define _DLLENTRY
#endif
#endif
