// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.06.2000 15:04:07 
//
// @doc
// @module ShapeGeometryTree.h | Declaration of the <c CShapeGeometryTree> class

#if !defined(_SHAPEGEOMETRYTREE_H__0B7816A3_4C8F_48D4_8D6D_10B46633EDF1__INCLUDED_)
#define _SHAPEGEOMETRYTREE_H__0B7816A3_4C8F_48D4_8D6D_10B46633EDF1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "ShapeLib/Shapefil.h"

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse für Geometrie-QueadTree
class CShapeGeometryTree
{
public:
	CShapeGeometryTree() : 
		m_pTree(NULL) 
	{
	}
	~CShapeGeometryTree() 
	{
		Tidy();
	}

	HRESULT CreateTree (SHPHandle hSHP)
	{
		COM_TRY {
			Tidy();

		// Build a quadtree structure for this file
			m_pTree = SHPCreateTree (hSHP, 2, 0, NULL, NULL);
			if (NULL == m_pTree) return E_OUTOFMEMORY;

		// Trim unused nodes from the tree
			SHPTreeTrimExtraNodes(m_pTree);

		} COM_CATCH;
		return S_OK;
	}

	HRESULT SearchObjects (double *pdWindow, HRESULT (CALLBACK *pFcn)(SHPObject *, UINT_PTR), UINT_PTR dwData, bool fExact = FALSE)
	{
		if (NULL == pdWindow)
			return E_POINTER;

		RETURN_FAILED_HRESULT(TreeNodeSearch(&pdWindow[0], &pdWindow[2], pFcn, dwData, fExact));
		return S_OK;
	}

protected:
	void Tidy()
	{
		if (NULL != m_pTree) {
			SHPDestroyTree(m_pTree);
			m_pTree = NULL;
		}
	}
	HRESULT TreeNodeSearch(double *padfBoundsMin, double *padfBoundsMax, HRESULT (CALLBACK *pFcn)(SHPObject *, UINT_PTR), UINT_PTR dwData, bool fExact);
	HRESULT CheckRealOverlap (SHPObject *pObj, double *padfBoundsMin, double *padfBoundsMax);
	HRESULT CheckRealOverlapLine (double *pdX, double *pdY, int iVertices, double *padfBoundsMin, double *padfBoundsMax);
	HRESULT CheckRealOverlapArea (SHPObject *pObj, double *padfBoundsMin, double *padfBoundsMax);

private:
	SHPTree *m_pTree;
};

#endif // !defined(_SHAPEGEOMETRYTREE_H__0B7816A3_4C8F_48D4_8D6D_10B46633EDF1__INCLUDED_)
