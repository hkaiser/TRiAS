//	Implementation of Glockenspiel Container release 2.0,
//
//	Glockenspiel's Framework for managing objects
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  BinNode.cxx - Implementation file for the BinaryNode class
//-------------------------------------------------------------------------

// #include <afx.h>
#include "contpre.hxx"

/*
IMPLEMENT_SERIAL (CBinaryNode, CKeyNode, 1)

#define new DEBUG_NEW
*/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


_DLLENTRY CBinaryNode :: CBinaryNode (void)
{
	m_pParent = m_pLeft = m_pRight = NULL;
}


_DLLENTRY CBinaryNode :: CBinaryNode (CTree &tr)
		       : CKeyNode (tr)
{
	m_pParent = m_pLeft = m_pRight = NULL;
}

_DLLENTRY CBinaryNode :: CBinaryNode (FSHandle h, CTree & tr, CBinaryNode *par)
		       : CKeyNode (h, tr)
{
	TX_ASSERT (par);

	m_pParent = par;
	m_pLeft = m_pRight = NULL;
}

CKeyNode * _DLLENTRY CBinaryNode :: Find (void *key) const
{
	TX_ASSERT (key);

	for (const CBinaryNode * look = this; look; ) {
	int cmp = look -> Compare (key);

		if (cmp > 0)		// key > this
			look = look -> m_pRight;
		else if (cmp < 0)	// key < this
			look = look -> m_pLeft;
		else				// key == this
			return (CKeyNode *) look;
	}

return 0;				// key not found
}

void _DLLENTRY CBinaryNode :: Graft (CBinaryNode * old, CBinaryNode * replace)
{
	if (m_pLeft == old)
		m_pLeft = replace;
	else
		m_pRight = replace;

	if (replace)
		replace -> m_pParent = this;
}

CBinaryNode * _DLLENTRY CBinaryNode :: RightMost (void) const
{
const CBinaryNode * righty = this;

	while (righty -> m_pRight)
		righty = righty -> m_pRight;

return (CBinaryNode *) righty;
}

CBinaryNode * _DLLENTRY CBinaryNode :: LeftMost (void) const
{
const CBinaryNode * lefty = this;

	while (lefty -> m_pLeft)
		lefty = lefty -> m_pLeft;

return (CBinaryNode *) lefty;
}

CBinaryNode * _DLLENTRY CBinaryNode :: LeftMostOrRight (void) const
{
const CBinaryNode * leftyOrRight = this;

	while (leftyOrRight -> m_pLeft || leftyOrRight -> m_pRight) {
		if (leftyOrRight -> m_pLeft)
			return leftyOrRight -> LeftMost ();
		else
			leftyOrRight = leftyOrRight -> m_pRight;
	}

return (CBinaryNode *) leftyOrRight;
}

CKeyNode * _DLLENTRY CBinaryNode :: Next (void) const
{
	if (m_pRight)
		return m_pRight -> LeftMost ();
	else {
	const CBinaryNode * bnode = this;
	
		while (bnode -> m_pParent -> m_pLeft != bnode)
			bnode = bnode -> m_pParent;

		bnode = bnode -> m_pParent;

		if (bnode -> m_pParent)
			return (CKeyNode *) bnode;
		else
			return NULL;
	}
}

CKeyNode * _DLLENTRY CBinaryNode :: Prev (void) const
{
	if (m_pLeft)
		return m_pLeft -> RightMost ();
	else {
	const CBinaryNode * bnode = this;
	
		while (bnode -> m_pParent && bnode -> m_pParent -> m_pRight != bnode)
			bnode = bnode -> m_pParent;

		return bnode -> m_pParent;
	}
}


// Serialisation support -----------------------------------------------------
/*
void _DLLENTRY CBinaryNode :: Serialize (CArchive &ar)
{
	CKeyNode :: Serialize (ar);
	
WORD fLeft, fRight;

	if (ar.IsStoring()) {
		fLeft = m_pLeft != NULL;
		fRight = m_pRight != NULL;

		ar << fLeft << fRight;
		if (fLeft) ar << m_pLeft;
		if (fRight) ar << m_pRight;
		{
		CNakedLock nl (NULL, GetHandle());
		
			ar << (CObject *)nl.P();
		}
	} else {
		ar >> fLeft >> fRight;	
		if (fLeft) {
			ar >> m_pLeft;
			m_pLeft -> SetParent (this);
			m_pLeft -> SetContainer (&GetContainer());
		}
		if (fRight) {
			ar >> m_pRight;		
			m_pRight -> SetParent (this);
			m_pRight -> SetContainer (&GetContainer());
		}
		{
		CObject *pObj;
		
			ar >> pObj;
			SetHandle ((FSHandle)pObj);
		}		
	} 
}

*/
