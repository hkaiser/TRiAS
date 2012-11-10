// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 11:02:03 
//
// @doc
// @module EPSGMgr.h | Declaration of the <c CEPSGManager> class

#if !defined(_EPSGMGR_H__D7C5A202_55FE_4243_9FEF_1EE34030AC45__INCLUDED_)
#define _EPSGMGR_H__D7C5A202_55FE_4243_9FEF_1EE34030AC45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

typedef struct CODE {
	CODETYPE	m_codeType;
	long		m_codeValue;
	CODE (CODETYPE t, long v) : m_codeType(t), m_codeValue(v) {}
} CODE;

inline bool operator < (const CODE& rc1, const CODE& rc2) 
{
	return rc1.m_codeType < rc2.m_codeType && rc1.m_codeValue < rc2.m_codeValue;
}

typedef	struct tagGMRECODETABLE {
	CODETYPE	m_codeType;
	long		m_codeTRiAS;
	long		m_codeGM;
} GMRECODETABLE;
typedef const GMRECODETABLE const *LPCGMRECODETABLE;

typedef struct CSPROPERTIES_V1 
{
	ULONG						m_Version;
	ULONG						m_PPSize;
	TRIASCSTYPE					m_CS;
	TRIASCSGEODETICDATUM		m_GD;
	TRIASCSELLIPSOID			m_EL;
//	double						m_elHA;
//	double						m_elHB;
//	TRIASCSUNITOFLENGTH			m_elUOL;
	TRIASCSPRIMEMERIDIAN		m_PM;
//	double						m_pmOff;
	TRIASCSPROJECTIONALGORITHM	m_PA;
//	double						m_PP[tcsPP_SizeOfParameterSet];
	TRIASCSDTRANSALGORITHM		m_DT;
//	double						m_TP[tcsPP_SizeOfParameterSet];

	CSPROPERTIES_V1 (
			TRIASCSTYPE cs = tcsCS_Undefined, 
			TRIASCSGEODETICDATUM gd = tcsGD_Undefined,
			TRIASCSPROJECTIONALGORITHM pa = tcsPA_Undefined) :
		m_Version(0x01000000),
//		m_PPSize(tcsPP_SizeOfParameterSet),
		m_CS(cs),
		m_GD(gd),
		m_PA(pa),
		m_EL(tcsEL_Undefined),
//		m_elHA(0), m_elHB(0), m_elUOL( tcsUOL_Undefined ),
		m_PM(tcsPM_Undefined),
//		m_pmOff(0),
		m_DT(tcsDTA_Undefined)
	{
	/*	memset(m_PP, 0, sizeof(m_PP));
		memset(m_TP, 0, sizeof(m_TP)); */ 
	}
} CSPROPERTIES_V1;
typedef CSPROPERTIES_V1 CSPROPERTIES;

inline bool operator< (const CSPROPERTIES& rc1, const CSPROPERTIES& rc2) 
{
	return memcmp(&rc1, &rc2, sizeof(CSPROPERTIES)) < 0;
}
inline bool operator== (const CSPROPERTIES& rc1, const CSPROPERTIES& rc2) 
{
	return memcmp(&rc1, &rc2, sizeof(CSPROPERTIES)) == 0;
}

//inline bool operator!=(const CSPROPERTIES& rc1, const CSPROPERTIES& rc2) 
//{
//	return !(rc1 == rc2);
//}

typedef map<CODETYPE, map<long, const long *> > CodeParamMap;
typedef map<CODETYPE, map<long, LPCTSTR> > CodeMap;
typedef map<CODETYPE, map<long, LPCPARAMETERSET> > ParamMap;
typedef map<CODETYPE, map<long, long> > RecodeMap;
typedef map<CSPROPERTIES, long> KnownCSMap;
typedef map<TRIASCSDTRANSALGORITHM, map<TRIASCSDTRANSPARAMETER, LPCTSTR> > DT_AttribMap;
typedef vector<TRIASCSDTRANSPARAMETER> DT_AttribsVector;
typedef map<TRIASCSPROJECTIONALGORITHM, map<TRIASCSPROJECTIONPARAMETER, LPCTSTR> > PA_AttribMap;
typedef vector<TRIASCSPROJECTIONPARAMETER> PA_AttribsVector;

#define GM_RECODER(fromType, toType) \
	toType RecodeFromGM(CODETYPE codeType, fromType code) \
	{ return (toType)RecodeFromGM(codeType, (long)code); }

class CEPSGManager 
{
private:
	CodeMap	m_mapOfTRiASCodes;
	RecodeMap m_mapOfTRiAS2GM;
	RecodeMap m_mapOfGM2TRiAS;
	ParamMap m_mapOfParameters;
	DT_AttribMap m_mapOfDTAttribs;
	PA_AttribMap m_mapOfPAAttribs;
	CodeParamMap m_mapOfCodeParam;
	KnownCSMap m_mapOfKnownCS;

	void LoadTable(LPCDT_ATTRIBUTESET pDTAttributes);
	void LoadTable(LPCPA_ATTRIBUTESET pPAAttributes);
	void LoadTable(CODETYPE codeType, LPCCODEPARAM pRawTable);
	void LoadTable(CODETYPE codeType, LPCCODENAME pRawTable);
	void LoadTable(CODETYPE codeType, LPCCODEPARAMSET pRawTable);
	long RecodeFromGM(CODETYPE codeType, long code);
	long RecodeFromTRiAS(CODETYPE codeType, long code);

public:
	CEPSGManager();
	virtual ~CEPSGManager();

	void LoadTables();
	void UnloadTables();
	bool IsCSKnown(const CSPROPERTIES& prop);
	LPCTSTR	Decode(CODETYPE codeType, long code);
	LPCTSTR	GetAttrib(TRIASCSPROJECTIONALGORITHM pa, TRIASCSPROJECTIONPARAMETER pp);
	LPCTSTR	GetAttrib(TRIASCSDTRANSALGORITHM ta, TRIASCSDTRANSPARAMETER tp);
	int GetAttribs(TRIASCSPROJECTIONALGORITHM pa, PA_AttribsVector& v);
	int GetAttribs(TRIASCSDTRANSALGORITHM ta, DT_AttribsVector& v);
	LPCPARAMETERSET	GetParameters(CODETYPE codeType, long code);
	long GetParameter(CODETYPE codeType, long code);
	GM_RECODER(CSBaseStorageConstants, TRIASCSTYPE);
	GM_RECODER(CSProjectionAlgorithmConstants, TRIASCSPROJECTIONALGORITHM);
	GM_RECODER(CSGeodeticDatumConstants, TRIASCSGEODETICDATUM);
};

extern CEPSGManager _EM;

#endif // !defined(_EPSGMGR_H__D7C5A202_55FE_4243_9FEF_1EE34030AC45__INCLUDED_)
