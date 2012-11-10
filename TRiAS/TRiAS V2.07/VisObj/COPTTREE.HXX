// Baumklasse, die sich automatisch ausbalanciert -----------------------------
// File: COPTTREE.HXX

#if !defined(_COPTTREE_HXX)
#define _COPTTREE_HXX

class COptTree : public CTree {
private:
	DWORD m_dwOptTime;
	DWORD m_dwInsertTime;

public:
		COptTree (CONTFLAG fContFlags = CFDefault) : CTree (fContFlags),
			  m_dwOptTime(1), m_dwInsertTime(0) {}
		COptTree (pGetKeyFcn pF1, pKeyCmpFcn pF2 = StrCmp, 
			  CONTFLAG fContFlags = CFDefault)
			: CTree (pF1, pF2, fContFlags), 
			  m_dwOptTime(1), m_dwInsertTime(0) {}
#if !defined(WIN32)
		COptTree (CFreeStore &rFS, pGetKeyFcn pF1, pKeyCmpFcn pF2 = StrCmp,
			  CONTFLAG fContFlags = CFDefault)
			: CTree (rFS, pF1, pF2, fContFlags),
			  m_dwOptTime(1), m_dwInsertTime(0) {}
#endif
	BOOL Insert (FSHandle, void *);
};

// spezielle CCreatorKlasse, die auf COptTree zugreift ------------------------
class COptCreator : public CCreator {
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
class DatumType##Creator : public COptCreator {				\
public:										\
	DatumType##Creator (ContainerType& c) : COptCreator (c) {}		\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); }	\
};										\
										\
inline void * operator new (size_t size, DatumType##Creator& cr, DatumType *) 	\
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
class DatumType##Creator : public COptCreator {					\
public:										\
	DatumType##Creator (ContainerType& c) : COptCreator (c) {}		\
	DatumType * operator -> (void) { return (DatumType *)CLock::P();}	\
	operator DatumType * (void) { return (DatumType *)CLock :: P();}	\
	DatumType * InsertPtr (DatumType *pD) { return (DatumType *)InsertPointer (pD); }	\
};										\
										\
inline void * operator new (size_t size, DatumType##Creator& cr, DatumType *) 	\
{ return cr.Alloc (size); }

#endif // WIN32


#endif // _COPTTREE_HXX
