#include "stdafx.h"

#ifdef LAFX_COLL_SEG
#pragma code_seg(LAFX_COLL_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: tree.cpp 1.1 1996/07/12 17:16:21 andy Exp $";
/* $Log: tree.cpp $
// Revision 1.1  1996/07/12  17:16:21  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CTree, CObject, 0 );
IMPLEMENT_DYNAMIC( CTreeInspector, CObject )

#define new DEBUG_NEW

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// realisiert Zähloperationen über dem Baum

class CCountInspector : public CTreeInspector
{
	DECLARE_DYNAMIC( CCountInspector )

// Construction
public:
	CCountInspector() : m_nItems( 0 ), m_nLeafs( 0 )		{ }

// Overrives
public:
	virtual BOOL	OnInspectNode( CTree* pNode, CObject* pNodeObject );
	virtual	void	Reset();

// Attributes
protected:
	long	m_nItems;
	long	m_nLeafs;
public:
	long	Nodes();
	long	Leafs();
	long	Items();
};

///////////////////////////////////////////////////////////////////////////
// Implementierung CCountInspector

BOOL CCountInspector::OnInspectNode( CTree* pNode, CObject* pNodeObject )
{
	m_nItems += pNode->GetItems();
	m_nLeafs += 0 == pNode->GetItems() && NULL != pNode->GetObject() ? 1 : 0;
	return TRUE;
}

inline long CCountInspector::Nodes()	{ return m_nItems - m_nLeafs; }
inline long CCountInspector::Leafs()	{ return m_nLeafs; }
inline long CCountInspector::Items()	{ return m_nItems; }
inline void CCountInspector::Reset()	{ m_nItems = m_nLeafs = 0; }

///////////////////////////////////////////////////////////////////////////
// Implementierung CTree

CTree::CTree( int level, BOOL bAutodelete )
{
	m_iLevel = level;
	m_nItems = 0;
	m_pObject = NULL;
	m_bAutodelete = bAutodelete;
	m_pParent = NULL;
}

CTree::~CTree( )
{
	CObject	*pNode;
	for( int i = 0; i < m_arrayOfNodes.GetSize(); i++ )
	{
		if( NULL != ( pNode = m_arrayOfNodes.GetAt( i ) ) )
			delete pNode;
		m_arrayOfNodes.SetAt( i, NULL );
	}
	m_arrayOfNodes.RemoveAll();
	if( m_bAutodelete && NULL != m_pObject )
	{
		ASSERT_VALID( m_pObject );
		ASSERT( m_pObject->IsKindOf( RUNTIME_CLASS( CObject ) ) );
		delete m_pObject;
	}
}

CObject* CTree::SetAt( LPCTSTR pszLevel, CObject* pObject )
{
	int	iThisLevel = atoi( pszLevel );

	if( 0 == iThisLevel )		// Blatt
	{
		CObject*	pOldObject = m_pObject;
		m_pObject = pObject;
		return pOldObject;
	}

	CTree	*pNode;

	if( m_arrayOfNodes.GetSize() <= iThisLevel || NULL == (  pNode = (CTree*) m_arrayOfNodes.GetAt( iThisLevel ) ) )
	{
		pNode = new CTree( m_iLevel + 1 );
		pNode->m_pParent = this;
		m_arrayOfNodes.SetAtGrow( iThisLevel, (CObject*&) pNode );
		m_arrayOfIndexes.SetAtGrow( m_nItems++, iThisLevel );
	}

	char	*pszNextLevel = (char*) pszLevel + strspn( pszLevel, "0123456789" );
	if( '\0' != *pszNextLevel )
		pszNextLevel += strcspn( pszNextLevel, "0123456789" );

	return pNode->SetAt( pszNextLevel, pObject );
}

CTree* CTree::GetNode( LPCTSTR pszNode )
{
	int	iThisLevel = atoi( pszNode );
	if( 0 == iThisLevel )		// Blatt
	{
		return this;
	}
	CTree	*pNode;
	if( iThisLevel >= m_arrayOfNodes.GetSize() || NULL == ( pNode = (CTree*) m_arrayOfNodes.GetAt( iThisLevel ) ) )
		return NULL;
	
	char	*pszNextNode = (char*) pszNode + strspn( pszNode, "0123456789" );
	if( '\0' != *pszNextNode )
		pszNextNode += strcspn( pszNextNode, "0123456789" );
	return pNode->GetNode( pszNextNode );
}

void CTree::LTraverse( CTreeInspector *pInspect )
{
	ASSERT( NULL != pInspect && pInspect->IsKindOf( RUNTIME_CLASS( CTreeInspector ) ) );

	CTree	*pNode;
	if( !pInspect->OnInspectNode( this, m_pObject ) )
		return;
	for( int i = 0; i < m_arrayOfIndexes.GetSize(); i++ )
	{
		pNode = (CTree*) m_arrayOfNodes[ m_arrayOfIndexes.GetAt(i) ];
		ASSERT( NULL != pNode && pNode->IsKindOf( RUNTIME_CLASS( CTree ) ) );
		pNode->LTraverse( pInspect );
	}
}

void CTree::BTraverse( CTreeInspector* pInspector )
{
	ASSERT( NULL != pInspector && pInspector->IsKindOf( RUNTIME_CLASS( CTreeInspector ) ) );
	if( !pInspector->OnInspectNode( this, m_pObject ) )
		return;
	if( NULL != m_pParent )
		m_pParent->BTraverse( pInspector );
}

void CTree::BBTraverse( CTreeInspector* pInspector )
{
	ASSERT( NULL != pInspector && pInspector->IsKindOf( RUNTIME_CLASS( CTreeInspector ) ) );
	if( NULL != m_pParent )
		m_pParent->BBTraverse( pInspector );
	if( !pInspector->OnInspectNode( this, m_pObject ) )
		return;
}

#ifdef _DEBUG

void CTree::AssertValid() const
{
	CObject::AssertValid();
	ASSERT( NULL == m_pObject || m_pObject->IsKindOf( RUNTIME_CLASS( CObject ) ) );
}

void CTree::Dump(CDumpContext& dc) const
{
	ASSERT_VALID( this );
	CObject::Dump( dc );

	dc << "{" << m_iLevel << "/" << m_nItems << "/" << (void FAR*) m_pObject << "}\n";
	if( m_pObject )
		m_pObject->Dump( dc );
	if( m_arrayOfNodes.GetSize() )
		m_arrayOfNodes.Dump( dc );
//	m_arrayOfIndexes.Dump( dc );
}
#endif	// _DEBUG

#undef new

IMPLEMENT_DYNAMIC( CCountInspector, CTreeInspector )
