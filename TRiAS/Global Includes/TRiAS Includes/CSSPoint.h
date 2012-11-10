// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/01/1998 08:00:41 PM
//
// @doc
// @module CSSPoint.h | Description here

#if !defined(_CSSPOINT_H__C0875A94_1105_11D2_8663_00600875138A__INCLUDED_)
#define _CSSPOINT_H__C0875A94_1105_11D2_8663_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/vector>

/////////////////////////////////////////////////////////////////////////////
// 
#if !defined(__GMCSSTYPES_H__) && !defined(_CSPOINT_DEFINED)
#define _CSPOINT_DEFINED
struct CSPointBase
{
	double X;
	double Y;
	double Z;
};
#endif // __GMCSSTYPES_H__

///////////////////////////////////////////////////////////////////////////////
//
class CSPoint : public CSPointBase
{
public:
	CSPoint (double dx, double dy, double dz = 0.0)
	{
		X = dx; Y = dy; Z = dz;
	}
};
typedef vector<CSPointBase> CPoints;

#endif // !defined(_CSSPOINT_H__C0875A94_1105_11D2_8663_00600875138A__INCLUDED_)
