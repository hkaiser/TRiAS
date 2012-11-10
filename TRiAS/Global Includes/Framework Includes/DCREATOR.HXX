// Klassendeklarationen für doppelte Container
// File: DCREATOR.HXX

#if !defined(_DCREATOR_HXX)
#define _DCREATOR_HXX

#if !defined(NODCREATOR)

class _CTR_ENTRY32 CDCreator : public CLock {
private:
	CContainer & cont1;		// Container 1
	CContainer & cont2;		// Container 2

public:
// Konstruktor
		CDCreator (CContainer &c1, CContainer &c2);

// Memberfunktionen
	void * Alloc (size_t size);
#if _MSC_VER >= 1200
	void Free (void *pMem);
#endif // _MSC_VER >= 1200
	BOOL Insert (void);

// Destruktor
		~CDCreator (void);

#if defined(_DEBUG) && defined(WIN32)
	void		AssertValid (void) const;
#endif
};

inline void *operator new (size_t size, CDCreator & dcr) 
{
	return dcr.Alloc (size);
}

#if _MSC_VER >= 1200
inline void operator delete (void *pMem, CDCreator & cr)
{
	cr.Free (pMem);
}
#endif // _MSC_VER >= 1200

#if !defined(WIN32)
#define DeclareDLock(CT, DatumType) \
\
class DatumType##Lock : public CLock { \
public: \
	DatumType##Lock (CNavigator &nav) : CLock (nav) {} \
	DatumType##Lock (CFreeStore *pfs, FSHandle h) : CLock (pfs, h) {} \
	DatumType * operator -> () { return (DatumType *)CLock :: P(); } \
	operator DatumType * () { return (DatumType *)CLock :: P(); } \
}; \
\
class DatumType##DCreator : public CDCreator { \
public: \
	DatumType##DCreator (CT &c) : CDCreator ((CT##1 &)c, (CT##2 &)c) {}	\
	DatumType * operator -> () { return (DatumType *)CLock :: P(); } \
	operator DatumType * () { return (DatumType *)CLock :: P(); } \
}; \
\
inline void * operator new (size_t size, DatumType##DCreator &dcr, \
	DatumType *) { return dcr.Alloc (size); }

#else // _MSC_VER >= 1200

#define DeclareDLockBase(CT, DatumType)	\
\
class DatumType##Lock : public CLock { \
public: \
	DatumType##Lock (CNavigator &nav) : CLock (nav) {} \
	DatumType * operator -> () { return (DatumType *)CLock :: P(); } \
	operator DatumType * () { return (DatumType *)CLock :: P(); } \
}; \
\
class DatumType##DCreator : public CDCreator { \
public: \
	DatumType##DCreator (CT &c) : CDCreator ((CT##1 &)c, (CT##2 &)c) {}	\
	DatumType * operator -> () { return (DatumType *)CLock :: P(); } \
	operator DatumType * () { return (DatumType *)CLock :: P(); } \
}; \
\
inline void * operator new (size_t size, DatumType##DCreator &dcr, \
	DatumType *) { return dcr.Alloc (size); } 

#if _MSC_VER < 1200
#define DeclareDLock(CT,DatumType)	DeclareDLockBase(CT,DatumType)
#else
#define DeclareDLock(CT,DatumType)	DeclareDLockBase(CT,DatumType) \
inline void operator delete (void *pMem, DatumType##DCreator &dcr, 	\
	DatumType *) { dcr.Free (pMem); }
#endif // _MSC_VER < 1200

#endif // WIN32

#endif // NODCREATOR

#endif // _DCREATOR_HXX
