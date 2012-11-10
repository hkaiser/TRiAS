///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ScaleHeader.h | Koordinaten Scale/Offset-korrigieren

#if !defined(_SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_)
#define _SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/vector>

#include <dbtypes.h>
#include <HeaderEntry.h>
#include <CSSPoint.h>

///////////////////////////////////////////////////////////////////////////////
//
class _TRIAS01_ENTRY CScaleHeader
{
private:
	HPROJECT m_hPr;
	SCALEKOEFFS m_Koeffs;

protected:
	inline double GetHeaderDouble (LPCSTR pcKey, double dDefault = 0.0);
	bool Initialize(HPROJECT hPr);
	bool EvalInvKoeffs();

public:
	CScaleHeader();
	CScaleHeader(HPROJECT hPr);

// DBKoordinaten --> Realkoordinaten
	HRESULT UnScale (double dX, double dY, CPoints *pPoints)
	{
		_ASSERTE(NULL != m_hPr);
		try {
			pPoints -> push_back(CSPoint(UnScaleX(dX, dY), UnScaleY(dX, dY)));
		} catch (...) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}
	HRESULT UnScale (double dX, double dY, CSPointBase &rPoint)
	{
		rPoint.X = UnScaleX(dX, dY);
		rPoint.Y = UnScaleY(dX, dY);
		rPoint.Z = 0.0;
		return S_OK;
	}
	double UnScaleX (const double dX, const double dY) const 
	{
		return m_Koeffs.m_dK11 * dX + m_Koeffs.m_dK12 * dY + m_Koeffs.m_dOffsetX;
	}
	double UnScaleY (const double dX, const double dY) const 
	{
		return m_Koeffs.m_dK21 * dX + m_Koeffs.m_dK22 * dY + m_Koeffs.m_dOffsetY;
	}
	void UnScale (double dX, double dY, double *pdX, double *pdY)
	{
		*pdX = UnScaleX(dX, dY);
		*pdY = UnScaleY(dX, dY);
	}
	void UnScale (double &rdX, double &rdY)
	{
	double dX = UnScaleX(rdX, rdY), dY = UnScaleY(rdX, rdY);

		rdX = dX; rdY = dY;
	}

// Realkoordinaten --> DBKoordinaten
	HRESULT Scale (CSPointBase &rPoint, vector<double> *pdX, vector<double> *pdY)
	{
		_ASSERTE(NULL != m_hPr);
		try {
			pdX -> push_back(ScaleX(rPoint.X, rPoint.Y));
			pdY -> push_back(ScaleY(rPoint.X, rPoint.Y));
		} catch (...) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}
	double ScaleX (const double dX, const double dY) const 
	{
		return m_Koeffs.m_dInvK11 * (dX-m_Koeffs.m_dOffsetX) + m_Koeffs.m_dInvK12 * (dY-m_Koeffs.m_dOffsetY);
	}
	double ScaleY (const double dX, const double dY) const 
	{
		return m_Koeffs.m_dInvK21 * (dX-m_Koeffs.m_dOffsetX) + m_Koeffs.m_dInvK22 * (dY-m_Koeffs.m_dOffsetY);
	}
	void Scale (double dX, double dY, double *pdX, double *pdY)
	{
		*pdX = ScaleX(dX, dY);
		*pdY = ScaleY(dX, dY);
	}
	void Scale (double &rdX, double &rdY)
	{
	double dX = ScaleX(rdX, rdY), dY = ScaleY(rdX, rdY);

		rdX = dX; rdY = dY;
	}

	bool operator!() { return NULL == m_hPr ? true : false; }
};

#endif // !defined(_SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_)
