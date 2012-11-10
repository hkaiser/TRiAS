// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.06.2000 03:16:11
//
// @doc
// @module ShapeGeometryTree.cpp | Implementation of the <c CShapeGeometryTree> class

#include "StdAfx.h"

#include <float.h>

#include "Strings.h"
#include "ShapeGeometryTree.h"
#include "ShapeLayer.h"

///////////////////////////////////////////////////////////////////////////////
// SHPTreeNodeSearchAndDump
HRESULT CShapeGeometryTree::TreeNodeSearch (
	double *padfBoundsMin, double *padfBoundsMax, 
	HRESULT (CALLBACK *pFcn)(SHPObject *, UINT_PTR), UINT_PTR dwData, bool fExact)
{
// Perform the search for likely candidates.  These are shapes 
// that fall into a tree node whose bounding box intersects our
// area of interest.
int	nShapeCount = 0;
int *panHits = SHPTreeFindLikelyShapes (m_pTree, padfBoundsMin, padfBoundsMax, &nShapeCount);

	if (NULL == panHits)
		return S_OK;		// nothing found

// Read all of these shapes, and establish whether the shape's 
// bounding box actually intersects the area of interest.  Note
// that the bounding box could intersect the area of interest, 
// and the shape itself still not cross it but we don't try to 
// address that here.                                          
HRESULT hr = S_OK;

	for (int i = 0; i < nShapeCount && SUCCEEDED(hr); i++) {
	CShapeObject Object (SHPReadObject (m_pTree -> hSHP, panHits[i]));

		if (!Object)
			continue;
		
		if (SHPCheckBoundsOverlap (padfBoundsMin, padfBoundsMax, &(Object -> dfXMin), &(Object -> dfXMax), m_pTree->nDimension))
		{
			if (!fExact || S_OK == CheckRealOverlap (Object, padfBoundsMin, padfBoundsMax))
				hr = pFcn (Object, dwData);
		}
	}
	free (panHits);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
namespace {
	inline int sign (double a) { return (a < 0) ? -1 : 1; }

	// Test, ob Stützstrecke (dX1, dY1) -> (dX2, dY2) das gegebenene Suchfenster
	// schneidet oder vollständig innerhalb liegt
	BOOL LineInContainer (
		double dX1, double dY1, double dX2, double dY2, 
		double dXMin, double dYMin, double dXMax, double dYMax)
	{
	double rdx, rdxa, rdxb, rdy, rdya, rdyb, rpa, rpb;

	// ein Streckenendpunkt im Container ?
		if ((dX1 >= dXMin) && (dX1 <= dXMax) && (dY1 >= dYMin) && (dY1 <= dYMax))
			return TRUE;	// AnfangsPunkt auf Rand oder im Container

		if ((dX2 >= dXMin) && (dX2 <= dXMax) && (dY2 >= dYMin) && (dY2 <= dYMax))
			return TRUE;	// EndPunkt auf Rand oder im Container 

	// beide Streckenendpunkte links, rechts, oberhalb, unterhalb Container ?
		if ((dX1 < dXMin) && (dX2 < dXMin))
			return FALSE;	// X der Strecke < X des Containers

		if ((dX1 > dXMax) && (dX2 > dXMax)) 
			return FALSE;	// X der Strecke > X des Containers

		if ((dY1 < dYMin) && (dY2 < dYMin))
			return FALSE;	// Y der Strecke < Y des Containers

		if ((dY1 > dYMax) && (dY2 > dYMax))
			return FALSE;	// Y der Strecke > Y des Containers
		
	double dX = dX2 - dX1;
	double dY = dY2 - dY1;

	// Fall, wenn DX oder DY = 0 (Strecke senkrecht bzw. waagerecht)
		if (0.0 == dX || 0.0 == dY)
			return TRUE;	// Strecke auf Rand oder durch Container

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
			return TRUE;	// Strecke auf Eckpunkt des Containers

		if (sign(rpa) == sign(rpb))
			return FALSE;	// Strecke außerhalb des Containers

		return TRUE;		// Strecke durch Container
	}

}

///////////////////////////////////////////////////////////////////////////////
// Test auf reale Überlappung des Testfensters mit einem ShapeObjekt
HRESULT CShapeGeometryTree::CheckRealOverlap (SHPObject *pObj, double *padfBoundsMin, double *padfBoundsMax)
{
	switch (pObj -> nSHPType) {
	case SHPT_POINT:
	case SHPT_POINTM:
	case SHPT_POINTZ:
		return S_OK;		// Punkte sind entweder drin, oder eben auch nicht ...

	case SHPT_MULTIPOINT:
	case SHPT_MULTIPOINTM:
	case SHPT_MULTIPOINTZ:
		break;

	case SHPT_ARC:
	case SHPT_ARCM:
	case SHPT_ARCZ:
		return CheckRealOverlapLine (pObj -> padfX, pObj ->padfY, pObj -> nVertices, padfBoundsMin, padfBoundsMax);

	case SHPT_POLYGON:
	case SHPT_POLYGONZ:
	case SHPT_POLYGONM:
		return CheckRealOverlapArea (pObj, padfBoundsMin, padfBoundsMax);
	}
	return E_NOTIMPL;		// unbekannter Objekttyp
}

///////////////////////////////////////////////////////////////////////////////
// Überlappungstest für Linien
HRESULT CShapeGeometryTree::CheckRealOverlapLine (
	double *pdX, double *pdY, int iVertices, double *padfBoundsMin, double *padfBoundsMax)
{
double dX1, dY1, dX2, dY2;

	dX1 = pdX[0];		// erster Stützpunkt
	dY1 = pdY[0];

// sämtliche Stützstrecken durchgehen
	for (int i = 1; i < iVertices; ++i) {
		dX2 = pdX[i];
		dY2 = pdY[i];
		if (LineInContainer (dX1, dY1, dX2, dY2, padfBoundsMin[0], padfBoundsMin[1], padfBoundsMax[0], padfBoundsMax[1]))
			return S_OK;	// Stützstrecke schneidet Container oder liegt innerhalb

	// die nächste Stützstrecke
		dX1 = dX2;
		dY1 = dY2;
	}
	return S_FALSE;
}

namespace {
// Lage des Punktes (x,y) bezüglich des geschlossenen Polygonzuges (pX, pY) der Länge lCnt
// return-Werte sind
//   S_OK     der Punkt liegt innerhalb der eingeschlossenen Fläche bzw. auf deren Kontur
//	 S_FALSE  der Punkt liegt außerhalb der Kontur
//   E_FAIL   Polygonzug ist entartet bzw. nicht geschlossen

	bool Intersection (double x11, double y11, double x21, double y21, double x12, double y12, double x22, double y22);
	int TurnDirection (double x1, double y1, double x2, double y2, double x3, double y3);

	HRESULT PunktLage (double x, double y, double* pX, double* pY, long lCnt)
	{
		if (NULL == pX || NULL == pY)
			return E_POINTER;

		if (lCnt <= 3 ||								// Polygonzug ist entartet
			pX[0] != pX[lCnt-1] || pY[0] != pY[lCnt-1])	// Polygonzug ist nicht geschlossen
		{
			return E_FAIL;
		}

	// Koordinaten der waagerechten Testlinie
	double xa = x, ya = y, xe = DBL_MAX, ye = y;

	long lCutCnt = 0;	// Zähler für echte Schnitte der Testlinie mit dem Polygonzug
	long j = lCnt - 2;	// Index des letzten Polygonpunktes, von dem bekannt ist, daß
						// er nicht auf der Testlinie liegt

		while (0 == TurnDirection (xa, ya, xe, ye, pX[j], pY[j])) {
			if (--j < 0)
				return E_FAIL;	// entarteter Polygonzug, d.h. alle Punkte liegen auf einer Geraden,
		}						// die mit der Trägergeraden der Testlinie identsch ist

	int iTD1, iTD2, iTD3;		// return-Werte von TurnDirection()

		for (long k = 0; k < lCnt-1; k++) {
		// Test, ob Punkt auf der Kontur der eingeschlossenen Fläche liegt
			if (0 == TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y))
				return S_OK;	// Punkt liegt auf der Kontur

		// Im nachfolgenden if-Zweig wird der Fall behandelt, daß der nächste Punkt P[k] nicht auf
		// der waagerechten Testlinie liegt.
		// Liegt P[k] auf der Testlinie (else-Zweig), wird P[k] i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt im Dreieck P[k-1], P[k], P[k+1], ergibt sich durch das
		// Weglassen von P[k] eine Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
			if (0 != TurnDirection (xa, ya, xe, ye, pX[k], pY[k])) {
			// Zähler lCutCnt inkrementieren, wenn echter Schnitt vorliegt, d. h. P[k] und P[j]
			// auf verschiedenen Seiten der Testlinie liegen
				if (Intersection (pX[k], pY[k], pX[j], pY[j], xa, ya, xe, ye))
					lCutCnt++;
				j = k;
			}
			else {	// P[k] liegt auf der Testlinie
				iTD1 = TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y);

				if (k > 0) {
					iTD2 = TurnDirection (pX[k-1], pY[k-1], pX[k], pY[k], x, y);
					iTD3 = TurnDirection (pX[k+1], pY[k+1], pX[k-1], pY[k-1], x, y);
				}
				else {   // k == 0
					iTD2 = TurnDirection (pX[lCnt-2], pY[lCnt-2], pX[0], pY[0], x, y);
					iTD3 = TurnDirection (pX[1], pY[1], pX[lCnt-2], pY[lCnt-2], x, y);
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


// Bewegungsrichtung, wenn man bei 3 gegebenen Punkten P1(x1,y1), P2(x2,y2) und P3(x3,y3) vom
// ersten, zum zweiten und dann zum dritten geht; return-Werte sind
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn P2 zwischen P1 und P3 liegt bzw.
//    bei P1 == P2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn P1 zwischen P3 und P2 liegt
//  0 bei Kollinearität, wenn P3 zwischen P1 und P2 liegt bzw.
//    bei P1 == P3, P2 == P3, P1 == P2 == P3
	int TurnDirection (double x1, double y1, double x2, double y2, double x3, double y3)
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
	bool Intersection (double x11, double y11, double x21, double y21, double x12, double y12,
					   double x22, double y22)
	{
		return ((TurnDirection (x11, y11, x21, y21, x12, y12) *
				 TurnDirection (x11, y11, x21, y21, x22, y22)) <= 0) &&
				((TurnDirection (x12, y12, x22, y22, x11, y11) *
				  TurnDirection (x12, y12, x22, y22, x21, y21)) <= 0);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Überlappungstest für Flächen (mit Inseln)
HRESULT CShapeGeometryTree::CheckRealOverlapArea (
	SHPObject *pObj, double *padfBoundsMin, double *padfBoundsMax)
{
double *pdX = pObj -> padfX;
double *pdY = pObj -> padfY;
unsigned long ulCnt;

	if (1 == pObj -> nParts) 
		ulCnt = pObj -> nVertices;
	else
		ulCnt = pObj -> panPartStart[1];

	for (int iKnt = 0; iKnt < pObj -> nParts; ++iKnt) {
		if (0 != iKnt) {
		// die nächste Kontur
			pdX += ulCnt;
			pdY += ulCnt;

			if (iKnt == pObj -> nParts -1)
				ulCnt = pObj -> nVertices - pObj -> panPartStart[iKnt];			// letztes Polygon
			else
				ulCnt = pObj -> panPartStart[iKnt+1] - pObj -> panPartStart[iKnt];
		}
		if (S_OK == CheckRealOverlapLine(pdX, pdY, ulCnt, padfBoundsMin, padfBoundsMax))
			return S_OK;
	}

// keine der Stützstrecken schneidet das Suchfenster bzw. liegt innerhalb desselben

// Prüfung, ob 1 Eckpunkt des Suchfensters in Flächenumrandung liegt, dazu alle Polygone nochmal
// durchgehen und genauer hinsehen
	pdX = pObj -> padfX;  
	pdY = pObj -> padfY;  
	if (1 == pObj -> nParts) 
		ulCnt = pObj -> nVertices;
	else
		ulCnt = pObj -> panPartStart[1];

	for (int iKnt1 = 0; iKnt1 < pObj -> nParts; ++iKnt1) {
		if (0 != iKnt1) {
		// nächste Kontur
			pdX += ulCnt;
			pdY += ulCnt;

			if (iKnt1 == pObj -> nParts -1)
				ulCnt = pObj -> nVertices - pObj -> panPartStart[iKnt1];			// letztes Polygon
			else
				ulCnt = pObj -> panPartStart[iKnt1+1] - pObj -> panPartStart[iKnt1];
		}

	// alle Konturen separat behandeln
	HRESULT hr = PunktLage (padfBoundsMin[0], padfBoundsMin[1], pdX, pdY, ulCnt);	// liefert Resultat in fInner

		if (FAILED(hr))
			return hr;

		if (0 == iKnt1) {		// Außenkontur
			if (S_FALSE == hr) 
				return S_FALSE;		// Punkt außerhalb äußerer Umrandung
		} 
		else if (S_OK == hr)	// Innenkontur
			return S_FALSE;			// Punkt im Loch
	} 
	return S_OK;		// Punkt in Fläche
}

