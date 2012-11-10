// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 13:15:51
//
// @doc
// @module PCS_LambertConicConformal2P.cpp | Implementation of the <c CTPCSLambertConicConformal2P> class

#include "stdafx.h"
#include "LibCTFImpl.h"

HRESULT CTPCSLambertConicConformal2P::IsValid() 
{
HRESULT hr = CTransform::IsValid();

	return SUCCEEDED(hr) ? IsInitialized() : hr;
}

HRESULT CTPCSLambertConicConformal2P::EvalParams()
{
// Standard Parallels cannot be equal and on opposite sides of the equator
	if (fabs(m_firstParallel + m_secondParallel) < EPSLN) 
		return RCS_E_BADPARALLEL;
   
	m_es = 1.0 - SQUARE(m_MeSelf.m_HB / m_MeSelf.m_HA);
	m_e = sqrt(m_es);

double dSin1 = sin(m_firstParallel);
double ms1 = msfnz(m_e, dSin1, cos(m_firstParallel));
double ts1 = tsfnz(m_e, m_firstParallel, dSin1);

double dSin2 = sin(m_secondParallel);
double ms2 = msfnz(m_e, dSin2, cos(m_secondParallel));
double ts2 = tsfnz(m_e, m_secondParallel, dSin2);

double ts0 = tsfnz(m_e, m_latOrigin, sin(m_latOrigin));

	if (fabs(m_firstParallel - m_secondParallel) > EPSLN)
		m_ns = log(ms1/ms2) / log(ts1/ts2);
	else
		m_ns = dSin1;

	m_f0 = ms1 / (m_ns * pow(ts1, m_ns));
	m_rh = m_MeSelf.m_HA * m_f0 * pow(ts0, m_ns);

	return S_OK;
}

HRESULT CTPCSLambertConicConformal2P::SetParameters (long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);

// Parameter kopieren
	m_latOrigin = pParam[tcsPP_LambertConicConformal2SP_LatitudeOfFalseOrigin];
	m_lonOrigin = pParam[tcsPP_LambertConicConformal2SP_LongitudeOfFalseOrigin];
	m_falseEasting = pParam[tcsPP_LambertConicConformal2SP_EastingAtFalseOrigin];
	m_falseNorthing = pParam[tcsPP_LambertConicConformal2SP_NorthingAtFalseOrigin];
	m_firstParallel = pParam[tcsPP_LambertConicConformal2SP_LatitudeOfFirstStandardParallel];
	m_secondParallel = pParam[tcsPP_LambertConicConformal2SP_LatitudeOfSecondStandardParallel];

// weitere Parameter berechnen
	if (S_OK != EvalParams())
		return E_UNEXPECTED;

	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTPCSLambertConicConformal2P::GetDefaults (long nParams, double *pParam) 
{
	_ASSERTE(tcsPP_SizeOfParameterSet == nParams);
	pParam[tcsPP_LambertConicConformal2SP_LatitudeOfFalseOrigin] = m_latOrigin;
	pParam[tcsPP_LambertConicConformal2SP_LongitudeOfFalseOrigin] = m_lonOrigin;
	pParam[tcsPP_LambertConicConformal2SP_EastingAtFalseOrigin] = m_falseEasting;
	pParam[tcsPP_LambertConicConformal2SP_NorthingAtFalseOrigin] = m_falseNorthing;
	pParam[tcsPP_LambertConicConformal2SP_LatitudeOfFirstStandardParallel] = m_firstParallel;
	pParam[tcsPP_LambertConicConformal2SP_LatitudeOfSecondStandardParallel] = m_secondParallel;

// weitere Parameter berechnen
	if (S_OK != EvalParams())
		return E_UNEXPECTED;

	m_fIsInitialized = true;
	return S_OK;
}

// geod --> proj
HRESULT CTPCSLambertConicConformal2P::Transform (long nCoords, LPTCSDBLCOORD pData) 
{
	if (!IsInitialized())
		return S_FALSE;

	_ASSERTE(0 < nCoords);

double dHaF0 = m_MeSelf.m_HA * m_f0;

	for (long i = 0; i < nCoords; i++, pData++) {
	double dX = pData -> c1;
	double dY = pData -> c2;

		if (fabs(fabs(dY) - HALF_PI) > EPSLN) {
		double theta = m_ns * adjust_lon (dY - m_lonOrigin);
		double ts = tsfnz (m_e, dX, sin (dX));
		double rh1 = dHaF0 * pow (ts, m_ns);

			pData -> c1 = rh1 * sin(theta) + m_falseEasting;
			pData -> c2 = m_rh - rh1 * cos(theta) + m_falseNorthing;
		}
		else {
			if (dX * m_ns <= 0) 
				return RCS_E_CANTPROJECTPOINT;
			pData -> c1 = m_falseEasting;
			pData -> c2 = m_rh + m_falseNorthing;
		}
	}
	return S_OK;
}

// proj --> geod
HRESULT CTPCSLambertConicConformal2P::TransformInverse (long nCoords, LPTCSDBLCOORD pData) 
{
	if (!IsInitialized())
		return S_FALSE;

	_ASSERTE(0 < nCoords);
	
double dHaF0 = m_MeSelf.m_HA * m_f0;

	for (long i = 0; i < nCoords; i++, pData++) {
	long fErrorFlag = 0;
	double dX = pData -> c1 - m_falseEasting;
	double dY = m_rh - pData -> c2 + m_falseNorthing;
	double rh1, con;

		if (m_ns > 0) {
			rh1 = sqrt (dX * dX + dY * dY);
			con = 1.0;
		} 
		else {
			rh1 = -sqrt (dX * dX + dY * dY);
			con = -1.0;
		}
		
	double theta = 0.0;
		
		if (rh1 != 0)
			theta = atan2 ((con * dX), (con * dY));
		
		if ((rh1 != 0) || (m_ns > 0.0)) {
		double ts = pow ((rh1 / dHaF0), 1.0 / m_ns);

			dY = phi2z (m_e, ts, &fErrorFlag);
			if (fErrorFlag != 0)
			   return RCS_E_NOCONVERGENCE;
		}
		else
			dY = -HALF_PI;
		
		dX = adjust_lon (theta/m_ns + m_lonOrigin);

		pData -> c1 = dX;
		pData -> c2 = dY;
	}
	return S_OK;
}

