//  Usage: #include <containr.hxx>
//
//	Declaration of Glockenspiel Container release 2.0,
//
//	Glockenspiel's Framework for managing objects
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  ccontainr.hxx - Declarations of all the Container classes
//-------------------------------------------------------------------------
#ifndef TRIASCON_HXX
#define TRIASCON_HXX

#include <ctrtypes.hxx>
#if defined(WIN32)
#if defined(__GC__)
#include <gc_cpp.h>
#endif // __GC__
#else  // WIN32
#include <freestor.hxx>
#endif // WIN32
#include <tassert.hxx>
#if defined(_SYNC_WITHMUTEX) || _MSC_VER < 1100
#include <syncthrd.hxx>			// ThreadSynchronisation mit Mutex
#else
#include <syncthrdcs.hxx>		// ThreadSynchronisation mit CriticalSection
#endif // _SYNC_WITHMUTEX

#define RECURSION	1

#if !defined(STRICT)
#define STRICT	1
#endif
#if _MSC_VER >= 800 && !defined(MSCC8)
#define MSCC8	1
#endif

#if defined(_DEBUG) && defined(WIN32)
#define TX_ASSERT_VALID_CONT(pC)	(pC)->AssertValid()
#else
#define TX_ASSERT_VALID_CONT(pC)
#endif //_DEBUG
	

#ifndef NOCONTAINER

typedef enum tagCONTFLAGS {
	CFNoSpecial 	= 0x00,
	CFAutoDelete 	= 0x01,
	CFUniqueKey 	= 0x02,
	CFSyncThreads	= 0x04,
//
	CFAll		= 0x07,
#if !defined(WIN32)
	CFDefault	= CFAutoDelete,
#else
	CFDefault	= tagCONTFLAGS(CFAutoDelete|CFSyncThreads),
#endif
} CONTFLAG;

class _CTR_ENTRY32 CContainer : public CSyncMonitor // : public CObject
{
friend class CNavigator;
friend class CLock;
friend class CCreator;
friend class CDCreator;						// #HK910924

private:
#if !defined(WIN32)
	CFreeStore *	m_pFS;
#endif
	ulong		m_ulCount;
	CNavigator * 	m_grNavs[MAX_NAVIGATORS];
	unsigned short	m_fContFlags : 3;			// #HK940604

	void		Register (CNavigator *);
	void		Unregister (CNavigator *);

protected:
#if !defined(WIN32)
	CFreeStore *	GetFreeStore (void) const;
#endif
virtual	CNode *		DataStructure (void) const { return NULL; }
virtual CNode *		FirstNode (void) const;
virtual CNode *		LastNode (void) const;
virtual BOOL		Insert (FSHandle, void *);
virtual	BOOL		Delete (CNode *);
virtual	void		UserDelete (void * /*pobj*/) {};

public:
//	DECLARE_SERIAL (CContainer);
//	void Serialize (CArchive &ar);
	
		CContainer (CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CContainer (CFreeStore &, CONTFLAG fContFlags = CFDefault);
#endif
#if defined(__WATCOMC__) || defined(WIN32)
	virtual ~CContainer (void) {}
#else
		~CContainer (void) {}
#endif
	
virtual BOOL		EveryDelete (void);
virtual void		Every (pGenericFcn) {};
virtual BOOL		Every (pGenericDataFcn, void *) { return false; }

	ulong		Count (void) const;
	
	unsigned short ContFlags (CONTFLAG fMask = CFAll) { return (unsigned short)(m_fContFlags & fMask); }

#if defined(WIN32) && defined(_DEBUG)
virtual void		AssertValid (void) const;
#endif
};


#ifndef NOSEQCONTAINER

class _CTR_ENTRY32 CSeqContainer : public CContainer
{
public:
//	DECLARE_SERIAL (CSeqContainer);
//	void Serialize (CArchive &ar);
	
