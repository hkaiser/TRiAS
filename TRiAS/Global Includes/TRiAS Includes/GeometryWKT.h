// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.08.2001 21:05:30 
//
// @doc
// @module GeometryWKT.h | Declaration of the <c CGeometryWKT> class

#if !defined(_GEOMETRYWKT_H__D16D8B7D_B2B4_44F4_9162_C0FEE7E1A33C__INCLUDED_)
#define _GEOMETRYWKT_H__D16D8B7D_B2B4_44F4_9162_C0FEE7E1A33C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#pragma warning (disable: 4192)	// automatically excluding 'IMoniker' while importing type library

/////////////////////////////////////////////////////////////////////////////
// Includes
#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/PBasic.tlh>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#import <tlb/tdbgeo.tlb>			\
	no_namespace					\
	raw_native_types				\
	raw_interfaces_only				\
	named_guids						\
	no_implementation				\
	exclude("IPersist", "IPersistMemory")

#include <CSSPoint.h>
#include <ScaleHeader.h>

namespace trias_geometrywkt {

class CMakeWKT 
{
public:
	CMakeWKT(CScaleHeader &rHdr) :
		m_rHdr(rHdr)
	{
	}
	~CMakeWKT()
	{
	}

	HRESULT AppendPoint (CComBSTR &rbstr, double dX, double dY, bool fAppendComma = true);

private:
	CScaleHeader &m_rHdr;
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CreatePointWKTFromVertices (CScaleHeader &rHdr, double_v &rX, double_v &rY, BSTR *pbstrWKT);
HRESULT CreateLineWKTFromVertices (CScaleHeader &rHdr, double_v &rX, double_v &rY, BSTR *pbstrWKT);
HRESULT CreateAreaWKTFromVertices (CScaleHeader &rHdr, ulong_v &vKnt, double_v &rX, double_v &rY, BSTR *pbstrWKT);

}

#endif // !defined(_GEOMETRYWKT_H__D16D8B7D_B2B4_44F4_9162_C0FEE7E1A33C__INCLUDED_)
