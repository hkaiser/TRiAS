// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
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

///////////////////////////////////////////////////////////////////////////////
// Konstanten
const int MAX_SUBNODE = 4;
const double SPATIALTREE_SPLIT_RATIO = 0.55;
const int SPATIALTREE_DIMENSION = 2;

///////////////////////////////////////////////////////////////////////////////
// ein verwaltetes Objekt
class CObjectWithRect
{
public:
	CObjectWithRect(IUnknown *pIUnk, double dXMin, double dYMin, double dXMax, double dYMax) :
		m_Unk(pIUnk), m_dXMin(dXMin), m_dYMin(dYMin), m_dXMax(dXMax), m_dYMax(dYMax)
	{
	}

	IUnknown *GetUnknown() { return m_Unk; }		// no AddRef()
	double &XMin() { return m_dXMin; }
	double &YMin() { return m_dYMin; }
	double &XMax() { return m_dXMax; }
	double &YMax() { return m_dYMax; }

private:
	WUnknown m_Unk;
	double m_dXMin;
	double m_dYMin;
	double m_dXMax;
	double m_dYMax;
};

///////////////////////////////////////////////////////////////////////////////
// ein Node aus dem Baum
class CSpatialTreeNode
{
public:
	friend class CSpatialTree;
	
	CSpatialTreeNode(double *pdBoundsMin, double *pdBoundsMax);
	~CSpatialTreeNode();

	bool AddObject(CObjectWithRect &Object, int nMaxDepth);

protected:
	bool CheckObjectContained(CObjectWithRect &rObject)
	{ 
		return CheckObjectContained(rIObject, m_dBoundsMin, m_dBoundsMax); 
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
	static bool CheckObjectContained(_DGMGeometry *pObject, 
		double *padfBoxMin, double *padfBoxMax);

private:
// region covered by this node 
	double m_dBoundsMin[SPATIALTREE_DIMENSION];
	double m_dBoundsMax[SPATIALTREE_DIMENSION];

// list of shapes stored at this node. The papsShapeObj pointers or the whole list can be NULL 
	int m_nFeatureCount;
	IUnknown **m_pFeatureIds;

	int m_nSubNodes;
	CSpatialTreeNode *m_apsSubNode[MAX_SUBNODE];
};

///////////////////////////////////////////////////////////////////////////////
// Der Baum an sich
class CSpatialTree 
{
public:
	CSpatialTree(long lShapeCount, double *padfBoundsMin, double *padfBoundsMax, 
		int nMaxDepth = 0);
	~CSpatialTree();

// Add a shape to the tree
	int AddObject(CObjectWithRect &rObject, long lId)
	{ 
		_ASSERTE(NULL != m_psRoot); 
		return m_psRoot->AddObject(rObject, m_nMaxDepth); 
	}
//	int RemoveObject(int nFeatureId);

// Recherchefunktionen
	HRESULT SearchObjects (double *pdWindow, 
		HRESULT (CALLBACK *pFcn)(IUnknown *, UINT_PTR), UINT_PTR dwData, 
		bool fExact = FALSE)
	{
		if (NULL == pdWindow)
			return E_POINTER;

		RETURN_FAILED_HRESULT(TreeNodeSearch(&pdWindow[0], &pdWindow[2], pFcn, 
			dwData, fExact));
		return S_OK;
	}

protected:
// Trim empty nodes from the tree.  Note that we never trim an empty root node.
	void TrimExtraNodes() 
	{ 
		_ASSERTE(NULL != m_psRoot); 
		m_psRoot -> Trim(); 
	}

	HRESULT TreeNodeSearch (double *padfBoundsMin, double *padfBoundsMax, 
		HRESULT (CALLBACK *pFcn)(IUnknown *, UINT_PTR), UINT_PTR dwData, 
		bool fExact = false);

	_DGMGeometry **FindLikelyFeatures(double *padfBoundsMin, double *padfBoundsMax, 
		int *pnFeatureCount);
	bool CollectFeatureIds(CSpatialTreeNode *psTreeNode, double *padfBoundsMin, 
		double *padfBoundsMax, int *GetFeatureCount, int *pnMaxFeatures, 
		IUnknown * **ppanFeatureList);

	static HRESULT CheckRealOverlap (_DGMGeometry *Obj, double *padfBoundsMin, 
		double *padfBoundsMax);
	static HRESULT CheckRealOverlapLine (_DGMGeometry *pIObj, 
		double *padfBoundsMin, double *padfBoundsMax);
	HRESULT CheckRealOverlapLine (CSCOORD const *ppts, int iVertices, 
		double *padfBoundsMin, double *padfBoundsMax);
	static HRESULT CheckRealOverlapArea (_DGMGeometry *pIObj, 
		double *padfBoundsMin, double *padfBoundsMax);

	static bool CheckBoundsOverlap(double *, double *, double *, double *);

private:
	int m_nMaxDepth;
	CSpatialTreeNode *m_psRoot;
};

#endif // !defined(_SPATIALTREE_H__8A6E1DAC_E554_4D08_9D7A_4A6CA96EA6A9__INCLUDED_)
