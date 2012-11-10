// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:08:35 
//
// @doc
// @module LibCTF.h | Declaration of the <c CTransform> class

#if !defined(__LIBCTF_H__F74904B0_F703_11d1_8F51_0060085FC1CE)
#define __LIBCTF_H__F74904B0_F703_11d1_8F51_0060085FC1CE

#include <math.h>
#ifndef _ATL_NO_DEBUG_CRT
#include <crtdbg.h>
#endif

#include "DtoACTF.h"
#include "../EllipsParams.h"

///////////////////////////////////////////////////////////////////////////////
// ein Koordinatenpunkt
typedef struct TCSDBLCOORD {
	double	c1;
	double	c2;
	double	h;
} TCSDBLCOORD;

typedef TCSDBLCOORD* LPTCSDBLCOORD;

///////////////////////////////////////////////////////////////////////////////
// Parameter des Ellipsoides
#define	HB(ha,f)	(1-(f))*(ha)				// hb=(1-f)*ha
#define	F(ha,hb)	((ha)-(hb))/(ha)			// f=(ha-hb)/ha
#define	E2(f)		((f)*(2-(f)))				// e²=2*f-f²
#define	E12(f)		1-E2(f)						// 1 - e²
#define	E22(ha,hb)	(((ha)/(hb))*((ha)/(hb))-1)	// e'²=(ha²-hb²)/hb²

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für alle Projektions-Algorithmen
class CTransform 
{
// das, was jeder Transformator so braucht
protected:
	CEllipsoidParams m_MeSelf;
	double m_scaleXIn;
	double m_scaleYIn;
	double m_scaleXOut;
	double m_scaleYOut;
	long m_lPrec;

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReference
	CComBSTR m_bstrName;
	CComBSTR m_bstrAlias;
	CComBSTR m_bstrRemarks;
	CComBSTR m_bstrAuth;
	CComBSTR m_bstrAbbreviation;
	long m_lCode;
#endif // defined(_USE_OGC_COMPATIBILITY)

	virtual HRESULT	SetModelParameters () { return S_OK; }
	virtual HRESULT SetModelParameters2 (double HA2, double f2)  { return S_OK; }

public:
	CTransform() :
		m_scaleXIn(1), m_scaleYIn(1), m_scaleXOut(1), m_scaleYOut(1), 
#if defined(_USE_OGC_COMPATIBILITY)
		m_lCode(0),
#endif // defined(_USE_OGC_COMPATIBILITY)
		m_lPrec(0)
	{
	}
	virtual ~CTransform() {}
	
	virtual HRESULT SetModel (double HA, double f, double HA2 = 0, double f2 = 0);
	virtual HRESULT SetScale (double scaleXIn, double scaleYIn, double scaleXOut = 1, double scaleYOut = 1);
	virtual	HRESULT SetParameters (long nParams, double *pParam) = 0;
	virtual	HRESULT GetDefaults (long nParams, double *pParam) = 0;
	virtual HRESULT Transform (long nCoords, LPTCSDBLCOORD pData) = 0;
	virtual HRESULT TransformInverse (long nCoords, LPTCSDBLCOORD pData) = 0;
	virtual HRESULT IsValid();

// UIHelper
	virtual HRESULT get_Precision (long *plPrec);
	virtual HRESULT put_Precision (long lPrec);
	virtual HRESULT get_InputMask (COORDELEMENT rgElement, BSTR *pbstrMask);
	virtual HRESULT Format (COORDELEMENT rgElement, double dValue, BSTR *pbstrFormattedElement);
	virtual HRESULT Convert (COORDELEMENT rgElement, BSTR bstrFormatted, double *pdValue);

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReference
	virtual HRESULT get_Name(BSTR *pbstrName);
	virtual HRESULT put_Name(BSTR bstrName);
	virtual HRESULT get_Authority(BSTR *pbstrAuth);
	virtual HRESULT put_Authority(BSTR bstrAuth);
	virtual HRESULT get_Code(long *plCode);
	virtual HRESULT put_Code(long lCode);
	virtual HRESULT get_Alias(BSTR *pbstrAlias);
	virtual HRESULT put_Alias(BSTR bstrAlias);
	virtual HRESULT get_Abbreviation(BSTR *pbstrAbbrev);
	virtual HRESULT put_Abbreviation(BSTR bstrAbbrev);
	virtual HRESULT get_Remarks(BSTR *pbstrRemarks);
	virtual HRESULT put_Remarks(BSTR bstrRemarks);
	virtual HRESULT get_WellKnownText(BSTR *pbstrWkt);
#endif // defined(_USE_OGC_COMPATIBILITY)
};

