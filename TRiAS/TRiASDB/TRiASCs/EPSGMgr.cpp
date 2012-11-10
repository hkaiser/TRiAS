// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 11:08:24 
//
// @doc
// @module EPSGMgr.cpp | Definition of the <c CEPSGManager> class

#include "stdafx.h"
#include "TRiASCs.h"
#include "EPSGMgr.h"
#include "LibCTF/LibCTFImpl.h"

GMRECODETABLE tblOfRecode[] = 
{
	{ tcsCType_Storage		, tcsCS_Projected					, csbsProjected },
	{ tcsCType_Storage		, tcsCS_Geographic					, csbsGeographic },

	{ tcsCType_GD			, tcsGD_WorldGeodeticSystem1972		, csgdWGS72 },
	{ tcsCType_GD			, tcsGD_WorldGeodeticSystem1984		, csgdWGS84 },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetz	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_Pulkovo1942					, csgdPulkovo1942 },
	{ tcsCType_GD			, tcsGD_EuropeanTerrestrialReferenceSystem89			, cseGRS80 },	// #HK010118
	{ tcsCType_GD			, tcsGD_EuropeanDatum1950			, csgdEuropean1950 },	// #HK000125

	{ tcsCType_PA			, tcsPA_TransverseMercator			, cspaTransverseMercator },
	{ tcsCType_PA			, tcsPA_GaussKrueger				, cspaGaussKruger },
	{ tcsCType_PA			, tcsPA_LambertConicConformal2SP	, cspaLambert },		// #HK000125
	{ tcsCType_PA			, tcsPA_CassiniSoldner				, cspaCassini },		// #HK010112

	{ tcsCType_Ellipsoid	, tcsEL_Krassowsky1940				, cseKrassovsky	},		// GM: 4
	{ tcsCType_Ellipsoid	, tcsEL_International1924			, cseInternational	},	// GM: 5		// #HK000125
	{ tcsCType_Ellipsoid	, tcsEL_Clarke1866					, cseClark1866	},		// GM: 8
	{ tcsCType_Ellipsoid	, tcsEL_Bessel1841					, cseBessel1841	},		// GM: 10
	{ tcsCType_Ellipsoid	, tcsEL_WGS84						, cseWGS84		},		// GM: 22
	{ tcsCType_Ellipsoid	, tcsEL_GRS1980						, cseGRS80		},		// GM: 22

// #HK020228	
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzAblN	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzAblM	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzAblS	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzRd83	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzPd83	, csgdPotsdam },

// #HK020419
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzRd83DHDN	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzDHDN	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzAblN2	, csgdPotsdam },
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzAblS2	, csgdPotsdam },

// #HK020426
	{ tcsCType_GD			, tcsGD_DeutscheHauptdreiecksnetzBesD	, csgdPotsdam },

	{ tcsCType_Undefined	, tcsCType_Undefined, tcsCType_Undefined },
};

