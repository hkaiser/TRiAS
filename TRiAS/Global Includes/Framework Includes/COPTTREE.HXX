///////////////////////////////////////////////////////////////////////////
// @doc 
// @module COPTTREE.HXX | Baumklasse, die sich automatisch ausbalanciert

#if !defined(_COPTTREE_HXX__766329D7_0736_11D2_8657_00600875138A__INCLUDED_)
#define _COPTTREE_HXX__766329D7_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class _CTR_ENTRY32 COptTree : 
	public CTree 
{
protected:
static BOOL m_fP5TickerAvailable;

	ULARGE_INTEGER m_liOptTime;			// letzte Optimierungzeit
	ULARGE_INTEGER m_liInsertTime;		// letzte 'optimale' EinfügeZeit
	ULARGE_INTEGER m_liLastInsertTime;	// letzte Einfügezeit
	LONG m_lDelta;
	BOOL m_fOptimized;

public:
		COptTree (CONTFLAG fContFlags = CFDefault, LONG lDelta = 1) 
			: CTree (fContFlags), m_lDelta(lDelta)
		{
			ULISet32(m_liOptTime, 1);
			ULISet32(m_liInsertTime, 0);
			ULISet32(m_liLastInsertTime, 0);
			m_fOptimized = true;
		}
		COptTree (pGetKeyFcn pGetKey, pKeyCmpFcn pKeyCmp = StrCmp, 
			  CONTFLAG fContFlags = CFDefault, LONG lDelta = 1)
			: CTree (pGetKey, pKeyCmp, fContFlags), m_lDelta(lDelta)
		{
			ULISet32(m_liOptTime, 1);
			ULISet32(m_liInsertTime, 0);
			m_fOptimized = true;
		}
#if !defined(WIN32)
		COptTree (CFreeStore &rFS, pGetKeyFcn pGetKey, pKeyCmpFcn pKeyCmp = StrCmp,
			  CONTFLAG fContFlags = CFDefault, LONG lDelta = 10)
			: CTree (rFS, pGetKeyFcn, pKeyCmpFcn, fContFlags), m_lDelta(lDelta)
		{
			ULISet32(m_liOptTime, 1);
			ULISet32(m_liInsertTime, 0);
			m_fOptimized = true;
		}
#endif
	BOOL Insert (FSHandle, void *);
};

// spezielle CCreatorKlasse, die auf COptTree zugreift ------------------------
class COptCreator : 
	public CCreator 
{
public:
		COptCreator (COptTree &rOT) : CCreator ((CContainer &)rOT) {}
		~COptCreator (void) {}
};

// Spezielles Macro -----------------------------------------------------------
#if !defined(WIN32)

#define DeclareOptLock(ContainerType, DatumType)				\
										\
class DatumType##Lock : public CLock {						\
public:										\
	DatumType##Lock (CNavigator & nav) : CLock (nav) {}			\
	DatumType##Lock (CFreeStore * pfs, FSHandle h):CLock(pfs,h){}		\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
};										\
										\
class DatumType##OptCreator : public COptCreator {				\
public:										\
	DatumType##OptCreator (ContainerType& c) : COptCreator (c) {}		\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); }	\
};																		\
typedef DatumType##OptCreator DatumType##Creator;						\
inline void * operator new (size_t size, DatumType##OptCreator& cr, DatumType *) 	\
{ return cr.Alloc (size); }

#else // WIN32

#define DeclareOptLock(ContainerType, DatumType)				\
										\
class DatumType##Lock : public CLock {						\
public:										\
	DatumType##Lock (CNavigator & nav) : CLock (nav) {}			\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
};										\
										\
class DatumType##OptCreator : public COptCreator {					\
public:										\
	DatumType##OptCreator (ContainerType& c) : COptCreator (c) {}		\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); }	\
};										\
typedef DatumType##OptCreator DatumType##Creator;						\
inline void * operator new (size_t size, DatumType##OptCreator& cr, DatumType *) 	\
{ return cr.Alloc (size); }

#endif // WIN32

#endif // !defined(_COPTTREE_HXX__766329D7_0736_11D2_8657_00600875138A__INCLUDED_)