// diverse Konstanten
const double tcsPI = 3.1415926535897932384626433;
const double tcsHalfPI = tcsPI * 0.5;
const double tcsTwoPI = tcsPI * 2.0;

inline HRESULT CTransform::SetModel (double ha, double f, double ha2 /*= 0*/, double f2 /*= 0*/)  
{
	if (0 == ha) 
		return RCS_E_HA_NULL;
	if (0 == f)
		return RCS_E_F_NULL;

	m_MeSelf.SetParams(ha, f);

	if (!SUCCEEDED (SetModelParameters())) 
		return RCS_E_MODELPARAMETERS;
	if (0 != ha2 && 0 != f2) 
		return SetModelParameters2 (ha2, f2);

	return S_OK;
}

inline HRESULT CTransform::SetScale (
	double scaleXOut, double scaleYOut, double scaleXIn /*= 1*/, double scaleYIn /*= 1*/) 
{
	if (0 == scaleXOut || 0 == scaleYOut || 0 == scaleXIn || 0 == scaleYIn) 
		return RCS_E_SCALE_NULL;

	m_scaleXOut = scaleXOut;
	m_scaleYOut = scaleYOut;
	m_scaleXIn = scaleXIn;
	m_scaleYIn = scaleYIn;
	return S_OK;
}

inline HRESULT CTransform::IsValid() 
{
	return S_OK;
}

// UIHelper
inline HRESULT CTransform::get_Precision(long *plPrec)
{
	if (NULL == plPrec)
		return E_POINTER;
	*plPrec = m_lPrec;
	return S_OK;
}

inline HRESULT CTransform::put_Precision(long lPrec)
{
	m_lPrec = lPrec;
	return S_OK;
}

// Implementation of get_InputMask
inline HRESULT CTransform::get_InputMask(COORDELEMENT rgElement, BSTR *pbstrMask)
{
CComBSTR bstrMask (L"999999#");

	if (m_lPrec > 0) {
		bstrMask.Append(L".");
		for (long i = 0; i < m_lPrec; ++i)
			bstrMask.Append(L"#");
	}
	*pbstrMask = bstrMask.Detach();
	return S_OK;
}

// Implementation of Format
inline HRESULT CTransform::Format (COORDELEMENT rgElement, double dValue, BSTR *pbstrFormattedElement)
{
	if (NULL == pbstrFormattedElement)
		return E_POINTER;

char cbFormat[20];
char cbBuffer[_MAX_PATH];

	if (0 == m_lPrec)
		strcpy (cbFormat, "%ld");
	else
		wsprintf (cbFormat, "%%ld.%%0%dlu", m_lPrec);

CComBSTR bstrT (DtoACTF (cbBuffer, cbFormat, m_lPrec, dValue));

	*pbstrFormattedElement = bstrT.Detach();
	return S_OK;
}

// Implementation of Convert
inline HRESULT CTransform::Convert(COORDELEMENT rgElement, BSTR bstrFormatted, double *pdValue)
{
	if (NULL == pdValue)
		return E_POINTER;
		
	USES_CONVERSION;
	*pdValue = atof (OLE2A(bstrFormatted));
	return S_OK;
}