///////////////////////////////////////////////////////////////////////////////////
// Tabelle der Ellipsoidparameter und geozentrischen Translationsparameter 
// für Ellipsoidübergänge zu WGS84
// http://www.colorado.edu/geography/gcraft/notes/datum/dlist.html
CODEPARAMSET _PT_DATUMSHIFTPARAM[] = 
{
//	  geod. Datum (dX, dY, dZ, rx, ry, rz, ds)
	{ tcsGD_Pulkovo1942,					
		{ +24.9, -126.4, -93.2, -0.308e-6, -1.197e-6, -0.200e-6, 1.013e-6 } },
	{ tcsGD_DeutscheHauptdreiecksnetz,		
		{ +606.069176231606, +22.9985051548215, +413.04801358317, } },
//		{ +582, +105, +414, -0.504e-6, -0.169e-6, 1.493e-6, 8.3e-6 } },	// EPSG
	{ tcsGD_WorldGeodeticSystem1972,		
		{ 0, 0, 5, } },
	{ tcsGD_WorldGeodeticSystem1984,		
		{ 0, } },
	{ tcsGD_EuropeanTerrestrialReferenceSystem89,		
		{ 0, } },
	{ tcsGD_EuropeanDatum1950,				
		{ -87, -96, -120, } },	// #HK000125

// #HK020228
// Dreiteilung des Festpunktnetzes (alte Bundesländer)
	{ tcsGD_DeutscheHauptdreiecksnetzAblN,	// alte Bundesländer Nord (55°-52°20')
		{ 590.5, 69.5, 411.6, -3.860e-6, -0.250e-6, -17.457e-6, 8.299e-6 } },
	{ tcsGD_DeutscheHauptdreiecksnetzAblM,	// alte Bundesländer Mitte (52°20'-50°20')
		{ 584.8, 67.0, 400.3, 0.511e-6, 0.061e-6, -11.526e-6, 10.291e-6 } },
	{ tcsGD_DeutscheHauptdreiecksnetzAblS,	// alte Bundesländer Süd (50°20'-47°)
		{ 597.1, 71.4, 412.1, 4.334e-6, 0.329e-6, -7.577e-6, 7.576e-6 } },

// Zweiteilung des Festpunktnetzes (alte Bundesländer)
	{ tcsGD_DeutscheHauptdreiecksnetzAblN2,	// alte Bundesländer Nord (55°-51°)
		{ 587.1, 68.4, 405.4, -3.262e-6, -0.294e-6, -16.536e-6, 9.413e-6 } },
	{ tcsGD_DeutscheHauptdreiecksnetzAblS2,	// alte Bundesländer Süd (51°-47°)
		{ 591.8, 70.3, 408.3, 3.447e-6, 0.410e-6, -8.514e-6, 8.572e-6 } },

// Alte Bundesländer gesamt 
	{ tcsGD_DeutscheHauptdreiecksnetzDHDN,
		{ 592.0, 72.5, 410.9, 1.308e-6, 0.247e-6, -11.463e-6, 8.205e-6 } },

// Neue Bundesländer
	{ tcsGD_DeutscheHauptdreiecksnetzRd83,	// neue Bundesländer (außer Thüringen)
		{ 612.4, 77.0, 440.2, -0.261e-6, 0.274e-6, -13.559e-6, 2.547e-6 } },
	{ tcsGD_DeutscheHauptdreiecksnetzPd83,	// neue Bundesländer (Thüringen)
		{ 599.4, 72.4, 419.2, -0.304e-6, -0.109e-6, -13.201e-6, 6.463e-6 } },

// #HK020419
	{ tcsGD_DeutscheHauptdreiecksnetzRd83DHDN,	// Deutsche Hauptdreiecksnetz RD83 (neu)
		{ 598.1, 73.7, 418.2, 0.980e-6, 0.220e-6, -11.904e-6, 6.701e-6 } },

// #HK020426
	{ tcsGD_DeutscheHauptdreiecksnetzBesD,	// Deutsche Hauptdreiecksnetz RD83 (neu)
		{ 585.7, 87.0, 409.20000000000005, -0.524e-6, -0.155e-6, 2.822e-6, 8.780e-6 } },

	{ tcsGD_Undefined, {0} },
};

// Tabelle der Winkelmaßeinheiten
CODEPARAMSET _PT_UOACONVPARAM[] = 
{
	{ tcsUOA_Radian,				{ PI,			PI		} },
	{ tcsUOA_Degree,				{ PI,			180		} },
	{ tcsUOA_ArcMinute,				{ PI,			10800	} },
	{ tcsUOA_ArcSecond,				{ PI,			648000	} },
	{ tcsUOA_Second,				{ PI,			648000	} },
	{ tcsUOA_Grad,					{ PI,			200		} },
	{ tcsUOA_Gon,					{ PI,			200		} },
	{ tcsUOA_Microradian,			{ 1,			1000000	} },
	{ tcsUOA_Undefined, {0} },
};

// Tabelle der Längenmaßeinheiten
CODEPARAMSET _PT_UOLCONVPARAM[] = 
{
	{ tcsUOL_Metre,					{ 1,			1			} },
	{ tcsUOL_MilliMetre,			{ 1,			1000		} },
	{ tcsUOL_CentiMetre,			{ 1,			100			} },
	{ tcsUOL_KiloMetre,				{ 1000,			1			} },
	{ tcsUOL_Foot,					{ 0.3048,		1			} },
	{ tcsUOL_USSurveyFoot,			{ 12,			39.37		} },
	{ tcsUOL_ModifiedAmericanFoot,	{ 12.0004584,	39.37		} },
	{ tcsUOL_ClarkeSFoot,			{ 12,			39.370432	} },
	{ tcsUOL_IndianFootClarke,		{ 12,			39.370142	} },
	{ tcsUOL_Link,					{ 7.92,			39.370432	} },
	{ tcsUOL_LinkBenoit,			{ 7.92,			39.370113	} },
	{ tcsUOL_LinkSears,				{ 7.92,			39.370147	} },
	{ tcsUOL_ChainBenoit,			{ 792,			39.370113	} },
	{ tcsUOL_ChainSears,			{ 792,			39.370147	} },
	{ tcsUOL_YardSears,				{ 36,			39.370147	} },
	{ tcsUOL_IndianYard,			{ 36,			39.370141	} },
	{ tcsUOL_Fathom,				{ 1.8288,		1			} },
	{ tcsUOL_NauticalMile,			{ 1852,			1			} },
	{ tcsUOL_GermanLegalMetre,		{ 1.0000135965,	1			} },
	{ tcsUOL_FootSears,				{ 12,			39.370147	} },
	{ tcsUOL_USSurveyChain,			{ 792,			39.37		} },
	{ tcsUOL_USSurveyLink,			{ 7.92,			39.37		} },
	{ tcsUOL_USSurveyMile,			{ 63360,		39.37		} },
	{ tcsUOL_Inch,					{ 2.54,			100			} },
	{ tcsUOL_Undefined, {0} },
};

