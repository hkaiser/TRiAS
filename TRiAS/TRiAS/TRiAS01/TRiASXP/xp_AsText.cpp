// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 12.08.2001 17:40:20 
//
// @doc
// @module xp_AsText.cpp | Definition of the xp_AsText XP

#include "stdafx.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// convert geometry filed to OG WKT format
#define PRINTERROR(pSrvProc, s) printError(pSrvProc, XP_ASTEXT_ERROR, __LINE__, s)
#define PRINTUSAGE(pSrvProc)	PRINTERROR(pSrvProc, "Usage: EXEC xp_AsText <@geometry>, <@wellknowntext output>")

extern "C" 
RETCODE __declspec(dllexport) xp_AsText(SRV_PROC *pSrvProc)
{
#ifdef _DEBUG
// In a debug build, look up the data type name for assistance.
DBCHAR *pdbcDataType = NULL;
int cbDataType = 0;
#endif

	COM_TRY {
	// Count up the number of input parameters.  There should be exactly two.
		if (2 != srv_rpcparams(pSrvProc)) 
			return PRINTUSAGE (pSrvProc);	// Send error message and return

	// Use srv_paraminfo to get data type and length information.
	BYTE bType1, bType2;
	ULONG cbMaxLen1, cbMaxLen2;
	ULONG cbActualLen1, cbActualLen2;
	BOOL fNull1, fNull2;

	// check 1st parameter
		if (FAIL == srv_paraminfo(pSrvProc, 1, &bType1, &cbMaxLen1, &cbActualLen1, NULL, &fNull1))
			return PRINTERROR(pSrvProc, "srv_paraminfo for parameter 1 failed...");

#ifdef _DEBUG
    // A debugging aid. Get the name of the data type of the parameter.
	    pdbcDataType = srv_symbol(SRV_DATATYPE, (int)bType1, &cbDataType);
#endif

	// make sure first parameter is of image datatype (should be geometry)
		if (bType1 != SRVIMAGE)
			return PRINTUSAGE(pSrvProc);

	// check 2nd parameter
		if (FAIL == srv_paraminfo(pSrvProc, 2, &bType2, &cbMaxLen2, &cbActualLen2, NULL, &fNull2))
			return PRINTERROR(pSrvProc, "srv_paraminfo for parameter 2 failed...");

#ifdef _DEBUG
    // A debugging aid. Get the name of the data type of the parameter.
	    pdbcDataType = srv_symbol(SRV_DATATYPE, (int)bType2, &cbDataType);
#endif

	// make sure second parameter is of ntext datatype
		if (bType2 != SRVNVARCHAR && bType2 != SRVBIGVARCHAR)
			return PRINTUSAGE(pSrvProc);

	// make sure second parameter is a return (OUTPUT) parameter
		if (!(srv_paramstatus(pSrvProc, 2) & SRV_PARAMRETURN))
			return PRINTUSAGE(pSrvProc);

	// retrieve geometry
	std::auto_ptr<BYTE> Geometry (new BYTE[cbActualLen1]);

		if (FAIL == srv_paraminfo(pSrvProc, 1, &bType1, &cbMaxLen1, &cbActualLen1, Geometry.get(), &fNull1))
			return PRINTERROR(pSrvProc, "srv_paraminfo(data) for parameter 1 failed...");
	
	// convert geometry to wkt format
	CComBSTR bstrWKT;
	WUnknown Unk (*(GUID *)Geometry.get());
	WPersistMemoryWks PM (Unk);

		THROW_FAILED_HRESULT(PM -> Load (Geometry.get() + sizeof(GUID), cbActualLen1 - sizeof(GUID)));
		THROW_FAILED_HRESULT(PM -> SaveWkt (&bstrWKT, false));

	// set output parameter
	ULONG ulLen = 0;
	BYTE *pOutData = NULL;

		USES_CONVERSION;
		if (SRVNVARCHAR == bType2) {
			pOutData = (BYTE *)bstrWKT.m_str;
			ulLen = min(cbMaxLen2, ULONG(bstrWKT.Length()*sizeof(OLECHAR)));
		} else {
			pOutData = (BYTE *)OLE2A(bstrWKT);
			ulLen = min(cbMaxLen2, ULONG(bstrWKT.Length()));
		}

		if (FAIL == srv_paramsetoutput(pSrvProc, 2, pOutData, ulLen, FALSE))
			return PRINTERROR(pSrvProc, "srv_paramsetoutput for parameter 2 failed...");

		srv_senddone(pSrvProc, SRV_DONE_MORE, 0, 0);

	} COM_CATCH_RETURN(XP_ERROR);
	return XP_NOERROR;
}

