// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.08.2001 21:07:00 
//
// @doc
// @module GeometryWKT.cpp | Definition of the <c CGeometryWKT> class

#include "trias01p.hxx"

#include <NativeObject.h>
#include <GeometryWKT.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

namespace trias_geometrywkt {

///////////////////////////////////////////////////////////////////////////////
// Helperklasse
HRESULT CMakeWKT::AppendPoint (CComBSTR &rbstr, double dX, double dY, bool fAppendComma)
{
CComVariant vX (0.0);
CComVariant vY (0.0);

	m_rHdr.UnScale (dX, dY, &V_R8(&vX), &V_R8(&vY));
	
	RETURN_FAILED_HRESULT(vX.ChangeType(VT_BSTR));
	RETURN_FAILED_HRESULT(vY.ChangeType(VT_BSTR));

	rbstr.AppendBSTR(V_BSTR(&vX));
	rbstr.Append(L" ");
	rbstr.AppendBSTR(V_BSTR(&vY));
	if (fAppendComma)
		rbstr.Append(L", ");
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Punkt
HRESULT CreatePointWKTFromVertices (CScaleHeader &rHdr, double_v &rX, double_v &rY, BSTR *pbstrWKT)
{
	if (NULL == pbstrWKT)
		return E_POINTER;
	*pbstrWKT = NULL;

// Zeichenkette für Punkt zusammenbauen
CMakeWKT MakeWKT (rHdr);
CComBSTR bstrWKT (L"POINT(");

	RETURN_FAILED_HRESULT(MakeWKT.AppendPoint (bstrWKT, *rX.begin(), *rY.begin(), false));

	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT.Detach();
	return (NULL != *pbstrWKT) ? S_OK : E_OUTOFMEMORY;
}

///////////////////////////////////////////////////////////////////////////////
// Linie
HRESULT CreateLineWKTFromVertices (CScaleHeader &rHdr, double_v &rX, double_v &rY, BSTR *pbstrWKT)
{
	if (NULL == pbstrWKT)
		return E_POINTER;
	*pbstrWKT = NULL;

// Zeichenkette für Linie zusammenbauen
CMakeWKT MakeWKT (rHdr);
CComBSTR bstrWKT (L"LINESTRING(");
double_i itx = rX.begin();
double_i ity = rY.begin();
double_v::size_type vCnt = rX.size();

	_ASSERTE(rX.size() == rY.size());
	for (double_v::size_type i = 0; i < vCnt; i++) 
	{
		MakeWKT.AppendPoint (bstrWKT, *itx, *ity, i != vCnt-1);
		++itx; ++ity;
	}

	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT.Detach();
	return (NULL != *pbstrWKT) ? S_OK : E_OUTOFMEMORY;
}

///////////////////////////////////////////////////////////////////////////////
// Fläche
HRESULT CreateAreaWKTFromVertices (
	CScaleHeader &rHdr, ulong_v &vKnt, double_v &rX, double_v &rY, BSTR *pbstrWKT)
{
	if (NULL == pbstrWKT)
		return E_POINTER;
	*pbstrWKT = NULL;

// Zeichenkette für Linie zusammenbauen
CMakeWKT MakeWKT (rHdr);
CComBSTR bstrWKT (L"POLYGON(");
double_i itx = rX.begin();
double_i ity = rY.begin();

	for (ulong_v::size_type iKnt = 0; iKnt < vKnt.size(); ++iKnt) {
		bstrWKT.Append(L"(");

	double_v::size_type vCnt = vKnt[iKnt];

		for (double_v::size_type i = 0; i < vCnt; i++) 
		{
			MakeWKT.AppendPoint (bstrWKT, *itx, *ity, i != vCnt);
			++itx; ++ity;
		}
		bstrWKT.Append(L")");

		if (iKnt != vKnt.size())
			bstrWKT.Append(L", ");
	}

	bstrWKT.Append(L")");
	*pbstrWKT = bstrWKT.Detach();
	return (NULL != *pbstrWKT) ? S_OK : E_OUTOFMEMORY;
}

}
