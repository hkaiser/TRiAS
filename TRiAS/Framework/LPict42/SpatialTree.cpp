// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.02.2002 12:12:06 
//
// @doc
// @module SpatialTree.cpp | Definition of the <c CSpatialTree> class

#include "StdAfx.h"

#include "LPictImpl.h"
#include "SpatialTree.h"

#include <limits>
#include <ospace/std/algorithm>

///////////////////////////////////////////////////////////////////////////////
// nützliche Makros
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) {if(NULL==x){}else{delete(x);(x)=NULL;}}
#endif // !DELETE

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
namespace {
// Helperfunktion für Speicherverwaltung
	template <typename T>
	inline T *SfRealloc(T *pMem, int nNewSize)
	{
		if (pMem == NULL)
			return ((T *) malloc(nNewSize));
		else
			return ((T *) realloc(pMem, nNewSize));
	}
	template <typename T>
	inline void SfFree(T *pMem)
	{
		free (pMem);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Geometriebaum (Quadtree)
BOOL CSpatialTree::Init (long lTileCnt, double *padfBoundsMin, 
		double *padfBoundsMax, int nMaxDepth)
{
	DELETE_OBJ(m_psRoot);

	_ASSERTE(NULL != padfBoundsMin && NULL != padfBoundsMax);

// If no max depth was defined, try to select a reasonable one
// that implies approximately 8 shapes per node.
	if (0 == nMaxDepth) {
	int nMaxNodeCount = 1;

		while (4 * nMaxNodeCount < lTileCnt)
		{
			++nMaxDepth;
			nMaxNodeCount = 2 * nMaxNodeCount;
		}
	}
	m_nMaxDepth = nMaxDepth;

// Allocate the root node.

// Assign the bounds to the root node. If none are passed in,
// use the bounds of the provided file otherwise the create
// function will have already set the bounds.
	ATLTRY(m_psRoot = new CSpatialTreeNode(padfBoundsMin, padfBoundsMax));
	return (NULL != m_psRoot) ? TRUE : FALSE;
}

CSpatialTree::~CSpatialTree()
{
	DELETE_OBJ(m_psRoot);
}

void CSpatialTree::Clear()
{
	if (NULL != m_psRoot)
		m_psRoot->Clear();		// nur Subnodes abräumen
}

///////////////////////////////////////////////////////////////////////////////
// Recherchefunktionen

// alle Tiles eines Bereiches enumerieren
HRESULT CSpatialTreeNode::TileSearch (
	double *padfBoundsMin, double *padfBoundsMax, 
	DRAWTILEPROC pfcnDrawTile, CDC *pDC, CRect const &rcSrc, CRect const &rcDst)
{
// Does this node overlap the area of interest at all?  If not,	
// return without adding to the list at all.
	if (!CheckBoundsOverlap(padfBoundsMin, padfBoundsMax))
		return S_OK;	// Node ist außerhalb des untersuchten Bereiches

// enumerate local tiles
HRESULT hr = S_OK;

	for (int i = 0; i < m_nFeatureCount && S_OK == hr; ++i) {
		_ASSERTE(NULL != m_pFeatureIds[i]);

	double dBoundsMin[2] = { m_pFeatureIds[i]->GetXMin(), m_pFeatureIds[i]->GetYMin() };
	double dBoundsMax[2] = { m_pFeatureIds[i]->GetXMax(), m_pFeatureIds[i]->GetYMax() };
	
		if (CSpatialTreeNode::CheckBoundsOverlap (padfBoundsMin, padfBoundsMax, 
				dBoundsMin, dBoundsMax))
		{
			hr = pfcnDrawTile (m_pFeatureIds[i], pDC, rcSrc, rcDst);
		}
	}
	if (S_OK != hr)
		return hr;

// Recurse to subnodes if they exist.
	for (int j = 0; j < m_nSubNodes; ++j) {
		if (NULL != m_apsSubNode[j]) {
			hr = m_apsSubNode[j]->TileSearch(padfBoundsMin, padfBoundsMax, pfcnDrawTile, pDC, rcSrc, rcDst);
			if (S_OK != hr)
				return hr;		// Fehler oder abgebrochen, daher aufhören
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Nodeverwaltung
CSpatialTreeNode::CSpatialTreeNode(double *padfBoundsMin, double *padfBoundsMax) :
	m_nFeatureCount(0), m_pFeatureIds(NULL), m_nSubNodes(0)
{
	memset(m_apsSubNode, '\0', MAX_SUBNODE * sizeof(CSpatialTreeNode *));
	if (padfBoundsMin != NULL)
		memcpy(m_dBoundsMin, padfBoundsMin, SPATIALTREE_DIMENSION * sizeof(double));

	if (padfBoundsMax != NULL)
		memcpy(m_dBoundsMax, padfBoundsMax, SPATIALTREE_DIMENSION * sizeof(double));
}

CSpatialTreeNode::~CSpatialTreeNode()
{
	Clear();
}

void CSpatialTreeNode::Clear()
{
	for (int i = 0; i < m_nSubNodes; ++i) {
		DELETE_OBJ(m_apsSubNode[i]);
	}
	m_nSubNodes = 0;

	for (int j = 0; j < m_nFeatureCount; ++j) {
		DELETE_OBJ(m_pFeatureIds[j]);
	}
	m_nFeatureCount = 0;
	SfFree (m_pFeatureIds);		// wurde mit malloc/realloc angelegt
	m_pFeatureIds = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Split a region into two subregion evenly, cutting along the
// longest dimension.
/* static */
void CSpatialTreeNode::SplitBounds(
	double *padfBoundsMinIn, double *padfBoundsMaxIn,
	double *padfBoundsMin1, double *padfBoundsMax1,
	double *padfBoundsMin2, double *padfBoundsMax2)
{
// The output bounds will be very similar to the input bounds, 
// so just copy over to start.
	memcpy(padfBoundsMin1, padfBoundsMinIn, sizeof(double) * SPATIALTREE_DIMENSION);
	memcpy(padfBoundsMax1, padfBoundsMaxIn, sizeof(double) * SPATIALTREE_DIMENSION);
	memcpy(padfBoundsMin2, padfBoundsMinIn, sizeof(double) * SPATIALTREE_DIMENSION);
	memcpy(padfBoundsMax2, padfBoundsMaxIn, sizeof(double) * SPATIALTREE_DIMENSION);
	
	if ((padfBoundsMaxIn[0] - padfBoundsMinIn[0]) > (padfBoundsMaxIn[1] - padfBoundsMinIn[1])) {
	// Split in X direction.
	double dfRange = (padfBoundsMaxIn[0] - padfBoundsMinIn[0]) * 
		SPATIALTREE_SPLIT_RATIO;

		padfBoundsMax1[0] = padfBoundsMinIn[0] + dfRange;
		padfBoundsMin2[0] = padfBoundsMaxIn[0] - dfRange;
	}
	else {
	// Otherwise split in Y direction.
	double dfRange = (padfBoundsMaxIn[1] - padfBoundsMinIn[1]) * 
		SPATIALTREE_SPLIT_RATIO;

		padfBoundsMax1[1] = padfBoundsMinIn[1] + dfRange;
		padfBoundsMin2[1] = padfBoundsMaxIn[1] - dfRange;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ein neues Objekt zum Baum hinzufügen
bool CSpatialTreeNode::AddTile(CPgrTile *pTile, int nMaxDepth)
{
// If there are subnodes, then consider wether this object
// will fit in them.
	if (nMaxDepth > 1 && m_nSubNodes > 0) {
		for (int i = 0; i < m_nSubNodes; ++i) {
			_ASSERTE(NULL != m_apsSubNode[i]);
			if (m_apsSubNode[i] -> CheckObjectContained(pTile)) 
				return m_apsSubNode[i] -> AddTile(pTile, nMaxDepth - 1);
		}
	}
	else if (nMaxDepth > 1 && 0 == m_nSubNodes)	{
	// Otherwise, consider creating four subnodes if could fit into	
	// them, and adding to the appropriate subnode.
	double adfBoundsMinH1[SPATIALTREE_DIMENSION], adfBoundsMaxH1[SPATIALTREE_DIMENSION];
	double adfBoundsMinH2[SPATIALTREE_DIMENSION], adfBoundsMaxH2[SPATIALTREE_DIMENSION];
	double adfBoundsMin1[SPATIALTREE_DIMENSION], adfBoundsMax1[SPATIALTREE_DIMENSION];
	double adfBoundsMin2[SPATIALTREE_DIMENSION], adfBoundsMax2[SPATIALTREE_DIMENSION];
	double adfBoundsMin3[SPATIALTREE_DIMENSION], adfBoundsMax3[SPATIALTREE_DIMENSION];
	double adfBoundsMin4[SPATIALTREE_DIMENSION], adfBoundsMax4[SPATIALTREE_DIMENSION];

		SplitBounds(m_dBoundsMin, m_dBoundsMax, adfBoundsMinH1, adfBoundsMaxH1, adfBoundsMinH2, adfBoundsMaxH2);
		SplitBounds(adfBoundsMinH1, adfBoundsMaxH1, adfBoundsMin1, adfBoundsMax1, adfBoundsMin2, adfBoundsMax2);
		SplitBounds(adfBoundsMinH2, adfBoundsMaxH2, adfBoundsMin3, adfBoundsMax3, adfBoundsMin4, adfBoundsMax4);

		if (CheckObjectContained(pTile, adfBoundsMin1, adfBoundsMax1) ||
			CheckObjectContained(pTile, adfBoundsMin2, adfBoundsMax2) ||
			CheckObjectContained(pTile, adfBoundsMin3, adfBoundsMax3) ||
			CheckObjectContained(pTile, adfBoundsMin4, adfBoundsMax4))
		{
			m_nSubNodes = 4;
			ATLTRY((
				m_apsSubNode[0] = new CSpatialTreeNode(adfBoundsMin1, adfBoundsMax1),
				m_apsSubNode[1] = new CSpatialTreeNode(adfBoundsMin2, adfBoundsMax2),
				m_apsSubNode[2] = new CSpatialTreeNode(adfBoundsMin3, adfBoundsMax3),
				m_apsSubNode[3] = new CSpatialTreeNode(adfBoundsMin4, adfBoundsMax4)
			));

		// recurse back on this node now that it has subnodes
			return AddTile(pTile, nMaxDepth);
		}
	}

// If none of that worked, just add it to this nodes list.
	++m_nFeatureCount;

CPgrTile * *pFeatureIds = SfRealloc(m_pFeatureIds, sizeof(CPgrTile *) * m_nFeatureCount);

	if (NULL != pFeatureIds) {
		m_pFeatureIds =	pFeatureIds;
		ATLTRY(m_pFeatureIds[m_nFeatureCount - 1] = new CPgrTile(*pTile));
		return true;
	}
	return false;
}

// This is the recurve version of CSpatialTreeTrimExtraNodes() that
// walks the tree cleaning it up.
bool CSpatialTreeNode::Trim()
{
// Trim subtrees, and free subnodes that come back empty.
	for (int i = 0; i < m_nSubNodes; ++i) {
		_ASSERTE(NULL != m_apsSubNode[i]);
		if (m_apsSubNode[i] -> Trim()) {
			_ASSERTE(0 == m_apsSubNode[i] -> m_nSubNodes && 
				0 == m_apsSubNode[i] -> m_nFeatureCount);

			DELETE_OBJ(m_apsSubNode[i]);
			m_apsSubNode[i] = m_apsSubNode[m_nSubNodes - 1];
			--m_nSubNodes;
			--i;	// process the new occupant of this subnode entry
		}
	}

	for (int j = m_nSubNodes; j < MAX_SUBNODE; ++j)
		m_apsSubNode[j] = NULL;		// avoid confusion

// we should be trimmed if we have no subnodes, and no shapes.
	return (0 == m_nSubNodes && 0 == m_nFeatureCount) ? true : false;
}