#if defined(_USE_OGC_COMPATIBILITY)
///////////////////////////////////////////////////////////////////////////////
// ISpatialReference
// Implementation of get_Name
inline HRESULT CTransform::get_Name(BSTR *pbstrName)
{
	_ASSERTE(NULL != pbstrName);
	*pbstrName = CComBSTR(m_bstrName).Detach();
	return (NULL != *pbstrName) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of put_Name
inline HRESULT CTransform::put_Name(BSTR bstrName)
{
	m_bstrName = bstrName;
	return (NULL != m_bstrName.m_str) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of get_Authority
inline HRESULT CTransform::get_Authority(BSTR *pbstrAuth)
{
	_ASSERTE(NULL != pbstrAuth);
	*pbstrAuth = CComBSTR(m_bstrAuth).Detach();
	return (NULL != *pbstrAuth) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of put_Authority
inline HRESULT CTransform::put_Authority(BSTR bstrAuth)
{
	m_bstrAuth = bstrAuth;
	return (NULL != m_bstrAuth.m_str) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of get_Code
inline HRESULT CTransform::get_Code(long *plCode)
{
	_ASSERTE(NULL != plCode);
	*plCode = m_lCode;
	return S_OK;
}

// Implementation of put_Code
inline HRESULT CTransform::put_Code(long lCode)
{
	m_lCode = lCode;
	return S_OK;
}

// Implementation of get_Alias
inline HRESULT CTransform::get_Alias(BSTR *pbstrAlias)
{
	_ASSERTE(NULL != pbstrAlias);
	*pbstrAlias = CComBSTR(m_bstrAlias).Detach();
	return (NULL != *pbstrAlias) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of put_Alias
inline HRESULT CTransform::put_Alias(BSTR bstrAlias)
{
	m_bstrAlias = bstrAlias;
	return (NULL != m_bstrAlias.m_str) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of get_Remarks
inline HRESULT CTransform::get_Remarks(BSTR *pbstrRemarks)
{
	_ASSERTE(NULL != pbstrRemarks);
	*pbstrRemarks = CComBSTR(m_bstrRemarks).Detach();
	return (NULL != *pbstrRemarks) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of put_Remarks
inline HRESULT CTransform::put_Remarks(BSTR bstrRemarks)
{
	m_bstrRemarks = bstrRemarks;
	return (NULL != m_bstrRemarks.m_str) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of get_Abbreviation
inline HRESULT CTransform::get_Abbreviation(BSTR *pbstrAbbrev)
{
	_ASSERTE(NULL != pbstrAbbrev);
	*pbstrAbbrev = CComBSTR(m_bstrAbbreviation).Detach();
	return (NULL != *pbstrAbbrev) ? S_OK : E_OUTOFMEMORY;
}

// Implementation of put_Abbreviation
inline HRESULT CTransform::put_Abbreviation(BSTR bstrAbbrev)
{
	m_bstrAbbreviation = bstrAbbrev;
	return (NULL != m_bstrAbbreviation.m_str) ? S_OK : E_OUTOFMEMORY;
}
// Implementation of get_WellKnownText
inline HRESULT CTransform::get_WellKnownText(BSTR *pbstrWkt)
{
	return E_NOTIMPL;
}
#endif // defined(_USE_OGC_COMPATIBILITY)

///////////////////////////////////////////////////////////////////////////////
// alle bekannten Projektionen
#include "PCS_GaussKrueger.h"
#include "PCS_Generic.h"
#include "PCS_CylindricEquirectangular.h"
#include "PCS_LambertConicConformal2P.h"
#include "PCS_CassiniSoldner.h"

///////////////////////////////////////////////////////////////////////////////
// alle bekannten Datumstransformationen
#include "DS_ThroughECEF.h"
#include "DS_Through7Parameter.h"

#endif // __LIBCTF_H__F74904B0_F703_11d1_8F51_0060085FC1CE

