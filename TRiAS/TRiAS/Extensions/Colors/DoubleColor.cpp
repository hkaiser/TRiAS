// DoubleColor.cpp : Implementation of CDoubleColor

#include "stdafx.h"

#include "resource.h"

#include "rgb_hsb2.h"
#include "Colors.h"
#include "DoubleColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialization
HRESULT CDoubleColor::FinalConstruct (void)
{
	m_dRed = 0.0;
	m_dGreen = 0.0;
	m_dBlue = 0.0;

	m_dHue = 0.0;
	m_dSat = 0.0;
	m_dBright = 0.0;
	
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo methods

STDMETHODIMP CDoubleColor::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDoubleColor,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IDoubleColor methods

STDMETHODIMP CDoubleColor::get_RGB (long *plRGB)
{
	if (NULL == plRGB) return E_POINTER;

long lRed = long(m_dRed * 255.0 + 0.5);
long lGreen = long(m_dGreen * 255.0 + 0.5);
long lBlue = long(m_dBlue * 255.0 + 0.5);

	*plRGB = RGB(lRed, lGreen, lBlue);
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_RGB (long lRGB)
{
	m_dRed = double(GetRValue(lRGB))/255.0;
	m_dGreen = double(GetGValue(lRGB))/255.0;
	m_dBlue = double(GetBValue (lRGB))/255.0;

	RGBtoHSBService (m_dRed, m_dGreen, m_dBlue, m_dHue, m_dSat, m_dBright);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Red (double *pdRed)
{
	if (NULL == pdRed) return E_POINTER;

	*pdRed = m_dRed;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Red (double dRed)
{
	if (dRed < 0.0 || dRed > 1.0)
		return E_INVALIDARG;

	m_dRed = dRed;
	RGBtoHSBService (m_dRed, m_dGreen, m_dBlue, m_dHue, m_dSat, m_dBright);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Green (double *pdGreen)
{
	if (NULL == pdGreen) return E_POINTER;

	*pdGreen = m_dGreen;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Green (double dGreen)
{
	if (dGreen < 0.0 || dGreen > 1.0)
		return E_INVALIDARG;

	m_dGreen = dGreen;
	RGBtoHSBService (m_dRed, m_dGreen, m_dBlue, m_dHue, m_dSat, m_dBright);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Blue (double *pdBlue)
{
	if (NULL == pdBlue) return E_POINTER;

	*pdBlue = m_dBlue;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Blue (double dBlue)
{
	if (dBlue < 0.0 || dBlue > 1.0)
		return E_INVALIDARG;

	m_dBlue = dBlue;
	RGBtoHSBService (m_dRed, m_dGreen, m_dBlue, m_dHue, m_dSat, m_dBright);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Hue (double *pdHue)
{
	if (NULL == pdHue) return E_POINTER;

	*pdHue = m_dHue;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Hue (double dHue)
{
	if (dHue < 0.0 || dHue > 360.0)
		return E_INVALIDARG;

	m_dHue = dHue;
	HSBtoRGBService(m_dHue, m_dSat, m_dBright, m_dRed, m_dGreen, m_dBlue);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Saturation (double *pdSat)
{
	if (NULL == pdSat) return E_POINTER;

	*pdSat = m_dSat;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Saturation (double dSat)
{
	if (dSat < 0.0 || dSat > 1.0)
		return E_INVALIDARG;

	m_dSat = dSat;
	HSBtoRGBService(m_dHue, m_dSat, m_dBright, m_dRed, m_dGreen, m_dBlue);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Brightness (double *pdBright)
{
	if (NULL == pdBright) return E_POINTER;

	*pdBright = m_dBright;
	return S_OK;
}

STDMETHODIMP CDoubleColor::put_Brightness (double dBright)
{
	if (dBright < 0.0 || dBright > 1.0)
		return E_INVALIDARG;

	m_dBright = dBright;
	HSBtoRGBService(m_dHue, m_dSat, m_dBright, m_dRed, m_dGreen, m_dBlue);
	return S_OK;
}

STDMETHODIMP CDoubleColor::get_Complement (IDoubleColor **ppIColor)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDoubleColor::get_Saturated (IDoubleColor **ppIColor)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDoubleColor::get_Grayed (IDoubleColor **ppIColor)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDoubleColor::get_Pure (IDoubleColor **ppIColor)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDoubleColor::InitRGB (double dRed, double dGreen, double dBlue)
{
	if (dRed < 0.0 || dRed > 1.0) return E_INVALIDARG;
	if (dGreen < 0.0 || dGreen > 1.0) return E_INVALIDARG;
	if (dBlue < 0.0 || dBlue > 1.0)	return E_INVALIDARG;

	m_dRed = dRed;
	m_dGreen = dGreen;
	m_dBlue = dBlue;
	RGBtoHSBService (m_dRed, m_dGreen, m_dBlue, m_dHue, m_dSat, m_dBright);

	return S_OK;
}

STDMETHODIMP CDoubleColor::InitHSB (double dHue, double dSat, double dBright)
{
	if (dHue < 0.0 || dHue > 360.0) return E_INVALIDARG;
	if (dSat < 0.0 || dSat > 1.0) return E_INVALIDARG;
	if (dBright < 0.0 || dBright > 1.0) return E_INVALIDARG;

	m_dHue = dHue;
	m_dSat = dSat;
	m_dBright = dBright;
	HSBtoRGBService(m_dHue, m_dSat, m_dBright, m_dRed, m_dGreen, m_dBlue);

	return S_OK;
}

STDMETHODIMP CDoubleColor::RetrieveRGB (double *pdRed, double *pdGreen, double *pdBlue)
{
	if (NULL == pdRed || NULL == pdGreen || NULL == pdBlue)
		return E_POINTER;

	*pdRed = m_dRed;
	*pdGreen = m_dGreen;
	*pdBlue = m_dBlue;
	return S_OK;
}

STDMETHODIMP CDoubleColor::RetrieveHSB (double *pdHue, double *pdSat, double *pdBright)
{
	if (NULL == pdHue || NULL == pdSat || NULL == pdBright)
		return E_POINTER;

	*pdHue = m_dHue;
	*pdSat = m_dSat;
	*pdBright = m_dBright;
	return S_OK;
}

