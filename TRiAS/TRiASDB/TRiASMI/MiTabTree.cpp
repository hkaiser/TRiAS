// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 19.01.2001 18:47:03 
//
// @doc
// @module CMiTabTree.cpp | Definition of the <c CCMiTabTree> class

#include "StdAfx.h"

#include "Strings.h"
#include "MiTabTree.h"

#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
namespace {
	inline int sign (double a) { return (a < 0) ? -1 : 1; }

	// Test, ob Stützstrecke (dX1, dY1) -> (dX2, dY2) das gegebenene Suchfenster
	// schneidet oder vollständig innerhalb liegt
	bool LineInContainer (
		double dX1, double dY1, double dX2, double dY2, 
		double dXMin, double dYMin, double dXMax, double dYMax)
	{
	double rdx, rdxa, rdxb, rdy, rdya, rdyb, rpa, rpb;

	// ein Streckenendpunkt im Container ?
		if ((dX1 >= dXMin) && (dX1 <= dXMax) && (dY1 >= dYMin) && (dY1 <= dYMax))
			return true;	// AnfangsPunkt auf Rand oder im Container

		if ((dX2 >= dXMin) && (dX2 <= dXMax) && (dY2 >= dYMin) && (dY2 <= dYMax))
			return true;	// EndPunkt auf Rand oder im Container 

	// beide Streckenendpunkte links, rechts, oberhalb, unterhalb Container ?
		if ((dX1 < dXMin) && (dX2 < dXMin))
			return false;	// X der Strecke < X des Containers

		if ((dX1 > dXMax) && (dX2 > dXMax)) 
			return false;	// X der Strecke > X des Containers

		if ((dY1 < dYMin) && (dY2 < dYMin))
			return false;	// Y der Strecke < Y des Containers

		if ((dY1 > dYMax) && (dY2 > dYMax))
			return false;	// Y der Strecke > Y des Containers
		
	double dX = dX2 - dX1;
	double dY = dY2 - dY1;

	// Fall, wenn DX oder DY = 0 (Strecke senkrecht bzw. waagerecht)
		if (0.0 == dX || 0.0 == dY)
			return true;	// Strecke auf Rand oder durch Container

	// Strecke schneidet Teilstueck des Containers ab oder nicht
	// Pinzip: gegenseitige Lage eines Punktepaares und einer Geraden,
	//         die durch 2 Punkte bestimmt ist !
		rdx = dX;
		rdy = dY;
		if (sign(dX) == sign(dY)) {
			rdxa = dXMax - dX1;
			rdya = dYMin - dY1;
			rdxb = dXMin - dX1;
			rdyb = dYMax - dY1;
		}
		else {
			rdxa = dXMin - dX1;
			rdya = dYMin - dY1;
			rdxb = dXMax - dX1;
			rdyb = dYMax - dY1;
		}
		rpa = rdx*rdya - rdy*rdxa;
		rpb = rdx*rdyb - rdy*rdxb;
		if(rpa == 0.0 || rpb == 0.0)
			return true;	// Strecke auf Eckpunkt des Containers

		if (sign(rpa) == sign(rpb))
			return false;	// Strecke außerhalb des Containers

		return true;		// Strecke durch Container
	}

// Bewegungsrichtung, wenn man bei 3 gegebenen Punkten P1(x1,y1), P2(x2,y2) und P3(x3,y3) vom
// ersten, zum zweiten und dann zum dritten geht; return-Werte sind
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn P2 zwischen P1 und P3 liegt bzw.
//    bei P1 == P2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn P1 zwischen P3 und P2 liegt
//  0 bei Kollinearität, wenn P3 zwischen P1 und P2 liegt bzw.
//    bei P1 == P3, P2 == P3, P1 == P2 == P3
	inline int TurnDirection (double x1, double y1, double x2, double y2, double x3, double y3)
	{
	double dx1 = x2 - x1;
	double dy1 = y2 - y1;
	double dx2 = x3 - x1;
	double dy2 = y3 - y1;

		if (dx1*dy2 > dy1*dx2)
			return +1;
		if (dx1*dy2 < dy1*dx2)
			return -1;
		if (dx1*dx2 < 0 || dy1*dy2 < 0)
			return -1;
		if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
			return +1;
		return 0;
	} // TurnDirection

// 2 Strecken (x11,y11)-(x21,y21) und (x12,y12)-(x22,y22) haben wenigstens einen Punkt
// gemeinsam; dann Rückgabe von true, sonst false
	inline bool Intersection (
		double x11, double y11, double x21, double y21, double x12, double y12, double x22, double y22)
	{
		return ((TurnDirection (x11, y11, x21, y21, x12, y12) *
				 TurnDirection (x11, y11, x21, y21, x22, y22)) <= 0) &&
				((TurnDirection (x12, y12, x22, y22, x11, y11) *
				  TurnDirection (x12, y12, x22, y22, x21, y21)) <= 0);
	}

// Lage des Punktes (x,y) bezüglich des geschlossenen Polygonzuges (pX, pY) der Länge lCnt
// return-Werte sind
//   S_OK     der Punkt liegt innerhalb der eingeschlossenen Fläche bzw. auf deren Kontur
//	 S_FALSE  der Punkt liegt außerhalb der Kontur
//   E_FAIL   Polygonzug ist entartet bzw. nicht geschlossen
	HRESULT PunktLage (double x, double y, const OGRRawPoint *ppts, int lCnt)
	{
		if (NULL == ppts)
			return E_POINTER;

		if (lCnt <= 3 ||								// Polygonzug ist entartet
			ppts[0].x != ppts[lCnt-1].x || ppts[0].y != ppts[lCnt-1].y)	// Polygonzug ist nicht geschlossen
		{
			return E_FAIL;
		}

	// Koordinaten der waagerechten Testlinie
	double xa = x, ya = y, xe = DBL_MAX, ye = y;

	long lCutCnt = 0;	// Zähler für echte Schnitte der Testlinie mit dem Polygonzug
	long j = lCnt - 2;	// Index des letzten Polygonpunktes, von dem bekannt ist, daß
						// er nicht auf der Testlinie liegt

		while (0 == TurnDirection (xa, ya, xe, ye, ppts[j].x, ppts[j].y)) {
			if (--j < 0)
				return E_FAIL;	// entarteter Polygonzug, d.h. alle Punkte liegen auf einer Geraden,
		}						// die mit der Trägergeraden der Testlinie identsch ist

	int iTD1, iTD2, iTD3;		// return-Werte von TurnDirection()

		for (long k = 0; k < lCnt-1; k++) {
		// Test, ob Punkt auf der Kontur der eingeschlossenen Fläche liegt
			if (0 == TurnDirection (ppts[k].x, ppts[k].y, ppts[k+1].x, ppts[k+1].y, x, y))
				return S_OK;	// Punkt liegt auf der Kontur

		// Im nachfolgenden if-Zweig wird der Fall behandelt, daß der nächste Punkt P[k] nicht auf
		// der waagerechten Testlinie liegt.
		// Liegt P[k] auf der Testlinie (else-Zweig), wird P[k] i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt im Dreieck P[k-1], P[k], P[k+1], ergibt sich durch das
		// Weglassen von P[k] eine Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
			if (0 != TurnDirection (xa, ya, xe, ye, ppts[k].x, ppts[k].y)) {
			// Zähler lCutCnt inkrementieren, wenn echter Schnitt vorliegt, d. h. P[k] und P[j]
			// auf verschiedenen Seiten der Testlinie liegen
				if (Intersection (ppts[k].x, ppts[k].y, ppts[j].x, ppts[j].y, xa, ya, xe, ye))
					lCutCnt++;
				j = k;
			}
			else {	// P[k] liegt auf der Testlinie
				iTD1 = TurnDirection (ppts[k].y, ppts[k].y, ppts[k+1].x, ppts[k+1].y, x, y);

				if (k > 0) {
					iTD2 = TurnDirection (ppts[k-1].x, ppts[k-1].y, ppts[k].x, ppts[k].y, x, y);
					iTD3 = TurnDirection (ppts[k+1].x, ppts[k+1].y, ppts[k-1].x, ppts[k-1].x, x, y);
				}
				else {   // k == 0
					iTD2 = TurnDirection (ppts[lCnt-2].x, ppts[lCnt-2].y, ppts[0].x, ppts[0].y, x, y);
					iTD3 = TurnDirection (ppts[1].x, ppts[1].y, ppts[lCnt-2].x, ppts[lCnt-2].y, x, y);
				}

				if (iTD1 >= 0 && iTD2 >= 0 && iTD3 >= 0) 	// konvexe Ecke des Polygonzuges:
					return S_OK;							// Punkt liegt innerhalb

				if (iTD1 <= 0 && iTD2 <= 0 && iTD3 <= 0) 	// konkave Ecke des Polygonzuges:
					return S_FALSE;							// Punkt liegt außerhalb
			}
		}

	// ungerade Schnittanzahl bedeutet Enthaltensein
		if (0 != (lCutCnt % 2))
			return S_OK;

		return S_FALSE;
	} // PunktLage

// Helperfunktion für Speicherverwaltung
	template<class T>
	inline T *SfRealloc(T *pMem, int nNewSize)
	{
		if (pMem == NULL)
			return ((T *) malloc(nNewSize));
		else
			return ((T *) realloc(pMem, nNewSize));
	}
}

