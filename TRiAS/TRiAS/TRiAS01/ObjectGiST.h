// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 25.01.2003 12:16:06 
//
// @doc
// @module ObjectGiST.h | Declaration of the <c CObjectGiST> class

#if !defined(_OBJECTGIST_H__DD4B14CB_4EA2_4C0C_96DF_1C7CEEC15710__INCLUDED_)
#define _OBJECTGIST_H__DD4B14CB_4EA2_4C0C_96DF_1C7CEEC15710__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//
#include "RSTree/RT.h"

///////////////////////////////////////////////////////////////////////////////
// 
class CObjectGiST
{
public:
	CObjectGiST(CONNECTFILTER *pFilter);
	~CObjectGiST();

	bool IsValid() { return m_rsTree.IsOpen(); }
	trias_gist::GiSTcursor *Search(double dXMin, double dXMax, double dYMin, double dYMax);

private:
	trias_gist::RT m_rsTree;
	os_string m_strTableName;
};

#endif // !defined(_OBJECTGIST_H__DD4B14CB_4EA2_4C0C_96DF_1C7CEEC15710__INCLUDED_)
