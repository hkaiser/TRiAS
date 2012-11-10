//  Usage: #include <ctrtypes.hxx>
//
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
//  ctrtypes.hxx - Containers 2.0 Forward declarations
//-------------------------------------------------------------------------

#ifndef _CTRTYPES_HXX
#define _CTRTYPES_HXX

#if defined(WIN32)

#if defined(__CTRDLL__)
#define _CTR_ENTRY32 __declspec(dllexport)
#else
#define _CTR_ENTRY32 __declspec(dllimport)
#endif // defined(__CTRDLL__)

#define	_DLLENTRY
#define _DISPATCH_ENTRY		
#define	PASCAL_FUNC

#else // WIN32

#if defined(__BCPLUSPLUS__)
#define _DLLENTRY		_export
#define	_DLLENTRY_NODATA	_export
#define _DISPATCH_ENTRY		_export
#define	PASCAL_FUNC		_pascal
#else
#define _DLLENTRY		__export
#define	_DLLENTRY_NODATA	__export
#define _DISPATCH_ENTRY		__loadds
#define	PASCAL_FUNC		__pascal
#define _CTR_ENTRY32		
#endif

#endif // WIN32

#include <cxxtypes.hxx>

#define MAX_NAVIGATORS	10

// pGenericFcn is used by Container::Every()
typedef void 	(*pGenericFcn) (void *);
typedef BOOL	(*pGenericDataFcn) (void *, void *);

// pGetKeyFcn is used by KeyContainer
typedef void *	(*pGetKeyFcn) (void *);

// pKeyCmpFcn is used by KeyContainer
typedef int	(*pKeyCmpFcn) (void *key1, void *key2);

// pHashFcn is used by HashTable
typedef uint	(*pHashFcn) (void *key);

extern _CTR_ENTRY32 int StrCmp (void *str1, void *str2);
extern _CTR_ENTRY32 int IntCmp (void *pint1, void *pint2);

extern _CTR_ENTRY32 uint StrHash (void *keystr);
extern _CTR_ENTRY32 uint IntHash (void *keyint);

class CContainer;
class 	CSeqContainer;
class		CArrayContainer;
class		CListContainer;
class	CKeyContainer;
class		CHashTable;
class		CTree;

class CNavigator;
class	CRing;
class	CTable;

class CNode;
class	CSeqNode;
class		CArrayNode;
class		CListNode;
class	CKeyNode;
class		CHashNode;
class		CHListNode;
class		CBinaryNode;

class CLock;
class 	CCreator;

#endif // _CTRTYPES_HXX