///////////////////////////////////////////////////////////////////////////////
// Geometriebaum (Quadtree)
CMiTabTree::CMiTabTree (CMiTabLayer *pLayer, int nMaxDepth, double *padfBoundsMin, double *padfBoundsMax) :
	m_pLayer(pLayer), m_nMaxDepth(nMaxDepth), m_psRoot(NULL)
{
	_ASSERTE(NULL != padfBoundsMin || NULL != pLayer -> GetMiTabHandle());

// If no max depth was defined, try to select a reasonable one
// that implies approximately 8 shapes per node.
	if (0 == m_nMaxDepth && NULL != pLayer -> GetMiTabHandle()) {
	int nMaxNodeCount = 1;
	int nFeatureCount = m_pLayer -> GetObjectCount();

		while (4 * nMaxNodeCount < nFeatureCount)
		{
			++m_nMaxDepth;
			nMaxNodeCount = 2 * nMaxNodeCount;
		}
	}

// Allocate the root node.

// Assign the bounds to the root node. If none are passed in,
// use the bounds of the provided file otherwise the create
// function will have already set the bounds.
	if (NULL == padfBoundsMin) {
	double dBoundsMin[MITAB_DIMENSION], dBoundsMax[MITAB_DIMENSION];

		m_pLayer -> GetBoundingRect (&dBoundsMin[0], &dBoundsMin[1], &dBoundsMax[0], &dBoundsMax[1], false);
		m_psRoot = new CMiTabTreeNode(dBoundsMin, dBoundsMax);
	}
	else
		m_psRoot = new CMiTabTreeNode(padfBoundsMin, padfBoundsMax);
}

