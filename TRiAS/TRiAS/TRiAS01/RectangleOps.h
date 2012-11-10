// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.01.2003 19:03:37 
//
// @doc
// @module RectangleOps.h | Definition of Rectangle operations

#if !defined(_RECTANGLEOPS_H__79AEEDFE_AE40_4C53_ABB1_C33713DA5858__INCLUDED_)
#define _RECTANGLEOPS_H__79AEEDFE_AE40_4C53_ABB1_C33713DA5858__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Testen, ob Punkt innerhalb eines rechteckigen Bereiches liegt
inline
bool PointInRect(double const x, double const y, CONNECTFILTEREX const *pFilter)
{
	return	x >= pFilter->m_dXMin && x <= pFilter->m_dXMax && 
			y >= pFilter->m_dYMin && y <= pFilter->m_dYMax;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob STützstrecke innerhalb eines rechteckigen Bereiches liegt
inline 
bool SegmentInRect (double const x1, double const y1, double const x2, 
	double const y2, CONNECTFILTEREX const *pFilter)
{
	return	PointInRect(x1, y1, pFilter) && PointInRect(x2, y2, pFilter);
}

///////////////////////////////////////////////////////////////////////////////
// Disjoint
inline
bool Disjoint (double const *pdCont, CONNECTFILTEREX const *pFilter)
{
	if (pdCont[XMAX_IDX] < pFilter->m_dXMin || pdCont[XMIN_IDX] > pFilter->m_dXMax ||
		pdCont[YMAX_IDX] < pFilter->m_dYMin || pdCont[YMIN_IDX] > pFilter->m_dYMax)
	{
		return true;	// disjoint containers
	}
	return false;
}

inline
bool Disjoint (double const dXMin, double const dYMin, double const dXMax, 
	double const dYMax, CONNECTFILTEREX const *pFilter)
{
	if (dXMin < pFilter->m_dXMin || dYMin > pFilter->m_dXMax ||
		dXMax < pFilter->m_dYMin || dYMax > pFilter->m_dYMax)
	{
		return true;	// disjoint containers
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// 
inline
bool Inside(double const *pdCont, CONNECTFILTEREX const *pFilter)
{
	if (pdCont[XMIN_IDX] >= pFilter->m_dXMin && pdCont[XMAX_IDX] <= pFilter->m_dXMax &&
		pdCont[YMIN_IDX] >= pFilter->m_dYMin && pdCont[YMAX_IDX] <= pFilter->m_dYMax)
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// 
inline
bool Contain(double const *pdCont, CONNECTFILTEREX const *pFilter)
{
	if (pdCont[XMIN_IDX] < pFilter->m_dXMin && pdCont[XMAX_IDX] > pFilter->m_dXMax &&
		pdCont[YMIN_IDX] < pFilter->m_dYMin && pdCont[YMAX_IDX] > pFilter->m_dYMax)
	{
		return true;
	}
	return false;
}

#endif // !defined(_RECTANGLEOPS_H__79AEEDFE_AE40_4C53_ABB1_C33713DA5858__INCLUDED_)
