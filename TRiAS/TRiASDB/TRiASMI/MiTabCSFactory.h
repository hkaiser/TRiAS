// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 09:27:11 
//
// @doc
// @module MiTabCSFactory.h | Declaration of the <c CMiTabCSFactory> class

#if !defined(_MITABCSFACTORY_H__BCA90B48_F493_4E09_A02B_0B8E28ECB4E5__INCLUDED_)
#define _MITABCSFACTORY_H__BCA90B48_F493_4E09_A02B_0B8E28ECB4E5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ogr/ogr_spatialref.h>
#include "MiTabDatasource.h"

///////////////////////////////////////////////////////////////////////////////
// Bereitstellen des MapInfo Srs als TRiASCS
class CMiTabCSFactory
{
public:
	CMiTabCSFactory(CMiTabLayer *pLayer) :
		m_pLayer(pLayer)
	{
	}
	~CMiTabCSFactory()
	{
	}

	HRESULT RetrieveCS (ITRiASCS **ppICS);

protected:
	HRESULT InitGCS (OGRSpatialReference *pOgrSrs, ITRiASCS *pIGCS);
	HRESULT InitPCS (OGRSpatialReference *pOgrSrs, LPCSTR pcProj, ITRiASCS *pICS);

	HRESULT GetGeodDatum (OGRSpatialReference *pOgrSrs, TRIASCSGEODETICDATUM *prgDatum);
	HRESULT GetTranslations (OGRSpatialReference *pOgrSrs, double *pdX, double *pdY, double *pdZ);
	HRESULT GetUnitOfLength (OGRSpatialReference *pOgrSrs, TRIASCSUNITOFLENGTH *prgUOL);
	HRESULT GetPrimeMeridian (OGRSpatialReference *pOgrSrs, TRIASCSPRIMEMERIDIAN *prgPrimeMeridian);

private:
	CMiTabLayer *m_pLayer;
};

#endif // !defined(_MITABCSFACTORY_H__BCA90B48_F493_4E09_A02B_0B8E28ECB4E5__INCLUDED_)