CMiTabTree::~CMiTabTree()
{
	DELETE_OBJ(m_psRoot);
}

HRESULT CMiTabTree::ReadFromFile()
{
// If we have a file, insert all it's shapes into the tree.
	if (NULL != m_pLayer -> GetMiTabHandle()) {
		for (long lObjCursor = mitab_c_next_feature_id(m_pLayer -> GetMiTabHandle(), -1);
			 -1 != lObjCursor;
			 lObjCursor = mitab_c_next_feature_id(m_pLayer -> GetMiTabHandle(), lObjCursor)) 
		{
		CMiTabObjectMBR Obj (mitab_c_read_feature(m_pLayer -> GetMiTabHandle(), lObjCursor));

			if (!AddObject(Obj))
				return E_OUTOFMEMORY;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recherchefunktionen

// Work function implementing CMiTabTreeFindLikelyShapes() on a
// tree node by tree node basis.
bool CMiTabTree::CollectFeatureIds(
	CMiTabTreeNode *psTreeNode, double *padfBoundsMin, double * padfBoundsMax,
	int *pnFeatureCount, int *pnMaxFeatures, long **ppanFeatureList)
{
// Does this node overlap the area of interest at all?  If not,	
// return without adding to the list at all.
	if (!psTreeNode->CheckBoundsOverlap(padfBoundsMin, padfBoundsMax))
		return true;

// Grow the list to hold the shapes on this node.
	if (*pnFeatureCount + psTreeNode->m_nFeatureCount > *pnMaxFeatures)
	{
		*pnMaxFeatures = (*pnFeatureCount + psTreeNode->m_nFeatureCount) * 2 + 20;

	long *panFeatureList = SfRealloc (*ppanFeatureList, sizeof(long) * *pnMaxFeatures);

		if (NULL != panFeatureList)
			*ppanFeatureList = panFeatureList;
		else
			return false;
	}

// Add the local nodes shapeids to the list.
	for (int i = 0; i < psTreeNode->m_nFeatureCount; ++i)
	{
		(*ppanFeatureList)[(*pnFeatureCount)++] = psTreeNode->m_pFeatureIds[i];
	}
	
// Recurse to subnodes if they exist.
	for (int j = 0; j < psTreeNode->m_nSubNodes; ++j)
	{
		if (NULL != psTreeNode->m_apsSubNode[j]) {
			if (!CollectFeatureIds(psTreeNode->m_apsSubNode[j], padfBoundsMin, padfBoundsMax, pnFeatureCount, pnMaxFeatures, ppanFeatureList))
				return false;		// Fehler, daher abbrechen
		}
	}
	return true;
}

// Find all shapes within tree nodes for which the tree node
// bounding box overlaps the search box.  The return value is
// an array of shapeids terminated by a -1.  The shapeids will
// be in order, as hopefully this will result in faster(more	
// sequential) reading from the file.
long *CMiTabTree::FindLikelyFeatures(double *padfBoundsMin, double *padfBoundsMax, int *pnFeatureCount)

{
long *panFeatureList = NULL;
int nMaxFeatures = 0;

// Perform the search by recursive descent.
	*pnFeatureCount = 0;
	if (!CollectFeatureIds(m_psRoot, padfBoundsMin, padfBoundsMax, pnFeatureCount, &nMaxFeatures, &panFeatureList))
		return NULL;

	sort(panFeatureList, panFeatureList + *pnFeatureCount);

// For now I just use a bubble sort to order the shapeids, but
// this should really be a quicksort.
//	for (int i = 0; i < *pnFeatureCount - 1; i++)
//	{
//		for (int j = 0; j <(*pnFeatureCount) - i - 1; j++)
//		{
//			if (panFeatureList[j] > panFeatureList[j + 1])
//			{
//				int nTempId;
//
//				nTempId = panFeatureList[j];
//				panFeatureList[j] = panFeatureList[j + 1];
//				panFeatureList[j + 1] = nTempId;
//			}
//		}
//	}
	return panFeatureList;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objekte eines Bereiches suchen
HRESULT CMiTabTree::TreeNodeSearch (
	double *padfBoundsMin, double *padfBoundsMax, 
	HRESULT (CALLBACK *pFcn)(mitab_feature, UINT_PTR), UINT_PTR dwData, bool fExact)
{
// Perform the search for likely candidates.  These are shapes 
// that fall into a tree node whose bounding box intersects our
// area of interest.
int	nFeatureCount = 0;
long *panHits = FindLikelyFeatures (padfBoundsMin, padfBoundsMax, &nFeatureCount);

	if (NULL == panHits)
		return S_OK;		// nothing found

// Read all of these shapes, and establish whether the shape's 
// bounding box actually intersects the area of interest.  Note
// that the bounding box could intersect the area of interest, 
// and the shape itself still not cross it but we don't try to 
// address that here.                                          
HRESULT hr = S_OK;

	for (int i = 0; i < nFeatureCount && SUCCEEDED(hr); i++) {
	CMiTabObject Object (mitab_c_read_feature (m_pLayer -> GetMiTabHandle(), panHits[i]));

		if (!Object)
			continue;
		
	double dBoundsMin[2];
	double dBoundsMax[2];

		mitab_c_get_mbr (Object, dBoundsMin[0], dBoundsMin[1], dBoundsMax[0], dBoundsMax[1]);
		if (CMiTabTreeNode::CheckBoundsOverlap (padfBoundsMin, padfBoundsMax, dBoundsMin, dBoundsMax))
		{
			if (!fExact || S_OK == CheckRealOverlap (Object, padfBoundsMin, padfBoundsMax))
				hr = pFcn (Object, dwData);
		}
	}
	free (panHits);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Test auf reale Überlappung des Testfensters mit einem ShapeObjekt
/* static */
HRESULT CMiTabTree::CheckRealOverlap (mitab_feature Obj, double *padfBoundsMin, double *padfBoundsMax)
{
	switch (mitab_c_get_type(Obj)) {
	case TABFC_Point:
	case TABFC_FontPoint:
	case TABFC_CustomPoint:
	case TABFC_Text:
		return S_OK;		// Punkte/Texte sind entweder drin, oder eben auch nicht ...

	case TABFC_Polyline:
		return CheckRealOverlapLine (Obj, padfBoundsMin, padfBoundsMax);

	case TABFC_Region:
	case TABFC_Rectangle:
		return CheckRealOverlapArea (Obj, padfBoundsMin, padfBoundsMax);

	case TABFC_NoGeom:
	case TABFC_Arc:
	case TABFC_Ellipse:
		break;				// not supported yet
	}
	return E_NOTIMPL;		// unbekannter Objekttyp
}

///////////////////////////////////////////////////////////////////////////////
// Überlappungstest für Flächen (mit Inseln)
/* static */
HRESULT CMiTabTree::CheckRealOverlapArea (
	mitab_feature obj, double *padfBoundsMin, double *padfBoundsMax)
{
int iParts = mitab_c_get_parts(obj);
int iVertices = mitab_c_get_vertex_count(obj, 0);
const OGRRawPoint *ppts = mitab_c_get_raw_coords(obj, 0);

	for (int iKnt = 0; iKnt < iParts; ++iKnt) {
		if (0 != iKnt) {
		// die nächste Kontur
			iVertices = mitab_c_get_vertex_count(obj, iKnt);
			ppts = mitab_c_get_raw_coords(obj, iKnt);
		}
		if (S_OK == CheckRealOverlapLine(ppts, iVertices, padfBoundsMin, padfBoundsMax))
			return S_OK;
	}

// keine der Stützstrecken schneidet das Suchfenster bzw. liegt innerhalb desselben

// Prüfung, ob 1 Eckpunkt des Suchfensters in Flächenumrandung liegt, dazu alle Polygone nochmal
// durchgehen und genauer hinsehen
	iVertices = mitab_c_get_vertex_count(obj, 0);
	ppts = mitab_c_get_raw_coords(obj, 0);
	for (int iKnt1 = 0; iKnt1 < iParts; ++iKnt1) {
		if (0 != iKnt1) {
		// nächste Kontur
			iVertices = mitab_c_get_vertex_count(obj, iKnt1);
			ppts = mitab_c_get_raw_coords(obj, iKnt1);
		}

	// alle Konturen separat behandeln
	HRESULT hr = PunktLage (padfBoundsMin[0], padfBoundsMin[1], ppts, iVertices);	// liefert Resultat in fInner

		if (FAILED(hr))
			return hr;

		if (0 == iKnt1) {		// Außenkontur
			if (S_FALSE == hr) 
				return S_FALSE;	// Punkt außerhalb äußerer Umrandung
		} 
		else if (S_OK == hr)	// Innenkontur
			return S_FALSE;		// Punkt im Loch
	} 
	return S_OK;		// Punkt in Fläche
}

///////////////////////////////////////////////////////////////////////////////
// Überlappungstest für Linien
/* static  */
HRESULT CMiTabTree::CheckRealOverlapLine (
	const OGRRawPoint *ppts, int iVertices, double *padfBoundsMin, double *padfBoundsMax)
{
	if (NULL == ppts)
		return S_FALSE;
		
double dX1, dY1, dX2, dY2;

	dX1 = ppts[0].x;		// erster Stützpunkt
	dY1 = ppts[0].y;

// sämtliche Stützstrecken durchgehen
	for (int i = 1; i < iVertices; ++i) {
		dX2 = ppts[i].x;
		dY2 = ppts[i].y;
		if (LineInContainer (dX1, dY1, dX2, dY2, padfBoundsMin[0], padfBoundsMin[1], padfBoundsMax[0], padfBoundsMax[1]))
			return S_OK;	// Stützstrecke schneidet Container oder liegt innerhalb

	// die nächste Stützstrecke
		dX1 = dX2;
		dY1 = dY2;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Nodeverwaltung
CMiTabTreeNode::CMiTabTreeNode(double *padfBoundsMin, double *padfBoundsMax) :
	m_nFeatureCount(0), m_pFeatureIds(NULL), m_nSubNodes(0)
{
	memset(m_apsSubNode, '\0', MAX_SUBNODE * sizeof(CMiTabTreeNode *));
	if (padfBoundsMin != NULL)
		memcpy(m_dBoundsMin, padfBoundsMin, MITAB_DIMENSION * sizeof(double));

	if (padfBoundsMax != NULL)
		memcpy(m_dBoundsMax, padfBoundsMax, MITAB_DIMENSION * sizeof(double));
}

CMiTabTreeNode::~CMiTabTreeNode()
{
	for (int i = 0; i < m_nSubNodes; ++i)
	{
		if (NULL != m_apsSubNode[i]) {
			DELETE_OBJ(m_apsSubNode[i]);
		}
	}
	free (m_pFeatureIds);		// wurde mit malloc/realloc angelegt
}

///////////////////////////////////////////////////////////////////////////////
// Does the given shape fit within the indicated extents?
/* static */
bool CMiTabTreeNode::CheckObjectContained(CMiTabObjectMBR &rObject, double *padfBoxMin, double *padfBoxMax)
{
double dXMin, dYMin, dXMax, dYMax;

	rObject.GetMBR(dXMin, dYMin, dXMax, dYMax);
	if (dXMin < padfBoxMin[0] || dXMax > padfBoxMax[0])
		return false;
	if (dYMin < padfBoxMin[1] || dYMax > padfBoxMax[1])
		return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Split a region into two subregion evenly, cutting along the
// longest dimension.
/* static */
void CMiTabTreeNode::SplitBounds(
	double *padfBoundsMinIn, double *padfBoundsMaxIn,
	double *padfBoundsMin1, double *padfBoundsMax1,
	double *padfBoundsMin2, double *padfBoundsMax2)
{
// The output bounds will be very similar to the input bounds, 
// so just copy over to start.
	memcpy(padfBoundsMin1, padfBoundsMinIn, sizeof(double) * MITAB_DIMENSION);
	memcpy(padfBoundsMax1, padfBoundsMaxIn, sizeof(double) * MITAB_DIMENSION);
	memcpy(padfBoundsMin2, padfBoundsMinIn, sizeof(double) * MITAB_DIMENSION);
	memcpy(padfBoundsMax2, padfBoundsMaxIn, sizeof(double) * MITAB_DIMENSION);
	
	if ((padfBoundsMaxIn[0] - padfBoundsMinIn[0]) > (padfBoundsMaxIn[1] - padfBoundsMinIn[1])) {
	// Split in X direction.
	double dfRange = (padfBoundsMaxIn[0] - padfBoundsMinIn[0]) * MITAB_SPLIT_RATIO;

		padfBoundsMax1[0] = padfBoundsMinIn[0] + dfRange;
		padfBoundsMin2[0] = padfBoundsMaxIn[0] - dfRange;
	}
	else {
	// Otherwise split in Y direction.
	double dfRange = (padfBoundsMaxIn[1] - padfBoundsMinIn[1]) * MITAB_SPLIT_RATIO;

		padfBoundsMax1[1] = padfBoundsMinIn[1] + dfRange;
		padfBoundsMin2[1] = padfBoundsMaxIn[1] - dfRange;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ein neues Objekt zum Baum hinzufügen
bool CMiTabTreeNode::AddObject(CMiTabObjectMBR &rObject, int nMaxDepth)
{
// If there are subnodes, then consider wiether this object
// will fit in them.
	if (nMaxDepth > 1 && m_nSubNodes > 0)
	{
		for (int i = 0; i < m_nSubNodes; ++i)
		{
			_ASSERTE(NULL != m_apsSubNode[i]);
			if (m_apsSubNode[i] -> CheckObjectContained(rObject)) 
				return m_apsSubNode[i] -> AddObject(rObject, nMaxDepth - 1);
		}
	}
	else if (nMaxDepth > 1 && 0 == m_nSubNodes)	{
	// Otherwise, consider creating four subnodes if could fit into	
	// them, and adding to the appropriate subnode.
	double adfBoundsMinH1[MITAB_DIMENSION], adfBoundsMaxH1[MITAB_DIMENSION];
	double adfBoundsMinH2[MITAB_DIMENSION], adfBoundsMaxH2[MITAB_DIMENSION];
	double adfBoundsMin1[MITAB_DIMENSION], adfBoundsMax1[MITAB_DIMENSION];
	double adfBoundsMin2[MITAB_DIMENSION], adfBoundsMax2[MITAB_DIMENSION];
	double adfBoundsMin3[MITAB_DIMENSION], adfBoundsMax3[MITAB_DIMENSION];
	double adfBoundsMin4[MITAB_DIMENSION], adfBoundsMax4[MITAB_DIMENSION];

		SplitBounds(m_dBoundsMin, m_dBoundsMax, adfBoundsMinH1, adfBoundsMaxH1, adfBoundsMinH2, adfBoundsMaxH2);
		SplitBounds(adfBoundsMinH1, adfBoundsMaxH1, adfBoundsMin1, adfBoundsMax1, adfBoundsMin2, adfBoundsMax2);
		SplitBounds(adfBoundsMinH2, adfBoundsMaxH2, adfBoundsMin3, adfBoundsMax3, adfBoundsMin4, adfBoundsMax4);

		if (CheckObjectContained(rObject, adfBoundsMin1, adfBoundsMax1) ||
			CheckObjectContained(rObject, adfBoundsMin2, adfBoundsMax2) ||
			CheckObjectContained(rObject, adfBoundsMin3, adfBoundsMax3) ||
			CheckObjectContained(rObject, adfBoundsMin4, adfBoundsMax4))
		{
			m_nSubNodes = 4;
			m_apsSubNode[0] = new CMiTabTreeNode(adfBoundsMin1, adfBoundsMax1);
			m_apsSubNode[1] = new CMiTabTreeNode(adfBoundsMin2, adfBoundsMax2);
			m_apsSubNode[2] = new CMiTabTreeNode(adfBoundsMin3, adfBoundsMax3);
			m_apsSubNode[3] = new CMiTabTreeNode(adfBoundsMin4, adfBoundsMax4);

		// recurse back on this node now that it has subnodes
			return AddObject(rObject, nMaxDepth);
		}
	}

// If none of that worked, just add it to this nodes list.
	++m_nFeatureCount;

long *pFeatureIds = SfRealloc(m_pFeatureIds, sizeof(long) * m_nFeatureCount);

	if (NULL != pFeatureIds) {
		m_pFeatureIds =	pFeatureIds;
		m_pFeatureIds[m_nFeatureCount - 1] = mitab_c_get_feature_id	(rObject);
		return true;
	}
	return false;
}

// This is the recurve version of CMiTabTreeTrimExtraNodes() that
// walks the tree cleaning it up.
bool CMiTabTreeNode::Trim()
{
// Trim subtrees, and free subnodes that come back empty.
	for (int i = 0; i < m_nSubNodes; ++i)
	{
		_ASSERTE(NULL != m_apsSubNode[i]);
		if (m_apsSubNode[i] -> Trim()) {
			DELETE_OBJ(m_apsSubNode[i]);
			m_apsSubNode[i] = m_apsSubNode[m_nSubNodes - 1];
			--m_nSubNodes;
			--i;	// process the new occupant of this subnode entry
		}
	}

// we should be trimmed if we have no subnodes, and no shapes.
	return (0 == m_nSubNodes && 0 == m_nFeatureCount) ? true : false;
}

