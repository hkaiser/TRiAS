//	Header file for Computer Associates FreeStore release 2.0
//
//  Copyright (c) 1992 Trischford Limited 
//  (A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//  FreeStor.hxx - FreeStore 2.0 Header file
//
//-------------------------------------------------------------------------

#ifndef _FREESTOR_HXX
#define _FREESTOR_HXX

#include <cxxtypes.hxx>

#if defined(MSCC8) || defined(__WATCOMC__)
typedef int (*pNewHandler) (size_t);
#else
typedef void (*pNewHandler) (void);
#endif

class DS_LinkedList;

class CFreeStore // : public CObject
{
private:
friend	void  *  	operator new    (size_t);
friend	void		operator delete (void  *);

protected:
#if defined(MSWIND) && !defined(WIN32)
		DS_LinkedList *DS_List;
#endif

	pNewHandler	m_pAllocHandler;
	int		m_cNoSelected;
	
public:
//	DECLARE_SERIAL (CFreeStore);
//	void Serialize (CArchive &ar);
	
		CFreeStore (void);

virtual	FSHandle	Alloc (size_t);	
virtual	void		Dealloc (FSHandle);
virtual void *		Lock (FSHandle);
virtual void		Unlock (FSHandle);
virtual FSHandle	GetHandle (void *);
virtual void *		Load (void);
virtual void		Save (void *);

	pNewHandler	SetNewHandler (pNewHandler);
	pNewHandler 	GetNewHandler (void) const;
	void		Select (void);
	void		DeSelect (void);

virtual		~CFreeStore (void);
};
typedef CFreeStore * pFreeStore;

typedef struct tagALLOCPTR ALLOCPTR;	// forward declaration
typedef struct tagALLOCPTR {
	size_t stSize;		// Größe der Allozierung
	size_t stInvSize;	// Inverses Bitmuster
	ulong ulCnt;		// Nummer der Allozierung
	ALLOCPTR *pPrev;	// vorhergehende Allozierung
	ALLOCPTR *pNext;	// nächster in der Kette
} ALLOCPTR;
	
class CFindBugFS : public CFreeStore
{
private:
#ifdef MSWIND
	Bool		m_fDebugging;
#endif
	CFreeStore * 	m_pNormalFS;
	ulong		m_ulBytes;
	ulong		m_ulAllocations;
	ulong		m_ulCnt;	// Zähler der Allozierungen
	
	ALLOCPTR *	m_pChunks;	// AllozierungsKette

	void		ErrorOut (char *, ...);
	void		Abort(void);

public:
		CFindBugFS (CFreeStore *);

	FSHandle	Alloc (size_t);
	void		Dealloc (FSHandle);
	void *		Lock (FSHandle);
	void		Unlock (FSHandle);
	FSHandle	GetHandle (void *);

	ulong		BytesAllocated (void);
	ulong		ChunksAllocated (void);

		~CFindBugFS (void);
};

#ifdef MSWIND

class CWindowsFS : public CFreeStore
{
public:
//	DECLARE_SERIAL (CWindowsFS);
//	void Serialize (CArchive &ar);
	
#if defined(WIN32)
	inline	CWindowsFS (void) {}	// nothing to do
	inline	~CWindowsFS (void) {}
#else
		CWindowsFS (void);
		~CWindowsFS (void);
#endif // WIN32
};

class CLocalAllocator : public CFreeStore
{
public:
//	DECLARE_SERIAL (CLocalAllocator);
//	void Serialize (CArchive &ar);
	
		CLocalAllocator (void);

	FSHandle	Alloc (size_t);
	void		Dealloc (FSHandle);
	void *		Lock (FSHandle);
	void		Unlock (FSHandle);
	FSHandle      	GetHandle (void *);

		~CLocalAllocator (void);
};

#if !defined(WIN32)
class CGlobalAllocator : public CFreeStore
{
public:
//	DECLARE_SERIAL (CGlobalAllocator);
//	void Serialize (CArchive &ar);
	
               	CGlobalAllocator (void);

	FSHandle	Alloc (size_t);
	void		Dealloc (FSHandle);
	void *		Lock (FSHandle);
	void		Unlock (FSHandle);
   	FSHandle	GetHandle (void *);

		~CGlobalAllocator (void);
};

class CSharedAllocator : public CGlobalAllocator
{
public:
//	DECLARE_SERIAL (CSharedAllocator);
//	void Serialize (CArchive &ar);
	
		CSharedAllocator (void);

	FSHandle	Alloc (size_t);

		~CSharedAllocator (void);
};
#endif // WIN32
#endif   // MSWIND

//	And for compatibility with AT&T

#if defined(MSCC8) || defined(__WATCOMC__)
#include <new.h>
#endif

extern pNewHandler set_new_handler (pNewHandler);

void * operator new (size_t, void *);
void * operator new (size_t, CFreeStore &);

#endif
