// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 19.01.2001 18:55:59 
//
// @doc
// @module CMiTabTree.h | Declaration of the <c CCMiTabTree> class

#if !defined(_CMiTabTree_H__571A93AA_6573_47C8_989A_D86B86A7B067__INCLUDED_)
#define _CMiTabTree_H__571A93AA_6573_47C8_989A_D86B86A7B067__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include "MiTabLayer.h"

///////////////////////////////////////////////////////////////////////////////
// Konstanten
const int MAX_SUBNODE = 4;
const double MITAB_SPLIT_RATIO = 0.55;
const int MITAB_DIMENSION = 2;

///////////////////////////////////////////////////////////////////////////////
// ein Node aus dem Baum
class CMiTabTreeNode
{
public:
	friend class CMiTabTree;
	
	CMiTabTreeNode(double *pdBoundsMin, double *pdBoundsMax);
	~CMiTabTreeNode();

	bool AddObject(CMiTabObjectMBR &rObject, int nMaxDepth);

protected:
	bool CheckObjectContained(CMiTabObjectMBR &rObject)
		{ return CheckObjectContained(rObject, m_dBoundsMin, m_dBoundsMax); }
	bool CheckBoundsOverlap(double *padfBoxMin, double *padfBoxMax)
		{ return CheckBoundsOverlap(m_dBoundsMin, m_dBoundsMax, padfBoxMin, padfBoxMax); }

	bool Trim();

	static void SplitBounds(double *padfBoundsMinIn, double *padfBoundsMaxIn,
		double *padfBoundsMin1, double *padfBoundsMax1,
		double *padfBoundsMin2, double *padfBoundsMax2);

// Do the given boxes overlap at all?
	static bool CheckBoundsOverlap(double *padfBoundsMin, double *padfBoundsMax, double *padfBoxMin, double *padfBoxMax)
	{
		if (padfBoxMax[0] < padfBoundsMin[0] || padfBoundsMax[0] < padfBoxMin[0])
			return false;
		if (padfBoxMax[1] < padfBoundsMin[1] || padfBoundsMax[1] < padfBoxMin[1])
			return false;
		return true;
	}
	static bool CheckObjectContained(CMiTabObjectMBR &rObject, double *padfBoxMin, double *padfBoxMax);

private:
// region covered by this node 
	double m_dBoundsMin[MITAB_DIMENSION];
	double m_dBoundsMax[MITAB_DIMENSION];

// list of shapes stored at this node. The papsShapeObj pointers or the whole list can be NULL 
	int m_nFeatureCount;
	long *m_pFeatureIds;

	int m_nSubNodes;
	CMiTabTreeNode *m_apsSubNode[MAX_SUBNODE];
};

///////////////////////////////////////////////////////////////////////////////
// Der Baum an sich
class CMiTabTree 
{
public:
	CMiTabTree(CMiTabLayer *pLayer, int nMaxDepth = 0, double *padfBoundsMin = NULL, double *padfBoundsMax = NULL);
	~CMiTabTree();

	HRESULT ReadFromFile();

// Add a shape to the tree, but don't keep a pointer to the object data, just keep the shapeid.
	int AddObject(CMiTabObjectMBR &rObject)
		{ _ASSERTE(NULL != m_psRoot); return m_psRoot->AddObject(rObject, m_nMaxDepth); }
//	int RemoveObject(int nFeatureId);

// Recherchefunktionen
	HRESULT SearchObjects (double *pdWindow, HRESULT (CALLBACK *pFcn)(mitab_feature, UINT_PTR), UINT_PTR dwData, bool fExact = FALSE)
	{
		if (NULL == pdWindow)
			return E_POINTER;

		RETURN_FAILED_HRESULT(TreeNodeSearch(&pdWindow[0], &pdWindow[2], pFcn, dwData, fExact));
		return S_OK;
	}

protected:
// Trim empty nodes from the tree.  Note that we never trim an empty root node.
	void TrimExtraNodes() { _ASSERTE(NULL != m_psRoot); m_psRoot -> Trim(); }

	HRESULT TreeNodeSearch (double *padfBoundsMin, double *padfBoundsMax, 
		HRESULT (CALLBACK *pFcn)(mitab_feature, UINT_PTR), UINT_PTR dwData, bool fExact = false);

	long *FindLikelyFeatures(double *padfBoundsMin, double *padfBoundsMax, int *pnFeatureCount);
	bool CollectFeatureIds(CMiTabTreeNode *psTreeNode, double *padfBoundsMin, double *padfBoundsMax,
		int *GetFeatureCount, int *pnMaxFeatures, long **ppanFeatureList);

	static HRESULT CheckRealOverlap (mitab_feature Obj, double *padfBoundsMin, double *padfBoundsMax);
	static HRESULT CheckRealOverlapLine (mitab_feature obj, double *padfBoundsMin, double *padfBoundsMax)
		{ return CheckRealOverlapLine(mitab_c_get_raw_coords(obj, 0), mitab_c_get_vertex_count(obj, 0), padfBoundsMin, padfBoundsMax); }
	static HRESULT CheckRealOverlapLine (const OGRRawPoint *ppts, int iVertices, double *padfBoundsMin, double *padfBoundsMax);
	static HRESULT CheckRealOverlapArea (mitab_feature Obj, double *padfBoundsMin, double *padfBoundsMax);

	static bool CheckBoundsOverlap(double *, double *, double *, double *);

private:
	CMiTabLayer *m_pLayer;
	int m_nMaxDepth;
	CMiTabTreeNode *m_psRoot;
};

#endif // !defined(_CMiTabTree_H__571A93AA_6573_47C8_989A_D86B86A7B067__INCLUDED_)
