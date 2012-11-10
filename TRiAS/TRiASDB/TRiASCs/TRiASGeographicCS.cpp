// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.07.2000 14:09:19
//
// @doc
// @module TRiASGeographicCS.cpp | Implementation of the <c CTRiASGeographicCS> class

#include "stdafx.h"

#include <math.h>

#include "Strings.h"
#include "LibCTF/DtoACTF.h"

#include "TRiASCsImpl.h"
#include "TRiASGeographicCS.h"

#include "EPSGMgr.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

HRESULT CTRiASGeographicCS::FinalConstruct() 
{
	return InternalInitialize();
}

void CTRiASGeographicCS::FinalRelease() 
{
}

HRESULT	CTRiASGeographicCS::PutEllipsoid(TRIASCSELLIPSOID newVal) 
{
	ERROR_EXPR_FALSE(_EM.Decode(tcsCType_Ellipsoid, newVal), GCS_E_INVALIDELLIPSOID);
	if (tcsEL_UserDefined != newVal) {
	LPCPARAMETERSET	p = _EM.GetParameters(tcsCType_Ellipsoid, newVal);

		ERROR_EXPR_TRUE(NULL == p, GCS_E_INVALIDELLIPSOID);
		m_HA = p->p[0];
		m_f = p->p[2];
		m_HB = m_HA *(1 - m_f); 
	}
	m_EL = newVal;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASGeographicCS

STDMETHODIMP CTRiASGeographicCS::get_UnitOfAngle(TRIASCSUNITOFANGLE* pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_UOA;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_UnitOfAngle(TRIASCSUNITOFANGLE newVal) 
{
	ERROR_EXPR_TRUE(!_EM.Decode(tcsCType_UOA, newVal), GCS_E_INVALIDUNITOFANGLE);
	ERROR_EXPR_TRUE(!_EM.GetParameters(tcsCType_UOA, newVal), GCS_E_INVALIDUNITOFANGLE);
	m_UOA = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_GeodeticDatum(TRIASCSGEODETICDATUM * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_GD;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_GeodeticDatum(TRIASCSGEODETICDATUM newVal) 
{
	ERROR_EXPR_TRUE(!_EM.Decode(tcsCType_GD, newVal), GCS_E_INVALIDGEODETICDATUM);
	m_GD = newVal;
	if (tcsGD_UserDefined != newVal)
	{
		return PutEllipsoid((TRIASCSELLIPSOID) _EM.GetParameter(tcsCType_EllipsOfGD, newVal));
	}
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_PrimeMeridian(TRIASCSPRIMEMERIDIAN* pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_PM;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_PrimeMeridian(TRIASCSPRIMEMERIDIAN newVal) 
{
	ERROR_EXPR_TRUE(!_EM.Decode(tcsCType_PM, newVal), GCS_E_INVALIDPRIMEMERIDIAN);
	m_PM = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_SemiMajorAxis(double * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_HA;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_SemiMajorAxis(double newVal) 
{
	ERROR_EXPR_TRUE(tcsEL_UserDefined != m_EL, TCS_E_CANNOTWRITEDATA);
	m_HA = newVal;
	m_HB = m_HA *(1 - m_f); 
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_SemiMinorAxis(double * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_HB;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_Flattening(double * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_f;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_Flattening(double newVal) 
{
	ERROR_EXPR_TRUE(tcsEL_UserDefined != m_EL, TCS_E_CANNOTWRITEDATA);
	m_f = newVal;
	m_HB = m_HA * (1 - m_f); 
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::get_Ellipsoid(TRIASCSELLIPSOID * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_EL;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_Ellipsoid(TRIASCSELLIPSOID newVal) 
{
	ERROR_EXPR_TRUE(tcsGD_UserDefined != m_GD, TCS_E_CANNOTWRITEDATA);
	return PutEllipsoid(newVal);
}

STDMETHODIMP CTRiASGeographicCS::CanTransform(LONG typeOfTransformation) 
{
	if (tcsGD_UserDefined == typeOfTransformation ||
		NULL != _EM.GetParameters(tcsCType_DT, typeOfTransformation))
	{
		return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSValidate

STDMETHODIMP CTRiASGeographicCS::IsValid() 
{
	ERROR_EXPR_TRUE(tcsGD_Undefined == m_GD, GCS_E_INVALIDGEODETICDATUM);
	ERROR_EXPR_TRUE(tcsPM_Undefined == m_PM, GCS_E_INVALIDPRIMEMERIDIAN);
	ERROR_EXPR_TRUE(tcsUOA_Undefined == m_UOA, GCS_E_INVALIDUNITOFANGLE);
	if (tcsGD_UserDefined == m_GD)
	{
		ERROR_EXPR_TRUE(tcsEL_Undefined == m_EL, GCS_E_INVALIDELLIPSOID);
	}
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::RecomputeTransformation(/*[in, defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS) 
{
	ERROR_EXPR_FALSE(this == pGCS, E_FAIL);
		// muß ich selber sein ;-)
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInit

HRESULT CTRiASGeographicCS::LoadData(IStream * pStream, DWORD dwVersion) 
{
	CHECKINPOINTER(pStream);
	COM_TRY {
		if ((dwVersion & ~GCS_VERSION_MINOR_MASK) > LASTKNOWN_GCS_VERSION)
			return E_UNEXPECTED;

		LoadItem(pStream, m_UOA);
		LoadItem(pStream, m_GD);
		LoadItem(pStream, m_EL);
		LoadItem(pStream, m_PM);
		LoadItem(pStream, m_HA);
		LoadItem(pStream, m_f);
		LoadItem(pStream, m_HB);
		
		if (dwVersion >= GCS_VERSION_101)
			LoadItem (pStream, m_lPrec);
		else
			m_lPrec = 2;
			
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASGeographicCS::SaveData(IStream *pStream, BOOL bClearDirty) 
{
	CHECKINPOINTER(pStream);
	COM_TRY {
		SaveItem(pStream, m_UOA);
		SaveItem(pStream, m_GD);
		SaveItem(pStream, m_EL);
		SaveItem(pStream, m_PM);
		SaveItem(pStream, m_HA);
		SaveItem(pStream, m_f);
		SaveItem(pStream, m_HB);

		SaveItem(pStream, m_lPrec);		// ab V1.01
	} COM_CATCH;
	return S_OK;
}

DWORD CTRiASGeographicCS::GetDataSize() 
{
	return sizeof(m_UOA) + sizeof(m_GD)	+ sizeof(m_PM) + sizeof(m_EL) + sizeof(m_HA) + 
		   sizeof(m_f) + sizeof(m_HB) + sizeof(m_lPrec);
}

HRESULT CTRiASGeographicCS::OnInitNew() 
{
	return InternalInitialize();
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSUIHelper

STDMETHODIMP CTRiASGeographicCS::get_Precision(long *plPrec)
{
	if (NULL == plPrec)
		return E_POINTER;
	*plPrec = m_lPrec;
	return S_OK;
}

STDMETHODIMP CTRiASGeographicCS::put_Precision(long lPrec)
{
	m_lPrec = lPrec;
	return S_OK;
}

// Implementation of get_InputMask
STDMETHODIMP CTRiASGeographicCS::get_InputMask(COORDELEMENT Element, BSTR *pbstrUIMask)
{
	ATLTRACE(_T("CTRiASGeographicCS::get_InputMask\n"));
	CHECKOUTPOINTER(pbstrUIMask);

CComBSTR bstrMask (L"##°##'##");

	if (m_lPrec > 0) {
		bstrMask += L".";
		for (long i = 0; i < m_lPrec; ++i)
			bstrMask += L"#";
	}
	bstrMask += "\"??";
	*pbstrUIMask = bstrMask.Detach();
	return S_OK;
}

// Implementation of Format
STDMETHODIMP CTRiASGeographicCS::Format(COORDELEMENT rgElement, double dValue, BSTR *pbstrFormattedElement)
{
	ATLTRACE(_T("CTRiASGeographicCS::Format\n"));
	CHECKOUTPOINTER(pbstrFormattedElement);

char cbFormat[20];
char cbBuffer[256];
char cbSek[32];
bool fSign = false;
long lGrad = 0;
long lMin = 0;
double dSek = 0.0;

	if (0 == m_lPrec)
		strcpy (cbFormat, "%02ld");
	else
		wsprintf (cbFormat, "%%02ld.%%0%dlu", m_lPrec);

	switch (rgElement) {
	case COORDELEMENT_X:
		fSign = dValue < 0;
		dValue = fabs(dValue);

		lGrad = (long)(dValue/3600.0);
		lMin = (long)(dValue/60.0 - (double)lGrad * 60.0);
		dSek = dValue - (double)lGrad * 3600.0 - (double)lMin * 60.0;

		if (dSek >= 60.0) { dSek -= 60.0; lMin++; }
		if (lMin >= 60) { lMin -= 60; lGrad++; }

		DtoACTF (cbSek, cbFormat, 0, dSek);
		wsprintf (cbBuffer, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, fSign ? g_cbWL : g_cbOL);
		break;

	case COORDELEMENT_Y:
		fSign = dValue < 0;
		dValue = fabs(dValue);

		lGrad = (long)(dValue/3600.0);
		lMin = (long)(dValue/60.0 - (double)lGrad * 60.0);
		dSek = dValue - (double)lGrad * 3600.0 - (double)lMin * 60.0;

		if (dSek >= 60.0) { dSek -= 60.0; lMin++; }
		if (lMin >= 60) { lMin -= 60; lGrad++; }

		DtoACTF (cbSek, cbFormat, 0, dSek);
		wsprintf (cbBuffer, "%d°%02d'%s\"%s", lGrad, lMin, cbSek, fSign ? g_cbSB : g_cbNB);
		break;

	case COORDELEMENT_Z:
		DtoACTF (cbBuffer, cbFormat, m_lPrec, dValue);
		break;

	default:
		return E_INVALIDARG;
	}

// Resultat liefern
CComBSTR bstr (cbBuffer);

	*pbstrFormattedElement = bstr.Detach();
	return S_OK;
}

// Implementation of Convert
namespace {
	bool SkipWhites (char *& pS) 
	{
		while (*pS) {
			if (isascii(*pS) && (isdigit(*pS) || '-' == *pS)) 
				break;
			pS++;
		}
		return *pS != '\0';
	}

	bool AtoI (char *& pS, int *iR)
	{
		*iR = 0;
		while (*pS && isascii(*pS) && isdigit(*pS))
			*iR = (*iR * 10) + *pS++ - '0';
		return *pS != '\0';
	}
}

STDMETHODIMP CTRiASGeographicCS::Convert(COORDELEMENT rgElement, BSTR bstrFormatted, double *pdValue)
{
	ATLTRACE(_T("CTRiASGeographicCS::Convert\n"));
	CHECKOUTPOINTER(pdValue);
	USES_CONVERSION;
	
char *cptr = OLE2A(bstrFormatted);
int lGrad = 0;
int lMin = 0;
bool fSign = false;

	SkipWhites (cptr);
	if ('-' == *cptr) {
		fSign = true;
		++cptr;
	}

	if (!AtoI (cptr, &lGrad) || !SkipWhites (cptr)) {
		*pdValue = lGrad * 3600.0;
		if (fSign)
			*pdValue = -(*pdValue);
		return S_OK;
	}
	if (!AtoI (cptr, &lMin) || !SkipWhites (cptr)) {
		*pdValue = lGrad * 3600.0 + lMin * 60.0;
		if (fSign)
			*pdValue = -(*pdValue);
		return S_OK;
	}

double dSek = atof (cptr);

	*pdValue = lGrad * 3600.0 + lMin * 60.0 + dSek;

// Vorzeichen etc. feststellen
	switch (rgElement) {
	case COORDELEMENT_X:
		if (NULL != strstr (cptr, g_cbWL))
			fSign = true;
		break;

	case COORDELEMENT_Y:
		if (NULL != strstr (cptr, g_cbSB))
			fSign = true;
		break;

	case COORDELEMENT_Z:
		break;

	default:
		return E_INVALIDARG;
	}

	if (fSign)
		*pdValue = -(*pdValue);
	return S_OK;
}