///////////////////////////////////////////////////////////////////////////////
// 
CEPSGManager::CEPSGManager() 
{
}

CEPSGManager::~CEPSGManager() 
{
}

void CEPSGManager::LoadTable(CODETYPE codeType, LPCCODENAME pT) 
{
	for (/**/; -1 != pT->code && NULL != pT->name; ++pT)
	{
		m_mapOfTRiASCodes[codeType][pT->code] = pT->name;
	}
}

void CEPSGManager::LoadTable(CODETYPE codeType, LPCCODEPARAMSET pT) 
{
	for (/**/; -1 != pT->code; ++pT)
	{
		m_mapOfParameters[codeType][pT->code] = &pT->p;
	}
}

void CEPSGManager::LoadTable(CODETYPE codeType, LPCCODEPARAM pT) 
{
	for (/**/; -1 != pT->code; ++pT)
	{
		m_mapOfCodeParam[codeType][pT->code] = &pT->param;
	}
}

void CEPSGManager::LoadTable(LPCDT_ATTRIBUTESET p) 
{
	for (/**/; tcsDTA_Undefined != p->ta; p++)
	{
		m_mapOfDTAttribs[p->ta][p->tp] = p->value;
	}
}

void CEPSGManager::LoadTable(LPCPA_ATTRIBUTESET p) 
{
	for (/**/; tcsPA_Undefined != p->pa; p++)
	{
		m_mapOfPAAttribs[p->pa][p->pp] = p->value;
	}
}

void CEPSGManager::LoadTables() 
{
	LoadTable(tcsCType_GD, _CT_TRIASCSGEODETICDATUM);
	LoadTable(tcsCType_Ellipsoid, _CT_TRIASCSELLIPSOID);
	LoadTable(tcsCType_PM, _CT_TRIASCSPRIMEMERIDIAN);
	LoadTable(tcsCType_UOA, _CT_TRIASCSUNITOFANGLE);
	LoadTable(tcsCType_UOL, _CT_TRIASCSUNITOFLENGTH);
	LoadTable(tcsCType_PA, _CT_TRIASCSPROJECTIONALGORITHM);
	LoadTable(tcsCType_DT, _PT_DATUMSHIFTPARAM);
	LoadTable(tcsCType_UOA, _PT_UOACONVPARAM);
	LoadTable(tcsCType_UOL, _PT_UOLCONVPARAM);
	LoadTable(tcsCType_Ellipsoid, _PT_ELLIPSPARAM);
	LoadTable(tcsCType_EllipsOfGD, _PT_ELLIPSFROMGD);
	LoadTable(_DT_ATTRIBUTES);
	LoadTable(_PA_ATTRIBUTES);
	for (LPCGMRECODETABLE pTable = tblOfRecode; -1 != pTable->m_codeType; ++pTable)
	{
		m_mapOfTRiAS2GM[pTable->m_codeType][pTable->m_codeTRiAS] = pTable->m_codeGM;
		m_mapOfGM2TRiAS[pTable->m_codeType][pTable->m_codeGM] = pTable->m_codeTRiAS;
	}

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetz, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetz, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetz, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_Pulkovo1942, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_Pulkovo1942, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_Pulkovo1942, tcsPA_CylindricEquirectangular)] = 1;

// #HK000125
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_EuropeanDatum1950, tcsPA_LambertConicConformal2SP)] = 1;

// #HK010112
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetz, tcsPA_CassiniSoldner)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_EuropeanTerrestrialReferenceSystem89, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_EuropeanTerrestrialReferenceSystem89, tcsPA_TransverseMercator)] = 1;

