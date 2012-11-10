#ifndef	__LAFXCOLL_H__
#define	__LAFXCOLL_H__

#include <afx.h>
#include "lmfcx/lafx.h"

#if _MFC_VER >= 0x0320
#include <afxplex_.h>
#endif


#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

/////////////////////////////////////////////////////////////////////////////
// Klassen
//  - Die Klassen sind weitetgehend selbsterklärend
//  - Die '//__' - Notation dient dem schnelleren Suchen. Vor jeder Klassendefinition
//    ist diese Zeichenkette zu finden, so daß schnell dorthin gesprungen werden
//    kann (ALT-F3!)
/////////////////////////////////////////////////////////////////////////////

// class	CObject;
	class	CDoubleArray;		//__CDoubleArray
	class	CPointArray;		//__CPointlArray
	class	CPointlArray;		//__CPointlArray
	class	CMapDWordToOb;		//__CMapDWordToOb
	class	CTree;
	class	CTreeInspector;

/////////////////////////////////////////////////////////////////////////////
//__CDoubleArray:
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CDoubleArray : public CObject
{
	DECLARE_SERIAL(CDoubleArray)
public:

// Construction
	CDoubleArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	double GetAt(int nIndex) const;
	void SetAt(int nIndex, double newElement);
	double& ElementAt(int nIndex);

	// Potentially growing the array
	void SetAtGrow(int nIndex, double newElement);
	int Add(double newElement);

	// overloaded operator helpers
	double operator[](int nIndex) const;
	double& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, double newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CDoubleArray* pNewArray);

// Implementation
protected:
	double* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CDoubleArray();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
//__CPointlArray:
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CPointlArray : public CObject
{
	DECLARE_SERIAL(CPointlArray)
public:

// Construction
	CPointlArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	POINTL GetAt(int nIndex) const;
	void SetAt(int nIndex, POINTL newElement);
	POINTL& ElementAt(int nIndex);

	// Potentially growing the array
	void SetAtGrow(int nIndex, POINTL newElement);
	int Add(POINTL newElement);

	// overloaded operator helpers
	POINTL operator[](int nIndex) const;
	POINTL& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, POINTL newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CPointlArray* pNewArray);

// Implementation
protected:
	POINTL* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CPointlArray();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
//__CPointArray:
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CPointArray : public CObject
{
	DECLARE_SERIAL(CPointArray)
public:

// Construction
	CPointArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	POINT GetAt(int nIndex) const;
	void SetAt(int nIndex, POINT newElement);
	POINT& ElementAt(int nIndex);

	// Potentially growing the array
	void SetAtGrow(int nIndex, POINT newElement);
	int Add(POINT newElement);

	// overloaded operator helpers
	POINT operator[](int nIndex) const;
	POINT& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, POINT newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CPointArray* pNewArray);

// Implementation
protected:
	POINT* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CPointArray();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
//__CMapDWordToOb:
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMapDWordToOb : public CObject
{
	DECLARE_SERIAL(CMapDWordToOb)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		CObject* value;
	};
public:

// Construction
	CMapDWordToOb(int nBlockSize=10);

// Attributes
	int GetCount() const;
	BOOL IsEmpty() const;
	BOOL Lookup(DWORD key, CObject*& rValue) const;

// Operations
	// Lookup and add if not there
	CObject*& operator[](DWORD key);

	// add a new (key, value) pair
	void SetAt(DWORD key, CObject* newValue);

	// removing existing (key, ?) pair; don't remove the contents!!!
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, CObject*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	~CMapDWordToOb();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

////////////////////////////////////////////////////////////////////////////
// Baum zur Abbildung von Hierarchien
// - Identifikation eines Node erfolgt über Zeichenkette
//   z.B.: "1.2.10"

class CTreeInspector : public CObject
{
	DECLARE_DYNAMIC( CTreeInspector )
public:
	virtual BOOL OnInspectNode( CTree* const pNode, CObject*& prNodeObject ) = 0;
	virtual	void Reset() = 0;
};

class CCountInspector;

class CTree : public CObject
{
	DECLARE_SERIAL( CTree )
protected:
	friend class CCountInspector;

// Construction
public:
	CTree( int iStartLevel = 1, BOOL bAutodeleteObjects = TRUE );
// Attributes
protected:
	CTree	*m_pParent;
	int			m_iLevel;
	int			m_nItems;
	BOOL		m_bAutodelete;
	CObject		*m_pObject;
	CObArray	m_arrayOfNodes;
	CWordArray	m_arrayOfIndexes;
// Implementation
public:
	virtual ~CTree( );

	//////////////////////////////////////////////////////////////////////
	// Informationen über den aktuellen Knoten

	int		GetLevel() const;		// bezogen auf den bei der Konstruktion angegebenen
	int		GetItems() const;		// Anzahl Elemente im Knoten
	CTree*	GetParent() const;		// Vaterknoten ermitteln
	
	//////////////////////////////////////////////////////////////////////
	// Element einfügen
	// -	liefert den vorher dem Knoten zugewiesenen Objektzeiger
	//		(also NULL, wenn bisher leer)

	CObject*	SetAt( const CTree* pNode, CObject* pObject );	// an bestimmten Knoten
	CObject*	SetAt( LPCTSTR pszNode, CObject* pObject );		// mit Knotensuche

	//////////////////////////////////////////////////////////////////////
	// Knoten / Elemente suchen
	// -	Achtung:
	//			pObject = GetNode( "1.1.3" )->GetObject(); nicht verwenden
	//		geht schief, wenn (NULL == GetNode( "1.1.3" )) !!!!
	// -	dafür:
	//			pObject = GetObject( "1.1.3" );

	CTree		*GetNode( LPCTSTR pszNode );	// NULL ... kein Knoten
	CObject		*GetObject( );					// NULL ... kein Objekt
	CObject		*GetObject( LPCTSTR pszNode );	// dito

	//////////////////////////////////////////////////////////////////////
	// Löschoperationen:
	//	-	Remove... Objekte / Knoten (inkl. Teilbaum) / Baum
	// 		werden gelöscht, OHNE die Objekte zu zerstören
	//	-	Delete... dasselbe MIT löschen

	BOOL		RemoveAll( );
	BOOL		DeleteAll( );
	CObject*	RemoveObjectAt( LPCTSTR pszNode );
	BOOL		DeleteObjectAt( LPCTSTR pszNode );
	CTree*		RemoveNodeAt( LPCTSTR pszNode );
	CTree*		DeleteNodeAt( LPCTSTR pszNode );
	
	//////////////////////////////////////////////////////////////////////
	// Baum durchlaufen

	void LTraverse( CTreeInspector* pInspector );	// linksseitig
	void RTraverse( CTreeInspector* pInspector );	// rechtsseitig
	void BTraverse( CTreeInspector* pInspector );	// rückwärts (vom Ausgangsknoten zum Toplevel)
	void BBTraverse( CTreeInspector* pInspector );	// rückwärts (erst hoch, dann zum Ausgangsknoten)

// CTree diagnostics
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFXCOLL_INLINE)
#define	_AFXCOLL_INLINE  inline
#endif
#include	"lmfcx/lafxcoll.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif			// __LAFXCOLL_H__
