///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ScaleHeader.h | Koordinaten Scale/Offset-korrigieren

#if !defined(_SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_)
#define _SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

///////////////////////////////////////////////////////////////////////////////
//
class CSPoint : public CSSpoint
{
public:
	CSPoint (double dx, double dy, double dz = 0.0)
	{
		x = dx; y = dy; z = dz;
	}
};
typedef vector<CSSpoint> CPoints;

///////////////////////////////////////////////////////////////////////////////
//
class CScaleHeader
{
private:
	HPROJECT m_hPr;
	double m_dK11, m_dK12, m_dK21, m_dK22;
	double m_dOffsetX, m_dOffsetY;

protected:
	inline double GetHeaderDouble (LPCSTR pcKey, double dDefault = 0.0);
	double UnScaleX (const double dX, const double dY) const 
	{
		return m_dK11 * dX + m_dK12 * dY + m_dOffsetX;
	}
	double UnScaleY (const double dX, const double dY) const 
	{
		return m_dK21 * dX + m_dK22 * dY + m_dOffsetY;
	}

public:
	CScaleHeader();
	bool Initialize(HPROJECT hPr);

	HRESULT Scale (double dX, double dY, CPoints *pPoints)
	{
		ASSERT(NULL != m_hPr);
		try {
			pPoints -> push_back(CSPoint(UnScaleX(dX, dY), UnScaleY(dX, dY)));
		} catch (...) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}
};

#endif // !defined(_SCALEHEADER_H__562078F3_B0F2_11D1_859F_00600875138A__INCLUDED_)
