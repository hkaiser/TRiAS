// ColorLookUp.cpp : Implementation of CColorLookUp

#include "stdafx.h"

#include "resource.h"

#include "rgb_hsb2.h"
#include "Colors.h"
#include "ColorLookUp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo methods

STDMETHODIMP CColorLookUp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColorLookUp,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IColorLookUp methods

STDMETHODIMP CColorLookUp::Init (
	int iCnt, IDoubleColor *pIColor1, IDoubleColor *pIColor2, VARIANT vColor3)
{
	if (NULL == pIColor1 || NULL == pIColor2) return E_POINTER;

CComVariant vC3;
HRESULT hr = VariantChangeType (&vC3, &vColor3, 0, VT_DISPATCH);

	m_iSteps = iCnt;
	if (SUCCEEDED(hr)) {
	// 3 Farben gegeben
		if (iCnt < 3 || iCnt > 255) return E_INVALIDARG;
		try {
			m_StartColor = pIColor1;
			m_MiddleColor = pIColor2;
			m_EndColor = V_DISPATCH(&vC3);	// throws hr
		
			THROW_FAILED_HRESULT(InitColors3());

		} catch (HRESULT hr) {
			return hr;
		}

	} else {
		if (iCnt < 2 || iCnt > 255) return E_INVALIDARG;
		m_StartColor = pIColor1;
		m_EndColor = pIColor2;
		
		hr = InitColors2();
		if (FAILED(hr)) return hr;
	}

	return S_OK;
}

STDMETHODIMP CColorLookUp::get_Color (int iIndex, IDoubleColor **ppIColor)
{
	if (NULL == ppIColor) return E_POINTER;
	if (iIndex < 0 || iIndex >= m_iSteps) return E_INVALIDARG;

WDoubleColor DColor (m_Colors[iIndex]);
		
	*ppIColor = DColor.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
inline double RestrictToRange (double dMin, double dVal, double dMax)
{
	if (dVal < dMin) dVal = dMin;
	if (dVal > dMax) dVal = dMax;
	return dVal;
}

// Rücknormierung
inline double InvNorm (double dReiz, double dFaktor)
{
	return pow(RestrictToRange(0.0, dReiz, dFaktor)/dFaktor, 1.0/GAMMA);
}

HRESULT CColorLookUp::InitColors2 (void)
{
	m_Colors.erase();		// alle bisherigen löschen

// Helligkeiten der Einzelreize berechnen
double dRed, dGreen, dBlue;
double dYR1, dYG1, dYB1;
HRESULT hr = m_StartColor -> RetrieveRGB (&dRed, &dGreen, &dBlue);

	if (FAILED(hr)) return hr;
	dYR1 = HelligkeitRot (dRed);
	dYG1 = HelligkeitGruen (dGreen);
	dYB1 = HelligkeitBlau (dBlue);

double dYR2, dYG2, dYB2;

	hr = m_EndColor -> RetrieveRGB (&dRed, &dGreen, &dBlue);
	if (FAILED(hr)) return hr;

	dYR2 = HelligkeitRot (dRed);
	dYG2 = HelligkeitGruen (dGreen);
	dYB2 = HelligkeitBlau (dBlue);

double dYRDiff = dYR2 - dYR1;
double dYGDiff = dYG2 - dYG1;
double dYBDiff = dYB2 - dYB1;

// LambdaR/G/B (Farbanteile)
double dLambda = dYRDiff + dYGDiff + dYBDiff;

// Berechnung der Schrittweite aus der Stufenanzahl
double dBright1, dBright2;

	hr = m_StartColor -> get_Brightness (&dBright1);
	if (FAILED(hr)) return hr;
	hr = m_EndColor -> get_Brightness (&dBright2);
	if (FAILED(hr)) return hr;

	try {
	double dK = (dBright2-dBright1)/(m_iSteps-1);
	double dAct = dBright1;
	double dInvW1 = 0;

		for (int i = 0; i < m_iSteps; i++, dAct += dK) {
		// Helligkeit aus ZwischenWert rückrechnen
		double dInvW = InvWahrnehmung(dAct);

			if (0 == i) dInvW1 = dInvW;

		// evtl. auf Bezugswert skalieren
		double dDiff = dInvW - dInvW1;
		double dYRAct = (dDiff*dYRDiff)/dLambda + dYR1;
		double dYGAct = (dDiff*dYGDiff)/dLambda + dYG1;
		double dYBAct = (dDiff*dYBDiff)/dLambda + dYB1;

		// zurücknormieren
			dRed = InvNorm (dYRAct, BEZUGSWERT_ROT);
			dGreen = InvNorm (dYGAct, BEZUGSWERT_GRUEN);
			dBlue = InvNorm (dYBAct, BEZUGSWERT_BLAU);

		// neue DoubleColor erzeugen und zu FarbFeld hinzufügen
		WDoubleColor NewColor (CLSID_DoubleColor);	// throws hr

			THROW_FAILED_HRESULT(NewColor -> InitRGB (dRed, dGreen, dBlue));
			m_Colors.push_back (NewColor);
		}

	} catch (HRESULT hr) {
		return hr;
	} catch (...) {
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

HRESULT CColorLookUp::InitColors3 (void)
{
	return E_NOTIMPL;
}