// #HK020228
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblM, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblM, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblM, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblM, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzPd83, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzPd83, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzPd83, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzPd83, tcsPA_CassiniSoldner)] = 1;

// #HK020419
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83DHDN, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83DHDN, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83DHDN, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzRd83DHDN, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzDHDN, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzDHDN, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzDHDN, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzDHDN, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN2, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN2, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN2, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblN2, tcsPA_CassiniSoldner)] = 1;

	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS2, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS2, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS2, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzAblS2, tcsPA_CassiniSoldner)] = 1;

// #HK020426
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzBesD, tcsPA_GaussKrueger)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzBesD, tcsPA_TransverseMercator)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzBesD, tcsPA_CylindricEquirectangular)] = 1;
	m_mapOfKnownCS[CSPROPERTIES(tcsCS_Projected, tcsGD_DeutscheHauptdreiecksnetzBesD, tcsPA_CassiniSoldner)] = 1;
}

void CEPSGManager::UnloadTables() 
{
	m_mapOfKnownCS.erase(m_mapOfKnownCS.begin(), m_mapOfKnownCS.end());

	m_mapOfTRiASCodes.erase(m_mapOfTRiASCodes.begin(), m_mapOfTRiASCodes.end());
	m_mapOfTRiAS2GM.erase(m_mapOfTRiAS2GM.begin(), m_mapOfTRiAS2GM.end());
	m_mapOfGM2TRiAS.erase(m_mapOfGM2TRiAS.begin(), m_mapOfGM2TRiAS.end());
	m_mapOfParameters.erase(m_mapOfParameters.begin(), m_mapOfParameters.end());
	m_mapOfCodeParam.erase(m_mapOfCodeParam.begin(), m_mapOfCodeParam.end());
	m_mapOfDTAttribs.erase(m_mapOfDTAttribs.begin(), m_mapOfDTAttribs.end());
	m_mapOfPAAttribs.erase(m_mapOfPAAttribs.begin(), m_mapOfPAAttribs.end());
}

bool CEPSGManager::IsCSKnown(const CSPROPERTIES& prop) 
{
	return (m_mapOfKnownCS.find(prop) == m_mapOfKnownCS.end()) ? false : true;
}

LPCPARAMETERSET	CEPSGManager::GetParameters(CODETYPE codeType, long code) 
{
	return m_mapOfParameters[codeType][code];
}

long CEPSGManager::GetParameter(CODETYPE codeType, long code) 
{
const long *p = m_mapOfCodeParam[codeType][code];

	return (NULL == p) ? -1 : *p;
}

LPCTSTR CEPSGManager::Decode(CODETYPE codeType, long code) 
{
	return m_mapOfTRiASCodes[codeType][code];
}

long CEPSGManager::RecodeFromGM(CODETYPE codeType, long code) 
{
	return m_mapOfGM2TRiAS[codeType][code];
}

long CEPSGManager::RecodeFromTRiAS(CODETYPE codeType, long code) 
{
	return m_mapOfTRiAS2GM[codeType][code];
}

LPCTSTR	CEPSGManager::GetAttrib(TRIASCSPROJECTIONALGORITHM pa, TRIASCSPROJECTIONPARAMETER pp) 
{
	return m_mapOfPAAttribs[pa][pp];
}

LPCTSTR	CEPSGManager::GetAttrib(TRIASCSDTRANSALGORITHM ta, TRIASCSDTRANSPARAMETER tp) 
{
	return m_mapOfDTAttribs[ta][tp];
}

int CEPSGManager::GetAttribs(TRIASCSPROJECTIONALGORITHM pa, PA_AttribsVector& v) 
{
	v.clear();
	for (map<TRIASCSPROJECTIONPARAMETER, LPCTSTR>::iterator i = m_mapOfPAAttribs[pa].begin(); 
		 i != m_mapOfPAAttribs[pa].end(); i++)
	{
		v.push_back((*i).first);
	}
	return v.size();
}

int CEPSGManager::GetAttribs(TRIASCSDTRANSALGORITHM ta, DT_AttribsVector& v) 
{
	v.clear();
	for (map<TRIASCSDTRANSPARAMETER, LPCTSTR>::iterator i = m_mapOfDTAttribs[ta].begin(); 
		 i != m_mapOfDTAttribs[ta].end(); i++)
	{
		v.push_back((*i).first);
	}
	return v.size();
}
