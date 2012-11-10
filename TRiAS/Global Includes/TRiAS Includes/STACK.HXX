// Implementation eines allgemeinen Stack's
// File: STACK.HXX

#if !defined(_STACK_HXX)
#define _STACK_HXX

#include <containr.hxx>

// Generischer Stack ----------------------------------------------------------
#if defined(WIN16)

#define Stack(DatumType)						\
class DatumType##Stack : public CListContainer {                       	\
protected: inline void UserDelete (void *); 				\
public:	DatumType##Stack (void) {}                             		\
	DatumType##Stack (CFreeStore &fs) : CListContainer (fs) {}     	\
	inline BOOL isValidTop (void);					\
	inline void Push (DatumType &);					\
	inline DatumType Pop (void);                                    \
	inline DatumType Top (void);					\
	~DatumType##Stack (void) { EveryDelete(); }			\
};                                                                      \
DeclareLock (DatumType##Stack, DatumType);				\
inline void DatumType##Stack :: Push (DatumType &DatumPar) {		\
DatumType##Creator DTC(*this);                                          \
	Create (DTC, DatumType) (DatumPar);                             \
}                                                                       \
inline DatumType DatumType##Stack :: Pop (void) {	    		\
DatumType RetVal; CRing r(*this); r.Last(); 				\
	{ DatumType##Lock l(r);	RetVal = *l; }				\
	r.Delete();                                             	\
return RetVal;								\
}									\
inline BOOL DatumType##Stack :: isValidTop (void) {			\
CRing r(*this); r.Last(); return r.Valid();				\
}									\
inline DatumType DatumType##Stack :: Top (void) {			\
CRing r(*this); r.Last();						\
	{ DatumType##Lock l(r);	return *l; }				\
}									\
inline void DatumType##Stack :: UserDelete (void *p##DatumType) {	\
	((DatumType *)p##DatumType)-> /*DatumType ::*/ ~DatumType ();	\
}

#else // WIN16

#define Stack(DatumType)						\
class DatumType##Stack : public CListContainer {                       	\
protected: inline void UserDelete (void *); 				\
public:	DatumType##Stack (void) {}                             		\
	inline BOOL isValidTop (void);					\
	inline void Push (DatumType &);					\
	inline DatumType Pop (void);                                    \
	inline DatumType Top (void);					\
	~DatumType##Stack (void) { EveryDelete(); }			\
};                                                                      \
DeclareLock (DatumType##Stack, DatumType);				\
inline void DatumType##Stack :: Push (DatumType &DatumPar) {		\
DatumType##Creator DTC(*this);                                          \
	ContCreate (DTC, DatumType) (DatumPar);                         \
}                                                                       \
inline DatumType DatumType##Stack :: Pop (void) {	    		\
DatumType RetVal; CRing r(*this); r.Last(); 				\
	{ DatumType##Lock l(r);	RetVal = *l; }				\
	r.Delete();                                             	\
return RetVal;								\
}									\
inline BOOL DatumType##Stack :: isValidTop (void) {			\
CRing r(*this); r.Last(); return r.Valid();				\
}									\
inline DatumType DatumType##Stack :: Top (void) {			\
CRing r(*this); r.Last();						\
	{ DatumType##Lock l(r);	return *l; }				\
}									\
inline void DatumType##Stack :: UserDelete (void *p##DatumType) {	\
	((DatumType *)p##DatumType)-> /*DatumType ::*/ ~DatumType ();	\
}

#endif // WIN16

// ----------------------------------------------------------------------------

#endif // _STACK_HXX
