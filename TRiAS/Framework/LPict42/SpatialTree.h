// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.02.2002 12:11:55 
//
// @doc
// @module SpatialTree.h | Declaration of the <c CSpatialTree> class

#if !defined(_SPATIALTREE_H__8A6E1DAC_E554_4D08_9D7A_4A6CA96EA6A9__INCLUDED_)
#define _SPATIALTREE_H__8A6E1DAC_E554_4D08_9D7A_4A6CA96EA6A9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "PgrTile.h"

///////////////////////////////////////////////////////////////////////////////
// Typ der Enumerationsprozedur zum Zeichnen
typedef HRESULT (__stdcall *DRAWTILEPROC)(CPgrTile *pTile, CDC *pDC, 
	CRect const &rSrc, CRect const &rDest);

///////////////////////////////////////////////////////////////////////////////
// Konstanten
const int MAX_SUBNODE = 4;
const double SPATIALTREE_SPLIT_RATIO = 0.55;
const int SPATIALTREE_DIMENSION = 2;

///////////////////////////////////////////////////////////////////////////////
// ein Node aus dem Baum
class CSpatialTreeNode
{
public:
	friend class CSpatialTree;
	
	CSpatialTreeNode(double *pdBoundsMin, double *pdBoundsMax);
	~CSpatialTreeNode();

	bool AddTile(CPgrTile *pTile, int nMaxDepth);
	void Clear();		// alle Subnodes abräumen

	HRESULT TileSearch (double *padfBoundsMin, double *padfBoundsMax, 
		DRAWTILEPROC pfcnDrawTile, CDC *pDC, CRect const &rcSrc, CRect const &rcDst);

protected:
	bool CheckObjectContained(CPgrTile *pTile)
	{ 
		return CheckObjectContained(pTile, m_dBoundsMin, m_dBoundsMax); 
	}
	bool CheckBoundsOverlap(double *padfBoxMin, double *padfBoxMax)
	{ 
		return CheckBoundsOverlap(m_dBoundsMin, m_dBoundsMax, padfBoxMin, padfBoxMax); 
	}
	bool Trim();

	static void SplitBounds(double *padfBoundsMinIn, double *padfBoundsMaxIn,
		double *padfBoundsMin1, double *padfBoundsMax1,
		double *padfBoundsMin2, double *padfBoundsMax2);

// Do the given boxes overlap at all?
	static bool CheckBoundsOverlap(double *padfBoundsMin, double *padfBoundsMax, 
		double *padfBoxMin, double *padfBoxMax)
	{
		if (padfBoxMax[0] < padfBoundsMin[0] || padfBoundsMax[0] < padfBoxMin[0])
			return false;
		if (padfBoxMax[1] < padfBoundsMin[1] || padfBoundsMax[1] < padfBoxMin[1])
			return false;
		return true;
	}

// Does the given shape fit within the indicated extents?
	static bool CheckObjectContained(CPgrTile *pTile, double *padfBoxMin, 
		double *padfBoxMax)
	{
		if (pTile->GetXMin() < padfBoxMin[0] || pTile->GetXMax() > padfBoxMax[0])
			return false;
		if (pTile->GetYMin() < padfBoxMin[1] || pTile->GetYMax() > padfBoxMax[1])
			return false;

		return true;
	}

private:
// region covered by this node 
	double m_dBoundsMin[SPATIALTREE_DIMENSION];
	double m_dBoundsMax[SPATIALTREE_DIMENSION];

// list of shapes stored at this node. The papsShapeObj pointers or the whole list can be NULL 
	int m_nFeatureCount;
	CPgrTile **m_pFeatureIds;

	int m_nSubNodes;
	CSpatialTreeNode *m_apsSubNode[MAX_SUBNODE];
};

///////////////////////////////////////////////////////////////////////////////
// Der Baum an sich
class CSpatialTree 
{
public:
	CSpatialTree() : m_nMaxDepth(0), m_psRoot(NULL) {}
	~CSpatialTree();

// Initialisierung
	BOOL Init(long lShapeCount, double *padfBoundsMin, double *padfBoundsMax, 
		int nMaxDepth = 0);

// Add a shape to the tree
	int AddTile(CPgrTile *pTile)
	{ 
		_ASSERTE(NULL != m_psRoot); 
		return m_psRoot->AddTile(pTile, m_nMaxDepth); 
	}

// Recherchefunktionen
	HRESULT TileSearch (double *padfBoundsMin, double *padfBoundsMax, 
		DRAWTILEPROC pfcnDrawTile, CDC *pDC, CRect const &rcSrc, CRect const &rcDst)
	{
		_ASSERTE(NULL != m_psRoot);
		return m_psRoot->TileSearch(padfBoundsMin, padfBoundsMax, pfcnDrawTile,
			pDC, rcSrc, rcDst);
	}

// alles freigeben
	void Clear();

// Trim empty nodes from the tree.  Note that we never trim an empty root node.
	void TrimExtraNodes() 
	{ 
		_ASSERTE(NULL != m_psRoot); 
		m_psRoot -> Trim(); 
	}

protected:
	static bool CheckBoundsOverlap(double *, double *, double *, double *);

private:
	int m_nMaxDepth;
	CSpatialTreeNode *m_psRoot;
};

#endif // !defined(_SPATIALTREE_H__8A6E1DAC_E554_4D08_9D7A_4A6CA96EA6A9__INCLUDED_)