		CSeqContainer (CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CSeqContainer (CFreeStore &, CONTFLAG fContFlags = CFDefault);
#endif

	void		Every (pGenericFcn);
	BOOL		Every (pGenericDataFcn, void *);

friend class CRing;     
};

#ifndef NOARRAYCONTAINER

class _CTR_ENTRY32 CArrayContainer : public CSeqContainer
{
private:
	CArrayNode *	m_pArray;
	uint		m_uiSize;

protected:
	CNode *		DataStructure (void) const;
	CNode *		LastNode (void) const;
	BOOL		Insert (FSHandle, void *);
	BOOL		Delete (CNode *);

public:
//	DECLARE_SERIAL (CArrayContainer);
//	void Serialize (CArchive &ar);
		
		CArrayContainer (uint noelems = 1000, CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CArrayContainer (CFreeStore &, uint noelems = 1000, CONTFLAG fContFlags = CFDefault);
#endif
	BOOL		Resize (uint);
	uint		Size (void) const;

		~CArrayContainer (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

#endif	// NOARRAYCONTAINER
#ifndef NOLISTCONTAINER

class _CTR_ENTRY32 CListContainer : public CSeqContainer
{
private:
	CListNode *	m_pBase;

protected:
	CNode *		DataStructure (void) const;
	CNode *		LastNode (void) const;
	BOOL		Insert (FSHandle, void *);
	BOOL		Delete (CNode *);

public:
//	DECLARE_SERIAL (CListContainer);
//	void Serialize (CArchive &ar);
		
		CListContainer (CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CListContainer (CFreeStore &, CONTFLAG fContFlags = CFDefault);
#endif
		~CListContainer (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

#endif	// NOLISTCONTAINER
#endif	// NOSEQCONTAINER
#ifndef NOKEYCONTAINER

class _CTR_ENTRY32 CKeyContainer : public CContainer
{
private:
friend class CTable;
friend class CKeyNode;

protected:
	pGetKeyFcn	m_pGetKeyFcn;
	pKeyCmpFcn	m_pKeyCmpFcn;

public:
//	DECLARE_SERIAL (CKeyContainer);
//	void Serialize (CArchive &ar);
		
		CKeyContainer (CONTFLAG fContFlags = CFDefault);
		CKeyContainer (pGetKeyFcn, pKeyCmpFcn = StrCmp, CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CKeyContainer (CFreeStore &, pGetKeyFcn, pKeyCmpFcn = StrCmp, CONTFLAG fContFlags = CFDefault);
#endif

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

#ifndef NOHASHTABLE

class _CTR_ENTRY32 CHashTable : public CKeyContainer
{
private:
friend class CHashNode;
friend class CHListNode;                                  

	CHashNode *	m_pBuckets;
	pHashFcn	m_pHashFcn;
	
protected:
	CNode *		DataStructure (void) const;
	CNode *		FirstNode (void) const;
	CNode *		LastNode (void) const;
	BOOL		Insert (FSHandle, void *);
	BOOL		Delete (CNode *);

public:
//	DECLARE_SERIAL (CHashTable);
//	void Serialize (CArchive &ar);
		
		CHashTable (CONTFLAG fContFlags = CFDefault);
		CHashTable (pGetKeyFcn, pKeyCmpFcn = StrCmp,
			    pHashFcn = StrHash, uint buckets = 101,
			    CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CHashTable (CFreeStore &, pGetKeyFcn, pKeyCmpFcn = StrCmp,
			    pHashFcn = StrHash, uint buckets = 101,
			    CONTFLAG fContFlags = CFDefault);
#endif

	void		Every (pGenericFcn);
	BOOL		Every (pGenericDataFcn, void *);
	
	uint		Size (void) const;
	uint		EmptyBuckets (void) const;
	uint		BucketsOfLength (uint len) const;
	uint		AverageCompares (void) const;

		~CHashTable (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

#endif // NOHASHTABLE
#ifndef NOTREE

#if !defined(NOOPTTREE)
// #HK910826: Einfügen der Funktionen zum optimieren des Baumes
enum Richtung { LINKS, RECHTS, LINKS_MAX3, RECHTS_MAX3 };	// #HK910826, #HK960116
#endif // NOOPTTREE

class _CTR_ENTRY32 CTree : public CKeyContainer
{
#if !defined(NOOPTTREE)
// ----------------------------------------------------------------------------
// im Vergleich zu CTree ist lediglich die Funktion neu, die den
// gefüllten Baum ausgleicht (Optimize())
private:
// lokale Funktionsdeklarationen
	CBinaryNode *Branch (CBinaryNode *, Richtung);	// Funktionen zum
	CBinaryNode *Fold (CBinaryNode *, Richtung);	// 'Falten 'des Baumes
	CBinaryNode *Special (CBinaryNode *, Richtung);
	long Depth (CBinaryNode *, Richtung);	// AstLänge bestimmen
	CBinaryNode *Linear (void);		// Linearisierung des Baumes
	void CorrectParents (void);		// ParentPointer richten
	BOOL ValidateTree (CBinaryNode *);
// ----------------------------------------------------------------------------
#endif // NOOPTTREE
friend class CBinaryNode;
friend class CUniqueTree;	// #HK930501

	void		PreOrder (CBinaryNode *, pGenericFcn);
	void		InOrder (CBinaryNode *, pGenericFcn);
	BOOL		InOrder (CBinaryNode *, pGenericDataFcn, void *);
	void		PostOrder (CBinaryNode *, pGenericFcn);
	
protected:
	CBinaryNode *	m_pRoot;

	CNode *		DataStructure (void) const;
	CNode *		FirstNode (void) const;
	CNode *		LastNode (void) const;
	BOOL		Insert (FSHandle, void *);
	BOOL		Delete (CNode *);
	
public:
//	DECLARE_SERIAL (CTree);
//	void Serialize (CArchive &ar);
		
		CTree (CONTFLAG fContFlags = CFDefault);
		CTree (pGetKeyFcn, pKeyCmpFcn = StrCmp, 
		       CONTFLAG fContFlags = CFDefault);
#if !defined(WIN32)
		CTree (CFreeStore &, pGetKeyFcn, pKeyCmpFcn = StrCmp,
		       CONTFLAG fContFlags = CFDefault);
#endif

	void		Every (pGenericFcn);
	BOOL 		Every (pGenericDataFcn, void *);
	uint		AverageCompares (void) const;
#if !defined(NOOPTTREE)
	void 		Optimize (void);	// zusätzliche Funktion
#endif // NOOPTTREE

// Funktion zum umhängen eines Nodes an eine andere Stelle (#HK920328)
	CNode *		ReInsert (CBinaryNode *, void *, unsigned short);

		~CTree (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

#endif	// NOTREE
#endif	// NOKEYCONTAINER
#endif	// NOCONTAINER
#ifndef NONAVIGATOR

class _CTR_ENTRY32 CNavigator // : public CObject
{
friend class CLock;
friend class CContainer;         
private:
	CContainer &	m_rCont;

void		DeleteNotify (CNode *);
	
protected:
	CNode *		m_pCurrentNode;
	
CContainer &	GetContainer (void) const;
FSHandle	GetHandle (void) const;

//	DECLARE_DYNAMIC (CNavigator);

		CNavigator (void);		// nur als BasisKlasse verwenden
		CNavigator (CContainer &);
		CNavigator (CNavigator &);

public:
void		Reset (void);
BOOL		First (void);
BOOL		Last (void);
BOOL		Valid (void) const;
BOOL		Delete (void);

		~CNavigator (void);
};

#ifndef NORING

class _CTR_ENTRY32 CRing : public CNavigator
{
private:
	ulong		m_ulRank;
	
public:
//	DECLARE_DYNAMIC (CRing);
	
		CRing (CSeqContainer &);
		CRing (CRing &);

	BOOL		First (void);
	BOOL		Last (void);
	BOOL		Next (void);
	BOOL		Prev (void);
	BOOL		Goto (ulong);		// 0-based offset.
	ulong		GetRank (void) const;
};

#endif	// NORING
#ifndef NOTABLE

class _CTR_ENTRY32 CTable : public CNavigator
{                      
public:
//	DECLARE_DYNAMIC (CTable);
	
		CTable (CKeyContainer &);
		CTable (CTable &);

	BOOL		Next (void);
	BOOL		Prev (void);
	BOOL		Find (void * key);
	BOOL		FindNext (void * key);
	BOOL		FindPrev (void * key);

	BOOL		FindFirst (void *key);		// #HK911012

	BOOL		ReInsert (void *newKey, unsigned short KeySize);	// #HK920328
};

#endif	// NOTABLE
#endif	// NONAVIGATOR
#ifndef NONODE

class _CTR_ENTRY32 CNode // : public CObject
{
private:
	FSHandle	m_fsHandle;
	int		m_iLocks;

public:
//	DECLARE_SERIAL (CNode);
//	void Serialize (CArchive &ar);
		
		CNode (void);
		CNode (FSHandle);

	FSHandle	GetHandle (void) const;
	void		SetHandle (FSHandle);
	void		Lock (void);
	void		Unlock (void);
	int		Locked (void) const;
	CNode &		operator = (CNode &);

virtual CNode *		CurrentAfterDelete (CNode * /*current*/) { return NULL;} 
};

#ifndef NOSEQNODE

class _CTR_ENTRY32 CSeqNode : public CNode
{      
public:
//	DECLARE_SERIAL (CSeqNode);
//	void Serialize (CArchive &ar);
	
		CSeqNode (void);
		CSeqNode (FSHandle);

virtual	CSeqNode *	Next (ulong /*nodes*/ = 1) const { return NULL; }
virtual CSeqNode *	Prev (ulong /*nodes*/ = 1) const { return NULL; }
};

#ifndef NOARRAYNODE

class _CTR_ENTRY32 CArrayNode : public CSeqNode
{      
public:
//	DECLARE_SERIAL (CArrayNode);
//	void Serialize (CArchive &ar);
	
		CArrayNode (void);
		CArrayNode (FSHandle h);

	CSeqNode *	Next (ulong nodes = 1) const;
	CSeqNode *	Prev (ulong nodes = 1) const;
	
	CNode *		CurrentAfterDelete (CNode * current);
};

#endif	// NOARRAYNODE
#ifndef NOLISTNODE

class _CTR_ENTRY32 CListNode : public CSeqNode
{
private:
	CListNode *	m_pNext;
	CListNode *	m_pPrev;

public:
//	DECLARE_SERIAL (CListNode);
//	void Serialize (CArchive &ar);
	
		CListNode (void);
		CListNode (FSHandle);

	CSeqNode *	Next (ulong nodes = 1) const;
	CSeqNode *	Prev (ulong nodes = 1) const;
	CNode *		CurrentAfterDelete (CNode * current);

	CListNode *	GetNext (void) const;
	CListNode *	GetPrev (void) const;
	void		SetNext (CListNode *);
	void		SetPrev (CListNode *);
	void		Append (CListNode *);
	void		Remove (void);
};

#endif	// NOLISTNODE
#endif	// NOSEQNODE
#ifndef NOKEYNODE

class _CTR_ENTRY32 CKeyNode : public CNode
{      
private:
	CKeyContainer *	m_pCont;
	
public:                              
//	DECLARE_SERIAL (CKeyNode);
//	void Serialize (CArchive &ar);
//	void AssertValid (void) const;
	
		CKeyNode (void);
		CKeyNode (CKeyContainer &);
		CKeyNode (FSHandle, CKeyContainer &);

	CKeyContainer &	GetContainer (void) const;
	void		SetContainer (CKeyContainer *pCont);
	
	int		Compare (void *key) const;
	CNode *		CurrentAfterDelete (CNode *current);

virtual CKeyNode *	Find (void * /*key*/) const { return NULL; }
virtual CKeyNode *	FindNext (void * /*key*/) const;
virtual CKeyNode *	FindPrev (void * /*key*/) const;
virtual CKeyNode *	Next (void) const { return NULL; }
virtual CKeyNode *	Prev (void) const { return NULL; }

	CKeyNode *	FindFirst (void *key) const;	// #HK911012
};

#ifndef NOHASHNODE

class _CTR_ENTRY32 CHashNode : public CKeyNode
{
private:
	CHListNode **	m_ppBuckets;
	uint		m_uiSize;

protected:
	void 		ReSize (uint newnobuckets);
	
public:
//	DECLARE_SERIAL (CHashNode);
//	void Serialize (CArchive &ar);
//	void AssertValid (void) const;
		
		CHashNode (void);
		CHashNode (CHashTable & ht, uint nobuckets);

	void		SetNode (uint, CHListNode *);
	CHListNode *	GetNode (uint) const;
	uint 		Size (void) const;
	CNode *		CurrentAfterDelete (CNode * current);

	CKeyNode *	Find (void * key) const;
	CKeyNode *	Next (void) const;
	CKeyNode *	Prev (void) const;

		~CHashNode (void);
};

#endif	// NOHASHNODE
#ifndef NOHLISTNODE

class _CTR_ENTRY32 CHListNode : public CKeyNode
{        
private:
	CHListNode *	m_pNext;
	CHListNode *	m_pPrev;

public:          
//	DECLARE_SERIAL (CHListNode);
//	void Serialize (CArchive &ar);
	
		CHListNode (void);
		CHListNode (CHashTable &);
		CHListNode (FSHandle, CHashTable &);

	CHListNode * 	GetNext (void) const;
	CHListNode * 	GetPrev (void) const;
	void		SetNext (CHListNode *);
	void		SetPrev (CHListNode *);
	
	void		Append (CHListNode *);
	void		Insert (CHListNode *);
	void		Remove (void);

	CKeyNode *	Find (void * key) const;
	CKeyNode *	FindNext (void * key) const;
	CKeyNode *	FindPrev (void * key) const;
	CKeyNode *	Next (void) const;
	CKeyNode *	Prev (void) const;
};

#endif	// NOHLISTNODE
#ifndef NOBINARYNODE

class _CTR_ENTRY32 CBinaryNode : public CKeyNode
{
private:
	CBinaryNode *	m_pParent;
	CBinaryNode *	m_pLeft;
	CBinaryNode *	m_pRight;

public:
//	DECLARE_SERIAL (CBinaryNode);
//	void Serialize (CArchive &ar);
	
		CBinaryNode (void);
		CBinaryNode (CTree &);
		CBinaryNode (FSHandle h, CTree &, CBinaryNode *);

	CKeyNode *	Find (void * key) const;
	CKeyNode *	Next (void) const;
	CKeyNode *	Prev (void) const;

	CBinaryNode *	Left (void) const;
	CBinaryNode *	Right (void) const;
	CBinaryNode *	Parent (void) const;
	void		SetLeft (CBinaryNode *);
	void		SetRight (CBinaryNode *);
	void		SetParent (CBinaryNode *);

	void		Graft (CBinaryNode * old, CBinaryNode * replacement);
	CBinaryNode *	LeftMost (void) const;
	CBinaryNode *	LeftMostOrRight (void) const;
	CBinaryNode *	RightMost (void) const;
};

#endif	// NOBINARYNODE
#endif	// NOKEYNODE
#endif	// NONODE
#ifndef NOLOCK

class _CTR_ENTRY32 CLock // : public CObject
{
private:
#if !defined(WIN32)
	CFreeStore * 	m_pFS;
#endif
	FSHandle	m_fsHandle;
	CNode *		m_pNode;
	void *		m_pObj;
	
protected:
		CLock (CNavigator &);
#if defined(WIN32)
		CLock (FSHandle);
#else
		CLock (CFreeStore *, FSHandle);

	CFreeStore *	GetFreeStore (void) const;
#endif
	FSHandle &	GetHandle (void);		// CV3B: removed const
	void		lock (void);
	void		Unlock (void);

	void *		P (void);

public:
//	DECLARE_DYNAMIC (CLock);
	
	BOOL		Valid (void);

		~CLock (void);

#if defined(WIN32) && defined(_DEBUG)
virtual void		AssertValid (void) const;
#endif
};


#ifndef NOCREATOR

class _CTR_ENTRY32 CCreator : public CLock
{
private:
	CContainer &	m_rCont;
	
public:
//	DECLARE_DYNAMIC (CCreator);
	
		CCreator (CContainer &);

	void *		Alloc (size_t);
#if _MSC_VER >= 1200
	void		Free (void *pMem);		// #HK990104
#endif // _MSC_VER >= 1200
	void		Insert (void);
	void 		Revoke (void);			// #HK930317
	void *		InsertPointer (void *);	// #HK940606
	
		~CCreator (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

inline void * operator new (size_t size, CCreator & cr)
{
	return cr.Alloc (size);
}

#if _MSC_VER >= 1200
inline void operator delete (void *pMem, CCreator & cr)
{
	cr.Free (pMem);
}
#endif // _MSC_VER >= 1200

#endif	// NOCREATOR
#ifndef NONAKEDLOCK

class _CTR_ENTRY32 CNakedLock : public CLock
{
public:
#if defined(WIN32)
		CNakedLock (FSHandle h);
#else
		CNakedLock (CFreeStore *pfs, FSHandle h);
#endif
	
	void *		P (void);
};

#endif	// NONAKEDLOCK

#if !defined(WIN32)

#define DeclareLock(ContainerType, DatumType) \
\
class DatumType##Lock : public CLock { \
public: \
	DatumType##Lock (CNavigator & nav) : CLock (nav) {} \
	DatumType##Lock (CFreeStore * pfs, FSHandle h):CLock(pfs,h){} \
	DatumType * operator -> (void) { return (DatumType *)CLock::P();} \
	operator DatumType * (void) { return (DatumType *)CLock :: P();} \
}; \
\
class DatumType##Creator : public CCreator { \
public: \
	DatumType##Creator (ContainerType& c) : CCreator (c) {} \
	DatumType * operator -> (void) { return (DatumType *)CLock::P();} \
	operator DatumType * (void) { return (DatumType *)CLock :: P();} \
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); } \
}; \
\
inline void * operator new (size_t size, DatumType##Creator& cr, DatumType *) \
{ return cr.Alloc (size); }

#else // WIN32

#define DeclareLockBase(ContainerType, DatumType) \
\
class DatumType##Lock : public CLock { \
public: \
	DatumType##Lock (CNavigator & nav) : CLock (nav) {}	\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();} \
	operator DatumType * (void) { return (DatumType *)CLock :: P();} \
}; \
\
class DatumType##Creator : public CCreator { \
public: \
	DatumType##Creator (ContainerType& c) : CCreator (c) {} \
	DatumType * operator -> (void) { return (DatumType *)CLock::P();} \
	operator DatumType * (void) { return (DatumType *)CLock :: P();} \
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); } \
}; \
\
inline void * operator new (size_t size, DatumType##Creator& cr, DatumType *) \
{ return cr.Alloc (size); } 

#if _MSC_VER < 1200
#define DeclareLock(ContainerType,DatumType)	DeclareLockBase(ContainerType,DatumType)
#else
#define DeclareLock(ContainerType,DatumType)	DeclareLockBase(ContainerType,DatumType) \
inline void operator delete (void *pMem, DatumType##Creator& cr, DatumType *) \
{ cr.Free (pMem); }
#endif // _MSC_VER < 1200

#endif // WIN32

#if defined(__MFC__) || defined(__ATL_USED__)
#define ContCreate(creator, Type)	new (creator, (Type*) 0) Type
#else
#define Create(creator, Type)	new (creator, (Type*) 0) Type
#endif

#endif // NOLOCK

//#if !defined(_DEBUG) || defined(NATIVECTR)
#if defined(NATIVECTR)
#undef NOINLINES	// in DLL inlines benutzen
#endif
#include <ctrlines.hxx>
//#endif

#endif // TRIASCON_HXX
