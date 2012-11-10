// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.02.2002 13:31:33 
//
// @doc
// @module PolyGISDatasource.h | Declaration of the <c CPolyGISDatasource> class

#if !defined(_POLYGISDATASOURCE_H__59C59421_FFCC_4C79_97AD_1A1CEBE7F2D6__INCLUDED_)
#define _POLYGISDATASOURCE_H__59C59421_FFCC_4C79_97AD_1A1CEBE7F2D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// repräsentiert eine geöffnete Datenquelle in PolyGIS
class CPolyGISDatasource
{
public:
	CPolyGISDatasource() :
		m_fWriteable(false)
	{
	}
	~CPolyGISDatasource()
	{
	}

	HRESULT Open (LPCSTR pcPolyGIS, LPCSTR pcName, bool fWriteable);

private:
	bool m_fWriteable;
};

#endif // !defined(_POLYGISDATASOURCE_H__59C59421_FFCC_4C79_97AD_1A1CEBE7F2D6__INCLUDED_)
